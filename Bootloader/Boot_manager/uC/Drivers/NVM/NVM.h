
#ifndef __NVM_H__
#define __NVM_H__

#include "stm32h5xx.h"
#include "Flash_Main.h"
/*******************Application Part*************************/
#define App1_BaseAdd										0x08006000U
#define App2_BaseAdd										0x08016000U
#define TOTAL_APP_HEADER					2
#define HEADER_APP_1							0
#define HEADER_APP_2							1

/************************************************************/

/***************************NVM Part*************************/
#define NVM_START_ADDRESS						0x08012000
#define NVM_END_ADDRESS							0x08015FFC

#define TOTAL_NVM_BLOCK						1
#define NVM_DATA_BLOCK_SIZE				4
#define NVM_ONE_BLOCK_SIZE 				8

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


extern NVM_Data_Config_ST NVM_Block;
extern NVM_Block_Read_ST NVM_last_block;


#endif