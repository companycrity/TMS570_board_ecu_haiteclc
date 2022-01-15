/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_SrlComOutput.c
 *     Workspace:  C:/synergy_projects/Haitec/Haitec_LC_EPS_TMS570#sag_EPS#1-EA3#fzh7xw/Haitec_LC_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *     SW-C Type:  Ap_SrlComOutput
 *  Generated at:  Thu Jan 21 14:33:32 2016
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_SrlComOutput>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * %version:          EA3#9.1.7 %
 * %derived_by:       fzh7xw %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev      Author   Change Description                                                               SCR #
 * --------   -------  -------  ------------------------------------------------------------------------------  -------
 * 07/18/13    1       OT       Initial Version
 * 08/01/13    2       OT       Implemented SCom messages
 * 08/02/13    3       OT       Implemented EpasFailure
 * 08/08/13    4       OT       Fixed EpasFailure casting issue
 * 08/14/13    5       OT       Fixed Steering_Torque signal
 * 08/28/13    6       OT       Updated EpasFailed strategy
 * 08/30/13    7       OT       Implemented ComM mode requests, mode disabling for new EpasFailed strategy
 * 01/09/14    8       OT       Added MemMap statements
 * 02/17/14    9       OT       Updates for SER 001F
 * 02/13/15    9.1.1   OT       Updates for SER 001I                                                             38922
 * 04/17/15    9.1.2   OT       Updates to NM logic
 * 04/22/15    9.1.3   OT       Update to message Tx disabling method                                            13262
 * 06/25/15    9.1.4   OT       ErrorPassive anomaly fix
 * 06/25/15    9.1.5   OT       Changed from complete Tx/Rx disabling to just periodic Tx disabling
 * 10/16/15    9.1.6   OT       Corrected Dem call conditions                                                 EA3#3944
 * 01/22/16    9.1.7   WH       Added new signals for SCIR002C
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Operation Prototypes:
 =====================
  DtrmnElapsedTime_mS_u16 of Port Interface SystemTime
    Nexteer SystemTime Service


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_SrlComOutput.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "Com.h"
#include "Can.h"
#include "CanIf.h"
#include "CalConstants.h"
#include "GlobalMacro.h"


#define D_SASANGLELOLMT_HWDEG_F32			-900.0f
#define D_SASANGLEHILMT_HWDEG_F32			900.0f
#define D_SASANGLEOFFSET_HWDEG_F32			900.0f
#define D_SASANGLESCALE_HWDEGPCNT_F32		0.1f
#define D_ELECTPWRLOLMT_AMP_F32				0.0f
#define D_ELECTPWRHILMT_AMP_F32				127.0f
#define D_ELECTPWRSCALE_AMPPCNT_F32			0.5f
#define D_STEERINGTORQUELOLMT_HWNM_F32		-22.78f
#define D_STEERINGTORQUEHILMT_HWNM_F32		22.967f
#define D_STEERINGTORQUEOFFSET_HWNM_F32		22.78f
#define D_STEERINGTORQUESCALE_HWNMPCNT_F32	0.1794f
#define D_RELSTEERWHLANGSCALE_HWDEG_F32 	0.1f
#define D_RELSTEERWHLANGOFFSET_HWDEG_F32 	2000.0f
#define D_RELSTEERWHLANGLOLMT_HWDEG_F32 	-2000.0f
#define D_RELSTEERWHLANGHILMT_HWDEG_F32 	2000.0f


#define SRLCOMOUTPUT_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint32, AP_SRLCOMOUTPUT_VAR) NMTimer_mS_M_u32;
STATIC VAR(float32, AP_SRLCOMOUTPUT_VAR) RelHwPosInit_HwDeg_M_f32;
#define SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


#define SRLCOMOUTPUT_START_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(uint8, AP_SRLCOMOUTPUT_VAR) SASMsgCount_Cnt_M_u08;
STATIC VAR(uint8, AP_SRLCOMOUTPUT_VAR) NMMessage_Cnt_M_u08[8u];
STATIC VAR(Dem_IndicatorStatusType, AP_SRLCOMOUTPUT_VAR) EpasFailedIndicator_Cnt_M_enum;
STATIC VAR(uint8, AUTOMATIC) CumMechMtrPosStatus_Cnt_M_u08;
#define SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" /* PRQA S 5087 */


#define SRLCOMOUTPUT_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) NMFirstMessageSent_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) NMSendMessage_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) NMBusOffSinceLastTx_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) NMErrorSinceLastTx_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) PrevEpsEn_Cnt_M_lgc;
STATIC VAR(boolean, AP_SRLCOMOUTPUT_VAR) RelHwPosInitSet_Cnt_M_lgc;
#define SRLCOMOUTPUT_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */


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
 * DT_Elect_PWR_Consumpt: Integer in interval [0...254]
 * DT_EpasFailed: Boolean
 * DT_Rel_Steer_Wheel_Ang: Integer in interval [0...65535]
 * DT_Rel_Steer_Wheel_Ang_Validity: Integer in interval [0...1]
 * DT_SAS_Angle: Integer in interval [0...18000]
 * DT_SAS_CAL: Boolean
 * DT_SAS_CheckSum: Integer in interval [0...15]
 * DT_SAS_Init: Boolean
 * DT_SAS_MsgCount: Integer in interval [0...15]
 * DT_SAS_OK: Boolean
 * DT_Steering_Torque: Integer in interval [0...255]
 * DT_Steering_Torque_V: Boolean
 * Double: Real in interval [-DBL_MAX...DBL_MAX] with double precision including NaN (standard type)
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 * IoHwAb_BoolType: Integer in interval [0...1]
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * ComM_ModeType: Enumeration of integer in interval [0...2] with enumerators
 *   COMM_NO_COMMUNICATION (0U)
 *   COMM_SILENT_COMMUNICATION (1U)
 *   COMM_FULL_COMMUNICATION (2U)
 * Dem_IndicatorStatusType: Enumeration of integer in interval [0...3] with enumerators
 *   DEM_INDICATOR_OFF (0U)
 *   DEM_INDICATOR_CONTINUOUS (1U)
 *   DEM_INDICATOR_BLINKING (2U)
 *   DEM_INDICATOR_BLINK_CONT (3U)
 * NTCNumber: Enumeration of integer in interval [0...511] with enumerators
 *   NTC_Num_FlashWrapperLgcFlt (1U)
 *   NTC_Num_FlashECCCorr (2U)
 *   NTC_Num_FlashECCMemFlt (3U)
 *   NTC_Num_FlashCRCMemFault (4U)
 *   NTC_Num_NvMBlkDftActA (6U)
 *   NTC_Num_NvMBlkDftActB (7U)
 *   NTC_Num_NvMBlkDftActC (8U)
 *   NTC_Num_CurrentSensorCalOutOfRange (9U)
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
 *   NTC_Num_PeripheralStartupFlt (55U)
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
 *   NTC_Num_BattVltgMeasdCorrlnFlt (73U)
 *   NTC_Num_IvtrPwrDiscnctFailr (74U)
 *   NTC_Num_PowerRelayInit2Flt (75U)
 *   NTC_Num_GateDrvFltInProcess (76U)
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
 *   NTC_Num_Inv2GateDrvFltInProcess (92U)
 *   NTC_Num_Inv2GateDrvFlt (93U)
 *   NTC_Num_Inv2OnStateSingleFET (94U)
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
 *   NTC_Num_HWACrossChecks (108U)
 *   NTC_Num_HWASnsrCommFault (109U)
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
 *   NTC_Num_TurnCntr_PosLossNotSpdDep (134U)
 *   NTC_Num_KinematicIntDiag (144U)
 *   NTC_Num_HighFriction (145U)
 *   NTC_Num_DutyCycleExceeded (148U)
 *   NTC_Num_AbsTempThermLimit (149U)
 *   NTC_Num_LatchActive (160U)
 *   NTC_Num_OpTrqVsHwTrq (168U)
 *   NTC_Num_CurrentReas (169U)
 *   NTC_Num_LoaRpdShutdn (170U)
 *   NTC_Num_LoaCtrldShutdn (171U)
 *   NTC_Num_LoaMgr_HwTqIdptSigTooLow (172U)
 *   NTC_Num_LoaMgr_MotAgIdptSigTooLow (173U)
 *   NTC_Num_LoaMgr_MotCurrIdptSigTooLow (174U)
 *   NTC_Num_LoaMgr_IvtrIdptSigTooLow (175U)
 *   NTC_Num_OpVoltage (176U)
 *   NTC_Num_ExVoltageLow (177U)
 *   NTC_Num_ReducedAsstLowVoltage (178U)
 *   NTC_Num_ExVoltageHigh (180U)
 *   NTC_Num_OpVoltageOvrMax (181U)
 *   NTC_Num_BattTransOverVolt (182U)
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
 *   NTC_Num_DataOther2FltMsg_M (295U)
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
 *   NTC_Num_DataOtherFlt2Msg_R (335U)
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
 *   NTC_Num_InvalidMsg_ParkAssistParallel (464U)
 *   NTC_Num_FlexrayCommunicationError (465U)
 *   NTC_Num_InvalidMsg_AI (466U)
 *   NTC_Num_MissingMsg_AI (467U)
 *   NTC_Num_InvalidMsg_AJ (472U)
 *   NTC_Num_MissingMsg_AJ (473U)
 *   NTC_Num_InvalidMsg_AK (480U)
 *   NTC_Num_MissingMsg_AK (481U)
 *   NTC_Num_MissingMsg_AL (489U)
 *   NTC_Num_SysConsistencyVerf (496U)
 *   NTC_Num_ConfigMisMatch (497U)
 *   NTC_Num_CalNotPrgmd (498U)
 *   NTC_Num_TunSetNotPrgmd (499U)
 *   NTC_Num_EEPROMtoFeeCpyError (500U)
 *   NTC_Num_EOLVehTunNtPerf (501U)
 *   NTC_Num_MtrSensorNotTrimmed (502U)
 *   NTC_Num_HWASensorNotTrimmed (504U)
 *   NTC_Num_HWASensorTrimNoAttempt (505U)
 *   NTC_Num_TrqSensorScaleNotSet (506U)
 *   NTC_Num_TrqSensorNotTrimmed (507U)
 *   NTC_Num_AnaHWDiffTqOfstNotTrmd (508U)
 *   NTC_Num_DigTrqSensorScaleNotSet (509U)
 *   NTC_Num_DigTrqSensorNotTrimmed (510U)
 *   NTC_Num_SENTHWDiffTqOfstNotTrmd (511U)
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
 * Boolean: D_TRUE_CNT_LGC = TRUE
 * Double: D_SFINVMILLI_ULS_F32 = 1000
 * Float: D_100MS_SEC_F32 = 0.1F
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082F
 * Float: D_2MS_SEC_F32 = 0.002F
 * Float: D_2PI_ULS_F32 = 6.2831853071796F
 * Float: D_MSECPERSEC_ULS_F32 = 1000.0F
 * Float: D_MTRTRQCMDHILMT_MTRNM_F32 = 8.8F
 * Float: D_MTRTRQCMDLOLMT_MTRNM_F32 = -8.8F
 * Float: D_ONE_ULS_F32 = 1.0F
 * Float: D_PIOVR180_ULS_F32 = 0.0174532925199F
 * Float: D_PI_ULS_F32 = 3.1415926535898F
 * Float: D_RADPERREV_ULS_F32 = 6.28318530718F
 * Float: D_VECUMIN_VOLTS_F32 = 5.0F
 * Float: D_ZERO_ULS_F32 = 0.0F
 * SInt16: D_NEGONE_CNT_S16 = -1
 * SInt16: D_ONE_CNT_S16 = 1
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt32: D_NEGONE_CNT_S32 = -1
 * SInt32: D_ONE_CNT_S32 = 1
 * SInt32: D_ZERO_CNT_S32 = 0
 * SInt8: D_NEGONE_CNT_S8 = -1
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ONE_CNT_U16 = 1U
 * UInt16: D_SEVEN_CNT_U16 = 7U
 * UInt16: D_ZERO_CNT_U16 = 0U
 * UInt32: D_ONE_CNT_U32 = 1U
 * UInt32: D_ZERO_CNT_U32 = 0U
 * UInt8: D_FOUR_CNT_U08 = 4U
 * UInt8: D_MTRPOLESDIV2_CNT_U8 = 3U
 * UInt8: D_ONE_CNT_U8 = 1U
 * UInt8: D_QUADRANT1_CNT_U8 = 1U
 * UInt8: D_QUADRANT2_CNT_U8 = 2U
 * UInt8: D_QUADRANT3_CNT_U8 = 3U
 * UInt8: D_QUADRANT4_CNT_U8 = 4U
 * UInt8: D_THREE_CNT_U08 = 3U
 * UInt8: D_TWO_CNT_U08 = 2U
 * UInt8: D_ZERO_CNT_U8 = 0U
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_SRLCOMOUTPUT_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SrlComOutput_Init1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
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
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_ComM_UserRequest_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_COMM_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) SrlComOutput_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SrlComOutput_Init1
 *********************************************************************************************************************/
	
	PrevEpsEn_Cnt_M_lgc = TRUE;
	Rte_Call_ComM_UserRequest_RequestComMode(COMM_FULL_COMMUNICATION);
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SrlComOutput_Per1
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   UInt8 Rte_IRead_SrlComOutput_Per1_CumMechMtrPosStatus_Cnt_u08(void)
 *   Float Rte_IRead_SrlComOutput_Per1_HandwheelAuthority_Uls_f32(void)
 *   Float Rte_IRead_SrlComOutput_Per1_HandwheelPosition_HwDeg_f32(void)
 *   Float Rte_IRead_SrlComOutput_Per1_RelHwPos_HwDeg_f32(void)
 *   UInt16 Rte_IRead_SrlComOutput_Per1_SrlComHwPosStatus_Cnt_u16(void)
 *   Boolean Rte_IRead_SrlComOutput_Per1_SrlComHwTrqValid_Cnt_lgc(void)
 *   Float Rte_IRead_SrlComOutput_Per1_SrlComHwTrq_HwNm_f32(void)
 *   Float Rte_IRead_SrlComOutput_Per1_SupplyCurrent_Amp_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_SrlComOutput_Per1_Com_Elect_PWR_Consumpt_Cnt_u08(DT_Elect_PWR_Consumpt data)
 *   DT_Elect_PWR_Consumpt *Rte_IWriteRef_SrlComOutput_Per1_Com_Elect_PWR_Consumpt_Cnt_u08(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_EpasFailed_Cnt_lgc(DT_EpasFailed data)
 *   DT_EpasFailed *Rte_IWriteRef_SrlComOutput_Per1_Com_EpasFailed_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_Rel_Steer_Wheel_Ang_Cnt_u16(DT_Rel_Steer_Wheel_Ang data)
 *   DT_Rel_Steer_Wheel_Ang *Rte_IWriteRef_SrlComOutput_Per1_Com_Rel_Steer_Wheel_Ang_Cnt_u16(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_Rel_Steer_Wheel_Ang_Validity_Cnt_lgc(DT_Rel_Steer_Wheel_Ang_Validity data)
 *   DT_Rel_Steer_Wheel_Ang_Validity *Rte_IWriteRef_SrlComOutput_Per1_Com_Rel_Steer_Wheel_Ang_Validity_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_SAS_Angle_Cnt_u16(DT_SAS_Angle data)
 *   DT_SAS_Angle *Rte_IWriteRef_SrlComOutput_Per1_Com_SAS_Angle_Cnt_u16(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_SAS_CAL_Cnt_lgc(DT_SAS_CAL data)
 *   DT_SAS_CAL *Rte_IWriteRef_SrlComOutput_Per1_Com_SAS_CAL_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_SAS_CheckSum_Cnt_u08(DT_SAS_CheckSum data)
 *   DT_SAS_CheckSum *Rte_IWriteRef_SrlComOutput_Per1_Com_SAS_CheckSum_Cnt_u08(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_SAS_Init_Cnt_lgc(DT_SAS_Init data)
 *   DT_SAS_Init *Rte_IWriteRef_SrlComOutput_Per1_Com_SAS_Init_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_SAS_MsgCount_Cnt_u08(DT_SAS_MsgCount data)
 *   DT_SAS_MsgCount *Rte_IWriteRef_SrlComOutput_Per1_Com_SAS_MsgCount_Cnt_u08(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_SAS_OK_Cnt_lgc(DT_SAS_OK data)
 *   DT_SAS_OK *Rte_IWriteRef_SrlComOutput_Per1_Com_SAS_OK_Cnt_lgc(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_Steering_Torque_Cnt_u08(DT_Steering_Torque data)
 *   DT_Steering_Torque *Rte_IWriteRef_SrlComOutput_Per1_Com_Steering_Torque_Cnt_u08(void)
 *   void Rte_IWrite_SrlComOutput_Per1_Com_Steering_Torque_V_Cnt_lgc(DT_Steering_Torque_V data)
 *   DT_Steering_Torque_V *Rte_IWriteRef_SrlComOutput_Per1_Com_Steering_Torque_V_Cnt_lgc(void)
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
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_EpsEn_OP_GET(IoHwAb_BoolType *signal)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_EpsEn_E_NOT_OK
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_GetNTCFailed(NTCNumber NTC_Cnt_T_enum, Boolean *NTCFailed_Ptr_T_lgc)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_ComM_UserRequest_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_COMM_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *   Std_ReturnType Rte_Call_EpasFailed_GetIndicatorStatus(Dem_IndicatorStatusType *IndicatorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_IndicatorStatus_E_NOT_OK
 *   Std_ReturnType Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(UInt32 InitialTime, UInt16 *ElapsedTime)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_SystemTime_GetSystemTime_mS_u32(UInt32 *CurrentTime)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_SRLCOMOUTPUT_APPL_CODE) SrlComOutput_Per1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SrlComOutput_Per1
 *********************************************************************************************************************/
	
    VAR(float32, AUTOMATIC) RelHwPos_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) HandwheelAuthority_Uls_T_f32;
	VAR(float32, AUTOMATIC) HandwheelPosition_HwDeg_T_f32;
	VAR(uint16,  AUTOMATIC) SrlComHwPosStatus_Cnt_T_u16;
	VAR(boolean, AUTOMATIC) SrlComHwTrqValid_Cnt_T_lgc;
	VAR(float32, AUTOMATIC) SrlComHwTrq_HwNm_T_f32;
	VAR(float32, AUTOMATIC) SupplyCurrent_Amp_T_f32;
	VAR(boolean, AUTOMATIC) EpsEn_Cnt_T_lgc;
	VAR(uint8,   AUTOMATIC) BusOffStatus_Cnt_T_u08;
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) SystemState_Cnt_T_enum;
	VAR(boolean, AUTOMATIC) BusOff_Cnt_T_lgc;
	
    VAR(float32, AUTOMATIC) RelSteerWhlAg_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) SASAngle_HwDeg_T_f32;
	VAR(float32, AUTOMATIC) ElectPWRConsumpt_Amp_T_f32;
	VAR(float32, AUTOMATIC) SteeringTorque_HwNm_T_f32;
	VAR(uint16,  AUTOMATIC) ElapsedTime_mS_T_u16;
	VAR(PduInfoType, AUTOMATIC) PduInfo_Cnt_T_str;
	
	VAR(DT_Elect_PWR_Consumpt, AUTOMATIC) ElectPWRConsumpt_Cnt_T_u08;
	VAR(DT_EpasFailed,         AUTOMATIC) EpasFailed_Cnt_T_lgc;
	VAR(DT_SAS_Angle,          AUTOMATIC) SASAngle_Cnt_T_u16;
	VAR(DT_SAS_CAL,            AUTOMATIC) SASCAL_Cnt_T_lgc;
	VAR(DT_SAS_CheckSum,       AUTOMATIC) SASCheckSum_Cnt_T_u08;
	VAR(DT_SAS_Init,           AUTOMATIC) SASInit_Cnt_T_lgc;
	VAR(DT_SAS_OK,             AUTOMATIC) SASOK_Cnt_T_lgc;
	VAR(DT_SAS_MsgCount,       AUTOMATIC) SASMsgCount_Cnt_T_u08;
	VAR(DT_Steering_Torque,    AUTOMATIC) SteeringTorque_Cnt_T_u08;
	VAR(DT_Steering_Torque_V,  AUTOMATIC) SteeringTorqueV_Cnt_T_lgc;
	VAR(DT_Rel_Steer_Wheel_Ang,  AUTOMATIC) RelSteerWhlAg_Cnt_T_u16;
    VAR(DT_Rel_Steer_Wheel_Ang_Validity,  AUTOMATIC) RelSteerWhlAgVld_Cnt_T_u08;
	
    RelHwPos_HwDeg_T_f32 = Rte_IRead_SrlComOutput_Per1_RelHwPos_HwDeg_f32();
    CumMechMtrPosStatus_Cnt_M_u08 = Rte_IRead_SrlComOutput_Per1_CumMechMtrPosStatus_Cnt_u08();
	HandwheelAuthority_Uls_T_f32 = Rte_IRead_SrlComOutput_Per1_HandwheelAuthority_Uls_f32();
	HandwheelPosition_HwDeg_T_f32 = Rte_IRead_SrlComOutput_Per1_HandwheelPosition_HwDeg_f32();
	SrlComHwPosStatus_Cnt_T_u16 = Rte_IRead_SrlComOutput_Per1_SrlComHwPosStatus_Cnt_u16();
	SrlComHwTrqValid_Cnt_T_lgc = Rte_IRead_SrlComOutput_Per1_SrlComHwTrqValid_Cnt_lgc();
	SrlComHwTrq_HwNm_T_f32 = Rte_IRead_SrlComOutput_Per1_SrlComHwTrq_HwNm_f32();
	SupplyCurrent_Amp_T_f32 = Rte_IRead_SrlComOutput_Per1_SupplyCurrent_Amp_f32();
	Rte_Call_EpsEn_OP_GET(&EpsEn_Cnt_T_lgc);
	BusOffStatus_Cnt_T_u08 = Can_GetStatus(0u);
	SystemState_Cnt_T_enum = Rte_Mode_SystemState_Mode();
	Rte_Call_NxtrDiagMgr_GetNTCFailed(NTC_Num_BusOffCh1, &BusOff_Cnt_T_lgc);
	
	if( (SystemState_Cnt_T_enum == RTE_MODE_StaMd_Mode_OPERATE) ||
		(SystemState_Cnt_T_enum == RTE_MODE_StaMd_Mode_WARMINIT) ||
		(SystemState_Cnt_T_enum == RTE_MODE_StaMd_Mode_DISABLE) )
	{
		Rte_Call_EpasFailed_GetIndicatorStatus(&EpasFailedIndicator_Cnt_M_enum);
	}
	
	
	/* Tx Enable */
	if( EpsEn_Cnt_T_lgc != PrevEpsEn_Cnt_M_lgc )
	{
		if( EpsEn_Cnt_T_lgc == TRUE )
		{
			Com_IpduGroupStart(PduGrp_EPAS__CAN00_Tx, TRUE);
		}
		else
		{
			Com_IpduGroupStop(PduGrp_EPAS__CAN00_Tx);
		}
		
		PrevEpsEn_Cnt_M_lgc = EpsEn_Cnt_T_lgc;
	}
	
	
	
	/*** EPAS1 -- 0x39A ***/
	
	/* SAS_Angle */
	SASAngle_HwDeg_T_f32 = Limit_m(HandwheelPosition_HwDeg_T_f32, D_SASANGLELOLMT_HWDEG_F32, D_SASANGLEHILMT_HWDEG_F32);
	SASAngle_Cnt_T_u16 = (DT_SAS_Angle)((SASAngle_HwDeg_T_f32 + D_SASANGLEOFFSET_HWDEG_F32) / D_SASANGLESCALE_HWDEGPCNT_F32);
	
	/* SAS_CAL */
	if( HandwheelAuthority_Uls_T_f32 >= k_SASCALAuthorityThresh_Uls_f32 )
	{
		SASCAL_Cnt_T_lgc = TRUE;
	}
	else
	{
		SASCAL_Cnt_T_lgc = FALSE;
	}
	
	/* SAS_OK */
	if( SrlComHwPosStatus_Cnt_T_u16 != 0x5555u )
	{
		SASOK_Cnt_T_lgc = FALSE;
	}
	else
	{
		SASOK_Cnt_T_lgc = TRUE;
	}
	
	/* SAS_MsgCount */
	SASMsgCount_Cnt_T_u08 = 0u; /* populated in PDU callout */
	
	/* SAS_CheckSum */
	SASCheckSum_Cnt_T_u08 = 0u; /* populated in PDU callout */
	
	/* SAS_Init */
	SASInit_Cnt_T_lgc = SASCAL_Cnt_T_lgc;
	
	
	
	/*** EPAS2 -- 0x39E ***/
	
	/* Elect_PWR_Consumpt */
	ElectPWRConsumpt_Amp_T_f32 = Limit_m(SupplyCurrent_Amp_T_f32, D_ELECTPWRLOLMT_AMP_F32, D_ELECTPWRHILMT_AMP_F32);
	ElectPWRConsumpt_Cnt_T_u08 = (DT_Elect_PWR_Consumpt)(ElectPWRConsumpt_Amp_T_f32 / D_ELECTPWRSCALE_AMPPCNT_F32);
	
	/* EpasFailed */
	if( EpasFailedIndicator_Cnt_M_enum != DEM_INDICATOR_OFF )
	{
		EpasFailed_Cnt_T_lgc = TRUE;
	}
	else
	{
		EpasFailed_Cnt_T_lgc = FALSE;
	}
	
	/* Steering_Torque_V */
	if( SrlComHwTrqValid_Cnt_T_lgc == FALSE )
	{
		SteeringTorqueV_Cnt_T_lgc = TRUE;
	}
	else
	{
		SteeringTorqueV_Cnt_T_lgc = FALSE;
	}
	
	/* Steering_Torque */
	SteeringTorque_HwNm_T_f32 = Limit_m(SrlComHwTrq_HwNm_T_f32, D_STEERINGTORQUELOLMT_HWNM_F32, D_STEERINGTORQUEHILMT_HWNM_F32);
	SteeringTorque_Cnt_T_u08 = (DT_Steering_Torque)((SteeringTorque_HwNm_T_f32 + D_STEERINGTORQUEOFFSET_HWNM_F32) / D_STEERINGTORQUESCALE_HWNMPCNT_F32);
	
	
	
	/*** NMmEPAS -- 0x707 ***/
	
	if( NMFirstMessageSent_Cnt_M_lgc == FALSE )
	{
		NMSendMessage_Cnt_M_lgc = TRUE;
	}
	else
	{
		Rte_Call_SystemTime_DtrmnElapsedTime_mS_u16(NMTimer_mS_M_u32, &ElapsedTime_mS_T_u16);
		
		if( ElapsedTime_mS_T_u16 >= k_SATimer_mS_u16 )
		{
			NMSendMessage_Cnt_M_lgc = TRUE;
		}
	}
	
	if( NMBusOffSinceLastTx_Cnt_M_lgc == FALSE )
	{
		if( BusOff_Cnt_T_lgc == TRUE )
		{
			NMBusOffSinceLastTx_Cnt_M_lgc = TRUE;
			NMErrorSinceLastTx_Cnt_M_lgc = FALSE;
		}
		else
		{
			if( (BusOffStatus_Cnt_T_u08 & (CAN_STATUS_WARNING | CAN_STATUS_PASSIVE)) != 0u )
			{
				NMErrorSinceLastTx_Cnt_M_lgc = TRUE;
			}
		}
	}
	
	if( (NMSendMessage_Cnt_M_lgc == TRUE) &&
		(EpsEn_Cnt_T_lgc == TRUE) )
	{
		
		if( NMFirstMessageSent_Cnt_M_lgc == FALSE )
		{
			NMMessage_Cnt_M_u08[1u] = 0x04u;
		}
		else if( NMBusOffSinceLastTx_Cnt_M_lgc == TRUE )
		{
			NMMessage_Cnt_M_u08[1u] = 0x86u;
		}
		else if( NMErrorSinceLastTx_Cnt_M_lgc == TRUE )
		{
			NMMessage_Cnt_M_u08[1u] = 0x46u;
		}
		else
		{
			NMMessage_Cnt_M_u08[1u] = 0x06u;
		}
		
		PduInfo_Cnt_T_str.SduDataPtr = (SduDataPtrType)(&NMMessage_Cnt_M_u08);
		PduInfo_Cnt_T_str.SduLength = 8u;
		
		if( E_OK == CanIf_Transmit(2u, &PduInfo_Cnt_T_str) )
		{
			Rte_Call_SystemTime_GetSystemTime_mS_u32(&NMTimer_mS_M_u32);
		}
	}
    
    if ( FALSE != k_BroadcastRelHwPos_Cnt_lgc)
    {
        if ( 100u == CumMechMtrPosStatus_Cnt_M_u08)
        {
            RelSteerWhlAgVld_Cnt_T_u08 = 1u;         
        }
        else
        {
            RelSteerWhlAgVld_Cnt_T_u08 = 0u;
        }
        if ( FALSE == RelHwPosInitSet_Cnt_M_lgc )
        {
            RelHwPosInit_HwDeg_M_f32 = RelHwPos_HwDeg_T_f32;
            RelSteerWhlAg_HwDeg_T_f32 = 0.0f;
        }
        else
        {
            RelSteerWhlAg_HwDeg_T_f32 = RelHwPos_HwDeg_T_f32 - RelHwPosInit_HwDeg_M_f32;            
        }
        RelSteerWhlAg_HwDeg_T_f32 = Limit_m(RelSteerWhlAg_HwDeg_T_f32, D_RELSTEERWHLANGLOLMT_HWDEG_F32, D_RELSTEERWHLANGHILMT_HWDEG_F32);
        RelSteerWhlAg_Cnt_T_u16 = (DT_Rel_Steer_Wheel_Ang)((RelSteerWhlAg_HwDeg_T_f32 + D_RELSTEERWHLANGOFFSET_HWDEG_F32) / D_RELSTEERWHLANGSCALE_HWDEG_F32);	
	
    }
    else
    {
        RelSteerWhlAg_Cnt_T_u16 = 0u;
        RelSteerWhlAgVld_Cnt_T_u08 = 0u;
    }
    
	Rte_IWrite_SrlComOutput_Per1_Com_Rel_Steer_Wheel_Ang_Cnt_u16(RelSteerWhlAg_Cnt_T_u16);
	Rte_IWrite_SrlComOutput_Per1_Com_Rel_Steer_Wheel_Ang_Validity_Cnt_lgc(RelSteerWhlAgVld_Cnt_T_u08);
	Rte_IWrite_SrlComOutput_Per1_Com_Elect_PWR_Consumpt_Cnt_u08(ElectPWRConsumpt_Cnt_T_u08);
	Rte_IWrite_SrlComOutput_Per1_Com_EpasFailed_Cnt_lgc(EpasFailed_Cnt_T_lgc);
	Rte_IWrite_SrlComOutput_Per1_Com_SAS_Angle_Cnt_u16(SASAngle_Cnt_T_u16);
	Rte_IWrite_SrlComOutput_Per1_Com_SAS_CAL_Cnt_lgc(SASCAL_Cnt_T_lgc);
	Rte_IWrite_SrlComOutput_Per1_Com_SAS_CheckSum_Cnt_u08(SASCheckSum_Cnt_T_u08);
	Rte_IWrite_SrlComOutput_Per1_Com_SAS_Init_Cnt_lgc(SASInit_Cnt_T_lgc);
	Rte_IWrite_SrlComOutput_Per1_Com_SAS_OK_Cnt_lgc(SASOK_Cnt_T_lgc);
	Rte_IWrite_SrlComOutput_Per1_Com_SAS_MsgCount_Cnt_u08(SASMsgCount_Cnt_T_u08);
	Rte_IWrite_SrlComOutput_Per1_Com_Steering_Torque_Cnt_u08(SteeringTorque_Cnt_T_u08);
	Rte_IWrite_SrlComOutput_Per1_Com_Steering_Torque_V_Cnt_lgc(SteeringTorqueV_Cnt_T_lgc);
	
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_SRLCOMOUTPUT_APPL_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


FUNC(boolean, COM_APPL_CODE) Appl_COMCout_Pdu_EPAS1__CAN00(PduIdType ComTxPduId,
														   P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SduPtr)
{
	VAR(uint8, AUTOMATIC) TempResult_Cnt_T_u08;
	VAR(uint8, AUTOMATIC) SASCheckSum_Cnt_T_u08;
	
	/* SAS_MsgCount */
	SASMsgCount_Cnt_M_u08 = (SASMsgCount_Cnt_M_u08 + 1u) % 16u;
	
	/* SAS_CheckSum */
	TempResult_Cnt_T_u08 = SduPtr[0] ^ SduPtr[1] ^ SduPtr[2] ^ SduPtr[3];
	SASCheckSum_Cnt_T_u08 = ((TempResult_Cnt_T_u08 >> 4) & 0x0F) ^ (TempResult_Cnt_T_u08 & 0x0F) ^ SASMsgCount_Cnt_M_u08;
	SduPtr[4] = ((SASMsgCount_Cnt_M_u08 << 4) & 0xF0) | (SASCheckSum_Cnt_T_u08 & 0x0F);
	
	return TRUE;
}


FUNC(void, CANIF_APPL_CODE) SrlComOutput_RxNM(PduIdType CanRxPduId, P2CONST(uint8, AUTOMATIC, CANIF_APPL_VAR) CanSduPtr)
{
	if( (CanSduPtr[1u] & 3u) == 2u )
	{
		NMSendMessage_Cnt_M_lgc = TRUE;
	}
}


FUNC(void, CANIF_APPL_CODE) SrlComOutput_TxNM(PduIdType CanTxPduId)
{
	if( NMFirstMessageSent_Cnt_M_lgc == FALSE )
	{
		NMFirstMessageSent_Cnt_M_lgc = TRUE;
	}
	else
	{
		if( NMBusOffSinceLastTx_Cnt_M_lgc == TRUE )
		{
			NMBusOffSinceLastTx_Cnt_M_lgc = FALSE;
		}
		
		if( NMErrorSinceLastTx_Cnt_M_lgc == TRUE )
		{
			NMErrorSinceLastTx_Cnt_M_lgc = FALSE;
		}
	}
	
	NMSendMessage_Cnt_M_lgc = FALSE;
	Rte_Call_SystemTime_GetSystemTime_mS_u32(&NMTimer_mS_M_u32);
}

FUNC(void, COM_APPL_CODE) Appl_COMCbkTAck_Com_Rel_Steer_Wheel_Ang__EPAS2__CAN00(void)
{    
    if (100u == CumMechMtrPosStatus_Cnt_M_u08)
    {
        RelHwPosInitSet_Cnt_M_lgc = TRUE;
    }    
    
    return;
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
