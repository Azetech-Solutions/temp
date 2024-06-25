
#include "Flowcontrol.h"

//Tx
FC_TxData_ST FC_TxData;
//Rx
FC_RxData_ST FC_RxData;
//FC Manage 
FCControl_ST FCManage;

uint8_t FcRxFlag = FALSE;


/***************************************************************************************/

void FC_RxCbk(UBYTE Length, UBYTE *Data)
{
	for(int i=0;i<Length;i++)
	{
		FC_RxData.Bytes[i] = *(Data++);
	}
	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
	FcRxFlag = TRUE;
}

/***************************************************************************************/

uint16_t FindDataLengthInFlash(uint32_t startAddress, uint32_t sectorSize)
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

uint16_t FC_DataCopy(uint32_t SAdd,uint16_t Len)
{
	FC_TxData_ST *Tx = &FC_TxData;
	FCControl_ST *fcmge = &FCManage;
	uint16_t i = 0,cnt=0;
	uint8_t MemoryLen = (Len/sizeof(uint32_t));
	
	while((cnt < FCDATAMAXLENGTH)) // max len 61*4
	{
		if((*(uint32_t*)(SAdd)) != 0xFFFFFFFF &&(cnt <MemoryLen))
		{
			Tx->FCData[i]   = (uint8_t) ((*(uint32_t*)(SAdd)) >> 24);
			Tx->FCData[i+1] = (uint8_t) ((*(uint32_t*)(SAdd)) >> 16);
			Tx->FCData[i+2] = (uint8_t) ((*(uint32_t*)(SAdd)) >> 8);
			Tx->FCData[i+3] = (uint8_t) ((*(uint32_t*)(SAdd)));
			
			fcmge->FCNextAddress = SAdd += 4U;
			i += 4U;
			cnt++;
			Len -=4;
		}
		else { 
			Tx->FCData[i]   = 0;
			Tx->FCData[i+1] = 0;
			Tx->FCData[i+2] = 0;
			Tx->FCData[i+3] = 0;
			
			fcmge->FCNextAddress = SAdd += 4U;
			i += 4U;
			cnt++;
		}
	}
	
	fcmge->FCFlag.FC_TxDataUpdateFlag = TRUE;
	return Len;
}
/***************************************************************************************/

uint8_t FCTxDataUpdateComif()
{
	uint8_t retval = FALSE;
	FC_TxData_ST *tx = &FC_TxData;
	FCControl_ST *fcmge = &FCManage;
	uint8_t *Dta = ComIf_GetShadowBuffer_Boot_FC_Response();
	
	if(fcmge->FCFlag.FC_TxDataUpdateFlag == TRUE)
	{
		for(int i =0;i<ComIf_GetLength_Boot_FC_Response();i++)
		{
			Dta[i] = tx->Bytes[i];
		}
		
		fcmge->FCFlag.FC_TxDataUpdateFlag = FALSE;
		retval = TRUE;
		
		ComIf_TransmitFromBuffer_Boot_FC_Response();
	}
	
	return retval;
}
/***************************************************************************************/

uint8_t FCData_Transmit(uint32_t BlockAdd)
{
	FC_TxData_ST *tx = &FC_TxData;
	FC_RxData_ST *rx = &FC_RxData;
	FCControl_ST *fcmge = &FCManage;
	uint8_t retval=0;
	
	if(fcmge->FCFlag.FCInitialFlag == TRUE)
	{
		if(BlockAdd == NVM_BASE_ADDRESS) { 
			fcmge->FCMAXlength = FindDataLengthInFlash(NVM_BASE_ADDRESS,NVM_SECTOR_SIZE);
		}
		else if(BlockAdd == NVS_BASE_ADDRESS){ 
			fcmge->FCMAXlength = FindDataLengthInFlash(NVS_BASE_ADDRESS,NVS_SECTOR_SIZE);
		}
		
		if(fcmge->FCMAXlength != 0U) {
			FCFindFrameType(fcmge->FCMAXlength);
		}
		
		fcmge->FCFlag.FCInitialFlag = FALSE;
	}
	
	if(tx->FrameType == FCSINGLEFRAMETYPE)
	{
		if(fcmge->FCFlag.FCSingleframeFlag == TRUE) {
//		uint32_t Add = ((ULONG)Rx->AddMSB1 << 24)| ((ULONG)Rx->AddMSB2 << 16)|
//														((ULONG)Rx->AddLSB2 << 8) | ((ULONG)Rx->AddLSB1);
		uint32_t Add = 0x08012000;
		uint16_t Len = (((tx->LengthMSB1 << 8) | tx->Length) & 0x0FFF );
		
		FC_DataCopy(Add,Len); // data copy in the tx strucutre 
		FCTxDataUpdateComif(); // update and transmit
		
		fcmge->FCFlag.FCSingleframeFlag = FALSE;
		fcmge->FCFlag.FCInitialFlag = FALSE;
		}
		else {
			if(rx->FCAck == 0x00) {
				fcmge->FCFlag.FCInitialFlag = TRUE;
				retval = 1;
			}
		}		
	}
	else if(tx->FrameType == FCFIRSTFRAMETYPE || tx->FrameType == FCCONSECUTIVEFRAMETYPE)
	{
		if(fcmge->FCFlag.FCFirstframeFlag == TRUE)
		{
//		uint32_t Add = ((ULONG)Rx->AddMSB1 << 24)| ((ULONG)Rx->AddMSB2 << 16)|
//														((ULONG)Rx->AddLSB2 << 8) | ((ULONG)Rx->AddLSB1);
		
			uint32_t Add = 0x08012000;
			uint16_t Len = (((tx->LengthMSB1 << 8) | tx->Length) & 0x0FFF );
			
			fcmge->FCBalanceLength = FC_DataCopy(Add,Len);
			FCTxDataUpdateComif(); // update and transmit
			
			fcmge->FCFlag.FCFirstframeFlag = FALSE;
		}
		else
		{
			if(1) //(rx->FrameType == FCFLOWCONTROLFRAMETYPE)
			{
				uint16_t rxLen = (((rx->LengthMSB1 << 8) | rx->Length) & 0x0FFF );
													
					uint8_t Index = 0;
					
					if( fcmge->FCBalanceLength > 0) // (fcmge->FCMAXlength - rxLen)
					{
						tx->FrameType = FCCONSECUTIVEFRAMETYPE;
						tx->LengthMSB1 = Index;
						fcmge->FCBalanceLength = FC_DataCopy(fcmge->FCNextAddress,fcmge->FCBalanceLength );
						FCTxDataUpdateComif();
						Index++;					
					}
					else
					{
						retval = TRUE;
					}
			}
		}
	}
	
	return retval;
}
/***************************************************************************************/

void FCFindFrameType(uint16_t Len)
{
	FC_TxData_ST *FType = &FC_TxData;
	FCControl_ST *fcmge = &FCManage;
	uint16_t TotalLen = Len/sizeof(uint32_t);
	
	if(TotalLen <= FCDATAMAXLENGTH)
	{
		FType->FrameType = FCSINGLEFRAMETYPE;
		FType->LengthMSB1 = ((Len & 0x0F00) >> 8);
		FType->Length = (uint8_t)((Len & 0x00FF));
		fcmge->FCFlag.FCSingleframeFlag = TRUE;
	}
	else
	{
		FType->FrameType = FCFIRSTFRAMETYPE;
		FType->LengthMSB1 = ((Len & 0x0F00) >> 8);
		FType->Length = (uint8_t)((Len & 0x00FF));
		fcmge->FCFlag.FCFirstframeFlag = TRUE;
	}
}
/***************************************************************************************/

// if (length <= 6) {
//        // Single Frame (SF)
//        uint8_t sf[8] = {0x00};
//        sf[0] = 0x00 | length; // SF with length
//        memcpy(&sf[1], data, length);
//        UART_SendMessage(sf, 8);
//    } else {
//        // First Frame (FF)
//        uint8_t ff[8] = {0x10 | ((length >> 8) & 0x0F), length & 0xFF};
//        memcpy(&ff[2], data, 6);
//        UART_SendMessage(ff, 8);

//        // Wait for Flow Control (FC) frame
//        uint8_t fc[8] = {0};
//        HAL_UART_Receive(&huart1, fc, 8, HAL_MAX_DELAY);

//        if ((fc[0] & 0xF0) == 0x30) { // Flow Control Frame (FC)
//            uint8_t blockSize = fc[1];
//            uint8_t separationTime = fc[2];

//            // Consecutive Frames (CF)
//            uint16_t offset = 6;
//            uint8_t seqNum = 1;

//            while (offset < length) {
//                uint8_t cf[8] = {0x20 | (seqNum & 0x0F)};
//                uint8_t dataLen = (length - offset > 7) ? 7 : (length - offset);
//                memcpy(&cf[1], &data[offset], dataLen);
//                UART_SendMessage(cf, 8);
//                offset += dataLen;
//                seqNum++;
//                if (seqNum == blockSize) {
//                    seqNum = 0;
//                }
//                HAL_Delay(separationTime);
//            }
//        }
//    }