#ifndef __UART_DRIVER_H__
#define __UART_DRIVER_H__

#include "stm32h5xx.h"

#include "Includes.h"
#include "Platform_Types.h"
#include "Buffer.h"
#include "ComIf.h"
#include <string.h>

extern void Uart3_Init(void);
extern uint8_t Uar3t_Tx_Byte(uint8_t Data);
extern void Uart3_Tx_str(char *data);
extern void USART3_Main(void);
extern void debugMain(void);
#endif