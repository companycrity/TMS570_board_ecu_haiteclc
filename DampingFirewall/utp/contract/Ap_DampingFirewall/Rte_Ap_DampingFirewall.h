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
 *          File:  Rte_Ap_DampingFirewall.h
 *     Workspace:  C:/Synergy_projects/DampingFirewall-lz4p8n/DampingFirewall/autosar/Ap_DampingFirewall.dcf
 *     SW-C Type:  Ap_DampingFirewall
 *  Generated at:  Wed May 15 15:21:28 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  Application header file for SW-C <Ap_DampingFirewall> (Contract Phase)
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_AP_DAMPINGFIREWALL_H
# define _RTE_AP_DAMPINGFIREWALL_H

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

typedef P2CONST(struct Rte_CDS_Ap_DampingFirewall, TYPEDEF, RTE_CONST) Rte_Instance;


/**********************************************************************************************************************
 * Init Values for unqueued S/R communication (primitive types only)
 *********************************************************************************************************************/

# define Rte_InitValue_AsstFirewallActive_Uls_f32 (0.0F)
# define Rte_InitValue_BaseAssistCmd_MtrNm_f32 (0.0F)
# define Rte_InitValue_CombinedDamping_MtrNm_f32 (0.0F)
# define Rte_InitValue_DampingCmd_MtrNm_f32 (0.0F)
# define Rte_InitValue_Defeat_Damping_Svc_Cnt_lgc (FALSE)
# define Rte_InitValue_FreqDepDmpSrlComSvcDft_Cnt_lgc (FALSE)
# define Rte_InitValue_HwTorque_HwNm_f32 (0.0F)
# define Rte_InitValue_InertiaComp_MtrNm_f32 (0.0F)
# define Rte_InitValue_MEC_Counter_Cnt_enum (0U)
# define Rte_InitValue_MtrVelCRF_MtrRadpS_f32 (0.0F)
# define Rte_InitValue_VehicleLonAccel_KphpS_f32 (0.0F)
# define Rte_InitValue_VehicleSpeed_Kph_f32 (0.0F)
# define Rte_InitValue_WIRCmdAmpBlnd_MtrNm_f32 (0.0F)


# define RTE_START_SEC_CODE
# include "MemMap.h"

/**********************************************************************************************************************
 * API prototypes
 *********************************************************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_Ap_DampingFirewall_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum);

# define RTE_STOP_SEC_CODE
# include "MemMap.h"



/**********************************************************************************************************************
 * Rte_IRead_<r>_<p>_<d>
 * Rte_IStatus_<r>_<p>_<d>
 * Rte_IWrite_<r>_<p>_<d>
 * Rte_IWriteRef_<r>_<p>_<d>
 * Rte_IInvalidate_<r>_<p>_<d>
 *********************************************************************************************************************/

# define Rte_IRead_DampingFirewall_Per1_AsstFirewallActive_Uls_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_AsstFirewallActive_Uls_f32->value)

# define Rte_IRead_DampingFirewall_Per1_BaseAssistCmd_MtrNm_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_BaseAssistCmd_MtrNm_f32->value)

# define Rte_IRead_DampingFirewall_Per1_DampingCmd_MtrNm_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_DampingCmd_MtrNm_f32->value)

# define Rte_IRead_DampingFirewall_Per1_Defeat_Damping_Svc_Cnt_lgc() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_Defeat_Damping_Svc_Cnt_lgc->value)

# define Rte_IRead_DampingFirewall_Per1_FreqDepDmpSrlComSvcDft_Cnt_lgc() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_FreqDepDmpSrlComSvcDft_Cnt_lgc->value)

# define Rte_IRead_DampingFirewall_Per1_HwTorque_HwNm_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_HwTorque_HwNm_f32->value)

# define Rte_IRead_DampingFirewall_Per1_InertiaComp_MtrNm_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_InertiaComp_MtrNm_f32->value)

# define Rte_IRead_DampingFirewall_Per1_MEC_Counter_Cnt_enum() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_MEC_Counter_Cnt_enum->value)

# define Rte_IRead_DampingFirewall_Per1_MtrVelCRF_MtrRadpS_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_MtrVelCRF_MtrRadpS_f32->value)

# define Rte_IRead_DampingFirewall_Per1_VehicleLonAccel_KphpS_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_VehicleLonAccel_KphpS_f32->value)

# define Rte_IRead_DampingFirewall_Per1_VehicleSpeed_Kph_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_VehicleSpeed_Kph_f32->value)

# define Rte_IRead_DampingFirewall_Per1_WIRCmdAmpBlnd_MtrNm_f32() \
  (Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_WIRCmdAmpBlnd_MtrNm_f32->value)

# define Rte_IWrite_DampingFirewall_Per1_CombinedDamping_MtrNm_f32(data) \
  ( \
  Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_CombinedDamping_MtrNm_f32->value = (data) \
  )

# define Rte_IWriteRef_DampingFirewall_Per1_CombinedDamping_MtrNm_f32() \
  (&Rte_Inst_Ap_DampingFirewall->DampingFirewall_Per1_CombinedDamping_MtrNm_f32->value)


/**********************************************************************************************************************
 * Rte_Call_<p>_<o> (C/S invocation)
 *********************************************************************************************************************/
# define Rte_Call_NxtrDiagMgr_SetNTCStatus Rte_Call_Ap_DampingFirewall_NxtrDiagMgr_SetNTCStatus




# define RTE_START_SEC_AP_DAMPINGFIREWALL_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 *
 * Runnable Entity Name: DampingFirewall_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DAMPINGFIREWALL_APPL_CODE) DampingFirewall_Init1(void);

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DampingFirewall_Per1
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
 *   Float Rte_IRead_DampingFirewall_Per1_AsstFirewallActive_Uls_f32(void)
 *   Float Rte_IRead_DampingFirewall_Per1_BaseAssistCmd_MtrNm_f32(void)
 *   Float Rte_IRead_DampingFirewall_Per1_DampingCmd_MtrNm_f32(void)
 *   Boolean Rte_IRead_DampingFirewall_Per1_Defeat_Damping_Svc_Cnt_lgc(void)
 *   Boolean Rte_IRead_DampingFirewall_Per1_FreqDepDmpSrlComSvcDft_Cnt_lgc(void)
 *   Float Rte_IRead_DampingFirewall_Per1_HwTorque_HwNm_f32(void)
 *   Float Rte_IRead_DampingFirewall_Per1_InertiaComp_MtrNm_f32(void)
 *   ManufModeType Rte_IRead_DampingFirewall_Per1_MEC_Counter_Cnt_enum(void)
 *   Float Rte_IRead_DampingFirewall_Per1_MtrVelCRF_MtrRadpS_f32(void)
 *   Float Rte_IRead_DampingFirewall_Per1_VehicleLonAccel_KphpS_f32(void)
 *   Float Rte_IRead_DampingFirewall_Per1_VehicleSpeed_Kph_f32(void)
 *   Float Rte_IRead_DampingFirewall_Per1_WIRCmdAmpBlnd_MtrNm_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DampingFirewall_Per1_CombinedDamping_MtrNm_f32(Float data)
 *   Float *Rte_IWriteRef_DampingFirewall_Per1_CombinedDamping_MtrNm_f32(void)
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DAMPINGFIREWALL_APPL_CODE) DampingFirewall_Per1(void);

# define RTE_STOP_SEC_AP_DAMPINGFIREWALL_APPL_CODE
# include "MemMap.h"


/**********************************************************************************************************************
 * Application errors
 *********************************************************************************************************************/

# define RTE_E_NxtrDiagMgr_E_NOT_OK (1U)

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1368646238
#    error "The magic number of the generated file <C:/Synergy_projects/DampingFirewall-lz4p8n/DampingFirewall/utp/contract/Ap_DampingFirewall/Rte_Ap_DampingFirewall.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1368646238
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_AP_DAMPINGFIREWALL_H */
