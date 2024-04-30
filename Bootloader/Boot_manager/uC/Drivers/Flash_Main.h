#ifndef __FLASH_DRIVER_H__
#define __FLASH_DRIVER_H__

#include "stm32h5xx.h"                  // Device header
#include "stm32h503xx.h"
#include "main.h"


#define FLASH_KEY1                 0x45670123U
#define FLASH_KEY2                 0xCDEF89ABU

#define BANK_1 0
#define BANK_2 1

extern void FLASH_init(void);
extern void FLASH_Unlock(void);
extern void FLASH_Lock(void);

/* Proram Read Main API */
extern uint32_t Flash_Read(const uint32_t Address);
 /* Proram wirte Main API */
extern void FLASH_Write(uint32_t Address, uint32_t Data);
/* To use 4 word data write */
extern uint32_t Multi_Word_write(uint32_t Address,uint32_t *Data);
/* To used for Check the Errors */
extern uint8_t Flash_Error_Check();
/* Proram Sector Erase Main API */
extern uint8_t FLASH_Sector_Erase(uint8_t Sec,uint8_t Bnk);
/* Single sector erase */
extern uint8_t Flash_SingleSec_Erase(uint8_t Sec,uint8_t Bnk);
/* To choose the bnk and do Proram Erase */
extern uint8_t FLASH_Erase_NoofSectors(uint8_t Bnk);
/* To use verify the Single sector Erase */
extern uint32_t Verify_SingleSec_Erase(uint32_t Address); 	


#endif