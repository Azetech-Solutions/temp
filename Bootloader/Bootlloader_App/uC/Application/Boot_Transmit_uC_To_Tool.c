
/****HEADER FILE INCLUTION****/
#include "Boot_Transmit_uC_To_Tool.h"

/****GLOBAL VARIABLE INCLUTION****/
extern UBYTE UART_Init_bit;
UBYTE UART_BUSY_Flag = FALSE;
void send(ULONG data);

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

void Boot_Error_Notification(ULONG Debug0, ULONG Debug1)
{
	Debug_SendNumberWithDescription("Error_not",Debug0);
}
void send(ULONG data)
{
    uint32_t rev=0,rev1=0;
    while(data)
    {
        rev = (rev*10)+(data%10);
        data/=10;
    }
    while(rev)
    {
        rev1 = rev%10;
        Uar3t_Tx_Byte((uint8_t)(rev1+48));
        rev/=10;
    }
}

