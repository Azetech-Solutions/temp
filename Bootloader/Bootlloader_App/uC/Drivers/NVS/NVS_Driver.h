#ifndef __NVS_DRIVER__
#define __NVS_DRIVER__

#include "stm32h5xx.h"
#include "NVS.h"

#define NVS_Block_1		0   	/* Admin Data */
#define NVS_Block_2		1		/* Bootloader Data */
#define NVS_Block_3		2		/* App1 Data */
#define NVS_Block_4		3		/* App2 Data */
#define NVS_Block_5		4		/* IoT Data */

/* NVS Init */
extern void NVS_Init(void);

/* Scan the last NVS Block & Read it and store the RAM Memory */
extern void NVS_Scan_Block(void);

/* Read the data from the last NVS Blocks */
extern void NVS_Block_Read(uint32_t Address,uint32_t Blk_no);

/* Read the Particular NVS Block Data's */
extern void NVS_Block_Data_Read(uint8_t Block_Inx, uint32_t **Data);

/* To check the Last NVM Block is valid or Not */
extern uint8_t IS_NVS_BlockValid(uint8_t Block_Inx);

/* To find the Sum of the NVM Block Data's */
extern uint32_t NVS_data_ChkSum(uint32_t Add,uint8_t Size);

#endif