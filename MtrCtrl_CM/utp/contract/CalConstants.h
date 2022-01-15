/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : CalConstants.h
* Module Description: This file contains the declarations of calibration 
*                     constants used in the EPS Software.
* Product           : Gen II Plus EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri May  9 16:48:22 2003
* %version:          6 %
* %derived_by:       qzx0t0 %
* %date_modified:    Thu Feb 13 10:30:44 2014 %
*---------------------------------------------------------------------------*/

#ifndef CALCONSTANTS_H
#define CALCONSTANTS_H



#include "Filter_Types.h"

/*********************** Start of Auto Generated Code ************************/

/****************** File Generated on 02/13/2014 10:15:50 AM ******************/
/************************* MotorControl_CM - Rev  9 **************************/


extern CONST(float32, CAL_CONST) k_MinTrqCmdScl_Uls_f32;
extern CONST(float32, CAL_CONST) k_MaxTrqCmdScl_Uls_f32;
extern CONST(float32, CAL_CONST) k_NoofPoles_Uls_f32;
extern CONST(float32, CAL_CONST) k_PIGainVspdCutoff_kph_f32;
extern CONST(uint16, CAL_CONST) t_KpqGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KpqGainY_Uls_u6p10[8];
extern CONST(uint16, CAL_CONST) t_KiqGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KiqGainY_Uls_u10p6[8];
extern CONST(uint16, CAL_CONST) t_KpdGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KpdGainY_Uls_u6p10[8];
extern CONST(uint16, CAL_CONST) t_KidGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KidGainY_Uls_u10p6[8];
extern CONST(float32, CAL_CONST) k_MtrPosComputationDelay_Sec_f32;
extern CONST(float32, CAL_CONST) k_MinKeRngLmt_VpRadpS_f32;
extern CONST(float32, CAL_CONST) k_MaxKeRngLmt_VpRadpS_f32;
extern CONST(float32, CAL_CONST) k_MinRRngLmt_Ohm_f32;
extern CONST(float32, CAL_CONST) k_MaxRRngLmt_Ohm_f32;
extern CONST(float32, CAL_CONST) k_MinLqRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_MaxLqRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_MinLdRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_MaxLdRngLmt_Henry_f32;
extern CONST(float32, CAL_CONST) k_NomTemp_DegC_f32;
extern CONST(float32, CAL_CONST) k_MagThrC_VpRadpSpDegC_f32;
extern CONST(float32, CAL_CONST) k_NomRfet_Ohm_f32;
extern CONST(float32, CAL_CONST) k_SiThermCoeff_OhmpDegC_f32;
extern CONST(float32, CAL_CONST) k_CuThermCoeff_OhmpDegC_f32;
extern CONST(uint16, CAL_CONST) t_KeSatTblX_Amp_u9p7[16];
extern CONST(uint16, CAL_CONST) t_KeSatTblY_Uls_u2p14[16];
extern CONST(uint16, CAL_CONST) t_CurrParamCompDaxRef_Amp_u9p7[6];
extern CONST(uint16, CAL_CONST) t_CurrParamCompQaxRef_Amp_u9p7[7];
extern CONST(uint16, CAL_CONST) t2_CurrParamLdSatSclFac_Uls_u2p14[6][7];
extern CONST(uint16, CAL_CONST) t2_CurrParamLqSatSclFac_Uls_u2p14[6][7];
extern CONST(float32, CAL_CONST) k_PiSamplingTs_Sec_f32;
extern CONST(uint16, CAL_CONST) t_CommOffsetTblX_Uls_u3p13[2];
extern CONST(uint16, CAL_CONST) t_CommOffsetTblY_Cnt_u16[2];
extern CONST(uint16, CAL_CONST) k_EstPkCurr2msLPFKn_Uls_u16;
extern CONST(uint16, CAL_CONST) k_EstPkCurrSlowLoopLPFKn_Uls_u16;
extern CONST(uint16, CAL_CONST) t_KiqGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KiqGainY_Uls_u10p6[8];
extern CONST(uint16, CAL_CONST) t_KpdGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KpdGainY_Uls_u6p10[8];
extern CONST(uint16, CAL_CONST) t_KidGainX_MtrRadpSec_u12p4[8];
extern CONST(uint16, CAL_CONST) t_KidGainY_Uls_u10p6[8];
extern CONST(uint16, CAL_CONST) k_MtrVelFiltFFKn_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_MtrVelFiltPIKn_Cnt_u16;
extern CONST(float32, CAL_CONST) k_MtrPosComputationDelay_Sec_f32;
extern CONST(float32, CAL_CONST) k_NoofPoles_Uls_f32;
extern CONST(float32, CAL_CONST) k_Harmonic6thElec_Uls_f32;
extern CONST(float32, CAL_CONST) k_Harmonic12thElec_Uls_f32;
extern CONST(float32, CAL_CONST) k_Harmonic18thElec_Uls_f32;
extern CONST(uint16, CAL_CONST) t_MtrCurrQaxRpl_Amp_u9p7[7];
extern CONST(uint16, CAL_CONST) t_MtrCurrDaxRpl_Amp_u9p7[6];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl6X_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl6Y_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl18X_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl18Y_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl12X_Amp_s6p9[6][7];
extern CONST(sint16, CAL_CONST) t2_MtrCurrQaxRpl12Y_Amp_s6p9[6][7];
extern CONST(uint16, CAL_CONST) t_MtrCurrQaxRplPIY_Amp_u9p7[7];
extern CONST(uint16, CAL_CONST) t_MtrVelX_MtrRadpS_T_u16[10];
extern CONST(uint16, CAL_CONST) t2_MtrTrqCancPIMagRP_Uls_u6p10[10][7];
extern CONST(uint16, CAL_CONST) t2_MtrTrqCancPIPhRP_Rev_u0p16[10][7];
extern CONST(float32, CAL_CONST) k_InstMtrDirHyst_Deg_f32;
extern CONST(float32, CAL_CONST) k_NomLq_Henry_f32;
extern CONST(float32, CAL_CONST) k_NomLd_Henry_f32;
extern CONST(float32, CAL_CONST) t_RefDeltaPoints_Rad_f32[8];
extern CONST(uint16, CAL_CONST) t_Q13VltgSchedXTbl_MtrRadpS_u12p4[10];
extern CONST(uint16, CAL_CONST) t_Q13VltgSchedYTbl_Volt_u5p11[10];
extern CONST(uint16, CAL_CONST) t_Q24VltgSchedXTbl_MtrRadpS_u12p4[10];
extern CONST(uint16, CAL_CONST) t_Q24VltgSchedYTbl_Volt_u5p11[10];
extern CONST(float32, CAL_CONST) k_IdqRefTrqTol_Rad_f32;
extern CONST(uint16, CAL_CONST) k_IdqRefTrqNIter_Cnt_u16;
extern CONST(float32, CAL_CONST) k_IdqRefIminTol_Amp_f32;
extern CONST(uint16, CAL_CONST) k_IdqRefIminNIter_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_IdqRefLocateRefNIter_Cnt_u16;
extern CONST(float32, CAL_CONST) k_deadtimeVScale_Uls_f32;
extern CONST(float32, CAL_CONST) k_IdBoostGain_Uls_f32;
extern CONST(float32, CAL_CONST) k_IdBoostVRThreshScl_Uls_f32;
extern CONST(uint16, CAL_CONST) t_IdBoostTrqCmdX_MtrNm_u4p12[11];
extern CONST(uint16, CAL_CONST) t_IdBoostTrqCharSclY_Uls_u1p15[11];
#endif
