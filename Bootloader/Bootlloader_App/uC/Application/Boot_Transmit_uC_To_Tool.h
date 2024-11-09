#ifndef __Boot_Transmit_uC_To_Tool__
#define __Boot_Transmit_uC_To_Tool__

#include "Debug.h"
#include "Uart_Driver.h"

typedef struct _UartFlag
{
	UBYTE UART_BUSY_Flag : 1;
}UartFlag_ST;

extern UBYTE Boot_Transmit_FUN(UWORD Length, void * Data);
extern void Boot_Error_Notification(ULONG Debug0, ULONG Debug1);

#endif