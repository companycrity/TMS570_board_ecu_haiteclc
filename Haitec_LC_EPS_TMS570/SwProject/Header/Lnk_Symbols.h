/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Lnk_Symbols.h
* Module Description: This file contains the declarations of Link Time Symbols
*                     used in the application.
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 11 11:30:00 2013
 * %version:          5 %
 * %derived_by:       nzx5jd %
 * %date_modified:    Mon Jan 27 15:51:00 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 07/11/13   1       OT        Initial Haitec version
 * 07/29/13   2       OT        Removed Flash API from RAM
 * 07/31/13   3       OT        Added Lnk_BootRelNum_Addr
 * 10/10/13   4       OT        Updated Lnk_BootRelNum_Addr data type
 * 01/27/14   5       OT        Removed unused symbols
 */

#ifndef LNK_SYMBOLS_H
#define LNK_SYMBOLS_H

#include "Std_Types.h"

extern VAR(uint8, AUTOMATIC) Lnk_BootRelNum_Addr;

extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_BSS_Start;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_BSS_End;

extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_AppBlock_Start;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_AppBlock_Length;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_CalBlock_Start;
extern CONSTP2VAR(void, AUTOMATIC, AUTOMATIC) Lnk_CalBlock_Length;

#endif

