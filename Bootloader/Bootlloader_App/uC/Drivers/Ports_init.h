#ifndef __PORTS_INIT__
#define __PORTS_INIT__

#include "stm32h5xx.h"   
#include "stm32h5xx_hal_gpio.h"

#include "NVM_Driver.h"

static void GpioclockEnable(void);
static void Uart3_IO_init(void);
extern void Init(void);
#endif