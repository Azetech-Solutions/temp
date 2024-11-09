
/****HEADER FILE INCLUTION****/
#include "Bootloader_Main.h"
#include "Flowcontrol.h"

/***************************************************************************************/

static Boot_RxByte_ST Boot_Rx_Data; // Boot Rx ST
Boot_TxByte_ST Boot_Tx_Data;	// Boot Tx ST

/****ENUM VARIABLE Declaration****/
static Boot_state_EN Boot_State_Control = Boot_Idle;//Boot_Idle;//Boot_NVM_State;

/***************************************************************************************/
/****FLAGS Declaration****/
static BOOT_Control_ST Boot_CtlFlag;

/***************************************************************************************/

/*COMIF data Reception Function*/
void Boot_Req_Data_RxCbk(UBYTE Length, UBYTE *Data)
{
	BOOT_Control_ST *FlashControl = &Boot_CtlFlag;
	for(UBYTE i=0; i<Length;i++)
	{
		Boot_Rx_Data.Bytes[i] = *(Data++);
	}	
	FlashControl->BootCmdReceiveVerifyFlag = TRUE;
}

/************************************** Boot Main **************************************/

void Boot_Main()
{
	BOOT_Control_ST *FlashControl = &Boot_CtlFlag;
	Boot_RxByte_ST *Rx = &Boot_Rx_Data;
	Boot_TxByte_ST *Tx = &Boot_Tx_Data;
	
		switch(Boot_State_Control)
		{
			case Boot_Idle :
			{
				if(FlashControl->BootCmdReceiveVerifyFlag == TRUE)
				{
					if(Rx->Boot_command == FLASH_STARTCMD)
					{
						Tx->Boot_Status = BOOT_STATUS_OK;
						Boot_State_Control = Boot_Start;
						BOOT_RES_STATUS();
					}
					else if(Rx->Boot_command == FLASH_ERASECMD)
					{
						FlashControl->ChooseIndividualErase_Flg = TRUE;
						Boot_State_Control = Boot_Erase_Flash;
					}
					else 
					{ Tx->Byte = BOOT_STATUS_NOT_OK; 
						BOOT_RES_STATUS(); }
					
					FlashControl->BootCmdReceiveVerifyFlag = FALSE;
				}
			}
			break;
			case Boot_Start :
			{
				if(FlashControl->BootCmdReceiveVerifyFlag == TRUE)
				{
					if(Rx->Boot_command == FLASH_ERASECMD) {  //erase cmd
							FlashControl->ChooseFlash_Erase_Flag = TRUE;
							Boot_State_Control = Boot_Erase_Flash; 
					}
					else if(Rx->Boot_command == FLASH_FLASHCMD)  // application
					{
							if(FlashControl->IndividualEraseVerifyFlag == FALSE) {
								Tx->Boot_Status = BOOT_STATUS_OK;  
								Boot_State_Control = Boot_Start; 
							}
							else
							{
								Tx->Boot_Status = BOOT_STATUS_OK;
								Boot_State_Control = Boot_Wating_for_next_command;
								FlashControl->IndividualEraseVerifyFlag = FALSE;
							}
							BOOT_RES_STATUS();
					}
					else { Tx->Byte = BOOT_STATUS_NOT_OK; BOOT_RES_STATUS(); }			
					FlashControl->BootCmdReceiveVerifyFlag = FALSE;
				}
			}
			break;
			case Boot_Wating_for_next_command :
			{
				if(FlashControl->BootCmdReceiveVerifyFlag == TRUE)
				{
					if(Rx->Boot_command == FLASH_DATACMD) // flash the data write cmd
					{	
						Boot_State_Control = Boot_Flash_Write;
						FlashControl->Flash_Write_Flag = TRUE;
					}
					else if(Rx->Boot_command == FLASH_COMPLETECMD)  // flash complete cmd
					{
						if(FlashControl->ChooseNvsFlag == FALSE)
						{							
							uint32_t Flash_Add = TOGET_MEMORYADDRESS(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 
																												Rx->Flash_Add_3_byte, Rx->Flash_Add_4_byte);
							
							if(App_Image_Chksum_calculation((Flash_Add+ 0x40U)) == ChkAppHeader_ChkSum(Flash_Add))
							{
								if(Update_Nvm_Block(Flash_Add)) // NVM Block Updated
								{
									Tx->Byte = BOOT_STATUS_OK; 
									Boot_State_Control = Boot_Idle;
									BOOT_RES_STATUS();
								}
							}
						}						
					}
					else if(Rx->Boot_command == FLASH_ERASECMD) { 
						Tx->Byte = BOOT_STATUS_OK; 
						BOOT_RES_STATUS();					
					}
					else { Tx->Byte = BOOT_STATUS_NOT_OK; 
								 BOOT_RES_STATUS();}
					FlashControl->BootCmdReceiveVerifyFlag = FALSE;
				}
			}
			break;
			case Boot_Flash_Write :			
			{
				if(FlashControl->Flash_Write_Flag == TRUE)
				{
					ULONG Flash_Add=0, Flash_data[4]={0};

					/* Adding the Flash Address */
					Flash_Add = TOGET_MEMORYADDRESS(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 
																						Rx->Flash_Add_3_byte, Rx->Flash_Add_4_byte);
						
					/* FLash data's are arranging Based on hex file */
					Flash_data[0] = TOGET_DATA(Rx->Data_4, Rx->Data_3, Rx->Data_2, Rx->Data_1);
					Flash_data[1] = TOGET_DATA(Rx->Data_8, Rx->Data_7, Rx->Data_6, Rx->Data_5);
					Flash_data[2] = TOGET_DATA(Rx->Data_12, Rx->Data_11, Rx->Data_10, Rx->Data_9);
					Flash_data[3] = TOGET_DATA(Rx->Data_16, Rx->Data_15, Rx->Data_14, Rx->Data_13);
											
					if(FLASH_Multi_Word_write(Flash_Add, Flash_data, 4) != Flash_Add)
					{ //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
						Tx->Byte = BOOT_STATUS_OK;
						FlashControl->Flash_Write_Flag = FALSE;
					}
					else {	Tx->Byte = BOOT_STATUS_NOT_OK; }
					
					Boot_State_Control = Boot_Wating_for_next_command;							
					BOOT_RES_STATUS();
					FlashControl->BootCmdReceiveVerifyFlag = FALSE;				
				}		
			}
			break;
			case Boot_Erase_Flash :
			{
				uint32_t Flash_Erase_Add =0;
				uint8_t Bank=0;
				
				if(FlashControl->ChooseIndividualErase_Flg == TRUE)
				{
						if((Rx->Flash_Add_1_byte == BOOTMANAGER_SECTOR) && (Rx->Flash_Add_2_byte == BANK_1)) // single sector erase
						{
								if(FLASH_Erase_NoofSectors(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 1))
								{
									 if(VerifyFlashErase(BOOTMANAGER_BASE_ADDRESS,BOOTMANAGER_END_ADDRESS))
									 {
											FlashControl->IndividualEraseVerifyFlag = TRUE; // to used the flash write operation
											Tx->Byte = BOOT_STATUS_OK; // this is an a ACK for Coressponding boot start Command data is received 		
											Boot_State_Control = Boot_Idle;											
									 }
									 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; }
								}
								BOOT_RES_STATUS();
						}		/* Boot manager sector erase End*/
						else if((Rx->Flash_Add_1_byte == BOOTLOADER_SECTOR) && (Rx->Flash_Add_2_byte == BANK_1)) // Double sector erase
						{
								if(FLASH_Erase_NoofSectors(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 2))
								{
									 if(VerifyFlashErase(BOOTLOADER_BASE_ADDRESS,BOOTLOADER_END_ADDRESS))
									 { 	
											FlashControl->IndividualEraseVerifyFlag = TRUE;
											Tx->Byte = BOOT_STATUS_OK; 
											Boot_State_Control = Boot_Idle; 											
									 }
									 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; }
								}
								BOOT_RES_STATUS();
						}		/* Bootloader sector erase End*/
						else if((Rx->Flash_Add_1_byte == APP1_SECTOR) && (Rx->Flash_Add_2_byte == BANK_1)) // multi sector erase
						{
								if(FLASH_Erase_NoofSectors(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 5)) // verify to erase memory
								{
									if( VerifyFlashErase(APP_1_BASE_ADDRESS,APP_1_END_ADDRESS))
									{
										FlashControl->IndividualEraseVerifyFlag = TRUE;
										Tx->Byte = BOOT_STATUS_OK; 
										Boot_State_Control = Boot_Idle;										
									}
									else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; }
								}
								BOOT_RES_STATUS();
						}		/* App1 sector erase End*/
						else if((Rx->Flash_Add_1_byte == NVS_SECTOR) && (Rx->Flash_Add_2_byte == BANK_2))  // single sector erase
						{
								if(FLASH_Erase_NoofSectors(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 1))
								{
									 if(VerifyFlashErase(NVS_BASE_ADDRESS,NVS_END_ADDRESS))
									 {
											FlashControl->IndividualEraseVerifyFlag = TRUE;
											Tx->Byte = BOOT_STATUS_OK;												
											Boot_State_Control = Boot_Idle;											
									 }
									 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; }
								}
								BOOT_RES_STATUS();
						}		/* NVS sector erase End*/
						else if((Rx->Flash_Add_1_byte == NVM_SECTOR)&& (Rx->Flash_Add_2_byte == BANK_2))  // Double sector erase
						{
								if(FLASH_Erase_NoofSectors(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 2))
								{
									 if(VerifyFlashErase(NVM_BASE_ADDRESS,NVM_END_ADDRESS))
									 {
											FlashControl->IndividualEraseVerifyFlag = TRUE;
											Tx->Byte = BOOT_STATUS_OK;
											Boot_State_Control = Boot_Idle;
											Last_NVMBlock_Add = 0x08011FE0;											
									 }
									 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; }
								}
								BOOT_RES_STATUS();
						}		/* NVM sector erase End*/
						else if((Rx->Flash_Add_1_byte == APP2_SECTOR)&& (Rx->Flash_Add_2_byte == BANK_2))  // multi sector erase
						{
								if(FLASH_Erase_NoofSectors(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 5)) // verify to erase memory
								{
									if( VerifyFlashErase(APP_2_BASE_ADDRESS,APP_2_END_ADDRESS))
									{
										FlashControl->IndividualEraseVerifyFlag = TRUE;
										Tx->Byte = BOOT_STATUS_OK; 
										Boot_State_Control = Boot_Idle;										
									}
									else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; }
								}
								BOOT_RES_STATUS();
						}		/* App2 sector erase End*/			
					FlashControl->ChooseIndividualErase_Flg = FALSE;
				}  // end FlashControl->ChooseIndividualErase_Flg check

				if(FlashControl->ChooseFlash_Erase_Flag == TRUE)
				{
					Flash_Erase_Add = TOGET_MEMORYADDRESS(Rx->Flash_Add_1_byte, Rx->Flash_Add_2_byte, 
																									Rx->Flash_Add_3_byte, Rx->Flash_Add_4_byte);
					
					if(Flash_Erase_Add == APP_1_BASE_ADDRESS) { Bank = BANK_1; }
					else if(Flash_Erase_Add == APP_2_BASE_ADDRESS) {	Bank = BANK_2;	}
					
					if( ( Flash_Erase_Add == APP_1_BASE_ADDRESS ) || ( Flash_Erase_Add == APP_2_BASE_ADDRESS ) )
					{
						if(FLASH_Erase_NoofSectors(3, Bank ,5)) // verify to erase memory
						{
								Tx->Byte = BOOT_STATUS_OK; // this is an a ACK for Coressponding boot start Command data is received 		
								Boot_State_Control = Boot_Wating_for_next_command;
						}
						else
						{
							Tx->Byte = BOOT_STATUS_NOT_OK; // this is an a ACK for Coressponding boot start Command data is received 		
							Boot_State_Control = Boot_Start;							
						}
						BOOT_RES_STATUS();
					}
					FlashControl->ChooseFlash_Erase_Flag = FALSE;
				}
			}// switch end
			break;
		} // main switch case end	
} // Boot main function end

/***************************************************************************************/

void Boot_Response_status()
{
	UBYTE *Data = ComIf_GetShadowBuffer_Boot_Boot_Response();
	Boot_TxByte_ST *Tx = &Boot_Tx_Data;
	
	*Data = Tx->Byte;	
	
	ComIf_TransmitFromBuffer_Boot_Boot_Response();
}
/***************************************************************************************/

