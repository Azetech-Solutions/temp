#ifndef __PORTS_INIT__
#define __PORTS_INIT__

#include "stm32h5xx.h"   
#include "stm32h5xx_hal_gpio.h"

#include "Backup_ram.h"
#include "NVS_Driver.h"
#include "NVM_Driver.h"
#include "Debug.h"
#include "PLL_Driver.h"

extern void GpioclockEnable(void);
extern void Uart3_IO_init(void);

#endif