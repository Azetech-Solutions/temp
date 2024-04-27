
#ifndef __NVM_DRIVER_H__
#define __NVM_DRIVER_H__

#include "stm32h5xx.h"


extern uint32_t Last_NVMBlock_Add;
extern uint8_t Total_NVM_Block_No;

extern uint8_t Chk_NVMTotal_Block();

extern void NVM_Init(void);
extern void NVM_Scan_Block(void);

extern void NVM_Block_Read_FUN(uint32_t Block_Inx);

extern uint8_t IS_Chk_LtBlk_NVMValid();


extern uint8_t NVM_Block_Write(void);
extern void NVM_Multi_Word_write(uint32_t Address,uint32_t *Data,uint32_t Size);

extern uint8_t NVM_Block_Erase(void);
extern uint8_t Verify_NVM_Sector_Erase(uint32_t Address);

extern uint8_t Update_Nvm_Block(uint32_t App_Add);
extern void Read_Apps_Header(void);

extern uint32_t App_Image_Chksum_calculation(uint32_t Add);

#endif