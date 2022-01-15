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
 * %version:          EA3#4 %
 * %derived_by:       jzk9cc %
 * %date_modified:    Mon Jul 29 12:50:01 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 */

#ifndef CALCONSTANTS_H
#define CALCONSTANTS_H

#include "Std_Types.h"


typedef struct
{
  uint16 Threshold;
  uint16 PStep;
  uint16 NStep;
} DiagSettings_Str;

/*********************** Start of Auto Generated Code ************************/

/****************** File Generated on 11/24/2015 4:53:11 PM ******************/
/******************************** EPWM- Rev5 *********************************/



extern CONST(sint16, CAL_CONST) k_ADCTrig1Offset_Cnt_s16;
extern CONST(uint16, CAL_CONST) k_PwmDeadBand_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_PwmRelay_Cnt_u16;
extern CONST(uint32, CAL_CONST) k_SENTSyncDelay_Cnt_u32;
extern CONST(DiagSettings_Str, CAL_CONST) k_HwTrqDiag_Cnt_str;
extern CONST(uint16, CAL_CONST) k_SPI50UOff_Cnt_u16;
extern CONST(uint16, CAL_CONST) k_SPI1mOff_Cnt_u16;
extern CONST(uint32, CAL_CONST) k_SENTSyncTrgMin_Cnt_u32;
#endif


