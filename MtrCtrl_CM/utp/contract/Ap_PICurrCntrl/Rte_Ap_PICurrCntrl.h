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
 *          File:  Rte_Ap_PICurrCntrl.h
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/autosar
 *     SW-C Type:  Ap_PICurrCntrl
 *  Generated at:  Tue Nov 26 16:56:58 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  Application header file for SW-C <Ap_PICurrCntrl> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_PICURRCNTRL_H
# define _RTE_AP_PICURRCNTRL_H

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

typedef P2CONST(struct Rte_CDS_Ap_PICurrCntrl, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_CorrMtrPosElec_Rev_f32 ((Float)0)
# define Rte_InitValue_DervLambdaAlphaDiag_Volt_f32 ((Float)0)
# define Rte_InitValue_DervLambdaBetaDiag_Volt_f32 ((Float)0)
# define Rte_InitValue_EstKe_VpRadpS_f32 ((Float)0)
# define Rte_InitValue_EstR_Ohm_f32 ((Float)0)
# define Rte_InitValue_MRFMtrVel_MtrRadpS_f32 ((Float)0)
# define Rte_InitValue_MtrCurrDaxRef_Amp_f32 ((Float)0)


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Rte_ModeType_StaMd_Mode, RTE_CODE) Rte_Mode_Ap_PICurrCntrl_SystemState_Mode(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

# define Rte_IRead_PICurrCntrl_Per2_CorrMtrPosElec_Rev_f32() \
  (Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_CorrMtrPosElec_Rev_f32->value)

# define Rte_IRead_PICurrCntrl_Per2_EstKe_VpRadpS_f32() \
  (Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_EstKe_VpRadpS_f32->value)

# define Rte_IRead_PICurrCntrl_Per2_EstR_Ohm_f32() \
  (Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_EstR_Ohm_f32->value)

# define Rte_IRead_PICurrCntrl_Per2_MRFMtrVel_MtrRadpS_f32() \
  (Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_MRFMtrVel_MtrRadpS_f32->value)

# define Rte_IRead_PICurrCntrl_Per2_MtrCurrDaxRef_Amp_f32() \
  (Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_MtrCurrDaxRef_Amp_f32->value)

# define Rte_IWrite_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(data) \
  ( \
  Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32->value = (data) \
  )

# define Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32() \
  (&Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32->value)

# define Rte_IWrite_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(data) \
  ( \
  Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32->value = (data) \
  )

# define Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32() \
  (&Rte_Inst_Ap_PICurrCntrl->PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32->value)


/**********************************************************************************************************************
 * Rte_Mode_<p>_<m>
 *********************************************************************************************************************/
# define Rte_Mode_SystemState_Mode Rte_Mode_Ap_PICurrCntrl_SystemState_Mode




# define RTE_START_SEC_AP_PICURRCNTRL_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: PICurrCntrl_Per2
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
 *   Float Rte_IRead_PICurrCntrl_Per2_CorrMtrPosElec_Rev_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_EstKe_VpRadpS_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_EstR_Ohm_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_MRFMtrVel_MtrRadpS_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_MtrCurrDaxRef_Amp_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(void)
 *   void Rte_IWrite_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(void)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_PICURRCNTRL_APPL_CODE) PICurrCntrl_Per2(void);

# define RTE_STOP_SEC_AP_PICURRCNTRL_APPL_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1385500434
#    error "The magic number of the generated file <C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/utp/contract/Ap_PICurrCntrl/Rte_Ap_PICurrCntrl.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1385500434
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_AP_PICURRCNTRL_H */
