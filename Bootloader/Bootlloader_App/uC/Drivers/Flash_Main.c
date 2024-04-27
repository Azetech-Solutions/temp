
#include "Flash_Main.h"
#include "Bootloader_Main.h"

void FLASH_init(void)
{
	/* PWR Voltage Scalling */
	CLEAR_BIT(PWR->VOSCR,PWR_VOSCR_VOS);
	while(!(PWR->VOSSR & PWR_VOSSR_VOSRDY));
	SET_BIT(FLASH->ACR,FLASH_ACR_WRHIGHFREQ_0); 
	FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
}
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

/* Flash Read Function */
uint32_t Flash_Read(const uint32_t Address)
{
	uint32_t Data=0;
	Data = *(uint32_t*)Address;
	return Data;
}

/* Program Write Function */
void FLASH_Write(uint32_t Address, uint32_t Data)
{
	
	SET_BIT(FLASH->NSCR,FLASH_CR_PG); // Porgramming is Enabled
	
	*(__IO uint32_t*)Address = (__IO uint32_t)Data;
	
	CLEAR_BIT(FLASH->NSCR,FLASH_CR_PG); // Porgramming is Disabled
}

uint32_t Multi_Word_write(uint32_t Address,uint32_t *Data)
{
	volatile uint32_t End_Flash_Add =0,i=0;
	__disable_irq();
	FLASH_Unlock();
	
	Flash_Error_Check();
	
	while(i<4)
	{
		FLASH_Write(Address,(*Data++));
		Address +=4U;
		End_Flash_Add = Address;
		i++;
	}
	
	Flash_Error_Check();
	
	FLASH_Lock();
	__enable_irq();
	
	if(End_Flash_Add != 0U)
		return End_Flash_Add;
	else
		return FALSE;
}

uint8_t Flash_Error_Check()
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

/* Sector Erase Function */
uint8_t FLASH_Sector_Erase(uint8_t Sec,uint8_t Bnk)
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
		FLASH->NSCR &=~FLASH_CR_SNB;
		
		FLASH->NSCR |= (FLASH_CR_SER | FLASH_CR_BKSEL); // Sector Erase request
		FLASH->NSCR |= (Sec << FLASH_CR_SNB_Pos); // Select the Sector
		FLASH->NSCR |= FLASH_CR_START; // Start the Erase operation	
		retval = TRUE;
	}
	
	CLEAR_REG(FLASH->NSCR);
	return retval;
}

uint8_t Flash_SingleSec_Erase(uint8_t Sec,uint8_t Bnk)
{
	uint8_t retval = FALSE;
	FLASH_Unlock();
	Flash_Error_Check();
	
	if(FLASH_Sector_Erase(Sec,Bnk))
	{
		retval = TRUE;
	}
	
	Flash_Error_Check();
	FLASH_Lock();
	
	return retval;
}
uint8_t FLASH_Erase_NoofSectors(uint8_t Bnk)
{
	uint8_t retval = FALSE;
	FLASH_Unlock();
	Flash_Error_Check();
	
	if(Bnk == Bank1)
	{
		uint8_t Sec;
		for(Sec =3; Sec <= 7; Sec++)
		{
			FLASH_Sector_Erase(Sec,Bnk);
		}
		
		if(Verify_Sectors_Erase(APP1_START_ADDRESS))
		{
			retval = TRUE;
		}	
	}
	else if(Bnk == Bank2)
	{
		uint8_t Sec;
		for(Sec=10;Sec<=15;Sec++)
		{
			FLASH_Sector_Erase(Sec,Bnk);
		}
		
		if(Verify_Sectors_Erase(APP2_START_ADDRESS))
		{
			retval = TRUE;
		}	
	}
	
	Flash_Error_Check();
	FLASH_Lock();
	
	return retval;
}

/*Verify_page_Erase Function,it used to verify the memory Erase*/
uint32_t Verify_Sectors_Erase(uint32_t Address)
{
	if(Address == APP1_START_ADDRESS)
	{
			uint32_t *ptr =(uint32_t*)Address;
			uint32_t End_Address =(Address+0xA000);
	
			while((uint32_t)ptr<End_Address)
			{
				if(*ptr != 0xFFFFFFFF)
				{
					return 0;
				}
				ptr++;
			}
	}
	else if( Address == APP2_START_ADDRESS)
	{
			uint32_t *ptr =(uint32_t*)Address;
			uint32_t End_Address =(Address+0xC000);
	
			while((uint32_t)ptr<End_Address)
			{
				if(*ptr != 0xFFFFFFFF)
				{
					return 0;
				}
				ptr++;
			}
	}	
	return 1;
}