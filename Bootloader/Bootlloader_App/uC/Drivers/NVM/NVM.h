
#ifndef __NVM_H__
#define __NVM_H__

#include "stm32h5xx.h"
#include "Flash_Main.h"
#include "Platform_Types.h"

/*******************Application Part*************************/
#define APP_1_BASE_ADDRESS										0x08006000U
#define APP_1_END_ADDRESS											0x08010000U
#define APP_2_BASE_ADDRESS										0x08016000U
#define APP_2_END_ADDRESS											0x08020000U

#define TOTAL_APP_HEADER											2U
#define HEADER_APP_1													0U
#define HEADER_APP_2													1U

/************************************************************/

/***************************NVM Part*************************/
/* NVM Sector 1 */
#define NVM_SECTOR_ONE_START_ADDRESS						0x08012000
#define NVM_SECTOR_ONE_END_ADDRESS							0x08013FFC
/* NVM Sector 2 */
#define NVM_SECTOR_TWO_START_ADDRESS						0x08014000
#define NVM_SECTOR_TWO_END_ADDRESS							0x08015FFC
/* NVM Sectors */
#define NVM_SECTOR_ONE							1U
#define NVM_SECTOR_TWO							2U

#define NVM_DATA_BLOCK_SIZE					4U
#define NVM_ONE_BLOCK_SIZE 					8U

/************************************************************/

typedef struct __NVM_ID_LEN
{
	uint16_t NVM_ID;
	uint16_t NVM_Length;
	
}NVM_ID_Len_ST;
typedef struct __NVM_FLAG
{
	uint8_t NVM_Version;
	uint8_t Res2;
	uint8_t Res3;
	uint8_t Res4;
	
}NVM_Flag_ST;

typedef struct __NVM_DATA_CONFIG
{
	uint32_t NVM_S_address;
	uint32_t NVM_Block_Size;
	uint8_t NVM_SrtUp_Flg;
	uint32_t NVM_Header;
	NVM_ID_Len_ST NVM_IdLen;
	NVM_Flag_ST NVM_Flag;
	uint32_t NVM_ChkSum;
	uint32_t NVM_Data[4];
	
}NVM_Data_Config_ST;


typedef struct __NVM_BLOCK_READ
{
	uint32_t NVM_R_Header;
	NVM_ID_Len_ST NVM_R_IdLen;
	NVM_Flag_ST NVM_R_Flag;
	uint32_t NVM_R_ChkSum;
	uint32_t NVM_R_Data[4];
	
}NVM_Block_Read_ST;

typedef struct _CHECK_HEADER
{
	uint32_t Header_start_Add;
	uint32_t Ck_Header;
	uint32_t Ck_SAddress;
	uint32_t Ck_EAddress;
	uint32_t Ck_Flags;
	uint32_t Ck_cksum;
	
}Check_App_Header_ST;

extern NVM_Data_Config_ST NVM_Block;
extern NVM_Block_Read_ST NVM_last_block;
extern Check_App_Header_ST Ck_Hdr[];

#endif