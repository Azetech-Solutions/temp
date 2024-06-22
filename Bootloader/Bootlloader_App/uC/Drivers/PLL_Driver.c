#include "PLL_Driver.h"

/* For 64 Mhz using internal RC oscillator
* im not configure the PLL2 Clock 
*
*/
void PLL_Init(void)
{
	/* PWR Voltage Scalling */
	PWR->VOSCR |= PWR_VOSCR_VOS_0;
	while(!(PWR->VOSSR & PWR_VOSSR_VOSRDY));
	
	RCC->CR |= RCC_CR_HSION; // Internal clock select 
	while(!(RCC->CR & RCC_CR_HSIRDY)); // wait for Ready Flag
	
	RCC->CR &=~ RCC_CR_PLL1ON; // Clear the PLL 1
	while(RCC->CR & RCC_CR_PLL1RDY);  // verify the PLL1 Unlock
	
	/* set the Defult  AHB Clock, APB1 & APB2 Clock*/
	RCC->CFGR2 = 0x00000000; //&=~(RCC_CFGR2_HPRE_Msk | RCC_CFGR2_PPRE1_Msk | RCC_CFGR2_PPRE2_Msk | RCC_CFGR2_PPRE3_Msk);

	RCC->PLL1CFGR = 0x00000000; //&=~(RCC_PLL1CFGR_PLL1VCOSEL | RCC_PLL1CFGR_PLL1SRC | RCC_PLL1CFGR_PLL1RGE);

	/* set p clock is core clock */
	RCC->PLL1DIVR	= 0x00000000; //&=~(RCC_PLL1DIVR_PLL1P | RCC_PLL1DIVR_PLL1R | RCC_PLL1DIVR_PLL1Q  | RCC_PLL1DIVR_PLL1N);
	
	/* Clear the PLL Multiplication factor*/
	RCC->PLL1CFGR |= RCC_PLL1CFGR_PLL1M_4 ;
		
	/*  set the PLL clock (HSI)*/
	RCC->PLL1CFGR |= (RCC_PLL1CFGR_PLL1SRC_1  //CSI selected
										|RCC_PLL1CFGR_PLL1RGE);
										
	/* P ,Q, R Clock are enabled */
	RCC->PLL1CFGR |= (RCC_PLL1CFGR_PLL1REN | RCC_PLL1CFGR_PLL1QEN | RCC_PLL1CFGR_PLL1PEN);
	

	
	/* P, Q, R, N clock Divide factors  */
	RCC->PLL1DIVR |= (RCC_PLL1DIVR_PLL1N_4 | RCC_PLL1DIVR_PLL1R_0 | 
										RCC_PLL1DIVR_PLL1Q_0 |(RCC_PLL1DIVR_PLL1P_2 | RCC_PLL1DIVR_PLL1P_0));
	
	RCC->CR |= RCC_CR_PLL1ON; // Clear the PLL 1
	while(!(RCC->CR & RCC_CR_PLL1RDY));  // verify the PLL1 Unlock
	
	RCC->CFGR1 |= RCC_CFGR1_SW ;	
	while(!(RCC->CFGR1 & RCC_CFGR1_SWS));
	
	SystemCoreClockUpdate();
}
