
#ifndef __NVM_DRIVER_H__
#define __NVM_DRIVER_H__


#include "Flash_Main.h"

/************************************************************/

typedef struct __NVM_ID_LEN
{
	uint16_t NVM_ID :16 ;
	uint16_t NVM_Length :16;
	
}NVM_ID_Len_ST;

/************************************************************/

typedef struct __NVM_FLAG
{
	uint8_t NVM_Version :8;
	uint8_t Res2 :8;
	uint8_t Res3 :8;
	uint8_t Res4 :8;
	
}NVM_Flag_ST;
typedef struct _NVMData
{
	uint32_t NVMData0;
	uint32_t NVMData1;
	uint32_t NVMData2;
	uint32_t NVMData3;
}NVMData_ST;

typedef struct _NVMControl_Flg
{
		uint8_t StartupFlg : 1;
		uint8_t IsNVMTrg :1;
		uint8_t IsGetAllData: 1;
		uint8_t IsReorgTrg : 1;
		uint8_t IsClearTrg :1;
		uint8_t IsUpdateTrg :1;
		uint8_t IsUpdateAllTrg :1;
		uint8_t res  : 1;
	
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
	NVMData_ST NVM_Data;
	
}NVM_Data_Config_ST;

/************************************************************/

typedef struct _CHECK_HEADER
{
	uint32_t Header_start_Add;
	uint32_t Ck_Header;
	uint32_t Ck_SAddress;
	uint32_t Ck_EAddress;
	uint32_t Ck_cksum;
	uint32_t Ck_MajorVersion;
	uint32_t Ck_MinorVersion;
	uint32_t Ck_BuildVersion;
	uint32_t Ck_ReleaseType;
	
}Check_App_Header_ST;


/************************************************************/
extern NVM_Data_Config_ST NVM_Block;
extern Check_App_Header_ST Ck_Hdr[];

/* use to find the last NVM block Address */
extern volatile uint32_t Last_NVMBlock_Add;

/* use to find the last NVM block Address & Total NVM block Numbers */
extern void Chk_NVMLast_BlockAdd();

/* NVM Init */
extern void NVM_Init(void);

/* Scan the last NVM Block & Read it and store the RAM Memory */
static void NVM_Scan_Block(void);

/* Read the data from the last NVM Block */
static void NVM_Block_Read_FUN(NVM_Data_Config_ST *Rblk,uint32_t Current_Address);


/* TO Write the New NVM Block Data  */
static uint8_t NVM_Block_Write(void);

/* New NVM Data's are Updating */
extern uint8_t Update_Nvm_Block(uint32_t Add);
static void NVM_VersionUpdate();
static void ChkNVMApplication(uint32_t Add);
static uint32_t NVM_AddUpdate(uint32_t Blk_add);

/* This function is read the Headers of the APP1 & APP2 */
extern void Read_Apps_Header(void);
extern uint32_t ChkAppHeader_ChkSum();

extern uint8_t NVM_ReOrg();
extern uint8_t NvmTool_Update();
extern uint8_t NVMToolClear();

extern uint32_t App_Image_Chksum_calculation(uint32_t Add);  // this api not used anywhere

#endif