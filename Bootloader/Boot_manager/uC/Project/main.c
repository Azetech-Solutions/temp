
#include "main.h"

static uint32_t jumping_var,jump_Flag;
uint8_t val;
int main()
{
	Init();
	
	Check_App_Header_ST *App1 = &Ck_Hdr[HEADER_APP_1];
	Check_App_Header_ST *App2 = &Ck_Hdr[HEADER_APP_2];
	NVM_Block_Read_ST *Check_app1_2 = &NVM_last_block;
	
	/* Verify the jump place to app1, app2 or boot */
	bkSRAM_ReadVariable(BKRAM_JUMP_VERIFY_ADD,&jumping_var);
//	bkSRAM_ReadVariable(BKRAM_JUMP_VALIDATE_FLAG,&jump_Flag); // to validate the app
//	uint32_t *ptr;
//	NVS_Block_Data_Read(1,&ptr);
	
	if(jumping_var == 0xAAAAAAAA)
	{
		if(App1->Ck_cksum == App_Image_Chksum_calculation((App1->Header_start_Add+128U)))
		{
			bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_APP_WRITE_VALUE);
			Jump_APP_1();
		}
		else if(App2->Ck_cksum == App_Image_Chksum_calculation(App2->Header_start_Add+128U))
		{
			bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_APP_WRITE_VALUE);
			Jump_APP_2();
		}
		else 
		{
			if(IsBoot_valid() != 0U)
			{
				bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_BOOT_WRITE_VALUE);
				Jump_BOOTLOADER();
			}
		}
	}
	else if(jumping_var == 0xBBBBBBBB)
	{
		if(IsBoot_valid() != 0U)
		{
			bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_BOOT_WRITE_VALUE);
			Jump_BOOTLOADER();
		}
	}
	else if(jumping_var <= 0xFFFFFFFF && jumping_var >=0x00000000)
	{
		if(Check_app1_2->NVM_R_Data[0] == 0xAAAA1111)
		{
			if(App1->Ck_cksum == App_Image_Chksum_calculation((App1->Header_start_Add+128U)))
			{
				bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_APP_WRITE_VALUE);
//				bkSRAM_WriteVariable(BKRAM_JUMP_VALIDATE_FLAG,0xAAAA1111);
				Jump_APP_1();
			}
			else if(App2->Ck_cksum == App_Image_Chksum_calculation(App2->Header_start_Add+128U))
			{
				if(Update_Nvm_Block(App2_BaseAdd))
				{	
					bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_APP_WRITE_VALUE);
//					bkSRAM_WriteVariable(BKRAM_JUMP_VALIDATE_FLAG,0xAAAA2222);					
					Jump_APP_2();
				}
			}
			else 
			{
				if(IsBoot_valid() != 0U)
				{
					bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_BOOT_WRITE_VALUE);
					Jump_BOOTLOADER();
				}
			}
		}
		else if(Check_app1_2->NVM_R_Data[0] == 0xAAAA2222)
		{
			if(App2->Ck_cksum == App_Image_Chksum_calculation(App2->Header_start_Add+128U))
			{
				bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_APP_WRITE_VALUE);
//				bkSRAM_WriteVariable(BKRAM_JUMP_VALIDATE_FLAG,0xAAAA2222);				
				Jump_APP_2();
			}		
			else if(App1->Ck_cksum == App_Image_Chksum_calculation((App1->Header_start_Add+128U)))
			{					
				if(Update_Nvm_Block(App1_BaseAdd))
				{
					bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_APP_WRITE_VALUE);
//					bkSRAM_WriteVariable(BKRAM_JUMP_VALIDATE_FLAG,0xAAAA1111);
					Jump_APP_1();
				}						
			}
			else 
			{
				if(IsBoot_valid() != 0U)
				{
					bkSRAM_WriteVariable(BKRAM_JUMP_UpdateApp_ADD,ISJUMP_BOOT_WRITE_VALUE);
					Jump_BOOTLOADER();
				}
			}
		}
			
	}
	
	while(1);
}

void Init(void)
{
	bkSRAM_Init();
	val= Chk_NVMTotal_Block();
	NVS_Init();
	NVM_Init();
	Read_Apps_Header();
//	Gpio_init();
}

void Gpio_init(void)
{
	PORTA_CLOCK_ENABLE();
	
	GPIO_InitTypeDef PA1 ={0};
	/* For Check the Pin to move bootloader or App */
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
	
	PA1.Pin = GPIO_PIN_1;
	PA1.Mode = GPIO_MODE_OUTPUT_PP;
	PA1.Pull = GPIO_NOPULL;
	PA1.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA,&PA1);
	
}