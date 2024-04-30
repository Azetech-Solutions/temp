
#ifndef __NVM_DRIVER_H__
#define __NVM_DRIVER_H__

#include "stm32h5xx.h"

/* use to find the last NVM block Address */
extern volatile uint32_t Last_NVMBlock_Add;

/* use to find the Total NVM block Numbers */
extern uint8_t Total_NVM_Block_No;

/* use to find the last NVM block Address & Total NVM block Numbers */
extern uint8_t Chk_NVMTotal_Block();

/* NVM Init */
extern void NVM_Init(void);

/* Scan the last NVM Block & Read it and store the RAM Memory */
extern void NVM_Scan_Block(void);

/* Read the data from the last NVM Block */
extern void NVM_Block_Read_FUN(uint32_t Block_Inx);

/* To check the Last NVM Block is valid or Not */
extern uint8_t IS_Chk_LtBlk_NVMValid();

/* To find the Sum of the NVM Block Data's */
extern uint32_t NVM_data_ChkSum(uint32_t Add);

/* TO Write the New NVM Block Data  */
extern uint8_t NVM_Block_Write(void);
extern void NVM_Multi_Word_write(uint32_t Address,uint32_t *Data,uint32_t Size);

/* New NVM Data's are Updating */
extern uint8_t Update_Nvm_Block(uint32_t App_Add);

/* This function is read the Headers of the APP1 & APP2 */
extern void Read_Apps_Header(void);

extern uint32_t App_Image_Chksum_calculation(uint32_t Add);

#endif