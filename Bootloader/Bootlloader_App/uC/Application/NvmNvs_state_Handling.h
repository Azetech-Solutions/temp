#ifndef __NVMNVS_STATE_HANDLING_H__
#define __NVMNVS_STATE_HANDLING_H__

#include "Ports_init.h"

typedef enum
{
	NVM_IdleState = 0,
	NVM_UpdateState,
	NVM_ClearState,
	NVM_GetAllDataState,
	NVM_ReorgState,
	NVM_UpdateAllState,
	READ_VersionState,
	NVS_UpdateState,
	NVS_LastAddressState
}NVM_State_EN;

/************* NVM CMDs *************/
#define NVM_GETALLDATACMD			0xE1
#define NVM_UPDATECMD					0xE2
#define NVM_CLEARCMD					0xE3
#define NVM_UPDATEALLCMD			0xE4
#define NVM_REORGCMD					0xE5

#define GETAPPVERSIONCMD      0xD0
#define NVS_UPDATECMD					0xFA
#define NVS_LASTADDRESSCMD    0xD1

extern void NVM_NVS_Main(void);
#endif