/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_MtrCtrl.h
* Module Description: Motor control Complex Driver configuration
* Product           : Gen II Plus - EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Mar 23 13:00:00 2013
* %version:          2 %
* %derived_by:       nzt9hv %
* %date_modified:    Tue Nov 26 17:25:01 2013 %
*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 03/21/12  1     Selva      Updated to version 8 FDD SF99 B	                                                   7711			
 */

#ifndef MTRCTRL_H
#define MTRCTRL_H

#ifdef MTRCTRL
extern VAR(float32, AUTOMATIC) MtrCurrQaxRef_Amp_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrCurrDaxRef_Amp_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrDaxIntegralGain_Uls_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrDaxPropotionalGain_Uls_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrQaxIntegralGain_Uls_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrQaxPropotionalGain_Uls_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrPosComputationDelay_Rad_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrVoltDaxFF_Volt_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrVoltQaxFF_Volt_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrEstKe_VpRadpS_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrCurrQaxRpl_Amp_M_f32[2];
extern VAR(float32, AUTOMATIC) MtrCurrQaxCog_Amp_M_f32;  
extern VAR(uint16, AUTOMATIC)  FastDataAccessBufIndex_Cnt_M_u16;
extern VAR(uint16, AUTOMATIC)  SlowDataAccessBufIndex_Cnt_M_u16;   
#endif
extern FUNC(void, PICurrCntrl_CODE) PICurrCntrl_Per1(void);
extern FUNC(void, IPMTRQCANC_CODE) TrqCogCancRefPer1(void);


#endif
