#include "NvmNvs_state_Handling.h"
#include "Flowcontrol.h"

static uint8_t FC_CMD;

static NVM_State_EN NVMStateControl = NVM_IdleState;//NVM_IdleState;//NVM_UpdateAllState;

void NVM_NVS_Main(void)
{
	NVM_Data_Config_ST *Nvm = &NVM_Block;
	FC_RxData_ST *FcRx = &FC_RxData;
	FlowControl_ST *FlowControlFlags = &FCManage;
	Boot_TxByte_ST *Tx = &Boot_Tx_Data;


		switch(NVMStateControl)
		{
			case NVM_IdleState:
			{
				if(FlowControlFlags->FCFlag.FcRxFlag == TRUE)
				{ //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
					FC_CMD = TOGET_CMD(FcRx->LengthMSB1,FcRx->FrameType);
					Nvm->NVM_CtrlFlg.IsNVMTrg = TRUE;  // main block handled
					
					if(FC_CMD == NVM_GETALLDATACMD) {
						NVMStateControl = NVM_GetAllDataState;
						
						FlowControlFlags->FCPreviousAddress = TOGET_MEMORYADDRESS(FcRx->FCData[0],FcRx->FCData[1],FcRx->FCData[2],FcRx->FCData[3]);
					}
					else if(FC_CMD == NVM_UPDATECMD) {
						
						NVMStateControl = NVM_UpdateState;
					}
					else if(FC_CMD == NVM_CLEARCMD) {
						Nvm->NVM_CtrlFlg.IsClearTrg = TRUE;
						NVMStateControl = NVM_ClearState;
					}
					else if(FC_CMD == NVM_UPDATEALLCMD) {
						
						NVMStateControl = NVM_UpdateAllState;
						
						FlowControlFlags->FCPreviousAddress = TOGET_MEMORYADDRESS(FcRx->FCData[0],FcRx->FCData[1],FcRx->FCData[2],FcRx->FCData[3]);
						
						Tx->Boot_Status = BOOT_STATUS_OK;
						BOOT_RES_STATUS();
					}
					else if(FC_CMD == NVM_REORGCMD) {
						Nvm->NVM_CtrlFlg.IsReorgTrg = TRUE;
						NVMStateControl = NVM_ReorgState;
					}
					else if(FC_CMD == GETAPPVERSIONCMD)
					{
						NVMStateControl = READ_VersionState;
					}
					else if(FC_CMD == NVS_UPDATECMD)
					{
						NVMStateControl = NVS_UpdateState;
						
						FlowControlFlags->FCPreviousAddress = TOGET_MEMORYADDRESS(FcRx->FCData[0],FcRx->FCData[1],FcRx->FCData[2],FcRx->FCData[3]);
						
						Tx->Boot_Status = BOOT_STATUS_OK;
						BOOT_RES_STATUS();
					}
					else if (FC_CMD == NVS_LASTADDRESSCMD)
					{
						NVMStateControl = NVS_LastAddressState;
					}
					FlowControlFlags->FCFlag.FcRxFlag =  FALSE;
				}			
			}
			break;
			case NVM_UpdateState:
			{
					if( NvmTool_Update())
					{
						Tx->Byte = BOOT_STATUS_OK; NVMStateControl = NVM_IdleState; BOOT_RES_STATUS();
					}
					else { NVMStateControl = NVM_IdleState;  Tx->Byte = BOOT_STATUS_NOT_OK; BOOT_RES_STATUS(); }
			}
			break;
			case NVM_ClearState:
			{					
				if( NVMToolClear() ) 
				{
					Tx->Byte = BOOT_STATUS_OK; 						
					NVMStateControl = NVM_IdleState;
					BOOT_RES_STATUS();
				}
				else {
							 NVMStateControl = NVM_IdleState;
							 Tx->Byte = BOOT_STATUS_NOT_OK; 
							 BOOT_RES_STATUS(); }
			}
			break;
			case NVM_ReorgState:
			{				
				if( NVM_ReOrg() )
				{
					Tx->Byte = BOOT_STATUS_OK;
					NVMStateControl = NVM_IdleState;
					BOOT_RES_STATUS();
				}
				else {
							 NVMStateControl = NVM_IdleState;
							 Tx->Byte = BOOT_STATUS_NOT_OK;
							 BOOT_RES_STATUS(); }
			}
			break;
			case NVM_UpdateAllState:
			{ 
				if(FCData_Receive())
				{
					NVMStateControl = NVM_IdleState;
				}
			}
			break;
			case NVM_GetAllDataState:
			{
				if(FCData_Transmit())
				{
					NVMStateControl = NVM_IdleState;
				}				
			}
			break;
			case READ_VersionState:
			{
				if(Read_AppVersion( TOGET_MEMORYADDRESS(FcRx->FCData[0],FcRx->FCData[1],FcRx->FCData[2],FcRx->FCData[3]) ))
				{
					NVMStateControl = NVM_IdleState;
				}				
			}
			break;
			case NVS_UpdateState:
			{
				//FlowControlFlags->FCPreviousAddress = 0x08010000;
				if(FCData_Receive())
				{
					NVMStateControl = NVM_IdleState;
				}
			}
			break;
			case NVS_LastAddressState:
			{
				if(find_NvsNextblockAddress())
				{
					NVMStateControl = NVM_IdleState;
				}
			}
			break;
		} // nvmstate end			
}