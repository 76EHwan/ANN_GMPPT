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

/**
 * Description
 * Minimum template to show how to use the Neural-ART Embedded Client API
 *          Re-target of the printf function is out-of-scope.
 *
 *
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
/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/

/* Input defs ----------------------------------------------------------------*/
#include "aiTestUtility.h"
/**

 // Array to store the data of the input tensor
 stai_ptr data_ins[] = {
 };
 */

/* Output defs ----------------------------------------------------------------*/

/**

 // c-array to store the data of the output tensor
 stai_ptr data_outs[] = {
 };
 */

/* Global byte buffer to save instantiated C-model network context */
STAI_NETWORK_CONTEXT_DECLARE(network_context, STAI_NETWORK_CONTEXT_SIZE)

/* Activations buffers -------------------------------------------------------*/

/* Entry points --------------------------------------------------------------*/

/* Array of pointer to manage the model's input/output tensors */
static stai_size in_length, out_length;
static stai_ptr stai_input[STAI_NETWORK_IN_NUM];
static stai_ptr stai_output[STAI_NETWORK_OUT_NUM];

/* 
 * Bootstrap
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

/* 
 * Run inference
 */
stai_return_code aiRun() {
	stai_return_code ret_code;

	/** Profiling code to calculate the inference time of the model. You can remove it if not needed */
	static uint32_t inference_nb = 0;
	static uint32_t total_cycles = 0;
	uint32_t start_tick, end_tick, end_dwt = 0;
	struct dwtTime t;
	cyclesCounterInit();

	LC_PRINT("---- Inference number %" PRIu32 " ----\r\n", inference_nb);
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
	/** End of inference */

	/** Continue profiling */
	end_dwt = cyclesCounterEnd();
	total_cycles += end_dwt;
	end_tick = HAL_GetTick();
	dwtCyclesToTime(end_dwt, &t);

	LC_PRINT(" duration DWT    : %d.%03d ms\r\n", t.s * 1000 + t.ms, t.us);
	LC_PRINT(" duration SysTick: %" PRIu32" ms\r\n", end_tick - start_tick);
	LC_PRINT(" CPU cycles      : %" PRIu32 "\r\n", end_dwt);
	LC_PRINT(" CPU cycles (avg): %" PRIu32 "\r\n",
			total_cycles / ++inference_nb);
//	LC_PRINT(" Sleep for 5s...\r\n");
//	HAL_Delay(5000);

	return ret_code;
}

#define IN_SCALE  0.00415258f
#define IN_ZP     (-118)

#define MPPT_DURATION_MS  10000U
#define MPPT_PERIOD_MS    20U          /* 제어 주기 */
#define MPPT_SETTLE_MS    5U           /* duty 변경 후 정착 */
#define MPPT_PWM_CH       TIM_CHANNEL_1 /* acquire와 동일하게. CubeMX가 CH2면 CH2로 */
#define DUTY_STEP         40           /* ARR=3999 기준 약 1% */
#define DUTY_MIN          200          /* ~5% */
#define DUTY_MAX          3600         /* ~90%, 부트스트랩 여유 */
#define DP_DEADBAND       2.0f         /* 미세 진동 억제 */

__attribute__((section(".dma_buffer"), aligned(32)))       uint32_t uhADC2ConvertedData[2];

volatile uint8_t adc_done = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc == &hadc2)
		adc_done = 1;
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

	/* rank1=ch5, rank2=ch10. 핀 배정에 맞춰 V/I 결정 */
	*i_raw = (uint16_t) uhADC2ConvertedData[0]; /* ch5  = PANEL_I 라고 가정 */
	*v_raw = (uint16_t) uhADC2ConvertedData[1]; /* ch10 = PANEL_V 라고 가정 */
	return 0;
}

int acquire_and_process_data() {
	/* USER CODE BEGIN acquire_and_process_data */
	int8_t *in = (int8_t*) stai_input[0];

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

	for (uint8_t i = 0; i < 8; i++) {
		uint32_t duty = htim1.Instance->ARR / 8 * (i + 1);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, duty);
		HAL_Delay(5); /* duty 변경 후 정착 대기 */

		adc_done = 0;
		MODIFY_REG(hadc2.Instance->CFGR1, ADC_CFGR1_DMNGT, ADC_CFGR1_DMNGT_0);
		if (HAL_ADC_Start_DMA(&hadc2, uhADC2ConvertedData, 2) != HAL_OK) {
			BSP_LED_On(LED_RED);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
			return -1;
		}
		uint32_t t0 = HAL_GetTick();
		while (!adc_done) {
			if (HAL_GetTick() - t0 > 100) {
				BSP_LED_On(LED_RED);
				HAL_ADC_Stop_DMA(&hadc2);
				HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
				return -1;
			}
		}
		HAL_ADC_Stop_DMA(&hadc2);

		in[i * 2] = quantize(uhADC2ConvertedData[0] / 4095.0f);
		in[i * 2 + 1] = quantize(uhADC2ConvertedData[1] / 4095.0f);

		HAL_Delay(10);
	}

	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);

	SCB_CleanDCache_by_Addr((uint32_t*) in, 16);
	return 0;
	/* USER CODE END acquire_and_process_data */
}

int post_process() {
	/* USER CODE BEGIN post_process */
	int8_t q = ((int8_t*) stai_output[0])[0];
	float mpp_hint = (q + 128) * 0.00390625f; /* 모델 출력 0~1 */
	LC_PRINT("out=%d (%.4f)\r\n", q, mpp_hint);

	uint32_t arr = htim1.Instance->ARR;

	/* 시작 duty: 모델 출력으로 초기점 잡기 (없으면 50%) */
	int32_t duty = (int32_t) (mpp_hint * (float) arr);
	if (duty < DUTY_MIN)
		duty = DUTY_MIN;
	if (duty > DUTY_MAX)
		duty = DUTY_MAX;

	int32_t dir = DUTY_STEP; /* 초기 탐색 방향 */
	float p_prev = -1.0f;

	HAL_TIM_PWM_Start(&htim1, MPPT_PWM_CH);
	/* CH2N 보완출력 쓰면: HAL_TIMEx_PWMN_Start(&htim1, MPPT_PWM_CH); */

	uint32_t start = HAL_GetTick();
	while (HAL_GetTick() - start < MPPT_DURATION_MS) {
		__HAL_TIM_SET_COMPARE(&htim1, MPPT_PWM_CH, (uint32_t ) duty);
		HAL_Delay(MPPT_SETTLE_MS);

		uint16_t v_raw, i_raw;
		if (adc_read_VI(&v_raw, &i_raw) != 0) {
			BSP_LED_On(LED_RED);
			break;
		}
		float power = (float) v_raw * (float) i_raw;

		if (p_prev >= 0.0f) {
			float dp = power - p_prev;
			if (dp < -DP_DEADBAND) {
				dir = -dir; /* 전력 감소 → 방향 반전 */
			} else if (dp <= DP_DEADBAND) {
				dir = 0; /* MPP 근처, 정지 (이번 스텝만) */
			}
		}
		p_prev = power;

		duty += (dir == 0 ? DUTY_STEP : dir); /* deadband면 한쪽으로 살짝 흔들어 재탐색 */
		if (duty < DUTY_MIN)
			duty = DUTY_MIN;
		if (duty > DUTY_MAX)
			duty = DUTY_MAX;

		BSP_LED_Toggle(LED_BLUE);
		HAL_Delay(MPPT_PERIOD_MS - MPPT_SETTLE_MS);
	}

	HAL_TIM_PWM_Stop(&htim1, MPPT_PWM_CH);
	/* HAL_TIMEx_PWMN_Stop(&htim1, MPPT_PWM_CH); */
	return 0;
	/* USER CODE END post_process */
}

/* ============================================================
 * Injection test (no ADC, no P&O).  <-- ADDED
 * Must sit here: after quantize()/stai_input/stai_output/aiRun are defined,
 * and before STM32CubeAI_Studio_AI_Process() which calls ai_inject_test().
 * NOTE: this line is NOT inside a USER CODE block, so re-add it after any
 *       .ioc regeneration. Keep the test file as .h so the IDE does NOT
 *       auto-compile it as a separate source.
 * ============================================================ */
#include "ai_inject_test.h"

/* 
 * Example of main loop function
 */
void main_loop() {
	/* USER CODE BEGIN main_loop */
	while (1) {
		/* 1 - Acquire, pre-process and fill the input buffers */
		acquire_and_process_data();

		/* 2 - Call inference engine */
		aiRun();

		/* 3 - Post-process the predictions */
		post_process();
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
	/* --- injection test: run once, print pred vs true, then idle --- */
	pwm_test();   /* duty 10→90% 무한 스윕 */
	while (1) {
		HAL_Delay(1000);
	}
	/* 원래 live 경로로 돌릴 땐 위 두 줄 지우고 아래 주석 해제 */
	// main_loop();
}

void STM32CubeAI_Studio_AI_Deinit(void) {
	aiDeinit();
}

#ifdef __cplusplus
}
#endif
