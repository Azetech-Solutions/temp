/**********************************************************/
/*          ALL PHERIPHEALS I/O INIT                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/

#include "Ports_init.h"

void delay()
{
	unsigned int i;
	for(i=0;i<800000;i++);
}

void Init(void)
{
	FLASH_init();
	Chk_NVMLast_BlockAdd();
	Buffer_Init();
	bkSRAM_Init();	
	GpioclockEnable();
	Uart3_Init();
	//NVS_Init();
	NVM_Init();
	Read_Apps_Header();
}
static void GpioclockEnable(void)
{
	/* GPIO Ports Clock Enable */
	PORTA_CLOCK_ENABLE();
//	PORTB_CLOCK_ENABLE();
//	PORTC_CLOCK_ENABLE();
//	PORTD_CLOCK_ENABLE();
//	PORTH_CLOCK_ENABLE();
	Uart3_IO_init();
}
/***************************************************************************************/

static void Uart3_IO_init(void)
{
	GPIO_InitTypeDef PA3_PA4 ={0};
	
	/* Pheriperal Clock Enable */
	USART3_CLOCK_ENABLE();
	
  /*Configure GPIO pins : PA3 PA4 
	 *	A3--> Rx
	 *	A4--> Tx
	*/
	PA3_PA4.Pin = GPIO_PIN_3| GPIO_PIN_4;
	PA3_PA4.Pull = GPIO_NOPULL;
	PA3_PA4.Alternate = GPIO_AF13_USART3;
	PA3_PA4.Mode = GPIO_MODE_AF_PP;
	PA3_PA4.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA,&PA3_PA4);
}
/***************************************************************************************/
