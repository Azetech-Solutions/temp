
/****HEADER FILE INCLUTION****/
#include "Boot_Transmit_uC_To_Tool.h"

/****GLOBAL VARIABLE INCLUTION****/

static UBYTE UART_BUSY_Flag = FALSE;

/***************************************************************************************/

UBYTE Boot_Transmit_FUN(UWORD Length, void * Data)
{
	UBYTE retval = COMIF_EC_GENERIC_ERROR;
	
	if(UART_Init_bit == TRUE)
	{
		if(UART_BUSY_Flag == FALSE)
		{
			for(UBYTE i=0;i<Length;i++)
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
				UART_BUSY_Flag = TRUE;
			}
			
			if(retval == COMIF_EC_NO_ERROR)
			{
				ComIf_TxConfirmation(C_ComIfChannel_Boot);
				UART_BUSY_Flag = FALSE;
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
	Debug_SendNumberWithDescription("Error_not",Debug0);
}
/***************************************************************************************/
