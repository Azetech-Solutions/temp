#ifndef __PORTS_INIT__
#define __PORTS_INIT__

#include "stm32h5xx.h"   
#include "stm32h5xx_hal_gpio.h"

extern void GpioClockEnable(void);
extern void Uart3_IO_init(void);

#endif