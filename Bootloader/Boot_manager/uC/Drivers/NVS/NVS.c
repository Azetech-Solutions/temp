
#include "NVS.h"

NVS_DATA_CONFIG_ST Nvs_Block_data[NVS_TOTAL_BLOCKS]= {
	/* Admin Data */
	{
		/*Start Add*/ 0x00, 
		/*Block Size*/ 16,		// 16(in word)x32bit
		{	
			/* Reserved Flg */ 0,
			/*Block Sts_Flg*/ 1,
		},
		{
			/*Block Index*/ 0,
			/*Block legnth*/ 0,
		},
		/*Block Checksum*/ 0,
		/*Block Data*/ 0
	},
	/* Block One BootLoader Data */
	{
		/*Start Add*/ 0x40, 
		/*Block Size*/ 36,   	// 36(in word)x32bit
		{	
			/* Reserved Flg */ 0,
			/*Block Sts_Flg*/ 1,
		},
		{
			/*Block Index*/ 1,
			/*Block legnth*/ 0,
		},
		/*Block Checksum*/ 0,
		/*Block Data*/ 0
	},
//	/* Block two App1 Data */
//	{
//		/*Start Add*/ 0xD0, 
//		/*Block Size*/ 36,		// 36(in word)x32bit
//		{	
//			/* Reserved Flg */ 0,
//			/*Block Sts_Flg*/ 1,
//		},
//		{
//			/*Block Index*/ 2,
//			/*Block legnth*/ 0,
//		},
//		/*Block Checksum*/ 0,
//		/*Block Data*/ 0
//	},
//	
//	{
//		/*Start Add*/ 0x0160, 
//		/*Block Size*/ 36,		// 36(in word)x32bit
//		{	
//			/* Reserved Flg */ 0,
//			/*Block Sts_Flg*/ 1,
//		},
//		{
//			/*Block Index*/ 3,
//			/*Block legnth*/ 0,
//		},
//		/*Block Checksum*/ 0,
//		/*Block Data*/ 0
//	},
//	
//	{
//		/*Start Add*/ 0x01F0,
//		/*Block Size*/ 40,		// 40(in word)x32bit
//		{	
//			/* Reserved Flg */ 0,
//			/*Block Sts_Flg*/ 1,
//		},
//		{
//			/*Block Index*/ 4,
//			/*Block legnth*/ 0,
//		},
//		/*Block Checksum*/ 0,
//		/*Block Data*/ 0
//	}
};