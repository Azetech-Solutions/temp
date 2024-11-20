
#ifndef __FLOWCONTROL_H__
#define __FLOWCONTROL_H__

#include "Ports_init.h"
#include "Addresses_Handling.h"

#define FC_DATAMAXLENGTH_TX												 	 (63U)  // this len is max data transmit to tool
#define FC_DATAMAXLENGHT_RX													 (1024U)

#define FC_SINGLEFRAMETYPE                     		 	 (0U)
#define FC_FIRSTFRAMETYPE                     			 (1U)
#define FC_CONSECUTIVEFRAMETYPE                      (2U)
#define FC_FLOWCONTROLFRAMETYPE                      (3U)

/************************************************************/
#define FC_SENDSTATUS																 (0u)
#define	FC_WAITSTATUS														     (1U)
#define	FC_ABORTSTATUS												     	 (2U)
#define	FC_REPEATSTATUS													     (3U)
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
		uint8_t FCTiming :4;
		uint8_t FCAck :4;		
		// 252 bytes
		uint8_t FCData[252];
	};
	uint8_t Bytes[255];
	
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
		uint8_t FCTiming :4;
		uint8_t FCAck :4;		
		// 240 bytes
		uint8_t FCData[240];
	};
	uint8_t Bytes[243];
	
}FC_RxData_ST;


typedef struct _FC_ControlFlags
{
	uint8_t FcRxFlag : 1; //both
	uint8_t FCInitialFlag : 1; //tx
	uint8_t FCSingleframeFlag : 1; //tx
	uint8_t FCFirstframeFlag  : 1; //tx
	uint8_t FCConsecutiveframeFlag : 1; //tx
	uint8_t FC_TxDataUpdateFlag : 1; //both
	uint8_t FC_CompleteFlag : 1; //both
}FlowControlFlags_ST;

typedef struct _FC_Control
{
	FlowControlFlags_ST FCFlag;
	uint16_t FCMAXlength; // to get the max len of tx & rx
	uint16_t FCReceivedLength;  // to store the totally received len
	uint16_t FCBalanceLength; // max len - received len
	uint16_t FCUpdateComifLength;  // update comif len
	uint32_t FCPreviousAddress; // to store the start add
	uint32_t FCNextAddress; // to move next address
	uint8_t FCConsecutiveIndex;  

}FlowControl_ST;

/*Variable*/
extern FC_RxData_ST FC_RxData;
extern FlowControl_ST FCManage;

extern volatile uint16_t fcrxLen;
extern void FC_RxCbk(UBYTE Length, UBYTE *Data); // comif function

static inline uint16_t FindDataLengthInFlash(uint32_t startAddress, uint32_t sectorSize);
static inline void FCFindFrameType(FC_TxData_ST *FType,uint16_t Len);
static uint16_t FC_DataCopy(FC_TxData_ST *Tx, uint32_t SAdd, uint16_t Len);
static inline uint8_t FCTxDataUpdateComif(FC_TxData_ST *tx, uint16_t ComifDataLen);

extern uint8_t FCData_Transmit();

extern uint8_t FCData_Receive();

extern uint8_t received_DataCopy(uint8_t pos, FC_RxData_ST *rx);
extern uint8_t Read_AppVersion(uint32_t Add);

/* To find the Nvs Block Next start address */
extern uint8_t find_NvsNextblockAddress(void);
#endif