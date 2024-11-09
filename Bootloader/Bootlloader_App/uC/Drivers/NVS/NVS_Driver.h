#ifndef __NVS_DRIVER__
#define __NVS_DRIVER__

#include "Debug.h"
#include "Flash_Main.h"

/***************************NVS Part*************************/

#define NVS_TOTAL_BLOCKS						1

/************************************************************/

typedef struct __NVS_ID_LEN
{
	uint16_t NVS_ID;
	uint16_t NVS_Length;
	
}NVS_ID_Len_ST;

/************************************************************/

typedef struct _NVS_STATUS_FLAG
{
	uint8_t RES :7;
	uint8_t Flag :1;
	
}NVS_STATUS_FLAG_ST;

/************************************************************/

typedef struct _NVS_Dataconfig
{
	uint32_t Start_Address;
	uint16_t Block_Size;
	NVS_STATUS_FLAG_ST Sts_flg;
	uint32_t NVS_Pattern;
	NVS_ID_Len_ST NVS_ID_Len;
	uint32_t Block_Checksum;
	uint32_t *Data;
}NVS_Dataconfig_ST;

/************************************************************/

/* NVS Init */
extern void NVS_Init(void);

/* Scan the last NVS Block & Read it and store the RAM Memory */
static void NVS_Scan_Block(void);

/* Read the data from the last NVS Blocks */
static void NVS_Block_Read(uint32_t Address,uint32_t Blk_no);

/* Read the Particular NVS Block Data's */
extern void NVSBlock_DataRead(uint8_t Block_Inx, uint32_t **Data);

/* To check the Last NVM Block is valid or Not */
static uint8_t IS_NVS_BlockValid(uint8_t Block_Inx);

/* To find the Sum of the NVM Block Data's */
extern uint32_t FindBlock_DataSum(uint32_t Add,uint8_t Size);

#endif