#ifndef __NVS_DRIVER__
#define __NVS_DRIVER__

#include "stm32h5xx.h"
#include "NVS.h"

#define TRUE      1
#define FALSE     0


#define Block_1		0   /* Admin Data */
#define Block_2		1		/* Bootloader Data */
#define Block_3		2		/* App1 Data */
#define Block_4		3		/* App2 Data */
#define Block_5		4		/* IoT Data */

extern void Nvs_Init(void);
extern void Nvs_Scan_Block(void);
extern void Nvs_Block_Read(uint32_t Address,uint32_t Blk_no);
extern uint32_t Nvs_Single_word_Read(const uint32_t Address);

extern void NVS_Block_Data_Read(uint8_t Block_Inx, uint32_t **Data);

extern uint8_t IS_NVS_BlockValid(uint8_t Block_Inx);

extern uint32_t NVS_data_ChkSum(uint32_t Add,uint8_t Size);

/* no need now */
extern void NVS_Block_Write(uint8_t Block_Inx);
extern uint32_t NVS_Multi_Word_write(uint32_t Address,uint32_t *Data,uint32_t Size);


#endif