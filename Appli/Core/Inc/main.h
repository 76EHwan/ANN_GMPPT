/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined ( __ICCARM__ )
#  define CMSE_NS_CALL  __cmse_nonsecure_call
#  define CMSE_NS_ENTRY __cmse_nonsecure_entry
#else
#  define CMSE_NS_CALL  __attribute((cmse_nonsecure_call))
#  define CMSE_NS_ENTRY __attribute((cmse_nonsecure_entry))
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"

#include "stm32n6xx_nucleo.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* Function pointer declaration in non-secure*/
#if defined ( __ICCARM__ )
typedef void (CMSE_NS_CALL *funcptr)(void);
#else
typedef void CMSE_NS_CALL (*funcptr)(void);
#endif

/* typedef for non-secure callback functions */
typedef funcptr funcptr_NS;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWM_L_Pin GPIO_PIN_4
#define PWM_L_GPIO_Port GPIOC
#define PWR_EN_Pin GPIO_PIN_10
#define PWR_EN_GPIO_Port GPIOD
#define UCPD1_INT_Pin GPIO_PIN_2
#define UCPD1_INT_GPIO_Port GPIOD
#define LOAD_EN_Pin GPIO_PIN_2
#define LOAD_EN_GPIO_Port GPIOC
#define PANEL_EN_Pin GPIO_PIN_5
#define PANEL_EN_GPIO_Port GPIOD
#define PWM_H_Pin GPIO_PIN_7
#define PWM_H_GPIO_Port GPIOD
#define CAM_NRST_Pin GPIO_PIN_5
#define CAM_NRST_GPIO_Port GPIOO
#define BAT_V_Pin GPIO_PIN_3
#define BAT_V_GPIO_Port GPIOF
#define PANEL_I_Pin GPIO_PIN_9
#define PANEL_I_GPIO_Port GPIOA
#define TEMP_Pin GPIO_PIN_15
#define TEMP_GPIO_Port GPIOG
#define LOAD_I_Pin GPIO_PIN_10
#define LOAD_I_GPIO_Port GPIOA
#define UCPD1_ISENSE_Pin GPIO_PIN_5
#define UCPD1_ISENSE_GPIO_Port GPIOA
#define UCPD_PWR_EN_Pin GPIO_PIN_7
#define UCPD_PWR_EN_GPIO_Port GPIOA
#define UCPD1_VSENSE_Pin GPIO_PIN_11
#define UCPD1_VSENSE_GPIO_Port GPIOA
#define USB1_OCP_Pin GPIO_PIN_7
#define USB1_OCP_GPIO_Port GPION
#define OUTPUT_I_Pin GPIO_PIN_12
#define OUTPUT_I_GPIO_Port GPIOA
#define PANEL_V_Pin GPIO_PIN_8
#define PANEL_V_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
