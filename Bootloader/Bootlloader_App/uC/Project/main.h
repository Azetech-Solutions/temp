#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32h5xx.h"

#include "Uart_Driver.h"
#include "PLL_Driver.h"
#include "Ports_init.h"
#include "Bootloader_Main.h"
#include "Boot_Transmit_uC_To_Tool.h"
#include "Backup_ram.h"
#include "NVS.h"
#include "NVS_Driver.h"
#include "NVM.h"
#include "NVM_Driver.h"

#include "Includes.h"
#include "Platform_Types.h"
#include "Buffer.h"
#include "Buffer_Config.h"
#include "ComIf.h"
#include "ComIf_Config.h"
#include "Debug.h"

extern void Init(void);
#endif