
#ifndef __NVM_DRIVER_H__
#define __NVM_DRIVER_H__

#include "stm32h5xx.h"
#include "Flash_Main.h"
#include "NVS_Driver.h"

typedef struct __NVM_ID_LEN
{
	uint16_t NVM_ID;
	uint16_t NVM_Length;
	
}NVM_ID_Len_ST;

/************************************************************/

typedef struct __NVM_FLAG
{
	uint8_t NVM_Version;
	uint8_t Res2;
	uint8_t Res3;
	uint8_t Res4;
	
}NVM_Flag_ST;

typedef struct _NVMControl_Flg
{
		uint8_t StartupFlg : 1;
		uint8_t IsReorgTrg : 1;
		uint8_t res  : 6;
	
}NVMControl_Flg_ST;
/************************************************************/

typedef struct __NVM_DATA_CONFIG
{
	uint32_t NVM_S_address;
	uint32_t NVM_Block_Size;
	NVMControl_Flg_ST NVM_CtrlFlg;
	uint32_t NVM_Header;
	NVM_ID_Len_ST NVM_IdLen;
	NVM_Flag_ST NVM_Flag;
	uint32_t NVM_ChkSum;
	uint32_t NVM_Data[4];
	
}NVM_Data_Config_ST;


/************************************************************/

extern NVM_Data_Config_ST NVM_Block;

/* use to find the last NVM block Address */
extern volatile uint32_t Last_NVMBlock_Add;

extern volatile uint32_t FindNVMApplicationAdd;

/* use to find the last NVM block Address & Total NVM block Numbers */
extern void Chk_NVMTotal_Block();

/* NVM Init */
extern void NVM_Init(void);

/* Scan the last NVM Block & Read it and store the RAM Memory */
extern void NVM_Scan_Block(void);

/* Read the data from the last NVM Block */
extern void NVM_Block_Read_FUN();


/* TO Write the New NVM Block Data  */
extern uint8_t NVM_Block_Write(void);
extern uint8_t NVM_Multi_Word_write(uint32_t Address,uint32_t *Data,uint32_t Size);

/* New NVM Data's are Updating */
extern uint8_t Update_Nvm_Block();
extern void NVM_VersionUpdate();
extern void ChkNVMApplication();
extern uint32_t NVM_AddUpdate(uint32_t Blk_add);
extern uint8_t NVM_ReOrg();

#endif