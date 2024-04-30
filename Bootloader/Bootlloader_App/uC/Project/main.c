#include "main.h"

static uint32_t Boot_or_App;
char arr[] ={"7;;315?<08006000000000000000000000000000000000009<7="};
void delay();
int main()
{
	Init();
	
	bkSRAM_ReadVariable(BkUpRam_Verify_App_ADD,&Boot_or_App);
	
	if(Boot_or_App == 0x0B0B0B0B)
	{
		Debug_SendString("vfy_bkp");
		Boot_TxByte_ST *Tx = &Boot_Tx_Data;
		Tx->Boot_Status =0x0C;
		Boot_Res_Status();
		bkSRAM_WriteVariable(BkUpRam_Verify_App_ADD,BkupRam_ADD_Clear);
	}
	
//	uint32_t *ptr;
//	NVS_Block_Data_Read(1,&ptr);
	
//	ComIf_RxIndication_Boot(arr,strlen(arr));
	while(1)
	{
		delay();
		USART3_Main();
		Boot_Main();
		Debug_MainFunction();
		delay();
	}
}
void delay()
{
	unsigned int i;
	for(i=0;i<800000;i++);
}

void Init(void)
{
	FLASH_init();
	Buffer_Init();
	bkSRAM_Init();
	Total_NVM_Block_No = Chk_NVMTotal_Block();
	GpioClockEnable();
	Uart3_Init();
	NVS_Init();
	NVM_Init();
	Read_Apps_Header();
}