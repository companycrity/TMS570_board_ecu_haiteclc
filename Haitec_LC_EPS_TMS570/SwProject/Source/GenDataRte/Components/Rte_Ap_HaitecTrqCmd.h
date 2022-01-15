/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2011 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Components/Rte_Ap_HaitecTrqCmd.h
 *     Workspace:  C:/SynergyProjects/Haitec_LC_EPS_TMS570-nzx5jd/Haitec_LC_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_HAITECTRQCMD_H
# define _RTE_AP_HAITECTRQCMD_H

# ifndef RTE_CORE
#  ifdef RTE_APPLICATION_HEADER_FILE
#   error Multiple application header files included.
#  endif
#  define RTE_APPLICATION_HEADER_FILE
# endif

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"

# ifndef RTE_CORE

#  define RTE_START_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

/************************************************************************/
/* extern declaration of RTE buffers for optimized macro implementation */
/************************************************************************/
extern VAR(Float, RTE_VAR_INIT) Rte_MtrTempEst_AssistMechTempEst_DegC_f32;
extern VAR(Float, RTE_VAR_INIT) Rte_SignlCondn_VehicleSpeed_Kph_f32;

#  define RTE_STOP_SEC_VAR_Ap_10_INIT_UNSPECIFIED
#  include "MemMap.h"

# endif /* !defined(RTE_CORE) */


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

#  define Rte_InitValue_AssitMechTempEst_DegC_f32 (0.0F)
#  define Rte_InitValue_HwTrq_HwNm_f32 (0.0F)
#  define Rte_InitValue_MtrVelCRF_MtrRadpS_f32 (0.0F)
#  define Rte_InitValue_VehSpd_Kph_f32 (0.0F)
# endif


# ifndef RTE_CORE
#  define RTE_START_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"

/**********************************************************************************************************************
 * Buffers for implicit communication
 *********************************************************************************************************************/

extern VAR(Rte_tsTask_2ms_10, RTE_VAR_NOINIT) Rte_Task_2ms_10;

#  define RTE_STOP_SEC_VAR_Ap_10_NOINIT_UNSPECIFIED
#  include "MemMap.h"
# endif


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/

# define RTE_STOP_SEC_CODE
# include "MemMap.h"


# ifndef RTE_CORE

/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

#  define Rte_IRead_HaitecTrqCmd_Per1_AssitMechTempEst_DegC_f32() \
  (Rte_Task_2ms_10.Rte_RB.Rte_Ap_HaitecTrqCmd_HaitecTrqCmd_Per1.Rte_AssitMechTempEst_DegC_f32.value)

#  define Rte_IRead_HaitecTrqCmd_Per1_HwTrq_HwNm_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_Sweep_OutputHwTrq_HwNm_f32.value)

#  define Rte_IRead_HaitecTrqCmd_Per1_MtrVelCRF_MtrRadpS_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_MtrVel_MotorVelCRF_MtrRadpS_f32.value)

#  define Rte_IRead_HaitecTrqCmd_Per1_VehSpd_Kph_f32() \
  (Rte_Task_2ms_10.Rte_TB.Rte_I_SignlCondn_VehicleSpeed_Kph_f32.value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
#  define Rte_Read_AssitMechTempEst_DegC_f32 Rte_Read_Ap_HaitecTrqCmd_AssitMechTempEst_DegC_f32
#  define Rte_Read_Ap_HaitecTrqCmd_AssitMechTempEst_DegC_f32(data) (*(data) = Rte_MtrTempEst_AssistMechTempEst_DegC_f32, ((Std_ReturnType)RTE_E_OK))
#  define Rte_Read_VehSpd_Kph_f32 Rte_Read_Ap_HaitecTrqCmd_VehSpd_Kph_f32
#  define Rte_Read_Ap_HaitecTrqCmd_VehSpd_Kph_f32(data) (*(data) = Rte_SignlCondn_VehicleSpeed_Kph_f32, ((Std_ReturnType)RTE_E_OK))


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (unmapped) for synchronous C/S communication
 *********************************************************************************************************************/
#  define RTE_START_SEC_AP_ASTLMT_APPL_CODE
#  include "MemMap.h"
FUNC(Std_ReturnType, RTE_AP_ASTLMT_APPL_CODE) AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float MtrTrqCmd_MtrNm_f32);
#  define RTE_STOP_SEC_AP_ASTLMT_APPL_CODE
#  include "MemMap.h"

#  define Rte_Call_AstLmt_Scom_ManualTrqCmd AstLmt_Scom_ManualTrqCmd


# endif /* !defined(RTE_CORE) */


# define RTE_START_SEC_AP_HAITECTRQCMD_APPL_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * Runnable entities
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_Init1(void);

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_Per1(void);

FUNC(Std_ReturnType, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_SCom_StartCtrl(Float Param_ManTrqCmd_MtrNm_f32, Boolean Param_DefeatHwTrq_Cnt_lgc, Boolean Param_DefeatTemp_Cnt_lgc);

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_SCom_StopCtrl(void);

# define RTE_STOP_SEC_AP_HAITECTRQCMD_APPL_CODE
# include "MemMap.h"


# ifndef RTE_CORE
/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

#  define RTE_E_AssistLmtFunc_Scom_RTE_E_MtrTrqLmt_SCom_VSTH (34U)

#  define RTE_E_AssistLmtFunc_Scom_RTE_E_OK (1U)

#  define RTE_E_HaitecTrqCmd_SCom_E_NOT_OK (1U)
# endif /* !defined(RTE_CORE) */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */


#endif /* _RTE_AP_HAITECTRQCMD_H */
