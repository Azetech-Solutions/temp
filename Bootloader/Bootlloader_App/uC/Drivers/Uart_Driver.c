
#include "Uart_Driver.h"

UBYTE UART_Init_bit = FALSE;
/***************************************************************************************/
//#ifdef UART_INIT
void Uart3_Init(void)
{
	USART3->CR1 = USART_CR1_FIFOEN;
	USART3->CR3 = (USART_CR3_TXFTCFG_1 | //TXFIFO reaches 1/2 of its depth
										USART_CR3_RXFTCFG_1); //RXFTCFG reaches 1/2 of its depth
	
	 /*M1: Word length & M0: Word length*/
	USART3->CR1 &= (~USART_CR1_M0)|(~USART_CR1_M1);
	 /*Oversampling 8*/
	USART3->CR1 |= USART_CR1_OVER8;
	
/**********************************************************/
/*		Baud Rate Config For Baurate 115200										
			In case of oversampling by 8: 											
			USARTDIV = 2 * 64000000 / 115200
			USARTDIV = 1111.1 (0d1111.1  = 0x457)
			BRR[3:0] = USARTDIV[3:0] >> 1 = 0x7 >> 1 = 0x3
			BRR = 0x453																					*/
/**********************************************************/
	USART3->BRR = 0x453;
	
		/* Rx & Tx Enable*/
	USART3->CR1 |= (USART_CR1_TE | USART_CR1_RE ) ; 
	
	USART3->CR1 |= USART_CR1_RXNEIE_RXFNEIE;
	/* Stop Bits */
	USART3->CR2 &= ~USART_CR2_STOP;
		/*Enable the USART*/
	USART3->CR1 |= USART_CR1_UE;
	/*USART1 Interrupt Enable*/
	NVIC_EnableIRQ(USART3_IRQn);
	
	UART_Init_bit =TRUE;
}
//#endif
/***************************************************************************************/

uint8_t Uar3t_Tx_Byte(uint8_t Data)
{
	uint8_t retval = 0;
	
	if(USART3->ISR & USART_ISR_TXE_TXFNF)
	{
		USART3->TDR = Data;
		
		while(!(USART3->ISR & USART_ISR_TC));
		/*Transmission complete clear flag*/
		USART3->ICR |= USART_ICR_TCCF;
		retval = 1;
	}
	
	return retval;
}
/***************************************************************************************/

static void Uart3_Txstring(char *data)
{
	while(*data)
	{
		Uar3t_Tx_Byte(*data++);
	}
}
/***************************************************************************************/

void USART3_IRQHandler(void)
{
	__disable_irq();
	
	if(USART3->ISR & USART_ISR_RXNE_RXFNE)
	{
		uint8_t data = USART3->RDR;
		UART3_Buffer_EnQueue(data);	
	}
	__enable_irq();
}
/***************************************************************************************/

void USART3_Main(void)
{
	while(!UART3_IsBufferEmpty())
	{
		uint8_t Data=0;
		if(UART3_Buffer_DeQueue(&Data))
		{
			ComIf_RxIndication_Boot(Data);
		}
	}
}
/***************************************************************************************/

void debugMain(void)
{
	while(!Debug_IsBufferEmpty())
	{
		UBYTE data =0 ;		
		if(Debug_Buffer_DeQueue(&data))
		{
			Uar3t_Tx_Byte(data);
		}
	}
}
/***************************************************************************************/
