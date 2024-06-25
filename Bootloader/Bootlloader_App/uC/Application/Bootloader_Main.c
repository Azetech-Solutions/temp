
/****HEADER FILE INCLUTION****/
#include "Bootloader_Main.h"
#include "stm32h5xx_hal_gpio.h"
#include "Flowcontrol.h"

/***************************************************************************************/

Boot_RxByte_ST Boot_Rx_Data; //Rx callback function Variable

Boot_TxByte_ST Boot_Tx_Data; //TX function Variable

static volatile uint8_t cnt=0; //to Receive the Last Adderss of the Flash

static volatile ULONG Verify_AppCkSum;

/****ENUM VARIABLE Declaration****/
Boot_state_EN Boot_State_Control = Boot_Idle;

/***************************************************************************************/

/****FLAGS Declaration****/
static UBYTE BootCmdReceiveVerifyFlag = FALSE;
static UBYTE Flash_Write_Flag = FALSE;
static UBYTE ChooseNvsFlag = FALSE;

static UBYTE IndividualEraseVerifyFlag = FALSE;   // verify the individual erase is done or not
static UBYTE ChooseIndividualErase_Flg = FALSE;  // in idle state handle
static UBYTE Flash_Erase_Flag = FALSE;   // this is used to cyclic method

/***************************************************************************************/

/*COMIF data Reception Function*/
void Boot_Req_Data_RxCbk(UBYTE Length, UBYTE *Data)
{
	for(UBYTE i=0; i<Length;i++)
	{
		Boot_Rx_Data.Bytes[i] = *(Data++);
	}
	
	BootCmdReceiveVerifyFlag = TRUE;
	//Debug_SendString("OK\n");
}

/************************************** Boot Main **************************************/

void Boot_Main()
{
	Boot_RxByte_ST *Rx = &Boot_Rx_Data;
	Boot_TxByte_ST *Tx = &Boot_Tx_Data;
	FC_RxData_ST *FcRx = &FC_RxData;
	
	uint8_t FC_CMD = ((FcRx->LengthMSB1 << 4) | FcRx->FrameType );
	switch(Boot_State_Control)
	{
		case Boot_Idle :
		{cnt++;
			//Debug_SendString("Idle\n");
			if(BootCmdReceiveVerifyFlag == TRUE || FcRxFlag == TRUE)
			{
				if(Rx->Boot_command == 0xF5)
				{
					Tx->Boot_Status = BOOT_STATUS_OK;
					Boot_State_Control = Boot_Start;
					Boot_Res_Status();
				}
				else if(Rx->Boot_command == 0xFE)
				{
					ChooseIndividualErase_Flg = TRUE;
					Boot_State_Control = Boot_Erase_Flash;
				}
				else if( FC_CMD >= 0xE1 && FC_CMD <=  0xE5)
				{
					NVM_Block.NVM_CtrlFlg.IsNVMTrg = TRUE;  // main block handled
					Boot_State_Control = Boot_NVM_State;
				}
				else 
				{ Tx->Byte = BOOT_STATUS_NOT_OK; 
					Boot_Res_Status(); }
				
				BootCmdReceiveVerifyFlag = FALSE; FcRxFlag = FALSE;				
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
			//Debug_SendString("Start\n");			
			if(BootCmdReceiveVerifyFlag == TRUE)
			{
				if(Rx->Boot_command == 0xFE)
				{
						Flash_Erase_Flag = TRUE;  
						Boot_State_Control = Boot_Erase_Flash; 
				}
				else if(Rx->Boot_command == 0xFA) // nvs
				{		
						if(IndividualEraseVerifyFlag == FALSE)
						{
							if(*(uint32_t*)(NVS_BASE_ADDRESS) != 0xFFFFFFFF || *(uint32_t*)(NVS_BASE_ADDRESS) == 0xFFFFFFFF )
							{
								if(Flash_SingleSec_Erase(NVS_BLOCK_SECTOR,BANK_2)) // For Erasing NVS Block
								{
									Boot_State_Control = Boot_Wating_for_next_command;
									Tx->Boot_Status = BOOT_STATUS_OK;
									Boot_Res_Status();
									ChooseNvsFlag = TRUE; } } }
						else
						{
							Boot_State_Control = Boot_Wating_for_next_command;
							Tx->Boot_Status = BOOT_STATUS_OK;
							Boot_Res_Status();
							ChooseNvsFlag = TRUE;  
							IndividualEraseVerifyFlag = FALSE; }
				}
				else if(Rx->Boot_command == 0xFB)  // application
				{
						if(IndividualEraseVerifyFlag == FALSE)
						{ //Verify_AppCkSum = 0;
							Tx->Boot_Status = BOOT_STATUS_OK;  
							Boot_State_Control = Boot_Start;
							Boot_Res_Status(); }
						else
						{
							//Verify_AppCkSum = 0;
							Tx->Boot_Status = BOOT_STATUS_OK;
							Boot_State_Control = Boot_Wating_for_next_command;
							IndividualEraseVerifyFlag = FALSE;
							Boot_Res_Status();
						}
				}
				else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_Res_Status(); }			
				BootCmdReceiveVerifyFlag = FALSE;
			}		
		}
		break;
		case Boot_Wating_for_next_command :
		{
			//Debug_SendString("Wait\n");
			if(BootCmdReceiveVerifyFlag == TRUE)
			{
				if(Rx->Boot_command == 0xFD)
				{					
					Boot_State_Control = Boot_Flash_Write;
					Flash_Write_Flag = TRUE;
				}
				else if(Rx->Boot_command == 0xFC)
				{									
					if(ChooseNvsFlag == FALSE)
					{ uint32_t Flash_Add = 0;						
						Flash_Add = ((ULONG)Rx->Flash_Add_1_byte << 24)| ((ULONG)Rx->Flash_Add_2_byte << 16)|
														((ULONG)Rx->Flash_Add_3_byte << 8) | ((ULONG)Rx->Flash_Add_4_byte);
						
						//Verify_AppCkSum = ((~Verify_AppCkSum)+1); // to find the total data of checksum							
						if(App_Image_Chksum_calculation((Flash_Add+ 0x40U)) == ChkAppHeader_ChkSum(Flash_Add))
						{
							//Debug_SendNumberWithDescription("FCkSum",Verify_AppCkSum);
							if(Update_Nvm_Block(Flash_Add))
							{
								HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
								//Debug_SendString("T_com\n"); 
								Tx->Byte = BOOT_STATUS_OK; 
								Boot_State_Control = Boot_Idle;
								//Verify_AppCkSum = 0;
								Boot_Res_Status();
							}
						}
					}
					else { ChooseNvsFlag = FALSE; 
								Tx->Byte = BOOT_STATUS_OK; 
								Boot_State_Control = Boot_Idle;
								Boot_Res_Status(); }
				}
				else if(Rx->Boot_command == 0xFE) 
				{ Tx->Byte = BOOT_STATUS_OK; 
					Boot_Res_Status();
					
				}
				else { Tx->Byte = BOOT_STATUS_NOT_OK; 
							 Boot_Res_Status();}
				BootCmdReceiveVerifyFlag = FALSE;
			}
		}
		break;
		case Boot_Flash_Write :
		{	//Debug_SendString("Flash\n");			
			if(Flash_Write_Flag == TRUE)
			{
					ULONG Flash_Add=0, Flash_data[4]={0};

					/* Adding the Flash Address */
					Flash_Add = ((ULONG)Rx->Flash_Add_1_byte << 24)| ((ULONG)Rx->Flash_Add_2_byte << 16)|
														((ULONG)Rx->Flash_Add_3_byte << 8) | ((ULONG)Rx->Flash_Add_4_byte);
					
					if(ChooseNvsFlag == TRUE)
					{
								/* FLash data's are arranging */
						Flash_data[0] = ((ULONG)(Rx->Data_1 << 24) | (ULONG)(Rx->Data_2 << 16) |
														(ULONG)(Rx->Data_3 << 8) | (ULONG)Rx->Data_4);
						Flash_data[1] = ((ULONG)(Rx->Data_5 << 24) | (ULONG)(Rx->Data_6 << 16) | 
														(ULONG)(Rx->Data_7 << 8) | (ULONG)Rx->Data_8);
						Flash_data[2] = ((ULONG)(Rx->Data_9 << 24) | (ULONG)(Rx->Data_10 << 16) | 
														(ULONG)(Rx->Data_11 << 8) | (ULONG)Rx->Data_12);
						Flash_data[3] = ((ULONG)(Rx->Data_13 << 24) | (ULONG)(Rx->Data_14 << 16) | 
														(ULONG)(Rx->Data_15 << 8) | (ULONG)Rx->Data_16);
					}
					else
					{
							/* FLash data's are arranging */
						Flash_data[0] = ((ULONG)(Rx->Data_4 << 24) | (ULONG)(Rx->Data_3 << 16) |
															(ULONG)(Rx->Data_2 << 8) | (ULONG)Rx->Data_1);
						Flash_data[1] = ((ULONG)(Rx->Data_8 << 24) | (ULONG)(Rx->Data_7 << 16) | 
															(ULONG)(Rx->Data_6 << 8) | (ULONG)Rx->Data_5);
						Flash_data[2] = ((ULONG)(Rx->Data_12 << 24) | (ULONG)(Rx->Data_11 << 16) | 
															(ULONG)(Rx->Data_10 << 8) | (ULONG)Rx->Data_9);
						Flash_data[3] = ((ULONG)(Rx->Data_16 << 24) | (ULONG)(Rx->Data_15 << 16) | 
															(ULONG)(Rx->Data_14 << 8) | (ULONG)Rx->Data_13);
					}
					
//					if((ChooseNvsFlag == FALSE && (Flash_Add >=0x08006040)) || (ChooseNvsFlag == FALSE && (Flash_Add >= 0x08016040 )))
//					{						
//						Verify_AppCkSum += calculateChecksum( Flash_data, (sizeof(Flash_data)/sizeof(Flash_data[0])) );
//						//Debug_SendNumberWithDescription("CkSum",Verify_AppCkSum);
//					}
										
					if((Rx->Boot_command == 0xFD) && (Flash_Add != 0U))
					{	
						
						if(Multi_Word_write(Flash_Add,Flash_data) != Flash_Add)
						{
							Tx->Byte = BOOT_STATUS_OK;
							Flash_Write_Flag = FALSE;
							Boot_State_Control = Boot_Wating_for_next_command;							
						}
						else {	Tx->Byte = BOOT_STATUS_NOT_OK; }	
					}
				Boot_Res_Status();
				BootCmdReceiveVerifyFlag = FALSE;				
			}		
		}
		break;
		case Boot_Erase_Flash :
		{
			//Debug_SendString("Erase\n");
			uint32_t Flash_Erase_Add =0;
			uint8_t Bank=0;
			
			if(ChooseIndividualErase_Flg == TRUE)
			{
				if((Rx->Flash_Add_1_byte == BOOTMANAGER_SECTOR) && (Rx->Flash_Add_2_byte == BANK_1)) // single sector erase
				{
							if(Flash_SingleSec_Erase(Rx->Flash_Add_1_byte,Rx->Flash_Add_2_byte))
							{
								 if(VerifyFlashErase(BOOTMANAGER_BASE_ADDRESS,BOOTMANAGER_END_ADDRESS))
								 {
									  IndividualEraseVerifyFlag = TRUE; // to used the flash write operation
										Tx->Byte = BOOT_STATUS_OK; // this is an a ACK for Coressponding boot start Command data is received 		
										Boot_State_Control = Boot_Idle;
										Boot_Res_Status();
								 }
								 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle;
												Boot_Res_Status(); }
							}
							else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; Boot_Res_Status(); }
					}
					else if((Rx->Flash_Add_1_byte == BOOTLOADER_SECTOR) && (Rx->Flash_Add_2_byte == BANK_1)) // Double sector erase
					{
							if(Flash_DoubleSec_Erase(Rx->Flash_Add_1_byte,Rx->Flash_Add_2_byte))
							{
								 if(VerifyFlashErase(BOOTLOADER_BASE_ADDRESS,BOOTLOADER_END_ADDRESS))
								 { 	
										IndividualEraseVerifyFlag = TRUE;
										Tx->Byte = BOOT_STATUS_OK; 
										Boot_State_Control = Boot_Idle; 
										Boot_Res_Status();
								 }
								 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; 
												Boot_Res_Status(); }
							}
							else { Tx->Byte = BOOT_STATUS_NOT_OK;	Boot_State_Control = Boot_Idle; Boot_Res_Status(); }
					}
					else if((Rx->Flash_Add_1_byte == APP1_SECTOR) && (Rx->Flash_Add_2_byte == BANK_1)) // multi sector erase
					{
							if(FLASH_Erase_NoofSectors(Rx->Flash_Add_2_byte)) // verify to erase memory
							{
								if( VerifyFlashErase(APP_1_BASE_ADDRESS,APP_1_END_ADDRESS))
								{
									IndividualEraseVerifyFlag = TRUE;
									Tx->Byte = BOOT_STATUS_OK; 
									Boot_State_Control = Boot_Idle;
									Boot_Res_Status();
								}
								else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; 
											 Boot_Res_Status(); }
							}
							else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; Boot_Res_Status(); }
					}
					else if((Rx->Flash_Add_1_byte == NVS_SECTOR) && (Rx->Flash_Add_2_byte == BANK_2))  // single sector erase
					{
							if(Flash_SingleSec_Erase(Rx->Flash_Add_1_byte,Rx->Flash_Add_2_byte))
							{
								 if(VerifyFlashErase(NVS_BASE_ADDRESS,NVS_END_ADDRESS))
								 {
										IndividualEraseVerifyFlag = TRUE;
										Tx->Byte = BOOT_STATUS_OK;												
										Boot_State_Control = Boot_Idle;
										Boot_Res_Status();
								 }
								 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; 
												Boot_Res_Status(); }
							}
							else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; Boot_Res_Status(); }
					}
					else if((Rx->Flash_Add_1_byte == NVM_SECTOR)&& (Rx->Flash_Add_2_byte == BANK_2))  // Double sector erase
					{
							if(Flash_DoubleSec_Erase(Rx->Flash_Add_1_byte,Rx->Flash_Add_2_byte))
							{
								 if(VerifyFlashErase(NVM_BASE_ADDRESS,NVM_END_ADDRESS))
								 {
										IndividualEraseVerifyFlag = TRUE;
										Tx->Byte = BOOT_STATUS_OK;
										Boot_State_Control = Boot_Idle;
										Last_NVMBlock_Add = 0x08011FE0;
										Boot_Res_Status();
								 }
								 else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; 
												Boot_Res_Status(); }
							}
							else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; Boot_Res_Status(); }
					}
					else if((Rx->Flash_Add_1_byte == APP2_SECTOR)&& (Rx->Flash_Add_2_byte == BANK_2))  // multi sector erase
					{
							if(FLASH_Erase_NoofSectors(Rx->Flash_Add_2_byte)) // verify to erase memory
							{
								if( VerifyFlashErase(APP_2_BASE_ADDRESS,APP_2_END_ADDRESS))
								{
									IndividualEraseVerifyFlag = TRUE;
									Tx->Byte = BOOT_STATUS_OK; 
									Boot_State_Control = Boot_Idle;
									Boot_Res_Status();
								}
								else { Tx->Byte = BOOT_STATUS_NOT_OK; Boot_State_Control = Boot_Idle; 
											 Boot_Res_Status(); }
							}
							else{ Tx->Byte = BOOT_STATUS_NOT_OK;  Boot_State_Control = Boot_Idle; Boot_Res_Status(); }
					}					
				ChooseIndividualErase_Flg = FALSE;
			}  // end ChooseIndividualErase_Flg check

			if(Flash_Erase_Flag == TRUE)
			{
				Flash_Erase_Add = ((ULONG)Rx->Flash_Add_1_byte << 24)| ((ULONG)Rx->Flash_Add_2_byte << 16)|
										((ULONG)Rx->Flash_Add_3_byte << 8) | ((ULONG)Rx->Flash_Add_4_byte);					
				
				if(Flash_Erase_Add == APP_1_BASE_ADDRESS) { Bank = BANK_1; }
				else if(Flash_Erase_Add == APP_2_BASE_ADDRESS) {	Bank = BANK_2;	}
				
				if((Flash_Erase_Add == APP_1_BASE_ADDRESS && Flash_Erase_Add != 0U) || (Flash_Erase_Add == APP_2_BASE_ADDRESS && Flash_Erase_Add != 0U))
				{
					if(FLASH_Erase_NoofSectors(Bank)) // verify to erase memory
					{						
							Tx->Byte = BOOT_STATUS_OK; // this is an a ACK for Coressponding boot start Command data is received 		
							Boot_State_Control = Boot_Wating_for_next_command;
							Boot_Res_Status();
					}
					else
					{
						Tx->Byte = BOOT_STATUS_NOT_OK; // this is an a ACK for Coressponding boot start Command data is received 		
						Boot_State_Control = Boot_Start;
						Boot_Res_Status();
					}					
				}
				Flash_Erase_Flag = FALSE;
			}
		}// switch end
		break;
		case Boot_NVM_State:
		{
				if(FC_CMD == 0xE1)
				{
					NVM_Block.NVM_CtrlFlg.IsGetAllData = TRUE;					
					
					Boot_State_Control = Boot_Idle;
				}
				else if(FC_CMD == 0xE2)
				{
					NVM_Block.NVM_CtrlFlg.IsUpdateTrg = TRUE;
//					if( NvmTool_Update())
//					{
//						Tx->Byte = BOOT_STATUS_OK; Boot_State_Control = Boot_Idle;
//					}
//					else { Boot_State_Control = Boot_Idle; Tx->Byte = BOOT_STATUS_NOT_OK; }
				}
				else if(FC_CMD == 0xE3)
				{
					NVM_Block.NVM_CtrlFlg.IsClearTrg = TRUE;
					if( NVMToolClear() )
					{
						Tx->Byte = BOOT_STATUS_OK; 
						Boot_State_Control = Boot_Idle;
						Boot_Res_Status();
					}
					else { Boot_State_Control = Boot_Idle; 
								 Tx->Byte = BOOT_STATUS_NOT_OK; 
								 Boot_Res_Status(); }
				}
				else if(FC_CMD == 0xE4)
				{
					NVM_Block.NVM_CtrlFlg.IsUpdateAllTrg = TRUE;
					
				}
				else if(FC_CMD == 0xE5)
				{
					NVM_Block.NVM_CtrlFlg.IsReorgTrg = TRUE;
					if( NVM_ReOrg() )
					{
						Tx->Byte = BOOT_STATUS_OK;
						Boot_State_Control = Boot_Idle;
						Boot_Res_Status();
					}
					else { Boot_State_Control = Boot_Idle; 
							   Tx->Byte = BOOT_STATUS_NOT_OK;
								 Boot_Res_Status(); }
				}
		}
		break;
	}
}
/***************************************************************************************/

void Boot_Response_status()
{
	UBYTE *Data = ComIf_GetShadowBuffer_Boot_Boot_Response();
	Boot_TxByte_ST *Tx = &Boot_Tx_Data;
	
	*Data = Tx->Byte;	
	ComIf_TransmitFromBuffer_Boot_Boot_Response();
}
/***************************************************************************************/

//ULONG calculateChecksum(ULONG *data, ULONG length) 
//{
//    ULONG sum = 0;
//    UBYTE i;
//    // Sum up all the byte values
//    for ( i = 0; i < length; i++) {
//        sum = sum +data[i];
//    }
//		
//    return sum;
//}
/***************************************************************************************/