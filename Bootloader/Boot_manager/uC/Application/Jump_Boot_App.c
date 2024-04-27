
#include "Jump_Boot_App.h"

FPtr JUMP_TO_BOOT = 0;
FPtr JUMP_TO_APP_1 = 0;
FPtr JUMP_TO_APP_2 = 0;

/* Jump Bootloader */
void Jump_BOOTLOADER(void)
{
	uint32_t JUMP_ADD = 0;
	
	JUMP_ADD = (*(__IO uint32_t*)(BOOTLOADER_ADDRESS +4U));
	JUMP_TO_BOOT = (FPtr)JUMP_ADD;
	
	__disable_irq();
	RCC_DeInit();
	S_DeInit();
	
	SCB->VTOR = BOOTLOADER_ADDRESS;
	__enable_irq();
	
	/* Initialize user application's Stack Pointer */
	__set_MSP(*(__IO uint32_t*)BOOTLOADER_ADDRESS);

	/* Jump to Boot File */
	JUMP_TO_BOOT();
}

/* Jump Application */
void Jump_APP_1(void)
{
	Check_App_Header_ST *App1 = &Ck_Hdr[HEADER_APP_1];
	uint32_t JUMP_ADD = 0;
		/* Jump to user application */
	JUMP_ADD = (*(__IO uint32_t*)(App1->Ck_SAddress + 4U));
	JUMP_TO_APP_1 = (FPtr) JUMP_ADD;
	
	__disable_irq();
	RCC_DeInit();
	S_DeInit();
	
	SCB->VTOR = App1->Ck_SAddress;
	__enable_irq();

	/* Initialize user application's Stack Pointer */
	 __set_MSP(*(__IO uint32_t*) App1->Ck_SAddress);

	/* Jump to Application File */
	JUMP_TO_APP_1();
}
void Jump_APP_2(void)
{
	Check_App_Header_ST *App2 = &Ck_Hdr[HEADER_APP_2];
	uint32_t JUMP_ADD = 0;
		/* Jump to user application */
	JUMP_ADD = (*(__IO uint32_t*)(App2->Ck_SAddress + 4U));
	JUMP_TO_APP_2 = (FPtr) JUMP_ADD;
	
	__disable_irq();
	RCC_DeInit();
	S_DeInit();
	
	SCB->VTOR = App2->Ck_SAddress;
	__enable_irq();

	/* Initialize user application's Stack Pointer */
	 __set_MSP(*(__IO uint32_t*) App2->Ck_SAddress);

	/* Jump to Application File */
	JUMP_TO_APP_2();
}
void RCC_DeInit(void)
{
  /* Increasing the CPU frequency */
  if (FLASH_LATENCY_DEFAULT  > __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_DEFAULT);
  }

  /* Set HSION bit */
  SET_BIT(RCC->CR, RCC_CR_HSION);

  /* Wait till HSI is ready */
  while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == 0U);

  /* Set HSIDIV Default value */
  CLEAR_BIT(RCC->CR, RCC_CR_HSIDIV);

  /* Set HSITRIM default value */
  WRITE_REG(RCC->HSICFGR, RCC_HSICFGR_HSITRIM_6);

  /* Reset CFGR register (HSI is selected as system clock source) */
  CLEAR_REG(RCC->CFGR1);
  CLEAR_REG(RCC->CFGR2);

  /* Wait till clock switch is ready */
  while (READ_BIT(RCC->CFGR1, RCC_CFGR1_SWS) != 0U);

  /* Reset HSECSSON, HSEON, HSIKERON, CSION, CSIKERON and HSI48ON bits */
  CLEAR_BIT(RCC->CR, RCC_CR_CSION | RCC_CR_CSIKERON | RCC_CR_HSECSSON | RCC_CR_HSIKERON | RCC_CR_HSI48ON | \
            RCC_CR_HSEON);

  /* Reset HSEEXT bit*/
  CLEAR_BIT(RCC->CR, RCC_CR_HSEEXT);

  /* Clear PLL1ON bit */
  CLEAR_BIT(RCC->CR, RCC_CR_PLL1ON);

  /* Wait till PLL1 is disabled */
  while (READ_BIT(RCC->CR, RCC_CR_PLL1RDY) != 0U);

  /* Reset PLL2N bit */
  CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON);

  /* Wait till PLL2 is disabled */
  while (READ_BIT(RCC->CR, RCC_CR_PLL2RDY) != 0U);

  /* Reset PLL1CFGR register */
  CLEAR_REG(RCC->PLL1CFGR);

  /* Reset PLL1DIVR register */
  WRITE_REG(RCC->PLL1DIVR, 0x01010280U);

  /* Reset PLL1FRACR register */
  CLEAR_REG(RCC->PLL1FRACR);

  /* Reset PLL2CFGR register */
  CLEAR_REG(RCC->PLL2CFGR);

  /* Reset PLL2DIVR register */
  WRITE_REG(RCC->PLL2DIVR, 0x01010280U);

  /* Reset PLL2FRACR register */
  CLEAR_REG(RCC->PLL2FRACR);
	
  /* Reset HSEBYP bit */
  CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

  /* Disable all interrupts */
  CLEAR_REG(RCC->CIER);

  /* Clear all interrupts flags */
  WRITE_REG(RCC->CICR, 0xFFFFFFFFU);

  /* Reset all RSR flags */
  SET_BIT(RCC->RSR, RCC_RSR_RMVF);

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HSI_VALUE;

  /* Decreasing the number of wait states because of lower CPU frequency */
  if (FLASH_LATENCY_DEFAULT  < __HAL_FLASH_GET_LATENCY())
  {
    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
    __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_DEFAULT);
  }
}

void disable_interrupt(void)
{
	uint8_t i;
	//Disable all enabled interrupts in NVIC.
	for(i=0;i<16;i++)
	{
		NVIC->ICER[i] = 0xFFFFFFFF;
	}
	//Clear all pending interrupt requests in NVIC.
	for(i=0;i<16;i++)
	{
		NVIC->ICPR[i] = 0xFFFFFFFF;
	}
}
void S_DeInit(void)
{
	disable_interrupt();
	
	/* Disable SysTick and clear its exception pending bit */
	SysTick->CTRL = 0 ;
	SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk ;  //removes the pending state from the SysTick exception.
	
	GPIOA_CLK_DISABLE();
	GPIOB_CLK_DISABLE();
	GPIOC_CLK_DISABLE();
	GPIOD_CLK_DISABLE();
	GPIOH_CLK_DISABLE();
	
	APB1_FORCE_RESET();
	APB2_FORCE_RESET();
	APB3_FORCE_RESET();
	
	APB1_RELEASE_RESET();
	APB2_RELEASE_RESET();
	APB3_RELEASE_RESET();
}