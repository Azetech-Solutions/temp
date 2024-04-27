#include "Backup_ram.h"

void PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->DBPCR, PWR_DBPCR_DBP);
}

void PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->DBPCR, PWR_DBPCR_DBP);
}

void PWREx_EnableBkupRAM_REG(void)
{
  SET_BIT(PWR->BDCR, PWR_BDCR_BREN);
}

void bkSRAM_ReadVariable(uint32_t read_adress, uint32_t* read_data)
{
		PWR_EnableBkUpAccess();

		BKPRAM_CLK_ENABLE();

		*read_data =  *(uint32_t*) (read_adress);

		BKPRAM_CLK_DISABLE();

		PWR_DisableBkUpAccess();
}

void bkSRAM_WriteVariable(uint32_t write_adress,uint32_t vall)
{
		PWR_EnableBkUpAccess();
		BKPRAM_CLK_ENABLE();
		*(__IO uint32_t*)write_adress = vall ;
//	       SCB_CleanDCache_by_Addr((uint32_t *)(0x38800000 + write_adress),8);
		BKPRAM_CLK_DISABLE();

		PWR_DisableBkUpAccess();
}
void bkSRAM_Init(void)
{
		FLASH_Unlock();

		/*DBP : Enable access to Backup domain */
		PWR_EnableBkUpAccess();
		BKPRAM_CLK_ENABLE();

		/*BRE : Enable backup regulator
			BRR : Wait for backup regulator to stabilize */

		PWREx_EnableBkupRAM_REG();
	 /*DBP : Disable access to Backup domain */
		BKPRAM_CLK_DISABLE();

		PWR_DisableBkUpAccess();

		FLASH_Lock();
}