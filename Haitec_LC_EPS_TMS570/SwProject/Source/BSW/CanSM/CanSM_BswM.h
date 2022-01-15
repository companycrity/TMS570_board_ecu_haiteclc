/*  *****   STARTSINGLE_OF_MULTIPLE_COMMENT    *****  */




/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  Copyright (c) 2008 - 2013 by Vector Informatik GmbH.                                            All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
         File:  CanSM_BswM.h
    Component:  CAN State Manager
       Module:  -
    Generator:  -

  Description:  Public header of the CAN State Manager AUTOSAR Release 3.0
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
-----------------------------------------------------------------------------------------------------------------------
  Mark A. Fingerle              mfi           Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
-----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Change Id     Description
-----------------------------------------------------------------------------------------------------------------------
  01.16.00  2011-01-13  mfi     ESCAN00046656 Call Appl_CanSM_BusOffEnd() if a BusOff recovery is interrupted
                                ESCAN00047400 change shutdown sequence for Partial Network
                                ESCAN00046783 Support Multiple Identity Configuration
                                ESCAN00047494 Adapt CanSM for usage with IdentityManagerConfig
                                ESCAN00047436 BswM callout BswM_CanSM_CurrentState
                                ESCAN00044505 The application call back function declaration is surround by the same MemMap.h section as CanSM code
                                ESCAN00047985 No CAN communication possible, caused by bus-off in SILENT communication
                                ESCAN00048379 Definition CANSM_PRE_COMPILE used before it is set - Build Lib Check not usable
  01.16.01  2011-05-05  mfi     ESCAN00044505 The application call back function declaration is surround by the same MemMap.h section as CanSM code
                                ESCAN00050250 Extend Bus Off recovery handling, additional ModeIndications during BusOff recovery
  01.16.02  2012-08-23  mfi     ESCAN00051096 Call SetControllerMode (or TransceiverMode) during startup only if necessary
  01.16.03  2013-02-03  mfi     ESCAN00064035 GetCurrentComMode() delivers wrong mode during running bus-off recovery
**********************************************************************************************************************/

#ifndef CANSM_BSWM_H

# define CANSM_BSWM_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
* Version
**********************************************************************************************************************/
/* AUTOSAR CAN State Management version */
/* ##V_CFG_MANAGEMENT ##CQProject : Ccl_AsrSmCan CQComponent : Implementation */
# define CCL_ASRSMCAN_BSWM_HEADER_VERSION                             0x0116u   /* BCD coded version number */
# define CCL_ASRSMCAN_BSWM_HEADER_RELEASE_VERSION                     0x03u   /* BCD coded release version number  */


/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
#include "Platform_Types.h"
#include "Compiler_Cfg.h"

#define CANSM_BSWM_NO_COMMUNICATION       0u
#define CANSM_BSWM_SILENT_COMMUNICATION   1u
#define CANSM_BSWM_FULL_COMMUNICATION     2u
#define CANSM_BSWM_BUS_OFF                3u

typedef VAR(uint8, CANSM_VAR_NOINIT) CanSM_BswMCurrentStateType;


/*******************************************************************************
* Organi check
*******************************************************************************/


#endif /* end if not defined ( CANSM_BSWM_H ) */
/**********************************************************************************************************************
  END OF FILE: CanSM_BswM.h
**********************************************************************************************************************/
/*  *****   STOPSINGLE_OF_MULTIPLE_COMMENT    *****  */

