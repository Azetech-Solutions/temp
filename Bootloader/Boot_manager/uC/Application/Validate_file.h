
#ifndef __VALIDATE_FILE_H__
#define __VALIDATE_FILE_H__

#include "stm32h5xx.h"
#include "main.h"
#include "Jump_Boot_App.h"
#include "NVS_Driver.h"

typedef struct _CHECK_HEADER
{
	uint32_t Header_start_Add;
	uint32_t Ck_Header;
	uint32_t Ck_SAddress;
	uint32_t Ck_EAddress;
	uint32_t Ck_cksum;
	uint32_t Ck_MajorVersion;
	uint32_t Ck_MinorVersion;
	uint32_t Ck_BuildVersion;
	uint32_t Ck_ReleaseType;
	
}Check_App_Header_ST;

/* To check the Bootloader is valid or not */
extern uint8_t IsBoot_valid(void);

/* To read the APP 1&2 Header */
extern void Read_Apps_Header(void);

/* This Function is used to find the total checksum of the app 1 or 2, bootloader image  */
extern uint32_t App_Image_Chksum_calculation(uint32_t Add);

extern Check_App_Header_ST Ck_Hdr[];

#endif