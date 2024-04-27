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
			/* Flag NVM Varsion */0,
			/* Flag Res2 */	0,
			/* Flag Res3 */ 0,
			/* Flag Res4 */ 0,			
		},	
		/* NVM chksum */	0,
		/* NVM Data */ 0,	
};