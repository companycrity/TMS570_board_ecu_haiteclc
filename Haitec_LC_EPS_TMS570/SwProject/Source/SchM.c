/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : SchM.c
* Module Description: AUTOSAR BSW Scheduler
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/*******************************************************************************
* Version Control:
* Date Created:      Wed Jul 17 12:00:00 2013
* %version:          EA3#13 %
* %derived_by:       nzx5jd %
* %date_modified:    Fri Feb 21 14:21:36 2014 %
*******************************************************************************/
/*******************************************************************************
* Change History:
* Date      Rev      Author    Change Description
* --------  -------  --------  ------------------------------------------------
* 07/17/13   1       OT        Initial Haitec version
* 07/29/13   2       OT        Added Fee main function call
* 08/02/13   3       OT        Updated CanSM header for compiler warnings
* 08/10/13   4       OT        Integrated Vmm
* 08/23/13   5       OT        Restructured SchM for application split
* 09/17/13   6       OT        Added CMS periodic to 10ms task
* 01/08/14   7       OT        Migrated Wdg Init runnables to trusted functions
* 02/21/14   8       OT        Added resource scheduler calls for init timing
* 11/17/14   9.1.1   OT        Integrated GliwaT1
* 08/25/15   12      OT        Changed timing on SchM task for faster XCP response
*******************************************************************************/


#include "Std_Types.h"
#include "Os.h"
#include "Interrupts.h"

#include "Can.h"
#include "CanSM_SchM.h"
#include "CanTp.h"
#include "Cd_NvMProxy.h"
#include "Com.h"
#include "ComM.h"
#include "Dcm.h"
#include "Dem.h"
#include "EcuM.h"
#include "EPS_DiagSrvcs_ISO.h"
#include "fee.h"
#include "FlsTst.h"
#include "T1_AppInterface.h"
#include "NtWrap.h"
#include "NvM.h"
#include "Rte_Ap_StaMd9.h"
#include "Wdg_TMS570LS3x_Lcfg.h"
#include "WdgM.h"
#include "WdgM_PBcfg.h"


#define SCHM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, AUTOMATIC) Task2msCounter_Cnt_M_u16;
#define SCHM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"


TASK(Task_SchM_100ms_0)
{
	Fee_MainFunction();
	TerminateTask();
}


TASK(Task_SchM_100ms_9)
{
	NvMProxy_MainFunction();
	NvM_MainFunction();
	TerminateTask();
}


TASK(Task_SchM_2ms_9)
{
	if( Task2msCounter_Cnt_M_u16 == 0u )
	{
		T1_AppHandler();
		Com_MainFunctionTx();
		EcuM_MainFunction();
	}
	
	Can_MainFunction_Read();
	
	if( Task2msCounter_Cnt_M_u16 == 0u )
	{
		CanSM_MainFunction();
		CanTp_MainFunction();
		Com_MainFunctionRx();
		ComM_MainFunction_0();
		Dem_MainFunction();
		Dcm_MainFunction();
		EPSDiagSrvcs_Task();
	}
	
	if( Task2msCounter_Cnt_M_u16 < 4u )
	{
		Task2msCounter_Cnt_M_u16++;
	}
	else
	{
		Task2msCounter_Cnt_M_u16 = 0u;
	}
	
	TerminateTask();
}


TASK(Task_SchM_4ms_0)
{
	WdgM_MainFunction();
	FlsTst_MainFunction();
	TerminateTask();
}


TASK(Task_SchM_Trns_9)
{
	StaMd9_Trns_DemShutdown();
	TerminateTask();
}


TASK(Task_SchM_Init_9)
{
	GetResource(RES_SCHEDULER);
	EcuM_StartupTwo();
	TWrapC_Wdg_TMS570LS3x_Init(&wdg_tms570ls3x_config);
	TWrapC_WdgM_Init(&WdgMConfig_Mode0);
	ReleaseResource(RES_SCHEDULER);
	ClearSysTickInterruptFlg();
	EnableSysTickInterrupt();
	TerminateTask();
}


TASK(Task_Bkgnd)
{
	while( TRUE )
	{
		T1_AppBgHandler();
	}
}

