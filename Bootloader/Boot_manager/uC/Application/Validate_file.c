#include "Validate_file.h"
#include "Flash_Main.h"

uint32_t NVS_data_ChkSum(uint32_t Add,uint8_t Size);
static uint8_t nvsblkData_lenth=0;

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
/******************************************************************************************/
/* To check the APP - 1 is valid or not */
uint8_t IsApp1_valid(void)
{
	NVS_DATA_CONFIG_ST *ckapp1 = &Nvs_Block_data[NVS_Block_3];
	uint8_t retval=0;
	if(ckapp1->Block_Checksum == App_Image_Chksum_calculation((uint32_t)ckapp1->Data))
	{
		retval = 1;
	}
	
	return retval;
}
/******************************************************************************************/
/* To check the APP - 2 is valid or not */
uint8_t IsApp2_valid(void)
{
	NVS_DATA_CONFIG_ST *ckapp2 = &Nvs_Block_data[NVS_Block_4];
	uint8_t retval=0;
	if(ckapp2->Block_Checksum == App_Image_Chksum_calculation((uint32_t)ckapp2->Data))
	{
		retval = 1;
	}
	return retval;
}
/******************************************************************************************/
/* To check the Bootloader is valid or not */
uint8_t IsBoot_valid(void)
{
	NVS_DATA_CONFIG_ST *ckapp1 = &Nvs_Block_data[NVS_Block_2];
	uint8_t retval=0;
	uint16_t chk_Id =0,len=0;
	uint32_t Blk_add =0,data_chk=0;
	
	Blk_add = (ckapp1->Start_Address | NVS_START_ADDRESS );
	
	chk_Id = (uint16_t)Flash_Read((Blk_add));	
	len = (uint16_t)(Flash_Read(Blk_add)>>16);
	
	data_chk = NVS_data_ChkSum((Blk_add+8U),(ckapp1->Block_Size-2U)); //NVS_BLOCK_ONE_TOTA_DATA_SUM();
	
	data_chk = (~(chk_Id+len+data_chk))+1;
	if( ckapp1->Block_Checksum == data_chk)
	{
		retval = 1;
	}
	return retval;
}
/******************************************************************************************/
/* This Function is used to find the total app 1/2, bootloader image check sum */
uint32_t App_Image_Chksum_calculation(uint32_t Add)  // this api not used anywhere
{
	uint32_t retval=0,ck= 0;
	
	
	while(Flash_Read(Add) != 0xFFFFFFFF)
	{
		ck += Flash_Read(Add);
		Add += 4U;
	}
	
	return (((~ck)+1)&0xFFFFFFFF);
}
/******************************************************************************************/
void Read_Apps_Header(void)
{
	uint8_t i;
	
	for(i=0;i<2;i++)
	{
		Check_App_Header_ST *Ck = &Ck_Hdr[i];
	
		Ck->Ck_Header = Flash_Read(Ck->Header_start_Add);

		Ck->Ck_SAddress = Flash_Read((Ck->Header_start_Add+4U));

		Ck->Ck_EAddress =	Flash_Read((Ck->Header_start_Add+8U));

		Ck->Ck_Flags = Flash_Read((Ck->Header_start_Add+12U));

		Ck->Ck_cksum = Flash_Read((Ck->Header_start_Add+16U));
	}
}
/******************************************************************************************/