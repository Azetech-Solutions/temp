
#include "NVS_Driver.h"

/***************************************************************************************/
static NVS_Dataconfig_ST Nvs_Config_Block = {
	
		/*Start Add*/ 0x00,
		/*Block Size*/ 16,
		{	
			/* Reserved Flg */ 0,
			/*Block Sts_Flg*/ 1,
		},
		/*Nvs pattern*/0,
		{
			/*Block Index*/ 0,
			/*Block legnth*/ 0,
		},
		/*Block Checksum*/ 0,
		/*Block Data*/ 0
		
};
/***************************************************************************************/

void NVS_Init(void)
{
	NVS_Scan_Block();
}
/***************************************************************************************/

static void NVS_Scan_Block(void)
{
	uint8_t Blk_No;
	
	for(Blk_No = 0; Blk_No < NVS_TOTAL_BLOCKS; Blk_No++)
	{
		NVS_Dataconfig_ST *Current_Block = &Nvs_Config_Block;
		
		if(Current_Block->Sts_flg.Flag == TRUE)
		{
			NVS_Block_Read((NVS_BASE_ADDRESS|Current_Block->Start_Address),Blk_No);
		}
	}
}
/***************************************************************************************/

static void NVS_Block_Read(uint32_t Address,uint32_t Blk_no)
{
		NVS_Dataconfig_ST *NSRead = &Nvs_Config_Block;
		
		NSRead->NVS_ID_Len.NVS_ID = (uint16_t)FLASH_Read(Address);		
		NSRead->NVS_ID_Len.NVS_Length = (uint16_t)(FLASH_Read((Address))>>16);
		
		NSRead->Block_Checksum = FLASH_Read((Address+4U));
		
		NSRead->Data = (uint32_t*)(Address+8U);
		
}
/***************************************************************************************/
void NVSBlock_DataRead(uint8_t Block_Inx, uint32_t **Data)
{
	NVS_Dataconfig_ST *NSRead = &Nvs_Config_Block;
	
	if(IS_NVS_BlockValid(Block_Inx) == TRUE)
	{
			*Data = NSRead->Data;
	}
}	
/***************************************************************************************/
static uint8_t IS_NVS_BlockValid(uint8_t Block_Inx)
{
	uint8_t retval = 0;
	uint32_t Blk_add =0;
	
	NVS_Dataconfig_ST *Chk_Blk = &Nvs_Config_Block;
	
	Blk_add = (Chk_Blk->Start_Address | NVS_BASE_ADDRESS ); // to find the block start address
	
	if( Chk_Blk->Block_Checksum == FindBlock_DataSum(Blk_add+8U,(Chk_Blk->Block_Size-3U)) )
	{
		retval = 1;
	}
	
	return retval;
}
/***************************************************************************************/

uint32_t FindBlock_DataSum(uint32_t Add,uint8_t Size)
{
	uint8_t i=0;
	uint32_t sum=0;
	
	while(i<Size)
	{
		uint32_t checkadd = FLASH_Read(Add);
		if( checkadd!= 0xFFFFFFFFU && checkadd != 0x00000000U)
		{
			sum+= checkadd; //FLASH_Read(Add);
		}
		Add+=4U;
		i++;
	}
	
	return (((~sum)+1)& 0xFFFFFFFF);
}
/***************************************************************************************/
