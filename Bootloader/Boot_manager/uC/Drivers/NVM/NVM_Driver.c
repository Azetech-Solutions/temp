#include "NVM_Driver.h"
#include "NVM.h"


uint8_t IsNVMRead_Allow = FALSE;
uint8_t NVM_Init_Flag = FALSE;
uint8_t NVM_Sec2_EraseVerify_Flg = FALSE;

volatile uint32_t Last_NVMBlock_Add=0;  //this variable is used to find the last valid NVM address
static uint32_t PreLast_NVMBlock_Add;
static uint8_t nmblkData_lenth =0;
uint8_t Total_NVM_Block_No =0; // this variable is used to find the Data lenth of 

/***************************************************************************************/
void NVM_Init(void)
{
	NVM_Init_Flag = TRUE;
	
	NVM_Scan_Block();
}
/***************************************************************************************/
void NVM_Scan_Block(void)
{
	uint8_t Blk_No;
	
		NVM_Data_Config_ST *NVMBlkRead = &NVM_Block;
		
		if(NVMBlkRead->NVM_SrtUp_Flg == TRUE)
		{
			IsNVMRead_Allow = TRUE;
			
			if(NVM_Init_Flag == TRUE)
			{
				NVM_Block_Read_FUN(Blk_No);  // NVM Block data Read function
			}
		}
		
	NVM_Init_Flag = FALSE;
}
/***************************************************************************************/
void NVM_Block_Read_FUN(uint32_t Block_Inx)
{
//	NVM_Data_Config *nvconfig = &NVM_Block;
	NVM_Block_Read_ST  *nmread = &NVM_last_block;
	uint32_t Current_Address=0;
	uint8_t i;
	
	Current_Address = Last_NVMBlock_Add; // last block of NVM data is Read
	
	if(IsNVMRead_Allow == TRUE)
	{
		nmread->NVM_R_Header = Flash_Read(Current_Address);	// to read the last block  nvm Header/ Pattern
		
		nmread->NVM_R_IdLen.NVM_ID = (uint16_t)(Flash_Read(Current_Address+4U)); // to read the last block  nvm Id
		nmread->NVM_R_IdLen.NVM_Length = (uint16_t)((Flash_Read(Current_Address+4U)) >> 16); // to read the last block  nvm length
		
		nmread->NVM_R_Flag.NVM_Version = (uint8_t)(Flash_Read(Current_Address+8U)); // to read the last block  nvm verison
		
		nmread->NVM_R_ChkSum = Flash_Read(Current_Address+12U); // to read the last block  nvm checksum
		
		Current_Address +=16U;  // to read the last block  nvm data's
		for(i=0;i<NVM_DATA_BLOCK_SIZE;i++)
		{
			nmread->NVM_R_Data[i] = Flash_Read(Current_Address);
			Current_Address+=4U;
		}
		
		IsNVMRead_Allow = FALSE;
	}
}
/***************************************************************************************/
uint8_t IS_Chk_LtBlk_NVMValid()
{
	uint8_t retval = 0;
	uint16_t Add_Id_Len =0;
	uint32_t Blk_add =0,Find_val=0;
	
//	NVM_Data_Config *NVMBlkRead = &NVM_Block;	
	NVM_Block_Read_ST  *ckvid = &NVM_last_block;
	
	Blk_add = PreLast_NVMBlock_Add;   //(NVM_START_ADDRESS | NVMBlkRead->NVM_S_address);
	
	Add_Id_Len = (ckvid->NVM_R_IdLen.NVM_ID + ckvid->NVM_R_IdLen.NVM_Length);//(uint16_t)Flash_Read((Blk_add+4U));
	Find_val = (~(Add_Id_Len + NVM_data_ChkSum(Blk_add + 16U)))+1; // to read the last block of nvm data's (4 word) and calculating the checksum
	
	if( ckvid->NVM_R_ChkSum == Find_val)
	{
		retval = 1;
	}
	
	return retval;
}
/***************************************************************************************/
/*
*  This Function to Find the Total NVM Block and find the last block Address
*/
uint8_t Chk_NVMTotal_Block()
{
	uint8_t count = 0;
	
	uint32_t SAdd = NVM_SECTOR_ONE_START_ADDRESS;
	
	while(SAdd < NVM_SECTOR_TWO_END_ADDRESS)
	{
		if(Flash_Read(SAdd) == 0xA1A1A1A1)
		{	
			count++;
			Last_NVMBlock_Add = SAdd;  // to find the last valid nvm block 
		}
		
		SAdd+=4U;
	}
	
	return count;  // return total number of nvm blocks
}
/***************************************************************************************/
uint8_t NVM_Block_Write(void)
{
	uint8_t retval=0;
	/* Header->len->Id->Flag->chksum->data*/
		NVM_Data_Config_ST *upDtBlk = &NVM_Block;	
	
		/* To find the last block is valid or not , if it is valid do Data write operation, otherwise not */	
		if(IS_Chk_LtBlk_NVMValid()== TRUE) 
		{
			/* This function is used to Update new NVM block  Data's */
			NVM_Multi_Word_write((Last_NVMBlock_Add + (NVM_ONE_BLOCK_SIZE*sizeof(uint32_t))),&NVM_Block.NVM_Header,upDtBlk->NVM_Block_Size);
			
			retval = 1;
		}	
		
	return retval;
}
/***************************************************************************************/
void NVM_Multi_Word_write(uint32_t Address,uint32_t *Data,uint32_t Size)
{
	volatile uint32_t End_Flash_Add =0,i=0;
	
	__disable_irq();
	FLASH_Unlock();
	Flash_Error_Check();
	
	while(i<Size)
	{
		FLASH_Write(Address,(*Data++));
		Address +=4U;
		End_Flash_Add = Address;
		i++;
	}
	
	Flash_Error_Check();
	FLASH_Lock();
	__enable_irq();
}

/***************************************************************************************/
uint32_t NVM_data_ChkSum(uint32_t Add)
{
	uint8_t i=0;
	uint32_t sum=0;
	nmblkData_lenth=0;  // reset the data length
	
	while(i<NVM_DATA_BLOCK_SIZE)
	{
		if(Flash_Read(Add) != 0xFFFFFFFFU && Flash_Read(Add) != 0x00000000U)
		{
			sum+= Flash_Read(Add);
			nmblkData_lenth++;
		}
		Add+=4U;
		i++;
	}
	
	return sum;
}
/***************************************************************************************/
/* This function update the New NVM Block */
uint8_t Update_Nvm_Block(uint32_t App_Add)
{
	NVM_Data_Config_ST *updt_nvm = &NVM_Block;
	NVM_Block_Read_ST  *copy_nvm= &NVM_last_block;
	uint8_t retval =0;
	uint32_t Blk_add =0,Find_val =0;
	uint32_t Add_Id_Len =0,i=0;
	
	Blk_add = Last_NVMBlock_Add;   //(NVM_START_ADDRESS | NVMBlkRead->NVM_S_address);
	
			/* NVM Address update */
			if( Blk_add >= NVM_SECTOR_ONE_START_ADDRESS && Blk_add < (NVM_SECTOR_TWO_START_ADDRESS - 50U))
			{
				PreLast_NVMBlock_Add = Last_NVMBlock_Add;
				Blk_add = Last_NVMBlock_Add;
			}
			else if((Blk_add >= (NVM_SECTOR_TWO_START_ADDRESS - 50U)) && Blk_add <= NVM_SECTOR_TWO_START_ADDRESS )
			{
				PreLast_NVMBlock_Add = Last_NVMBlock_Add;
				Last_NVMBlock_Add = 0x08013FE0;	// This address is nvm sec 2 start address - 20U for write the NVM data on sec 2
			}
			else if(Blk_add >=NVM_SECTOR_TWO_START_ADDRESS && (Blk_add <(APP_2_BASE_ADDRESS - 50U)))
			{
				PreLast_NVMBlock_Add = Last_NVMBlock_Add;
				Blk_add = Last_NVMBlock_Add;
			}
			else if((Blk_add >= (APP_2_BASE_ADDRESS - 50U)) && (Blk_add <= APP_2_BASE_ADDRESS) ) //end NVM address
			{
					// erase sec 1
					if(Flash_SingleSec_Erase(NVM_SECTOR_ONE,BANK_2))
					{
						// update the last NVM block address
						PreLast_NVMBlock_Add = Last_NVMBlock_Add;
						Last_NVMBlock_Add = 0x08011FE0; // This address is nvm sec 1 start address - 20U for write the NVM data on sec 1
						NVM_Sec2_EraseVerify_Flg = TRUE;
					}
			}
			updt_nvm->NVM_Header = copy_nvm->NVM_R_Header;
	
			/* APP version and ID Update */	
			if(copy_nvm->NVM_R_Flag.NVM_Version < 255)
			{
				updt_nvm->NVM_Flag.NVM_Version = copy_nvm->NVM_R_Flag.NVM_Version +1U;
				updt_nvm->NVM_IdLen.NVM_ID = copy_nvm->NVM_R_IdLen.NVM_ID;
			}
			else
			{
				updt_nvm->NVM_Flag.NVM_Version = 0U;
				
				if( copy_nvm->NVM_R_IdLen.NVM_ID < 255)
				{
					updt_nvm->NVM_IdLen.NVM_ID = copy_nvm->NVM_R_IdLen.NVM_ID + 1U;
				}
				else
				{
					updt_nvm->NVM_IdLen.NVM_ID = 0U;
				}					
			}
		
			/* final working APP update */
			if(App_Add >= APP_1_BASE_ADDRESS && App_Add < APP_1_END_ADDRESS)
			{
				updt_nvm->NVM_Data[0] = 0xAAAA1111;
			}
			else if(App_Add >= APP_2_BASE_ADDRESS && App_Add < APP_2_END_ADDRESS)
			{
				updt_nvm->NVM_Data[0] = 0xAAAA2222;
			}						
			/* Length Update */
			updt_nvm->NVM_IdLen.NVM_Length = sizeof(updt_nvm->NVM_Data[0]); // change it 
			
			/* Checksum Update */
			Add_Id_Len = (updt_nvm->NVM_IdLen.NVM_ID + updt_nvm->NVM_IdLen.NVM_Length);
			
			Add_Id_Len = Add_Id_Len + updt_nvm->NVM_Data[0];
			
			Find_val = ((~Add_Id_Len)+1);
			
			updt_nvm->NVM_ChkSum = Find_val;
			
			/* Write the updated NVM Block in flash memory */
			if(NVM_Block_Write())
			{
				if(NVM_Sec2_EraseVerify_Flg == TRUE)
				{
					/* Erase the Sec2 */
					if(Flash_SingleSec_Erase(NVM_SECTOR_TWO,BANK_2))
					{
						retval = 1;
					}
					NVM_Sec2_EraseVerify_Flg = FALSE;
					return retval;
				}
				retval = 1;
			}

	return retval;
}