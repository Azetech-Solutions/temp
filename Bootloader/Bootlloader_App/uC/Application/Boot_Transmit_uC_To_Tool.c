
/****HEADER FILE INCLUTION****/
#include "Boot_Transmit_uC_To_Tool.h"

/****GLOBAL VARIABLE INCLUTION****/

static UartFlag_ST Uart;

/***************************************************************************************/

UBYTE Boot_Transmit_FUN(UWORD Length, void * Data)
{
	UBYTE retval = COMIF_EC_GENERIC_ERROR;
	
	if(UART_Init_bit == TRUE)
	{
		if(Uart.UART_BUSY_Flag == FALSE)
		{
			for(UWORD i=0;i<Length;i++)
			{
				if(Uar3t_Tx_Byte(*((UB*)(Data++))))
				{
					retval = COMIF_EC_NO_ERROR;
				}
				else
				{
					retval = COMIF_EC_TRANSMISSION_ABORTED;
					break;
				}
				Uart.UART_BUSY_Flag = TRUE;
			}
			
			if(retval == COMIF_EC_NO_ERROR)
			{
				ComIf_TxConfirmation(C_ComIfChannel_Boot);
				Uart.UART_BUSY_Flag = FALSE;
			}		
		}
		else
		{
			retval = COMIF_EC_CHANNEL_BUSY;
		}
	}
	
	return retval;
}

/***************************************************************************************/

void Boot_Error_Notification(ULONG Debug0, ULONG Debug1)
{
	Debug_SendNumberWithDescription("Debug 0",Debug0);
	Debug_SendNumberWithDescription("Debug 1",Debug1);
}
/***************************************************************************************/
