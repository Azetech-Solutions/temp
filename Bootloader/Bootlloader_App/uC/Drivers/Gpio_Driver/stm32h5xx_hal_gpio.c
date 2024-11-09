
/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal_gpio.h"


  /*
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
	*
  * @brief  Initialize the GPIOx peripheral according to the specified parameters in the pGPIO_Init.
  * @note   If GPIOx peripheral pin is used in EXTI_MODE and the pin is secure in case
  *         the system implements the security (TZEN=1), it is up to the secure application to
  *         insure that the corresponding EXTI line is set secure.
  * @param  GPIOx: where x can be (A..I) for stm32h56xxx and stm32h57xxx family lines and
  *         (A..D or H) for stm32h503xx family line to select the GPIO peripheral for STM32H5 family
  * @param  pGPIO_Init: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, const GPIO_InitTypeDef *pGPIO_Init)
{
  uint32_t tmp;
  uint32_t iocurrent;
  uint32_t position = 0U;


  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(pGPIO_Init->Pin));
  assert_param(IS_GPIO_MODE(pGPIO_Init->Mode));
  assert_param(IS_GPIO_PULL(pGPIO_Init->Pull));

  /* Configure the port pins */
  while (((pGPIO_Init->Pin) >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = (pGPIO_Init->Pin) & (1UL << position);

    if (iocurrent != 0U)
    {
      /*--------------------- GPIO Mode Configuration ------------------------*/
      /* In case of Alternate function mode selection */
      if ((pGPIO_Init->Mode == GPIO_MODE_AF_PP) || (pGPIO_Init->Mode == GPIO_MODE_AF_OD))
      {
        /* Check the Alternate function parameters */
        assert_param(IS_GPIO_AF_INSTANCE(GPIOx));
        assert_param(IS_GPIO_AF(pGPIO_Init->Alternate));

        /* Configure Alternate function mapped with the current IO */
        tmp = GPIOx->AFR[position >> 3U];
        tmp &= ~(0x0FUL << ((position & 0x07U) * 4U));
        tmp |= ((pGPIO_Init->Alternate & 0x0FUL) << ((position & 0x07U) * 4U));
        GPIOx->AFR[position >> 3U] = tmp;
      }

      /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
      tmp = GPIOx->MODER;
      tmp &= ~(GPIO_MODER_MODE0 << (position * 2U));
      tmp |= ((pGPIO_Init->Mode & GPIO_MODE) << (position * 2U));
      GPIOx->MODER = tmp;

      /* In case of Output or Alternate function mode selection */
      if ((pGPIO_Init->Mode == GPIO_MODE_OUTPUT_PP) || (pGPIO_Init->Mode == GPIO_MODE_AF_PP) ||
          (pGPIO_Init->Mode == GPIO_MODE_OUTPUT_OD) || (pGPIO_Init->Mode == GPIO_MODE_AF_OD))
      {
        /* Check the Speed parameter */
        assert_param(IS_GPIO_SPEED(pGPIO_Init->Speed));

        /* Configure the IO Speed */
        tmp = GPIOx->OSPEEDR;
        tmp &= ~(GPIO_OSPEEDR_OSPEED0 << (position * 2U));
        tmp |= (pGPIO_Init->Speed << (position * 2U));
        GPIOx->OSPEEDR = tmp;

        /* Configure the IO Output Type */
        tmp = GPIOx->OTYPER;
        tmp &= ~(GPIO_OTYPER_OT0 << position) ;
        tmp |= (((pGPIO_Init->Mode & GPIO_OUTPUT_TYPE) >> 4U) << position);
        GPIOx->OTYPER = tmp;
      }

      if (pGPIO_Init->Mode != GPIO_MODE_ANALOG)
      {
        /* Check the Pull parameters */
        assert_param(IS_GPIO_PULL(pGPIO_Init->Pull));

        /* Activate the Pull-up or Pull down resistor for the current IO */
        tmp = GPIOx->PUPDR;
        tmp &= ~(GPIO_PUPDR_PUPD0 << (position * 2U));
        tmp |= ((pGPIO_Init->Pull) << (position * 2U));
        GPIOx->PUPDR = tmp;
      }

      /*--------------------- EXTI Mode Configuration ------------------------*/
      /* Configure the External Interrupt or event for the current IO */
      if ((pGPIO_Init->Mode & EXTI_MODE) == EXTI_MODE)
      {
        tmp = EXTI->EXTICR[position >> 2U];
        tmp &= ~((0x0FUL) << (8U * (position & 0x03U)));
        tmp |= (GPIO_GET_INDEX(GPIOx) << (8U * (position & 0x03U)));
        EXTI->EXTICR[position >> 2U] = tmp;

        /* Clear Rising Falling edge configuration */
        tmp = EXTI->RTSR1;
        tmp &= ~((uint32_t)iocurrent);
        if ((pGPIO_Init->Mode & RISING_EDGE) == RISING_EDGE)
        {
          tmp |= iocurrent;
        }
        EXTI->RTSR1 = tmp;

        tmp = EXTI->FTSR1;
        tmp &= ~((uint32_t)iocurrent);
        if ((pGPIO_Init->Mode & FALLING_EDGE) == FALLING_EDGE)
        {
          tmp |= iocurrent;
        }
        EXTI->FTSR1 = tmp;

        /* Clear EXTI line configuration */
        tmp = EXTI->EMR1;
        tmp &= ~((uint32_t)iocurrent);
        if ((pGPIO_Init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
        {
          tmp |= iocurrent;
        }
        EXTI->EMR1 = tmp;

        tmp = EXTI->IMR1;
        tmp &= ~((uint32_t)iocurrent);
        if ((pGPIO_Init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
        {
          tmp |= iocurrent;
        }
        EXTI->IMR1 = tmp;
      }
    }

    position++;
  }
}

/**
  * @brief  De-initialize the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx: where x can be (A..I) for stm32h56xxx and stm32h57xxx family lines and
  *         (A..D or H) for stm32h503xx family line to select the GPIO peripheral for STM32H5 family
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
  * @retval None
  */
void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
  uint32_t tmp;
  uint32_t iocurrent;
  uint32_t position = 0U;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* Configure the port pins */
  while ((GPIO_Pin >> position) != 0U)
  {
    /* Get current io position */
    iocurrent = (GPIO_Pin) & (1UL << position);

    if (iocurrent != 0U)
    {
      /*------------------------- EXTI Mode Configuration --------------------*/
      /* Clear the External Interrupt or Event for the current IO */
      tmp = EXTI->EXTICR[position >> 2U];
      tmp &= ((0x0FUL) << (8U * (position & 0x03U)));
      if (tmp == (GPIO_GET_INDEX(GPIOx) << (8U * (position & 0x03U))))
      {
        /* Clear EXTI line configuration */
        EXTI->IMR1 &= ~(iocurrent);
        EXTI->EMR1 &= ~(iocurrent);

        /* Clear Rising Falling edge configuration */
        EXTI->RTSR1 &= ~(iocurrent);
        EXTI->FTSR1 &= ~(iocurrent);

        tmp = (0x0FUL) << (8U * (position & 0x03U));
        EXTI->EXTICR[position >> 2U] &= ~tmp;
      }

      /*------------------------- GPIO Mode Configuration --------------------*/
      /* Configure IO in Analog Mode */
      GPIOx->MODER |= (GPIO_MODER_MODE0 << (position * 2U));

      /* Configure the default Alternate Function in current IO */
      GPIOx->AFR[position >> 3U] &= ~(0x0FUL << ((position & 0x07U) * 4U));

      /* Configure the default value for IO Speed */
      GPIOx->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED0 << (position * 2U));

      /* Configure the default value IO Output Type */
      GPIOx->OTYPER  &= ~(GPIO_OTYPER_OT0 << position);

      /* Deactivate the Pull-up and Pull-down resistor for the current IO */
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPD0 << (position * 2U));
    }

    position++;
  }
}

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions
  *  @brief GPIO Read, Write, Toggle, Lock and EXTI management functions.
  *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Read the specified input port pin.
  * @param  GPIOx: where x can be (A..I) for stm32h56xxx and stm32h57xxx family lines and
  *         (A..D or H) for stm32h503xx family line to select the GPIO peripheral for STM32H5 family
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be GPIO_PIN_x where x can be (0..15).
  * @retval The input port pin value.
  */
GPIO_PinState HAL_GPIO_ReadPin(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != 0U)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Set or clear the selected data port bit.
  *
  * @note   This function uses GPIOx_BSRR and GPIOx_BRR registers to allow atomic read/modify
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  *
  * @param  GPIOx: where x can be (A..I) for stm32h56xxx and stm32h57xxx family lines and
  *         (A..D or H) for stm32h503xx family line to select the GPIO peripheral for STM32H5 family
  * @param  GPIO_Pin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_PIN_x where x can be (0..15).
  * @param  PinState: specifies the value to be written to the selected bit.
  *         This parameter can be one of the GPIO_PinState enum values:
  *            @arg GPIO_PIN_RESET: to clear the port pin
  *            @arg GPIO_PIN_SET: to set the port pin
  * @retval None
  */
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if (PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin;
  }
  else
  {
    GPIOx->BRR = (uint32_t)GPIO_Pin;
  }
}

/**
  * @brief  Set and clear several pins of a dedicated port in same cycle.
  * @note   This function uses GPIOx_BSRR and GPIOx_BRR registers to allow atomic read/modify
  *         accesses.
  * @param  GPIOx: where x can be (A..I) for stm32h56xxx and stm32h57xxx family lines and
  *         (A..D or H) for stm32h503xx family line to select the GPIO peripheral for STM32H5 family
  * @param  PinReset specifies the port bits to be reset
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15) or zero.
  * @param  PinSet specifies the port bits to be set
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15) or zero.
  * @note   Both PinReset and PinSet combinations shall not get any common bit, else
  *         assert would be triggered.
  * @note   At least one of the two parameters used to set or reset shall be different from zero.
  * @retval None
  */
void HAL_GPIO_WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet)
{
  uint32_t tmp;

  /* Check the parameters */
  /* Make sure at least one parameter is different from zero and that there is no common pin */
  assert_param(IS_GPIO_PIN((uint32_t)PinReset | (uint32_t)PinSet));
  assert_param(IS_GPIO_COMMON_PIN(PinReset, PinSet));

  tmp = (((uint32_t)PinReset << 16) | PinSet);
  GPIOx->BSRR = tmp;
}

/**
  * @brief  Toggle the specified GPIO pin.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral for STM32H5 family
  * @param  GPIO_Pin: specifies the pin to be toggled.
  * @retval None
  */
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint32_t odr;

  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* get current Output Data Register value */
  odr = GPIOx->ODR;

  /* Set selected pins that were at low level, and reset ones that were high */
  GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
}

/**
  * @brief  Lock GPIO Pins configuration registers.
  * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next reset.
  * @param  GPIOx: where x can be (A..I) for stm32h56xxx and stm32h57xxx family lines and
  *         (A..D or H) for stm32h503xx family line to select the GPIO peripheral for STM32H5 family
  * @param  GPIO_Pin: specifies the port bits to be locked.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = GPIO_LCKR_LCKK;

  /* Check the parameters */
  assert_param(IS_GPIO_LOCK_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  /* Apply lock key write sequence */
  tmp |= GPIO_Pin;
  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
  GPIOx->LCKR = tmp;
  /* Reset LCKx bit(s): LCKK='0' + LCK[15-0] */
  GPIOx->LCKR = GPIO_Pin;
  /* Set LCKx bit(s): LCKK='1' + LCK[15-0] */
  GPIOx->LCKR = tmp;
  /* Read LCKK bit*/
  tmp = GPIOx->LCKR;

  /* read again in order to confirm lock is active */
  if ((GPIOx->LCKR & GPIO_LCKR_LCKK) != GPIO_LCKR_LCKK)
  {
    return HAL_ERROR;
  }
  return HAL_OK;
}
