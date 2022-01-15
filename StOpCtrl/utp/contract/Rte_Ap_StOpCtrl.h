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
 *          File:  Rte_Ap_StOpCtrl.h
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/StOpCtrl-nzt9hv/StOpCtrl/autosar
 *     SW-C Type:  Ap_StOpCtrl
 *  Generated at:  Wed Sep 26 10:12:28 2012
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Application header file for SW-C <Ap_StOpCtrl> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_STOPCTRL_H
# define _RTE_AP_STOPCTRL_H

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

typedef P2CONST(struct Rte_CDS_Ap_StOpCtrl, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_DiagRampRate_XpmS_f32 ((Float)0)
# define Rte_InitValue_DiagRampValue_Uls_f32 ((Float)0)
# define Rte_InitValue_DiagStsDiagRmpActive_Cnt_lgc ((Boolean)FALSE)
# define Rte_InitValue_OperRampRate_XpmS_f32 ((Float)0)
# define Rte_InitValue_OperRampValue_Uls_f32 ((Float)0)
# define Rte_InitValue_OutputRampMult_Uls_f32 ((Float)0)
# define Rte_InitValue_RampDwnStatusComplete_Cnt_lgc ((Boolean)FALSE)
# define Rte_InitValue_RampSrlComSvcDft_Cnt_lgc ((Boolean)FALSE)


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_StOpCtrl_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, P2VAR(UInt32, AUTOMATIC, RTE_AP_STOPCTRL_APPL_VAR) ElapsedTime);
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_StOpCtrl_SystemTime_GetSystemTime_mS_u32(P2VAR(UInt32, AUTOMATIC, RTE_AP_STOPCTRL_APPL_VAR) CurrentTime);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

# define Rte_IRead_StOpCtrl_Per1_DiagRampRate_XpmS_f32() \
  (Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_DiagRampRate_XpmS_f32->value)

# define Rte_IRead_StOpCtrl_Per1_DiagRampValue_Uls_f32() \
  (Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_DiagRampValue_Uls_f32->value)

# define Rte_IRead_StOpCtrl_Per1_DiagStsDiagRmpActive_Cnt_lgc() \
  (Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_DiagStsDiagRmpActive_Cnt_lgc->value)

# define Rte_IRead_StOpCtrl_Per1_OperRampRate_XpmS_f32() \
  (Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_OperRampRate_XpmS_f32->value)

# define Rte_IRead_StOpCtrl_Per1_OperRampValue_Uls_f32() \
  (Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_OperRampValue_Uls_f32->value)

# define Rte_IRead_StOpCtrl_Per1_RampSrlComSvcDft_Cnt_lgc() \
  (Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_RampSrlComSvcDft_Cnt_lgc->value)

# define Rte_IWrite_StOpCtrl_Per1_OutputRampMult_Uls_f32(data) \
  ( \
  Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_OutputRampMult_Uls_f32->value = (data) \
  )

# define Rte_IWriteRef_StOpCtrl_Per1_OutputRampMult_Uls_f32() \
  (&Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_OutputRampMult_Uls_f32->value)

# define Rte_IWrite_StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc(data) \
  ( \
  Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc->value = (data) \
  )

# define Rte_IWriteRef_StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc() \
  (&Rte_Inst_Ap_StOpCtrl->StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc->value)


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32 Rte_Call_Ap_StOpCtrl_SystemTime_DtrmnElapsedTime_mS_u32
# define Rte_Call_SystemTime_GetSystemTime_mS_u32 Rte_Call_Ap_StOpCtrl_SystemTime_GetSystemTime_mS_u32




# define RTE_START_SEC_AP_STOPCTRL_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: StOpCtrl_Per1
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
 *   Float Rte_IRead_StOpCtrl_Per1_DiagRampRate_XpmS_f32(void)
 *   Float Rte_IRead_StOpCtrl_Per1_DiagRampValue_Uls_f32(void)
 *   Boolean Rte_IRead_StOpCtrl_Per1_DiagStsDiagRmpActive_Cnt_lgc(void)
 *   Float Rte_IRead_StOpCtrl_Per1_OperRampRate_XpmS_f32(void)
 *   Float Rte_IRead_StOpCtrl_Per1_OperRampValue_Uls_f32(void)
 *   Boolean Rte_IRead_StOpCtrl_Per1_RampSrlComSvcDft_Cnt_lgc(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_StOpCtrl_Per1_OutputRampMult_Uls_f32(Float data)
 *   Float *Rte_IWriteRef_StOpCtrl_Per1_OutputRampMult_Uls_f32(void)
 *   void Rte_IWrite_StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc(Boolean data)
 *   Boolean *Rte_IWriteRef_StOpCtrl_Per1_RampDwnStatusComplete_Cnt_lgc(void)
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u32(UInt32 InitialTime, UInt32 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_STOPCTRL_APPL_CODE) StOpCtrl_Per1(void);

# define RTE_STOP_SEC_AP_STOPCTRL_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1348673079
#    error "The magic number of the generated file <C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/StOpCtrl-nzt9hv/StOpCtrl/utp/contract/Rte_Ap_StOpCtrl.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1348673079
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_AP_STOPCTRL_H */
