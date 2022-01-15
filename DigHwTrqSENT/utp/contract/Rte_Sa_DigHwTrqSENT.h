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
 *          File:  Rte_Sa_DigHwTrqSENT.h
 *     Workspace:  C:/_00_Working_Files/_19_EA3.0_Work/03_Component_Development/DigHwTrqSENT/autosar
 *     SW-C Type:  Sa_DigHwTrqSENT
 *  Generated at:  Thu Jul 31 15:06:33 2014
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Application header file for SW-C <Sa_DigHwTrqSENT> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_SA_DIGHWTRQSENT_H
# define _RTE_SA_DIGHWTRQSENT_H

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

typedef P2CONST(struct Rte_CDS_Sa_DigHwTrqSENT, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_HwTorque_HwNm_f32 ((Float)0)
# define Rte_InitValue_MECCounter_Cnt_enum ((ManufModeType)0u)
# define Rte_InitValue_SrlComHwTrq_HwNm_f32 ((Float)0)
# define Rte_InitValue_SrlComHwTrqValid_Cnt_lgc ((Boolean)FALSE)
# define Rte_InitValue_SysCHwTorque_HwNm_f32 ((Float)0)
# define Rte_InitValue_T1_HwNm_f32 ((Float)0)
# define Rte_InitValue_T2_HwNm_f32 ((Float)0)


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Sa_DigHwTrqSENT_MECCounter_Cnt_enum(P2VAR(ManufModeType, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Sa_DigHwTrqSENT_T1_HwNm_f32(P2VAR(Float, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_Sa_DigHwTrqSENT_T2_HwNm_f32(P2VAR(Float, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_DigHwTrqSENT_FaultInjection_SCom_FltInjection(P2VAR(Float, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_DigHwTrqSENT_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus(P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) ErrorStatus);
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_DigHwTrqSENT_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(P2CONST(UInt8, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_DATA) DstPtr);
# else
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_DigHwTrqSENT_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(P2CONST(NvM_DestPtr, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_DATA) DstPtr);
# endif
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_DigHwTrqSENT_NxtrDiagMgr_GetNTCStatus(NTCNumber NTC_Cnt_T_enum, P2VAR(UInt8, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) Status_Ptr_T_u08);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Sa_DigHwTrqSENT_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

# define Rte_IRead_DigHwTrqSENT_Init1_MECCounter_Cnt_enum() \
  (Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Init1_MECCounter_Cnt_enum->value)

# define Rte_IRead_DigHwTrqSENT_Per1_T1_HwNm_f32() \
  (Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per1_T1_HwNm_f32->value)

# define Rte_IRead_DigHwTrqSENT_Per1_T2_HwNm_f32() \
  (Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per1_T2_HwNm_f32->value)

# define Rte_IWrite_DigHwTrqSENT_Per1_HwTorque_HwNm_f32(data) \
  ( \
  Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per1_HwTorque_HwNm_f32->value = (data) \
  )

# define Rte_IWriteRef_DigHwTrqSENT_Per1_HwTorque_HwNm_f32() \
  (&Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per1_HwTorque_HwNm_f32->value)

# define Rte_IWrite_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32(data) \
  ( \
  Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32->value = (data) \
  )

# define Rte_IWriteRef_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32() \
  (&Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32->value)

# define Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc(data) \
  ( \
  Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc->value = (data) \
  )

# define Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc() \
  (&Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc->value)

# define Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32(data) \
  ( \
  Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32->value = (data) \
  )

# define Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32() \
  (&Rte_Inst_Sa_DigHwTrqSENT->DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32->value)


/**********************************************************************************************************************
 * Rte_Read_<p>_<d> (explicit S/R communication with isQueued = false)
 *********************************************************************************************************************/
# define Rte_Read_MECCounter_Cnt_enum Rte_Read_Sa_DigHwTrqSENT_MECCounter_Cnt_enum
# define Rte_Read_T1_HwNm_f32 Rte_Read_Sa_DigHwTrqSENT_T1_HwNm_f32
# define Rte_Read_T2_HwNm_f32 Rte_Read_Sa_DigHwTrqSENT_T2_HwNm_f32


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_FaultInjection_SCom_FltInjection Rte_Call_Sa_DigHwTrqSENT_FaultInjection_SCom_FltInjection
# define Rte_Call_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus Rte_Call_Sa_DigHwTrqSENT_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus
# define Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock Rte_Call_Sa_DigHwTrqSENT_NvM_DigHwTrqSENTTrim_Srv_WriteBlock
# define Rte_Call_NxtrDiagMgr_GetNTCStatus Rte_Call_Sa_DigHwTrqSENT_NxtrDiagMgr_GetNTCStatus
# define Rte_Call_NxtrDiagMgr_SetNTCStatus Rte_Call_Sa_DigHwTrqSENT_NxtrDiagMgr_SetNTCStatus


/**********************************************************************************************************************
 * Per-Instance Memory User Types
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Rte_Pim (Per-Instance Memory)
 *********************************************************************************************************************/

# define Rte_Pim_DigTrqTrim() (Rte_Inst_Sa_DigHwTrqSENT->Pim_DigTrqTrim)




/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   DigHwTrqSENTTrim_DataType *Rte_Pim_DigTrqTrim(void)
 *
 *********************************************************************************************************************/


# define RTE_START_SEC_SA_DIGHWTRQSENT_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   ManufModeType Rte_IRead_DigHwTrqSENT_Init1_MECCounter_Cnt_enum(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Init1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Per1
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
 *   Float Rte_IRead_DigHwTrqSENT_Per1_T1_HwNm_f32(void)
 *   Float Rte_IRead_DigHwTrqSENT_Per1_T2_HwNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DigHwTrqSENT_Per1_HwTorque_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_DigHwTrqSENT_Per1_HwTorque_HwNm_f32(void)
 *   void Rte_IWrite_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_DigHwTrqSENT_Per1_SysCHwTorque_HwNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_FaultInjection_SCom_FltInjection(Float *SignalPath_Uls_f32, FltInjectionLocType LocationKey_Cnt_enum)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 4ms
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrqValid_Cnt_lgc(void)
 *   void Rte_IWrite_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32(Float data)
 *   Float *Rte_IWriteRef_DigHwTrqSENT_Per2_SrlComHwTrq_HwNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_GetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 *Status_Ptr_T_u08)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per2(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_Per3
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 100ms
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_Per3(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_ClrTrqTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ClrTrqTrim> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MECCounter_Cnt_enum(ManufModeType *data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const UInt8 *DstPtr)
# else
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
# endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DigHwTrqSENT_SCom_ClrTrqTrim(void)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DigHwTrqSENT_SCom_ConditionsNotCorrect
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_ClrTrqTrim(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_SetTrqTrim
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetTrqTrim> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MECCounter_Cnt_enum(ManufModeType *data)
 *   Std_ReturnType Rte_Read_T1_HwNm_f32(Float *data)
 *   Std_ReturnType Rte_Read_T2_HwNm_f32(Float *data)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
# ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const UInt8 *DstPtr)
# else
 *   Std_ReturnType Rte_Call_NvM_DigHwTrqSENTTrim_Srv_WriteBlock(const NvM_DestPtr *DstPtr)
# endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DigHwTrqSENT_SCom_SetTrqTrim(void)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DigHwTrqSENT_SCom_ConditionsNotCorrect
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_SetTrqTrim(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_TrimData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <TrimData> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void DigHwTrqSENT_SCom_TrimData(Float *EOLHwTrqTrim_HwNm_f32, Boolean *EOLHwTrqTrimPerformed_Cnt_Lgc)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_TrimData(P2VAR(Float, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrim_HwNm_f32, P2VAR(Boolean, AUTOMATIC, RTE_SA_DIGHWTRQSENT_APPL_VAR) EOLHwTrqTrimPerformed_Cnt_Lgc);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DigHwTrqSENT_SCom_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DigHwTrqSENT_SCom>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void DigHwTrqSENT_SCom_WriteData(Float HwTrqTrim_HwNm_f32)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_SA_DIGHWTRQSENT_APPL_CODE) DigHwTrqSENT_SCom_WriteData(Float HwTrqTrim_HwNm_f32);

# define RTE_STOP_SEC_SA_DIGHWTRQSENT_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_DigHwTrqSENT_SCom_ConditionsNotCorrect (34u)

# define RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK (1u)

# define RTE_E_NxtrDiagMgr_E_NOT_OK (1u)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1406832413
#    error "The magic number of the generated file <C:/_00_Working_Files/_19_EA3.0_Work/03_Component_Development/DigHwTrqSENT/utp/contract/Rte_Sa_DigHwTrqSENT.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1406832413
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_SA_DIGHWTRQSENT_H */
