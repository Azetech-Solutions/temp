#ifndef __Boot_Transmit_uC_To_Tool__
#define __Boot_Transmit_uC_To_Tool__


#include <stdio.h>
#include "Includes.h"
#include COMIF_CONFIG_H
#include COMIF_H
#include DEBUG_H
#include "Uart_Driver.h"

extern UBYTE Boot_Transmit_FUN(UWORD Length, void * Data);
extern void Boot_Error_Notification(ULONG Debug0, ULONG Debug1);

#endif