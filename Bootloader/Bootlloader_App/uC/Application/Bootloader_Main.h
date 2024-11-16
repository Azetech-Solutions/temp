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

/************* Flash CMDs *************/
#define FLASH_STARTCMD			  0xF5
#define FLASH_NVSCMD				  0xFA // not used
#define FLASH_FLASHCMD			  0xFB
#define FLASH_COMPLETECMD		  0xFC
#define FLASH_DATACMD				  0xFD
#define FLASH_ERASECMD			  0xFE



#define BOOT_RES_STATUS()  Boot_Response_status()

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
}Boot_state_EN;

typedef struct _BOOT_Control
{
	 UBYTE BootCmdReceiveVerifyFlag : 1;
	 UBYTE Flash_Write_Flag : 1;
	 UBYTE ChooseNvsFlag : 1;
	 UBYTE IndividualEraseVerifyFlag : 1;   // verify the individual erase is done or not
	 UBYTE ChooseIndividualErase_Flg : 1;  // in idle state handle
	 UBYTE ChooseFlash_Erase_Flag : 1;   // this is used to cyclic method
}BOOT_Control_ST;

extern void Boot_Req_Data_RxCbk(UBYTE Length, UBYTE *Data);

extern void Boot_Main();

extern void Boot_Response_status();

static Boot_RxByte_ST Boot_Rx_Data; // Boot Rx ST

extern Boot_TxByte_ST Boot_Tx_Data;	// Boot Tx ST

#endif
