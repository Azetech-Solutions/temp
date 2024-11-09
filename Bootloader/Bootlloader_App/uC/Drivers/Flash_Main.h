#ifndef __FLASH_DRIVER_H__
#define __FLASH_DRIVER_H__

//#include "stm32h5xx.h"                  // Device header
#include "Bootloader_Main.h"
#include "Addresses_Handling.h"


#define FLASH_KEY1                 0x45670123U
#define FLASH_KEY2                 0xCDEF89ABU

#define BANK_1      							 0U
#define BANK_2      							 1U 

/************************************************************************************************/

extern void FLASH_init(void);
extern void FLASH_Unlock(void);
extern void FLASH_Lock(void);
/************************************************************************************************/

extern uint32_t FLASH_Read(const uint32_t Address);	/* Proram Read Main API */
extern void FLASH_Write(uint32_t Address, uint32_t Data);  /* Proram wirte Main API */
static void FLASH_SecErase(uint8_t Sec,uint8_t Bnk);	/* Proram Sector Erase Main API */
static void FLASH_ErrorChk(); /* To used for Check the Errors Main API */

/************************************************************************************************/
extern uint32_t FLASH_Multi_Word_write(uint32_t Address, uint32_t *Data, uint32_t size);  /* To use 4 word data write */

/************************************************************************************************/
extern uint8_t FLASH_Erase_NoofSectors(uint8_t sec,uint8_t Bnk,uint8_t SecCount);  /* To choose the bnk and do Proram Erase */

/************************************************************************************************/
extern uint8_t VerifyFlashErase(uint32_t StAdd,uint32_t EnAdd);

/************************************************************************************************/

#endif