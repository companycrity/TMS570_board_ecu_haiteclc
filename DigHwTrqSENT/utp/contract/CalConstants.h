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
/* Version Control:
 * Date Created:      Wed Apr 13 12:17:00 2011
 * %version:          1 %
 * %derived_by:       nz63rn %
 * %date_modified:    Thu Jun 13 08:13:37 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 */

#ifndef CALCONSTANTS_H
#define CALCONSTANTS_H

#include "Std_Types.h"

extern CONST (float32, CAL_CONST) k_HwTrqLPFFc_Hz_f32;
extern CONST (float32, CAL_CONST) k_T1vsT2TrqSum_HwNm_f32;
extern CONST (float32, CAL_CONST) k_T1T2TransFltLim_HwNm_f32;
extern CONST (float32, CAL_CONST) k_T1T2CMCLPFEnable_HwNm_f32;
extern CONST (float32, CAL_CONST) k_T1T2CMCLPFFc_Hz_f32;
extern CONST (float32, CAL_CONST) k_CMCLPFOutLim_HwNm_f32;
extern CONST (float32, CAL_CONST) k_T1T2SSLPFFc_Hz_f32;
extern CONST (float32, CAL_CONST) k_T1T2SSLim_HwNm_f32;
extern CONST (uint16, CAL_CONST)  t_T1T2DepTrsTimecon_Hz_u6p10[17];
extern CONST (uint16, CAL_CONST)  t_T1T2IndTrsTimecon_HwNm_u5p11[17];
extern CONST (float32, CAL_CONST) k_MaxHwTrqTrim_HwNm_f32;

#endif
