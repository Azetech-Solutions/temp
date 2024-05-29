#ifndef __NVS_H__
#define __NVS_H__

#include "stm32h5xx.h"
#include "NVS_Driver.h"

/***************************NVS Part*************************/
#define NVS_TOTAL_BLOCKS						2
/*************************** NVS Address *************************/
#define NVS_START_ADDRESS  	0x08010000
#define NVS_END_ADDRESS  		0x08011FFC

#define NVS_BLOCK_SECTOR		0


/* to NVS force read
S Address
Block Size
index
*/
/* Block 1 */
#define NVS_BLOCK_ONE_START_ADD										(0x00)
#define NVS_BLOCK_ONE_BLOCK_SIZE 									(16U)
#define NVS_BLOCK_ONE_INDEX 											(0U)
#define NVS_BLOCK_ONE_GET_BUFFER()								((uint32_t*)Nvs_Block_data[NVS_BLOCK_ONE_INDEX])
#define NVS_BLOCK_ONE_TOTA_DATA_SUM()							(NVS_data_ChkSum((NVS_START_ADDRESS | NVS_BLOCK_ONE_START_ADD),(NVS_BLOCK_ONE_BLOCK_SIZE-2U)))
#define NVS_BLOCK_ONE_DATA_READ(x)								(NVS_Block_Data_Read(NVS_BLOCK_ONE_INDEX,x))
#define NVS_BLOCK_ONE_FORCE_READ() 								{	IsRead_Allow = TRUE;\
																										(Nvs_Block_Read((NVS_START_ADDRESS | NVS_BLOCK_ONE_START_ADD),NVS_BLOCK_ONE_INDEX)) }

/* Block 2 */
#define NVS_BLOCK_TWO_START_ADD										(0x40)
#define NVS_BLOCK_TWO_BLOCK_SIZE 									(36U)
#define NVS_BLOCK_TWO_INDEX 											(1U)
#define NVS_BLOCK_TWO_GET_BUFFER()								((uint32_t*)Nvs_Block_data[NVS_BLOCK_TWO_INDEX])
#define NVS_BLOCK_TWO_TOTA_DATA_SUM()							(NVS_data_ChkSum((NVS_START_ADDRESS | NVS_BLOCK_TWO_START_ADD),(NVS_BLOCK_TWO_BLOCK_SIZE-2U)))
#define NVS_BLOCK_TWO_DATA_READ(x)								(NVS_Block_Data_Read(NVS_BLOCK_TWO_INDEX,x))
#define NVS_BLOCK_TWO_FORCE_READ() 								 {	IsRead_Allow = TRUE; \
																											(Nvs_Block_Read((NVS_START_ADDRESS | NVS_BLOCK_TWO_START_ADD),NVS_BLOCK_TWO_INDEX)) }

/* Block 3 */
#define NVS_BLOCK_THREE_START_ADD										(0xD0)
#define NVS_BLOCK_THREE_BLOCK_SIZE 									(36U)
#define NVS_BLOCK_THREE_INDEX 											(2U)
#define NVS_BLOCK_THREE_GET_BUFFER()								((uint32_t*)Nvs_Block_data[NVS_BLOCK_THREE_INDEX])
#define NVS_BLOCK_THREE_TOTA_DATA_SUM()							(NVS_data_ChkSum((NVS_START_ADDRESS | NVS_BLOCK_THREE_START_ADD),(NVS_BLOCK_THREE_BLOCK_SIZE-2U)))
#define NVS_BLOCK_THREE_DATA_READ(x)								(NVS_Block_Data_Read(NVS_BLOCK_THREE_INDEX,x))
#define NVS_BLOCK_THREE_FORCE_READ() 								{	IsRead_Allow = TRUE;\
																											(Nvs_Block_Read((NVS_START_ADDRESS | NVS_BLOCK_THREE_START_ADD),NVS_BLOCK_THREE_INDEX)) }

/* Block 4 */
#define NVS_BLOCK_FOUR_START_ADD										(0x0160)
#define NVS_BLOCK_FOUR_BLOCK_SIZE 									(36U)
#define NVS_BLOCK_FOUR_INDEX 												(3U)
#define NVS_BLOCK_FOUR_GET_BUFFER()								  ((uint32_t*)Nvs_Block_data[NVS_BLOCK_FOUR_INDEX])
#define NVS_BLOCK_FOUR_TOTA_DATA_SUM()							(NVS_data_ChkSum((NVS_START_ADDRESS | NVS_BLOCK_FOUR_START_ADD),(NVS_BLOCK_FOUR_BLOCK_SIZE-2U)))
#define NVS_BLOCK_FOUR_DATA_READ(x)								  (NVS_Block_Data_Read(NVS_BLOCK_FOUR_INDEX,x))
#define NVS_BLOCK_FOUR_FORCE_READ() 								{	IsRead_Allow = TRUE;\
																											(Nvs_Block_Read((NVS_START_ADDRESS | NVS_BLOCK_FOUR_START_ADD),NVS_BLOCK_FOUR_INDEX)) }

/* Block 4 */
#define NVS_BLOCK_FIVE_START_ADD										(0x01F0)
#define NVS_BLOCK_FIVE_BLOCK_SIZE 									(40U)
#define NVS_BLOCK_FIVE_INDEX 												(4U)
#define NVS_BLOCK_FIVE_GET_BUFFER()								  ((uint32_t*)Nvs_Block_data[NVS_BLOCK_FIVE_INDEX])
#define NVS_BLOCK_FIVE_TOTA_DATA_SUM()							(NVS_data_ChkSum((NVS_START_ADDRESS | NVS_BLOCK_FIVE_START_ADD),(NVS_BLOCK_FIVE_BLOCK_SIZE-2U)))
#define NVS_BLOCK_FIVE_DATA_READ(x)								  (NVS_Block_Data_Read(NVS_BLOCK_FIVE_INDEX,x))
#define NVS_BLOCK_FIVE_FORCE_READ() 								{	IsRead_Allow = TRUE;\
																											(Nvs_Block_Read((NVS_START_ADDRESS | NVS_BLOCK_FIVE_START_ADD),NVS_BLOCK_FIVE_INDEX)) }

typedef struct __NVS_ID_LEN
{
	uint16_t NVS_ID;
	uint16_t NVS_Length;
	
}NVS_ID_Len_ST;

typedef struct _NVS_READ_DATA
{
	uint32_t Block_R_Number;
	NVS_ID_Len_ST NVS_R_ID_Len;
	uint32_t Block_R_Checksum;
	uint32_t *Block_R_Data;
	
}NVS_READ_DATA_ST;

typedef struct _NVS_STATUS_FLAG
{
	uint8_t RES :7;
	uint8_t Flag :1;
	
}NVS_STATUS_FLAG_ST;

typedef struct _NVS_DATA_CONFIG
{
	uint32_t Start_Address;
	uint32_t Block_Size;
	NVS_STATUS_FLAG_ST Sts_flg;
	NVS_ID_Len_ST NVS_ID_Len;
	uint32_t Block_Checksum;
	uint32_t *Data;
	
}NVS_DATA_CONFIG_ST;

extern NVS_DATA_CONFIG_ST  Nvs_Block_data[];
extern NVS_READ_DATA_ST  Nvs_Blk_Read[];


#endif 