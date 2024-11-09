#include "NVM_Driver.h"

uint8_t NVM_Sec2_EraseVerify_Flg = FALSE;

volatile uint32_t Last_NVMBlock_Add = 0x08011FE0;  //this variable is used to find the last valid NVM address initially it has the nvm (start address - 0x20)
volatile uint32_t FindNVMApplicationAdd;

/***************************************************************************************/
NVM_Data_Config_ST NVM_Block = {
	
		/* Starting Address */	0x00,
		/* Block Size */ 8,
		{
			/* StartUp Flag */ 1,
			/* ReOrgTrigger Flag */ 0,
			/* Res */ 0,
		},
		/* NVM Header */	0xC2C2C2C2,
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

/***************************************************************************************/
void NVM_Init(void)
{	
	NVM_Scan_Block();
}
/***************************************************************************************/
void NVM_Scan_Block(void)
{	
		NVM_Data_Config_ST *NVMBlkRead = &NVM_Block;
		
		if(NVMBlkRead->NVM_CtrlFlg.StartupFlg == TRUE) // not set false
		{
			NVM_Block_Read_FUN();  // NVM Block data Read function
		}	
}	
/***************************************************************************************/

void NVM_Block_Read_FUN()
{
		NVM_Data_Config_ST *nmread = &NVM_Block;
		uint32_t Current_Address=0;
		
		if(Last_NVMBlock_Add == 0x08011FE0)
		{ Current_Address = NVM_BASE_ADDRESS; }
		else { Current_Address = Last_NVMBlock_Add; } // last block of NVM data is Read 
		
		if(Current_Address != 0U)
		{
			nmread->NVM_Header = FLASH_Read(Current_Address);	// to read the last block  nvm Header/ Pattern
			
			nmread->NVM_IdLen.NVM_ID = (uint16_t)(FLASH_Read(Current_Address+4U)); // to read the last block  nvm Id
			nmread->NVM_IdLen.NVM_Length = (uint16_t)((FLASH_Read(Current_Address+4U)) >> 16); // to read the last block  nvm length
			
			nmread->NVM_Flag.NVM_Version = (uint8_t)(FLASH_Read(Current_Address+8U)); // to read the last block  nvm verison
			
			nmread->NVM_ChkSum = FLASH_Read(Current_Address+12U); // to read the last block  nvm checksum
			
			Current_Address +=16U;  // to read the last block  nvm data's
			for(uint8_t i=0;i<NVM_DATA_BLOCK_SIZE;i++)
			{
				nmread->NVM_Data[i] = FLASH_Read(Current_Address);
				Current_Address+=4U;
			}	
		}	
}
/***************************************************************************************/
//This Function to Find the Last block Address
void Chk_NVMTotal_Block()
{
	uint32_t SAdd = NVM_SECTOR_ONE_START_ADDRESS;
	
	while(SAdd < NVM_END_ADDRESS)
	{
		if(*(uint32_t*)(SAdd) == 0xC2C2C2C2)
		{	
			Last_NVMBlock_Add = SAdd;  // to get the last valid nvm block 
		}
		
		SAdd+=4U;
	}
}
/***************************************************************************************/
uint8_t NVM_Block_Write(void)
{
	uint8_t retval=0;
	/* Header->len->Id->Flag->chksum->data*/
		NVM_Data_Config_ST *upDtBlk = &NVM_Block;	
	
		/* This function is used to Update new NVM block  Data's */
		if( NVM_Multi_Word_write((Last_NVMBlock_Add + (NVM_ONE_BLOCK_SIZE*sizeof(uint32_t))),&NVM_Block.NVM_Header,upDtBlk->NVM_Block_Size) )
		{
			retval = 1;
		}
	return retval;
}
/***************************************************************************************/
uint8_t NVM_Multi_Word_write(uint32_t Address,uint32_t *Data,uint32_t Size)
{
	uint8_t retval = 0;
	uint8_t i=0;
	
	__disable_irq();
	FLASH_Unlock();
	FLASH_ErrorChk();
	
	do
	{
		FLASH_Write(Address,(*Data++));
		Address +=4U;
		Size--;
	}while(Size!=0);
	
	FLASH_ErrorChk();
	FLASH_Lock();
	__enable_irq();
	
	return retval = 1;
}

/***************************************************************************************/
/* This function update the New NVM Block */
uint8_t Update_Nvm_Block()
{
	NVM_Data_Config_ST *updt_nvm = &NVM_Block;
	uint8_t retval =0;
	
	NVM_VersionUpdate(); // update the Nvm version

	ChkNVMApplication(); // find the valid applicaiton 
		
	Last_NVMBlock_Add = NVM_AddUpdate(Last_NVMBlock_Add);  // Find the store nvm block address 
		
		/* Write the updated NVM Block in flash memory */
	if(NVM_Block_Write())
	{
		if(NVM_Sec2_EraseVerify_Flg == TRUE)
		{
			/* Erase the Sec2 */
			if(Flash_SingleSec_Erase(NVM_SECTOR_TWO,BANK_2)) { retval = 1; }
			NVM_Sec2_EraseVerify_Flg = FALSE;
			return retval;
		}
		retval = 1;
	}

	return retval;
}

/***************************************************************************************/

uint8_t NVM_ReOrg()
{
	NVM_Data_Config_ST *Reorg = &NVM_Block;
	uint8_t retval =0;
	
	if(Flash_SingleSec_Erase(NVM_SECTOR_ONE,BANK_2))
	{	
		if( VerifyFlashErase(NVM_SECTOR_ONE_START_ADDRESS,NVM_SECTOR_ONE_END_ADDRESS) )
		{
			Last_NVMBlock_Add = 0x08011FE0; // This address is nvm sec 1 start address - 20U for write the NVM data on sec 1
			NVM_Sec2_EraseVerify_Flg = TRUE;
			retval = 1;
		}
	}
	return retval;
}

/***************************************************************************************/

uint32_t NVM_AddUpdate(uint32_t Blk_add)
{
	NVM_Data_Config_ST *updt_nvm = &NVM_Block;

		/* NVM Address update */
		if( (Blk_add >= NVM_SECTOR_ONE_START_ADDRESS) && (Blk_add < (NVM_SECTOR_TWO_START_ADDRESS - 0x30U)) )
		{
			Blk_add = Last_NVMBlock_Add;
		}
		else if((Blk_add > (NVM_SECTOR_TWO_START_ADDRESS - 0x30U)) && (Blk_add <= NVM_SECTOR_TWO_START_ADDRESS) )
		{
			Last_NVMBlock_Add = 0x08013FE0;	// This address is nvm sec 2 start address - 20U for write the NVM data on sec 2
		}
		else if( (Blk_add >=NVM_SECTOR_TWO_START_ADDRESS) && (Blk_add <(APP_2_BASE_ADDRESS - 0x70U)))
		{
			Blk_add = Last_NVMBlock_Add;
		}
		else if((Blk_add >= (APP_2_BASE_ADDRESS - 0x70U)) && (Blk_add <= APP_2_BASE_ADDRESS) ) //end NVM address
		{				
				if(NVM_ReOrg()) { Blk_add = Last_NVMBlock_Add = 0x08011FE0; }								
		}
			
		return Blk_add;
}
/***************************************************************************************/

void NVM_VersionUpdate()
{
	NVM_Data_Config_ST *VerUpt = &NVM_Block;
	
	/* APP version and ID Update */	
	if( VerUpt->NVM_Flag.NVM_Version < 255 )
	{
		VerUpt->NVM_Flag.NVM_Version = VerUpt->NVM_Flag.NVM_Version +1U;
		VerUpt->NVM_IdLen.NVM_ID = VerUpt->NVM_IdLen.NVM_ID;
	}
	else
	{
		VerUpt->NVM_Flag.NVM_Version = 0U;
		if( VerUpt->NVM_IdLen.NVM_ID < 255) 
		{ VerUpt->NVM_IdLen.NVM_ID = VerUpt->NVM_IdLen.NVM_ID + 1U; }
		else { VerUpt->NVM_IdLen.NVM_ID = 0U; }					
	}
}

/***************************************************************************************/

void ChkNVMApplication()
{
	NVM_Data_Config_ST *UptApp = &NVM_Block;
	
		/* final working APP update */
	if(FindNVMApplicationAdd >= APP_1_BASE_ADDRESS && FindNVMApplicationAdd < APP_1_END_ADDRESS)
	{
		UptApp->NVM_Data[0] = 0xAAAA1111;
	}
	else if(FindNVMApplicationAdd >= APP_2_BASE_ADDRESS && FindNVMApplicationAdd < APP_2_END_ADDRESS)
	{
		UptApp->NVM_Data[0] = 0xAAAA2222;
	}
	
	/* Length Update */
	UptApp->NVM_IdLen.NVM_Length = sizeof(UptApp->NVM_Data[0]);
	
	/* cksum update */
	UptApp->NVM_ChkSum = ((~UptApp->NVM_Data[0])+1);
}

/***************************************************************************************/
