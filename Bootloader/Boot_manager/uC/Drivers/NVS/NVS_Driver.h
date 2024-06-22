#ifndef __NVS_DRIVER__
#define __NVS_DRIVER__

#include "stm32h5xx.h"
#include "Jump_Boot_App.h"

#define TRUE      1
#define FALSE     0

/***************************NVS Part*************************/

#define NVS_Block_1		0   	/* Admin Data */
#define NVS_Block_2		1		/* Bootloader Data */
#define NVS_Block_3		2		/* App1 Data */
#define NVS_Block_4		3		/* App2 Data */
#define NVS_Block_5		4		/* IoT Data */

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
extern NVS_Dataconfig_ST  Nvs_Config_Block;

/* NVS Init */
extern void NVS_Init(void);

/* Scan the last NVS Block & Read it and store the RAM Memory */
extern void NVS_Scan_Block(void);

/* Read the data from the last NVS Blocks */
extern void NVS_Block_Read(uint32_t Address,uint32_t Blk_no);

/* Read the Particular NVS Block Data's */
extern void NVSBlock_DataRead(uint8_t Block_Inx, uint32_t **Data);

/* To check the Last NVM Block is valid or Not */
extern uint8_t IS_NVS_BlockValid(uint8_t Block_Inx);

/* To find the Sum of the NVM Block Data's */
extern uint32_t FindBlock_DataSum(uint32_t Add,uint8_t Size);

#endif