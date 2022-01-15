/*******************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : EcuStartup.c
* Module Description: AUTOSAR Startup Sequence
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*******************************************************************************/
/*******************************************************************************
* Version Control:
* %version:          8 %
* %derived_by:       nzx5jd %
*******************************************************************************/
/*******************************************************************************
* Change History:
* Date      Rev      Author    Change Description
* --------  -------  --------  ------------------------------------------------
* 06/25/13   1       OT        Initial version
* 01/10/14   2       OT        Reintegrated startup functions
* 01/24/14   3       OT        Added over voltage threshold interrupt enable
* 04/21/14   4       OT        Added DMA init function calls
* 11/17/14   4.1.1   OT        Integrated GliwaT1
* 11/17/14   6       OT        Merged previous versions
* 03/03/15   7       OT        Added MPU init for anomaly EA3#210
* 04/24/15   8       OT        Added suspend/resume functionality*
*******************************************************************************/


/*******************************************************************************
* Include files
*******************************************************************************/

#include "T1_AppInterface.h"
#include "Os.h"
#include "EcuM.h"

#include "Nhet.h"
#include "Ap_DfltConfigData.h"
#include "Interrupts.h"
#include "SystemTime.h"
#include "FlsTst.h"
#include "Lnk_Symbols.h"
#include "CDD_Func.h"
#include "ePWM.h"
#include "Gpt.h"
#include "Port.h"
#include "Fee.h"
#include "ApplCallbacks.h"
#include "Can.h"
#include "CanIf.h"
#include "Com.h"
#include "ComM.h"
#include "PduR.h"
#include "Dcm.h"
#include "CanSM_EcuM.h"
#include "CanTp.h"
#include "XcpProf.h"
#include "CanXcp.h"
#include "Cd_FeeIf.h"
#include "Vmm.h"
#include "SpiNxt.h"
#include "Ap_ApXcp.h"
#include "NtWrap.h"
#include "uDiag.h"
#include "Dma.h"
#include "ti_fee.h" /* Required for suspend/resume erase API */


/*******************************************************************************
  * Name:        main
  * Description: 
  * Inputs:      None 
  * Outputs:     None
  *
*******************************************************************************/
int main(void)
{
	T1_AppInit();
	osInitialize();
	EcuM_Init();
}


/*******************************************************************************
  * Name:        EcuStartup_Init1
  * Description: Initialization executed prior to OS start  
  * Inputs:      None 
  * Outputs:     None
  *
*******************************************************************************/
void EcuStartup_Init1(void) 
{
	ComM_InitMemory();
	Dma_Init();
	FlsTst_Init(&FlsTst_Runtime);
	uDiagCCRM_Init();
	uDiagClockMonitor_Init();
	uDiagECC_Init();
	uDiagESM_Init();
	uDiagIOMM_Init();
	uDiagParity_Init();
	uDiagPeriphMPU_Init();
	uDiagStaticRegs_Init();
	uDiagVIM_Init();
	Nhet_Init1();
	ePWM_Init1();
	SpiNxt_Init();
	Dma_SetupMtrCtrlGroups();
}


/*******************************************************************************
  * Name:        EcuStartup_Init2
  * Description: Initialization executed after OS start, prior to RTE start
  * Inputs:      None 
  * Outputs:     None
  *
*******************************************************************************/
void EcuStartup_Init2(void)
{
	ApXcp_Init();
	Dem_PreInit();
	Gpt_Init(&Gpt_Runtime);
	SystemTime_Init();
	TWrapC_Adc_Init(NULL_PTR);
	TWrapC_Adc2_Init1();
	TWrapC_PwmCdd_Init();
	Gpt_EnableNotification(SystemTime_uS);
	EnableCRCInterrupt();
	TWrapC_FeeIf_Init();
	Port_Init(&Port_Runtime);
	NvM_Init();
	TWrapC_TI_Fee_SuspendResumeErase(Suspend_Erase);
	NvM_ReadAll();
	Appl_WaitNvMReady(0, TRUE);
	TWrapC_TI_Fee_SuspendResumeErase(Resume_Erase);
	TWrapC_StaMd_Init0();
	DfltConfigData_Init1();
	TWrapC_NvMProxy_Init();
    EnableOverVoltThreshInterrupt();
	Dem_Init();
	Can_Init(&CanConfigSet);
	CanIf_Init(&CanIfInitConfiguration);
	CanSM_Init();
	CanTp_Init();
	Com_Init(&ComConfig);
	ComM_Init();
	XcpInit();
	CanXcp_Init(NULL_PTR);
	PduR_Init(&PduRGlobalConfig);
	Dcm_Init();
	Vmm_InitMemory();
	Vmm_Init();
	EnableCanInterrupt();
}

