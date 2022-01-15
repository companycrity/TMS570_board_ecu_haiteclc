/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DfltConfigData.h
* Module Description:
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*****************************************************************************/
/* Version Control:
 * %version:          7 %
 * %derived_by:       nzx5jd %
 *---------------------------------------------------------------------------------------------------------------------
 * Date       Rev     Author   Change Description                                                               SCR #
 * --------   ------  -------  ------------------------------------------------------------------------------  -------
 * 07/09/13    1      OT       Initial Version
 * 07/30/13    2      OT       Removed T_InitMtrPosSnsr_EOLData
 * 07/31/13    3      OT       Removed T_InitHwTrqScaleData and T_InitNomMtrParam
 * 09/24/13    4      OT       Added deprecated NvM block
 * 05/22/13    5      OT       Added deprecated NvM blocks for NvM security implementation
 * 10/28/14    6      OT       Updated NvM initialization blocks and deprecated blocks
 * 06/26/15    7      OT       Cleaned up deprecated blocks
 */


#ifndef RTE_AP_DFLTCONFIGDATA_H
#define RTE_AP_DFLTCONFIGDATA_H


#include "Std_Types.h"
#include "Rte_Type.h"


typedef struct
{
  float32 EOLVehCntrOffset_HwDeg_f32;
  boolean EOLHwPosTrimPerformed_Cnt_lgc;
} Deprecated_EOLHwPosTrimType;

typedef struct
{
  float32 k_EOLHwTrqTrim_HwNm_f32;
  boolean k_EOLHwTrqTrimPerformed_Cnt_Lgc;
} Deprecated_DigHwTrqSENTTrim_DataType;

typedef struct
{
  sint16 CurrTempOffsetX_DegC_s10p5[16];
  sint16 CurrOffsetY1_Volts_s4p11[16];
  sint16 CurrOffsetY2_Volts_s4p11[16];
  uint8 CRC_Cnt_u08[2];
} Deprecated_CurrTempOffsetType;

typedef struct
{
  float32 EOLMtrCurrVcalCmd_VoltCnts_f32;
  float32 EOLMtrCurr1OffsetLo_Volts_f32;
  float32 EOLPhscurr1Gain_AmpspVolt_f32;
  float32 EOLPhscurr2Gain_AmpspVolt_f32;
  float32 EOLMtrCurr2OffsetLo_Volts_f32;
  float32 EOLMtrCurr1OffsetDiff_Volts_f32;
  float32 EOLMtrCurr2OffsetDiff_Volts_f32;
} Deprecated_PhaseCurrCal_DataType;

typedef struct
{
  float32 CWEOTPosition_HwDeg_f32;
  float32 CCWEOTPosition_HwDeg_f32;
  boolean CWEOTFound_Cnt_lgc;
  boolean CCWEOTFound_Cnt_lgc;
} Deprecated_EOTLearned_DataType;

typedef struct
{
  float32 FricOffset_HwNm_f32;
  float32 EOLFric_HwNm_f32;
  boolean EnableFricOffsetOutput_Cnt_lgc;
  boolean EnableFricLearning_Cnt_lgc;
  uint8   OpMode_Cnt_enum;
  uint16  RangeCounter_Cnt_u16[8][3];
  float32 Theta_HwNm_f32[8][4];
  float32 VehLearnedFric_HwNm_f32[4];
} Deprecated_AvgFricLrnType;

typedef struct
{
  float32 EOLVehCntrOffset_HwDeg_f32;
  uint16  EOLHwPosTrimPerformed_Cnt_u16;
} Deprecated_EOLHwPosTrimType1;


extern CONST(PhaseCurrCal_DataType, AP_DFLTCONFIGDATA_CONST) T_ShCurrCalInit_Cnt_str;
extern CONST(uint16,                AP_DFLTCONFIGDATA_CONST) T_CogTrqCalInit_Cnt_u16[512];
extern CONST(uint16,                AP_DFLTCONFIGDATA_CONST) T_CogTrqRplCompInit_Cnt_u16[9];
extern CONST(float32,               AP_DFLTCONFIGDATA_CONST) T_TorqueCmdSFInit_Uls_f32;
extern CONST(EOTLearned_DataType,   AP_DFLTCONFIGDATA_CONST) T_LearnedEOTInit_Cnt_str;
extern CONST(AvgFricLrnType,        AP_DFLTCONFIGDATA_CONST) T_AvgFricLrnDataInit_Cnt_str;

extern CONST(uint8, CDD_PARTNUMBER) k_SWRelNum_Cnt_u8[50];

extern FUNC(void, CDD_PARTNUMBER_CODE) DfltConfigData_Init1(void);


#endif /* RTE_AP_DFLTCONFIGDATA_H */
