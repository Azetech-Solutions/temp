/******************************************************************
                A Z E T E C H    S O L U T I O N S                 
-------------------------------------------------------------------
        T O O L   G E N E R A T E D   S O U R C E   C O D E        
                    D O   N O T   M O D I F Y                      
-------------------------------------------------------------------
 This file is generated with the Azetech copyrighted software tool 
 No modification should be done in this file without a written     
 consent from Azetech Solutions. Incase of any such instances,     
 Azetech Solutions will not be liable to any damages it cause.     
-------------------------------------------------------------------
 Any Distribution, Alteration, Removal, Disassemble, Decompile or  
 or Reverse Engineer the given software, without written consent   
 from Azetech Solutions by the Licensee or third parties were not  
 allowed. Such instance is considered as a breach and the Licensee 
 is the sole responsible and liable to any damages it cause.       
******************************************************************/

#ifndef __COMIF_CONFIG_H__
#define __COMIF_CONFIG_H__

#include "Platform_Types.h"
#include "ComIf_Config_Elements.h"

/*************************************************/
/* Functional Switches and Parameter Definitions */
/*************************************************/

/* Invalid Index handle */
#define P_COMIF_INVALID_HANDLE                255u

/* ComIf Input Method */
#define S_COMIF_INPUT_METHOD                  COMIF_INPUT_METHOD_POLLING

#define COMIF_MAX_SUPPORTED_DLC               255 // 255 Bytes

#define COMIF_MAX_SUPPORTED_CHKLEN            1   // 1 Byte

#define COMIF_TX_MAIN_FUNCTION_PERIOD         10

#define COMIF_RX_MAIN_FUNCTION_PERIOD         10

/*************************************************/
/*               Macro Definitions               */
/*************************************************/

#if COMIF_MAX_SUPPORTED_DLC < 255
#error "The channel Boot has more data length in the dynamic section than the supported DLC"
#endif

/* Transmit Message constants for the channel : Boot */
#define P_COMIF_TXBUFFER_SIZE_BOOT                    256u

/* Constants for the Tx message Boot_Response on Boot channel */

#define ComIf_GetIndex_Boot_Boot_Response()                   (0u)
#define ComIf_GetLength_Boot_Boot_Response()                  (1u)
#define ComIf_GetShadowBuffer_Boot_Boot_Response()            ((UBYTE *)ComIf_ShadowBuffer_Boot_Boot_Response)
#define ComIf_Transmit_Boot_Boot_Response(x, y)               ComIf_Transmit(C_ComIfChannel_Boot, 0, ((void *)x), y)
#define ComIf_ForceTransmit_Boot_Boot_Response(x, y)          do{ComIfTxMsgCfg_Boot[0].TxFlags.ForceTransmit = TRUE; ComIf_Transmit(C_ComIfChannel_Boot, 0, ((void *)x), y); } while(0)
#define ComIf_UpdateTxShadowBuffer_Boot_Boot_Response(x, y)   ComIf_UpdateTxShadowBuffer(C_ComIfChannel_Boot, 0, ((void *)x), y)
#define ComIf_TransmitFromBuffer_Boot_Boot_Response()         ComIf_Transmit_Boot_Boot_Response(ComIf_ShadowBuffer_Boot_Boot_Response, 1)
#define ComIf_ForceTransmitFromBuffer_Boot_Boot_Response()    ComIf_ForceTransmit_Boot_Boot_Response(ComIf_ShadowBuffer_Boot_Boot_Response, 1)

/* Debug Measurement Variables for Boot_Response on Boot */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_Boot[0].TxFlags.PendingForTransmission */
/* MODELNAME=ComIfTxMsgCfg_Boot_Boot_Response_PendingForTransmission */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_Boot[0].TxFlags.PendingForConfirmation */
/* MODELNAME=ComIfTxMsgCfg_Boot_Boot_Response_PendingForConfirmation */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_Boot[0].TxFlags.AggregatedInBuffer */
/* MODELNAME=ComIfTxMsgCfg_Boot_Boot_Response_AggregatedInBuffer */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */


/* Receive Message constants for the channel : Boot */

/* Constants for the Rx message Boot_Req_Data on Boot channel */

#define ComIf_GetIndex_Boot_Boot_Req_Data()                   (0u)
#define ComIf_GetLength_Boot_Boot_Req_Data()                  (21u)
#define ComIf_GetBuffer_Boot_Boot_Req_Data()                  ((UBYTE *)ComIf_RxMessageBuffer_Boot_Boot_Req_Data)
#define ComIf_GetRxFlags_Boot_Boot_Req_Data()                 (ComIfRxMsgCfg_Boot[0].RxFlags)
#define ComIf_IsNewMessageReceived_Boot_Boot_Req_Data()       ((ComIfRxMsgCfg_Boot[0].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_Boot[0].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_Boot_Boot_Req_Data() (ComIfRxMsgCfg_Boot[0].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_Boot_Boot_Req_Data()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_Boot[0].RxFlags))



#define COMIF_DYNAMIC_DATA_LENGTH_ENABLED

/*************************************************/
/*               Type Definitions                */
/*************************************************/

typedef struct __ComIfTxFlags
{
    /* This structure must not exceed 8 bytes */
    
    /* Control Bits */
	UBYTE EnableAggregation      : 1; // If set, then the message will be aggregated instead of transmitting
	UBYTE ForceTransmit          : 1; // If set, then the aggregation enabled messages will be sent directly
	
	/* Status Bits */
	UBYTE PendingForTransmission : 1; // If set, then the message will be sent in next aggregation cycle
	UBYTE AggregatedInBuffer     : 1; // If set, then the message has been copied to the channel data buffer
	UBYTE PendingForConfirmation : 1; // If set, then the message will receive confirmation after the aggregation transmit cycle is completed
	
}ComIfTxFlags;

typedef struct __ComIfTxMessageConfig
{
	UBYTE ID;
	UBYTE Length;
#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
	UBYTE DynLength;
#endif
	UBYTE ChecksumLength;
	ComIfTxFlags TxFlags;
	UBYTE * ShadowBuffer;
	void (*TxConfCallback)(void);
	UBYTE (*TxCallback)(UBYTE *, UBYTE *);
}ComIfTxMessageConfig;

typedef struct __ComIfRxFlags
{
    /* This structure must not exceed 8 bytes */
    
	/* Status Bits */
	UBYTE ReceptionStarted   : 1; // If set, then the message has been started receiving
	UBYTE NewMessageReceived : 1; // If set, then the message has been received completely and waiting for the RxCbk to be called
	UBYTE ErrorInReception   : 1; // If set, then the message has been received, but there is an error in reception
	UBYTE RxRequest          : 1; // If set, then the message is requested by the application
	UBYTE RxRequestPlaced    : 1; // If set, then the message reception request has been placed to the underlying module
	
}ComIfRxFlags;

typedef struct __ComIfRxMessageConfig
{
	UBYTE ID;
	UBYTE Length;
	UBYTE ChecksumLength;
	ComIfRxFlags RxFlags;
	UBYTE CurRxngIdx;
	UBYTE * MessageBuffer;
	void (*RxCallback)(UBYTE, UBYTE*);
}ComIfRxMessageConfig;

typedef enum __ComIf_ChannelType
{
	C_ComIfChannel_Boot = 0,

	C_ComIfChannel_TOTAL = 1
}ComIf_ChannelType;

typedef UBYTE (*ComIf_ChannelTransmitType)(UWORD, void*);

typedef void (*ComIf_ErrorNotificationType)(ULONG, ULONG);

typedef UBYTE (*ComIf_ChannelRxRequestType)(UBYTE);

typedef struct __ComIfChannelFlags
{
	/* Reception related flag */
	UBYTE IsReceiving          : 1;
	UBYTE Delimit              : 1;
	UBYTE DLCVerified          : 1;
	UBYTE IsRxRequestEnabled   : 1;
	
	UBYTE IsTransmitting       : 1;
	UBYTE IsAggregationEnabled : 1;
	UBYTE HasAggregatedMsgs    : 1;
	
}ComIfChannelFlags;

#ifdef COMIF_TX_AGGREGATION_ENABLED
typedef struct __ComIf_TxAggCtrl_t
{
	UWORD TxCycle;
	UWORD TxCycleCounter;

	UWORD BufferLimit;
	UWORD CurrentBufferLength;
	
}ComIf_TxAggCtrl_t;
#endif

typedef struct __ComIf_ChannelConfigType
{
	ComIf_ChannelTransmitType Transmit;
	ComIf_ErrorNotificationType ErrorCallback;

#ifdef COMIF_RX_REQUEST_ENABLED
	ComIf_ChannelRxRequestType RequestReception;
	UWORD RxRequestTimeout;
	UWORD RxRequestTimeoutCounter;
#endif

	UBYTE * TxBuffer;
	UWORD TxBufferLength;
	
#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
	UBYTE DynamicMaxDataLength;
#endif
	UBYTE DataTxfrMethod;
	
	ComIfTxMessageConfig * TxMessages;
	UBYTE TotalTxMessages;
	
	ComIfRxMessageConfig * RxMessages;
	UBYTE TotalRxMessages;

	UBYTE RxMsgIndex;
	UBYTE RxMsgLength;
	ComIfChannelFlags ChannelFlags;

#ifdef COMIF_TX_AGGREGATION_ENABLED
	ComIf_TxAggCtrl_t * TxAggCtrl;
#endif
	
}ComIf_ChannelConfigType;

/*************************************************/
/*               Global Variables                */
/*************************************************/

extern ComIf_ChannelConfigType ComIf_ChannelConfig[];

/* Channel Buffers and Configuration */

/* For the Channel: Boot */
extern ComIfTxMessageConfig ComIfTxMsgCfg_Boot[];
extern UBYTE ComIfChannelTxBuffer_Boot[];
extern UBYTE ComIf_ShadowBuffer_Boot_Boot_Response[];
extern ComIfRxMessageConfig ComIfRxMsgCfg_Boot[];
extern UBYTE ComIf_RxMessageBuffer_Boot_Boot_Req_Data[];

/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

static inline void ComIf_SetMessageProcessed(ComIfRxFlags * RxFlags)
{
	if(RxFlags != NULL)
	{
		RxFlags->NewMessageReceived = FALSE;
#ifdef COMIF_RX_REQUEST_ENABLED
		RxFlags->RxRequest = FALSE;
		RxFlags->RxRequestPlaced = FALSE;
#endif
	}
}

/*************************************************/
/*          Extern Function Declarations         */
/*************************************************/

extern UBYTE ComIf_Rx_Request(ComIf_ChannelType ChannelIndex, UBYTE MsgIndex);
extern UBYTE ComIf_Rx_CancelRequest(ComIf_ChannelType ChannelIndex, UBYTE MsgIndex);

/* Channel Specific Rx Indication Functions */
extern UBYTE ComIf_RxIndication_Boot(char * DataString, UWORD Length);

#endif /* __COMIF_CONFIG_H__ */

