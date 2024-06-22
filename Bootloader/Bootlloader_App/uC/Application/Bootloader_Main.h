#ifndef __BOOTLOADER_MAIN_H__
#define __BOOTLOADER_MAIN_H__

#include "Uart_Driver.h"
#include "Backup_ram.h"
#include "Debug.h"
#include "NVS_Driver.h"
#include "NVM_Driver.h"

/************* MUC - RESPONSE TO TOOL *************/

#define BOOT_STATUS_OK 					0x00
#define BOOT_STATUS_NOT_OK			0x01

/************* BANK - 0 *************/

#define BOOTMANAGER_SECTOR			0U
#define	BOOTLOADER_SECTOR				1U
#define	APP1_SECTOR							3U

/************* BANK - 1 *************/
#define	NVS_SECTOR							0U
#define	NVM_SECTOR							1U
#define	APP2_SECTOR							3U


#define Boot_Res_Status()  Boot_Response_status()

typedef struct __Flash_data
{
	UBYTE Data[16];
}Flash_data_ST;

typedef union _Boot_RxByte_ST
{
	struct
	{
		UBYTE Boot_command;
		UBYTE Flash_Add_1_byte;
		UBYTE Flash_Add_2_byte;
		UBYTE Flash_Add_3_byte;
		UBYTE Flash_Add_4_byte;
		UBYTE Data_1;
		UBYTE Data_2;
		UBYTE Data_3;
		UBYTE Data_4;
		UBYTE Data_5;
		UBYTE Data_6;
		UBYTE Data_7;
		UBYTE Data_8;
		UBYTE Data_9;
		UBYTE Data_10;
		UBYTE Data_11;
		UBYTE Data_12;
		UBYTE Data_13;
		UBYTE Data_14;
		UBYTE Data_15;
		UBYTE Data_16;
	};	
	UBYTE Bytes[21];
	
}Boot_RxByte_ST;

typedef union _Boot_TxByte_ST
{
	struct
	{
		UBYTE Boot_Status;	
	};
	
		UBYTE Byte;
}Boot_TxByte_ST;

typedef enum
{
	Boot_Idle = 0,
	Boot_Start,
	Boot_Wating_for_next_command,
	Boot_Flash_Write,
	Boot_Erase_Flash,
	Boot_NVM_State,
}Boot_state_EN;

extern Boot_RxByte_ST Boot_Rx_Data;
extern Boot_TxByte_ST Boot_Tx_Data;

extern void Boot_Req_Data_RxCbk(UBYTE Length, UBYTE *Data);

extern void Boot_Main();

extern void Boot_Response_status();

extern ULONG calculateChecksum(ULONG *data, ULONG length);
#endif
