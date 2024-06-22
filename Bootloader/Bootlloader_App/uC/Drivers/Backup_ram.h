#ifndef __BACKUP_RAM_H__
#define __BACKUP_RAM_H__

#include "stm32h5xx.h"
#include "Flash_Main.h"

/***************************************************************************************/
#define BKPRAM_CLK_ENABLE()        SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPRAMEN)

#define BKPRAM_CLK_DISABLE()         CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_BKPRAMEN)

/***************************************************************************************/

/* Below the backup ram addreses are used to store and verity the data */
#define BkUpRam_Base_ADD					0x40036400

#define BkUpRam_Verify_App_ADD		0x40036404 // this address is used to write data, to confirm the switch based on backup ram

#define BkupRam_ADD_Clear					0xFFFFFFFF

/***************************************************************************************/

extern void bkSRAM_Init(void);

extern void PWREx_EnableBkupRAM_REG(void);

extern void PWR_EnableBkUpAccess(void);
extern void PWR_DisableBkUpAccess(void);


extern void bkSRAM_WriteVariable(uint32_t write_adress,uint32_t vall);
extern void bkSRAM_ReadVariable(uint32_t read_adress, uint32_t* read_data);

/***************************************************************************************/

#endif