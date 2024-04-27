
#ifndef __VALIDATE_FILE_H__
#define __VALIDATE_FILE_H__

#include "stm32h5xx.h"
#include "main.h"
#include "Jump_Boot_App.h"
#include "NVS.h"
#include "NVS_Driver.h"

typedef struct _CHECK_HEADER
{
	uint32_t Header_start_Add;
	uint32_t Ck_Header;
	uint32_t Ck_SAddress;
	uint32_t Ck_EAddress;
	uint32_t Ck_Flags;
	uint32_t Ck_cksum;
	
}Check_App_Header_ST;

extern uint8_t IsApp1_valid(void);
extern uint8_t IsApp2_valid(void);
extern uint8_t IsBoot_valid(void);

extern void Read_Apps_Header(void);

extern uint32_t App_Image_Chksum_calculation(uint32_t Add);
extern Check_App_Header_ST Ck_Hdr[];

#endif