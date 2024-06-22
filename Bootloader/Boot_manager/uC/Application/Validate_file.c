#include "Validate_file.h"
#include "Flash_Main.h"


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
/******************************************************************************************/
/* To check the Bootloader is valid or not */
uint8_t IsBoot_valid(void)
{
	Check_App_Header_ST *Ck = &Ck_Hdr[HEADER_BLR];
	uint8_t retval=0;

	if( Ck->Ck_cksum == App_Image_Chksum_calculation(Ck->Ck_SAddress))
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
	
	
	while(*(uint32_t*)(Add) != 0xFFFFFFFF)
	{
		ck += FLASH_Read(Add);
		Add += 4U;
	}
	
	return (((~ck)+1)&0xFFFFFFFF);
}
/******************************************************************************************/
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
/******************************************************************************************/