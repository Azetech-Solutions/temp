
#include "Uart_Driver.h"
#include "Debug.h"
#define MAX_SIZE 						25


UBYTE UART_Init_bit = FALSE;
UBYTE data_buf[MAX_SIZE]={0}; // = {"7;;301?50;7="};
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

void uart3_Tx_str(char *data)
{
	while(*data)
	{
		Uar3t_Tx_Byte(*data++);
	}
}

void USART3_IRQHandler(void)
{
	__disable_irq();
	
	if(USART3->ISR & USART_ISR_RXNE_RXFNE)
	{
		uint8_t data = USART3->RDR;
		UART3_Buffer_EnQueue(data);
		//Uar3t_Tx_Byte(data);
	}
	
	__enable_irq();
}
void USART3_Main(void)
{
	BufferType_ST *Buff = UART3_Buffer_Get(); 
	
	memcpy(data_buf,Buff->BufferPtr,Buff->Length);
	
	ComIf_RxIndication_Boot((char*)data_buf,strlen((char*)data_buf));
	
	memset(data_buf,0,MAX_SIZE);
	if(Buff->BufferPtr != 0)
	{
		UART3_Buffer_Clear();
	}
}
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
