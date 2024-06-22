
#include "Flash_Main.h"

/************************************************************/
void FLASH_init(void)
{
	/* PWR Voltage Scalling */
	CLEAR_BIT(PWR->VOSCR,PWR_VOSCR_VOS);
	while(!(PWR->VOSSR & PWR_VOSSR_VOSRDY));
	SET_BIT(FLASH->ACR,FLASH_ACR_WRHIGHFREQ_0); 
	FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
}
/************************************************************/
/* Flash UnLock Function */
void FLASH_Unlock(void)
{
  if(READ_BIT(FLASH->NSCR, FLASH_CR_LOCK) != 0U)
  {
    /* Authorize the FLASH Control Register access */
    WRITE_REG(FLASH->NSKEYR, FLASH_KEY1);
    WRITE_REG(FLASH->NSKEYR, FLASH_KEY2);

    /* Verify Flash CR is unlocked */
    if(READ_BIT(FLASH->NSCR, FLASH_CR_LOCK) != 0U)
    {
			//Do Nothig
    }
  }
}
/************************************************************/
/* Flash Lock Function */
void FLASH_Lock(void)
{
	SET_BIT(FLASH->NSCR, FLASH_CR_LOCK);
	
  /* Verify Flash is locked */
  if (READ_BIT(FLASH->NSCR, FLASH_CR_LOCK) == 0U)
  {
		//Do Nothing
  }
}
/************************************************************/
/* Flash Read Function */
uint32_t FLASH_Read(const uint32_t Address)
{
	return  *(uint32_t*)Address;;
}
/************************************************************/
/* Program Write Function */
void FLASH_Write(uint32_t Address, uint32_t Data)
{
	
	SET_BIT(FLASH->NSCR,FLASH_CR_PG); // Porgramming is Enabled
	
	*(__IO uint32_t*)Address = (__IO uint32_t)Data;
	
	CLEAR_BIT(FLASH->NSCR,FLASH_CR_PG); // Porgramming is Disabled
}
/************************************************************/
uint32_t Multi_Word_write(uint32_t Address,uint32_t *Data)
{
	volatile uint32_t EnAdd =0,i=0;
	__disable_irq();
	FLASH_Unlock();
	
	FLASH_ErrorChk();
	
	while(i<4)
	{
		FLASH_Write(Address,(*Data++));
		Address +=4U;
		EnAdd = Address;
		i++;
	}
	
	FLASH_ErrorChk();
	
	FLASH_Lock();
	__enable_irq();
	
	if(EnAdd != 0U)
		return EnAdd;
	else
		return FALSE;
}
/************************************************************/
/* This is used for check the error during flash programming or erasing */
uint8_t FLASH_ErrorChk()
{
	uint8_t retval = 0;
	while((FLASH->NSSR & (FLASH_SR_BSY  | FLASH_SR_WBNE | FLASH_SR_DBNE))); // check the Flags
	
	/* Check the Errors */
	if(READ_BIT(FLASH->NSSR,( FLASH_SR_PGSERR| FLASH_SR_INCERR |FLASH_SR_WRPERR | FLASH_SR_STRBERR)))
	{
		SET_BIT(FLASH->NSCCR,( FLASH_SR_PGSERR| FLASH_SR_INCERR |FLASH_SR_WRPERR | FLASH_SR_STRBERR));
	}
	
	if(READ_BIT(FLASH->NSSR ,FLASH_SR_EOP) != 0U)
	{
		FLASH->NSCCR = FLASH_SR_EOP;
	}
	retval = 1;
	
	return retval;
}	
/************************************************************/
/* Sector Erase Function */
uint8_t FLASH_SecErase(uint8_t Sec,uint8_t Bnk)
{
	uint8_t retval = FALSE;
	
	if(Bnk == 0)
	{
		FLASH->NSCR &=~(FLASH_CR_SNB | FLASH_CR_BKSEL);
		
		FLASH->NSCR |= FLASH_CR_SER; // Sector Erase request
		FLASH->NSCR |= (Sec << FLASH_CR_SNB_Pos); // Select the Sector
		FLASH->NSCR |= FLASH_CR_START; // Start the Erase operation	
		retval = TRUE;
	}
	else
	{
		FLASH->NSCR &=~(FLASH_CR_SNB |FLASH_CR_BKSEL);
		
		FLASH->NSCR |= (FLASH_CR_SER | FLASH_CR_BKSEL); // Sector Erase request
		FLASH->NSCR |= (Sec << FLASH_CR_SNB_Pos); // Select the Sector
		FLASH->NSCR |= FLASH_CR_START; // Start the Erase operation	
		retval = TRUE;
	}
	
	CLEAR_REG(FLASH->NSCR);
	return retval;
}
/************************************************************/
uint8_t Flash_SingleSec_Erase(uint8_t Sec,uint8_t Bnk)
{
	uint8_t retval = FALSE;
	FLASH_Unlock();
	FLASH_ErrorChk();
	
	if(FLASH_SecErase(Sec,Bnk))
	{
		retval = TRUE;
	}
	
	FLASH_ErrorChk();
	FLASH_Lock();
	
	return retval;
}

uint8_t Flash_DoubleSec_Erase(uint8_t Sec,uint8_t Bnk)
{
	uint8_t retval= FALSE;
	FLASH_Unlock();
	FLASH_ErrorChk();
	
	
	if(Bnk ==  BANK_1)
	{
		uint8_t i;
		uint8_t EndSec = Sec+1;;
		for(i = Sec; i <= EndSec; i++)
		{
			FLASH_SecErase(Sec,Bnk);
		}
		retval = TRUE;
	}
	else if(Bnk == BANK_2)
	{
		uint8_t i;
		uint8_t EndSec = Sec+1;;
		for(i = Sec; i <= EndSec; i++)
		{
			FLASH_SecErase(Sec,Bnk);
		}
		retval = TRUE;
	}
	
	FLASH_ErrorChk();
	FLASH_Lock();
	
	return retval;
	
}

uint8_t FLASH_Erase_NoofSectors(uint8_t Bnk)
{
	uint8_t retval = FALSE;
	FLASH_Unlock();
	FLASH_ErrorChk();
	
	if(Bnk == BANK_1)
	{
		uint8_t Sec;
		for(Sec =3; Sec <= 7; Sec++)
		{
			FLASH_SecErase(Sec,Bnk);
		}
		
		if(VerifyFlashErase(APP_1_BASE_ADDRESS,APP_1_END_ADDRESS))
		{
			retval = TRUE;
		}	
	}
	else if(Bnk == BANK_2)
	{
		uint8_t Sec;
		for(Sec=3;Sec<=7;Sec++)
		{
			FLASH_SecErase(Sec,Bnk);
		}
		
		if(VerifyFlashErase(APP_2_BASE_ADDRESS,APP_2_END_ADDRESS))
		{
			retval = TRUE;
		}	
	}
	
	FLASH_ErrorChk();
	FLASH_Lock();
	
	return retval;
}
/************************************************************/
/*Verify_page_Erase Function,it used to verify the memory Erase*/
uint8_t VerifyFlashErase(uint32_t StAdd,uint32_t EnAdd)
{
	uint32_t *ptr =(uint32_t*)StAdd;

		while((uint32_t)ptr<EnAdd)
		{
			if(*ptr != 0xFFFFFFFF)
			{
				return 0;
			}
			ptr++;
		}	
		
	return 1;
}