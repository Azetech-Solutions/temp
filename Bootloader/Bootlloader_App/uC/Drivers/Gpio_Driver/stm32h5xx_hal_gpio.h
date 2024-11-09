/**
  ******************************************************************************
  * @file    stm32h5xx_hal_gpio.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_HAL_GPIO_H
#define STM32H5xx_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx.h"

#define GPIO_MODE             (0x00000003U)
#define EXTI_MODE             (0x10000000U)
#define GPIO_MODE_IT          (0x00010000U)
#define GPIO_MODE_EVT         (0x00020000U)
#define RISING_EDGE           (0x00100000U)
#define FALLING_EDGE          (0x00200000U)
#define GPIO_OUTPUT_TYPE      (0x00000010U)
#define GPIO_NUMBER           (16U)

#define PORTA_CLOCK_ENABLE()   	RCC->AHB2ENR |= (1<<0)
#define PORTB_CLOCK_ENABLE()   	RCC->AHB2ENR |= (1<<1)
#define PORTC_CLOCK_ENABLE()   	RCC->AHB2ENR |= (1<<2)
#define PORTD_CLOCK_ENABLE()   	RCC->AHB2ENR |= (1<<3)
#define PORTH_CLOCK_ENABLE()   	RCC->AHB2ENR |= (1<<7)

#define USART3_CLOCK_ENABLE()	  (RCC->APB1LENR = RCC_APB1LENR_USART3EN) 
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_RTC_50HZ      ((uint8_t)0x00)  /* RTC_50Hz Alternate Function mapping                       */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /* SWJ (SWD and JTAG) Alternate Function mapping             */
#define GPIO_AF0_TRACE         ((uint8_t)0x00)  /* TRACE Alternate Function mapping                          */
#define GPIO_AF0_CSLEEP        ((uint8_t)0x00)  /* CSLEEP Alternate Function mapping                         */
#define GPIO_AF0_CSTOP         ((uint8_t)0x00)  /* CSTOP Alternate Function mapping                          */
#define GPIO_AF0_CRS           ((uint8_t)0x00)  /* CRS Alternate Function mapping                            */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /* TIM1 Alternate Function mapping                           */
#define GPIO_AF1_TIM2          ((uint8_t)0x01)  /* TIM2 Alternate Function mapping                           */
#if defined(TIM16)
#define GPIO_AF1_TIM16         ((uint8_t)0x01)  /* TIM16 Alternate Function mapping                          */
#endif /* TIM16 */
#if defined(TIM17)
#define GPIO_AF1_TIM17         ((uint8_t)0x01)  /* TIM17 Alternate Function mapping                          */
#endif /* TIM17 */
#if (defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx))
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01)  /* LPTIM1 Alternate Function mapping                         */
#endif /* defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx) */

/**
  * @brief   AF 2 selection
  */
#if defined(STM32H503xx)
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /* LPTIM1 Alternate Function mapping                         */
#endif /* STM32H503xx */
#if defined(LPTIM3)
#define GPIO_AF2_LPTIM3        ((uint8_t)0x02)  /* LPTIM3 Alternate Function mapping                         */
#endif /* LPTIM3 */
#if defined(SAI1)
#define GPIO_AF2_SAI1          ((uint8_t)0x02)  /* SAI1 Alternate Function mapping                           */
#endif /* SAI1 */
#define GPIO_AF2_TIM3          ((uint8_t)0x02)  /* TIM3 Alternate Function mapping                           */
#if defined(TIM4)
#define GPIO_AF2_TIM4          ((uint8_t)0x02)  /* TIM4 Alternate Function mapping                           */
#endif /* TIM4 */
#if defined(TIM5)
#define GPIO_AF2_TIM5          ((uint8_t)0x02)  /* TIM5 Alternate Function mapping                           */
#endif /* TIM5 */
#if defined(TIM12)
#define GPIO_AF2_TIM12         ((uint8_t)0x02)  /* TIM12 Alternate Function mapping                          */
#endif /* TIM12 */
#if defined(TIM15)
#define GPIO_AF2_TIM15         ((uint8_t)0x02)  /* TIM15 Alternate Function mapping                          */
#endif /* TIM15 */
/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_I3C1          ((uint8_t)0x03)  /* I3C1 Alternate Function mapping                           */
#if defined(I3C2)
#define GPIO_AF3_I3C2          ((uint8_t)0x03)  /* I3C2 Alternate Function mapping                           */
#endif /* I3C2 */
#define GPIO_AF3_LPTIM2        ((uint8_t)0x03)  /* LPTIM2 Alternate Function mapping                         */
#if defined(LPTIM3)
#define GPIO_AF3_LPTIM3        ((uint8_t)0x03)  /* LPTIM3 Alternate Function mapping                         */
#endif /* LPTIM3 */
#define GPIO_AF3_LPUART1       ((uint8_t)0x03)  /* LPUART1 Alternate Function mapping                        */
#if defined(OCTOSPI1)
#define GPIO_AF3_OCTOSPI1      ((uint8_t)0x03)  /* OCTOSPI1 Alternate Function mapping                       */
#endif /* OCTOSPI1 */
#if (defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx))
#define GPIO_AF3_TIM1          ((uint8_t)0x03)  /* TIM1 Alternate Function mapping                           */
#endif /* defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx) */
#if defined(TIM8)
#define GPIO_AF3_TIM8          ((uint8_t)0x03)  /* TIM8 Alternate Function mapping                           */
#endif /* TIM8 */

/**
  * @brief   AF 4 selection
  */
#if defined(CEC)
#define GPIO_AF4_CEC           ((uint8_t)0x04)  /* CEC Alternate Function mapping                            */
#endif /* CEC */
#if defined(DCMI)
#define GPIO_AF4_DCMI          ((uint8_t)0x04)  /* DCMI Alternate Function mapping                           */
#define GPIO_AF4_PSSI          ((uint8_t)0x04)  /* PSSI Alternate Function mapping                           */
#endif /* DCMI */
#define GPIO_AF4_I2C1          ((uint8_t)0x04)  /* I2C1 Alternate Function mapping                           */
#define GPIO_AF4_I2C2          ((uint8_t)0x04)  /* I2C2 Alternate Function mapping                           */
#if defined(I2C3)
#define GPIO_AF4_I2C3          ((uint8_t)0x04)  /* I2C3 Alternate Function mapping                           */
#endif /* I2C3 */
#if defined(I2C4)
#define GPIO_AF4_I2C4          ((uint8_t)0x04)  /* I2C4 Alternate Function mapping                           */
#endif /* I2C4 */
#define GPIO_AF4_LPTIM1        ((uint8_t)0x04)  /* LPTIM1 Alternate Function mapping                         */
#define GPIO_AF4_LPTIM2        ((uint8_t)0x04)  /* LPTIM2 Alternate Function mapping                         */
#define GPIO_AF4_SPI1          ((uint8_t)0x04)  /* SPI1 Alternate Function mapping                           */
#if defined(TIM15)
#define GPIO_AF4_TIM15         ((uint8_t)0x04)  /* TIM15 Alternate Function mapping                          */
#endif /* TIM15 */
#define GPIO_AF4_USART1        ((uint8_t)0x04)  /* USART1 Alternate Function mapping                         */
#if defined(STM32H503xx)
#define GPIO_AF4_USART2        ((uint8_t)0x04)  /* USART2 Alternate Function mapping                         */
#endif /* STM32H503xx */

/**
  * @brief   AF 5 selection
  */
#if defined(CEC)
#define GPIO_AF5_CEC           ((uint8_t)0x05)  /* CEC Alternate Function mapping                            */
#endif /* CEC */
#if (defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx))
#define GPIO_AF5_I3C1          ((uint8_t)0x05)  /* I3C1 Alternate Function mapping                           */
#define GPIO_AF5_SPI3          ((uint8_t)0x05)  /* SPI3 Alternate Function mapping                           */
#endif /* defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx) */
#define GPIO_AF5_LPTIM1        ((uint8_t)0x05)  /* LPTIM1 Alternate Function mapping                         */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /* SPI1 Alternate Function mapping                           */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /* SPI2 Alternate Function mapping                           */
#if defined(SPI4)
#define GPIO_AF5_SPI4          ((uint8_t)0x05)  /* SPI4 Alternate Function mapping                           */
#endif /* SPI4 */
#if defined(SPI5)
#define GPIO_AF5_SPI5          ((uint8_t)0x05)  /* SPI5 Alternate Function mapping                           */
#endif /* SPI5 */
#if defined(SPI6)
#define GPIO_AF5_SPI6          ((uint8_t)0x05)  /* SPI6 Alternate Function mapping                           */
#endif /* SPI6 */

/**
  * @brief   AF 6 selection
  */
#if defined(I2C4)
#define GPIO_AF6_I2C4          ((uint8_t)0x06)  /* I2C4 Alternate Function mapping                           */
#endif /* I2C4 */
#if defined(OCTOSPI1)
#define GPIO_AF6_OCTOSPI1      ((uint8_t)0x06)  /* OCTOSPI1 Alternate Function mapping                       */
#endif /* OCTOSPI1 */
#if defined(SAI1)
#define GPIO_AF6_SAI1          ((uint8_t)0x06)  /* SAI1 Alternate Function mapping                           */
#endif /* SAI1 */
#if defined(STM32H503xx)
#define GPIO_AF6_SPI1          ((uint8_t)0x06)  /* SPI1 Alternate Function mapping                           */
#define GPIO_AF6_SPI2          ((uint8_t)0x06)  /* SPI2 Alternate Function mapping                           */
#endif /* STM32H503xx */
#define GPIO_AF6_SPI3          ((uint8_t)0x06)  /* SPI3 Alternate Function mapping                           */
#if defined(SPI4)
#define GPIO_AF6_SPI4          ((uint8_t)0x06)  /* SPI4 Alternate Function mapping                           */
#endif /* SPI4 */
#if defined(UART4)
#define GPIO_AF6_UART4         ((uint8_t)0x06)  /* UART4 Alternate Function mapping                          */
#endif /* UART4 */
#if defined(UART12)
#define GPIO_AF6_UART12        ((uint8_t)0x06)  /* UART12 Alternate Function mapping                         */
#endif /* UART12 */
#if defined(USART10)
#define GPIO_AF6_USART10       ((uint8_t)0x06)  /* USART10 Alternate Function mapping                        */
#endif /* USART10 */
#if defined(UCPD1)
#define GPIO_AF6_UCPD1         ((uint8_t)0x06)  /* UCPD1 Alternate Function mapping                          */
#endif /* UCPD1 */

/**
  * @brief   AF 7 selection
  */
#if defined(SDMMC1)
#define GPIO_AF7_SDMMC1        ((uint8_t)0x07)  /* SDMMC1 Alternate Function mapping                         */
#endif /* SDMMC1 */
#define GPIO_AF7_SPI2          ((uint8_t)0x07)  /* SPI2 Alternate Function mapping                           */
#define GPIO_AF7_SPI3          ((uint8_t)0x07)  /* SPI3 Alternate Function mapping                           */
#if defined(SPI6)
#define GPIO_AF7_SPI6          ((uint8_t)0x07)  /* SPI6 Alternate Function mapping                           */
#endif /* SPI6 */
#if defined(UART7)
#define GPIO_AF7_UART7         ((uint8_t)0x07)  /* UART7 Alternate Function mapping                          */
#endif /* UART7 */
#if defined(UART8)
#define GPIO_AF7_UART8         ((uint8_t)0x07)  /* UART8 Alternate Function mapping                          */
#endif /* UART8 */
#if defined(UART12)
#define GPIO_AF7_UART12        ((uint8_t)0x07)  /* UART12 Alternate Function mapping                         */
#endif /* UART12 */
#define GPIO_AF7_USART1        ((uint8_t)0x07)  /* USART1 Alternate Function mapping                         */
#define GPIO_AF7_USART2        ((uint8_t)0x07)  /* USART2 Alternate Function mapping                         */
#define GPIO_AF7_USART3        ((uint8_t)0x07)  /* USART3 Alternate Function mapping                         */
#if defined(USART6)
#define GPIO_AF7_USART6        ((uint8_t)0x07)  /* USART6 Alternate Function mapping                         */
#endif /* USART6 */
#if defined(USART10)
#define GPIO_AF7_USART10       ((uint8_t)0x07)  /* USART10 Alternate Function mapping                        */
#endif /* USART10 */
#if defined(USART11)
#define GPIO_AF7_USART11       ((uint8_t)0x07)  /* USART11 Alternate Function mapping                        */
#endif /* USART11 */

/**
  * @brief   AF 8 selection
  */
#if defined(STM32H503xx)
#define GPIO_AF8_I2C2          ((uint8_t)0x08)  /* I2C2 Alternate Function mapping                           */
#define GPIO_AF8_I3C1          ((uint8_t)0x08)  /* I3C1 Alternate Function mapping                           */
#define GPIO_AF8_USART1        ((uint8_t)0x08)  /* USART1 Alternate Function mapping                         */
#endif /* STM32H503xx */
#define GPIO_AF8_LPUART1       ((uint8_t)0x08)  /* LPUART1 Alternate Function mapping                        */
#if defined(SAI2)
#define GPIO_AF8_SAI2          ((uint8_t)0x08)  /* SAI2 Alternate Function mapping                           */
#endif /* SAI2 */
#if defined(SDMMC1)
#define GPIO_AF8_SDMMC1        ((uint8_t)0x08)  /* SDMMC1 Alternate Function mapping                         */
#endif /* SDMMC1 */
#if defined(SPI6)
#define GPIO_AF8_SPI6          ((uint8_t)0x08)  /* SPI6 Alternate Function mapping                           */
#endif /* SPI6 */
#if defined(UART4)
#define GPIO_AF8_UART4         ((uint8_t)0x08)  /* UART4 Alternate Function mapping                          */
#endif /* UART4 */
#if defined(UART5)
#define GPIO_AF8_UART5         ((uint8_t)0x08)  /* UART5 Alternate Function mapping                          */
#endif /* UART5 */
#if defined(UART8)
#define GPIO_AF8_UART8         ((uint8_t)0x08)  /* UART8 Alternate Function mapping                          */
#endif /* UART8 */

/**
  * @brief   AF 9 selection
  */
#define GPIO_AF9_FDCAN1        ((uint8_t)0x09)  /* FDCAN1 Alternate Function mapping                         */
#if defined(FDCAN2)
#define GPIO_AF9_FDCAN2        ((uint8_t)0x09)  /* FDCAN2 Alternate Function mapping                         */
#endif /* FDCAN2 */
#if defined(FMC_BANK1)
#define GPIO_AF9_FMC           ((uint8_t)0x09)  /* FMC Alternate Function mapping                            */
#endif /* FMC_BANK1 */
#if defined(OCTOSPI1)
#define GPIO_AF9_OCTOSPI1      ((uint8_t)0x09)  /* OCTOSPI1 Alternate Function mapping                       */
#endif /* OCTOSPI1 */
#if defined(SDMMC2)
#define GPIO_AF9_SDMMC2        ((uint8_t)0x09)  /* SDMMC2 Alternate Function mapping                         */
#endif /* SDMMC2 */
#if defined(TIM13)
#define GPIO_AF9_TIM13         ((uint8_t)0x09)  /* TIM13 Alternate Function mapping                          */
#endif /* TIM13 */
#if defined(TIM14)
#define GPIO_AF9_TIM14         ((uint8_t)0x09)  /* TIM14 Alternate Function mapping                          */
#endif /* TIM14 */
#if defined(STM32H503xx)
#define GPIO_AF9_USART2        ((uint8_t)0x09)  /* USART2 Alternate Function mapping                         */
#define GPIO_AF9_USART3        ((uint8_t)0x09)  /* USART3 Alternate Function mapping                         */
#endif /* STM32H503xx */

/**
  * @brief   AF 10 selection
  */
#define GPIO_AF10_CRS          ((uint8_t)0x0A)  /* CRS Alternate Function mapping                            */
#if defined(STM32H503xx)
#define GPIO_AF10_I3C1         ((uint8_t)0x0A)  /* I3C1 Alternate Function mapping                           */
#define GPIO_AF10_I3C2         ((uint8_t)0x0A)  /* I3C2 Alternate Function mapping                           */
#define GPIO_AF10_SPI3         ((uint8_t)0x0A)  /* SPI3 Alternate Function mapping                           */
#endif /* STM32H503xx */
#if defined(FMC_BANK1)
#define GPIO_AF10_FMC          ((uint8_t)0x0A)  /* FMC Alternate Function mapping                            */
#endif /* FMC_BANK1 */
#if defined(OCTOSPI1)
#define GPIO_AF10_OCTOSPI1     ((uint8_t)0x0A)  /* OCTOSPI1 Alternate Function mapping                       */
#endif /* OCTOSPI1 */
#if defined(SAI2)
#define GPIO_AF10_SAI2         ((uint8_t)0x0A)  /* SAI2 Alternate Function mapping                           */
#endif /* SAI2 */
#if defined(SDMMC2)
#define GPIO_AF10_SDMMC2       ((uint8_t)0x0A)  /* SDMMC2 Alternate Function mapping                         */
#endif /* SDMMC2 */
#if defined(TIM8)
#define GPIO_AF10_TIM8         ((uint8_t)0x0A)  /* TIM8 Alternate Function mapping                           */
#endif /* TIM8 */
#define GPIO_AF10_USB          ((uint8_t)0x0A)  /* USB Alternate Function mapping                            */

/**
  * @brief   AF 11 selection
  */
#if defined(ETH)
#define GPIO_AF11_ETH          ((uint8_t)0x0B)  /* ETH Alternate Function mapping                            */
#endif /* ETH */
#if defined(FMC_BANK1)
#define GPIO_AF11_FMC          ((uint8_t)0x0B)  /* FMC Alternate Function mapping                            */
#endif /* FMC_BANK1 */
#if defined(OCTOSPI1)
#define GPIO_AF11_OCTOSPI1     ((uint8_t)0x0B)  /* OCTOSPI1 Alternate Function mapping                       */
#endif /* OCTOSPI1 */
#if defined(SDMMC2)
#define GPIO_AF11_SDMMC2       ((uint8_t)0x0B)  /* SDMMC2 Alternate Function mapping                         */
#endif /* SDMMC2 */
#if defined(UART7)
#define GPIO_AF11_UART7        ((uint8_t)0x0B)  /* UART7 Alternate Function mapping                          */
#endif /* UART7 */
#if defined(UART9)
#define GPIO_AF11_UART9        ((uint8_t)0x0B)  /* UART9 Alternate Function mapping                          */
#endif /* UART9 */
#if defined(UCPD1)
#define GPIO_AF11_UCPD1        ((uint8_t)0x0B)  /* UCPD1 Alternate Function mapping                          */
#endif /* UCPD1 */
#if defined(STM32H503xx)
#define GPIO_AF11_I2C1         ((uint8_t)0x0B)  /* I2C1 Alternate Function mapping                           */
#define GPIO_AF11_I2C2         ((uint8_t)0x0B)  /* I2C2 Alternate Function mapping                           */
#define GPIO_AF11_SPI2         ((uint8_t)0x0B)  /* SPI2 Alternate Function mapping                           */
#define GPIO_AF11_USART2       ((uint8_t)0x0B)  /* USART2 Alternate Function mapping                         */
#endif /* STM32H503xx */

/**
  * @brief   AF 12 selection
  */
#if defined(FMC_BANK1)
#define GPIO_AF12_FMC          ((uint8_t)0x0C)  /* FMC Alternate Function mapping                            */
#endif /* FMC_BANK1 */
#if defined(SDMMC1)
#define GPIO_AF12_SDMMC1       ((uint8_t)0x0C)  /* SDMMC1 Alternate Function mapping                         */
#endif /* SDMMC1 */
#if defined(STM32H503xx)
#define GPIO_AF12_COMP1        ((uint8_t)0x0C)  /* COMP1 Alternate Function mapping                          */
#define GPIO_AF12_SPI1         ((uint8_t)0x0C)  /* SPI1 Alternate Function mapping                           */
#endif /* STM32H503xx */

/**
  * @brief   AF 13 selection
  */
#if defined(DCMI)
#define GPIO_AF13_DCMI         ((uint8_t)0x0D)  /* DCMI Alternate Function mapping                           */
#define GPIO_AF13_PSSI         ((uint8_t)0x0D)  /* PSSI Alternate Function mapping                           */
#endif /* DCMI */
#if defined(FMC_BANK1)
#define GPIO_AF13_FMC          ((uint8_t)0x0D)  /* FMC Alternate Function mapping                            */
#endif /* FMC_BANK1 */
#if defined(LPTIM5)
#define GPIO_AF13_LPTIM5       ((uint8_t)0x0D)  /* LPTIM5 Alternate Function mapping                         */
#endif /* LPTIM5 */
#if defined(STM32H503xx)
#define GPIO_AF13_USART2       ((uint8_t)0x0D)  /* USART2 Alternate Function mapping                         */
#define GPIO_AF13_USART3       ((uint8_t)0x0D)  /* USART3 Alternate Function mapping                         */
#endif /* STM32H503xx */

/**
  * @brief   AF 14 selection
  */
#if defined(STM32H503xx)
#define GPIO_AF14_LPTIM1       ((uint8_t)0x0E)  /* LPTIM1 Alternate Function mapping                         */
#define GPIO_AF14_LPTIM2       ((uint8_t)0x0E)  /* LPTIM2 Alternate Function mapping                         */
#define GPIO_AF14_TIM1         ((uint8_t)0x0E)  /* TIM1 Alternate Function mapping                           */
#define GPIO_AF14_TIM2         ((uint8_t)0x0E)  /* TIM2 Alternate Function mapping                           */
#define GPIO_AF14_TIM3         ((uint8_t)0x0E)  /* TIM3 Alternate Function mapping                           */
#endif /* STM32H503xx */
#if defined(LPTIM3)
#define GPIO_AF14_LPTIM3       ((uint8_t)0x0E)  /* LPTIM3 Alternate Function mapping                         */
#endif /* LPTIM3 */
#if defined(LPTIM4)
#define GPIO_AF14_LPTIM4       ((uint8_t)0x0E)  /* LPTIM4 Alternate Function mapping                         */
#endif /* LPTIM4 */
#if defined(LPTIM5)
#define GPIO_AF14_LPTIM5       ((uint8_t)0x0E)  /* LPTIM5 Alternate Function mapping                         */
#endif /* LPTIM5 */
#if defined(LPTIM6)
#define GPIO_AF14_LPTIM6       ((uint8_t)0x0E)  /* LPTIM6 Alternate Function mapping                         */
#endif /* LPTIM6 */
#if (defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx))
#define GPIO_AF14_TIM2         ((uint8_t)0x0E)  /* TIM2 Alternate Function mapping                           */
#endif /* defined(STM32H573xx) || defined(STM32H563xx) || defined(STM32H562xx) */
#if defined(UART5)
#define GPIO_AF14_UART5        ((uint8_t)0x0E)  /* UART5 Alternate Function mapping                          */
#endif /* UART5 */

/**
  * @brief   AF 15 selection
  */
#define GPIO_AF15_EVENTOUT     ((uint8_t)0x0F)  /* EVENTOUT Alternate Function mapping */
#define GPIO_GET_INDEX(__GPIOx__)           (((uint32_t )(__GPIOx__) & (~GPIOA_BASE)) >> 10)
#define IS_GPIO_AF(AF)   ((AF) <= (uint8_t)0x0F)
#define assert_param(expr) ((void)0U)
/* Exported types ------------------------------------------------------------*/

/** @defgroup GPIO_Exported_Types GPIO Exported Types
  * @{
  */
typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;
/**
  * @brief   GPIO Init structure definition
  */
typedef struct
{
  uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                           This parameter can be a value of @ref GPIO_pins */

  uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode */

  uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull */

  uint32_t Speed;      /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref GPIO_speed */

  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins
                            This parameter can be a value of @ref GPIOEx_Alternate_function_selection */
} GPIO_InitTypeDef;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
  * @{
  */
/** @defgroup GPIO_pins GPIO pins
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_ALL               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK              (0x0000FFFFU) /* PIN mask for assert test */
/**
  * @}
  */

/** @defgroup GPIO_mode GPIO mode
  * @brief GPIO Configuration Mode
  *        Elements values convention: 0xX0yz00YZ
  *           - X  : GPIO mode or EXTI Mode
  *           - y  : External IT or Event trigger detection
  *           - z  : IO configuration on External IT or Event
  *           - Y  : Output type (Push Pull or Open Drain)
  *           - Z  : IO Direction mode (Input, Output, (Alternate or Analog))
  * @{
  */
/*!< Input Floating Mode                                                 */
#define  GPIO_MODE_INPUT                        (0x00000000U)
/*!< Output Push Pull Mode                                               */
#define  GPIO_MODE_OUTPUT_PP                    (0x00000001U)
/*!< Output Open Drain Mode                                             */
#define  GPIO_MODE_OUTPUT_OD                    (0x00000011U)
/*!< Alternate Function Push Pull Mode                                   */
#define  GPIO_MODE_AF_PP                        (0x00000002U)
/*!< Alternate Function Open Drain Mode                                  */
#define  GPIO_MODE_AF_OD                        (0x00000012U)
/*!< Analog Mode                                                         */
#define  GPIO_MODE_ANALOG                       (0x00000003U)
/*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_RISING                    (0x10110000U)
/*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_FALLING                   (0x10210000U)
/*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
#define  GPIO_MODE_IT_RISING_FALLING            (0x10310000U)
/*!< External Event Mode with Rising edge trigger detection             */
#define  GPIO_MODE_EVT_RISING                   (0x10120000U)
/*!< External Event Mode with Falling edge trigger detection            */
#define  GPIO_MODE_EVT_FALLING                  (0x10220000U)
/*!< External Event Mode with Rising/Falling edge trigger detection      */
#define  GPIO_MODE_EVT_RISING_FALLING           (0x10320000U)
/**
  * @}
  */

/** @defgroup GPIO_speed GPIO speed
  * @brief GPIO Output Maximum frequency
  * @{
  */
#define  GPIO_SPEED_FREQ_LOW        (0x00000000U)   /*!< Low speed       */
#define  GPIO_SPEED_FREQ_MEDIUM     (0x00000001U)   /*!< Medium speed    */
#define  GPIO_SPEED_FREQ_HIGH       (0x00000002U)   /*!< High speed      */
#define  GPIO_SPEED_FREQ_VERY_HIGH  (0x00000003U)   /*!< Very-high speed */
/**
  * @}
  */

/** @defgroup GPIO_pull GPIO pull
  * @brief GPIO Pull-Up or Pull-Down Activation
  * @{
  */
#define  GPIO_NOPULL        (0x00000000U)   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP        (0x00000001U)   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN      (0x00000002U)   /*!< Pull-down activation                */
/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @defgroup GPIO_attributes GPIO attributes
  * @brief GPIO pin secure or non-secure attributes
  * @{
  */
#define  GPIO_PIN_SEC       (0x00000001U)   /*!< Secure pin attribute      */
#define  GPIO_PIN_NSEC      (0x00000000U)   /*!< Non-secure pin attribute  */
/**
  * @}
  */

#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Macros GPIO Exported Macros
  * @{
  */

/**
  * @brief  Check whether the specified EXTI line is rising edge asserted or not.
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_RISING_IT(__EXTI_LINE__)         (EXTI->RPR1 & (__EXTI_LINE__))

/**
  * @brief  Clear the EXTI's line rising pending bits.
  * @param  __EXTI_LINE__: specifies the EXTI lines to clear.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_RISING_IT(__EXTI_LINE__)       (EXTI->RPR1 = (__EXTI_LINE__))

/**
  * @brief  Check whether the specified EXTI line is falling edge asserted or not.
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_FALLING_IT(__EXTI_LINE__)        (EXTI->FPR1 & (__EXTI_LINE__))

/**
  * @brief  Clear the EXTI's line falling pending bits.
  * @param  __EXTI_LINE__: specifies the EXTI lines to clear.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_FALLING_IT(__EXTI_LINE__)      (EXTI->FPR1 = (__EXTI_LINE__))

/**
  * @brief  Check whether the specified EXTI line is asserted or not.
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__)         (__HAL_GPIO_EXTI_GET_RISING_IT(__EXTI_LINE__) || \
                                                       __HAL_GPIO_EXTI_GET_FALLING_IT(__EXTI_LINE__))

/**
  * @brief  Clear the EXTI's line pending bits.
  * @param  __EXTI_LINE__: specifies the EXTI lines to clear.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__)         \
  do {                                                  \
    __HAL_GPIO_EXTI_CLEAR_RISING_IT(__EXTI_LINE__);     \
    __HAL_GPIO_EXTI_CLEAR_FALLING_IT(__EXTI_LINE__);    \
  } while(0)


/**
  * @brief  Generate a Software interrupt on selected EXTI line(s).
  * @param  __EXTI_LINE__: specifies the EXTI line to set.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__)  (EXTI->SWIER1 = (__EXTI_LINE__))

/**
  * @brief  Check whether the specified EXTI line flag is set or not.
  * @param  __EXTI_LINE__ specifies the EXTI line flag to check.
  *         This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_FLAG(__EXTI_LINE__)       __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__)

/**
  * @brief  Clear the EXTI line pending flags.
  * @param  __EXTI_LINE__ specifies the EXTI lines flags to clear.
  *         This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_FLAG(__EXTI_LINE__)     __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define IS_GPIO_PIN_ACTION(ACTION)  (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))

#define IS_GPIO_PIN(__PIN__)        ((((uint32_t)(__PIN__) & GPIO_PIN_MASK) != 0x00U) &&\
                                     (((uint32_t)(__PIN__) & ~GPIO_PIN_MASK) == 0x00U))

#define IS_GPIO_COMMON_PIN(__RESETMASK__, __SETMASK__)  \
  (((uint32_t)(__RESETMASK__) & (uint32_t)(__SETMASK__)) == 0x00u)

#define IS_GPIO_MODE(__MODE__)      (((__MODE__) == GPIO_MODE_INPUT)              ||\
                                     ((__MODE__) == GPIO_MODE_OUTPUT_PP)          ||\
                                     ((__MODE__) == GPIO_MODE_OUTPUT_OD)          ||\
                                     ((__MODE__) == GPIO_MODE_AF_PP)              ||\
                                     ((__MODE__) == GPIO_MODE_AF_OD)              ||\
                                     ((__MODE__) == GPIO_MODE_IT_RISING)          ||\
                                     ((__MODE__) == GPIO_MODE_IT_FALLING)         ||\
                                     ((__MODE__) == GPIO_MODE_IT_RISING_FALLING)  ||\
                                     ((__MODE__) == GPIO_MODE_EVT_RISING)         ||\
                                     ((__MODE__) == GPIO_MODE_EVT_FALLING)        ||\
                                     ((__MODE__) == GPIO_MODE_EVT_RISING_FALLING) ||\
                                     ((__MODE__) == GPIO_MODE_ANALOG))

#define IS_GPIO_SPEED(__SPEED__)    (((__SPEED__) == GPIO_SPEED_FREQ_LOW)       ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_MEDIUM)    ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_HIGH)      ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_VERY_HIGH))

#define IS_GPIO_PULL(__PULL__)      (((__PULL__) == GPIO_NOPULL)   ||\
                                     ((__PULL__) == GPIO_PULLUP)   || \
                                     ((__PULL__) == GPIO_PULLDOWN))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

#define IS_GPIO_PIN_ATTRIBUTES(__ATTRIBUTES__)  (((__ATTRIBUTES__) == GPIO_PIN_SEC)  ||\
                                                 ((__ATTRIBUTES__) == GPIO_PIN_NSEC))

#endif /* __ARM_FEATURE_CMSE */

/**
  * @}
  */

/* Include GPIO HAL Extended module */
//#include "stm32h5xx_hal_gpio_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIO_Exported_Functions GPIO Exported Functions
  *  @brief    GPIO Exported Functions
  * @{
  */

/** @addtogroup GPIO_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and Configuration functions
  * @{
  */

/* Initialization and de-initialization functions *****************************/
void              HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, const GPIO_InitTypeDef *pGPIO_Init);
void              HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);

/**
  * @}
  */

/** @addtogroup GPIO_Exported_Functions_Group2 IO operation functions
  *  @brief    IO operation functions
  * @{
  */

/* IO operation functions *****************************************************/
GPIO_PinState     HAL_GPIO_ReadPin(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void              HAL_GPIO_WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet);
void              HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_EnableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_DisableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef	HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);

/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @addtogroup GPIO_Exported_Functions_Group3 IO attributes management functions
  * @{
  */

/* IO attributes management functions *****************************************/
void              HAL_GPIO_ConfigPinAttributes(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t PinAttributes);
HAL_StatusTypeDef HAL_GPIO_GetConfigPinAttributes(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin,
                                                  uint32_t *pPinAttributes);

/**
  * @}
  */

#endif /* __ARM_FEATURE_CMSE */
#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_GPIO_H */
