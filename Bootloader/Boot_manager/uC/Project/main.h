#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32h5xx.h"
#include "stm32h503xx.h"

#include "stm32h5xx_hal_gpio.h"

#include "Flash_Main.h"
#include "Backup_ram.h"

#include "Jump_Boot_App.h"
#include "Validate_file.h"

#include "NVS_Driver.h"
#include "NVM_Driver.h"

#define HSI_VALUE    (64000000UL)

#define __HAL_FLASH_SET_LATENCY(__LATENCY__)    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (__LATENCY__))
#define __HAL_FLASH_GET_LATENCY()               READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY)

#define GPIOA_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN)
#define GPIOB_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN)
#define GPIOC_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN)
#define GPIOD_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIODEN)
#define GPIOH_CLK_DISABLE()          CLEAR_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOHEN)

#define AHB1_FORCE_RESET()      WRITE_REG(RCC->AHB1RSTR, 0x010AD003U)
#define AHB1_RELEASE_RESET()    WRITE_REG(RCC->AHB1RSTR, 0x00000000U)

#define AHB2_FORCE_RESET()      WRITE_REG(RCC->AHB2RSTR, 0x001F1DFFU)
#define AHB2_RELEASE_RESET()    WRITE_REG(RCC->AHB2RSTR, 0x00000000U)

#define APB1_FORCE_RESET()     do { \
                                                 WRITE_REG(RCC->APB1LRSTR, 0xDFFEC1FFU); \
                                                 WRITE_REG(RCC->APB1HRSTR, 0x4080062BU); \
                                               } while(0)

#define APB1_RELEASE_RESET()   do { \
                                                 WRITE_REG(RCC->APB1LRSTR, 0x00000000U); \
                                                 WRITE_REG(RCC->APB1HRSTR, 0x00000000U); \
                                               } while(0)

#define APB2_FORCE_RESET()          WRITE_REG(RCC->APB2RSTR, 0x017F7800U)
#define APB2_RELEASE_RESET()        WRITE_REG(RCC->APB2RSTR, 0x00000000U)

#define APB3_FORCE_RESET()           WRITE_REG(RCC->APB3RSTR, 0x001008E0U)
#define APB3_RELEASE_RESET()         WRITE_REG(RCC->APB3RSTR, 0x00000000U)
																							 
#define BKRAM_JUMP_VERIFY_ADD						0x40036400
#define BKRAM_JUMP_UpdateApp_ADD				0x40036404
#define BKRAM_JUMP_VALIDATE_FLAG				0x40036408
																							 
#define ISJUMP_APP_WRITE_VALUE					0x0A0A0A0A
#define ISJUMP_BOOT_WRITE_VALUE					0x0B0B0B0B

/* Function Declaration */
extern void Gpio_init(void);
extern void Init(void);
#endif 