#ifndef __UART_DRIVER_H__
#define __UART_DRIVER_H__

#include "stm32h5xx.h"
#include "Buffer.h"
#include "ComIf.h"
#include "Debug.h"

#define UART_INIT
/***************************************************************************************/
extern UBYTE UART_Init_bit;

extern void Uart3_Init(void);

extern uint8_t Uar3t_Tx_Byte(uint8_t Data);

static void Uart3_Txstring(char *data);

extern void USART3_Main(void);

extern void debugMain(void);

/***************************************************************************************/
#endif