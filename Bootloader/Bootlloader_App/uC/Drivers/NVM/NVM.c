#include "NVM.h"

NVM_Block_Read_ST NVM_last_block;

NVM_Data_Config_ST NVM_Block = {
	
		/* Starting Address */	0x00,
		/* Block Size */ 8,
		/* StartUp Flag */ 1,
		/* NVM Header */	0xA1A1A1A1,
		{
			/* NVM ID */	0,
			/* NVM Length */	0,
		},
		{
			/* Flag App Varsion */0,
			/* Flag Res2 */	0,
			/* Flag Res3 */ 0,
			/* Flag Res4 */ 0,			
		},	
		/* NVM chksum */	0,
		/* NVM Data */ 0,	
};

Check_App_Header_ST Ck_Hdr[TOTAL_APP_HEADER]={

	{
		/* Starting address */App1_BaseAdd,
		/* Header */0,
		/* Program Starting address */0,
		/* Program End address */0,
		/* Flags */0,
		/* App1 - Cksum */0,
	},
	{
		/* Starting address */App2_BaseAdd,
		/* Header */0,
		/* Program Starting address */0,
		/* Program End address */0,
		/* Flags */0,
		/* App2 - Cksum */0,
	},
	
};