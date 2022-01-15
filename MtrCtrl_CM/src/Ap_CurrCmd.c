/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_CurrCmd.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/autosar
 *     SW-C Type:  Ap_CurrCmd
 *  Generated at:  Tue Nov 26 16:55:55 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_CurrCmd>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 16 00:46:49 2012
 * %version:          12 %
 * %derived_by:       nzt9hv %
 * %date_modified:    Tue Nov 26 14:04:38 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * -------   -------  --------  -------------------------------------------------------------------------------  ------
 * 09/20/12  4        OT        Partial implementation of SF99B v004
 * 11/20/12  5		 Selva 		Checkpoints and memmap statements added	
 * 03/21/13  6,7 		 Selva      Updated to version 8 FDD SF99 B	                                                   7711	
 * 03/21/13  8 		 Selva      Updated to version 8 FDD SF99 
 * 10/21/13  9       Selva      Updated for A5883                                                                    10050    
 * 11/06/13  10       Selva      Updated for V11 of     FDD SF99                                                      10740 
 * 11/08/13  11       Selva      Updated for V11 of FDD SF99  /Corrected NewDelta  A5883 contd                         10740 
 * 11/26/13  12       Selva      Updated for V12 of FDD SF99                                                          10950
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Component Types:
 ================
  Ap_CurrCmd
    Generates the Current Command and the Voltage Reference for the Current Control


 Data Element Prototypes:
 ========================
  Volt_f32 of Port Interface Voltage_Volt_f32
    This signal is intended to communicate any type voltage signal measured by the ecu.  This signal has a lower limit of 0 which reequires users of the signal to provide divide by 0 protection if it is used as a denominator in a calculation.  See Vecu port prototype if a port with a lower limit is desired.

  Volt_f32 of Port Interface Vecu_Volt_f32
    This port prototype is inteded to communicate voltage signals that represent the ecu supplied voltage.  This signal has a lower limit, which is non-zero, to allow users of the signal to use it as a denominator in an expression without requiring a divide by 0 check.

 *********************************************************************************************************************/

#include "Rte_Ap_CurrCmd.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Ap_CurrCmd_Cfg.h"
#include "CalConstants.h"
#include "fixmath.h"
#include "interpolation.h"
#include "filters.h"
#include <math.h>
#include <float.h>
#define MTRCTRL
#include "Ap_MtrCtrl.h"
#include "MtrCtrl_Cfg.h"

#define D_2OVRSQRT3_ULS_F32                     1.15470053837925F
#define D_NEG2OVRSQRT3_ULS_F32                  (-1.15470053837925F)
#define D_SQRT3OVR2_ULS_F32					    0.866025403784F
#define D_MTRPOLESDIV2_CNT_F32					3.0F
#define D_ROUND_ULS_F32							0.5F
#define D_NEGROUND_ULS_F32                      (-0.5F)
#define D_NEG_ULS_F32                        (-D_ONE_ULS_F32)
#define D_VECUMAX_VOLTS_F32                      31.0F
#define D_MAXCURRENT_AMP_F32					220.0F
#define D_SIZERDLTAPOINTS_CNT_U16              (uint16)(TableSize_m(t_RefDeltaPoints_Rad_f32))
#define D_MAXDELTAPOINTSSIZE_CNT_U16             (uint16)(D_SIZERDLTAPOINTS_CNT_U16 - 1U)
#define D_PIPLUSPIOVER4_ULS_F32                  (D_PI_ULS_F32+(D_PI_ULS_F32/4.0F))

#define CURRCMD_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
/* Display Variables */

STATIC  volatile VAR(float32, AP_CurrCmd_VAR_NOINIT) MtrCurrDaxRef_Amp_D_f32;
STATIC  volatile VAR(float32, AP_CurrCmd_VAR_NOINIT) MtrCurrQaxRef_Amp_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) PeakTorque_MtrNm_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) MtrVelFilt_RadpSec_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) MRFMtrVelFiltPI_MtrRadpS_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) ElecPosDelayComp_Rad_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) KpqGain_Uls_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) KiqGain_Uls_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) KpdGain_Uls_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) KidGain_Uls_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) MtrVoltQaxFF_Volt_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) MtrVoltDaxFF_Volt_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) IdMin_Amp_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) IqMin_Amp_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) IqMax_Amp_D_f32;
STATIC  volatile VAR(float32, AUTOMATIC) IdMax_Amp_D_f32;
STATIC  volatile  VAR(float32, AUTOMATIC) ImSqMin_AmpSq_D_f32;
STATIC  volatile  VAR(float32, AUTOMATIC) LimitedMRFMtrTrqCmd_MtrNm_D_f32;
STATIC  volatile  VAR(float32, AUTOMATIC) PhsAdvPeak_Rad_D_f32;
/* Module Variables */
STATIC VAR(float32, AUTOMATIC) EstKe_VpRadpS_M_f32;
STATIC VAR(float32, AUTOMATIC) Reluctance_Henry_M_f32;
STATIC VAR(float32, AUTOMATIC) TermXq_Uls_M_f32;
STATIC VAR(float32, AUTOMATIC) TermXd_Uls_M_f32;
STATIC VAR(float32, AUTOMATIC) TermEgR_Amp_M_f32;
STATIC VAR(float32, AUTOMATIC) TermVR2_AmpSq_M_f32;
STATIC VAR(float32, AUTOMATIC) TermEgRZ_Amp_M_f32;
STATIC VAR(float32, AUTOMATIC) TermVRZ_Amp_M_f32 ;
STATIC VAR(float32, AUTOMATIC) TermVR_Amp_M_f32 ;
STATIC VAR(sint32, AP_CurrCmd_VAR_NOINIT) MtrVelFiltFFSV_MtrRadpS_M_s11p20;
STATIC VAR(sint32, AP_CurrCmd_VAR_NOINIT) MtrVelFiltPISV_MtrRadpS_M_s11p20;
STATIC VAR(float32, AUTOMATIC) CosDelta_Cnt_M_f32[D_SIZERDLTAPOINTS_CNT_U16];
STATIC VAR(float32, AUTOMATIC) SinDelta_Cnt_M_f32[D_SIZERDLTAPOINTS_CNT_U16];
VAR(float32, AUTOMATIC) MtrCurrQaxRef_Amp_M_f32[2];
VAR(float32, AUTOMATIC) MtrCurrDaxRef_Amp_M_f32[2];
VAR(float32, AUTOMATIC) MtrDaxIntegralGain_Uls_M_f32[2];
VAR(float32, AUTOMATIC) MtrDaxPropotionalGain_Uls_M_f32[2];
VAR(float32, AUTOMATIC) MtrQaxIntegralGain_Uls_M_f32[2];
VAR(float32, AUTOMATIC) MtrQaxPropotionalGain_Uls_M_f32[2];
VAR(float32, AUTOMATIC) MtrPosComputationDelay_Rad_M_f32[2];
VAR(float32, AUTOMATIC) MtrVoltDaxFF_Volt_M_f32[2];
VAR(float32, AUTOMATIC) MtrVoltQaxFF_Volt_M_f32[2];
STATIC volatile VAR(float32, AUTOMATIC) CurrCmd_IdBoostAmount_Amp_D_f32;
#define CURRCMD_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */

#define CURRCMD_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
VAR(uint16, AUTOMATIC)  FastDataAccessBufIndex_Cnt_M_u16;
STATIC  volatile VAR(uint16, AUTOMATIC) LocateMinImNIter_Cnt_D_u16;
STATIC  volatile VAR(uint16, AUTOMATIC) LocateTrqExNIter_Cnt_D_u16;
STATIC  volatile VAR(uint16, AUTOMATIC) IndexState_Cnt_D_u16;
#define CURRCMD_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) ParabolicInterpolation(P2CONST(float32, AUTOMATIC, AUTOMATIC) IntpolPoints_Uls_T_f32);
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalculateIq(VAR(float32, AUTOMATIC) Torquecmd_MtrNm_T_f32, VAR(float32, AUTOMATIC)IdRef_Amp_T_f32);
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalculateImVSIdq(VAR(float32, AUTOMATIC)IdRef_Amp_T_f32, VAR(float32, AUTOMATIC)IqRef_Amp_T_f32 );
STATIC FUNC(Boolean, AP_CurrCmd_VAR_NOINIT) CurrtoVoltTest(VAR(float32, AUTOMATIC) IqRef_Amp_T_f32 , VAR(float32, AUTOMATIC) IdRef_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) VdR_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC)VqR_Amp_T_f32);
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalcTorque(VAR(float32, AUTOMATIC) CosDelta_Cnt_T_f32, VAR(float32, AUTOMATIC) SinDelta_Cnt_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IdMax_Amp_T_f32);
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) LocateTrqExtremes(VAR(float32, AUTOMATIC) MtrTrqCmd_MtrNm_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IdMax_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) PhsAdvPeak_Rad_T_f32);
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) LocateMinimumIm(VAR(float32, AUTOMATIC) MtrTrqCmd_MtrNm_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IdMin_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IqMin_Amp_T_f32);


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
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
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
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_PI_ULS_F32 = 3.1415926535898
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt8: D_QUADRANT1_CNT_U8 = 1u
 * UInt8: D_QUADRANT2_CNT_U8 = 2u
 * UInt8: D_QUADRANT3_CNT_U8 = 3u
 * UInt8: D_QUADRANT4_CNT_U8 = 4u
 * UInt8: D_ZERO_CNT_U8 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_CURRCMD_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CurrCmd_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRCMD_APPL_CODE) CurrCmd_Init(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CurrCmd_Init
 *********************************************************************************************************************/
 	VAR(uint16, AUTOMATIC) Index_Cnt_T_u16;
	/*** FillBracketArrays ***/
	for (Index_Cnt_T_u16 = D_ZERO_CNT_U16; Index_Cnt_T_u16 < D_SIZERDLTAPOINTS_CNT_U16  ; Index_Cnt_T_u16++)
		{
		CosDelta_Cnt_M_f32[Index_Cnt_T_u16] = cosf(t_RefDeltaPoints_Rad_f32[Index_Cnt_T_u16]);
		SinDelta_Cnt_M_f32[Index_Cnt_T_u16] = sinf(t_RefDeltaPoints_Rad_f32[Index_Cnt_T_u16]);
		
		}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: CurrCmd_Per1
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
 *   Boolean Rte_IRead_CurrCmd_Per1_CurrentGainSvc_Cnt_lgc(void)
 *   Float Rte_IRead_CurrCmd_Per1_EstKe_VpRadpS_f32(void)
 *   Float Rte_IRead_CurrCmd_Per1_EstLd_Henry_f32(void)
 *   Float Rte_IRead_CurrCmd_Per1_EstLq_Henry_f32(void)
 *   Float Rte_IRead_CurrCmd_Per1_EstR_Ohm_f32(void)
 *   Float Rte_IRead_CurrCmd_Per1_MRFMtrVel_MtrRadpS_f32(void)
 *   Float Rte_IRead_CurrCmd_Per1_MRFTrqCmdScl_MtrNm_f32(void)
 *   UInt8 Rte_IRead_CurrCmd_Per1_MtrQuad_Cnt_u08(void)
 *   Float Rte_IRead_CurrCmd_Per1_Vecu_Volt_f32(void)
 *   Float Rte_IRead_CurrCmd_Per1_VehSpd_Kph_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_CurrCmd_Per1_MtrCurrAngle_Rev_f32(Float data)
 *   Float *Rte_IWriteRef_CurrCmd_Per1_MtrCurrAngle_Rev_f32(void)
 *   void Rte_IWrite_CurrCmd_Per1_MtrCurrDaxRef_Amp_f32(Float data)
 *   Float *Rte_IWriteRef_CurrCmd_Per1_MtrCurrDaxRef_Amp_f32(void)
 *   void Rte_IWrite_CurrCmd_Per1_MtrCurrQaxRef_Amp_f32(Float data)
 *   Float *Rte_IWriteRef_CurrCmd_Per1_MtrCurrQaxRef_Amp_f32(void)
 *   void Rte_IWrite_CurrCmd_Per1_MtrTrqCmdSign_Cnt_s16(SInt16 data)
 *   SInt16 *Rte_IWriteRef_CurrCmd_Per1_MtrTrqCmdSign_Cnt_s16(void)
 *   void Rte_IWrite_CurrCmd_Per1_MtrVoltDaxFF_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_CurrCmd_Per1_MtrVoltDaxFF_Volt_f32(void)
 *   void Rte_IWrite_CurrCmd_Per1_MtrVoltQaxFF_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_CurrCmd_Per1_MtrVoltQaxFF_Volt_f32(void)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_CURRCMD_APPL_CODE) CurrCmd_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: CurrCmd_Per1
 *********************************************************************************************************************/
VAR(float32, AUTOMATIC) MRFMtrTrqCmd_MtrNm_T_f32;

VAR(float32, AUTOMATIC) EstR_Ohm_T_f32;
VAR(float32, AUTOMATIC) EstLd_Henry_T_f32;
VAR(float32, AUTOMATIC) EstLq_Henry_T_f32;
VAR(float32, AUTOMATIC) MRFMtrVel_MtrRadpS_T_f32;
VAR(float32, AUTOMATIC) VehSpd_Kph_T_f32;

VAR(float32, AUTOMATIC) MtrCurrDaxRef_Amp_T_f32;
VAR(float32, AUTOMATIC) MtrCurrQaxRef_Amp_T_f32;
VAR(float32, AUTOMATIC) MRFMtrVelFiltFF_MtrRadpS_T_f32;
VAR(float32, AUTOMATIC) KpqGain_Uls_T_f32;
VAR(float32, AUTOMATIC) KiqGain_Uls_T_f32;
VAR(float32, AUTOMATIC) KpdGain_Uls_T_f32;
VAR(float32, AUTOMATIC) KidGain_Uls_T_f32;
VAR(float32, AUTOMATIC) MtrCurrAngle_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrVoltQaxFF_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltDaxFF_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrCurrAngle_Rev_T_f32;
VAR(float32, AUTOMATIC) MtrCurrElecAngle_Rev_T_f32;
VAR(float32, AUTOMATIC)	ElecPosDelayComp_Rad_T_f32;
VAR(sint16, AUTOMATIC) MRFMtrVelFiltPI_MtrRadpS_T_s11p4;
VAR(sint16, AUTOMATIC) MRFMtrVel_MtrRadpS_T_s11p4;
VAR(uint16, AUTOMATIC) KpqGain_Uls_T_u6p10;
VAR(uint16, AUTOMATIC) KiqGain_Uls_T_u10p6;
VAR(uint16, AUTOMATIC) KpdGain_Uls_T_u6p10;
VAR(uint16, AUTOMATIC) KidGain_Uls_T_u10p6;
VAR(float32, AUTOMATIC) Vecu_Volt_T_f32;
VAR(uint8, AUTOMATIC) MtrQuad_Cnt_T_u8;
VAR(uint16, AUTOMATIC) VltgSched_Volt_T_u5p11;
VAR(float32, AUTOMATIC) LimitedMRFMtrTrqCmd_MtrNm_T_f32;

VAR(float32, AUTOMATIC) VdRRef_Amp_T_f32;
VAR(float32, AUTOMATIC) VqRRef_Amp_T_f32;
VAR(float32, AUTOMATIC) VsupplyAvail_Volt_T_f32;
VAR(float32, AUTOMATIC) TermZ_Uls_T_f32;
VAR(float32, AUTOMATIC) PhsAdvPeak_Rad_T_f32;
VAR(float32, AUTOMATIC) PeakTorque_MtrNm_T_f32;
VAR(float32, AUTOMATIC) IqRef_Amp_T_f32;
VAR(float32, AUTOMATIC) ImSqMin_AmpSq_T_f32;
VAR(float32, AUTOMATIC) IdMin_Amp_T_f32;
VAR(float32, AUTOMATIC) IqMin_Amp_T_f32;
VAR(float32, AUTOMATIC) IqMax_Amp_T_f32;
VAR(float32, AUTOMATIC) IntrMtrElec_MtrRadpSpOhm_T_f32;
VAR(float32, AUTOMATIC) IntrMtrElecGain_MtrRadpSpOhm_T_f32;
VAR(uint16, AUTOMATIC) IndexIter_Cnt_T_u16;
VAR(float32, AUTOMATIC) IdRef_Amp_T_f32;
VAR(float32, AUTOMATIC) IdMid_Amp_T_f32;
VAR(float32, AUTOMATIC) IdMax_Amp_T_f32;
VAR(uint16, AUTOMATIC) WriteAccessBufIndex_Cnt_T_u16;
VAR(boolean, AUTOMATIC) CurrentGainSvc_Cnt_T_lgc;
VAR(float32, AUTOMATIC) VdRBoost_Amp_T_f32;
VAR(float32, AUTOMATIC) VqRBoost_Amp_T_f32;
VAR(float32, AUTOMATIC) VRBoostTotal_AmpSq_T_f32;
VAR(float32, AUTOMATIC) VRDelta_Amp_T_f32;
VAR(uint16, AUTOMATIC) LimitedMRFMtrTrqCmd_MtrNm_T_u4p12;
VAR(uint16, AUTOMATIC) IdBoostTrqCharScl_Uls_T_u1p15;
VAR(float32, AUTOMATIC) IdBoostTrqCharScl_Uls_T_f32;
VAR(float32, AUTOMATIC) IdBoostAmount_Amp_T_f32;



/* Configurable Start of Runnable Checkpoint */
Rte_Call_CurrCmd_Per1_CP0_CheckpointReached();

IqRef_Amp_T_f32 =	D_ZERO_ULS_F32;
IdMid_Amp_T_f32 = D_ZERO_ULS_F32;

WriteAccessBufIndex_Cnt_T_u16 = (FastDataAccessBufIndex_Cnt_M_u16&1u)^1u;	
MRFMtrTrqCmd_MtrNm_T_f32=Rte_IRead_CurrCmd_Per1_MRFTrqCmdScl_MtrNm_f32();
MRFMtrVel_MtrRadpS_T_f32=Rte_IRead_CurrCmd_Per1_MRFMtrVel_MtrRadpS_f32();
EstKe_VpRadpS_M_f32=Rte_IRead_CurrCmd_Per1_EstKe_VpRadpS_f32();
EstR_Ohm_T_f32=Rte_IRead_CurrCmd_Per1_EstR_Ohm_f32();
EstLd_Henry_T_f32=Rte_IRead_CurrCmd_Per1_EstLd_Henry_f32();
EstLq_Henry_T_f32=Rte_IRead_CurrCmd_Per1_EstLq_Henry_f32();
VehSpd_Kph_T_f32=Rte_IRead_CurrCmd_Per1_VehSpd_Kph_f32();
Vecu_Volt_T_f32 = Rte_IRead_CurrCmd_Per1_Vecu_Volt_f32();
MtrQuad_Cnt_T_u8 = Rte_IRead_CurrCmd_Per1_MtrQuad_Cnt_u08();
CurrentGainSvc_Cnt_T_lgc = Rte_IRead_CurrCmd_Per1_CurrentGainSvc_Cnt_lgc();

Vecu_Volt_T_f32 = Limit_m(Vecu_Volt_T_f32, D_VECUMIN_VOLTS_F32, D_VECUMAX_VOLTS_F32);
/* Motor Velocity Filter (LPF) */
MRFMtrVel_MtrRadpS_T_s11p4 = FPM_FloatToFixed_m(MRFMtrVel_MtrRadpS_T_f32,s11p4_T);

MtrVelFiltFFSV_MtrRadpS_M_s11p20 = LPF_SvUpdate_s16InFixKTrunc_m(	MRFMtrVel_MtrRadpS_T_s11p4,
																	MtrVelFiltFFSV_MtrRadpS_M_s11p20, 
																	k_MtrVelFiltFFKn_Cnt_u16
																  );

MRFMtrVelFiltFF_MtrRadpS_T_f32 = FPM_FixedToFloat_m(MtrVelFiltFFSV_MtrRadpS_M_s11p20, s11p20_T);

MtrVelFiltPISV_MtrRadpS_M_s11p20 = LPF_SvUpdate_s16InFixKTrunc_m(	MRFMtrVel_MtrRadpS_T_s11p4,
																	MtrVelFiltPISV_MtrRadpS_M_s11p20, 
																	k_MtrVelFiltPIKn_Cnt_u16
																  );
	
MRFMtrVelFiltPI_MtrRadpS_T_s11p4 = (sint16)LPF_OpUpdate_s16InFixKTrunc_m(MtrVelFiltPISV_MtrRadpS_M_s11p20);

MRFMtrVelFiltPI_MtrRadpS_D_f32 = FPM_FixedToFloat_m(MRFMtrVelFiltPI_MtrRadpS_T_s11p4,s11p4_T);
MtrVelFilt_RadpSec_D_f32=MRFMtrVelFiltFF_MtrRadpS_T_f32;

/**** Position Compensation Delay ****/
ElecPosDelayComp_Rad_T_f32=MRFMtrVel_MtrRadpS_T_f32* k_MtrPosComputationDelay_Sec_f32 * (k_NoofPoles_Uls_f32*D_ROUND_ULS_F32);


 if (CurrentGainSvc_Cnt_T_lgc == TRUE)
 {
	KpqGain_Uls_T_f32= D_ZERO_ULS_F32;
	KiqGain_Uls_T_f32= D_ZERO_ULS_F32;						
	KpdGain_Uls_T_f32= D_ZERO_ULS_F32;
	KidGain_Uls_T_f32= D_ZERO_ULS_F32;
  
 }
 else
 {

	/* PI Gain Computation */

	if (VehSpd_Kph_T_f32<k_PIGainVspdCutoff_kph_f32)
	{
		
		
		/* Kpq */
		
					KpqGain_Uls_T_u6p10 = IntplVarXY_u16_u16Xu16Y_Cnt(t_KpqGainX_MtrRadpSec_u12p4, 
																t_KpqGainY_Uls_u6p10, 
																TableSize_m(t_KpqGainX_MtrRadpSec_u12p4),
																Abs_s16_m(MRFMtrVelFiltPI_MtrRadpS_T_s11p4)
														   );    
														   
			
		/*Kiq */												   
														   
					KiqGain_Uls_T_u10p6 = IntplVarXY_u16_u16Xu16Y_Cnt(t_KiqGainX_MtrRadpSec_u12p4, 
																t_KiqGainY_Uls_u10p6, 
																TableSize_m(t_KiqGainX_MtrRadpSec_u12p4),
																Abs_s16_m(MRFMtrVelFiltPI_MtrRadpS_T_s11p4)
														   ); 
					   
														   
		/*Kpd */
					KpdGain_Uls_T_u6p10 = IntplVarXY_u16_u16Xu16Y_Cnt(t_KpdGainX_MtrRadpSec_u12p4, 
																t_KpdGainY_Uls_u6p10, 
																TableSize_m(t_KpdGainX_MtrRadpSec_u12p4),
																Abs_s16_m(MRFMtrVelFiltPI_MtrRadpS_T_s11p4)
														   );    		
		
		/*Kid */
		
					KidGain_Uls_T_u10p6 = IntplVarXY_u16_u16Xu16Y_Cnt(t_KidGainX_MtrRadpSec_u12p4, 
																t_KidGainY_Uls_u10p6, 
																TableSize_m(t_KidGainX_MtrRadpSec_u12p4),
																Abs_s16_m(MRFMtrVelFiltPI_MtrRadpS_T_s11p4)
														   ); 
																					   
														   
		
	}
	else
	{
		
		KpqGain_Uls_T_u6p10=t_KpqGainY_Uls_u6p10[TableSize_m(t_KpqGainY_Uls_u6p10)-1U];
		KiqGain_Uls_T_u10p6=t_KiqGainY_Uls_u10p6[TableSize_m(t_KiqGainY_Uls_u10p6)-1U];
		KpdGain_Uls_T_u6p10=t_KpdGainY_Uls_u6p10[TableSize_m(t_KpdGainY_Uls_u6p10)-1U];
		KidGain_Uls_T_u10p6=t_KidGainY_Uls_u10p6[TableSize_m(t_KidGainY_Uls_u10p6)-1U];
		
	}


	KpqGain_Uls_T_f32= FPM_FixedToFloat_m(KpqGain_Uls_T_u6p10, u6p10_T);
	KiqGain_Uls_T_f32= FPM_FixedToFloat_m(KiqGain_Uls_T_u10p6, u10p6_T);						
	KpdGain_Uls_T_f32= FPM_FixedToFloat_m(KpdGain_Uls_T_u6p10, u6p10_T);
	KidGain_Uls_T_f32= FPM_FixedToFloat_m(KidGain_Uls_T_u10p6, u10p6_T);														   
}

KpqGain_Uls_D_f32 = KpqGain_Uls_T_f32;
KiqGain_Uls_D_f32 = KiqGain_Uls_T_f32;
KpdGain_Uls_D_f32 = KpdGain_Uls_T_f32;
KidGain_Uls_D_f32 =  KidGain_Uls_T_f32;


/*** Voltage Scheduling ***/
 if ((MtrQuad_Cnt_T_u8 == D_QUADRANT1_CNT_U8 )|| (MtrQuad_Cnt_T_u8 == D_QUADRANT3_CNT_U8 ))
 {	
		VltgSched_Volt_T_u5p11 = IntplVarXY_u16_u16Xu16Y_Cnt(t_Q13VltgSchedXTbl_MtrRadpS_u12p4, 
															t_Q13VltgSchedYTbl_Volt_u5p11, 
															TableSize_m(t_Q13VltgSchedXTbl_MtrRadpS_u12p4),
															Abs_s16_m(MRFMtrVel_MtrRadpS_T_s11p4)
													   );  
}
else
{
		VltgSched_Volt_T_u5p11  = IntplVarXY_u16_u16Xu16Y_Cnt(t_Q24VltgSchedXTbl_MtrRadpS_u12p4, 
															t_Q24VltgSchedYTbl_Volt_u5p11, 
															TableSize_m(t_Q24VltgSchedXTbl_MtrRadpS_u12p4),
															Abs_s16_m(MRFMtrVel_MtrRadpS_T_s11p4)
													   );
}

VsupplyAvail_Volt_T_f32 = 	(Vecu_Volt_T_f32 * k_deadtimeVScale_Uls_f32) - (FPM_FixedToFloat_m(VltgSched_Volt_T_u5p11,u5p11_T));


/*** Intermediate Calculations ***/

Reluctance_Henry_M_f32 = (EstLd_Henry_T_f32 - EstLq_Henry_T_f32) *(k_NoofPoles_Uls_f32 * D_ROUND_ULS_F32) ;

/*** TermXq and TermXd Calcultion ***/
IntrMtrElec_MtrRadpSpOhm_T_f32 = MRFMtrVel_MtrRadpS_T_f32/EstR_Ohm_T_f32;
IntrMtrElecGain_MtrRadpSpOhm_T_f32 = IntrMtrElec_MtrRadpSpOhm_T_f32 * (k_NoofPoles_Uls_f32 * D_ROUND_ULS_F32);

TermXd_Uls_M_f32=IntrMtrElecGain_MtrRadpSpOhm_T_f32*EstLd_Henry_T_f32;
TermXq_Uls_M_f32=IntrMtrElecGain_MtrRadpSpOhm_T_f32*EstLq_Henry_T_f32;

/*** Term EgR and Term VR calculation ***/
TermEgR_Amp_M_f32 = IntrMtrElec_MtrRadpSpOhm_T_f32 * EstKe_VpRadpS_M_f32;
TermVR_Amp_M_f32 = VsupplyAvail_Volt_T_f32 / EstR_Ohm_T_f32;
TermVR2_AmpSq_M_f32 = TermVR_Amp_M_f32 * TermVR_Amp_M_f32;

/*** TermZ, Term EgRZ , VRZ calculation ***/
TermZ_Uls_T_f32 = D_ONE_ULS_F32 + (TermXd_Uls_M_f32 * TermXq_Uls_M_f32);
TermEgRZ_Amp_M_f32 = TermEgR_Amp_M_f32 / TermZ_Uls_T_f32;
TermVRZ_Amp_M_f32 =  TermVR_Amp_M_f32 / TermZ_Uls_T_f32;


/*** LocateTorqueExtremes ***/
PeakTorque_MtrNm_T_f32 = LocateTrqExtremes( MRFMtrTrqCmd_MtrNm_T_f32, &IdMax_Amp_T_f32, &PhsAdvPeak_Rad_T_f32);
PeakTorque_MtrNm_D_f32 = PeakTorque_MtrNm_T_f32;
PhsAdvPeak_Rad_D_f32 = PhsAdvPeak_Rad_T_f32;
/*** Limit the peak torque***/
if (Abs_f32_m(MRFMtrTrqCmd_MtrNm_T_f32) < Abs_f32_m(PeakTorque_MtrNm_T_f32))
			
			{
					LimitedMRFMtrTrqCmd_MtrNm_T_f32 = MRFMtrTrqCmd_MtrNm_T_f32;
			}
else 
			{
			        LimitedMRFMtrTrqCmd_MtrNm_T_f32 = PeakTorque_MtrNm_T_f32;   
			}
	

ImSqMin_AmpSq_T_f32 = LocateMinimumIm( LimitedMRFMtrTrqCmd_MtrNm_T_f32, &IdMin_Amp_T_f32, &IqMin_Amp_T_f32);

ImSqMin_AmpSq_D_f32 = ImSqMin_AmpSq_T_f32; 
IqMin_Amp_D_f32 = IqMin_Amp_T_f32;
IdMin_Amp_D_f32 = IdMin_Amp_T_f32;

/**** D axis Current boost****/
if (k_IdBoostGain_Uls_f32 > D_ZERO_ULS_F32)
{
	(void)CurrtoVoltTest(IqMin_Amp_T_f32,IdMin_Amp_T_f32, &VdRBoost_Amp_T_f32, &VqRBoost_Amp_T_f32);
	VRBoostTotal_AmpSq_T_f32 =(VdRBoost_Amp_T_f32 * VdRBoost_Amp_T_f32) + ( VqRBoost_Amp_T_f32*VqRBoost_Amp_T_f32);
	VRDelta_Amp_T_f32 = (__sqrtf(VRBoostTotal_AmpSq_T_f32))-(k_IdBoostVRThreshScl_Uls_f32*TermVR_Amp_M_f32);
	if (VRDelta_Amp_T_f32 >= D_ZERO_ULS_F32)
		{
		   LimitedMRFMtrTrqCmd_MtrNm_T_u4p12 = FPM_FloatToFixed_m((Abs_f32_m(LimitedMRFMtrTrqCmd_MtrNm_T_f32)),u4p12_T);
		   IdBoostTrqCharScl_Uls_T_u1p15 = IntplVarXY_u16_u16Xu16Y_Cnt(t_IdBoostTrqCmdX_MtrNm_u4p12, 
															t_IdBoostTrqCharSclY_Uls_u1p15, 
															TableSize_m(t_IdBoostTrqCmdX_MtrNm_u4p12),
															LimitedMRFMtrTrqCmd_MtrNm_T_u4p12
													   );
			IdBoostTrqCharScl_Uls_T_f32	= FPM_FixedToFloat_m(IdBoostTrqCharScl_Uls_T_u1p15, u1p15_T);		
			
		    IdBoostAmount_Amp_T_f32 = VRDelta_Amp_T_f32 * k_IdBoostGain_Uls_f32 * IdBoostTrqCharScl_Uls_T_f32;
			if ((IdMin_Amp_T_f32-IdBoostAmount_Amp_T_f32) >=  IdMax_Amp_T_f32)
			{
				IdMin_Amp_T_f32 = IdMin_Amp_T_f32-IdBoostAmount_Amp_T_f32;
				IqMin_Amp_T_f32 = CalculateIq(LimitedMRFMtrTrqCmd_MtrNm_T_f32,IdMin_Amp_T_f32);
				
			}
			else
			{
				IdMin_Amp_T_f32 = IdMax_Amp_T_f32;
				IqMin_Amp_T_f32 = CalculateIq(LimitedMRFMtrTrqCmd_MtrNm_T_f32,IdMin_Amp_T_f32);
				
			}
		}
	else
		{
			IdBoostAmount_Amp_T_f32 = D_ZERO_ULS_F32;
		}

}
else
{

	 IdBoostAmount_Amp_T_f32 = D_ZERO_ULS_F32;
}

CurrCmd_IdBoostAmount_Amp_D_f32 = IdBoostAmount_Amp_T_f32 ;



/*** Locate Reference ***/
IqMax_Amp_T_f32= CalculateIq(LimitedMRFMtrTrqCmd_MtrNm_T_f32,IdMax_Amp_T_f32);

IqMax_Amp_D_f32 = IqMax_Amp_T_f32;
IdMax_Amp_D_f32 = IdMax_Amp_T_f32;

if ((CurrtoVoltTest(IqMin_Amp_T_f32,IdMin_Amp_T_f32, &VdRRef_Amp_T_f32, &VqRRef_Amp_T_f32)) == FALSE)
{
	IqRef_Amp_T_f32 = IqMin_Amp_T_f32;
	IdRef_Amp_T_f32 = IdMin_Amp_T_f32;	
}
else if ((CurrtoVoltTest(IqMax_Amp_T_f32,IdMax_Amp_T_f32, &VdRRef_Amp_T_f32,&VqRRef_Amp_T_f32)) == TRUE)
{
	IqRef_Amp_T_f32 = IqMax_Amp_T_f32;
	IdRef_Amp_T_f32 = IdMax_Amp_T_f32;	
}
else
{
  for (IndexIter_Cnt_T_u16= D_ZERO_CNT_U16; IndexIter_Cnt_T_u16 < k_IdqRefLocateRefNIter_Cnt_u16;IndexIter_Cnt_T_u16++)
  {
   IdMid_Amp_T_f32 = (IdMax_Amp_T_f32 + IdMin_Amp_T_f32) / 2.0F;
   IqRef_Amp_T_f32 = CalculateIq( LimitedMRFMtrTrqCmd_MtrNm_T_f32,IdMid_Amp_T_f32);
   if (CurrtoVoltTest(IqRef_Amp_T_f32,IdMid_Amp_T_f32, &VdRRef_Amp_T_f32,&VqRRef_Amp_T_f32) == TRUE)
	   {
			IdMin_Amp_T_f32 = IdMid_Amp_T_f32;
	   }
   else
	   {
			IdMax_Amp_T_f32 = IdMid_Amp_T_f32;
	   }	   
  }
  IdRef_Amp_T_f32 = IdMid_Amp_T_f32;
}


/*** Calculate Qax and Dax Refernce***/
MtrCurrQaxRef_Amp_T_f32 = IqRef_Amp_T_f32 * D_2OVRSQRT3_ULS_F32;
MtrCurrDaxRef_Amp_T_f32 = IdRef_Amp_T_f32 * D_NEG2OVRSQRT3_ULS_F32;


MtrCurrQaxRef_Amp_T_f32=Limit_m(MtrCurrQaxRef_Amp_T_f32,-D_MAXCURRENT_AMP_F32,D_MAXCURRENT_AMP_F32);
MtrCurrDaxRef_Amp_T_f32=Limit_m(MtrCurrDaxRef_Amp_T_f32,-D_MAXCURRENT_AMP_F32,D_MAXCURRENT_AMP_F32);

MtrCurrQaxRef_Amp_D_f32=MtrCurrQaxRef_Amp_T_f32;
MtrCurrDaxRef_Amp_D_f32=MtrCurrDaxRef_Amp_T_f32;

MtrVoltDaxFF_Volt_T_f32 = VdRRef_Amp_T_f32 * EstR_Ohm_T_f32 ;
MtrVoltQaxFF_Volt_T_f32 = VqRRef_Amp_T_f32 * EstR_Ohm_T_f32;

/* Motor CurrentAngle Computation */

MtrCurrAngle_Rad_T_f32 = atan2f(MtrCurrDaxRef_Amp_T_f32, MtrCurrQaxRef_Amp_T_f32);

if (MtrCurrAngle_Rad_T_f32 < D_ZERO_ULS_F32)
{
    MtrCurrAngle_Rev_T_f32= ((MtrCurrAngle_Rad_T_f32  + D_2PI_ULS_F32)/D_2PI_ULS_F32);
}
else
{
	MtrCurrAngle_Rev_T_f32 =(MtrCurrAngle_Rad_T_f32/D_2PI_ULS_F32);
}

MtrCurrElecAngle_Rev_T_f32=MtrCurrAngle_Rev_T_f32;
/*** Assign to display variables***/
ElecPosDelayComp_Rad_D_f32 = ElecPosDelayComp_Rad_T_f32;
MtrVoltDaxFF_Volt_D_f32 = MtrVoltDaxFF_Volt_T_f32 ;
MtrVoltQaxFF_Volt_D_f32 =  MtrVoltQaxFF_Volt_T_f32;
LimitedMRFMtrTrqCmd_MtrNm_D_f32 =LimitedMRFMtrTrqCmd_MtrNm_T_f32;


/*Writing the  current command output */

MtrDaxIntegralGain_Uls_M_f32[WriteAccessBufIndex_Cnt_T_u16] = KidGain_Uls_T_f32;
MtrDaxPropotionalGain_Uls_M_f32[WriteAccessBufIndex_Cnt_T_u16] = KpdGain_Uls_T_f32;
MtrQaxIntegralGain_Uls_M_f32[WriteAccessBufIndex_Cnt_T_u16] = KiqGain_Uls_T_f32;
MtrQaxPropotionalGain_Uls_M_f32[WriteAccessBufIndex_Cnt_T_u16] = KpqGain_Uls_T_f32;
MtrCurrQaxRef_Amp_M_f32[WriteAccessBufIndex_Cnt_T_u16] = MtrCurrQaxRef_Amp_T_f32;
MtrCurrDaxRef_Amp_M_f32[WriteAccessBufIndex_Cnt_T_u16] = MtrCurrDaxRef_Amp_T_f32;
Rte_IWrite_CurrCmd_Per1_MtrCurrDaxRef_Amp_f32(MtrCurrDaxRef_Amp_T_f32);
Rte_IWrite_CurrCmd_Per1_MtrCurrQaxRef_Amp_f32(MtrCurrQaxRef_Amp_T_f32);
MtrVoltDaxFF_Volt_M_f32[WriteAccessBufIndex_Cnt_T_u16]=MtrVoltDaxFF_Volt_T_f32;
MtrVoltQaxFF_Volt_M_f32[WriteAccessBufIndex_Cnt_T_u16]=MtrVoltQaxFF_Volt_T_f32;
Rte_IWrite_CurrCmd_Per1_MtrVoltDaxFF_Volt_f32(MtrVoltDaxFF_Volt_T_f32);
Rte_IWrite_CurrCmd_Per1_MtrVoltQaxFF_Volt_f32(MtrVoltQaxFF_Volt_T_f32);
Rte_IWrite_CurrCmd_Per1_MtrCurrAngle_Rev_f32(MtrCurrElecAngle_Rev_T_f32);
Rte_IWrite_CurrCmd_Per1_MtrTrqCmdSign_Cnt_s16(Sign_f32_m(MRFMtrTrqCmd_MtrNm_T_f32));
MtrPosComputationDelay_Rad_M_f32[WriteAccessBufIndex_Cnt_T_u16] = ElecPosDelayComp_Rad_T_f32;


/* Configurable End of Runnable Checkpoint */
Rte_Call_CurrCmd_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_CURRCMD_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
 /*****************************************************************************
 *
 *  Function Name:     ParabolicInterpolation
 *	
 *  Description:       
 *
 *  Inputs:            IntpolPoints_Uls_T_f32
 *
 *  Outputs:           ParaIntpol_Uls_T_f32
 *
 *****************************************************************************/
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) ParabolicInterpolation(P2CONST(float32, AUTOMATIC, AUTOMATIC) IntpolPoints_Uls_T_f32)
{
	VAR(float32, AUTOMATIC) ParaIntpol_Uls_T_f32;
	VAR(float32, AUTOMATIC) Num_Uls_T_f32;
	VAR(float32, AUTOMATIC) Den1_Uls_T_f32;
	VAR(float32, AUTOMATIC) Den2_Uls_T_f32;
	VAR(float32, AUTOMATIC) Den_Uls_T_f32;
	VAR(float32, AUTOMATIC) TermF1_Uls_T_f32;
	VAR(float32, AUTOMATIC) TermF2_Uls_T_f32;
	VAR(float32, AUTOMATIC) TermX1_Uls_T_f32;
	VAR(float32, AUTOMATIC) TermX2_Uls_T_f32;
	
	/*** Calculate Intermediate Terms ***/
	TermF1_Uls_T_f32 = (IntpolPoints_Uls_T_f32[1] - IntpolPoints_Uls_T_f32[3]);
	TermF2_Uls_T_f32 = (IntpolPoints_Uls_T_f32[3] - IntpolPoints_Uls_T_f32[5]);
	TermX1_Uls_T_f32 = (IntpolPoints_Uls_T_f32[0] - IntpolPoints_Uls_T_f32[2]);
	TermX2_Uls_T_f32 = (IntpolPoints_Uls_T_f32[2] - IntpolPoints_Uls_T_f32[4]);
	
	/*** Calculate Numerator and denominator for Interpolation for Parabolic interpolation***/
	Den1_Uls_T_f32 = TermF2_Uls_T_f32 * TermX1_Uls_T_f32;
	Den2_Uls_T_f32 =  TermF1_Uls_T_f32 * TermX2_Uls_T_f32;

	Num_Uls_T_f32 = (Den1_Uls_T_f32 * TermX1_Uls_T_f32) + (Den2_Uls_T_f32 *TermX2_Uls_T_f32) ;
	Den_Uls_T_f32 = 2.0F * (Den1_Uls_T_f32 - Den2_Uls_T_f32);

	/*** calculate Parabolic inetrpolation ***/ 
	if (Abs_f32_m(Den_Uls_T_f32) > FLT_EPSILON)
	{
		ParaIntpol_Uls_T_f32= (Num_Uls_T_f32/ Den_Uls_T_f32)+ IntpolPoints_Uls_T_f32[2];
	}
	else
	{
	    ParaIntpol_Uls_T_f32 = 1.0F/FLT_EPSILON;
	}

	return ParaIntpol_Uls_T_f32;
}

/*****************************************************************************
 *
 *  Function Name:     CalculateImVSIdq
 *	
 *  Description:       
 *
 *  Inputs:            IdRef_Amp_T_f32,IqRef_Amp_T_f32
 *
 *  Outputs:           ImVSIdq_AmpSq_T_f32
 *
 *****************************************************************************/

STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalculateImVSIdq( VAR(float32, AUTOMATIC)IdRef_Amp_T_f32, VAR(float32, AUTOMATIC)IqRef_Amp_T_f32 )
{
	
   VAR(float32, AUTOMATIC) ImVSIdq_AmpSq_T_f32;
  
  /*** F_IMVSIdq Block***/
  ImVSIdq_AmpSq_T_f32 = ((IqRef_Amp_T_f32) * (IqRef_Amp_T_f32)) + ((IdRef_Amp_T_f32) * (IdRef_Amp_T_f32));
  
  
  return  ImVSIdq_AmpSq_T_f32;
}

/*****************************************************************************
 *
 *  Function Name:     CalculateIq
 *	
 *  Description:       
 *
 *  Inputs:            Torquecmd_MtrNm_T_f32, IdRef_Amp_T_f32
 *
 *  Outputs:           IqRef_Amp_T_f32
 *
 *****************************************************************************/

STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalculateIq(VAR(float32, AUTOMATIC) Torquecmd_MtrNm_T_f32, VAR(float32, AUTOMATIC)IdRef_Amp_T_f32 )
{
   VAR(float32, AUTOMATIC) IqRefTmp_Amp_T_f32;	
   /*** Calculate Iq Reference***/  
  IqRefTmp_Amp_T_f32 = Torquecmd_MtrNm_T_f32/(EstKe_VpRadpS_M_f32 + (Reluctance_Henry_M_f32 * (IdRef_Amp_T_f32)));
   
  return  IqRefTmp_Amp_T_f32;
}

/*****************************************************************************
 *
 *  Function Name:     CurrtoVoltTest
 *	
 *  Description:       
 *
 *  Inputs:            MtrTrqCmd_MtrNm_T_f32,IqRef_Amp_T_f32,IdRef_Amp_T_f32
 *
 *  Outputs:           VqR_Amp_T_f32,VdR_Amp_T_f32,VoltTest_Uls_T_lgc
 *
 *****************************************************************************/

STATIC FUNC(Boolean, AP_CurrCmd_VAR_NOINIT) CurrtoVoltTest(VAR(float32, AUTOMATIC) IqRef_Amp_T_f32 , VAR(float32, AUTOMATIC) IdRef_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) VdR_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC)VqR_Amp_T_f32)
{
  VAR(boolean, AUTOMATIC) VoltTest_Uls_T_lgc;
  VAR(float32, AUTOMATIC) Vdq_AmpSq_T_f32;
  VAR(float32, AUTOMATIC)   VqRTemp_Amp_T_f32;
  VAR(float32, AUTOMATIC)   VdRTemp_Amp_T_f32;
  /*** Convert the Iq and Id to VqR and VdR respectively ***/
  VdRTemp_Amp_T_f32 = (IqRef_Amp_T_f32 * TermXq_Uls_M_f32) - IdRef_Amp_T_f32;
  VqRTemp_Amp_T_f32=  IqRef_Amp_T_f32 + (IdRef_Amp_T_f32 * TermXd_Uls_M_f32)+TermEgR_Amp_M_f32;
   
  Vdq_AmpSq_T_f32 =  ((VqRTemp_Amp_T_f32) * (VqRTemp_Amp_T_f32)) + ((VdRTemp_Amp_T_f32) * (VdRTemp_Amp_T_f32));
  /*** voltage Test  block***/
   if ((Vdq_AmpSq_T_f32 < TermVR2_AmpSq_M_f32))
		{
			VoltTest_Uls_T_lgc = FALSE;
		}
	else
	    {
			VoltTest_Uls_T_lgc = TRUE;		   
		}
	*VdR_Amp_T_f32 = VdRTemp_Amp_T_f32;
	*VqR_Amp_T_f32 = VqRTemp_Amp_T_f32;
	return 	VoltTest_Uls_T_lgc;
}

/*****************************************************************************
 *
 *  Function Name:     CalcTorque
 *	
 *  Description:       
 *
 *  Inputs:           CosDelta_Cnt_T_f32, SinDelta_Cnt_T_f32
 *
 *  Outputs:           IdMax_Amp_T_f32,TorqueCalc_MtrNm_T_f32
 *
 *****************************************************************************/
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) CalcTorque(VAR(float32, AUTOMATIC) CosDelta_Cnt_T_f32, VAR(float32, AUTOMATIC) SinDelta_Cnt_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IdMax_Amp_T_f32)
	
{

   VAR(float32, AUTOMATIC) TorqueCalc_MtrNm_T_f32;
   VAR(float32, AUTOMATIC) IqAxis_Amp_T_f32;
   VAR(float32, AUTOMATIC) IdAxis_Amp_T_f32;
   
   /*** Calculate Iq current, Id current ***/
   IqAxis_Amp_T_f32 = ((CosDelta_Cnt_T_f32 + ( TermXd_Uls_M_f32 * SinDelta_Cnt_T_f32)) * TermVRZ_Amp_M_f32) - TermEgRZ_Amp_M_f32;
   IdAxis_Amp_T_f32 =  (IqAxis_Amp_T_f32 * TermXq_Uls_M_f32) - (TermVR_Amp_M_f32 *SinDelta_Cnt_T_f32);
   /***Calculate Torque ***/	
   TorqueCalc_MtrNm_T_f32 = (EstKe_VpRadpS_M_f32 + (Reluctance_Henry_M_f32 *  IdAxis_Amp_T_f32) ) * IqAxis_Amp_T_f32;
   
   *IdMax_Amp_T_f32 = IdAxis_Amp_T_f32;
   return TorqueCalc_MtrNm_T_f32;

}	

/*****************************************************************************
 *
 *  Function Name:     LocateTrqExtremes
 *	
 *  Description:       
 *
 *  Inputs:            MtrTrqCmd_MtrNm_T_f32
 *
 *  Outputs:           IdMax_Amp_T_f32, PhsAdvPeak_Rad_T_f32,TorqueState_MtrNm_T_f32
 *
 *****************************************************************************/
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) LocateTrqExtremes(VAR(float32, AUTOMATIC) MtrTrqCmd_MtrNm_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IdMax_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) PhsAdvPeak_Rad_T_f32)

{
 	VAR(float32, AUTOMATIC)  NewDelta_Rad_T_f32;
    VAR(uint16,AUTOMATIC) Index_Cnt_T_u16;
	VAR(float32, AUTOMATIC) TorqueCalcTbl_MtrNm_T_f32[D_SIZERDLTAPOINTS_CNT_U16];
	VAR(float32, AUTOMATIC) TorqueState_MtrNm_T_f32 ;
	VAR(uint16, AUTOMATIC) IndexState_Cnt_T_u16 ;
	VAR(float32, AUTOMATIC) IntpolPoints_Uls_T_f32[6];
	VAR(float32, AUTOMATIC) PreNewDelta_Rad_T_f32;
	VAR(uint16,AUTOMATIC) IndexIter_Cnt_T_u16 ;
	VAR(float32, AUTOMATIC) NewSinDelta_Rad_T_f32;
	VAR(float32, AUTOMATIC) NewCosDelta_Rad_T_f32;
	
	IndexIter_Cnt_T_u16 = D_ZERO_CNT_U16;
	TorqueState_MtrNm_T_f32 = D_ZERO_ULS_F32;
	IndexState_Cnt_T_u16 = D_ZERO_CNT_U16;
	/***_FindPeakTorques***/
	if (MtrTrqCmd_MtrNm_T_f32 >= D_ZERO_ULS_F32)
	
	{   
		for (Index_Cnt_T_u16=D_ZERO_CNT_U16; Index_Cnt_T_u16<D_SIZERDLTAPOINTS_CNT_U16; Index_Cnt_T_u16++)
		
		{   /*** CalculateTorque ***/
			TorqueCalcTbl_MtrNm_T_f32[Index_Cnt_T_u16] = CalcTorque (CosDelta_Cnt_M_f32[Index_Cnt_T_u16],SinDelta_Cnt_M_f32 [Index_Cnt_T_u16],IdMax_Amp_T_f32);
			if (TorqueCalcTbl_MtrNm_T_f32[Index_Cnt_T_u16] >= TorqueState_MtrNm_T_f32)
			{
				TorqueState_MtrNm_T_f32 = TorqueCalcTbl_MtrNm_T_f32[Index_Cnt_T_u16];
				IndexState_Cnt_T_u16 = Index_Cnt_T_u16;
			}
		}
 
	}
	else
	
	{
		for (Index_Cnt_T_u16=D_ZERO_CNT_U16; Index_Cnt_T_u16<D_SIZERDLTAPOINTS_CNT_U16; Index_Cnt_T_u16++)
		
		
		{   /*** CalculateTorque***/
			TorqueCalcTbl_MtrNm_T_f32[Index_Cnt_T_u16] = CalcTorque (CosDelta_Cnt_M_f32[Index_Cnt_T_u16],SinDelta_Cnt_M_f32[Index_Cnt_T_u16],IdMax_Amp_T_f32);
			if (TorqueCalcTbl_MtrNm_T_f32[Index_Cnt_T_u16] <= TorqueState_MtrNm_T_f32)
			{
				TorqueState_MtrNm_T_f32 = TorqueCalcTbl_MtrNm_T_f32[Index_Cnt_T_u16];
				IndexState_Cnt_T_u16 = Index_Cnt_T_u16;
			}
		}
	
	}

   IndexState_Cnt_D_u16 =IndexState_Cnt_T_u16;
	/*** ChooseDeltaBrackets ***/
	IntpolPoints_Uls_T_f32[2] = t_RefDeltaPoints_Rad_f32[IndexState_Cnt_T_u16];
	IntpolPoints_Uls_T_f32[3] = TorqueCalcTbl_MtrNm_T_f32[IndexState_Cnt_T_u16];
	/*** Index if zero ***/
	if 	(IndexState_Cnt_T_u16 == D_ZERO_CNT_U16)
	{
		IntpolPoints_Uls_T_f32[4] = -D_PIPLUSPIOVER4_ULS_F32 ;
		IntpolPoints_Uls_T_f32[5] = TorqueCalcTbl_MtrNm_T_f32[D_MAXDELTAPOINTSSIZE_CNT_U16];
		IntpolPoints_Uls_T_f32[0] = t_RefDeltaPoints_Rad_f32[1U];
		IntpolPoints_Uls_T_f32[1] = TorqueCalcTbl_MtrNm_T_f32[1U];
	}
	/*** Index if reaches limit of the table ***/
	else if (IndexState_Cnt_T_u16 == (D_MAXDELTAPOINTSSIZE_CNT_U16))
	{
	
		IntpolPoints_Uls_T_f32[0] = D_PI_ULS_F32;
		IntpolPoints_Uls_T_f32[1] = TorqueCalcTbl_MtrNm_T_f32[D_ZERO_CNT_U16];
		IntpolPoints_Uls_T_f32[4] = t_RefDeltaPoints_Rad_f32[D_MAXDELTAPOINTSSIZE_CNT_U16-1U];
		IntpolPoints_Uls_T_f32[5] = TorqueCalcTbl_MtrNm_T_f32[D_MAXDELTAPOINTSSIZE_CNT_U16-1U];
		
		
	}
	/*** Finding out interpolation points for parabola ***/
	else
	{
		IntpolPoints_Uls_T_f32[0] = t_RefDeltaPoints_Rad_f32[IndexState_Cnt_T_u16+1U];
		IntpolPoints_Uls_T_f32[1] = TorqueCalcTbl_MtrNm_T_f32[IndexState_Cnt_T_u16+1U];
		IntpolPoints_Uls_T_f32[4] = t_RefDeltaPoints_Rad_f32[IndexState_Cnt_T_u16 - 1U];
		IntpolPoints_Uls_T_f32[5] = TorqueCalcTbl_MtrNm_T_f32[IndexState_Cnt_T_u16 - 1U];
	}
    	
	/*** WhileIteratorSubsystem ***/
	do 
	{
		NewDelta_Rad_T_f32 = ParabolicInterpolation(IntpolPoints_Uls_T_f32);
		NewSinDelta_Rad_T_f32 = sinf(NewDelta_Rad_T_f32);
		NewCosDelta_Rad_T_f32 = cosf(NewDelta_Rad_T_f32);
		/*** CalculateTorque***/
		TorqueState_MtrNm_T_f32 = CalcTorque (NewCosDelta_Rad_T_f32,NewSinDelta_Rad_T_f32,IdMax_Amp_T_f32);
		PreNewDelta_Rad_T_f32 = IntpolPoints_Uls_T_f32[2];
		if ((NewDelta_Rad_T_f32 - IntpolPoints_Uls_T_f32[2])> D_ZERO_ULS_F32)
				{
				IntpolPoints_Uls_T_f32[4] = IntpolPoints_Uls_T_f32[2];
				IntpolPoints_Uls_T_f32[5] = IntpolPoints_Uls_T_f32[3];
				}
		else
				{
				IntpolPoints_Uls_T_f32[0] = IntpolPoints_Uls_T_f32[2];
				IntpolPoints_Uls_T_f32[1] = IntpolPoints_Uls_T_f32[3];
				}
		IntpolPoints_Uls_T_f32[2] = NewDelta_Rad_T_f32;
		IntpolPoints_Uls_T_f32[3] = TorqueState_MtrNm_T_f32;
		IndexIter_Cnt_T_u16	++;
	} while ((Abs_f32_m((PreNewDelta_Rad_T_f32 - IntpolPoints_Uls_T_f32[2]))>k_IdqRefTrqTol_Rad_f32) && ((IndexIter_Cnt_T_u16 <k_IdqRefTrqNIter_Cnt_u16)));
	
	*PhsAdvPeak_Rad_T_f32 = NewDelta_Rad_T_f32;
	LocateTrqExNIter_Cnt_D_u16 = IndexIter_Cnt_T_u16;
    return(TorqueState_MtrNm_T_f32);
	
}



/*****************************************************************************
 *
 *  Function Name:     LocateMinimumIm
 *	
 *  Description:       
 *
 *  Inputs:            MtrTrqCmd_MtrNm_T_f32
 *
 *  Outputs:           IdMin_Amp_T_f32, IqMin_Amp_T_f32, ImSqrMin_AmpSq_T_f32
 *
 *****************************************************************************/
 
STATIC FUNC(float32, AP_CurrCmd_VAR_NOINIT) LocateMinimumIm(VAR(float32, AUTOMATIC) MtrTrqCmd_MtrNm_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IdMin_Amp_T_f32, P2VAR(float32, AUTOMATIC, AUTOMATIC) IqMin_Amp_T_f32)

{
	VAR(float32, AUTOMATIC) IdRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) UpperImVSIdq_AmpSq_T_f32;
	VAR(float32, AUTOMATIC) LocateMinimumIm_Cnt_T_f32[6];
	VAR(float32, AUTOMATIC) UpperIqRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) MidIqRef_Amp_T_f32;	
	VAR(float32, AUTOMATIC) MidImVSIdq_AmpSq_T_f32;
	VAR(float32, AUTOMATIC) IdMinTmp_Amp_T_f32;
	VAR(float32, AUTOMATIC) IqMinTmp_Amp_T_f32;	
	VAR(float32, AUTOMATIC) ImSqrMin_AmpSq_T_f32;
	VAR(uint16, AUTOMATIC) Index_Cnt_T_u16=D_ZERO_CNT_U16;
	VAR(float32, AUTOMATIC)	IdMinoldTmp_Amp_T_f32;
	/*** Calculate Id ***/
	IdRef_Amp_T_f32 =  Abs_f32_m(MtrTrqCmd_MtrNm_T_f32) / EstKe_VpRadpS_M_f32; 
	
	/*** calculate Upper Iq Ref boundary ***/
	UpperIqRef_Amp_T_f32 = CalculateIq( MtrTrqCmd_MtrNm_T_f32, (IdRef_Amp_T_f32 * (D_NEG_ULS_F32)) );
	UpperImVSIdq_AmpSq_T_f32 = CalculateImVSIdq((IdRef_Amp_T_f32 * (D_NEG_ULS_F32)), UpperIqRef_Amp_T_f32 );
	
	if ((IdRef_Amp_T_f32 - k_IdqRefIminTol_Amp_f32) < D_ZERO_ULS_F32)
	{
	ImSqrMin_AmpSq_T_f32 = UpperImVSIdq_AmpSq_T_f32;
	*IqMin_Amp_T_f32 =  UpperIqRef_Amp_T_f32;
	*IdMin_Amp_T_f32 =  -IdRef_Amp_T_f32;
	LocateMinImNIter_Cnt_D_u16 = Index_Cnt_T_u16;
	}
	else
	{
	MidIqRef_Amp_T_f32 = CalculateIq( MtrTrqCmd_MtrNm_T_f32, (IdRef_Amp_T_f32 * D_NEGROUND_ULS_F32));
	MidImVSIdq_AmpSq_T_f32 = CalculateImVSIdq((IdRef_Amp_T_f32 * D_NEGROUND_ULS_F32), MidIqRef_Amp_T_f32 );
	LocateMinimumIm_Cnt_T_f32[0] = -IdRef_Amp_T_f32;
	LocateMinimumIm_Cnt_T_f32[1] =  UpperImVSIdq_AmpSq_T_f32;
	LocateMinimumIm_Cnt_T_f32[2] = IdRef_Amp_T_f32 * D_NEGROUND_ULS_F32;
	LocateMinimumIm_Cnt_T_f32[3] = MidImVSIdq_AmpSq_T_f32;
	LocateMinimumIm_Cnt_T_f32[4] = D_ZERO_ULS_F32;
	LocateMinimumIm_Cnt_T_f32[5] = IdRef_Amp_T_f32 * IdRef_Amp_T_f32;
	do 
		{   /*** Parabolic Inetrpolation ***/
		IdMinTmp_Amp_T_f32 = ParabolicInterpolation(LocateMinimumIm_Cnt_T_f32);
		IqMinTmp_Amp_T_f32 = CalculateIq( MtrTrqCmd_MtrNm_T_f32,IdMinTmp_Amp_T_f32 );
		ImSqrMin_AmpSq_T_f32 = CalculateImVSIdq( IdMinTmp_Amp_T_f32 , IqMinTmp_Amp_T_f32 );
		/*** Find points for Parabolic Inetrpolation ***/
		IdMinoldTmp_Amp_T_f32 = LocateMinimumIm_Cnt_T_f32[2];
		if ((IdMinTmp_Amp_T_f32 - LocateMinimumIm_Cnt_T_f32[2])> D_ZERO_ULS_F32)
				{
				LocateMinimumIm_Cnt_T_f32[4] = LocateMinimumIm_Cnt_T_f32[2];
				LocateMinimumIm_Cnt_T_f32[5] = LocateMinimumIm_Cnt_T_f32[3];
				}
		else
				{
				LocateMinimumIm_Cnt_T_f32[0] = LocateMinimumIm_Cnt_T_f32[2];
				LocateMinimumIm_Cnt_T_f32[1] = LocateMinimumIm_Cnt_T_f32[3];
				}
		LocateMinimumIm_Cnt_T_f32[2] = IdMinTmp_Amp_T_f32;
		LocateMinimumIm_Cnt_T_f32[3] = ImSqrMin_AmpSq_T_f32;
		Index_Cnt_T_u16 ++;
		
		} while((Abs_f32_m((IdMinoldTmp_Amp_T_f32 - LocateMinimumIm_Cnt_T_f32[2]))> k_IdqRefIminTol_Amp_f32) && (Index_Cnt_T_u16 <k_IdqRefIminNIter_Cnt_u16));
	
	 /*** Assign the outputs back***/
	*IqMin_Amp_T_f32 = IqMinTmp_Amp_T_f32;
	*IdMin_Amp_T_f32 = IdMinTmp_Amp_T_f32;
	LocateMinImNIter_Cnt_D_u16 = Index_Cnt_T_u16;
	}
	
	
	return (ImSqrMin_AmpSq_T_f32);
	
}
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
