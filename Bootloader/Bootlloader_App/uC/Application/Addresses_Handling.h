#ifndef __Addresses_Handling_H__
#define __Addresses_Handling_H__


/******************* BootManager & BootLoader **************/

/************* BootManager *************/
#define BOOTMANAGER_BASE_ADDRESS						0x08000000U
#define BOOTMANAGER_END_ADDRESS							0x08002000U
#define BOOTMANAGER_SECTOR_SIZE							0x2000
/************* BootLoader *************/
#define BOOTLOADER_BASE_ADDRESS							0x08002000U
#define BOOTLOADER_END_ADDRESS							0x08006000U
#define BOOTLOADER_SECTOR_SIZE							0x4000
/************************************************************/

/*******************Application Part*************************/
/************* Application 1 *************/
#define APP_1_BASE_ADDRESS										0x08006000U
#define APP_1_END_ADDRESS											0x08010000U
#define APP_1_SECTOR_SIZE											0xA000
/************* Application 2 *************/
#define APP_2_BASE_ADDRESS										0x08016000U
#define APP_2_END_ADDRESS											0x08020000U
#define APP_2_SECTOR_SIZE											0xA000
/************* Application Header *************/
#define TOTAL_VERSION_HEADER									2U
#define HEADER_APP_1													0U
#define HEADER_APP_2													1U

/************************************************************/

/***************************NVM Part*************************/
												/* NVM Sector 1 */
#define NVM_SECTOR_ONE_START_ADDRESS						0x08012000
#define NVM_SECTOR_ONE_END_ADDRESS							0x08014000
												/* NVM Sector 2 */
#define NVM_SECTOR_TWO_START_ADDRESS						0x08014000
#define NVM_SECTOR_TWO_END_ADDRESS							0x08016000
												/* NVM Sectors */
#define NVM_BASE_ADDRESS												0x08012000
#define NVM_END_ADDRESS													0x08016000
#define NVM_SECTOR_SIZE													0x4000

#define NVM_SECTOR_ONE													1U
#define NVM_SECTOR_TWO													2U

#define NVM_DATA_BLOCK_SIZE											4U
#define NVM_ONE_BLOCK_SIZE 											8U

/************************************************************/
/*************************** NVS Address ********************/
#define NVS_BASE_ADDRESS  											 0x08010000
#define NVS_END_ADDRESS  												 0x08012000
#define NVS_SECTOR_SIZE													 0x2000

#define NVS_BLOCK_SECTOR												 0U
/************************************************************/


#endif