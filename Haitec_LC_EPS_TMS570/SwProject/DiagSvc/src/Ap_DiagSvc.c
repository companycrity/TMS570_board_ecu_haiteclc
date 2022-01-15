/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_DiagSvc.c
 *     Workspace:  C:/SynergyProjects/Haitec_LC_EPS_TMS570-nzx5jd/Haitec_LC_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *     SW-C Type:  Ap_DiagSvc
 *  Generated at:  Thu Sep 10 09:31:44 2015
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  C-Code implementation template for SW-C <Ap_DiagSvc>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/* Version Control:
 * %version:          EA3#31 %
 * %derived_by:       nzx5jd %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev      Author   Change Description                                                               SCR #
 * --------   -------  -------  ------------------------------------------------------------------------------  -------
 * 07/09/13    1       OT       Initial Version
 * 08/02/13    2       OT       Implemented basic CMS functionality
 * 08/10/13    3       OT       Implemented customer services
 * 08/12/13    4       OT       Implemented customer DIDs
 * 08/13/13    5       OT       Properly implemented programming session transition
 * 08/15/13    6       OT       Corrected tuning set implementation
 * 08/19/13    7       OT       Implemented failure criteria for NTC 1F5
 * 08/28/13    8       OT       Implemented basic security access functionality
 * 09/05/13    9       OT       Implemented latest manufacturing services
 * 09/23/13   10       OT       Added FDB4
 * 10/10/13   11       OT       Corrected F180 implementation
 * 11/15/13   12       OT       Corrected F180 implementation again
 * 01/09/14   13       OT       Migrated CallFblStart() to trusted function, added MemMap statements
 * 05/06/14   14       OT       Added length check on service $11
 * 05/21/14   15       OT       Changed DID F196 to 0100
 * 05/28/14   16       OT       Implemented DIDs F18A and F193
 * 08/30/14   17       OT       Updates for DSR 001F
 * 10/20/14   18       MS       Added FDB7 service handler
 * 10/24/14   19       MS       Added support for F0FF service
 * 11/05/14   20       OT       Anomaly fix for service 85
 * 12/15/14   21       OT       Updates for CMS v07B
 * 12/16/14   22       OT       Updates for VehDyn stored last position
 * 02/12/15   23       OT       Added FD17 and fixed ASCII filler byte                                           13028
 * 03/11/15   24       OT       Updates to F194 and F195 per DSR 001I                                            13108
 * 03/26/15   25       OT       Anomaly fixes for F009 and FEE0
 * 04/17/15   26       OT       Support SPRMIB for services 11 and 85                                            13253
 * 04/23/15   27       OT       Implemented service 28 manually                                                  13270
 * 08/28/15   28       OT       Implemented FE00 I/O control DID                                              EA3#2743
 * 09/10/15   30       OT       Corrected Dem calls                                                           EA3#1999
 * 10/16/15   31       OT       Corrected Dem calls again                                                     EA3#3944
 */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Data Types:
 ===========
  NvM_DestPtr
    DataPtr Type to be used by WriteBlock, ReadBlock and RestoreBlockDefaults operations. 	This type is used for all NVRAM blocks


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_DiagSvc.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "CalConstants.h"
#include "GlobalMacro.h"
#include "Dcm.h"
#include "Vmm_Dcm.h"
#include "Dem.h"
#include "Mcu.h"
#include "NtWrap.h"
#include "Ap_DfltConfigData.h"
#define NVM_SKIP_API_DECLARATIONS STD_ON
#include "EPS_DiagSrvcs_SrvcLUTbl.h"


#define D_ASCIIFILLER_CNT_U08	0x20u


#define DIAGSVC_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" /* PRQA S 5087 */
STATIC VAR(boolean, AP_DIAGSVC_VAR) HardReset_Cnt_M_lgc;
STATIC VAR(boolean, AP_DIAGSVC_VAR) SoftReset_Cnt_M_lgc;
#define DIAGSVC_STOP_SEC_VAR_CLEARED_BOOLEAN
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
 * Double: Real in interval [-DBL_MAX...DBL_MAX] with double precision including NaN (standard type)
 * Float: Real in interval [-FLT_MAX...FLT_MAX] with single precision (standard type)
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt32: Integer in interval [-2147483648...2147483647] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 * Enumeration Types:
 * ==================
 * Dcm_ConfirmationStatusType: Enumeration of integer in interval [0...3] with enumerators
 *   DCM_RES_POS_OK (0U)
 *   DCM_RES_POS_NOT_OK (1U)
 *   DCM_RES_NEG_OK (2U)
 *   DCM_RES_NEG_NOT_OK (3U)
 * Dcm_NegativeResponseCodeType: Enumeration of integer in interval [0...255] with enumerators
 *   DCM_E_GENERALREJECT (16U)
 *   DCM_E_SERVICENOTSUPPORTED (17U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTED (18U)
 *   DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT (19U)
 *   DCM_E_RESPONSE_TOO_LONG (20U)
 *   DCM_E_BUSYREPEATREQUEST (33U)
 *   DCM_E_CONDITIONSNOTCORRECT (34U)
 *   DCM_E_REQUESTSEQUENCEERROR (36U)
 *   DCM_E_REQUESTOUTOFRANGE (49U)
 *   DCM_E_SECURITYACCESSDENIED (51U)
 *   DCM_E_INVALIDKEY (53U)
 *   DCM_E_EXCEEDNUMBEROFATTEMPTS (54U)
 *   DCM_E_REQUIREDTIMEDELAYNOTEXPIRED (55U)
 *   DCM_E_UPLOADDOWNLOADNOTACCEPTED (112U)
 *   DCM_E_TRANSFERDATASUSPENDED (113U)
 *   DCM_E_GENERALPROGRAMMINGFAILURE (114U)
 *   DCM_E_WRONGBLOCKSEQUENCECOUNTER (115U)
 *   DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING (120U)
 *   DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION (126U)
 *   DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION (127U)
 *   DCM_E_RPMTOOHIGH (129U)
 *   DCM_E_RPMTOOLOW (130U)
 *   DCM_E_ENGINEISRUNNING (131U)
 *   DCM_E_ENGINEISNOTRUNNING (132U)
 *   DCM_E_ENGINERUNTIMETOOLOW (133U)
 *   DCM_E_TEMPERATURETOOHIGH (134U)
 *   DCM_E_TEMPERATURETOOLOW (135U)
 *   DCM_E_VEHICLESPEEDTOOHIGH (136U)
 *   DCM_E_VEHICLESPEEDTOOLOW (137U)
 *   DCM_E_THROTTLE_PEDALTOOHIGH (138U)
 *   DCM_E_THROTTLE_PEDALTOOLOW (139U)
 *   DCM_E_TRANSMISSIONRANGENOTINNEUTRAL (140U)
 *   DCM_E_TRANSMISSIONRANGENOTINGEAR (141U)
 *   DCM_E_BRAKESWITCH_NOTCLOSED (143U)
 *   DCM_E_SHIFTERLEVERNOTINPARK (144U)
 *   DCM_E_TORQUECONVERTERCLUTCHLOCKED (145U)
 *   DCM_E_VOLTAGETOOHIGH (146U)
 *   DCM_E_VOLTAGETOOLOW (147U)
 * Dcm_SecLevelType: Enumeration of integer in interval [0...255] with enumerators
 *   DCM_SEC_LEV_LOCKED (0U)
 *   DCM_SEC_LEV_L1 (1U)
 *   DCM_SEC_LEV_ALL (255U)
 * Dcm_SesCtrlType: Enumeration of integer in interval [1...255] with enumerators
 *   DCM_DEFAULT_SESSION (1U)
 *   DCM_PROGRAMMING_SESSION (2U)
 *   DCM_EXTENDED_DIAGNOSTIC_SESSION (3U)
 *   DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION (4U)
 *   NEXTEER (126U)
 *   DCM_ALL_SESSION_LEVEL (255U)
 * ManufModeType: Enumeration of integer in interval [0...2] with enumerators
 *   ProductionMode (0U)
 *   ManufacturingMode (1U)
 *   EngineeringMode (2U)
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
 * NvM_RequestResultType: Enumeration of integer in interval [0...5] with enumerators
 *   NVM_REQ_OK (0U)
 *   NVM_REQ_NOT_OK (1U)
 *   NVM_REQ_PENDING (2U)
 *   NVM_REQ_INTEGRITY_FAILED (3U)
 *   NVM_REQ_BLOCK_SKIPPED (4U)
 *   NVM_REQ_NV_INVALIDATED (5U)
 * NxtrDiagMgrStatus: Enumeration of integer in interval [0...255] with enumerators
 *   NTC_STATUS_PASSED (0U)
 *   NTC_STATUS_FAILED (1U)
 *   NTC_STATUS_PREPASSED (2U)
 *   NTC_STATUS_PREFAILED (3U)
 *
 * Array Types:
 * ============
 * Dcm_0Byte_Type: Array with 1 element(s) of type UInt8
 * Dcm_10Byte_Type: Array with 10 element(s) of type UInt8
 * Dcm_12Byte_Type: Array with 12 element(s) of type UInt8
 * Dcm_16Byte_Type: Array with 16 element(s) of type UInt8
 * Dcm_176Byte_Type: Array with 176 element(s) of type UInt8
 * Dcm_18Byte_Type: Array with 18 element(s) of type UInt8
 * Dcm_1Byte_Type: Array with 1 element(s) of type UInt8
 * Dcm_256Byte_Type: Array with 256 element(s) of type UInt8
 * Dcm_25Byte_Type: Array with 25 element(s) of type UInt8
 * Dcm_28Byte_Type: Array with 28 element(s) of type UInt8
 * Dcm_2Byte_Type: Array with 2 element(s) of type UInt8
 * Dcm_322Byte_Type: Array with 322 element(s) of type UInt8
 * Dcm_3Byte_Type: Array with 3 element(s) of type UInt8
 * Dcm_4Byte_Type: Array with 4 element(s) of type UInt8
 * Dcm_5Byte_Type: Array with 5 element(s) of type UInt8
 * Dcm_64Byte_Type: Array with 64 element(s) of type UInt8
 * Dcm_6Byte_Type: Array with 6 element(s) of type UInt8
 * Dcm_75Byte_Type: Array with 75 element(s) of type UInt8
 * Dcm_7Byte_Type: Array with 7 element(s) of type UInt8
 * Dcm_8Byte_Type: Array with 8 element(s) of type UInt8
 * Dcm_SecAccess_1_DataRecType: Array with 1 element(s) of type UInt8
 * Dcm_SecAccess_1_KeyType: Array with 3 element(s) of type UInt8
 * Dcm_SecAccess_1_SeedType: Array with 3 element(s) of type UInt8
 * NvM_DestPtr: Array with 65535 element(s) of type UInt8
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


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   UInt16 *Rte_Pim_TuningSetSelectData(void)
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   UInt8 *Rte_Pim_SparePartNumberData(void)
#else
 *   Dcm_10Byte_Type *Rte_Pim_SparePartNumberData(void)
#endif
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   UInt8 *Rte_Pim_SupplierIdentifierData(void)
#else
 *   Dcm_10Byte_Type *Rte_Pim_SupplierIdentifierData(void)
#endif
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_DIAGSVC_APPL_CODE
#include "MemMap.h"

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_Init1
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
 *   ManufModeType Rte_IRead_DiagSvc_Init1_MEC_Cnt_enum(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_DiagSvc_Init1_DesiredTunSet_Cnt_u16(UInt16 data)
 *   UInt16 *Rte_IWriteRef_DiagSvc_Init1_DesiredTunSet_Cnt_u16(void)
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
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_TuningSetSelect_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_Init1(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DiagSvc_Init1
 *********************************************************************************************************************/
	
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) TuningSet_Cnt_T_u16;
	
	MEC_Cnt_T_enum = Rte_IRead_DiagSvc_Init1_MEC_Cnt_enum();
	
	Rte_Call_TuningSetSelect_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum != NVM_REQ_OK )
	{
		TuningSet_Cnt_T_u16 = 0u;
		*Rte_Pim_TuningSetSelectData() = 0u;
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_FAILED);
		}
	}
	else
	{
		TuningSet_Cnt_T_u16 = *Rte_Pim_TuningSetSelectData();
		Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_PASSED);
	}
	
	Rte_IWrite_DiagSvc_Init1_DesiredTunSet_Cnt_u16(TuningSet_Cnt_T_u16);
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_SCom_GetTuningSet
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetTuningSet> of PortPrototype <DiagSvc_SCom>
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
 *   Std_ReturnType Rte_Call_TuningSetSelect_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void DiagSvc_SCom_GetTuningSet(UInt8 *TuningSet_Cnt_T_u08)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_GetTuningSet(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) TuningSet_Cnt_T_u08)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DiagSvc_SCom_GetTuningSet
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	
	Rte_Call_TuningSetSelect_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum != NVM_REQ_OK )
	{
		*TuningSet_Cnt_T_u08 = 0u;
	}
	else
	{
		*TuningSet_Cnt_T_u08 = (uint8)(*Rte_Pim_TuningSetSelectData() + 1u);
	}
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DiagSvc_SCom_SetTuningSet
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <SetTuningSet> of PortPrototype <DiagSvc_SCom>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_TuningSetSelect_InvalidateNvBlock(void)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DiagSvc_SCom_SetTuningSet(UInt8 TuningSet_Cnt_T_u08)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DiagSvc_SCom_E_OUTOFRANGE
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DiagSvc_SCom_SetTuningSet(UInt8 TuningSet_Cnt_T_u08)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DiagSvc_SCom_SetTuningSet (returns application error)
 *********************************************************************************************************************/
	
	VAR(Std_ReturnType, AUTOMATIC) RetVal_Cnt_T_enum;
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum);
	
	if( TuningSet_Cnt_T_u08 > D_NUMOFTUNSETS_CNT_U16 )
	{
		RetVal_Cnt_T_enum = RTE_E_DiagSvc_SCom_E_OUTOFRANGE;
	}
	else if( TuningSet_Cnt_T_u08 == 0u )
	{
		*Rte_Pim_TuningSetSelectData() = 0u;
		Rte_Call_TuningSetSelect_InvalidateNvBlock();
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_FAILED);
		}
		
		RetVal_Cnt_T_enum = RTE_E_OK;
	}
	else
	{
		*Rte_Pim_TuningSetSelectData() = TuningSet_Cnt_T_u08 - 1u;
		Rte_Call_TuningSetSelect_WriteBlock(NULL_PTR);
		Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_PASSED);
		
		RetVal_Cnt_T_enum = RTE_E_OK;
	}
	
	return RetVal_Cnt_T_enum;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0100_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0x0100>
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
 *   Std_ReturnType Rte_Call_TuningSetSelect_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0100_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0x0100_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_NOT_OK
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0100_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	
	Rte_Call_TuningSetSelect_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum != NVM_REQ_OK )
	{
		(*data)[0] = 0u;
	}
	else
	{
		(*data)[0] = (uint8)(*Rte_Pim_TuningSetSelectData() + 1u);
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0x0100_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0x0100>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_NxtrDiagMgr_SetNTCStatus(NTCNumber NTC_Cnt_T_enum, UInt8 Param_Cnt_T_u08, NxtrDiagMgrStatus Status_Cnt_T_enum)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NxtrDiagMgr_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_TuningSetSelect_InvalidateNvBlock(void)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_TuningSetSelect_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0x0100_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0x0100_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0x0100_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0x0100_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(ManufModeType, AUTOMATIC) MEC_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) TuningSet_Cnt_T_u16;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum);
	
	TuningSet_Cnt_T_u16 = (uint16)((*data)[0]);
	
	if( TuningSet_Cnt_T_u16 > D_NUMOFTUNSETS_CNT_U16 )
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
	}
	else if( TuningSet_Cnt_T_u16 == 0u )
	{
		*Rte_Pim_TuningSetSelectData() = 0u;
		Rte_Call_TuningSetSelect_InvalidateNvBlock();
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_FAILED);
		}
	}
	else
	{
		*Rte_Pim_TuningSetSelectData() = TuningSet_Cnt_T_u16 - 1u;
		Rte_Call_TuningSetSelect_WriteBlock(NULL_PTR);
		Rte_Call_NxtrDiagMgr_SetNTCStatus(NTC_Num_EOLVehTunNtPerf, 1u, NTC_STATUS_PASSED);
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf180_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf180>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf180_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf180_ReadData(Dcm_25Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf180_E_NOT_OK
 *   RTE_E_DidServices_0xf180_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf180_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf180_ReadData(P2VAR(Dcm_25Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf180_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) i;
	
	(*data)[0] = 1u;
	
	for( i = 1u; (i < TableSize_m(*data)) && ((&Lnk_BootRelNum_Addr)[i-1] > 0u); i++ )
	{
		(*data)[i] = (&Lnk_BootRelNum_Addr)[i-1];
	}
	
	for( ; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = D_ASCIIFILLER_CNT_U08;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf187_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf187>
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
 *   Std_ReturnType Rte_Call_SparePartNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf187_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf187_ReadData(Dcm_10Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf187_E_NOT_OK
 *   RTE_E_DidServices_0xf187_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf187_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	
	Rte_Call_SparePartNumber_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*Rte_Pim_SparePartNumberData())[i];
		}
	}
	else
	{
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf187_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xf187>
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
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_SparePartNumber_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_SparePartNumber_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf187_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xf187_WriteData(Dcm_10Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf187_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf187_WriteData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf187_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) i;
	
	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*Rte_Pim_SparePartNumberData())[i] = (*data)[i];
	}
	
	Rte_Call_SparePartNumber_WriteBlock(NULL_PTR);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf18a_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf18a>
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
 *   Std_ReturnType Rte_Call_SupplierIdentifier_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf18a_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf18a_ReadData(Dcm_10Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf18a_E_NOT_OK
 *   RTE_E_DidServices_0xf18a_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18a_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf18a_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	
	Rte_Call_SupplierIdentifier_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = (*Rte_Pim_SupplierIdentifierData())[i];
		}
		
	}
	else
	{
		
		(*data)[0] = 'B';
		(*data)[1] = '5';
		(*data)[2] = '1';
		(*data)[3] = '5';
		
		for( i = 4u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
		
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf18a_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xf18a>
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
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_SupplierIdentifier_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_SupplierIdentifier_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvM_AC3_SRBS_Srv_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf18a_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xf18a_WriteData(Dcm_10Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf18a_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18a_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18a_WriteData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf18a_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) i;
	
	for( i = 0u; i < TableSize_m(*data); i++ )
	{
		(*Rte_Pim_SupplierIdentifierData())[i] = (*data)[i];
	}
	
	Rte_Call_SupplierIdentifier_WriteBlock(NULL_PTR);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf18c_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf18c>
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
 *   Std_ReturnType Rte_Call_ECUSerialNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf18c_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf18c_ReadData(Dcm_16Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf18c_E_NOT_OK
 *   RTE_E_DidServices_0xf18c_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf18c_ReadData(P2VAR(Dcm_16Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf18c_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint32, AUTOMATIC) EcuSrlNum_Cnt_T_u32;
	VAR(uint16, AUTOMATIC) i;
	
	Rte_Call_ECUSerialNumber_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		
		EcuSrlNum_Cnt_T_u32 = (((uint32)Nvm_EcuSrlNum_Cnt_u8[0]) << 24u) |
							  (((uint32)Nvm_EcuSrlNum_Cnt_u8[1]) << 16u) |
							  (((uint32)Nvm_EcuSrlNum_Cnt_u8[2]) <<  8u) |
							  (((uint32)Nvm_EcuSrlNum_Cnt_u8[3]) <<  0u);
		
		for( i = 0u; (i < 10u) && (i < TableSize_m(*data)); i++ )
		{
			(*data)[i] = (uint8)((((uint32)(EcuSrlNum_Cnt_T_u32 / ((uint32)powf(10, 9-i)))) % 10u) + 0x30);
		}
		
		for( ; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
		
	}
	else
	{
		
		for( i = 0u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
		
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf191_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf191>
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
 *   Std_ReturnType Rte_Call_ECUHardwareNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf191_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf191_ReadData(Dcm_16Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf191_E_NOT_OK
 *   RTE_E_DidServices_0xf191_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf191_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf191_ReadData(P2VAR(Dcm_16Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf191_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	
	Rte_Call_ECUHardwareNumber_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		
		for( i = 0u; i < 8u; i++ )
		{
			(*data)[i] = Nvm_EcuHwPn_Cnt_u8[i];
		}
		
		for( ; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
		
	}
	else
	{
		
		(*data)[0] = '0';
		(*data)[1] = '0';
		(*data)[2] = '0';
		(*data)[3] = '0';
		(*data)[4] = '0';
		(*data)[5] = '0';
		(*data)[6] = '0';
		(*data)[7] = '0';
		
		for( i = 8u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
		
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf193_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf193>
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
 *   Std_ReturnType Rte_Call_ECUHardwareNumber_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf193_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf193_ReadData(Dcm_10Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf193_E_NOT_OK
 *   RTE_E_DidServices_0xf193_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf193_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf193_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf193_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(NvM_RequestResultType, AUTOMATIC) ErrorStatus_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	
	Rte_Call_ECUHardwareNumber_GetErrorStatus(&ErrorStatus_Cnt_T_enum);
	
	if( ErrorStatus_Cnt_T_enum == NVM_REQ_OK )
	{
		
		for( i = 0u; i < 3u; i++ )
		{
			(*data)[i] = Nvm_EcuHwPn_Cnt_u8[i+9u];
		}
		
		for( ; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
		
	}
	else
	{
		
		(*data)[0] = '0';
		(*data)[1] = '0';
		(*data)[2] = '0';
		
		for( i = 3u; i < TableSize_m(*data); i++ )
		{
			(*data)[i] = D_ASCIIFILLER_CNT_U08;
		}
		
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf194_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf194>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf194_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf194_ReadData(Dcm_10Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf194_E_NOT_OK
 *   RTE_E_DidServices_0xf194_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf194_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf194_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf194_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) i;
	
	for( i = 0u; (i < TableSize_m(*data)) && (k_SWRelNum_Cnt_u8[i + 10u] > 0u); i++ )
	{
		(*data)[i] = k_SWRelNum_Cnt_u8[i + 10u];
	}
	
	for( ; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = D_ASCIIFILLER_CNT_U08;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xf195_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xf195>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xf195_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xf195_ReadData(Dcm_10Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xf195_E_NOT_OK
 *   RTE_E_DidServices_0xf195_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf195_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xf195_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xf195_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) i;
	
	for( i = 0u; (i < TableSize_m(*data)) && (k_CalRelNum_Cnt_u8[i] > 0u); i++ )
	{
		(*data)[i] = k_CalRelNum_Cnt_u8[i];
	}
	
	for( ; i < TableSize_m(*data); i++ )
	{
		(*data)[i] = D_ASCIIFILLER_CNT_U08;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd01_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd01>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd01_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd01_ReadData(Dcm_322Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd01_E_NOT_OK
 *   RTE_E_DidServices_0xfd01_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd01_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd01_ReadData(P2VAR(Dcm_322Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd01_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD01u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd01_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd02_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd02>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd02_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd02_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd02_E_NOT_OK
 *   RTE_E_DidServices_0xfd02_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd02_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD02u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd02_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd02_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd02>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd02_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd02_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd02_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd02_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd02_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD02u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd07_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd07>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd07_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd07_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd07_E_NOT_OK
 *   RTE_E_DidServices_0xfd07_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd07_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD07u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd07_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd07_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd07>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd07_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd07_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd07_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd07_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd07_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD07u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd0d_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd0d>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd0d_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd0d_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0d_E_NOT_OK
 *   RTE_E_DidServices_0xfd0d_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd0d_ReadData (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_DidServices_0xfd0d_E_NOT_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd0d_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReturnControlToECU> of PortPrototype <DidServices_0xfd0d>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd0d_ReturnControlToECU(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd0d_ReturnControlToECU(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_2Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0d_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd0d_ReturnControlToECU (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD0Du, 0u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd0d_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ShortTermAdjustment> of PortPrototype <DidServices_0xfd0d>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd0d_ShortTermAdjustment(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd0d_ShortTermAdjustment(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_2Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0d_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0d_ShortTermAdjustment(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd0d_ShortTermAdjustment (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) i;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD0Du, 3u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	if( *ErrorCode > 0u )
	{
		for( i = 0u; i < RequestDataLength; i++ )
		{
			*ResponseData[i] = *RequestData[i];
		}
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd0e_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd0e>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd0e_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd0e_ReadData(Dcm_8Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0e_E_NOT_OK
 *   RTE_E_DidServices_0xfd0e_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd0e_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd0e_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD0Eu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd0e_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd10_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd10>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd10_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd10_ReadData(Dcm_10Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd10_E_NOT_OK
 *   RTE_E_DidServices_0xfd10_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd10_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd10_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd10_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD10u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd10_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd11_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd11>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd11_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd11_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd11_E_NOT_OK
 *   RTE_E_DidServices_0xfd11_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd11_ReadData (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_DidServices_0xfd11_E_NOT_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd11_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReturnControlToECU> of PortPrototype <DidServices_0xfd11>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd11_ReturnControlToECU(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd11_ReturnControlToECU(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_2Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd11_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd11_ReturnControlToECU (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD11u, 0u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd11_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ShortTermAdjustment> of PortPrototype <DidServices_0xfd11>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd11_ShortTermAdjustment(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd11_ShortTermAdjustment(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_2Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd11_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd11_ShortTermAdjustment(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd11_ShortTermAdjustment (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(uint16, AUTOMATIC) i;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD11u, 3u, (uint8*)RequestData, RequestDataLength, &RespLen_Cnt_T_u16);
	
	if( *ErrorCode > 0u )
	{
		for( i = 0u; i < RequestDataLength; i++ )
		{
			*ResponseData[i] = *RequestData[i];
		}
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd12_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd12>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd12_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd12_ReadData(Dcm_28Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd12_E_NOT_OK
 *   RTE_E_DidServices_0xfd12_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_ReadData(P2VAR(Dcm_28Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd12_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD12u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd12_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd12_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd12>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd12_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd12_WriteData(Dcm_28Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd12_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd12_WriteData(P2VAR(Dcm_28Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd12_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD12u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd13_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd13>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd13_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd13_ReadData(Dcm_75Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd13_E_NOT_OK
 *   RTE_E_DidServices_0xfd13_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd13_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd13_ReadData(P2VAR(Dcm_75Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd13_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD13u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd19_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd14_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd14>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd14_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd14_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd14_E_NOT_OK
 *   RTE_E_DidServices_0xfd14_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd14_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd14_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd14_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD14u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd14_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd17_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd17>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd17_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd17_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd17_E_NOT_OK
 *   RTE_E_DidServices_0xfd17_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd17_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd17_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd17_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD17u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd17_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd19_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd19>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd19_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd19_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd19_E_NOT_OK
 *   RTE_E_DidServices_0xfd19_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd19_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD19u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd19_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd19_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd19>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd19_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd19_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd19_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd19_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd19_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD19u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1a_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1a>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1a_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1a_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1a_E_NOT_OK
 *   RTE_E_DidServices_0xfd1a_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1a_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1a_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1a_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Au, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1a_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1b_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1b>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1b_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1b_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1b_E_NOT_OK
 *   RTE_E_DidServices_0xfd1b_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1b_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Bu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1b_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1b_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd1b>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1b_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd1b_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1b_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1b_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1b_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD1Bu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1c_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1c>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1c_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1c_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1c_E_NOT_OK
 *   RTE_E_DidServices_0xfd1c_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1c_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1c_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1c_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Cu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1c_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1e_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd1e>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1e_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd1e_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1e_E_NOT_OK
 *   RTE_E_DidServices_0xfd1e_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1e_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD1Eu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd1e_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd1e_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd1e>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd1e_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd1e_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd1e_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd1e_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd1e_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD1Eu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd20_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd20>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd20_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd20_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd20_E_NOT_OK
 *   RTE_E_DidServices_0xfd20_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd20_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd20_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd20_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD20u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd20_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd21_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd21>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd21_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd21_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd21_E_NOT_OK
 *   RTE_E_DidServices_0xfd21_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd21_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD21u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd21_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd21_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd21>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd21_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd21_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd21_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd21_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd21_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD21u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd23_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd23>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd23_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd23_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd23_E_NOT_OK
 *   RTE_E_DidServices_0xfd23_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd23_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD23u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd23_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd23_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd23>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd23_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd23_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd23_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd23_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd23_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD23u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd25_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd25>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd25_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd25_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd25_E_NOT_OK
 *   RTE_E_DidServices_0xfd25_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd25_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD25u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd25_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd25_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd25>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd25_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd25_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd25_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd25_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd25_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD25u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd26_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd26>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd26_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd26_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd26_E_NOT_OK
 *   RTE_E_DidServices_0xfd26_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd26_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD26u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd26_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd26_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd26>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd26_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd26_WriteData(Dcm_3Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd26_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd26_WriteData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd26_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD26u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd27_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd27>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd27_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd27_ReadData(Dcm_1Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd27_E_NOT_OK
 *   RTE_E_DidServices_0xfd27_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd27_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD27u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd27_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd27_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd27>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd27_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd27_WriteData(Dcm_1Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd27_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd27_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd27_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD27u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd29_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd29>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd29_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd29_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd29_E_NOT_OK
 *   RTE_E_DidServices_0xfd29_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd29_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD29u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd29_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd29_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd29>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd29_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd29_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd29_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd29_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd29_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD29u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd30_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd30>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd30_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd30_ReadData(Dcm_5Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd30_E_NOT_OK
 *   RTE_E_DidServices_0xfd30_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd30_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD30u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd30_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd30_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfd30>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd30_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfd30_WriteData(Dcm_5Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd30_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd30_WriteData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd30_WriteData (returns application error)
 *********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFD30u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfd31_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfd31>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfd31_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfd31_ReadData(Dcm_12Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd31_E_NOT_OK
 *   RTE_E_DidServices_0xfd31_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd31_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfd31_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfd31_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFD31u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfd31_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda1_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfda1>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda1_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfda1_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda1_E_NOT_OK
 *   RTE_E_DidServices_0xfda1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda1_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDA1u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfda1_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda1_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfda1>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda1_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfda1_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda1_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda1_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDA1u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda2_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfda2>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda2_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfda2_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda2_E_NOT_OK
 *   RTE_E_DidServices_0xfda2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda2_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDA2u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfda2_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda2_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfda2>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda2_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfda2_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda2_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda2_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDA2u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda3_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfda3>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda3_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfda3_ReadData(Dcm_12Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda3_E_NOT_OK
 *   RTE_E_DidServices_0xfda3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda3_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDA3u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfda3_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfda3_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfda3>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfda3_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfda3_WriteData(Dcm_12Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfda3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfda3_WriteData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfda3_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDA3u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdac_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdac>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdac_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdac_ReadData(Dcm_64Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdac_E_NOT_OK
 *   RTE_E_DidServices_0xfdac_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_ReadData(P2VAR(Dcm_64Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdac_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDACu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdac_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdac_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdac>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdac_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdac_WriteData(Dcm_64Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdac_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdac_WriteData(P2VAR(Dcm_64Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdac_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDACu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdad_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdad>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdad_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdad_ReadData(Dcm_7Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdad_E_NOT_OK
 *   RTE_E_DidServices_0xfdad_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdad_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdad_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdad_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDADu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdad_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdae_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdae>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdae_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdae_ReadData(Dcm_2Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdae_E_NOT_OK
 *   RTE_E_DidServices_0xfdae_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdae_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDAEu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdae_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdae_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdae>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdae_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdae_WriteData(Dcm_2Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdae_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdae_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdae_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDAEu, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdaf_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdaf>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdaf_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdaf_ReadData(Dcm_176Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdaf_E_NOT_OK
 *   RTE_E_DidServices_0xfdaf_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdaf_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdaf_ReadData(P2VAR(Dcm_176Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdaf_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDAFu, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdaf_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb0_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb0>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb0_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb0_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb0_E_NOT_OK
 *   RTE_E_DidServices_0xfdb0_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb0_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB0u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb0_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb0_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb0>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb0_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb0_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb0_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb0_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb0_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB0u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb1_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb1>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb1_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb1_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb1_E_NOT_OK
 *   RTE_E_DidServices_0xfdb1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb1_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB1u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb1_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb1_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb1>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb1_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb1_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb1_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb1_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB1u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb2_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb2>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb2_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb2_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb2_E_NOT_OK
 *   RTE_E_DidServices_0xfdb2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb2_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB2u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb2_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb2_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb2>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb2_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb2_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb2_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb2_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb2_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB2u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb3_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb3>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb3_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb3_ReadData(Dcm_256Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb3_E_NOT_OK
 *   RTE_E_DidServices_0xfdb3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_ReadData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb3_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB3u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb3_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb3_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb3>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb3_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb3_WriteData(Dcm_256Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb3_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb3_WriteData(P2VAR(Dcm_256Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb3_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB3u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb4_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb4>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb4_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb4_ReadData(Dcm_8Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb4_E_NOT_OK
 *   RTE_E_DidServices_0xfdb4_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb4_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB4u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb4_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb4_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb4>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb4_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb4_WriteData(Dcm_8Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb4_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb4_WriteData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb4_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB4u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb5_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb5>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb5_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb5_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb5_E_NOT_OK
 *   RTE_E_DidServices_0xfdb5_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb5_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB5u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb5_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb5_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb5>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb5_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb5_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb5_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb5_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb5_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB5u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb6_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb6>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb6_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb6_ReadData(Dcm_4Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb6_E_NOT_OK
 *   RTE_E_DidServices_0xfdb6_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb6_ReadData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB6u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);
	
	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb6_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}
	
	return RetValue_Cnt_T_u08;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb6_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb6>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb6_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb6_WriteData(Dcm_4Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb6_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb6_WriteData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb6_WriteData (returns application error)
 *********************************************************************************************************************/
	
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB6u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb7_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfdb7>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb7_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfdb7_ReadData(Dcm_18Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb7_E_NOT_OK
 *   RTE_E_DidServices_0xfdb7_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_ReadData(P2VAR(Dcm_18Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb7_ReadData (returns application error)
 *********************************************************************************************************************/

	VAR(uint8,  AUTOMATIC) CmdResp_Cnt_T_u08;
	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;

	CmdResp_Cnt_T_u08 = DiagSrvcs_MainHandler(0xFDB7u, 0x22u, (uint8*)data, 0u, &RespLen_Cnt_T_u16);

	if( CmdResp_Cnt_T_u08 != 0u )
	{
		RetValue_Cnt_T_u08 = RTE_E_DidServices_0xfdb7_E_NOT_OK;
	}
	else
	{
		RetValue_Cnt_T_u08 = RTE_E_OK;
	}

	return RetValue_Cnt_T_u08;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfdb7_WriteData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <WriteData> of PortPrototype <DidServices_0xfdb7>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfdb7_WriteData(UInt8 *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfdb7_WriteData(Dcm_18Byte_Type *data, UInt16 dataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfdb7_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_WriteData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfdb7_WriteData(P2VAR(Dcm_18Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data, UInt16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfdb7_WriteData (returns application error)
 *********************************************************************************************************************/

	VAR(uint16, AUTOMATIC) RespLen_Cnt_T_u16;

	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xFDB7u, 0x2Eu, (uint8*)data, dataLength, &RespLen_Cnt_T_u16);

	return RTE_E_OK;


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfe00_ReadData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReadData> of PortPrototype <DidServices_0xfe00>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfe00_ReadData(UInt8 *data)
#else
 *   Std_ReturnType DidServices_0xfe00_ReadData(Dcm_3Byte_Type *data)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfe00_E_NOT_OK
 *   RTE_E_DidServices_0xfe00_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfe00_ReadData(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfe00_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) data)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfe00_ReadData (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_DidServices_0xfe00_E_NOT_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfe00_ReturnControlToECU
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ReturnControlToECU> of PortPrototype <DidServices_0xfe00>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_HaitecTrqCmd_SCom_StopCtrl(void)
 *     Synchronous Server Invocation. Timeout: None
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_DCMServices_GetSesCtrlType(Dcm_SesCtrlType *SessionCtrlType)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DCMServices_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfe00_ReturnControlToECU(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfe00_ReturnControlToECU(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_3Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfe00_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfe00_ReturnControlToECU(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfe00_ReturnControlToECU(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfe00_ReturnControlToECU (returns application error)
 *********************************************************************************************************************/
	
	VAR(ManufModeType,    AUTOMATIC) MEC_Cnt_T_enum;
	VAR(Dcm_SesCtrlType,  AUTOMATIC) SesCtrlType_Cnt_T_enum;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum); /* PRQA S 3200 */
	Rte_Call_DCMServices_GetSesCtrlType(&SesCtrlType_Cnt_T_enum); /* PRQA S 3200 */
	
	if( SesCtrlType_Cnt_T_enum != NEXTEER )
	{
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		}
		else
		{
			*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
		}
	}
	else if( MEC_Cnt_T_enum == ProductionMode )
	{
		*ErrorCode = 0xFBu; /* EPSNrcMECEqZero */
	}
	else
	{
		Rte_Call_HaitecTrqCmd_SCom_StopCtrl();
		
		(*ResponseData)[0] = 0u;
		(*ResponseData)[1] = 0u;
		(*ResponseData)[2] = 0u;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_0xfe00_ShortTermAdjustment
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ShortTermAdjustment> of PortPrototype <DidServices_0xfe00>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_HaitecTrqCmd_SCom_StartCtrl(Float Param_ManTrqCmd_MtrNm_f32, Boolean Param_DefeatHwTrq_Cnt_lgc, Boolean Param_DefeatTemp_Cnt_lgc)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_HaitecTrqCmd_SCom_E_NOT_OK
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_DCMServices_GetSesCtrlType(Dcm_SesCtrlType *SessionCtrlType)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DCMServices_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType DidServices_0xfe00_ShortTermAdjustment(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType DidServices_0xfe00_ShortTermAdjustment(Dcm_3Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_3Byte_Type *ResponseData, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfe00_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfe00_ShortTermAdjustment(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_0xfe00_ShortTermAdjustment(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_0xfe00_ShortTermAdjustment (returns application error)
 *********************************************************************************************************************/
	
	VAR(ManufModeType,    AUTOMATIC) MEC_Cnt_T_enum;
	VAR(Dcm_SesCtrlType,  AUTOMATIC) SesCtrlType_Cnt_T_enum;
	VAR(uint16,           AUTOMATIC) TorqueCommand_Cnt_T_u16;
	VAR(float32,          AUTOMATIC) TorqueCommand_MtrNm_T_f32;
	VAR(uint8,            AUTOMATIC) Defeats_Cnt_T_u08;
	VAR(boolean,          AUTOMATIC) TempDefeat_Cnt_T_lgc;
	VAR(boolean,          AUTOMATIC) HwTrqDefeat_Cnt_T_lgc;
	VAR(Std_ReturnType,   AUTOMATIC) RetVal_Cnt_T_enum;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum); /* PRQA S 3200 */
	Rte_Call_DCMServices_GetSesCtrlType(&SesCtrlType_Cnt_T_enum); /* PRQA S 3200 */
	
	if( SesCtrlType_Cnt_T_enum != NEXTEER )
	{
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		}
		else
		{
			*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
		}
	}
	else if( MEC_Cnt_T_enum == ProductionMode )
	{
		*ErrorCode = 0xFBu; /* EPSNrcMECEqZero */
	}
	else
	{
		
		TorqueCommand_Cnt_T_u16 = (((uint16)((*RequestData)[0])) << 8) | ((uint16)((*RequestData)[1]));
		TorqueCommand_MtrNm_T_f32 = FPM_FixedToFloat_m(((sint16)TorqueCommand_Cnt_T_u16), s4p11_T);
		
		Defeats_Cnt_T_u08 = (*RequestData)[2];
		
		if( (Defeats_Cnt_T_u08 & 1u) == 0u )
		{
			TempDefeat_Cnt_T_lgc = FALSE;
		}
		else
		{
			TempDefeat_Cnt_T_lgc = TRUE;
		}
		
		if( (Defeats_Cnt_T_u08 & 2u) == 0u )
		{
			HwTrqDefeat_Cnt_T_lgc = FALSE;
		}
		else
		{
			HwTrqDefeat_Cnt_T_lgc = TRUE;
		}
		
		RetVal_Cnt_T_enum = Rte_Call_HaitecTrqCmd_SCom_StartCtrl(TorqueCommand_MtrNm_T_f32, HwTrqDefeat_Cnt_T_lgc, TempDefeat_Cnt_T_lgc);
		
		if( RetVal_Cnt_T_enum != E_OK )
		{
			*ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
		}
		else
		{
			(*ResponseData)[0] = (*RequestData)[0];
			(*ResponseData)[1] = (*RequestData)[1];
			(*ResponseData)[2] = (*RequestData)[2];
		}
		
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_Customer_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0x0100>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf180>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf187>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf18a>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf18c>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf191>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf193>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf194>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xf195>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DidServices_Customer_ConditionCheckRead(Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_Customer_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_Customer_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_Customer_ConditionCheckWrite
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0x0100>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xf187>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xf18a>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DidServices_Customer_ConditionCheckWrite(Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0x0100_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_Customer_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_Customer_ConditionCheckWrite (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_Nexteer_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd01>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd02>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd07>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd0e>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd10>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd12>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd13>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd14>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd17>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd19>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1a>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1b>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1c>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd1e>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd20>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd21>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd23>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd25>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd26>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd27>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd29>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd30>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd31>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfda1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfda2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfda3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdac>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdad>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdae>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdaf>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb0>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb4>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb5>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb6>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfdb7>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_DCMServices_GetSesCtrlType(Dcm_SesCtrlType *SessionCtrlType)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DCMServices_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DidServices_Nexteer_ConditionCheckRead(Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd01_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_Nexteer_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_Nexteer_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/
	
	VAR(ManufModeType,    AUTOMATIC) MEC_Cnt_T_enum;
	VAR(Dcm_SesCtrlType,  AUTOMATIC) SesCtrlType_Cnt_T_enum;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum); /* PRQA S 3200 */
	Rte_Call_DCMServices_GetSesCtrlType(&SesCtrlType_Cnt_T_enum); /* PRQA S 3200 */
	
	if( SesCtrlType_Cnt_T_enum != NEXTEER )
	{
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		}
		else
		{
			*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
		}
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_Nexteer_ConditionCheckWrite
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd02>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd07>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd12>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd19>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd1b>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd1e>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd21>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd23>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd25>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd26>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd27>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd29>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfd30>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfda1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfda2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfda3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdac>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdae>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb0>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb1>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb2>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb3>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb4>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb5>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb6>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckWrite> of PortPrototype <DidServices_0xfdb7>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_MEC_Cnt_enum(ManufModeType *data)
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
 *   Std_ReturnType Rte_Call_DCMServices_GetSesCtrlType(Dcm_SesCtrlType *SessionCtrlType)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DCMServices_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DidServices_Nexteer_ConditionCheckWrite(Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd02_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_Nexteer_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_Nexteer_ConditionCheckWrite (returns application error)
 *********************************************************************************************************************/
	
	VAR(ManufModeType,    AUTOMATIC) MEC_Cnt_T_enum;
	VAR(Dcm_SesCtrlType,  AUTOMATIC) SesCtrlType_Cnt_T_enum;
	
	Rte_Read_MEC_Cnt_enum(&MEC_Cnt_T_enum); /* PRQA S 3200 */
	Rte_Call_DCMServices_GetSesCtrlType(&SesCtrlType_Cnt_T_enum); /* PRQA S 3200 */
	
	if( SesCtrlType_Cnt_T_enum != NEXTEER )
	{
		if( MEC_Cnt_T_enum == ProductionMode )
		{
			*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
		}
		else
		{
			*ErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
		}
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: DidServices_Service2F_ConditionCheckRead
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd0d>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfd11>
 *   - triggered by server invocation for OperationPrototype <ConditionCheckRead> of PortPrototype <DidServices_0xfe00>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType DidServices_Service2F_ConditionCheckRead(Dcm_NegativeResponseCodeType *ErrorCode)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_DidServices_0xfd0d_E_PENDING
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) DidServices_Service2F_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: DidServices_Service2F_ConditionCheckRead (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf000_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf000>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf000_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf000_Start(Dcm_3Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf000_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf000_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf000_Start(P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf000_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF000u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf001_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf001>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf001_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf001_Start(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf001_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf001_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf001_Start(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf001_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF001u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf003_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf003>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf003_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf003_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf003_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf003_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf003_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf003_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF003u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf004_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf004>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf004_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf004_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf004_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf004_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf004_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf004_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF004u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf005_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf005>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf005_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf005_Start(Dcm_2Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_3Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf005_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf005_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf005_Start(P2VAR(Dcm_2Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_3Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf005_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF005u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf008_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf008>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf008_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf008_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf008_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf008_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf008_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf008_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF008u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf009_RequestResults
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <RequestResults> of PortPrototype <RoutineServices_0xf009>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf009_RequestResults(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf009_RequestResults(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_1Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf009_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_RequestResults(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf009_RequestResults (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF009u, 0x03u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf009_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf009>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf009_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf009_Start(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf009_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf009_Start (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF009u, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf009_Stop
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Stop> of PortPrototype <RoutineServices_0xf009>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf009_Stop(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf009_Stop(Dcm_0Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf009_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Stop(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf009_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf009_Stop (returns application error)
 *********************************************************************************************************************/
	
	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF009u, 0x02u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xf0ff_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xf0ff>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xf0ff_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xf0ff_Start(Dcm_6Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xf0ff_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf0ff_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xf0ff_Start(P2VAR(Dcm_6Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xf0ff_Start (returns application error)
 *********************************************************************************************************************/

	*ErrorCode = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0xF0FFu, 0x01u, (uint8*)RequestData, RequestDataLength, ResponseDataLength);

  return RTE_E_OK;

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RoutineServices_0xfee0_Start
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <Start> of PortPrototype <RoutineServices_0xfee0>
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
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_AbsHwPos_SCom_CustClrTrim(void)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_AbsHwPos_SCom_CustSetTrim(void)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_AbsHwPos_SCom_TrimNotPerformed
 *   Std_ReturnType Rte_Call_LrnEOT_Scom_ResetEOT(void)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_VehDyn_SCom_ResetCenter(void)
 *     Synchronous Server Invocation. Timeout: None
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType RoutineServices_0xfee0_Start(UInt8 *RequestData, UInt16 RequestDataLength, UInt8 *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType RoutineServices_0xfee0_Start(Dcm_1Byte_Type *RequestData, UInt16 RequestDataLength, Dcm_0Byte_Type *ResponseData, UInt16 *ResponseDataLength, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_RoutineServices_0xfee0_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xfee0_Start(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) RoutineServices_0xfee0_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) RequestData, UInt16 RequestDataLength, P2VAR(Dcm_0Byte_Type, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseData, P2VAR(UInt16, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RoutineServices_0xfee0_Start (returns application error)
 *********************************************************************************************************************/
	
	VAR(Std_ReturnType, AUTOMATIC) RetVal_Cnt_T_enum;
	
	if( (*RequestData)[0] == 1u )
	{
		RetVal_Cnt_T_enum = Rte_Call_AbsHwPos_SCom_CustSetTrim();
		
		if( RetVal_Cnt_T_enum != RTE_E_OK )
		{
			*ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
		}
	}
	else if( (*RequestData)[0] == 2u )
	{
		RetVal_Cnt_T_enum = Rte_Call_AbsHwPos_SCom_CustClrTrim();
		RetVal_Cnt_T_enum |= Rte_Call_LrnEOT_Scom_ResetEOT();
		RetVal_Cnt_T_enum |= Rte_Call_VehDyn_SCom_ResetCenter();
		
		if( RetVal_Cnt_T_enum != RTE_E_OK )
		{
			*ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
		}
	}
	else
	{
		*ErrorCode = DCM_E_REQUESTOUTOFRANGE;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_1_CompareKey
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <CompareKey> of PortPrototype <SecurityAccess_1>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType SecurityAccess_1_CompareKey(UInt8 *Key)
#else
 *   Std_ReturnType SecurityAccess_1_CompareKey(Dcm_SecAccess_1_KeyType *Key)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_1_E_COMPARE_KEY_FAILED
 *   RTE_E_SecurityAccess_1_E_NOT_OK
 *   RTE_E_SecurityAccess_1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_CompareKey(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Key)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_CompareKey(P2VAR(Dcm_SecAccess_1_KeyType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Key)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_1_CompareKey (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SecurityAccess_1_GetSeed
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSeed> of PortPrototype <SecurityAccess_1>
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
 *   Std_ReturnType Rte_Call_DCMServices_GetSecurityLevel(Dcm_SecLevelType *SecLevel)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_DCMServices_E_NOT_OK
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType SecurityAccess_1_GetSeed(UInt8 *securityAccessDataRecord, UInt8 *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
#else
 *   Std_ReturnType SecurityAccess_1_GetSeed(Dcm_SecAccess_1_DataRecType *securityAccessDataRecord, Dcm_SecAccess_1_SeedType *Seed, Dcm_NegativeResponseCodeType *ErrorCode)
#endif
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SecurityAccess_1_E_NOT_OK
 *   RTE_E_SecurityAccess_1_E_PENDING
 *
 *********************************************************************************************************************/

#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_GetSeed(P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) securityAccessDataRecord, P2VAR(UInt8, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#else
FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SecurityAccess_1_GetSeed(P2VAR(Dcm_SecAccess_1_DataRecType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) securityAccessDataRecord, P2VAR(Dcm_SecAccess_1_SeedType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) Seed, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_AP_DIAGSVC_APPL_VAR) ErrorCode)
#endif
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SecurityAccess_1_GetSeed (returns application error)
 *********************************************************************************************************************/
	
	VAR(Dcm_SecLevelType, AUTOMATIC) SecLevel_Cnt_T_enum;
	
	Rte_Call_DCMServices_GetSecurityLevel(&SecLevel_Cnt_T_enum);
	
	if( SecLevel_Cnt_T_enum == DCM_SEC_LEV_LOCKED )
	{
		(*Seed)[0] = 0x11;
		(*Seed)[1] = 0x22;
		(*Seed)[2] = 0x33;
	}
	else
	{
		(*Seed)[0] = 0x00;
		(*Seed)[1] = 0x00;
		(*Seed)[2] = 0x00;
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SessionControl_ChangeIndication
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ChangeIndication> of PortPrototype <SessionControl>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SessionControl_ChangeIndication(Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SessionControl_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_ChangeIndication(Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SessionControl_ChangeIndication (returns application error)
 *********************************************************************************************************************/
	
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) Mode_Cnt_T_enum;
	
	Mode_Cnt_T_enum = Rte_Mode_SystemState_Mode();
	
	if( (Mode_Cnt_T_enum == RTE_MODE_StaMd_Mode_DISABLE) ||
		(Mode_Cnt_T_enum == RTE_MODE_StaMd_Mode_OPERATE) ||
		(Mode_Cnt_T_enum == RTE_MODE_StaMd_Mode_WARMINIT) )
	{
		Dem_EnableEventStatusUpdate(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
	}
	
	if( SesCtrlTypeNew == DCM_PROGRAMMING_SESSION )
	{
		TWrapC_CallFblStart();
	}
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SessionControl_ConfirmationRespPending
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <ConfirmationRespPending> of PortPrototype <SessionControl>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SessionControl_ConfirmationRespPending(Dcm_ConfirmationStatusType status)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SessionControl_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_ConfirmationRespPending(Dcm_ConfirmationStatusType status)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SessionControl_ConfirmationRespPending (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: SessionControl_GetSesChgPermission
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <GetSesChgPermission> of PortPrototype <SessionControl>
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
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   Std_ReturnType SessionControl_GetSesChgPermission(Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew)
 *
 **********************************************************************************************************************
 *
 * Available Application Errors:
 * =============================
 *   RTE_E_SessionControl_E_FORCE_RCRRP
 *   RTE_E_SessionControl_E_NOT_OK
 *   RTE_E_SessionControl_E_PENDING
 *   RTE_E_SessionControl_E_SESSION_NOT_ALLOWED
 *
 *********************************************************************************************************************/

FUNC(Std_ReturnType, RTE_AP_DIAGSVC_APPL_CODE) SessionControl_GetSesChgPermission(Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: SessionControl_GetSesChgPermission (returns application error)
 *********************************************************************************************************************/
	
	return RTE_E_OK;
	
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_DIAGSVC_APPL_CODE
#include "MemMap.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_CheckUnspecifiedService(uint8 sid, P2VAR(boolean,AUTOMATIC,DCM_VAR_NOINIT) hasSprmib)
{
	VAR(Std_ReturnType, AUTOMATIC) RetValue_Cnt_T_u08;
	
	switch( sid )
	{
		case 0x11:
		case 0x28:
		case 0x85:
			*hasSprmib = TRUE;
			/* fallthrough */
			
		case 0x34:
		case 0x36:
		case 0x37:
		case 0xB0:
			RetValue_Cnt_T_u08 = DCM_E_OK;
			break;
		
		default:
			RetValue_Cnt_T_u08 = DCM_E_NOT_OK;
			break;
	}
	
	return RetValue_Cnt_T_u08;
}


FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_HandleUnspecifiedService(uint8                           sid
																,Dcm_MsgType                     requestPtr
																,Dcm_MsgLenType                  reqDataLen
																,Dcm_MsgType                     responsePtr
																,Dcm_MsgLenPtrType               resDataLenPtr
																,Dcm_NegativeResponseCodePtrType errorPtr)
{
	VAR(Rte_ModeType_StaMd_Mode, AUTOMATIC) Mode_Cnt_T_enum;
	VAR(Dcm_SesCtrlType, AUTOMATIC) Session_Cnt_T_enum;
	VAR(uint16, AUTOMATIC) i;
	
	Mode_Cnt_T_enum = Rte_Mode_SystemState_Mode();
	
	switch( sid )
	{
		case 0x11:
			
			if( reqDataLen != 1u )
			{
				*errorPtr = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
			}
			else if( (requestPtr[0] == 0x01) ||
					 (requestPtr[0] == 0x03) )
			{
				
				if( (Rte_SignlCondn_VehicleSpeed_Kph_f32 < k_VehSpdResetThresh_Kph_f32) &&
					(Abs_f32_m(Rte_Sweep_OutputHwTrq_HwNm_f32) < k_HwTrqResetThresh_Kph_f32) )
				{
					if( requestPtr[0] == 0x01 )
					{
						HardReset_Cnt_M_lgc = TRUE;
						responsePtr[0] = 0x01;
						*resDataLenPtr = 1u;
					}
					else
					{
						SoftReset_Cnt_M_lgc = TRUE;
						responsePtr[0] = 0x03;
						*resDataLenPtr = 1u;
					}
				}
				else
				{
					*errorPtr = DCM_E_CONDITIONSNOTCORRECT;
				}
			}
			else if( requestPtr[0] == 0x60 )
			{
				*errorPtr = (Dcm_NegativeResponseCodeType)DiagSrvcs_MainHandler(0x1160, requestPtr[0], (uint8*)responsePtr, 0u, resDataLenPtr);
			}
			else
			{
				*errorPtr = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			}
			
			break;
		
		
		case 0x28:
			
			Dcm_GetSesCtrlType(&Session_Cnt_T_enum);
			
			if( (Session_Cnt_T_enum != DCM_EXTENDED_DIAGNOSTIC_SESSION) &&
				(Session_Cnt_T_enum != NEXTEER) )
			{
				*errorPtr = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
			}
			else if( reqDataLen != 2u )
			{
				*errorPtr = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
			}
			else if( (requestPtr[0] == 0u) ||
					 (requestPtr[0] == 3u) )
			{
				
				if( requestPtr[1] != 1u )
				{
					*errorPtr = DCM_E_REQUESTOUTOFRANGE;
				}
				else if( requestPtr[0] == 3u )
				{
					Vmm_Dcm_CommunicationControl(VMM_ALL_CHANNEL, VMM_MSG_TYPE_ALL, FALSE, FALSE);
					responsePtr[0] = 3u;
					*resDataLenPtr = 1u;
				}
				else
				{
					Vmm_Dcm_CommunicationControl(VMM_ALL_CHANNEL, VMM_MSG_TYPE_ALL, TRUE, TRUE);
					responsePtr[0] = 0u;
					*resDataLenPtr = 1u;
				}
				
			}
			else
			{
				*errorPtr = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			}
			
			break;
		
		
		case 0x34:
		case 0x36:
		case 0x37:
			
			*errorPtr = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
			
			break;
		
		
		case 0x85:
			
			Dcm_GetSesCtrlType(&Session_Cnt_T_enum);
			
			if( (Session_Cnt_T_enum != DCM_EXTENDED_DIAGNOSTIC_SESSION) &&
				(Session_Cnt_T_enum != NEXTEER) )
			{
				*errorPtr = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
			}
			else if( reqDataLen != 1u )
			{
				*errorPtr = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
			}
			else if( (Mode_Cnt_T_enum != RTE_MODE_StaMd_Mode_DISABLE) &&
					 (Mode_Cnt_T_enum != RTE_MODE_StaMd_Mode_OPERATE) &&
					 (Mode_Cnt_T_enum != RTE_MODE_StaMd_Mode_WARMINIT) )
			{
				*errorPtr = DCM_E_CONDITIONSNOTCORRECT;
			}
			else if( requestPtr[0] == 1u )
			{
				Dem_EnableEventStatusUpdate(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
				responsePtr[0] = 1u;
				*resDataLenPtr = 1u;
			}
			else if( requestPtr[0] == 2u )
			{
				Dem_DisableEventStatusUpdate(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
				responsePtr[0] = 2u;
				*resDataLenPtr = 1u;
			}
			else
			{
				*errorPtr = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			}
			
			break;
		
		
		case 0xB0:
			
			if( reqDataLen < 2u )
			{
				*errorPtr = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
			}
			else if( requestPtr[0] != 1u )
			{
				*errorPtr = DCM_E_SUBFUNCTIONNOTSUPPORTED;
			}
			else
			{
				for( i = 0u; i < reqDataLen; i++ )
				{
					responsePtr[i] = requestPtr[i];
				}
				*resDataLenPtr = reqDataLen;
			}
			
			break;
		
		
		default:
			*errorPtr = DCM_E_SERVICENOTSUPPORTED;
			break;
	}
	
	return DCM_E_OK;
}


FUNC(void, DCM_APPL_CODE) Dcm_PostHandleUnspecifiedService(uint8 sid, Dcm_ConfirmationStatusType status)
{
	switch( sid )
	{
		case 0x11:
			if( HardReset_Cnt_M_lgc == TRUE )
			{
				Mcu_PerformReset();
			}
			else if( SoftReset_Cnt_M_lgc == TRUE )
			{
				StaMd_SCom_EcuReset();
			}
			else
			{
				/* do nothing */
			}
			break;
		
		default:
			break;
	}
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
