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

#include "ComIf.h"

/******************************************************/
/*           Global Variable Definitions              */
/******************************************************/

/* Channel Declarations */

/* -------------------------------------------------- */
/* For Boot Channel */
/* -------------------------------------------------- */

extern UBYTE Boot_Transmit_FUN(UWORD Length, void * Data);
extern void Boot_Error_Notification(ULONG Debug0, ULONG Debug1);

UBYTE ComIfChannelTxBuffer_Boot[255];

UBYTE ComIf_ShadowBuffer_Boot_Boot_Response[1];
UBYTE ComIf_ShadowBuffer_Boot_Nvm_Response[247];

ComIfTxMessageConfig ComIfTxMsgCfg_Boot[2] = {
	{
		/* Boot_Response */
		/* ID */        0xB5,
		/* Length */    1,
	#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* DynLength */ 0,
	#endif
		/* CHKLEN */    1,
		/* Tx Flags */  {
							0, // EnableAggregation
							0, // Force Transmit
							0, // PendingForTransmission
							0, // AggregatedInBuffer
							0  // PendingForConfirmation
						},
		/* Buffer */    ComIf_ShadowBuffer_Boot_Boot_Response,
		/* TxConfCbk */ NULL,
		/* TxCbk */     NULL
	},
	{
		/* Nvm_Response */
		/* ID */        0xD5,
		/* Length */    247,
	#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* DynLength */ 0,
	#endif
		/* CHKLEN */    1,
		/* Tx Flags */  {
							0, // EnableAggregation
							0, // Force Transmit
							0, // PendingForTransmission
							0, // AggregatedInBuffer
							0  // PendingForConfirmation
						},
		/* Buffer */    ComIf_ShadowBuffer_Boot_Nvm_Response,
		/* TxConfCbk */ NULL,
		/* TxCbk */     NULL
	},
};

extern void Boot_Req_Data_RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_Boot_Boot_Req_Data[22];
extern void NVM_BlockData_RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_Boot_NVM_BlockData[248];

ComIfRxMessageConfig ComIfRxMsgCfg_Boot[2] = {
	{
		/* Boot_Req_Data */
		/* ID */      0xB3,
		/* Length */  21,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_Boot_Boot_Req_Data,
		/* RxCbk */   &Boot_Req_Data_RxCbk
	},
	{
		/* NVM_BlockData */
		/* ID */      0xD3,
		/* Length */  247,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_Boot_NVM_BlockData,
		/* RxCbk */   &NVM_BlockData_RxCbk
	},
};


ComIf_ChannelConfigType ComIf_ChannelConfig[C_ComIfChannel_TOTAL] = 
{
    {	                                    /* For Boot ComIf Channel */
    	/* Transmit Function */             &Boot_Transmit_FUN,
    	/* Error Notification Function */   &Boot_Error_Notification,
#ifdef COMIF_RX_REQUEST_ENABLED
		/* Rx Request Function */           NULL,
		/* Rx Timeout Time */               0,
		/* Rx Timeout Time Counter */       0,
#endif
    	/* Transmit Buffer */               ComIfChannelTxBuffer_Boot,
    	/* Transmit Buffer Length */        255,
#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* Dynamic Max Data Length */       255,
#endif
    	/* Data Transfer Method */          COMIF_DATA_TXFR_METHOD_BYTES,
		/* Tx Message Config Pointer */     ComIfTxMsgCfg_Boot,
		/* Total Number of Tx Messages */   2,
		/* Rx Message Config Pointer */     ComIfRxMsgCfg_Boot,
		/* Total Number of Rx Messages */   2,
		/* Index of Receiving Message */    P_COMIF_INVALID_HANDLE,
		/* Length of Receiving Message */   0,
		/* Channel Specific Flags */
		{
			0,  // IsReceiving
			0,  // Delimit
			0,  // DLCVerified
			0,  // IsRxRequestEnabled
			0,  // IsTransmitting
			0,  // IsAggregationEnabled
			0,  // HasAggregatedMsgs
		},

#ifdef COMIF_TX_AGGREGATION_ENABLED
	#ifdef TX_AGGREGATION_ENABLED_BOOT
        /* Tx Aggregation Control */        &(ComIf_TxAggCtrl_Boot)
	#else
        /* Tx Aggregation Control */        NULL
	#endif
#endif
    },
};

/***************************************************/
/* Function Definitions                            */
/***************************************************/
/* Channel Specific Rx Indication Functions */

UBYTE ComIf_RxIndication_Boot(UBYTE DataByte)
{
	return ComIf_RxIndication(((UBYTE)C_ComIfChannel_Boot), DataByte);
}

