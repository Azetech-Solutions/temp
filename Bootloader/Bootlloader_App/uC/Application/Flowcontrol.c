
#include "Flowcontrol.h"
#include "NvmNvs_state_Handling.h"

//Tx
static FC_TxData_ST FC_TxData;
//Rx
FC_RxData_ST FC_RxData;
//FC Manage 
FlowControl_ST FCManage;

static uint32_t FCUpdateData[FC_DATAMAXLENGHT_RX];

static void FlowControl_STReset();

volatile uint16_t fcrxLen;
/***************************************************************************************/

void FC_RxCbk(UBYTE Length, UBYTE *Data)
{
	FlowControl_ST *fc = &FCManage;
	for(int i=0;i<Length;i++)
	{
		FC_RxData.Bytes[i] = *(Data++);
	}
	//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
	fc->FCFlag.FcRxFlag = TRUE;
	fcrxLen = (Length - 3);
}

/***************************************************************************************/

uint8_t Read_AppVersion(uint32_t Add)
{
	uint8_t retval = FALSE;
	FlowControl_ST *fcmge = &FCManage;
	FC_TxData_ST *tx = &FC_TxData;
	
	tx->FrameType = TOGET_LSBBITS(READVERSIONCMD);
	tx->LengthMSB1 = TOGET_MSBBITS(READVERSIONCMD);
		
	FC_DataCopy(&FC_TxData,(Add + 0x10),16);
	
	if(FCTxDataUpdateComif(&FC_TxData,fcmge->FCUpdateComifLength))
	{
		retval = TRUE;
		FlowControl_STReset();
	}
	return retval;
}
/***************************************************************************************/

static void FlowControl_STReset()
{
	FlowControl_ST *reset = &FCManage;
	
	reset->FCFlag.FCConsecutiveframeFlag = 0;
	reset->FCFlag.FCFirstframeFlag = 0;
	reset->FCFlag.FCInitialFlag = 0;
	reset->FCFlag.FcRxFlag = 0;
	reset->FCFlag.FCSingleframeFlag = 0;
	reset->FCFlag.FC_CompleteFlag = 0;
	reset->FCFlag.FC_TxDataUpdateFlag = 0;
	
	reset->FCBalanceLength = 0;
	reset->FCConsecutiveIndex = 0;
	reset->FCMAXlength = 0;
	reset->FCNextAddress = 0;
	reset->FCPreviousAddress = 0;
	reset->FCReceivedLength = 0;
	reset->FCUpdateComifLength = 0;
}
// This function return Total byte of the sector
static inline uint16_t  FindDataLengthInFlash(uint32_t startAddress, uint32_t sectorSize)
{
    uint16_t dataLength = 0;
    uint32_t *flashPtr = (uint32_t *)startAddress;
	
    while (dataLength < sectorSize) {
        if (*flashPtr == 0xFFFFFFFF) {
            break;
        }
        flashPtr++;
        dataLength += sizeof(uint32_t);
    }
    return dataLength;
}

/***************************************************************************************/
// This function find the type of transmission method (single or flow control) based on length
static inline void FCFindFrameType(FC_TxData_ST *FType, uint16_t Len)
{
	FlowControl_ST *fcmge = &FCManage;
	
	if(Len/sizeof(uint32_t) <= FC_DATAMAXLENGTH_TX)
	{
		FType->FrameType = FC_SINGLEFRAMETYPE;
		FType->LengthMSB1 = TOASSIGN_MSBBITS(Len);
		FType->Length = TOASSIGN_BYTE(Len);
		fcmge->FCFlag.FCSingleframeFlag = TRUE;
	}
	else
	{
		FType->FrameType = FC_FIRSTFRAMETYPE;
		FType->LengthMSB1 = TOASSIGN_MSBBITS(Len);
		FType->Length = TOASSIGN_BYTE(Len);
		fcmge->FCFlag.FCFirstframeFlag = TRUE;
	}
}
/***************************************************************************************/

// This function return balance length of the transmission
static uint16_t FC_DataCopy(FC_TxData_ST *Tx ,uint32_t SAdd,uint16_t Len)
{
	FlowControl_ST *fcmge = &FCManage;
	uint16_t i = 0,cnt=0;
	
	uint8_t MemoryLen = (Len/sizeof(uint32_t));
	
	fcmge->FCUpdateComifLength = 0 ;
	
	while((cnt < MemoryLen) && (cnt < FC_DATAMAXLENGTH_TX))
	{
		if((*(uint32_t*)(SAdd)) != 0xFFFFFFFF &&(cnt < MemoryLen))
		{
			Tx->FCData[i]   = (uint8_t) ((*(uint32_t*)(SAdd)) >> 24);
			Tx->FCData[i+1] = (uint8_t) ((*(uint32_t*)(SAdd)) >> 16);
			Tx->FCData[i+2] = (uint8_t) ((*(uint32_t*)(SAdd)) >> 8);
			Tx->FCData[i+3] = (uint8_t) ((*(uint32_t*)(SAdd)));
			
			fcmge->FCNextAddress = SAdd += 4U;
			i += 4U;
			cnt++;
			Len -=4;
			++fcmge->FCUpdateComifLength;
		}
		else { cnt++; }
	}	
	fcmge->FCUpdateComifLength *= sizeof(uint32_t);
	fcmge->FCUpdateComifLength += 3;  // Actual data's + 3 bytes of (frame type|lengthMSB1 + Length + Status|Timing)
	fcmge->FCFlag.FC_TxDataUpdateFlag = TRUE;
	
	return Len;
}
/***************************************************************************************/
// This function copy the data Tx struct to Comif and transmit to tool
static inline uint8_t FCTxDataUpdateComif(FC_TxData_ST *tx, uint16_t ComifDataLen)
{
	uint8_t retval = FALSE;
	FlowControl_ST *fcmge = &FCManage;
	uint8_t *Dta = ComIf_GetShadowBuffer_Boot_FC_Response();
	
	if(fcmge->FCFlag.FC_TxDataUpdateFlag == TRUE)
	{
		for(int i = 0; i < ComifDataLen ; i++)
		{
			Dta[i] = tx->Bytes[i];
		}
		
		fcmge->FCFlag.FC_TxDataUpdateFlag = FALSE;
		retval = TRUE;
		
		ComIf_Transmit_Boot_FC_Response(ComIf_ShadowBuffer_Boot_FC_Response,ComifDataLen); // comfi transmission
	}
	
	return retval;
}
/***************************************************************************************/
// this function transmit the Total data -> uC to Tool 
uint8_t FCData_Transmit()
{
	FC_TxData_ST *tx = &FC_TxData;
	FC_RxData_ST *rx = &FC_RxData;
	FlowControl_ST *fcTx = &FCManage;
	uint8_t retval=0;
	
	if(fcTx->FCFlag.FC_CompleteFlag == FALSE)
	{
/********************************************/
		if(fcTx->FCFlag.FCInitialFlag == FALSE)
		{
			if(fcTx->FCPreviousAddress == NVM_BASE_ADDRESS) { 
				fcTx->FCMAXlength = FindDataLengthInFlash(NVM_BASE_ADDRESS,NVM_SECTOR_SIZE);
			}
			else if(fcTx->FCPreviousAddress == NVS_BASE_ADDRESS){ 
				fcTx->FCMAXlength = FindDataLengthInFlash(NVS_BASE_ADDRESS,NVS_SECTOR_SIZE);
			}
			
			if(fcTx->FCMAXlength != 0U) {
				FCFindFrameType(&FC_TxData, fcTx->FCMAXlength);
			}
			fcTx->FCFlag.FCInitialFlag = TRUE;
		}
	/********************************************/
		if (tx->FrameType == FC_SINGLEFRAMETYPE)
		{
			if(fcTx->FCFlag.FCSingleframeFlag == TRUE)
			{
				FC_DataCopy( &FC_TxData, fcTx->FCPreviousAddress, fcTx->FCMAXlength ); // data copy in the tx strucutre 
				FCTxDataUpdateComif( &FC_TxData, fcTx->FCUpdateComifLength ); // update and transmit	
				fcTx->FCFlag.FCSingleframeFlag = FALSE;
			}
			
			if( TOGET_CMD(rx->LengthMSB1, rx->FrameType ) == NVM_GETALLDATACMD) //E1 CMD ((rx->LengthMSB1 << 4) | rx->FrameType )
			{
				if(rx->FCAck == FC_ABORTSTATUS) {
					fcTx->FCFlag.FC_CompleteFlag = TRUE;
				}
				else if(rx->FCAck == FC_WAITSTATUS)
				{
					// wait state do nothig 
				}
				else if(rx->FCAck == FC_REPEATSTATUS)
				{
					fcTx->FCFlag.FCSingleframeFlag = TRUE;
				}
			}
		}
	/********************************************/
		else if( tx->FrameType == FC_FIRSTFRAMETYPE || tx->FrameType == FC_CONSECUTIVEFRAMETYPE )
		{
			if(fcTx->FCFlag.FCFirstframeFlag == TRUE)
			{ //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
				fcTx->FCBalanceLength = FC_DataCopy( &FC_TxData, fcTx->FCPreviousAddress, fcTx->FCMAXlength );
				FCTxDataUpdateComif( &FC_TxData, fcTx->FCUpdateComifLength ); // update and transmit
				
				fcTx->FCFlag.FCConsecutiveframeFlag = TRUE;
				fcTx->FCFlag.FCFirstframeFlag = FALSE;		
			}
			else
			{
				if( rx->FrameType == FC_FLOWCONTROLFRAMETYPE )
				{
					//uint16_t rxLen = ; // (((rx->LengthMSB1 << 8) | rx->Length) & 0x0FFF );
						
						if(rx->FCAck == FC_SENDSTATUS && ((fcTx->FCMAXlength - TOGET_12_BITLENGTH(rx->LengthMSB1, rx->Length) ) > 0) )
						{
							while(fcTx->FCBalanceLength > 0)
							{
								tx->FrameType = FC_CONSECUTIVEFRAMETYPE;
								tx->LengthMSB1 = fcTx->FCConsecutiveIndex; // set the consecutive index  // need changes
								
								fcTx->FCBalanceLength = FC_DataCopy( &FC_TxData, fcTx->FCNextAddress, fcTx->FCBalanceLength );
								
								FCTxDataUpdateComif( &FC_TxData, fcTx->FCUpdateComifLength );
								fcTx->FCConsecutiveIndex++;
							}
							
							fcTx->FCFlag.FCConsecutiveframeFlag = FALSE;
						}
						else
						{
							if(rx->FCAck == FC_ABORTSTATUS) {
								fcTx->FCFlag.FC_CompleteFlag = TRUE;
							}
							else if(rx->FCAck == FC_SENDSTATUS)
							{
								//fcTx->FCPreviousAddress = fcTx->FCNextAddress;
								//fcTx->FCFlag.FCConsecutiveframeFlag = FALSE;
							}
							else if(rx->FCAck == FC_WAITSTATUS)
							{
								// wait state do nothig 
							}
							else if(rx->FCAck == FC_REPEATSTATUS)
							{
								fcTx->FCFlag.FCFirstframeFlag = TRUE;
							}
						}
							
				}
			}
		}

	/********************************************/
		if(fcTx->FCFlag.FC_CompleteFlag == TRUE) // reset all variables
		{
			FlowControl_STReset();
			retval = 1;
		}
	}	
	return retval;
}

/***************************************************************************************/

uint8_t FCData_Receive()
{
	uint8_t retval= FALSE;
	FC_TxData_ST *tx = &FC_TxData;
	FC_RxData_ST *rx = &FC_RxData;
	FlowControl_ST *fcRx = &FCManage;
/*****************************************************/
	if(fcRx->FCFlag.FC_CompleteFlag == FALSE)
	{
		if(rx->FrameType == FC_SINGLEFRAMETYPE)
		{
			if(fcRx->FCFlag.FCSingleframeFlag == FALSE)
			{
				fcRx->FCMAXlength = TOASSIGN_BYTE(rx->Length); //( rx->Length & 0xFF);
				received_DataCopy(fcRx->FCUpdateComifLength, &FC_RxData); // copy the data to the buffer
				
				if(fcRx->FCMAXlength == fcRx->FCReceivedLength)
				{
					//(Last_NVMBlock_Add + (NVM_ONE_BLOCK_SIZE*sizeof(uint32_t)))
					if((FLASH_Multi_Word_write(fcRx->FCPreviousAddress, FCUpdateData, fcRx->FCUpdateComifLength)))
					{
						HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
						tx->FrameType = FC_SINGLEFRAMETYPE;
						tx->LengthMSB1 = 0;
						tx->Length = 0;
						tx->FCTiming = 0;
						tx->FCAck = FC_ABORTSTATUS;
						fcRx->FCFlag.FC_TxDataUpdateFlag = TRUE;
						FCTxDataUpdateComif( &FC_TxData, 3);
						fcRx->FCFlag.FC_CompleteFlag = TRUE;
					}
				}
				fcRx->FCFlag.FCSingleframeFlag = TRUE;
			}						
		}
/*****************************************************/
		else if (rx->FrameType == FC_FIRSTFRAMETYPE)
		{
			if(fcRx->FCFlag.FCFirstframeFlag == FALSE)
			{
				fcRx->FCMAXlength = TOGET_12_BITLENGTH(rx->LengthMSB1, rx->Length);
				
				received_DataCopy(fcRx->FCUpdateComifLength, &FC_RxData); // data copied, and fcupdatecomif length initially 
				
				if (fcRx->FCReceivedLength == (fcRx->FCUpdateComifLength * 4U))
				{
					tx->FrameType = FC_FLOWCONTROLFRAMETYPE;
					tx->LengthMSB1 = TOASSIGN_MSBBITS(fcRx->FCReceivedLength);
					tx->Length = TOASSIGN_BYTE(fcRx->FCReceivedLength);
					tx->FCTiming = 0;
					tx->FCAck = FC_SENDSTATUS;				
					
					fcRx->FCFlag.FC_TxDataUpdateFlag = TRUE;
					FCTxDataUpdateComif( &FC_TxData, 3);
				}
				fcRx->FCFlag.FCFirstframeFlag = TRUE;
			}			
		}
/*****************************************************/
		else if (rx->FrameType == FC_CONSECUTIVEFRAMETYPE)
		{
			if(fcRx->FCMAXlength != fcRx->FCReceivedLength )
			{
				if(fcRx->FCFlag.FcRxFlag == TRUE)
				{
					HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
						if(received_DataCopy(fcRx->FCUpdateComifLength, &FC_RxData))
						{
							tx->FrameType = FC_FLOWCONTROLFRAMETYPE;
							tx->LengthMSB1 = TOASSIGN_MSBBITS(fcRx->FCReceivedLength);
							tx->Length = TOASSIGN_BYTE(fcRx->FCReceivedLength);
							tx->FCTiming = 0;
							tx->FCAck = FC_SENDSTATUS;
							
							fcRx->FCFlag.FC_TxDataUpdateFlag = TRUE;
							FCTxDataUpdateComif( &FC_TxData, 3);
							
						}
					fcRx->FCFlag.FcRxFlag = FALSE;
					}
				}
				else if(fcRx->FCMAXlength == fcRx->FCReceivedLength)
				{
					if((FLASH_Multi_Word_write(fcRx->FCPreviousAddress, FCUpdateData, fcRx->FCUpdateComifLength)))
					{
						tx->FrameType = FC_FLOWCONTROLFRAMETYPE;
						tx->LengthMSB1 = 0;
						tx->Length = 0;					
						tx->FCTiming = 0;					
						tx->FCAck = FC_ABORTSTATUS;
						
						fcRx->FCFlag.FC_TxDataUpdateFlag = TRUE;
						FCTxDataUpdateComif( &FC_TxData, 3);
						fcRx->FCFlag.FC_CompleteFlag = TRUE;
						
					}
				}
			}				
		}
/*****************************************************/
		if(fcRx->FCFlag.FC_CompleteFlag == TRUE) // reset all variables
		{
			FlowControl_STReset();
			retval = TRUE;
		}				
	
	return retval;
}


uint8_t received_DataCopy(uint8_t pos, FC_RxData_ST *rx)
{
	uint8_t retval =  FALSE;
	FlowControl_ST *fcRx = &FCManage;		
	uint8_t i = pos,ReceivingDataLen = 0,LenCount = 0;
	
	if(fcrxLen < 3)
	{
		return FALSE;
	}
	
	while( ReceivingDataLen < fcrxLen)
	{
		FCUpdateData[i] = TOGET_DATA(rx->FCData[ReceivingDataLen], rx->FCData[ReceivingDataLen+1], 
																	rx->FCData[ReceivingDataLen+2], rx->FCData[ReceivingDataLen+3]);
		i++; LenCount++;
		ReceivingDataLen += 4;
	}
	
	fcRx->FCReceivedLength += ReceivingDataLen;
	fcRx->FCUpdateComifLength += LenCount;
	
	return retval = TRUE;
}

uint8_t NvmTool_Update()
{
	FC_TxData_ST *tx = &FC_TxData;
	FC_RxData_ST *fcrx = &FC_RxData;
	FlowControl_ST *fcmge = &FCManage;	
	uint8_t retval = 0;
	
	//Chk_NVMLast_BlockAdd(); // recheck the nvm block address
	
		fcmge->FCMAXlength = TOASSIGN_BYTE(fcrx->Length);
		received_DataCopy(fcmge->FCUpdateComifLength, &FC_RxData); // copy the data to the buffer
	//	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
		if(fcmge->FCMAXlength == fcmge->FCReceivedLength)
		{
			if((FLASH_Multi_Word_write((Last_NVMBlock_Add + (NVM_ONE_BLOCK_SIZE*sizeof(uint32_t))), FCUpdateData, fcmge->FCUpdateComifLength)))
			{
				tx->FrameType = TOGET_LSBBITS(0xE2);
				tx->LengthMSB1 = TOGET_MSBBITS(0xE2);
				tx->Length = 0;
				tx->FCTiming = 0;
				tx->FCAck = FC_ABORTSTATUS;
				fcmge->FCFlag.FC_TxDataUpdateFlag = TRUE;
				FCTxDataUpdateComif( &FC_TxData, 3);
				fcmge->FCFlag.FC_CompleteFlag = TRUE;
			}
		}
			
		if(fcmge->FCFlag.FC_CompleteFlag == TRUE) // reset all variables
		{
			fcmge = (0);
			retval = TRUE;
		}			
	return retval;
}
