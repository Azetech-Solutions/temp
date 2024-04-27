#include "Debug.h"
#include "NVS.h"
#include "NVS_Driver.h"
#include "Flash_Main.h"

NVS_READ_DATA_ST  Nvs_Blk_Read[NVS_TOTAL_BLOCKS];

uint8_t IsRead_Allow = FALSE; 

static uint8_t nvsblkData_lenth=0;

void Nvs_Init(void)
{
	Nvs_Scan_Block();
//	NVS_Block_Write(1);
}

void Nvs_Scan_Block(void)
{
	uint8_t Blk_No;
	
	for(Blk_No = 0; Blk_No < NVS_TOTAL_BLOCKS; Blk_No++)
	{
		NVS_DATA_CONFIG_ST *Current_Block = &Nvs_Block_data[Blk_No];		
		IsRead_Allow = TRUE;
		if(Current_Block->Sts_flg.Flag == TRUE)
		{
			Nvs_Block_Read((NVS_START_ADDRESS|Current_Block->Start_Address),Blk_No);
		}
	
	}
}


void Nvs_Block_Read(uint32_t Address,uint32_t Blk_no)
{
	NVS_DATA_CONFIG_ST *NSRead = &Nvs_Block_data[Blk_no];
		
	if(IsRead_Allow == TRUE)
	{
		NSRead->NVS_ID_Len.NVS_ID = (uint16_t)Flash_Read(Address);		
		NSRead->NVS_ID_Len.NVS_Length = (uint16_t)(Flash_Read((Address))>>16);
		
		NSRead->Block_Checksum = Flash_Read((Address+4U));
		
		NSRead->Data = (uint32_t*)(Address+8U);
		
		IsRead_Allow = FALSE;
	}
}
uint32_t Nvs_Single_word_Read(const uint32_t Address)
{
	return *(uint32_t*)Address;
}

void NVS_Block_Data_Read(uint8_t Block_Inx, uint32_t **Data)
{
	NVS_DATA_CONFIG_ST *NSRead = &Nvs_Block_data[Block_Inx];
//	NVS_READ_DATA *NBlkRead = &Nvs_Blk_Read[Block_Inx];
	// add some check
	if(IS_NVS_BlockValid(Block_Inx) == TRUE)
	{
			*Data = NSRead->Data;
	}
}	

uint8_t IS_NVS_BlockValid(uint8_t Block_Inx)
{
	uint8_t retval = 0;
	uint32_t chk_Id =0,len=0;
	uint32_t Blk_add =0,data_chk=0;
	
	NVS_DATA_CONFIG_ST *Chk_Blk = &Nvs_Block_data[Block_Inx];
	
	Blk_add = (Chk_Blk->Start_Address | NVS_START_ADDRESS ); // to find the block start address
	
	chk_Id = (uint16_t)Flash_Read((Blk_add)); //
	len = (uint32_t)(Flash_Read(Blk_add)>>16);
	
	data_chk = NVS_data_ChkSum(Blk_add+8U,(Chk_Blk->Block_Size-3U));
	
	data_chk = ((~(chk_Id+len+data_chk))+1);
	if( Chk_Blk->Block_Checksum == data_chk)
	{
		retval = 1;
	}
	
	return retval;
}
/* This Function only gives the sum of the Data, because we want to add the id and length, 
	 after add it to convert the 2's complement */
uint32_t NVS_data_ChkSum(uint32_t Add,uint8_t Size)
{
	uint8_t i=0;
	uint32_t sum=0;
	nvsblkData_lenth=0;  // reset the data length
	
	while(i<Size)
	{
		if(Flash_Read(Add) != 0xFFFFFFFFU && Flash_Read(Add) != 0x00000000U)
		{
			sum+= Flash_Read(Add);
			nvsblkData_lenth++;
		}
		Add+=4U;
		i++;
	}
	
	return sum;
}

//void NVS_Block_Write(uint8_t Block_Inx)
//{
//	/* id->len->chksum->data*/
//	if((Block_Inx < NVS_TOTAL_BLOCKS) && (Block_Inx >= 0))
//	{
//		NVS_DATA_CONFIG *Chk_Blk = &Nvs_Block_data[Block_Inx];
//	
//		/* Data write */
//		
////		if(NVS_ValidBlockRead(Block_Inx)== TRUE) // I want add another check
////		{
//			NVS_Multi_Word_write((Chk_Blk->Start_Address | NVS_START_ADDRESS),&Nvs_Block_data[Block_Inx].Block_Index,Chk_Blk->Block_Size);
////		}
//		
//	}
//}

//uint32_t NVS_Multi_Word_write(uint32_t Address,uint32_t *Data,uint32_t Size)
//{
//	volatile uint32_t End_Flash_Add =0,i=0;
//	__disable_irq();
//	FLASH_Unlock();
//	
//	while(i<Size)
//	{
//		FLASH_Write(Address,(*Data++));
//		Address +=4U;
//		End_Flash_Add = Address;
//		i++;
//	}
//	
//	FLASH_Lock();
//	__enable_irq();
//	
//	if(End_Flash_Add != 0U)
//		return End_Flash_Add;
//	else
//		return FALSE;
//}