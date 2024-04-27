
/****HEADER FILE INCLUTION****/
#include "Bootloader_Main.h"
#include "Debug.h"
#include "NVS_Driver.h"
#include "NVM_Driver.h"
#include "NVM.h"
/****MACROS Declaration****/


/****FUNCTION POINTER Declaration****/
typedef void (*FPtr)(void); //Function Pointer Declare

/****GLOBAL VARIABLE Declaration****/

Boot_RxByte_ST Boot_Rx_Data; //Rx callback function Variable

Boot_TxByte_ST Boot_Tx_Data; //TX function Variable

volatile uint32_t cnt=0; //to Receive the Last Adderss of the Flash


FPtr Jump_To_Application; // Using Function pointer
uint32_t JumpAddress;

static volatile ULONG Verify_AppCkSum =0;
/****ENUM VARIABLE Declaration****/
Boot_state_EN Boot_State_Control = Boot_Idle;

/****FLAGS Declaration****/
UBYTE Boot_Command_Variable = FALSE;
UBYTE Flash_Write_Flag = FALSE;
UBYTE ISNVS_Flag = FALSE;
UBYTE Flash_Erase_Flag = FALSE;

/*COMIF data Reception Function*/
void Boot_Req_Data_RxCbk(UBYTE Length, UBYTE *Data)
{
	for(UBYTE i=0; i<Length;i++)
	{
		Boot_Rx_Data.Bytes[i] = *(Data++);
	}
	Boot_Command_Variable = TRUE;
	Debug_SendString("OK\n");
}


void Boot_Main()
{
	Boot_RxByte_ST *Rx = &Boot_Rx_Data;
	Boot_TxByte_ST *Tx = &Boot_Tx_Data;
	
	switch(Boot_State_Control)
	{
		case Boot_Idle :
		{cnt++;
			Debug_SendString("Idle\n");
			if(Boot_Command_Variable == TRUE)
			{
				if(Rx->Boot_command == 0xF5)
				{
					
					Tx->Boot_Status = BOOT_STATUS_OK;
					Boot_State_Control = Boot_Start;
					Boot_Res_Status();
				}
				else
				{
					Tx->Byte = BOOT_STATUS_NOT_OK; 
					Boot_Res_Status();
					//NVIC_SystemReset();		
				}	
				Boot_Command_Variable = FALSE;
			}
//			if(cnt==10)
//			{
//				bkSRAM_WriteVariable(0x40036400,0xAAAAAAAA);
//				NVIC_SystemReset();
//			}
		}
		break;
		case Boot_Start :
		{
			Debug_SendString("Start\n");
			
			if(Boot_Command_Variable == TRUE)
			{			
				if(Rx->Boot_command == 0xFE)
				{
						Flash_Erase_Flag = TRUE;
						Boot_State_Control = Boot_Erase_Flash;
				}
				else if(Rx->Boot_command == 0xFA)
				{
					// flg for the flash write in NVs block or App1 or App2
					if(*(uint32_t*)(NVS_START_ADDRESS) != 0xFFFFFFFF || *(uint32_t*)(NVS_START_ADDRESS) == 0xFFFFFFFF )
					{
						Flash_SingleSec_Erase(1,0); // For Erasing NVS Block
						
						Tx->Boot_Status = BOOT_STATUS_OK;
						ISNVS_Flag = TRUE;
					}

					Boot_State_Control = Boot_Wating_for_next_command;
					Boot_Res_Status();
				}
				else if(Rx->Boot_command == 0xFB)
				{
					Tx->Boot_Status = BOOT_STATUS_OK;
					Boot_State_Control = Boot_Wating_for_next_command;
					Boot_Res_Status();
				}
				else
				{
					Tx->Byte = BOOT_STATUS_NOT_OK; // this is an a NotACK for Coressponding boot start Command data is received or Not		
					Boot_Res_Status();
				}
				Boot_Command_Variable = FALSE;
			}
		}
		break;
		case Boot_Wating_for_next_command :
		{
			Debug_SendString("Wait\n");
			if(Boot_Command_Variable == TRUE)
			{
				if( (Rx->Boot_command == 0xFD) && (Boot_Command_Variable == TRUE) )
				{
					Boot_State_Control = Boot_Flash_Write;
					Flash_Write_Flag = TRUE;
				}
				else if(Rx->Boot_command == 0xFC)
				{
					uint32_t Flash_Add=0,chs_Hdr=0;
					
					if(ISNVS_Flag == FALSE)
					{
							Flash_Add = ((ULONG)Rx->Flash_Add_1_byte << 24)|
															((ULONG)Rx->Flash_Add_2_byte << 16)|
															((ULONG)Rx->Flash_Add_3_byte << 8) |
															((ULONG)Rx->Flash_Add_4_byte);
						
							if(Flash_Add >= 0x08006000 && Flash_Add < 0x08010000)
							{
								chs_Hdr = HEADER_APP_1;
								Read_Apps_Header();  // after fully write the app image that header value and cksum value are read it.
							}
							else if(Flash_Add >= 0x08016000 && Flash_Add < 0x08020000)
							{
								chs_Hdr = HEADER_APP_2;
								Read_Apps_Header();
							}					
							Check_App_Header_ST *Ck = &Ck_Hdr[chs_Hdr];
							
							Verify_AppCkSum = ((~Verify_AppCkSum)+1); // to find the total data of checksum
							
							if(Verify_AppCkSum == Ck->Ck_cksum)
							{
								Debug_SendNumberWithDescription("FCkSum",Verify_AppCkSum);
								if(Update_Nvm_Block(Flash_Add))
								{
									Debug_SendString("T_com\n");
									Tx->Byte = BOOT_STATUS_OK;
									Boot_Res_Status();
									Boot_State_Control = Boot_Idle;
								}
							}
						}
					else
					{
						ISNVS_Flag = FALSE;
						Tx->Byte = BOOT_STATUS_OK;
						Boot_Res_Status();
						Boot_State_Control = Boot_Idle;
					}
					
				}
				else
				{
					Tx->Byte = BOOT_STATUS_NOT_OK; 
					Boot_Res_Status();
				}
				Boot_Command_Variable = FALSE;
			}
		}
		break;
		case Boot_Flash_Write :
		{
			Debug_SendString("Flash\n");
			ULONG Flash_Add=0,End_Flash_Add=0;
			ULONG Flash_data[4]={0};
			
			if(Flash_Write_Flag == TRUE)
			{
				/* Adding the Flash Address */
				Flash_Add = ((ULONG)Rx->Flash_Add_1_byte << 24)|
													((ULONG)Rx->Flash_Add_2_byte << 16)|
													((ULONG)Rx->Flash_Add_3_byte << 8) |
													((ULONG)Rx->Flash_Add_4_byte);
				
				if(ISNVS_Flag == TRUE)
				{
							/* FLash data's are arranging */
					Flash_data[0] = (ULONG)(Rx->Data_1 << 24) | (ULONG)(Rx->Data_2 << 16) |
													(ULONG)(Rx->Data_3 << 8) | (ULONG)Rx->Data_4;
					Flash_data[1] = (ULONG)(Rx->Data_5 << 24) | (ULONG)(Rx->Data_6 << 16) | 
													(ULONG)(Rx->Data_7 << 8) | (ULONG)Rx->Data_8;
					Flash_data[2] = (ULONG)(Rx->Data_9 << 24) | (ULONG)(Rx->Data_10 << 16) | 
													(ULONG)(Rx->Data_11 << 8) | (ULONG)Rx->Data_12;
					Flash_data[3] = (ULONG)(Rx->Data_13 << 24) | (ULONG)(Rx->Data_14 << 16) | 
													(ULONG)(Rx->Data_15 << 8) | (ULONG)Rx->Data_16;
				}
				else
				{
						/* FLash data's are arranging */
					Flash_data[0] = (ULONG)(Rx->Data_4 << 24) | (ULONG)(Rx->Data_3 << 16) |
													(ULONG)(Rx->Data_2 << 8) | (ULONG)Rx->Data_1;
					Flash_data[1] = (ULONG)(Rx->Data_8 << 24) | (ULONG)(Rx->Data_7 << 16) | 
													(ULONG)(Rx->Data_6 << 8) | (ULONG)Rx->Data_5;
					Flash_data[2] = (ULONG)(Rx->Data_12 << 24) | (ULONG)(Rx->Data_11 << 16) | 
													(ULONG)(Rx->Data_10 << 8) | (ULONG)Rx->Data_9;
					Flash_data[3] = (ULONG)(Rx->Data_16 << 24) | (ULONG)(Rx->Data_15 << 16) | 
													(ULONG)(Rx->Data_14 << 8) | (ULONG)Rx->Data_13;
				}
				
				if((ISNVS_Flag == FALSE && (Flash_Add >=0x08006080)) || (ISNVS_Flag == FALSE && (Flash_Add >= 0x08014080 )))
				{
					Verify_AppCkSum += calculateChecksum(Flash_data,sizeof(Flash_data)/sizeof(Flash_data[0]));
					Debug_SendNumberWithDescription("CkSum",Verify_AppCkSum);
				}
					
				
				if((Rx->Boot_command == 0xFD) && (Flash_Add != 0U))
				{			
					End_Flash_Add = Multi_Word_write(Flash_Add,Flash_data);	//Do write operation in flash memory
				}	
				
				if(End_Flash_Add != Flash_Add)
				{
					Tx->Byte = BOOT_STATUS_OK;
					Boot_Res_Status();
					Flash_Write_Flag = FALSE;
					Boot_State_Control = Boot_Wating_for_next_command;
				}
				else
				{
					Tx->Byte = BOOT_STATUS_NOT_OK;
					Boot_Res_Status();
				}	
			}
			Boot_Command_Variable = FALSE;
		}
		break;
		case Boot_Erase_Flash :
		{
			Debug_SendString("Erase\n");
			ULONG Flash_Erase_Add =0;
			uint8_t Bank=0;
			
				if(Flash_Erase_Flag == TRUE)
				{
					Flash_Erase_Add = ((ULONG)Rx->Flash_Add_1_byte << 24)|
											((ULONG)Rx->Flash_Add_2_byte << 16)|
											((ULONG)Rx->Flash_Add_3_byte << 8) |
											((ULONG)Rx->Flash_Add_4_byte);
					
					if(Flash_Erase_Add == APP1_START_ADDRESS)
					{
						Bank = Bank1;
					}
					else if(Flash_Erase_Add == APP2_START_ADDRESS)
					{
						Bank = Bank2;
					}
					
					if((Flash_Erase_Add == APP1_START_ADDRESS && Flash_Erase_Add != 0U) || (Flash_Erase_Add == APP2_START_ADDRESS && Flash_Erase_Add != 0U))
					{
						if(FLASH_Erase_NoofSectors(Bank)) // verify to erase memory
						{
							if( Verify_Sectors_Erase(Flash_Erase_Add))
							{
								Flash_Erase_Flag = FALSE;
								Tx->Byte = BOOT_STATUS_OK; // this is an a ACK for Coressponding boot start Command data is received 		
								Boot_Res_Status();
								Boot_State_Control = Boot_Wating_for_next_command;
							}					
						}
						else
						{
							Tx->Byte = BOOT_STATUS_NOT_OK; // this is an a ACK for Coressponding boot start Command data is received 		
							Boot_Res_Status();
							Boot_State_Control = Boot_Start;					
						}
					}
				}
		break;
		}// switch end
	}
}

void Boot_Response_status()
{
	UBYTE *Data = ComIf_GetShadowBuffer_Boot_Boot_Response();
	Boot_TxByte_ST *Tx = &Boot_Tx_Data;
	
	*Data = Tx->Byte;	
	ComIf_TransmitFromBuffer_Boot_Boot_Response();
}

ULONG calculateChecksum(ULONG *data, ULONG length) 
{
    ULONG sum = 0;
    UBYTE i;
    // Sum up all the byte values
    for ( i = 0; i < length; i++) {
        sum = sum +data[i];
    }
		
    return sum; //((~sum) +1 );
}