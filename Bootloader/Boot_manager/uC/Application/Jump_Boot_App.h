
#ifndef __JUMP_BOOT_APP_H__
#define __JUMP_BOOT_APP_H__

#include "main.h"

#define App1_BaseAdd										0x08006000U
#define App2_BaseAdd										0x08016000U

#define APP_1_ADDRESS										0x08006080U
#define APP_2_ADDRESS										0x08016080U
#define BOOTLOADER_ADDRESS							0x08002000U


typedef void (*FPtr)(void);

extern void Jump_BOOTLOADER(void);
extern void Jump_APP_1(void);
extern void Jump_APP_2(void);
extern void RCC_DeInit(void);
extern void disable_interrupt(void);
extern void S_DeInit(void);

#endif