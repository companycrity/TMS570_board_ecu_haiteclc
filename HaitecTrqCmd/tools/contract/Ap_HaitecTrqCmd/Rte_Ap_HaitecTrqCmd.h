/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2010 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_Ap_HaitecTrqCmd.h
 *     Workspace:  C:/HaitecTrqCmd/HaitecTrqCmd/autosar
 *     SW-C Type:  Ap_HaitecTrqCmd
 *  Generated at:  Tue Sep  8 16:11:48 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Application header file for SW-C <Ap_HaitecTrqCmd> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_HAITECTRQCMD_H
# define _RTE_AP_HAITECTRQCMD_H

# ifdef RTE_APPLICATION_HEADER_FILE
#  error Multiple application header files included.
# endif
# define RTE_APPLICATION_HEADER_FILE

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

/* include files */

# include "Rte_Type.h"

typedef P2CONST(struct Rte_CDS_Ap_HaitecTrqCmd, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_AssitMechTempEst_DegC_f32 ((Float)0)
# define Rte_InitValue_HwTrq_HwNm_f32 ((Float)0)
# define Rte_InitValue_MtrVelCRF_MtrRadpS_f32 ((Float)0)
# define Rte_InitValue_VehSpd_Kph_f32 ((Float)0)


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Ap_HaitecTrqCmd_AssitMechTempEst_DegC_f32(P2VAR(Float, AUTOMATIC, RTE_AP_HAITECTRQCMD_APPL_VAR) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Ap_HaitecTrqCmd_VehSpd_Kph_f32(P2VAR(Float, AUTOMATIC, RTE_AP_HAITECTRQCMD_APPL_VAR) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_HaitecTrqCmd_AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float ManTrqCmd_MtrNm_f32);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

# define Rte_IRead_HaitecTrqCmd_Per1_AssitMechTempEst_DegC_f32() \
  (Rte_Inst_Ap_HaitecTrqCmd->HaitecTrqCmd_Per1_AssitMechTempEst_DegC_f32->value)

# define Rte_IRead_HaitecTrqCmd_Per1_HwTrq_HwNm_f32() \
  (Rte_Inst_Ap_HaitecTrqCmd->HaitecTrqCmd_Per1_HwTrq_HwNm_f32->value)

# define Rte_IRead_HaitecTrqCmd_Per1_MtrVelCRF_MtrRadpS_f32() \
  (Rte_Inst_Ap_HaitecTrqCmd->HaitecTrqCmd_Per1_MtrVelCRF_MtrRadpS_f32->value)

# define Rte_IRead_HaitecTrqCmd_Per1_VehSpd_Kph_f32() \
  (Rte_Inst_Ap_HaitecTrqCmd->HaitecTrqCmd_Per1_VehSpd_Kph_f32->value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Read_AssitMechTempEst_DegC_f32 Rte_Read_Ap_HaitecTrqCmd_AssitMechTempEst_DegC_f32
# define Rte_Read_VehSpd_Kph_f32 Rte_Read_Ap_HaitecTrqCmd_VehSpd_Kph_f32


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_AstLmt_Scom_ManualTrqCmd Rte_Call_Ap_HaitecTrqCmd_AstLmt_Scom_ManualTrqCmd




# define RTE_START_SEC_AP_HAITECTRQCMD_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: HaitecTrqCmd_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_Init1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HaitecTrqCmd_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_HaitecTrqCmd_Per1_AssitMechTempEst_DegC_f32(void)
 *   Float Rte_IRead_HaitecTrqCmd_Per1_HwTrq_HwNm_f32(void)
 *   Float Rte_IRead_HaitecTrqCmd_Per1_MtrVelCRF_MtrRadpS_f32(void)
 *   Float Rte_IRead_HaitecTrqCmd_Per1_VehSpd_Kph_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float ManTrqCmd_MtrNm_f32)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_Per1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HaitecTrqCmd_SCom_StartCtrl
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <StartCtrl> of PortPrototype <HaitecTrqCmd_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_AssitMechTempEst_DegC_f32(Float *data)
 *   Std_ReturnType Rte_Read_VehSpd_Kph_f32(Float *data)
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType HaitecTrqCmd_SCom_StartCtrl(Float Param_ManTrqCmd_MtrNm_f32, Boolean Param_DefeatHwTrq_Cnt_lgc, Boolean Param_DefeatTemp_Cnt_lgc)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_HaitecTrqCmd_SCom_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_SCom_StartCtrl(Float Param_ManTrqCmd_MtrNm_f32, Boolean Param_DefeatHwTrq_Cnt_lgc, Boolean Param_DefeatTemp_Cnt_lgc);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HaitecTrqCmd_SCom_StopCtrl
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <StopCtrl> of PortPrototype <HaitecTrqCmd_SCom>
 *
 **********************************************************************************************************************
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_AstLmt_Scom_ManualTrqCmd(Boolean EnableManualCtrl, Float ManTrqCmd_MtrNm_f32)
 *     Synchronous Server Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void HaitecTrqCmd_SCom_StopCtrl(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_SCom_StopCtrl(void);

# define RTE_STOP_SEC_AP_HAITECTRQCMD_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_HaitecTrqCmd_SCom_E_NOT_OK (1u)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1441748243
#    error "The magic number of the generated file <C:/HaitecTrqCmd/HaitecTrqCmd/tools/contract/Ap_HaitecTrqCmd/Rte_Ap_HaitecTrqCmd.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1441748243
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_AP_HAITECTRQCMD_H */
