/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Interrupts.h
* Module Description: Interrupts external definitions
* Product           : Gen II Plus - EA3.0
* Author            : Jeremy Warmbier
*****************************************************************************/
/* Version Control:
 * Date Created:      Wed Jul 17 11:00:00 2013
 * %version:          3 %
 * %derived_by:       nzx5jd %
 * %date_modified:    Fri Feb 21 14:21:28 2014 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author    Change Description                                                               SCR #
 * --------  -------  --------  ------------------------------------------------------------------------------  -------
 * 07/17/13   1       OT        Initial Haitec version
 * 01/24/14   2       OT        Added over voltage threshold interrupt
 * 02/21/14   3       OT        Added clear system tick interrupt
 */


#ifndef INTERRUPTS_H
#define INTERRUPTS_H


#include "tcb.h"


FUNC(void, INTERRUPT_CODE) EnableFIQInterrupts(void);
FUNC(void, INTERRUPT_CODE) EnableCanInterrupt(void);
FUNC(void, INTERRUPT_CODE) EnableMtrCtlInterrupt(void);
FUNC(void, INTERRUPT_CODE) EnableSysTickInterrupt(void);
FUNC(void, INTERRUPT_CODE) EnableESMLInterrupt(void);
FUNC(void, INTERRUPT_CODE) EnableCRCInterrupt(void);
FUNC(void, INTERRUPT_CODE) EnableOverVoltThreshInterrupt(void);
FUNC(void, INTERRUPT_CODE) DisableMtrCtlInterrupt(void);
FUNC(void, INTERRUPT_CODE) ClearSysTickInterruptFlg(void);

FUNC(void, INTERRUPT_CODE) DisableSysTickInterrupt(void);

#endif
