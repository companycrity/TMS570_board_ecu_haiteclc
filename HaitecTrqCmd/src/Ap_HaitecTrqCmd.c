/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_HaitecTrqCmd.c
 *     Workspace:  C:/HaitecTrqCmd/HaitecTrqCmd/autosar
 *     SW-C Type:  Ap_HaitecTrqCmd
 *  Generated at:  Tue Sep  8 16:11:43 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_HaitecTrqCmd>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
* Copyright 2015 Nexteer 
* Nexteer Confidential
*
* Module File Name  : Ap_HaitecTrqCmd.c
* Module Description: Provides a motor torque command from diagnostic service that is manipulated by a damping curve 
*					  based on motor velocity.  
* Project           : CBD   
* Author            : Jayakrishnan T
***********************************************************************************************************************
* Version Control:
* %version:          1 %
* %derived_by:       czmgrw %
*----------------------------------------------------------------------------------------------------------------------
* Date      Rev      Author         Change Description                                                        SCR #
* -------   -------  --------  ---------------------------------------------------------------------------  -----------
* 09/08/15   1       JK        Initial implementation of CF-15A HaitecTrqCmd								EA3#2981
**********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_HaitecTrqCmd.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "GlobalMacro.h"
#include "filters.h"
#include "CalConstants.h"

/* MISRA-C:2004 Rule 19.1: Deviation required for the AUTOSAR Compliance.  Rule suppressed by line at each occurrence.*/

#define D_VEHSPDTHD_KPH_F32  0.001f

#define HAITECTRQCMD_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, AP_HAITECTRQCMD_VAR) HaTqCmd_HwTrqLPFKSV_Cnt_M_Str;
STATIC VAR(LPF32KSV_Str, AP_HAITECTRQCMD_VAR) HaTqCmd_MtrVelLPFKSV_Cnt_M_Str;
#define HAITECTRQCMD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */

#define HAITECTRQCMD_START_SEC_VAR_CLEARED_32
#include "MemMap.h"  /* PRQA S 5087 */
STATIC VAR(float32, AP_HAITECTRQCMD_VAR) HaTqCmd_ManTrqCmd_MtrNm_M_f32;
STATIC VAR(float32, AP_HAITECTRQCMD_VAR) HaTqCmd_AbsFiltHwTrq_HwNm_M_f32;
#define HAITECTRQCMD_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"  /* PRQA S 5087 */

#define HAITECTRQCMD_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"  /* PRQA S 5087 */
STATIC VAR(boolean, AP_HAITECTRQCMD_VAR) HaTqCmd_DefeatTemp_Cnt_M_lgc;
STATIC VAR(boolean, AP_HAITECTRQCMD_VAR) HaTqCmd_DefeatHwTrq_Cnt_M_lgc;
STATIC VAR(boolean, AP_HAITECTRQCMD_VAR) HaTqCmd_ManCmdEna_Cnt_M_lgc;
#define HAITECTRQCMD_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"  /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * Boolean: Boolean (standard type)
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Defined Constants
 *
 **********************************************************************************************************************
 *
 * Primitive Type Constants:
 * =========================
 * Boolean: D_FALSE_CNT_LGC = FALSE
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8
 * Float: D_ZERO_ULS_F32 = 0
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_HAITECTRQCMD_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: HaitecTrqCmd_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HaitecTrqCmd_Init1
 *********************************************************************************************************************/
	 /* Initialize filters */
	 LPF_Init_f32_m(D_ZERO_ULS_F32, k_HaTqCmd_MotVelLpFilFrq_Hz_f32, D_2MS_SEC_F32, &HaTqCmd_MtrVelLPFKSV_Cnt_M_Str);
	 LPF_Init_f32_m(D_ZERO_ULS_F32, k_HaTqCmd_HwTqLpFilFrq_Hz_f32, D_2MS_SEC_F32, &HaTqCmd_HwTrqLPFKSV_Cnt_M_Str);

	 HaTqCmd_ManCmdEna_Cnt_M_lgc = FALSE;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HaitecTrqCmd_Per1
 *********************************************************************************************************************/

	/* Input variables */
	VAR(float32, AUTOMATIC) HwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(float32, AUTOMATIC) AssistMechTempEst_DegC_T_f32;
	VAR(float32, AUTOMATIC) MtrVelCRF_MtrRadpS_T_f32;

	/* Module internal variables */
	VAR(float32, AUTOMATIC) FiltMtrVelCRF_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) DampMtrTrq_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampedMtrTrqCmd_MtrNm_T_f32;
	VAR(boolean, AUTOMATIC) EnableManualCntrl_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) FiltHwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) AbsFiltHwTrq_HwNm_T_f32;

	/* Read RTE Inputs */
	HwTrq_HwNm_T_f32 = Rte_IRead_HaitecTrqCmd_Per1_HwTrq_HwNm_f32();
	VehSpd_Kph_T_f32 = Rte_IRead_HaitecTrqCmd_Per1_VehSpd_Kph_f32();
	AssistMechTempEst_DegC_T_f32 = Rte_IRead_HaitecTrqCmd_Per1_AssitMechTempEst_DegC_f32();
	MtrVelCRF_MtrRadpS_T_f32 = Rte_IRead_HaitecTrqCmd_Per1_MtrVelCRF_MtrRadpS_f32();

	/*Filtering*/
	FiltHwTrq_HwNm_T_f32 = (LPF_OpUpdate_f32_m(HwTrq_HwNm_T_f32, &HaTqCmd_HwTrqLPFKSV_Cnt_M_Str));
	FiltMtrVelCRF_MtrRadpS_T_f32 = LPF_OpUpdate_f32_m(MtrVelCRF_MtrRadpS_T_f32, &HaTqCmd_MtrVelLPFKSV_Cnt_M_Str);

	AbsFiltHwTrq_HwNm_T_f32 = Abs_f32_m(FiltHwTrq_HwNm_T_f32);
	HaTqCmd_AbsFiltHwTrq_HwNm_M_f32 = AbsFiltHwTrq_HwNm_T_f32;

	if(HaTqCmd_ManCmdEna_Cnt_M_lgc == TRUE)
	{
		/* Enable Conditions */
		if((VehSpd_Kph_T_f32 < D_VEHSPDTHD_KPH_F32) &&
		  ((HaTqCmd_AbsFiltHwTrq_HwNm_M_f32 < k_HaTqCmd_HwTqMgnLim_HwNm_f32) || (HaTqCmd_DefeatHwTrq_Cnt_M_lgc == TRUE)) &&
		  ((AssistMechTempEst_DegC_T_f32 < k_HaTqCmd_TempEstLim_DegC_f32) || (HaTqCmd_DefeatTemp_Cnt_M_lgc == TRUE)))
		{
			EnableManualCntrl_Cnt_T_lgc = TRUE;
		}
		else
		{
			EnableManualCntrl_Cnt_T_lgc = FALSE;
		}

		HaTqCmd_ManCmdEna_Cnt_M_lgc = EnableManualCntrl_Cnt_T_lgc;

		if(EnableManualCntrl_Cnt_T_lgc == FALSE)
		{
			DampedMtrTrqCmd_MtrNm_T_f32 = 0.0f;
		}
		else
		{
			/* Damping Torque  =   A * Vel^3  +  B * Vel^2  +  C * Vel  +  Offset */
			DampMtrTrq_MtrNm_T_f32  =  (k_HaTqCmd_PolyTermA_Uls_f32 * FiltMtrVelCRF_MtrRadpS_T_f32 * FiltMtrVelCRF_MtrRadpS_T_f32 * FiltMtrVelCRF_MtrRadpS_T_f32) +
									   (k_HaTqCmd_PolyTermB_Uls_f32 * FiltMtrVelCRF_MtrRadpS_T_f32 * FiltMtrVelCRF_MtrRadpS_T_f32) +
									   (k_HaTqCmd_PolyTermC_Uls_f32 * FiltMtrVelCRF_MtrRadpS_T_f32) +
									    k_HaTqCmd_PolyOffs_Uls_f32 ;

			/* Damped Torque Command  =  MtrTrqCmd - Damping Torque */
			DampedMtrTrqCmd_MtrNm_T_f32 = HaTqCmd_ManTrqCmd_MtrNm_M_f32 - DampMtrTrq_MtrNm_T_f32;
		}

		DampedMtrTrqCmd_MtrNm_T_f32 = Limit_m(DampedMtrTrqCmd_MtrNm_T_f32, D_MTRTRQCMDLOLMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);

		(void)Rte_Call_AstLmt_Scom_ManualTrqCmd(EnableManualCntrl_Cnt_T_lgc,DampedMtrTrqCmd_MtrNm_T_f32);
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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

FUNC(Std_ReturnType, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_SCom_StartCtrl(Float Param_ManTrqCmd_MtrNm_f32, Boolean Param_DefeatHwTrq_Cnt_lgc, Boolean Param_DefeatTemp_Cnt_lgc)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HaitecTrqCmd_SCom_StartCtrl (returns application error)
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;
	VAR(float32, AUTOMATIC) AssistMechTempEst_DegC_T_f32;
	VAR(Std_ReturnType, AUTOMATIC) ReturnVal_Cnt_T_enum;

	(void)Rte_Read_VehSpd_Kph_f32(&VehSpd_Kph_T_f32);
	(void)Rte_Read_AssitMechTempEst_DegC_f32(&AssistMechTempEst_DegC_T_f32);

	HaTqCmd_DefeatHwTrq_Cnt_M_lgc = Param_DefeatHwTrq_Cnt_lgc;
	HaTqCmd_DefeatTemp_Cnt_M_lgc  = Param_DefeatTemp_Cnt_lgc;
	HaTqCmd_ManTrqCmd_MtrNm_M_f32 = Limit_m(Param_ManTrqCmd_MtrNm_f32, D_MTRTRQCMDLOLMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);

	/* Enable Conditions */
	if((VehSpd_Kph_T_f32 < D_VEHSPDTHD_KPH_F32) &&
	  ((HaTqCmd_AbsFiltHwTrq_HwNm_M_f32 < k_HaTqCmd_HwTqMgnLim_HwNm_f32) || (HaTqCmd_DefeatHwTrq_Cnt_M_lgc == TRUE)) &&
	  ((AssistMechTempEst_DegC_T_f32 < k_HaTqCmd_TempEstLim_DegC_f32) || (HaTqCmd_DefeatTemp_Cnt_M_lgc == TRUE)))
	{
		HaTqCmd_ManCmdEna_Cnt_M_lgc = TRUE;
		ReturnVal_Cnt_T_enum = E_OK;
	}
	else
	{
		HaTqCmd_ManCmdEna_Cnt_M_lgc = FALSE;
		ReturnVal_Cnt_T_enum = RTE_E_HaitecTrqCmd_SCom_E_NOT_OK;
	}

	return(ReturnVal_Cnt_T_enum);


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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

FUNC(void, RTE_AP_HAITECTRQCMD_APPL_CODE) HaitecTrqCmd_SCom_StopCtrl(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: HaitecTrqCmd_SCom_StopCtrl
 *********************************************************************************************************************/

	HaTqCmd_ManCmdEna_Cnt_M_lgc = FALSE;
	(void)Rte_Call_AstLmt_Scom_ManualTrqCmd(HaTqCmd_ManCmdEna_Cnt_M_lgc,0.0f);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_HAITECTRQCMD_APPL_CODE
#include "MemMap.h"  /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
