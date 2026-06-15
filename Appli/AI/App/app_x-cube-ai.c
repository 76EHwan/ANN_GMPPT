/**
 ******************************************************************************
 * @file    app_x-cube-ai.c
 * @author  X-CUBE-AI C code generator
 * @brief   AI program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "app_x-cube-ai.h"
#include "bsp_ai.h"
#include "stai.h"
#include "npu_init.h"

/* USER CODE BEGIN includes */
#include "tim.h"
#include "adc.h"
#include "math.h"
/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

/* Input defs ----------------------------------------------------------------*/
#include "aiTestUtility.h"

/* Output defs ----------------------------------------------------------------*/

/* Global byte buffer to save instantiated C-model network context */
STAI_NETWORK_CONTEXT_DECLARE(network_context, STAI_NETWORK_CONTEXT_SIZE)

/* Activations buffers -------------------------------------------------------*/

/* Entry points --------------------------------------------------------------*/

/* Array of pointer to manage the model's input/output tensors */
static stai_size in_length, out_length;
static stai_ptr stai_input[STAI_NETWORK_IN_NUM];
static stai_ptr stai_output[STAI_NETWORK_OUT_NUM];

/* * Bootstrap
 */
int aiInit(void) {
	stai_return_code ret_code;

	/* 1: Initialize runtime library */
	ret_code = stai_runtime_init();

	/* 2: Initialize network model context */
	ret_code = stai_network_init(network_context);
	ret_code = stai_network_get_inputs(network_context, stai_input, &in_length);
	ret_code = stai_network_get_outputs(network_context, stai_output,
			&out_length);

	return 0;
}

int aiDeinit(void) {
	stai_return_code ret_code;

	/* 1: Deinitialize network model context */
	ret_code = stai_network_deinit(network_context);

	/* 2: Deinitialize runtime library */
	ret_code = stai_runtime_deinit();

	return 0;
}

/* * Run inference
 */
stai_return_code aiRun() {
	stai_return_code ret_code;

	static uint32_t inference_nb = 0;
	static uint32_t total_cycles = 0;
	uint32_t start_tick, end_tick, end_dwt = 0;
	struct dwtTime t;
	cyclesCounterInit();

	LC_PRINT("\r\n---- Inference number %" PRIu32 " ----\r\n", inference_nb);
	LC_PRINT("Results for network \"%s\"\r\nRunning...\r\n",
			STAI_NETWORK_C_MODEL_NAME);
	cyclesCounterStart();
	start_tick = HAL_GetTick();

	/* Perform the inference */
	ret_code = stai_network_run(network_context, STAI_MODE_SYNC);
	if (ret_code != STAI_SUCCESS) {
		ret_code = stai_network_get_error(network_context);
		LC_PRINT("Inference failed with error code %s\r\n",
				stai_get_return_code_name(ret_code));
	};

	end_dwt = cyclesCounterEnd();
	total_cycles += end_dwt;
	end_tick = HAL_GetTick();
	dwtCyclesToTime(end_dwt, &t);

	LC_PRINT(" duration DWT    : %d.%03d ms\r\n", t.s * 1000 + t.ms, t.us);
	LC_PRINT(" duration SysTick: %" PRIu32" ms\r\n", end_tick - start_tick);
	LC_PRINT(" CPU cycles      : %" PRIu32 "\r\n", end_dwt);
	LC_PRINT(" CPU cycles (avg): %" PRIu32 "\r\n",
			total_cycles / ++inference_nb);

	return ret_code;
}

/* USER CODE BEGIN PVD_Defines */
#define IN_SCALE  0.00415258f
#define IN_ZP     (-118)

#define MPPT_DURATION_MS  2000U
#define MPPT_PERIOD_MS    20U          /* 제어 주기 */
#define MPPT_SETTLE_MS    5U           /* duty 변경 후 정착 대기 시간 */
#define MPPT_PWM_CH       TIM_CHANNEL_2 /* buck 제어 채널 (sweep / P&O 공통) */
#define DUTY_STEP         40           /* ARR=3999 기준 약 1% */
#define DUTY_MIN          200          /* ~5% */
#define DUTY_MAX          3600         /* ~90% */

/* 하드웨어 변환 파라미터 (단위: 실제 물리량) */
#define V_REF            3.3f                     /* MCU ADC 기준 전압 (V) */
#define V_DIVIDER_RATIO  ((80.6f + 2.2f) / 2.2f)  /* 전압 분배 저항 비율 (약 37.636배) */
#define INA241_GAIN      100.0f                   /* INA241A4 증폭비 (V/V) */
#define R_SHUNT          0.005f                   /* 션트 저항 5mΩ (Ω) */
#define I_SENSE_RATIO    (INA241_GAIN * R_SHUNT)  /* 센서 최종 감도 (0.5 V/A) */

/* P&O 제어용 데드밴드 (기존 Raw값 대신 실제 와트(W) 단위 사용) */
#define DP_DEADBAND_W     0.5f                    /* 이 값보다 더 떨어질 때만 방향 반전 (패널 용량에 맞춰 수정하세요) */

__attribute__((section(".dma_buffer"), aligned(32)))  uint32_t uhADC2ConvertedData[2];
volatile uint8_t adc_done = 0;
/* USER CODE END PVD_Defines */

/* USER CODE BEGIN ADC_Callback */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc == &hadc2) {
		adc_done = 1;
	}
}

static inline int8_t quantize(float x) {
	int32_t q = (int32_t) lroundf(x / IN_SCALE) + IN_ZP;
	if (q > 127)
		q = 127;
	if (q < -128)
		q = -128;
	return (int8_t) q;
}

static int adc_read_VI(uint16_t *v_raw, uint16_t *i_raw) {
	adc_done = 0;
	MODIFY_REG(hadc2.Instance->CFGR1, ADC_CFGR1_DMNGT, ADC_CFGR1_DMNGT_0);
	if (HAL_ADC_Start_DMA(&hadc2, uhADC2ConvertedData, 2) != HAL_OK)
		return -1;

	uint32_t t0 = HAL_GetTick();
	while (!adc_done) {
		if (HAL_GetTick() - t0 > 100) {
			HAL_ADC_Stop_DMA(&hadc2);
			return -1;
		}
	}
	HAL_ADC_Stop_DMA(&hadc2);
	SCB_InvalidateDCache_by_Addr((void*) uhADC2ConvertedData,
			sizeof(uhADC2ConvertedData));
	*v_raw = (uint16_t) uhADC2ConvertedData[0]; /* rank1 = CH5 = PA8 = 전압 */
	*i_raw = (uint16_t) uhADC2ConvertedData[1]; /* rank2 = CH10 = PA9 = 전류 */
	return 0;
}
/* USER CODE END ADC_Callback */

int acquire_and_process_data() {
	/* USER CODE BEGIN acquire_and_process_data */
	int8_t *in = (int8_t*) stai_input[0];

	HAL_TIM_PWM_Start(&htim1, MPPT_PWM_CH);
	LC_PRINT("\r\n[Data Acquisition] Starting 8-point sweep...\r\n");

	/* 8개의 샘플 포인트 스윕으로 AI 모델 입력 데이터 구성 */
	for (uint8_t i = 0; i < 8; i++) {
		uint32_t duty = htim1.Instance->ARR / 8 * (i + 1);
		__HAL_TIM_SET_COMPARE(&htim1, MPPT_PWM_CH, duty);
		HAL_Delay(5); /* duty 변경 후 정착 대기 */

		adc_done = 0;
		MODIFY_REG(hadc2.Instance->CFGR1, ADC_CFGR1_DMNGT, ADC_CFGR1_DMNGT_0);
		if (HAL_ADC_Start_DMA(&hadc2, uhADC2ConvertedData, 2) != HAL_OK) {
			BSP_LED_On(LED_RED);
			HAL_TIM_PWM_Stop(&htim1, MPPT_PWM_CH);
			return -1;
		}

		uint32_t t0 = HAL_GetTick();
		while (!adc_done) {
			if (HAL_GetTick() - t0 > 100) {
				BSP_LED_On(LED_RED);
				HAL_ADC_Stop_DMA(&hadc2);
				HAL_TIM_PWM_Stop(&htim1, MPPT_PWM_CH);
				return -1;
			}
		}
		HAL_ADC_Stop_DMA(&hadc2);
		/* DMA가 SRAM에 쓴 새 값을 읽기 전 D-cache 무효화 (이게 없으면 8개 동일) */
		SCB_InvalidateDCache_by_Addr((void*) uhADC2ConvertedData,
				sizeof(uhADC2ConvertedData));

		in[i * 2] = quantize(uhADC2ConvertedData[0] / 4095.0f);     /* [0]=전압 */
		in[i * 2 + 1] = quantize(uhADC2ConvertedData[1] / 4095.0f); /* [1]=전류 */

		LC_PRINT(" Sweep [%d] Duty: %lu | V_raw: %lu, I_raw: %lu\r\n", i, duty,
				uhADC2ConvertedData[0], uhADC2ConvertedData[1]);

		HAL_Delay(10);
	}

	HAL_TIM_PWM_Stop(&htim1, MPPT_PWM_CH);

	SCB_CleanDCache_by_Addr((uint32_t*) in, 16);
	return 0;
	/* USER CODE END acquire_and_process_data */
}

int post_process() {
	/* USER CODE BEGIN post_process */
	int8_t q = ((int8_t*) stai_output[0])[0];
	float mpp_hint = (q + 128) * 0.00390625f; /* 모델 출력 0~1 매핑 */
	LC_PRINT("AI Predicted MPP Out=%d (%.4f)\r\n", q, mpp_hint);
	LC_PRINT("[MPPT Tracking] Starting P&O Algorithm...\r\n");

	uint32_t arr = htim1.Instance->ARR;

	/* AI 추론 결과를 P&O 알고리즘의 초기 Duty로 설정 */
	int32_t duty = (int32_t) (mpp_hint * (float) arr);
	if (duty < DUTY_MIN)
		duty = DUTY_MIN;
	if (duty > DUTY_MAX)
		duty = DUTY_MAX;

	int32_t dir = DUTY_STEP;
	float p_prev = -1.0f;

	HAL_TIM_PWM_Start(&htim1, MPPT_PWM_CH);

	uint32_t start = HAL_GetTick();
	while (HAL_GetTick() - start < MPPT_DURATION_MS) {
		__HAL_TIM_SET_COMPARE(&htim1, MPPT_PWM_CH, (uint32_t ) duty);
		HAL_Delay(MPPT_SETTLE_MS);

		uint16_t v_raw, i_raw;
		if (adc_read_VI(&v_raw, &i_raw) != 0) {
			BSP_LED_On(LED_RED);
			break;
		}

		/* 1. 실제 전압 계산 (V) */
		float actual_voltage = ((float) v_raw / 4095.0f) * V_REF
				* V_DIVIDER_RATIO;

		/* 2. 실제 전류 계산 (A) */
		float v_out_i = ((float) i_raw / 4095.0f) * V_REF; // 전류 앰프에서 나온 전압
		float actual_current = v_out_i / I_SENSE_RATIO;   // A 단위로 변환

		/* 3. 실제 전력 계산 (W) */
		float power_w = actual_voltage * actual_current;

		/* UART 출력 (터미널에서 실제 물리량을 직관적으로 확인) */
		LC_PRINT(
				" MPPT Duty: %4ld | V: %5.2f V, I: %5.2f A, Power: %6.2f W\r\n",
				duty, actual_voltage, actual_current, power_w);

		/* P&O: 전력이 dead-band 이상으로 떨어지면 방향 반전, 그 외엔 직전 방향 유지 */
		if (p_prev >= 0.0f) {
			float dp = power_w - p_prev;
			if (dp < -DP_DEADBAND_W) {
				dir = -dir; /* 전력 감소 → 방향 반전 */
			}
			/* 전력 증가 또는 dead-band 이내 → 방향 유지 */
		}
		p_prev = power_w;

		duty += dir; /* dir은 항상 ±DUTY_STEP, MPP 근처에서 ±1 step 진동 */
		if (duty < DUTY_MIN)
			duty = DUTY_MIN;
		if (duty > DUTY_MAX)
			duty = DUTY_MAX;

		BSP_LED_Toggle(LED_BLUE);
		HAL_Delay(MPPT_PERIOD_MS - MPPT_SETTLE_MS);
	}

	HAL_TIM_PWM_Stop(&htim1, MPPT_PWM_CH);
	return 0;
	/* USER CODE END post_process */
}

/* * Example of main loop function
 */
void main_loop() {
	/* USER CODE BEGIN main_loop */
	while (1) {
		/* 1 - Acquire, pre-process and fill the input buffers */
		if (acquire_and_process_data() == 0) {
			/* 2 - Call inference engine */
			aiRun();

			/* 3 - Post-process the predictions and run MPPT */
			post_process();
		} else {
			/* ADC 에러 시 잠시 대기 후 재시도 */
			LC_PRINT("Error: ADC reading failed. Retrying...\r\n");
			HAL_Delay(1000);
		}
	}
	/* USER CODE END main_loop */
}

/* Entry points --------------------------------------------------------------*/

void STM32CubeAI_Studio_AI_Init(void) {
	MX_UARTx_Init();
	aiPreInitialize();
	aiInit();
	/* USER CODE BEGIN init */
	/* USER CODE END init */
}

void STM32CubeAI_Studio_AI_Process(void) {
	/* USER CODE BEGIN process */
	/* 실제 운용 시작을 위해 패널 활성화 (핀 명칭 및 포트 확인 필요) */
	HAL_GPIO_WritePin(PANEL_EN_GPIO_Port, PANEL_EN_Pin, GPIO_PIN_SET);
	LC_PRINT("Panel Enabled. Starting Main Loop...\r\n");

	/* 메인 제어 루프 실행 */
	main_loop();
	/* USER CODE END process */
}

void STM32CubeAI_Studio_AI_Deinit(void) {
	aiDeinit();
}

#ifdef __cplusplus
}
#endif
