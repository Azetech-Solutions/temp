
#ifndef __FLOWCONTROL_H__
#define __FLOWCONTROL_H__

#include "Ports_init.h"
#include "Addresses_Handling.h"

#define FCDATAMAXLENGTH  												 (61U)  // this len is max data transmit to tool

#define FCSINGLEFRAMETYPE                     		 (0U)
#define FCFIRSTFRAMETYPE                     			 (1U)
#define FCCONSECUTIVEFRAMETYPE                     (2U)
#define FCFLOWCONTROLFRAMETYPE                     (3U)
/************************************************************/
typedef union _FC_TxData
{
	struct
	{
		// 1st byte
		uint8_t FrameType :4;
		uint8_t LengthMSB1 :4;
		// 2nd byte
		uint8_t Length :8;
		// 3rd byte
		uint8_t FCAck :4;
		uint8_t FCTiming :4;
		// 244 bytes
		uint8_t FCData[244];
	};
	uint8_t Bytes[247];
	
}FC_TxData_ST;

/************************************************************/

typedef union _FC_RxData
{
	struct
	{	// 1st byte
		uint8_t FrameType :4;
		uint8_t LengthMSB1 :4;
		// 2nd byte
		uint8_t Length :8;
		// 3rd byte
		uint8_t FCAck :4;
		uint8_t FCTiming :4;
		// 4 to 7 bytes
		uint8_t AddMSB1 :8;
		uint8_t AddMSB2 :8;
		uint8_t AddLSB2 :8;
		uint8_t AddLSB1 :8;
		// 240 bytes
		uint8_t FCData[240];
	};
	uint8_t Bytes[247];
	
}FC_RxData_ST;


typedef struct _FC_ControlFlags
{
	uint8_t FCInitialFlag : 1;
	uint8_t FCSingleframeFlag : 1;
	uint8_t FCFirstframeFlag  : 1;
	uint8_t FCConsecutiveframeFlag : 1;
	uint8_t	FCFlowcontrolframeFlag : 1;
	uint8_t FC_TxDataUpdateFlag : 1;
}FCControlFlags_ST;

typedef struct _FC_Control
{
	FCControlFlags_ST FCFlag;
	uint16_t FCMAXlength;
	uint16_t FCReceivedLength;
	uint16_t FCBalanceLength;
	uint32_t FCNextAddress;

}FCControl_ST;

/*Variable*/
extern uint8_t FcRxFlag;
extern FC_RxData_ST FC_RxData;
extern FC_TxData_ST FC_TxData;
extern FCControl_ST FCManage;

extern void FC_RxCbk(UBYTE Length, UBYTE *Data); // comif function

extern uint16_t FindDataLengthInFlash(uint32_t startAddress, uint32_t sectorSize);

extern void FCFindFrameType(uint16_t Len);
extern uint8_t FCData_Transmit(uint32_t BlockAdd);
extern uint16_t FC_DataCopy(uint32_t SAdd,uint16_t Len);
extern uint8_t FCTxDataUpdateComif();

#endif