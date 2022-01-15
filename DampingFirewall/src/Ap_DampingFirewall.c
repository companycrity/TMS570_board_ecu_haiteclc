/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_DampingFirewall.c
 *     Workspace:  C:/Synergy_projects/DampingFirewall-lz4p8n/DampingFirewall/autosar/Ap_DampingFirewall.dcf
 *     SW-C Type:  Ap_DampingFirewall
 *  Generated at:  Tue May 14 16:41:29 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_DampingFirewall>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * Date Created:      Mon Apr 25 13:00:00 2012
 * %version:          24 %
 * %derived_by:       gzkys7 %
 * %date_modified:    Mon Nov 18 14:29:42 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev     Author    Change Description                                                                SCR #
 * -------   ------  --------  --------------------------------------------------------------------------------  ------
 * 04/26/12  1       OT        Initial Version                                                                   5300
 * 05/08/12  2       OT        Fixed UTP Issues (naming consistency)                                             5300
 * 05/10/12  3       OT        Fixed calibration naming conflict
 * 05/18/12  4       OT        Fixed anomaly 3324 (using wrong variable for boundary calcs)                      5469
 * 05/22/12  5       OT        Updated to SF-35 V002 (anomaly 3325)                                              5469
 * 05/25/12  6       JW        Updated to SF-35 V003
 * 05/31/12  7       OT        Updated to SF-35 V004                                                             5586
 * 08/08/12  8       NRAR      Updated to SF-35 V004                                                             5904
 * 08/28/12  9		 KJS	   Updated to SF-35 V006. Removed input limit on inertia comp input for VBIC		 6117
 * 							   limiter. Added multiple display variables. Variable name changes for state
 * 							   variables for filter.
 * 09/16/12  10      BWL       Added watchdog checkpoints                                                        6219
 * 11/09/12  11      SR	       Correction to Memmap statement							 						 6736
 * 02/04/13	 14      VK		   Updated to SF-35 V007														 	 7209
 * 02/08/13  15      VK		   QAC fixes																		 7209
 * 02/08/13	 16      VK		   Calibration changes																 7209
 * 04/16/13	 17		 SP		   Anomaly 4407 fixes																 7882
 * 04/16/13  18      LN        Corrected Diverse VBIC calculation issues (anomaly 4809) 						 7926
 * 04/30/13	 19		 SP		   Anomaly 4913 fixes																 8118
 * 06/07/13	 19.1.1  JJW	   VBIC Error filter robustness change
 * 05/14/13  20		 SP		   Updated to SF-35 V008, Generate Command calculation changed to fixed point		 7819
 * 06/17/13  21      SP        Updated to SF-35 V009, undone the Generate Command calculation changes from v 8.0  	8649
 * 10/03/13  22      KMC       Updated to SF-35 v010 -- add filtering on UprBound and LwrBound                   10329
 * 11/18/13  23		 SP		   Fixed Anomaly 5206																 10695
 * 08/29/14  13      SB		   Anomaly 6259 correction															 12391
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Rte_Ap_DampingFirewall.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

#include "Ap_DampingFirewall_Cfg.h"
#include "CalConstants.h"
#include "GlobalMacro.h"
#include "fixmath.h"
#include "filters.h"
#include "interpolation.h"
#include <float.h>

#define D_ONEOVR2MS_SEC_U9P7					FPM_InitFixedPoint_m(500.0, u9p7_T)
#define D_2MS_SEC_U0P16							FPM_InitFixedPoint_m(0.002, u0p16_T)
#define D_2MS_SEC_U2P14							FPM_InitFixedPoint_m(0.002, u2p14_T)
#define D_PIOVR180_ULS_S4P11					FPM_InitFixedPoint_m(0.0174532925199, s4p11_T)	
#define D_ONE_ULS_U2P14							FPM_InitFixedPoint_m(1.0, u2p14_T)
#define D_ONE_ULS_U8P8							FPM_InitFixedPoint_m(1.0, u8p8_T)
#define D_ONE_ULS_U5P11							FPM_InitFixedPoint_m(1.0, u5p11_T)
#define D_TWO_ULS_S2P13							FPM_InitFixedPoint_m(2.0, s2p13_T)
#define D_2PI_ULS_U3P13							FPM_InitFixedPoint_m(6.2831853071796, u3p13_T)
#define D_ONE_ULS_U22P10						FPM_InitFixedPoint_m(1.0, u22p10_T)
#define D_TBARVELFILTVAL_HWDEGPSEC_S15P16		FPM_InitFixedPoint_m(1024.0, s15p16_T)
#define D_TERMA_MTRRADPSEC_S20P11				FPM_InitFixedPoint_m(4095.875, s20p11_T)
#define D_FDDADDCOEFTBLSIZE_ULS_U8				10U
#define D_EIGHT_ULS_U10P6						FPM_InitFixedPoint_m(8.0, u10p6_T)
#define D_SCALEDDRIVERVEL_MTRRADPS_S17P14		FPM_InitFixedPoint_m(10000.0, s17p14_T)
#define D_COMPENSATIONLIMIT_MTRNM_S11P20		FPM_InitFixedPoint_m(8.8, s11p20_T)
#define D_INERTIACOMPCALCLIMIT_MTRNM_U15P1		FPM_InitFixedPoint_m(8.8, u15p1_T)
#define D_FOUR_ULS_S3P12						FPM_InitFixedPoint_m(4.0, s3p12_T)
#define D_ADDCOEFCALCHILIMIT_MTRNMSPRAD_U1P15	FPM_InitFixedPoint_m(0.05, u1p15_T)
#define D_ADDCOEFCALCHILIMIT_MTRNMSPRAD_U3P13	FPM_InitFixedPoint_m(0.05, u3p13_T)
#define D_ABSSCALEDRIVERVELHI_MTRRADPS_U15P1	FPM_InitFixedPoint_m(4095.5, u15p1_T)
#define VEHICLELONACCEL_MIN_F32					(-64.0F)
#define VEHICLELONACCEL_MAX_F32					63.99804F

#define DAMPINGFIREWALL_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
/* Test Point Display Variable */
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWUprBound_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWLwrBound_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWUprBoundFilt_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWLwrBoundFilt_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWAddedDamp_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWAddedDampAFW_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWAddedDampDFW_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWSatDamp_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWDiverseVBIC_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWDefltDamp_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWDampActive_Uls_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) DampFWLimitedVBIC_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) LimitedDamp_MtrNm_D_f32;
STATIC volatile VAR(sint32, DAMPINGFIREWALL_VAR) DriverVel_MtrRadpSec_D_s24p7;
STATIC VAR(sint32, AP_DAMPINGFIREWALL_VAR_NOINIT) DampFWPrev1PreAttnComp_MtrNm_M_s20p11;
STATIC VAR(sint32, AP_DAMPINGFIREWALL_VAR_NOINIT) DampFWPrev2PreAttnComp_MtrNm_M_s20p11;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) PreFiltVBICError_MtrNm_D_f32;
STATIC volatile VAR(float32, DAMPINGFIREWALL_VAR) PostFiltVBICError_MtrNm_D_f32;
#define DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define DAMPINGFIREWALL_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(LPF32KSV_Str, DAMPINGFIREWALL_VAR) DampFWActiveKSV_M_str;
STATIC VAR(LPF32KSV_Str, DAMPINGFIREWALL_VAR) DampFWTbarVelFiltSv_M_str;
STATIC VAR(LPF32KSV_Str, DAMPINGFIREWALL_VAR) DampFWVBICErrFiltSv_M_str;
STATIC VAR(LPF32KSV_Str, DAMPINGFIREWALL_VAR) DampFWLwrBoundKSV_M_str;
STATIC VAR(LPF32KSV_Str, DAMPINGFIREWALL_VAR) DampFWUprBoundKSV_M_str;
#define DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

#define DAMPINGFIREWALL_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AUTOMATIC) DampFWInrtCmpPNStatus_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DampFWPNCountStatus_Cnt_M_lgc;
STATIC VAR(boolean, AUTOMATIC) DampFWVBICReducedPerfSV_Cnt_M_lgc;
STATIC volatile VAR(boolean, AUTOMATIC) DampFWVBICOverThresh_Cnt_D_lgc;
STATIC VAR(boolean, AUTOMATIC) ReducedPerfSV_Cnt_M_lgc;
STATIC volatile VAR(boolean, AUTOMATIC) DampFWOverBound_Cnt_D_lgc;
#define DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */


#define DAMPINGFIREWALL_START_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint16, AP_DAMPINGFIREWALL_VAR_NOINIT) InrtCmpPNAccum_Cnt_M_u16;
STATIC VAR(uint16, AP_DAMPINGFIREWALL_VAR_NOINIT) DampPNAcc_Cnt_M_u16;
STATIC VAR(uint16, AP_DAMPINGFIREWALL_VAR_NOINIT) PrevDecelGain_Uls_M_u5p11;
STATIC VAR(uint16, AP_DAMPINGFIREWALL_VAR_NOINIT) PrevRawDecelGain_Uls_M_u5p11;
STATIC VAR(sint16, AP_DAMPINGFIREWALL_VAR_NOINIT) DampFWPrev1SclDrvVel_MtrRadpS_M_s14p1;
STATIC VAR(sint16, AP_DAMPINGFIREWALL_VAR_NOINIT) DampFWPrev2SclDrvVel_MtrRadpS_M_s14p1;
STATIC volatile VAR(sint16, DAMPINGFIREWALL_VAR) FiltFreq_RadpS_D_s10p5;
STATIC volatile VAR(sint16, DAMPINGFIREWALL_VAR) ScaledDriverVel_MtrRadpS_D_s14p1;
STATIC volatile VAR(uint16, DAMPINGFIREWALL_VAR) OutputAtten_Uls_D_u8p8;
STATIC volatile VAR(uint16, DAMPINGFIREWALL_VAR) RawDecelGain_Uls_D_u5p11;
STATIC volatile VAR(uint16, DAMPINGFIREWALL_VAR) DecelGain_Uls_D_u5p11;
STATIC volatile VAR(uint16, DAMPINGFIREWALL_VAR) ADDCoefCalc_MtrNmSpRad_D_u0p16;
STATIC volatile VAR(uint16, DAMPINGFIREWALL_VAR) InertiaCompCalc_MtrNm_D_u9p7;
STATIC VAR(sint16, AUTOMATIC) DampFWPrevTbarAng_HwDeg_M_s6p9;

#define DAMPINGFIREWALL_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h" /* PRQA S 5087 */

typedef struct {
      sint16 b0_Uls_s0p15;
	  uint16 b1_Uls_u0p16;
	  sint16 b2_Uls_s0p15;
	  uint16 a0_Uls_u2p14;
	  sint16 a1_Uls_s4p11;
	  uint16 a2_Uls_u5p11;
}filterCoef_T;

STATIC FUNC(sint16, AP_DAMPINGFIREWALL_CODE) DriverVelCalc(  VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32,
																VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32,
																VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32 );

STATIC FUNC(uint16, AP_DAMPINGFIREWALL_CODE) ADDCoefCalc( VAR(float32, AUTOMATIC) BaseAssistCmd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
															 VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32,
															 VAR(float32, AUTOMATIC) VehicleLonAccel_KphpS_T_f32);
															 
STATIC FUNC(void, AP_DAMPINGFIREWALL_CODE) FilterCoefCalc( VAR(uint16, AUTOMATIC) ADDCoefCalc_MtrNmSpRad_T_u0p16, 
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, 
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32, 
															 CONSTP2VAR(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str);

STATIC FUNC(sint32, AP_DAMPINGFIREWALL_CODE) GenFddIcCmd( VAR(sint16, AUTOMATIC) ScaledDriverVel_MtrRadpS_T_s14p1, CONSTP2CONST(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str);

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
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * ManufModeType: Enumeration of integer in interval [0...2] with enumerators
 *   ProductionMode (0U)
 *   ManufacturingMode (1U)
 *   EngineeringMode (2U)
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1U)
 *   NTC_Num_FlashECCCorr (2U)
 *   NTC_Num_FlashECCMemFlt (3U)
 *   NTC_Num_FlashCRCMemFault (4U)
 *   NTC_Num_EEPROMDiag (10U)
 *   NTC_Num_EEPROMDiagMtrStr (11U)
 *   NTC_Num_PriSnsrTrqStorFlt (12U)
 *   NTC_Num_EEPROMDiagPosTrimStr (13U)
 *   NTC_Num_SecSnsrTrqStorFlt (14U)
 *   NTC_Num_EEPROMDiagPolarityStr (15U)
 *   NTC_Num_RAMDiag_GeneralFlt (16U)
 *   NTC_Num_RAMDiag_WrprLgcFlt (17U)
 *   NTC_Num_RAMDiag_ECCCorrIndFlt (18U)
 *   NTC_Num_RAMDiag_ECCMemFlt (19U)
 *   NTC_Num_RAMDiag_CRCMemFlt (20U)
 *   NTC_Num_RAMDiag_VIMRamFlt (23U)
 *   NTC_Num_RAMDiag_NHET1RamFlt (24U)
 *   NTC_Num_RAMDiag_NHET2RamFlt (25U)
 *   NTC_Num_RAMDiag_ADC1RamFlt (26U)
 *   NTC_Num_RAMDiag_DCANRamFault (27U)
 *   NTC_Num_RAMDiag_ADC2RamFlt (28U)
 *   NTC_Num_RAMDiag_HETTU1RamFlt (29U)
 *   NTC_Num_RAMDiag_HETTU2RamFlt (30U)
 *   NTC_Num_CPU_RegVer (32U)
 *   NTC_Num_CPU_CoreInitFlt (33U)
 *   NTC_Num_CPU_CoreRunTimeFlt (34U)
 *   NTC_Num_CPU_ClockMon (35U)
 *   NTC_Num_CPU_eFuseFlt (36U)
 *   NTC_Num_CPU_MPUViolation (37U)
 *   NTC_Num_CPU_FactPrcsErr (40U)
 *   NTC_Num_PropExeDiag_InitDiag (41U)
 *   NTC_Num_PrgFlwDeadlnFlt (42U)
 *   NTC_Num_PropExeDiag_RunTimeDiag (43U)
 *   NTC_Num_PropExeDiag_COPTimeout (44U)
 *   NTC_Num_PropExeDiag_PrefetchAbort (48U)
 *   NTC_Num_PropExeDiag_DataAbort (49U)
 *   NTC_Num_PerDiag_ADC1Flt (50U)
 *   NTC_Num_PerDiag_ADC2Flt (51U)
 *   NTC_Num_PerDiag_ADCCrossChkFlt (52U)
 *   NTC_Num_PerDiag_IllegalAccess (53U)
 *   NTC_Num_PerDiag_DMAFlt (54U)
 *   NTC_Num_PerDiag_CPUWarning (63U)
 *   NTC_Num_TmpMonFunc (64U)
 *   NTC_Num_TmpMonRunTimeFlt (65U)
 *   NTC_Num_PowerRelayInitFlt (66U)
 *   NTC_Num_PrechargeFailure (67U)
 *   NTC_Num_PowerRelayRunFlt (68U)
 *   NTC_Num_Thermistor (69U)
 *   NTC_Num_RefSupplyVltg (70U)
 *   NTC_Num_TrcvrInterfaceFlt (71U)
 *   NTC_Num_CPUSupplyOvervoltage (72U)
 *   NTC_Num_GateDrvFlt (77U)
 *   NTC_Num_OnStateSingleFET (78U)
 *   NTC_Num_OnStateMultiFET (79U)
 *   NTC_Num_PhaseVoltageVerf (80U)
 *   NTC_Num_PhaseDscnt (81U)
 *   NTC_Num_DigPhaseVoltageVerf (82U)
 *   NTC_Num_PhaseDscntFailedDisable (83U)
 *   NTC_Num_CurrentMeas1 (84U)
 *   NTC_Num_CurrentMeas2 (85U)
 *   NTC_Num_CurrentMeasCrossChk (86U)
 *   NTC_Num_PDSupplyOverVoltage (87U)
 *   NTC_Num_ChargePumpUnderVoltage (88U)
 *   NTC_Num_HwTrqSensor (96U)
 *   NTC_Num_AnaVsDigHwTrq (97U)
 *   NTC_Num_TrqSensorRecoveryFlt (98U)
 *   NTC_Num_TrqSensorScaleInvalid (100U)
 *   NTC_Num_T1vsT2 (101U)
 *   NTC_Num_T1OutofRange (102U)
 *   NTC_Num_T2OutofRange (103U)
 *   NTC_Num_DigT1vsT2 (104U)
 *   NTC_Num_DigT1OutofRange (105U)
 *   NTC_Num_DigT2OutofRange (106U)
 *   NTC_Num_RedT1vsT2 (107U)
 *   NTC_Num_HWASensorRel (110U)
 *   NTC_Num_HWASensorAbs (111U)
 *   NTC_Num_PriMSB_SinCosCorr (112U)
 *   NTC_Num_SecMSB_SinCosCorr (113U)
 *   NTC_Num_PriVsSec_SinCosCorr (114U)
 *   NTC_Num_DigMSBFlt (115U)
 *   NTC_Num_MtrVelFlt (116U)
 *   NTC_Num_HWAtoMtrAngleCorr (117U)
 *   NTC_Num_RedPriVsSec_SinCosCorr (118U)
 *   NTC_Num_TurnCntr_PosLoss (128U)
 *   NTC_Num_TurnCntr_MicroProcFlt (129U)
 *   NTC_Num_TurnCntr_SensorPosFlt (130U)
 *   NTC_Num_TurnCntr_SpiComFlt (131U)
 *   NTC_Num_TurnCntr_HighQuiescCur (132U)
 *   NTC_Num_TurnCntr_MainResets (133U)
 *   NTC_Num_KinematicIntDiag (144U)
 *   NTC_Num_HighFriction (145U)
 *   NTC_Num_DutyCycleExceeded (148U)
 *   NTC_Num_AbsTempThermLimit (149U)
 *   NTC_Num_LatchActive (160U)
 *   NTC_Num_OpTrqVsHwTrq (168U)
 *   NTC_Num_CurrentReas (169U)
 *   NTC_Num_OpVoltage (176U)
 *   NTC_Num_ExVoltageLow (177U)
 *   NTC_Num_ReducedAsstLowVoltage (178U)
 *   NTC_Num_ExVoltageHigh (180U)
 *   NTC_Num_OpVoltageOvrMax (181U)
 *   NTC_Num_IgnConfDiag (184U)
 *   NTC_Num_TurnCntr_LowBattery (185U)
 *   NTC_Num_EEPROMCloseFailed (191U)
 *   NTC_Num_SigPath1CrossChk (192U)
 *   NTC_Num_SigPath2CrossChk (193U)
 *   NTC_Num_SigPath3CrossChk (194U)
 *   NTC_Num_SigPath4CrossChk (195U)
 *   NTC_Num_SigPath5CrossChk (196U)
 *   NTC_Num_DampingFWReached (197U)
 *   NTC_Num_AssistFWReached (198U)
 *   NTC_Num_ReturnFWReached (199U)
 *   NTC_Num_DampingFWFltMode (200U)
 *   NTC_Num_AssistFWFltMode (201U)
 *   NTC_Num_VBICFltMode (202U)
 *   NTC_Num_StaMdsSysC (203U)
 *   NTC_NUM_SysFailureForRotVel (204U)
 *   NTC_NUM_SysFailForRedntRotVel (205U)
 *   NTC_Num_SysFailureForTrqSnsr (206U)
 *   NTC_Num_SysFailureForRedTrqSnsr (207U)
 *   NTC_NUM_SysFailureForCtrlVolt (209U)
 *   NTC_Num_GlblSgnlOvrwrtDet (223U)
 *   NTC_Num_VLF_00 (224U)
 *   NTC_Num_VLF_01 (225U)
 *   NTC_Num_VLF_02 (226U)
 *   NTC_Num_VLF_03 (227U)
 *   NTC_Num_VLF_04 (228U)
 *   NTC_Num_VLF_05 (229U)
 *   NTC_Num_VLF_06 (230U)
 *   NTC_Num_VLF_07 (231U)
 *   NTC_Num_VLF_08 (232U)
 *   NTC_Num_VLF_09 (233U)
 *   NTC_Num_VLF_10 (234U)
 *   NTC_Num_VLF_11 (235U)
 *   NTC_Num_VLF_12 (236U)
 *   NTC_Num_VLF_13 (237U)
 *   NTC_Num_VLF_14 (238U)
 *   NTC_Num_VLF_15 (239U)
 *   NTC_Num_VLF_16 (240U)
 *   NTC_Num_VLF_17 (241U)
 *   NTC_Num_VLF_18 (242U)
 *   NTC_Num_VLF_19 (243U)
 *   NTC_Num_VLF_20 (244U)
 *   NTC_Num_VLF_21 (245U)
 *   NTC_Num_VLF_22 (246U)
 *   NTC_Num_VLF_23 (247U)
 *   NTC_Num_VLF_24 (248U)
 *   NTC_Num_VLF_25 (249U)
 *   NTC_Num_VLF_26 (250U)
 *   NTC_Num_VLF_27 (251U)
 *   NTC_Num_VLF_28 (252U)
 *   NTC_Num_VLF_29 (253U)
 *   NTC_Num_VLF_30 (254U)
 *   NTC_Num_VLF_31 (255U)
 *   NTC_Num_BusOffCh1 (256U)
 *   NTC_Num_BusOffCh1NodeMute (257U)
 *   NTC_Num_Node1AAbsent (258U)
 *   NTC_Num_Node1AFaulty (259U)
 *   NTC_Num_Node1BAbsent (260U)
 *   NTC_Num_Node1BFaulty (261U)
 *   NTC_Num_Node1CAbsent (262U)
 *   NTC_Num_Node1CFaulty (263U)
 *   NTC_Num_Node1DAbsent (264U)
 *   NTC_Num_Node1DFaulty (265U)
 *   NTC_Num_Node1EAbsent (266U)
 *   NTC_Num_Node1EFaulty (267U)
 *   NTC_Num_Node1FAbsent (268U)
 *   NTC_Num_Node1FFaulty (269U)
 *   NTC_Num_Node1GAbsent (270U)
 *   NTC_Num_Node1GFaulty (271U)
 *   NTC_Num_BusOffCh2 (272U)
 *   NTC_Num_Node2AAbsent (273U)
 *   NTC_Num_Node2AFaulty (274U)
 *   NTC_Num_Node2BAbsent (275U)
 *   NTC_Num_Node2BFaulty (276U)
 *   NTC_Num_Node2CAbsent (277U)
 *   NTC_Num_Node2CFaulty (278U)
 *   NTC_Num_Node2DAbsent (279U)
 *   NTC_Num_Node2DFaulty (280U)
 *   NTC_Num_Node2EAbsent (281U)
 *   NTC_Num_Node2EFaulty (282U)
 *   NTC_Num_Node2FAbsent (283U)
 *   NTC_Num_Node2FFaulty (284U)
 *   NTC_Num_Node2GAbsent (285U)
 *   NTC_Num_Node2GFaulty (286U)
 *   NTC_Num_InvalidMsg_M (288U)
 *   NTC_Num_MissingMsg_M (289U)
 *   NTC_Num_CRCFltMsg_M (290U)
 *   NTC_Num_PgrsCntFltMsg_M (291U)
 *   NTC_Num_DataRngFltMsg_M (292U)
 *   NTC_Num_DataRateFltMsg_M (293U)
 *   NTC_Num_DataOtherFltMsg_M (294U)
 *   NTC_Num_InvalidMsg_N (296U)
 *   NTC_Num_MissingMsg_N (297U)
 *   NTC_Num_CRCFltMsg_N (298U)
 *   NTC_Num_PgrsCntFltMsg_N (299U)
 *   NTC_Num_DataRngFltMsg_N (300U)
 *   NTC_Num_DataRateFltMsg_N (301U)
 *   NTC_Num_DataOtherFltMsg_N (302U)
 *   NTC_Num_DataOtherFlt2Msg_N (303U)
 *   NTC_Num_InvalidMsg_O (304U)
 *   NTC_Num_MissingMsg_O (305U)
 *   NTC_Num_CRCFltMsg_O (306U)
 *   NTC_Num_PgrsCntFltMsg_O (307U)
 *   NTC_Num_DataRngFltMsg_O (308U)
 *   NTC_Num_DataRateFltMsg_O (309U)
 *   NTC_Num_DataOtherFltMsg_O (310U)
 *   NTC_Num_InvalidMsg_P (312U)
 *   NTC_Num_MissingMsg_P (313U)
 *   NTC_Num_CRCFltMsg_P (314U)
 *   NTC_Num_PgrsCntFltMsg_P (315U)
 *   NTC_Num_DataRngFltMsg_P (316U)
 *   NTC_Num_DataRateFltMsg_P (317U)
 *   NTC_Num_DataOtherFltMsg_P (318U)
 *   NTC_Num_InvalidMsg_Q (320U)
 *   NTC_Num_MissingMsg_Q (321U)
 *   NTC_Num_CRCFltMsg_Q (322U)
 *   NTC_Num_PgrsCntFltMsg_Q (323U)
 *   NTC_Num_DataRngFltMsg_Q (324U)
 *   NTC_Num_DataRateFltMsg_Q (325U)
 *   NTC_Num_DataOtherFltMsg_Q (326U)
 *   NTC_Num_InvalidMsg_R (328U)
 *   NTC_Num_MissingMsg_R (329U)
 *   NTC_Num_CRCFltMsg_R (330U)
 *   NTC_Num_PgrsCntFltMsg_R (331U)
 *   NTC_Num_DataRngFltMsg_R (332U)
 *   NTC_Num_DataRateFltMsg_R (333U)
 *   NTC_Num_DataOtherFltMsg_R (334U)
 *   NTC_Num_InvalidMsg_S (336U)
 *   NTC_Num_MissingMsg_S (337U)
 *   NTC_Num_CRCFltMsg_S (338U)
 *   NTC_Num_PgrsCntFltMsg_S (339U)
 *   NTC_Num_DataRngFltMsg_S (340U)
 *   NTC_Num_DataRateFltMsg_S (341U)
 *   NTC_Num_DataOtherFltMsg_S (342U)
 *   NTC_Num_InvalidMsg_T (344U)
 *   NTC_Num_MissingMsg_T (345U)
 *   NTC_Num_CRCFltMsg_T (346U)
 *   NTC_Num_PgrsCntFltMsg_T (347U)
 *   NTC_Num_DataRngFltMsg_T (348U)
 *   NTC_Num_DataRateFltMsg_T (349U)
 *   NTC_Num_DataOtherFltMsg_T (350U)
 *   NTC_Num_InvalidMsg_U (352U)
 *   NTC_Num_MissingMsg_U (353U)
 *   NTC_Num_CRCFltMsg_U (354U)
 *   NTC_Num_PgrsCntFltMsg_U (355U)
 *   NTC_Num_DataRngFltMsg_U (356U)
 *   NTC_Num_DataRateFltMsg_U (357U)
 *   NTC_Num_DataOtherFltMsg_U (358U)
 *   NTC_Num_InvalidMsg_V (360U)
 *   NTC_Num_MissingMsg_V (361U)
 *   NTC_Num_CRCFltMsg_V (362U)
 *   NTC_Num_PgrsCntFltMsg_V (363U)
 *   NTC_Num_DataRngFltMsg_V (364U)
 *   NTC_Num_DataRateFltMsg_V (365U)
 *   NTC_Num_DataOtherFltMsg_V (366U)
 *   NTC_Num_InvalidMsg_W (368U)
 *   NTC_Num_MissingMsg_W (369U)
 *   NTC_Num_CRCFltMsg_W (370U)
 *   NTC_Num_PgrsCntFltMsg_W (371U)
 *   NTC_Num_DataRngFltMsg_W (372U)
 *   NTC_Num_DataRateFltMsg_W (373U)
 *   NTC_Num_DataOtherFltMsg_W (374U)
 *   NTC_Num_InvalidMsg_X (376U)
 *   NTC_Num_MissingMsg_X (377U)
 *   NTC_Num_CRCFltMsg_X (378U)
 *   NTC_Num_PgrsCntFltMsg_X (379U)
 *   NTC_Num_DataRngFltMsg_X (380U)
 *   NTC_Num_DataRateFltMsg_X (381U)
 *   NTC_Num_DataOtherFltMsg_X (382U)
 *   NTC_Num_InvalidMsg_Y (384U)
 *   NTC_Num_MissingMsg_Y (385U)
 *   NTC_Num_CRCFltMsg_Y (386U)
 *   NTC_Num_PgrsCntFltMsg_Y (387U)
 *   NTC_Num_DataRngFltMsg_Y (388U)
 *   NTC_Num_DataRateFltMsg_Y (389U)
 *   NTC_Num_DataOtherFltMsg_Y (390U)
 *   NTC_Num_InvalidMsg_Z (392U)
 *   NTC_Num_MissingMsg_Z (393U)
 *   NTC_Num_CRCFltMsg_Z (394U)
 *   NTC_Num_PgrsCntFltMsg_Z (395U)
 *   NTC_Num_DataRngFltMsg_Z (396U)
 *   NTC_Num_DataRateFltMsg_Z (397U)
 *   NTC_Num_DataOtherFltMsg_Z (398U)
 *   NTC_Num_DSTXORActive (399U)
 *   NTC_Num_InvalidMsg_AA (400U)
 *   NTC_Num_MissingMsg_AA (401U)
 *   NTC_Num_CRCFltMsg_AA (402U)
 *   NTC_Num_PgrsCntFltMsg_AA (403U)
 *   NTC_Num_DataRngFltMsg_AA (404U)
 *   NTC_Num_DataRateFltMsg_AA (405U)
 *   NTC_Num_DataOtherFltMsg_AA (406U)
 *   NTC_Num_InvalidMsg_AB (408U)
 *   NTC_Num_MissingMsg_AB (409U)
 *   NTC_Num_CRCFltMsg_AB (410U)
 *   NTC_Num_PgrsCntFltMsg_AB (411U)
 *   NTC_Num_DataRngFltMsg_AB (412U)
 *   NTC_Num_DataRateFltMsg_AB (413U)
 *   NTC_Num_DataOtherFltMsg_AB (414U)
 *   NTC_Num_InvalidMsg_AC (416U)
 *   NTC_Num_MissingMsg_AC (417U)
 *   NTC_Num_CRCFltMsg_AC (418U)
 *   NTC_Num_PgrsCntFltMsg_AC (419U)
 *   NTC_Num_DataRngFltMsg_AC (420U)
 *   NTC_Num_DataRateFltMsg_AC (421U)
 *   NTC_Num_DataOtherFltMsg_AC (422U)
 *   NTC_Num_InvalidMsg_AD (424U)
 *   NTC_Num_MissingMsg_AD (425U)
 *   NTC_Num_CRCFltMsg_AD (426U)
 *   NTC_Num_PgrsCntFltMsg_AD (427U)
 *   NTC_Num_DataRngFltMsg_AD (428U)
 *   NTC_Num_DataRateFltMsg_AD (429U)
 *   NTC_Num_DataOtherFltMsg_AD (430U)
 *   NTC_Num_InvalidMsg_AE (432U)
 *   NTC_Num_MissingMsg_AE (433U)
 *   NTC_Num_CRCFltMsg_AE (434U)
 *   NTC_Num_PgrsCntFltMsg_AE (435U)
 *   NTC_Num_DataRngFltMsg_AE (436U)
 *   NTC_Num_DataRateFltMsg_AE (437U)
 *   NTC_Num_DataOtherFltMsg_AE (438U)
 *   NTC_Num_InvalidMsg_AF (440U)
 *   NTC_Num_MissingMsg_AF (441U)
 *   NTC_Num_CRCFltMsg_AF (442U)
 *   NTC_Num_PgrsCntFltMsg_AF (443U)
 *   NTC_Num_DataRngFltMsg_AF (444U)
 *   NTC_Num_DataRateFltMsg_AF (445U)
 *   NTC_Num_DataOtherFltMsg_AF (446U)
 *   NTC_Num_InvalidMsg_AG (448U)
 *   NTC_Num_MissingMsg_AG (449U)
 *   NTC_Num_CRCFltMsg_AG (450U)
 *   NTC_Num_PgrsCntFltMsg_AG (451U)
 *   NTC_Num_DataRngFltMsg_AG (452U)
 *   NTC_Num_DataRateFltMsg_AG (453U)
 *   NTC_Num_DataOtherFltMsg_AG (454U)
 *   NTC_Num_InvalidMsg_AH (456U)
 *   NTC_Num_MissingMsg_AH (457U)
 *   NTC_Num_CRCFltMsg_AH (458U)
 *   NTC_Num_PgrsCntFltMsg_AH (459U)
 *   NTC_Num_DataRngFltMsg_AH (460U)
 *   NTC_Num_DataRateFltMsg_AH (461U)
 *   NTC_Num_DataOtherFltMsg_AH (462U)
 *   NTC_Num_FlexrayCommunicationError (465U)
 *   NTC_Num_SysConsistencyVerf (496U)
 *   NTC_Num_ConfigMisMatch (497U)
 *   NTC_Num_CalNotPrgmd (498U)
 *   NTC_Num_EOLVehTunNtPerf (501U)
 *   NTC_Num_MtrSensorNotTrimmed (502U)
 *   NTC_Num_HWASensorNotTrimmed (504U)
 *   NTC_Num_HWASensorTrimNoAttempt (505U)
 *   NTC_Num_TrqSensorScaleNotSet (506U)
 *   NTC_Num_TrqSensorNotTrimmed (507U)
 *   NTC_Num_DigTrqSensorScaleNotSet (509U)
 *   NTC_Num_DigTrqSensorNotTrimmed (510U)
 * NxtrDiagMgrStatus: Enumeration of integer in interval [0...255] with enumerators
 *   NTC_STATUS_PASSED (0U)
 *   NTC_STATUS_FAILED (1U)
 *   NTC_STATUS_PREPASSED (2U)
 *   NTC_STATUS_PREFAILED (3U)
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
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_2PI_ULS_F32 = 6.2831853071796F
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8F
 * Float: D_ONE_ULS_F32 = 1.0F
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199F
 * Float: D_ZERO_ULS_F32 = 0.0F
 * SInt16: D_NEGONE_CNT_S16 = -1
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_DAMPINGFIREWALL_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DampingFirewall_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DAMPINGFIREWALL_APPL_CODE) DampingFirewall_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DampingFirewall_Init1
 *********************************************************************************************************************/
	
	PrevDecelGain_Uls_M_u5p11 = D_ONE_ULS_U5P11;
	LPF_KUpdate_f32_m(k_DampFWFWActiveLPF_Hz_f32, D_2MS_SEC_F32, &DampFWActiveKSV_M_str);
	LPF_KUpdate_f32_m(k_InrtCmp_TBarVelLPFKn_Hz_f32, D_2MS_SEC_F32, &DampFWTbarVelFiltSv_M_str);
	LPF_KUpdate_f32_m(k_DampFWVBICLPF_Hz_f32, D_2MS_SEC_F32, &DampFWVBICErrFiltSv_M_str);
	LPF_KUpdate_f32_m(k_DmpBoundLPFKn_Hz_f32, D_2MS_SEC_F32, &DampFWUprBoundKSV_M_str);
	LPF_KUpdate_f32_m(k_DmpBoundLPFKn_Hz_f32, D_2MS_SEC_F32, &DampFWLwrBoundKSV_M_str);
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

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

FUNC(void, RTE_AP_DAMPINGFIREWALL_APPL_CODE) DampingFirewall_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DampingFirewall_Per1
 *********************************************************************************************************************/
	
	
	VAR(float32, AUTOMATIC) AsstFirewallActive_Uls_T_f32;
	VAR(float32, AUTOMATIC) DampingCmd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32;
	VAR(float32, AUTOMATIC) InertiaComp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) MtrVelCRF_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32;
	
	VAR(uint16,  AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
	VAR(sint16,  AUTOMATIC) MtrVelCRF_MtrRadpS_T_s11p4;
	VAR(uint16,  AUTOMATIC) AbsMtrVelCRF_MtrRadpS_T_u11p5;
	
	VAR(sint16,  AUTOMATIC) UprBoundRaw_MtrNm_T_s7p8;
	VAR(float32, AUTOMATIC) UprBoundRaw_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) UprBoundFilt_MtrNm_T_f32;
	VAR(sint16,  AUTOMATIC) LwrBoundRaw_MtrNm_T_s7p8;
	VAR(float32, AUTOMATIC) LwrBoundRaw_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) LwrBoundFilt_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampLimited_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampFWActive_Uls_T_f32;
	
	VAR(uint16,  AUTOMATIC) AddDampingLookup_MtrNm_T_u5p11;
	VAR(float32, AUTOMATIC) AFWAddDamping_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DFWAddDamping_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) AddedDamp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) BaseAsstCmd_MtrNm_T_f32;
	
	VAR(float32, AUTOMATIC) CombinedDamping_MtrNm_T_f32;
	VAR(DiagSettings_Str, AUTOMATIC) DampFWPstepNstep_Cnt_T_str;
	VAR(DiagSettings_Str, AUTOMATIC) DampFWInrtCmpPstepNstep_Cnt_T_str;
	VAR(uint16, AUTOMATIC) ADDCoefCalc_MtrNmSpRad_T_u0p16;
	VAR(float32, AUTOMATIC)	DampFWSatDamp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC)	DefltDampLookup_MtrNm_T_f32;
	VAR(uint16, AUTOMATIC) DefltDampLookup_MtrNm_T_u5p11;
	VAR(boolean, AUTOMATIC) FDDDefSrvFlg_Cnt_T_lgc;
	VAR(filterCoef_T, AUTOMATIC) FilterCoef_T_Str;
	VAR(float32, AUTOMATIC) FrqDepDmpnInrtCmp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) LimitedDamp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) LimitedVBIC_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampFWOverBound_Uls_T_f32;
	VAR(float32, AUTOMATIC) VehicleLonAccel_KphpS_T_f32;
	VAR(sint16, AUTOMATIC) ScaledDriverVel_MtrRadpS_T_s14p1;
	VAR(float32, AUTOMATIC) VBICError_MtrNm_T_f32;	
	VAR(boolean, AUTOMATIC) DefeatDampingSvc_Cnt_T_lgc;
	VAR(ManufModeType, AUTOMATIC) MECCounter_Cnt_T_enum;
	
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_DampingFirewall_Per1_CP0_CheckpointReached();

	DampFWPstepNstep_Cnt_T_str.PStep = k_DampFWPstep_Cnt_u16;
	DampFWPstepNstep_Cnt_T_str.NStep = k_DampFWNstep_Cnt_u16;
	DampFWPstepNstep_Cnt_T_str.Threshold = t_DampFWPNstepThresh_Cnt_u16[1]; 

	DampFWInrtCmpPstepNstep_Cnt_T_str.PStep = k_DampFWInCmpPStep_Cnt_u16;
	DampFWInrtCmpPstepNstep_Cnt_T_str.NStep = k_DampFWInCmpNStep_Cnt_u16;
	DampFWInrtCmpPstepNstep_Cnt_T_str.Threshold  = t_DampFWDampInrtCmpPNThesh_Cnt_u16[1];

	DefeatDampingSvc_Cnt_T_lgc = Rte_IRead_DampingFirewall_Per1_Defeat_Damping_Svc_Cnt_lgc();
	MECCounter_Cnt_T_enum = Rte_IRead_DampingFirewall_Per1_MEC_Counter_Cnt_enum();
	
	AsstFirewallActive_Uls_T_f32 = Rte_IRead_DampingFirewall_Per1_AsstFirewallActive_Uls_f32();
	DampingCmd_MtrNm_T_f32 = Rte_IRead_DampingFirewall_Per1_DampingCmd_MtrNm_f32();
	HwTorque_HwNm_T_f32 = Rte_IRead_DampingFirewall_Per1_HwTorque_HwNm_f32();
	InertiaComp_MtrNm_T_f32 = Rte_IRead_DampingFirewall_Per1_InertiaComp_MtrNm_f32();
	MtrVelCRF_MtrRadpS_T_f32 = Rte_IRead_DampingFirewall_Per1_MtrVelCRF_MtrRadpS_f32();
	VehicleSpeed_Kph_T_f32 = Rte_IRead_DampingFirewall_Per1_VehicleSpeed_Kph_f32();
	BaseAsstCmd_MtrNm_T_f32 = Rte_IRead_DampingFirewall_Per1_BaseAssistCmd_MtrNm_f32();
	WIRCmdAmpBlnd_MtrNm_T_f32 = Rte_IRead_DampingFirewall_Per1_WIRCmdAmpBlnd_MtrNm_f32();
	FDDDefSrvFlg_Cnt_T_lgc = Rte_IRead_DampingFirewall_Per1_FreqDepDmpSrlComSvcDft_Cnt_lgc();
	VehicleLonAccel_KphpS_T_f32 = Rte_IRead_DampingFirewall_Per1_VehicleLonAccel_KphpS_f32();
	
	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
	MtrVelCRF_MtrRadpS_T_s11p4 = FPM_FloatToFixed_m(MtrVelCRF_MtrRadpS_T_f32, s11p4_T);
	
	AbsMtrVelCRF_MtrRadpS_T_u11p5 = FPM_FloatToFixed_m(Abs_f32_m(MtrVelCRF_MtrRadpS_T_f32), u11p5_T);
	
	/* Instead of using MEC Counter the enum is being used. enum equals ProductionMode when MEC Counter is 0. */
	if((DefeatDampingSvc_Cnt_T_lgc != D_FALSE_CNT_LGC) && (MECCounter_Cnt_T_enum != ProductionMode)) 
	{
		LimitedDamp_MtrNm_T_f32 = DampingCmd_MtrNm_T_f32;
		AddedDamp_MtrNm_T_f32 = 0.0F;
		(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DampingFWReached, 0x01U, NTC_STATUS_PASSED);
		(void) Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DampingFWFltMode, 0x01U, NTC_STATUS_PASSED);
	}
	else
	{
		/*** Damping Limiter - Determines Boundaries*/
		UprBoundRaw_MtrNm_T_s7p8 = BilinearXYM_s16_s16Xs16YM_Cnt(VehicleSpeed_Kph_T_u9p7,
																	MtrVelCRF_MtrRadpS_T_s11p4,
																	t_DampFWVehSpd_Kph_u9p7,
																	TableSize_m(t_DampFWVehSpd_Kph_u9p7),
																	t_DampFWUprBoundX_MtrRadpS_s11p4,
																	t2_DampFWUprBoundY_MtrNm_s7p8[0],
																	TableSize_m(t_DampFWUprBoundX_MtrRadpS_s11p4));
		
		UprBoundRaw_MtrNm_T_f32 = FPM_FixedToFloat_m(UprBoundRaw_MtrNm_T_s7p8, s7p8_T);
		
		UprBoundFilt_MtrNm_T_f32 = LPF_OpUpdate_f32_m(UprBoundRaw_MtrNm_T_f32, &DampFWUprBoundKSV_M_str);
		
		LwrBoundRaw_MtrNm_T_s7p8 = BilinearXYM_s16_s16Xs16YM_Cnt(VehicleSpeed_Kph_T_u9p7,
																	(D_NEGONE_CNT_S16 * MtrVelCRF_MtrRadpS_T_s11p4),
																	t_DampFWVehSpd_Kph_u9p7,
																	TableSize_m(t_DampFWVehSpd_Kph_u9p7),
																	t_DampFWUprBoundX_MtrRadpS_s11p4,
																	t2_DampFWUprBoundY_MtrNm_s7p8[0],
																	TableSize_m(t_DampFWUprBoundX_MtrRadpS_s11p4));
		
		LwrBoundRaw_MtrNm_T_f32 = FPM_FixedToFloat_m((D_NEGONE_CNT_S16 * LwrBoundRaw_MtrNm_T_s7p8), s7p8_T);
		
		LwrBoundFilt_MtrNm_T_f32 = LPF_OpUpdate_f32_m(LwrBoundRaw_MtrNm_T_f32, &DampFWLwrBoundKSV_M_str);
		
		DampLimited_MtrNm_T_f32 = Limit_m(DampingCmd_MtrNm_T_f32, -k_DampFWInpLimitDamp_MtrNm_f32, k_DampFWInpLimitDamp_MtrNm_f32);

		DampFWSatDamp_MtrNm_T_f32 = Limit_m(DampLimited_MtrNm_T_f32, LwrBoundFilt_MtrNm_T_f32, UprBoundFilt_MtrNm_T_f32);

		DampFWSatDamp_MtrNm_D_f32 = DampFWSatDamp_MtrNm_T_f32;
		DefltDampLookup_MtrNm_T_u5p11 = IntplVarXY_u16_u16Xu16Y_Cnt( t_DampFWDefltDampX_MtrRadpS_u11p5,
																	  t_DampFWDefltDampY_MtrNm_u5p11,
																	  TableSize_m(t_DampFWDefltDampX_MtrRadpS_u11p5),
																	  AbsMtrVelCRF_MtrRadpS_T_u11p5);

		DefltDampLookup_MtrNm_T_f32 =  FPM_FixedToFloat_m(DefltDampLookup_MtrNm_T_u5p11, u5p11_T);
		DefltDampLookup_MtrNm_T_f32 = DefltDampLookup_MtrNm_T_f32 * ((float32)Sign_f32_m(MtrVelCRF_MtrRadpS_T_f32));
		DampFWDefltDamp_MtrNm_D_f32 = DefltDampLookup_MtrNm_T_f32;


		if((DampLimited_MtrNm_T_f32 > UprBoundFilt_MtrNm_T_f32 ) || (DampLimited_MtrNm_T_f32 < LwrBoundFilt_MtrNm_T_f32))
		{
			DampFWOverBound_Cnt_D_lgc = TRUE;
			DampFWOverBound_Uls_T_f32 = D_ONE_ULS_F32;
			DampPNAcc_Cnt_M_u16 = DiagPStep_m(DampPNAcc_Cnt_M_u16, DampFWPstepNstep_Cnt_T_str);
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DampingFWReached, 0x01U, NTC_STATUS_FAILED);

		}
		else
		{
			DampFWOverBound_Cnt_D_lgc = FALSE;
			DampFWOverBound_Uls_T_f32 = D_ZERO_ULS_F32;
			DampPNAcc_Cnt_M_u16 = DiagNStep_m(DampPNAcc_Cnt_M_u16, DampFWPstepNstep_Cnt_T_str);
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DampingFWReached, 0x01U, NTC_STATUS_PASSED);
		}

		if( DampPNAcc_Cnt_M_u16 >= t_DampFWPNstepThresh_Cnt_u16[1] )
		{
			DampFWPNCountStatus_Cnt_M_lgc = TRUE; 
		}
		else if( DampPNAcc_Cnt_M_u16 > t_DampFWPNstepThresh_Cnt_u16[0] )
		{
			/* do nothing */
		}
		else
		{
			DampFWPNCountStatus_Cnt_M_lgc = FALSE;
		}

		
		if((TRUE == DampFWPNCountStatus_Cnt_M_lgc) || (TRUE == ReducedPerfSV_Cnt_M_lgc))
		{
			ReducedPerfSV_Cnt_M_lgc = TRUE;
			LimitedDamp_MtrNm_T_f32 = DefltDampLookup_MtrNm_T_f32;
			DampFWActive_Uls_T_f32 =D_ZERO_ULS_F32;
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DampingFWFltMode, 0x01U, NTC_STATUS_FAILED);


		}
		else
		{
			ReducedPerfSV_Cnt_M_lgc = FALSE;
			LimitedDamp_MtrNm_T_f32 = DampFWSatDamp_MtrNm_T_f32;
			DampFWActive_Uls_T_f32 = LPF_OpUpdate_f32_m(DampFWOverBound_Uls_T_f32, &DampFWActiveKSV_M_str);
			(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_DampingFWFltMode, 0x01U, NTC_STATUS_PASSED);
		}
	/**** End of Damping Limiter sub function ***/

		DampFWDampActive_Uls_D_f32 = DampFWActive_Uls_T_f32;
		LimitedDamp_MtrNm_D_f32 = LimitedDamp_MtrNm_T_f32;

	/*** BLOCK START - Additional Damping ***/
		AddDampingLookup_MtrNm_T_u5p11 = IntplVarXY_u16_u16Xu16Y_Cnt( t_DampFWAddDampAFWX_MtrRadpS_u11p5,
																	  t_DampFWAddDampAFWY_MtrNm_u5p11,
																	  TableSize_m(t_DampFWAddDampAFWX_MtrRadpS_u11p5),
																	  AbsMtrVelCRF_MtrRadpS_T_u11p5);
		
		AFWAddDamping_MtrNm_T_f32 = (FPM_FixedToFloat_m(AddDampingLookup_MtrNm_T_u5p11, u5p11_T)) * AsstFirewallActive_Uls_T_f32;
		
		AddDampingLookup_MtrNm_T_u5p11 = IntplVarXY_u16_u16Xu16Y_Cnt( t_DampFWAddDampDFWX_MtrRadpS_u11p5,
																	  t_DampFWAddDampDFWY_MtrNm_u5p11,
																	  TableSize_m(t_DampFWAddDampAFWX_MtrRadpS_u11p5),
																	  AbsMtrVelCRF_MtrRadpS_T_u11p5);
																	  
		DFWAddDamping_MtrNm_T_f32 = (FPM_FixedToFloat_m(AddDampingLookup_MtrNm_T_u5p11, u5p11_T)) * DampFWActive_Uls_T_f32;
		
		AddedDamp_MtrNm_T_f32 = Max_m(AFWAddDamping_MtrNm_T_f32, DFWAddDamping_MtrNm_T_f32) * ((float32)Sign_f32_m(MtrVelCRF_MtrRadpS_T_f32));
		
		/*** BLOCK END - Additional Damping ***/
	
	}	

	/*** BLOCK START - VBIC limiter ***/

	/* Calc ADD Coefficient */
	ADDCoefCalc_MtrNmSpRad_T_u0p16 = ADDCoefCalc(BaseAsstCmd_MtrNm_T_f32, WIRCmdAmpBlnd_MtrNm_T_f32, VehicleSpeed_Kph_T_f32, MtrVelCRF_MtrRadpS_T_f32, VehicleLonAccel_KphpS_T_f32);
	
	/* Calc Scaled Driver Velocity */
	ScaledDriverVel_MtrRadpS_T_s14p1 = DriverVelCalc(HwTorque_HwNm_T_f32, MtrVelCRF_MtrRadpS_T_f32, VehicleSpeed_Kph_T_f32);

	/* Calc Filter Coef */
	FilterCoefCalc(ADDCoefCalc_MtrNmSpRad_T_u0p16, VehicleSpeed_Kph_T_f32, WIRCmdAmpBlnd_MtrNm_T_f32, &FilterCoef_T_Str);
	
	/* Generate Command */
	FrqDepDmpnInrtCmp_MtrNm_T_f32 = FPM_FixedToFloat_m(GenFddIcCmd(ScaledDriverVel_MtrRadpS_T_s14p1, &FilterCoef_T_Str), s11p20_T);

	if (FDDDefSrvFlg_Cnt_T_lgc == TRUE)
	{
		FrqDepDmpnInrtCmp_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}

	/* Update display variable */
	DampFWDiverseVBIC_MtrNm_D_f32 = FrqDepDmpnInrtCmp_MtrNm_T_f32;
	
/*** BLOCK END - VBIC limiter ***/

	VBICError_MtrNm_T_f32 = InertiaComp_MtrNm_T_f32 - FrqDepDmpnInrtCmp_MtrNm_T_f32;
	PreFiltVBICError_MtrNm_D_f32 = VBICError_MtrNm_T_f32;
	VBICError_MtrNm_T_f32 = LPF_OpUpdate_f32_m(VBICError_MtrNm_T_f32, &DampFWVBICErrFiltSv_M_str);
	PostFiltVBICError_MtrNm_D_f32 = VBICError_MtrNm_T_f32;
	
	if( Abs_f32_m(VBICError_MtrNm_T_f32) > k_DampFWErrThresh_MtrNm_f32)
	{
		InrtCmpPNAccum_Cnt_M_u16 =  DiagPStep_m(InrtCmpPNAccum_Cnt_M_u16, DampFWInrtCmpPstepNstep_Cnt_T_str);
		DampFWVBICOverThresh_Cnt_D_lgc = TRUE;
	}
	else
	{
		InrtCmpPNAccum_Cnt_M_u16 =  DiagNStep_m(InrtCmpPNAccum_Cnt_M_u16, DampFWInrtCmpPstepNstep_Cnt_T_str);
		DampFWVBICOverThresh_Cnt_D_lgc = FALSE;
	}

	if(InrtCmpPNAccum_Cnt_M_u16 >= t_DampFWDampInrtCmpPNThesh_Cnt_u16[1])
	{
		DampFWInrtCmpPNStatus_Cnt_M_lgc = TRUE;
	}
	else if(InrtCmpPNAccum_Cnt_M_u16 > t_DampFWDampInrtCmpPNThesh_Cnt_u16[0])
	{
		/* Do Nothing */
	}
	else
	{
		DampFWInrtCmpPNStatus_Cnt_M_lgc = FALSE;
	}


	if((TRUE == DampFWInrtCmpPNStatus_Cnt_M_lgc) || (TRUE == DampFWVBICReducedPerfSV_Cnt_M_lgc))
	{
		DampFWVBICReducedPerfSV_Cnt_M_lgc = TRUE;
		LimitedVBIC_MtrNm_T_f32 = D_ZERO_ULS_F32;
	}
	else
	{
		DampFWVBICReducedPerfSV_Cnt_M_lgc = FALSE;
		LimitedVBIC_MtrNm_T_f32 = InertiaComp_MtrNm_T_f32;
	}
	
	if(TRUE == DampFWVBICReducedPerfSV_Cnt_M_lgc)
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_VBICFltMode, 0x01U, NTC_STATUS_FAILED);
	}
	else
	{
		(void)Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_VBICFltMode, 0x0U, NTC_STATUS_PASSED);
	}

	DampFWLimitedVBIC_MtrNm_D_f32 = LimitedVBIC_MtrNm_T_f32;


CombinedDamping_MtrNm_T_f32 = (LimitedDamp_MtrNm_T_f32 + AddedDamp_MtrNm_T_f32) - LimitedVBIC_MtrNm_T_f32;

CombinedDamping_MtrNm_T_f32 = Limit_m( CombinedDamping_MtrNm_T_f32, -D_MTRTRQCMDHILMT_MTRNM_F32, D_MTRTRQCMDHILMT_MTRNM_F32);


	
	DampFWUprBound_MtrNm_D_f32 = UprBoundRaw_MtrNm_T_f32;
	DampFWUprBoundFilt_MtrNm_D_f32 = UprBoundFilt_MtrNm_T_f32;
	DampFWLwrBound_MtrNm_D_f32 = LwrBoundRaw_MtrNm_T_f32;
	DampFWLwrBoundFilt_MtrNm_D_f32 = LwrBoundFilt_MtrNm_T_f32;
	DampFWAddedDamp_MtrNm_D_f32 = AddedDamp_MtrNm_T_f32;
	DampFWAddedDampAFW_MtrNm_D_f32 = AFWAddDamping_MtrNm_T_f32;
	DampFWAddedDampDFW_MtrNm_D_f32 = DFWAddDamping_MtrNm_T_f32;
	Rte_IWrite_DampingFirewall_Per1_CombinedDamping_MtrNm_f32(CombinedDamping_MtrNm_T_f32);
	
	
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_DampingFirewall_Per1_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_DAMPINGFIREWALL_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function: DriverVelCalc
 * 
 * Inputs: Hw_Torque, Motor_Vel_CRF, Vehicle_Speed
 * 
 * Outputs: Scaled Driver Velocity
 * 
 **********************************************************************************************************************/
STATIC FUNC(sint16, AP_FRQDEPDMPNINRTCMP_CODE) DriverVelCalc(  VAR(float32, AUTOMATIC) HwTorque_HwNm_T_f32,
																VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32,
																VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32 )
{
	VAR(float32, AUTOMATIC) TbarVel_HwDegpSec_T_f32;
	VAR(uint16, AUTOMATIC) TbarVel_ScaleFactor_Uls_T_u9p7;
	VAR(float32, AUTOMATIC) TbarVelFiltVal_HwDegpSec_T_f32;
	VAR(uint16, AUTOAMTIC) VehicleSpeed_Kph_T_u9p7;
	VAR(sint32, AUTOAMTIC) TbarVel_HwDegpSec_T_s15p16;
	VAR(sint16, AUTOAMTIC) CRFMotorVel_MtrRadpS_T_s11p4;
	VAR(sint32, AUTOAMTIC) TbarVelFiltVal_HwDegpSec_T_s20p11;
	VAR(sint16, AUTOAMTIC) TbarVelFiltVal_HwRadpSec_T_s9p6;
	VAR(sint32, AUTOAMTIC) ScaledDriverVel_MtrRadpS_T_s17p14;
	VAR(sint32, AUTOAMTIC) TbarVel_MtrRadpSec_T_s24p7;
	VAR(sint32, AUTOAMTIC) TermA_MtrRadpSec_T_s17p14;
	VAR(sint32, AUTOAMTIC) HwTorque_HwNm_T_s14p17;
	VAR(uint16, AUTOAMTIC) CalCmnTbarStiff_NmpDeg_T_u8p8;
	VAR(sint16, AUTOAMTIC) TbarAngle_HwDeg_T_s6p9;
	VAR(sint16, AUTOAMTIC) ScaledDriverVel_MtrRadpS_T_s14p1;
	VAR(sint32, AUTOAMTIC) CRFMotorVel_MtrRadpS_T_s24p7;
	
	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
	
	CRFMotorVel_MtrRadpS_T_s11p4 = FPM_FloatToFixed_m(CRFMotorVel_MtrRadpS_T_f32, s11p4_T);

	HwTorque_HwNm_T_s14p17 = FPM_FloatToFixed_m(HwTorque_HwNm_T_f32, s14p17_T);
	
	CalCmnTbarStiff_NmpDeg_T_u8p8 = FPM_FloatToFixed_m(k_CmnTbarStiff_NmpDeg_f32, u8p8_T);
	
	TbarAngle_HwDeg_T_s6p9 = ((sint32)HwTorque_HwNm_T_s14p17 / (sint32)CalCmnTbarStiff_NmpDeg_T_u8p8);
	/* Hw Trq range is -10 to 10 and cal range is 0.5 to 10 hence the max range out of division is -20 to 20 */
	
	TbarVel_HwDegpSec_T_s15p16 = (((sint32)TbarAngle_HwDeg_T_s6p9 - (sint32)DampFWPrevTbarAng_HwDeg_M_s6p9) * (sint32)D_ONEOVR2MS_SEC_U9P7);
	/* TbarAngle_HwDeg range is -20 to 20 and D_ONEOVR2MS_SEC_U9P7 is 500 results in max range of -20000 to 20000 and hence a s15p16 is enough*/
	
	DampFWPrevTbarAng_HwDeg_M_s6p9 = TbarAngle_HwDeg_T_s6p9; /* Update previous Tbar value */

	TbarVel_HwDegpSec_T_f32 = FPM_FixedToFloat_m(TbarVel_HwDegpSec_T_s15p16, s15p16_T);

	TbarVelFiltVal_HwDegpSec_T_f32 = LPF_OpUpdate_f32_m(TbarVel_HwDegpSec_T_f32, &DampFWTbarVelFiltSv_M_str);
	
	TbarVelFiltVal_HwDegpSec_T_s20p11 = FPM_FloatToFixed_m(TbarVelFiltVal_HwDegpSec_T_f32, s20p11_T);
	
	TbarVelFiltVal_HwRadpSec_T_s9p6 = FPM_Fix_m(((sint32)TbarVelFiltVal_HwDegpSec_T_s20p11 * (sint32)D_PIOVR180_ULS_S4P11), s9p22_T, s9p6_T);
	
	TbarVel_MtrRadpSec_T_s24p7 = FPM_Fix_m(((sint32)TbarVelFiltVal_HwRadpSec_T_s9p6 * (sint32)(FPM_FloatToFixed_m(k_CmnSysKinRatio_MtrDegpHwDeg_f32, u9p7_T))), s18p13_T, s24p7_T);
	
	CRFMotorVel_MtrRadpS_T_s24p7 = FPM_Fix_m(CRFMotorVel_MtrRadpS_T_s11p4, s11p4_T, s24p7_T);
	
	DriverVel_MtrRadpSec_D_s24p7 = (TbarVel_MtrRadpSec_T_s24p7 + CRFMotorVel_MtrRadpS_T_s24p7);
	
	TbarVel_ScaleFactor_Uls_T_u9p7 = IntplVarXY_u16_u16Xu16Y_Cnt(t_DampFWVehSpd_Kph_u9p7, 
																 t_InrtCmp_TBarVel_ScaleFactorTblY_Uls_u9p7, 
																 TableSize_m(t_DampFWVehSpd_Kph_u9p7),
																 VehicleSpeed_Kph_T_u9p7);	
	
	TermA_MtrRadpSec_T_s17p14 =  ((sint32)TbarVel_MtrRadpSec_T_s24p7 * (sint32)TbarVel_ScaleFactor_Uls_T_u9p7);
																 
	ScaledDriverVel_MtrRadpS_T_s17p14 = (sint32)TermA_MtrRadpSec_T_s17p14 + (sint32)FPM_Fix_m(((sint32)CRFMotorVel_MtrRadpS_T_s11p4 * (sint32)(FPM_FloatToFixed_m(k_InrtCmp_MtrVel_ScaleFactor_Uls_f32, u1p15_T))), s12p19_T, s17p14_T);
					   
	ScaledDriverVel_MtrRadpS_T_s14p1 = FPM_Fix_m((Limit_m(ScaledDriverVel_MtrRadpS_T_s17p14, -D_SCALEDDRIVERVEL_MTRRADPS_S17P14, D_SCALEDDRIVERVEL_MTRRADPS_S17P14)), s17p14_T, s14p1_T);
	/* Limited the range to +/- 4095.875 as per discussion with Mike Hales */
	
	ScaledDriverVel_MtrRadpS_D_s14p1 = ScaledDriverVel_MtrRadpS_T_s14p1;
									   
	return(ScaledDriverVel_MtrRadpS_T_s14p1);
}

/**********************************************************************************************************************
 * Function: ADDCoefCalc
 * 
 * Inputs: Base Assist Cmd, Vehicle_Speed, WIRCmdAmpBlnd
 * 
 * Outputs: ADD Coefficient 
 * 
 **********************************************************************************************************************/
STATIC FUNC(uint16, AP_FRQDEPDMPNINRTCMP_CODE) ADDCoefCalc( VAR(float32, AUTOMATIC) BaseAssistCmd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32,
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32,
															 VAR(float32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_f32,
															 VAR(float32, AUTOMATIC) VehicleLonAccel_KphpS_T_f32)
{
	VAR(uint16, AUTOMATIC) ADDCoefCalc_MtrNmSpRad_T_u0p16;
	VAR(uint16, AUTOMATIC) ADDCoefCalc_MtrNmSpRad_T_u1p15;
	VAR(uint16, AUTOMATIC) AbsBaseAssistCmd_MtrNm_T_u4p12;
	VAR(uint16, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_u8p8;
	VAR(uint16, AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
	VAR(sint32, AUTOMATIC) BaseAssistCmd_MtrNm_T_s4p27;
	VAR(uint16, AUTOMATIC) RollingFDD0_MtrNmSpRad_T_um1p17;
	VAR(uint16, AUTOMATIC) RollingFDD1_MtrNmSpRad_T_um1p17;
	VAR(uint16, AUTOMATIC) StaticFDD_MtrNmSpRad_T_um1p17;
	VAR(uint16, AUTOMATIC) RIAstWIRBlnd_MtrNmSpRad_T_u2p14;
	VAR(uint16, AUTOMATIC) FDDBlnd_Uls_T_u8p8;
	VAR(uint16, AUTOMATIC) FinRollingFDD_MtrNmSpRad_T_u0p16;
	VAR(uint16, AUTOMATIC) AbsMotorVel_MtrRadpS_T_u11p5;
	VAR(uint16, AUTOMATIC) DmpDecelGainSlewY_UlspS_T_u13p3;
	VAR(sint16, AUTOMATIC) VehicleLonAccel_KphpS_T_s6p9;
	VAR(uint16, AUTOMATIC) RawDecelGain_Uls_T_u5p11;
	VAR(uint16, AUTOMATIC) DecelGain_Uls_T_u5p11;
	VAR(sint16, AUTOMATIC) CalDmpGainOnThresh_KpHpS_s6p9;
	VAR(sint16, AUTOMATIC) CalDmpGainOffThresh_KpHpS_s6p9;
	VAR(uint16, AUTOMATIC) CalDmpDecelGain_Uls_u5p11;
	VAR(uint16, AUTOMATIC) CalDmpDecelGainFSlew_UlspS_u13p3;
	VAR(sint32, AUTOMATIC) CRFMotorVel_MtrRadpS_T_s11p20;
	
	BaseAssistCmd_MtrNm_T_s4p27 = FPM_FloatToFixed_m(BaseAssistCmd_MtrNm_T_f32, s4p27_T);
	AbsBaseAssistCmd_MtrNm_T_u4p12 = FPM_Fix_m(Abs_s32_m(BaseAssistCmd_MtrNm_T_s4p27),u5p27_T,u4p12_T);
	
	WIRCmdAmpBlnd_MtrNm_T_u8p8 = FPM_FloatToFixed_m(WIRCmdAmpBlnd_MtrNm_T_f32, u8p8_T);
	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
	
	CalDmpGainOnThresh_KpHpS_s6p9 = FPM_FloatToFixed_m(k_DmpGainOnThresh_KphpS_f32, s6p9_T);
	CalDmpGainOffThresh_KpHpS_s6p9 = FPM_FloatToFixed_m(k_DmpGainOffThresh_KphpS_f32, s6p9_T);
	CalDmpDecelGain_Uls_u5p11 = FPM_FloatToFixed_m(k_DmpDecelGain_Uls_f32, u5p11_T);
	CalDmpDecelGainFSlew_UlspS_u13p3 = FPM_FloatToFixed_m(k_DmpDecelGainFSlew_UlspS_f32, u13p3_T) ;
	
	/* Decel Gain */
	CRFMotorVel_MtrRadpS_T_s11p20 = FPM_FloatToFixed_m(CRFMotorVel_MtrRadpS_T_f32, s11p20_T);
	AbsMotorVel_MtrRadpS_T_u11p5 = FPM_Fix_m(Abs_s32_m(CRFMotorVel_MtrRadpS_T_s11p20),u12p20_T,u11p5_T);
	
	DmpDecelGainSlewY_UlspS_T_u13p3 = IntplVarXY_u16_u16Xu16Y_Cnt(t_DmpDecelGainSlewX_MtrRadpS_u11p5,
																  t_DmpDecelGainSlewY_UlspS_u13p3,
																  TableSize_m(t_DmpDecelGainSlewX_MtrRadpS_u11p5),
																  AbsMotorVel_MtrRadpS_T_u11p5);
	
	/* mutiply after conversion to float */
	VehicleLonAccel_KphpS_T_f32 = VehicleLonAccel_KphpS_T_f32*(-1.0F);
	VehicleLonAccel_KphpS_T_s6p9 = FPM_FloatToFixed_m(Limit_m(VehicleLonAccel_KphpS_T_f32, VEHICLELONACCEL_MIN_F32, VEHICLELONACCEL_MAX_F32),s6p9_T);
	
	if (VehicleLonAccel_KphpS_T_s6p9 > CalDmpGainOnThresh_KpHpS_s6p9)
	{
		RawDecelGain_Uls_T_u5p11 = CalDmpDecelGain_Uls_u5p11;
	}
	else if (VehicleLonAccel_KphpS_T_s6p9 < CalDmpGainOffThresh_KpHpS_s6p9)
	{
		RawDecelGain_Uls_T_u5p11 = D_ONE_ULS_U5P11;
	}
	else
	{
		RawDecelGain_Uls_T_u5p11 = PrevDecelGain_Uls_M_u5p11;
	}
	
	RawDecelGain_Uls_D_u5p11 = RawDecelGain_Uls_T_u5p11;
	
	/* Rate Limiter */
	DecelGain_Uls_T_u5p11 = Limit_m((sint32)RawDecelGain_Uls_T_u5p11,
										(sint32)((sint32)PrevDecelGain_Uls_M_u5p11 - (sint32)(FPM_Fix_m(((uint32)CalDmpDecelGainFSlew_UlspS_u13p3 * (uint32)D_2MS_SEC_U0P16), u13p19_T, u5p11_T))),
										(sint32)(PrevDecelGain_Uls_M_u5p11 + (FPM_Fix_m(((uint32)DmpDecelGainSlewY_UlspS_T_u13p3 * (uint32)D_2MS_SEC_U0P16), u13p19_T, u5p11_T))));
									
	PrevDecelGain_Uls_M_u5p11 = DecelGain_Uls_T_u5p11;
	DecelGain_Uls_D_u5p11 = DecelGain_Uls_T_u5p11;
	
	RollingFDD0_MtrNmSpRad_T_um1p17 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_DmpADDCoefX_MtrNm_u4p12, 
																	t2_FDD_ADDRollingTblYM_MtrNmpRadpS_um1p17[0], 
																	TableSize_m(t_DmpADDCoefX_MtrNm_u4p12),
																	AbsBaseAssistCmd_MtrNm_T_u4p12);
	
	RollingFDD1_MtrNmSpRad_T_um1p17 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_DmpADDCoefX_MtrNm_u4p12, 
																	t2_FDD_ADDRollingTblYM_MtrNmpRadpS_um1p17[1], 
																	TableSize_m(t_DmpADDCoefX_MtrNm_u4p12),
																	AbsBaseAssistCmd_MtrNm_T_u4p12);
	
	StaticFDD_MtrNmSpRad_T_um1p17 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_DmpADDCoefX_MtrNm_u4p12, 
																	t_FDD_ADDStaticTblY_MtrNmpRadpS_um1p17, 
																	TableSize_m(t_DmpADDCoefX_MtrNm_u4p12),
																	AbsBaseAssistCmd_MtrNm_T_u4p12);
	
	RIAstWIRBlnd_MtrNmSpRad_T_u2p14 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_WIRBlndTblX_MtrNm_u8p8, 
																	t_RIAstWIRBlndTblY_Uls_u2p14, 
																	TableSize_m(t_WIRBlndTblX_MtrNm_u8p8),
																	WIRCmdAmpBlnd_MtrNm_T_u8p8);
	
	/* change the vehspd cal to u9p7 and the corresponding input to u9p7 */
	FDDBlnd_Uls_T_u8p8 = IntplVarXY_u16_u16Xu16Y_Cnt(	t_DampFWVehSpd_Kph_u9p7, 
														t_FDD_BlendTblY_Uls_u8p8, 
														TableSize_m(t_DampFWVehSpd_Kph_u9p7),
														VehicleSpeed_Kph_T_u9p7);	
	
	FinRollingFDD_MtrNmSpRad_T_u0p16 = 	FPM_Fix_m((RollingFDD1_MtrNmSpRad_T_um1p17 * RIAstWIRBlnd_MtrNmSpRad_T_u2p14), u1p31_T, u0p16_T) + 
										FPM_Fix_m(((uint32)RollingFDD0_MtrNmSpRad_T_um1p17 * ((uint32)D_ONE_ULS_U2P14 - (uint32)RIAstWIRBlnd_MtrNmSpRad_T_u2p14)), u1p31_T, u0p16_T);
	
	ADDCoefCalc_MtrNmSpRad_T_u1p15 = FPM_Fix_m(((uint32)StaticFDD_MtrNmSpRad_T_um1p17 * ((uint32)D_ONE_ULS_U8P8 - (uint32)FDDBlnd_Uls_T_u8p8)), u7p25_T, u1p15_T) + 
	                                 FPM_Fix_m(((uint32)FinRollingFDD_MtrNmSpRad_T_u0p16 * (uint32)FDDBlnd_Uls_T_u8p8), u8p24_T, u1p15_T);
									 
	ADDCoefCalc_MtrNmSpRad_T_u1p15 = Limit_m(ADDCoefCalc_MtrNmSpRad_T_u1p15, 0U, D_ADDCOEFCALCHILIMIT_MTRNMSPRAD_U1P15);								 
									 
	ADDCoefCalc_MtrNmSpRad_T_u0p16 = FPM_Fix_m((Limit_m((FPM_Fix_m(((uint32)ADDCoefCalc_MtrNmSpRad_T_u1p15 * (uint32)DecelGain_Uls_T_u5p11), u6p26_T, u3p13_T)), 0U, D_ADDCOEFCALCHILIMIT_MTRNMSPRAD_U3P13)), u3p13_T, u0p16_T);
		
	ADDCoefCalc_MtrNmSpRad_D_u0p16 = ADDCoefCalc_MtrNmSpRad_T_u0p16;

	return(ADDCoefCalc_MtrNmSpRad_T_u0p16);
}

/**********************************************************************************************************************
 * Function: FilterCoefCalc
 * 
 * Inputs: ADDCoefCalc_MtrNmSpRad_T_u0p16, Vehicle_Speed, WIRCmdAmpBlnd, *FilterCoef_T_Str
 * 
 * Outputs: Create filter coefs (b0 -> b2, a0 -> a2)
 * 
 **********************************************************************************************************************/
STATIC FUNC(void, AP_FRQDEPDMPNINRTCMP_CODE) FilterCoefCalc( VAR(uint16, AUTOMATIC) ADDCoefCalc_MtrNmSpRad_T_u0p16, 
															 VAR(float32, AUTOMATIC) VehicleSpeed_Kph_T_f32, 
															 VAR(float32, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_f32, 
															 CONSTP2VAR(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str)
{
	VAR(uint16, AUTOMATIC) WIRCmdAmpBlnd_MtrNm_T_u8p8;
	VAR(uint16, AUTOMATIC) VehicleSpeed_Kph_T_u9p7;
	VAR(uint16, AUTOMATIC) FreqFilt0_Hz_T_u12p4;
	VAR(uint16, AUTOMATIC) FreqFilt1_Hz_T_u12p4;
	VAR(uint16, AUTOMATIC) DampFiltKpWIR_Hz_T_u2p14;
	VAR(uint16, AUTOMATIC) FiltFreqLUBlndSqrt_RadpS_T_u10p6;
	VAR(uint16, AUTOMATIC) InertiaCompCalc_MtrNm_T_u9p7;
	VAR(sint16, AUTOMATIC)	filtCoefA0TmpCalc_Uls_T_s2p13;
	VAR(sint16, AUTOMATIC)	filtCoefAxTmpCalc_Uls_T_s2p13;

	VAR(uint16, AUTOMATIC) filtCoefBx1TmpCalc_Uls_T_u1p15;
	VAR(sint16, AUTOMATIC) filtCoefBx2TmpCalc_Uls_T_s0p15;
	VAR(uint16, AUTOMATIC) filtCoefBx3TmpCalc_Uls_T_u1p15;
	
	VAR(float32, AUTOMATIC)	FiltFreqLUBlndSqrt_RadpS_T_f32;
	VAR(sint16, AUTOMATIC)	FiltFreqLUBlnd_RadpS_T_s10p5;
	VAR(uint32, AUTOMATIC)	FiltFreqLUBlnd_RadSqpSSq_T_u28p4;
	VAR(uint32, AUTOMATIC)	FiltFreqLUBlnd_RadSqpSSq_T_u22p10;
	VAR(uint16, AUTOMATIC)	InrtCmpScaleFactor_Uls_T_u9p7;
	VAR(uint32, AUTOMATIC)	TermA_RadSqpSSq_T_u21p11;
	VAR(uint16, AUTOMATIC)	TermB_KgmSq_T_u0p16;
	VAR(uint32, AUTOMATIC)	ADDCoefCalc_MtrNmSpRad_T_u10p22;
	VAR(uint32, AUTOMATIC)	TermA_RadSqpSSq_T_u26p6;

	VehicleSpeed_Kph_T_u9p7 = FPM_FloatToFixed_m(VehicleSpeed_Kph_T_f32, u9p7_T);
	WIRCmdAmpBlnd_MtrNm_T_u8p8 = FPM_FloatToFixed_m(WIRCmdAmpBlnd_MtrNm_T_f32, u8p8_T);

	/* Filter feq lookup and blending */
	FreqFilt0_Hz_T_u12p4 = IntplVarXY_u16_u16Xu16Y_Cnt(t_DampFWVehSpd_Kph_u9p7, 
																		t2_FDD_FreqTblYM_Hz_u12p4[0], 
																		TableSize_m(t_DampFWVehSpd_Kph_u9p7),
																		VehicleSpeed_Kph_T_u9p7);	

	FreqFilt1_Hz_T_u12p4 = IntplVarXY_u16_u16Xu16Y_Cnt(t_DampFWVehSpd_Kph_u9p7, 
																		t2_FDD_FreqTblYM_Hz_u12p4[1], 
																		TableSize_m(t_DampFWVehSpd_Kph_u9p7),
																		VehicleSpeed_Kph_T_u9p7);

	DampFiltKpWIR_Hz_T_u2p14 = IntplVarXY_u16_u16Xu16Y_Cnt(t_WIRBlndTblX_MtrNm_u8p8, 
																		t_DmpFiltKpWIRBlndY_Uls_u2p14, 
																		TableSize_m(t_WIRBlndTblX_MtrNm_u8p8),
																		WIRCmdAmpBlnd_MtrNm_T_u8p8);

	/* FDD value [w] */
	
	FiltFreqLUBlnd_RadpS_T_s10p5 =  (sint16)FPM_Fix_m(((sint32)FreqFilt1_Hz_T_u12p4 * (sint32)DampFiltKpWIR_Hz_T_u2p14), u14p18_T, s10p5_T) + 
									(sint16)FPM_Fix_m(((sint32)FreqFilt0_Hz_T_u12p4 * ((sint32)D_ONE_ULS_U2P14 - (sint32)DampFiltKpWIR_Hz_T_u2p14)), s13p18_T, s10p5_T);
													
	FiltFreqLUBlnd_RadpS_T_s10p5 = FPM_Fix_m(((sint32)FiltFreqLUBlnd_RadpS_T_s10p5 * (sint32)D_2PI_ULS_U3P13), s13p18_T, s10p5_T);
	
	FiltFreq_RadpS_D_s10p5 = FiltFreqLUBlnd_RadpS_T_s10p5;

	
	InrtCmpScaleFactor_Uls_T_u9p7 = IntplVarXY_u16_u16Xu16Y_Cnt(t_DampFWVehSpd_Kph_u9p7, 
																		t_InrtCmp_ScaleFactorTblY_Uls_u9p7, 
																		TableSize_m(t_DampFWVehSpd_Kph_u9p7),
																		VehicleSpeed_Kph_T_u9p7);
	
	FiltFreqLUBlnd_RadSqpSSq_T_u22p10 = ((uint32)FiltFreqLUBlnd_RadpS_T_s10p5 * (uint32)FiltFreqLUBlnd_RadpS_T_s10p5) + (uint32)D_ONE_ULS_U22P10;
	
	FiltFreqLUBlndSqrt_RadpS_T_f32 = sqrtf(FPM_FixedToFloat_m(FiltFreqLUBlnd_RadSqpSSq_T_u22p10, u22p10_T)); 
	
	FiltFreqLUBlndSqrt_RadpS_T_u10p6 = FPM_FloatToFixed_m(FiltFreqLUBlndSqrt_RadpS_T_f32, u10p6_T);

	/* FDD value [k] */
	
	FiltFreqLUBlnd_RadSqpSSq_T_u28p4 = FPM_Fix_m(FiltFreqLUBlnd_RadSqpSSq_T_u22p10, u22p10_T, u28p4_T);
	
	TermA_RadSqpSSq_T_u21p11 = ((uint32)InrtCmpScaleFactor_Uls_T_u9p7 * (uint32)FiltFreqLUBlnd_RadSqpSSq_T_u28p4);
	
	TermA_RadSqpSSq_T_u26p6 = FPM_Fix_m(TermA_RadSqpSSq_T_u21p11, u21p11_T, u26p6_T);
	
	ADDCoefCalc_MtrNmSpRad_T_u10p22 = FPM_Fix_m(ADDCoefCalc_MtrNmSpRad_T_u0p16, u0p16_T, u10p22_T);
	
	TermB_KgmSq_T_u0p16 = (uint16)(ADDCoefCalc_MtrNmSpRad_T_u10p22 / (uint32)FiltFreqLUBlndSqrt_RadpS_T_u10p6);
	
	TermB_KgmSq_T_u0p16 = (uint16)TermB_KgmSq_T_u0p16 + (uint16)(FPM_FloatToFixed_m(k_InrtCmp_MtrInertia_KgmSq_f32, u0p16_T));
	
	InertiaCompCalc_MtrNm_T_u9p7 = FPM_Fix_m(((uint32)TermA_RadSqpSSq_T_u26p6 * (uint32)TermB_KgmSq_T_u0p16), u10p22_T, u9p7_T);

	InertiaCompCalc_MtrNm_D_u9p7 = InertiaCompCalc_MtrNm_T_u9p7;
	
	/* B Terms */
	filtCoefBx1TmpCalc_Uls_T_u1p15 = FPM_Fix_m(((uint32)InertiaCompCalc_MtrNm_T_u9p7 * (uint32)D_2MS_SEC_U2P14), u11p21_T, u1p15_T);
	filtCoefBx2TmpCalc_Uls_T_s0p15 = FPM_Fix_m(((sint32)FPM_Fix_m(D_2MS_SEC_U2P14, u2p14_T, u7p9_T) * (sint32)((sint32)ADDCoefCalc_MtrNmSpRad_T_u0p16 * (sint32)FiltFreqLUBlnd_RadpS_T_s10p5)), s1p30_T, s0p15_T);
	filtCoefBx3TmpCalc_Uls_T_u1p15 = FPM_Fix_m(((uint32)ADDCoefCalc_MtrNmSpRad_T_u0p16 * (uint32)D_TWO_ULS_S2P13), u3p29_T, u1p15_T);

	/* b0 Calc */
	filtCoef_Uls_T_Str->b0_Uls_s0p15 = FPM_Fix_m(((sint32)((sint32)filtCoefBx2TmpCalc_Uls_T_s0p15 - (sint32)filtCoefBx1TmpCalc_Uls_T_u1p15 - (sint32)filtCoefBx3TmpCalc_Uls_T_u1p15) * (sint32)D_TWO_ULS_S2P13), s3p28_T, s0p15_T);
	/* b1 Calc */
	filtCoef_Uls_T_Str->b1_Uls_u0p16 = FPM_Fix_m(((uint32)ADDCoefCalc_MtrNmSpRad_T_u0p16 * (uint32)D_EIGHT_ULS_U10P6), u10p22_T, u0p16_T);
	/* b2 Calc */
	filtCoef_Uls_T_Str->b2_Uls_s0p15 = FPM_Fix_m((sint32)D_TWO_ULS_S2P13 * (sint32)((sint32)filtCoefBx1TmpCalc_Uls_T_u1p15 - (sint32)filtCoefBx2TmpCalc_Uls_T_s0p15 - (sint32)filtCoefBx3TmpCalc_Uls_T_u1p15), s3p28_T, s0p15_T);

	/* A terms */
	filtCoefAxTmpCalc_Uls_T_s2p13 = FPM_Fix_m(((sint32)FiltFreqLUBlnd_RadpS_T_s10p5 * (sint32)D_2MS_SEC_U2P14), s12p19_T, s2p13_T);
	/* a0 TmpCalc */
	filtCoefA0TmpCalc_Uls_T_s2p13 = filtCoefAxTmpCalc_Uls_T_s2p13 - D_TWO_ULS_S2P13;
	filtCoef_Uls_T_Str->a0_Uls_u2p14 = FPM_Fix_m(((sint32)filtCoefA0TmpCalc_Uls_T_s2p13 * (sint32)filtCoefA0TmpCalc_Uls_T_s2p13), s5p26_T, u2p14_T);
	/* a1 TmpCalc */
	filtCoef_Uls_T_Str->a1_Uls_s4p11 = FPM_Fix_m(((sint32)((FPM_Fix_m(((sint32)filtCoefAxTmpCalc_Uls_T_s2p13 * (sint32)filtCoefAxTmpCalc_Uls_T_s2p13), s5p26_T, s3p12_T)) - D_FOUR_ULS_S3P12) * (sint32)D_TWO_ULS_S2P13), s6p25_T, s4p11_T);
	/* a2 TmpCalc */
	filtCoefAxTmpCalc_Uls_T_s2p13 = (filtCoefAxTmpCalc_Uls_T_s2p13 + D_TWO_ULS_S2P13);
	filtCoef_Uls_T_Str->a2_Uls_u5p11 = FPM_Fix_m(((sint32)filtCoefAxTmpCalc_Uls_T_s2p13 * (sint32)filtCoefAxTmpCalc_Uls_T_s2p13), s5p26_T, u5p11_T);
}


/**********************************************************************************************************************
 * Function: GenFddIcCmd
 * 
 * Inputs: ScaledDriverVel_MtrRadpS_T_s14p1, *FilterCoef_T_Str
 * 
 * Outputs: Compenstation_MtrNm_T_f32;
 * 
 **********************************************************************************************************************/
STATIC FUNC(sint32, AP_FRQDEPDMPNINRTCMP_CODE) GenFddIcCmd( VAR(sint16, AUTOMATIC) ScaledDriverVel_MtrRadpS_T_s14p1, 
																 CONSTP2CONST(filterCoef_T, AUTOMATIC, AUTOMATIC) filtCoef_Uls_T_Str)
{
	VAR(float32, AUTOMATIC) filtCoef_a2_Uls_f32;
	VAR(float32, AUTOMATIC) DampFWPreAttnComp_MtrNm_T_f32;
	VAR(float32, AUTOMATIC) DampFWGenCmd_MtrNm_T_f32;
	
	VAR(sint32, AUTOMATIC) Compensation_MtrNm_T_s11p20;
	VAR(sint32, AUTOMATIC) GenCmdB0_MtrNm_T_s16p15;
	VAR(sint32, AUTOMATIC) GenCmdB1_MtrNm_T_s16p15;
	VAR(sint32, AUTOMATIC) GenCmdB2_MtrNm_T_s16p15;
	VAR(sint32, AUTOMATIC) GenCmdAx_Uls_T_s16p15;
	VAR(sint32, AUTOMATIC) PreAttnComp_MtrNm_T_s19p12;
	
	VAR(uint16, AUTOMATIC) OutputAtten_Uls_T_u8p8; 
	VAR(uint16, AUTOMATIC) AbsScaledDriverVel_MtrRadpS_T_u12p4;


	AbsScaledDriverVel_MtrRadpS_T_u12p4 = FPM_Fix_m((Limit_m((Abs_s16_m(ScaledDriverVel_MtrRadpS_T_s14p1)), 0U, D_ABSSCALEDRIVERVELHI_MTRRADPS_U15P1)), u15p1_T, u12p4_T);
	OutputAtten_Uls_T_u8p8 = IntplVarXY_u16_u16Xu16Y_Cnt(t_FDD_AttenTblX_MtrRadpS_u12p4, 
																		t_FDD_AttenTblY_Uls_u8p8, 
																		TableSize_m(t_FDD_AttenTblX_MtrRadpS_u12p4),
																		AbsScaledDriverVel_MtrRadpS_T_u12p4);
	OutputAtten_Uls_D_u8p8 = OutputAtten_Uls_T_u8p8;
	
	GenCmdB0_MtrNm_T_s16p15 = FPM_Fix_m(((sint32)filtCoef_Uls_T_Str->b0_Uls_s0p15 * (sint32)DampFWPrev2SclDrvVel_MtrRadpS_M_s14p1), s15p16_T, s16p15_T);
	
	GenCmdB1_MtrNm_T_s16p15 = FPM_Fix_m(((sint32)filtCoef_Uls_T_Str->b1_Uls_u0p16 * (sint32)DampFWPrev1SclDrvVel_MtrRadpS_M_s14p1), s14p17_T, s16p15_T);

	GenCmdB2_MtrNm_T_s16p15 = FPM_Fix_m(((sint32)filtCoef_Uls_T_Str->b2_Uls_s0p15 * (sint32)ScaledDriverVel_MtrRadpS_T_s14p1), s15p16_T, s16p15_T);

	GenCmdAx_Uls_T_s16p15 = FPM_Fix_m((((sint32)DampFWPrev1PreAttnComp_MtrNm_M_s20p11 * (sint32)filtCoef_Uls_T_Str->a1_Uls_s4p11) + 
							FPM_Fix_m(((sint32)DampFWPrev2PreAttnComp_MtrNm_M_s20p11 * (sint32)filtCoef_Uls_T_Str->a0_Uls_u2p14), s6p25_T, s9p22_T)),s9p22_T,s16p15_T);

	DampFWGenCmd_MtrNm_T_f32 = FPM_FixedToFloat_m(((GenCmdB0_MtrNm_T_s16p15 + GenCmdB1_MtrNm_T_s16p15 + GenCmdB2_MtrNm_T_s16p15) - 
							   GenCmdAx_Uls_T_s16p15), s16p15_T);
	
	/* Floating point part */

	filtCoef_a2_Uls_f32 = FPM_FixedToFloat_m(filtCoef_Uls_T_Str->a2_Uls_u5p11, u5p11_T);
	DampFWPreAttnComp_MtrNm_T_f32 = DampFWGenCmd_MtrNm_T_f32 / filtCoef_a2_Uls_f32;

	/* End Floating point part */
	
	/* Update previous values */
	DampFWPrev2PreAttnComp_MtrNm_M_s20p11 = DampFWPrev1PreAttnComp_MtrNm_M_s20p11;
	DampFWPrev1PreAttnComp_MtrNm_M_s20p11 = FPM_FloatToFixed_m(DampFWPreAttnComp_MtrNm_T_f32, s20p11_T);
	DampFWPrev2SclDrvVel_MtrRadpS_M_s14p1 = DampFWPrev1SclDrvVel_MtrRadpS_M_s14p1;
	DampFWPrev1SclDrvVel_MtrRadpS_M_s14p1 = ScaledDriverVel_MtrRadpS_T_s14p1;
	
	PreAttnComp_MtrNm_T_s19p12 = FPM_FloatToFixed_m(DampFWPreAttnComp_MtrNm_T_f32, s19p12_T);
	
	Compensation_MtrNm_T_s11p20 = ((sint32)PreAttnComp_MtrNm_T_s19p12 * ((sint32)OutputAtten_Uls_T_u8p8));

	Compensation_MtrNm_T_s11p20 = Limit_m(Compensation_MtrNm_T_s11p20, -D_COMPENSATIONLIMIT_MTRNM_S11P20, D_COMPENSATIONLIMIT_MTRNM_S11P20);
	
	return(Compensation_MtrNm_T_s11p20);
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
