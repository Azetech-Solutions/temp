#include "NVM_Driver.h"
#include "Flowcontrol.h"

//Flg
uint8_t NVM_Sec2_EraseVerify_Flg = FALSE;

volatile uint32_t Last_NVMBlock_Add = 0x08011FE0;  //this variable is used to find the last valid NVM address

/***************************************************************************************/
NVM_Data_Config_ST NVM_Block = {
	
		/* Starting Address */	0x00,
		/* Block Size */ 8,
		{
			/* StartUp Flag */ 1,
			/* NVMTrg Flag */ 0,
			/* IsGetAllData Flag */ 0,
			/* IsReorgTrg Flag */ 0,
			/* IsClearTrg Flag */ 0,
			/* IsUpdateTrg Flag */ 0,
			/* IsUpdateAllTrg Flag */ 0,
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


Check_App_Header_ST Ck_Hdr[TOTAL_VERSION_HEADER]={

//	{
//		/* Starting address */BOOTLOADER_BASE_ADDRESS,
//		/* Header */0,
//		/* Program Starting address */0,
//		/* Program End address */0,
//		/* Bootloader - Cksum  */0,
//		/* MajorVersion*/0,
//		/* MinorVersion*/0,
//		/* BuildVersion*/0,
//		/* ReleaseType*/0,
//	},
	{
		/* Starting address */APP_1_BASE_ADDRESS,
		/* Header */0,
		/* Program Starting address */0,
		/* Program End address */0,
		/* App1 - Cksum  */0,
		/* MajorVersion*/0,
		/* MinorVersion*/0,
		/* BuildVersion*/0,
		/* ReleaseType*/0,
	},
	{
		/* Starting address */APP_2_BASE_ADDRESS,
		/* Header */0,
		/* Program Starting address */0,
		/* Program End address */0,
		/* App2 - Cksum */0,
		/* MajorVersion*/0,
		/* MinorVersion*/0,
		/* BuildVersion*/0,
		/* ReleaseType*/0,
	},
};


/***************************************************************************************/

void NVM_Init(void)
{	
	NVM_Scan_Block();
}
/***************************************************************************************/
static void NVM_Scan_Block(void)
{	
		NVM_Data_Config_ST *NVMBlkRead = &NVM_Block;
		
		if(NVMBlkRead->NVM_CtrlFlg.StartupFlg == TRUE)
		{				
			NVM_Block_Read_FUN(&NVM_Block,Last_NVMBlock_Add);  // NVM Block data Read function
		}	
}
/***************************************************************************************/
/* This function is read the Headers of the APP1 & APP2 */
void Read_Apps_Header(void)
{
	uint8_t i;
	
	for(i=0;i<TOTAL_VERSION_HEADER;i++)
	{
		Check_App_Header_ST *Ck = &Ck_Hdr[i];
	
		Ck->Ck_Header = FLASH_Read(Ck->Header_start_Add);

		Ck->Ck_SAddress = FLASH_Read((Ck->Header_start_Add+4U));

		Ck->Ck_EAddress =	FLASH_Read((Ck->Header_start_Add+8U));

		Ck->Ck_cksum = FLASH_Read((Ck->Header_start_Add+12U));
		
		// read versions
		Ck->Ck_MajorVersion = FLASH_Read((Ck->Header_start_Add+16U));
		Ck->Ck_MinorVersion = FLASH_Read((Ck->Header_start_Add+20U));
		Ck->Ck_BuildVersion = FLASH_Read((Ck->Header_start_Add+24U));
		Ck->Ck_ReleaseType = FLASH_Read((Ck->Header_start_Add+28U));
	}
}
/***************************************************************************************/

uint32_t ChkAppHeader_ChkSum(uint32_t Add)
{
		uint8_t chk_Hdr;
		if(Add >= APP_1_BASE_ADDRESS && Add < APP_1_END_ADDRESS)
		{
			chk_Hdr = HEADER_APP_1;
			Read_Apps_Header();  // after fully write the app image that header value and cksum value are read it.
		}
		else if(Add >= APP_2_BASE_ADDRESS && Add < APP_2_END_ADDRESS)
		{
			chk_Hdr = HEADER_APP_2;
			Read_Apps_Header();
		}					
		Check_App_Header_ST *Ck = &Ck_Hdr[chk_Hdr];
		
		return Ck->Ck_cksum; 
}
/***************************************************************************************/

static void NVM_Block_Read_FUN(NVM_Data_Config_ST *Rblk,uint32_t Current_Address)
{
		Rblk->NVM_Header = FLASH_Read(Current_Address);	// to read the last block  nvm Header/ Pattern
		
		Rblk->NVM_IdLen.NVM_ID = (uint16_t)(FLASH_Read(Current_Address+4U)); // to read the last block  nvm Id
		Rblk->NVM_IdLen.NVM_Length = (uint16_t)((FLASH_Read(Current_Address+4U)) >> 16); // to read the last block  nvm length
		
		Rblk->NVM_Flag.NVM_Version = (uint8_t)(FLASH_Read(Current_Address+8U)); // to read the last block  nvm verison
		
		Rblk->NVM_ChkSum = FLASH_Read(Current_Address+12U); // to read the last block  nvm checksum
	
	// to read the last block  nvm data's
		Rblk->NVM_Data.NVMData0 = FLASH_Read(Current_Address+16U);
		Rblk->NVM_Data.NVMData1 = FLASH_Read(Current_Address+20U);
		Rblk->NVM_Data.NVMData2 = FLASH_Read(Current_Address+24U);
		Rblk->NVM_Data.NVMData3 = FLASH_Read(Current_Address+28U);	
	
}
/***************************************************************************************/
/*
*  This Function to Find the Total NVM Block and find the last block Address
*/
void Chk_NVMLast_BlockAdd(void)
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
static uint8_t NVM_Block_Write(void)
{
	uint8_t retval=0;
	/* Header->len->Id->Flag->chksum->data*/
		NVM_Data_Config_ST *upDtBlk = &NVM_Block;	
	
		/* This function is used to Update new NVM block  Data's */
		if( FLASH_Multi_Word_write((Last_NVMBlock_Add + (NVM_ONE_BLOCK_SIZE*sizeof(uint32_t))),&NVM_Block.NVM_Header,upDtBlk->NVM_Block_Size) )
		{
			retval = 1;
		}
	return retval;
}
/***************************************************************************************/

uint32_t App_Image_Chksum_calculation(uint32_t Add)  // this api not used anywhere
{
	uint32_t retval=0,ck= 0;
	
	
	while(*(uint32_t*)(Add) != 0xFFFFFFFF)
	{
		ck += FLASH_Read(Add);
		Add += 4U;
	}
	
	return (((~ck)+1)&0xFFFFFFFF);
}
/***************************************************************************************/
/* This function update the New NVM Block */
uint8_t Update_Nvm_Block(uint32_t Add)
{
	NVM_Data_Config_ST *updt_nvm = &NVM_Block;
	uint8_t retval =0;
	
	NVM_VersionUpdate(); // update the Nvm version

	ChkNVMApplication(Add); // find the valid applicaiton 
		
	Last_NVMBlock_Add = NVM_AddUpdate(Last_NVMBlock_Add);  // Find the store nvm block address 
		
	/* Write the updated NVM Block in flash memory */
	
	if(updt_nvm->NVM_CtrlFlg.IsNVMTrg == FALSE)
	{
		if(NVM_Block_Write())
		{
			if(NVM_Sec2_EraseVerify_Flg == TRUE)
			{
				/* Erase the Sec2 */
				if(FLASH_Erase_NoofSectors(NVM_SECTOR_TWO, BANK_2, 1)) 
				{ 
					if( VerifyFlashErase(NVM_SECTOR_TWO_START_ADDRESS,NVM_SECTOR_TWO_END_ADDRESS) ) 
					{ 
						NVM_Sec2_EraseVerify_Flg = FALSE;
						retval = 1; 
					} 
				}
				return retval;
			}
			retval = 1;
		}
	}
	
	return retval;
}

/***************************************************************************************/

uint8_t NVM_ReOrg()
{
	NVM_Data_Config_ST *Reorg = &NVM_Block;
	uint8_t retval =0;
	// erase nvm sec 1
	if(FLASH_Erase_NoofSectors(NVM_SECTOR_ONE, BANK_2, 1))
	{	
		if( VerifyFlashErase(NVM_SECTOR_ONE_START_ADDRESS,NVM_SECTOR_ONE_END_ADDRESS) )
		{
			Last_NVMBlock_Add = 0x08011FE0; // This address is nvm sec 1 start address - 20U for write the NVM data on sec 1
			NVM_Sec2_EraseVerify_Flg = TRUE;
			retval = 1;
		}
	}
	
	if(Reorg->NVM_CtrlFlg.IsNVMTrg == TRUE)
	{
		if(Reorg->NVM_CtrlFlg.IsReorgTrg == TRUE)  // this statement is executed after triggering a tool
		{
			retval = 0;
			if(NVM_Block_Write())
			{
				if(NVM_Sec2_EraseVerify_Flg == TRUE)
				{
					/* Erase the nvm Sec2 */
					if(FLASH_Erase_NoofSectors(NVM_SECTOR_TWO, BANK_2, 1)) 
					{ 
						if( VerifyFlashErase(NVM_SECTOR_TWO_START_ADDRESS,NVM_SECTOR_TWO_END_ADDRESS) ) 
						{
							Reorg->NVM_CtrlFlg.IsReorgTrg = FALSE;
							Reorg->NVM_CtrlFlg.IsNVMTrg = FALSE;
							NVM_Sec2_EraseVerify_Flg = FALSE;
							retval = 1; 
						} 
					}		
				}		
			}
		}
	}
	return retval;
}

/***************************************************************************************/

uint8_t NVMToolClear()  // set the deafault nvm values
{
	NVM_Data_Config_ST *toolClear = &NVM_Block;
	uint8_t retval = 0;
	
	if(toolClear->NVM_CtrlFlg.IsNVMTrg == TRUE)
	{
		if( NVM_ReOrg() )
		{
			if(toolClear->NVM_CtrlFlg.IsClearTrg == TRUE)
			{
				// update Nvm function caling
				NVM_VersionUpdate(); //set the default Nvm version
				ChkNVMApplication(0); //set the default Nvm Application
				
				if(NVM_Block_Write())
				{
					if(NVM_Sec2_EraseVerify_Flg == TRUE)
					{
						/* Erase the Sec2 */
						if(FLASH_Erase_NoofSectors(NVM_SECTOR_TWO, BANK_2 ,1)) 
						{
							if( VerifyFlashErase(NVM_SECTOR_TWO_START_ADDRESS,NVM_SECTOR_TWO_END_ADDRESS) ) { retval = 1; } 
						}
						NVM_Sec2_EraseVerify_Flg = FALSE;
						toolClear->NVM_CtrlFlg.IsClearTrg = FALSE;
						toolClear->NVM_CtrlFlg.IsNVMTrg = FALSE;
					}				
				}
			}
		}
	}
	return retval;
}
/***************************************************************************************/

static uint32_t NVM_AddUpdate(uint32_t Blk_add)
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

static void NVM_VersionUpdate()
{
	 NVM_Data_Config_ST *VerUpt = &NVM_Block;
	
		if(VerUpt->NVM_CtrlFlg.IsNVMTrg == FALSE)
		{
			/* APP version and ID Update */	
			if( VerUpt->NVM_Flag.NVM_Version < 255 )
			{
				VerUpt->NVM_Flag.NVM_Version = VerUpt->NVM_Flag.NVM_Version +1U;
				VerUpt->NVM_IdLen.NVM_ID = VerUpt->NVM_IdLen.NVM_ID;
			}
			else
			{
				VerUpt->NVM_Flag.NVM_Version = 0U;
				if( VerUpt->NVM_IdLen.NVM_ID < 255) { VerUpt->NVM_IdLen.NVM_ID = VerUpt->NVM_IdLen.NVM_ID + 1U; }
				else { VerUpt->NVM_IdLen.NVM_ID = 0U; }					
			}
		}
		else // this logic is used to tool re-org trigger
		{
				VerUpt->NVM_Flag.NVM_Version = 0;
				VerUpt->NVM_IdLen.NVM_ID = 0;
		}
}

/***************************************************************************************/
static void ChkNVMApplication(uint32_t Add)
{
		NVM_Data_Config_ST *UptApp = &NVM_Block;
		
		if(UptApp->NVM_CtrlFlg.IsNVMTrg == FALSE)
		{
				/* final working APP update */
			if(Add >= APP_1_BASE_ADDRESS && Add < APP_1_END_ADDRESS)
			{
				UptApp->NVM_Data.NVMData0 = 0xAAAA1111;
			}
			else if(Add >= APP_2_BASE_ADDRESS && Add < APP_2_END_ADDRESS)
			{
				UptApp->NVM_Data.NVMData0 = 0xAAAA2222;
			}
			
			/* Length Update */
			UptApp->NVM_IdLen.NVM_Length = sizeof(UptApp->NVM_Data.NVMData0);
			
			/* cksum update */
			UptApp->NVM_ChkSum = ((~UptApp->NVM_Data.NVMData0)+1);
		}
		else
		{
			UptApp->NVM_Data.NVMData0 = 0xAAAA1111;
			
			/* Length Update */
			UptApp->NVM_IdLen.NVM_Length = sizeof(UptApp->NVM_Data.NVMData0);
			
			/* cksum update */
			UptApp->NVM_ChkSum = ((~UptApp->NVM_Data.NVMData0)+1);
		}
}


/***************************************************************************************/
