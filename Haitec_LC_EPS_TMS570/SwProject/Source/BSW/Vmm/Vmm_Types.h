/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2008-2012 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Vmm_Types.h
 *    Component:  Vehicle Mode Management (communciation control)
 *       Module:  -
 *    Generator:  -
 *
 *  Description:  
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
  *  Thomas Kuhl                  Pet            Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2005-05-08  Pet                   Initial Version
 *  01.01.00  2008-09-30  Pet                   ESCAN00030485: Wrong I-PDU group will be switched by Vmm
 *                                              ESCAN00030002: PreCompile and Linktime Crc Check
 *                                              ESCAN00030741: Adapt message type values
 *                                              ESCAN00030785: Tx/Rx path not restarted after communication control phase
 *  01.02.00  2008-11-17  Pet                   ESCAN00031587: Missing deadline monitoring handling
 *                                              ESCAN00031647: Add DLL Version check
 *  01.03.00  2009-03-16  Pet                   ESCAN00033774: Add Ecu passive mode handling
 *                                              ESCAN00034049: Compiler Warning 
 *  01.04.00  2009-07-08  Pet                   ESCAN00036114: pre-processor checks for building the library
 *                                              ESCAN00036266: adapt spelling of common used names in comments
 *  01.05.00  2010-12-10  Pet                   ESCAN00045710: typing error in Vmm_Dcm_CommunicationControl FLASE -> FALSE
 *                                              ESCAN00046774: Support Multiple Identity Configuration
 *  01.05.01  2012-10-31  Pet                   ESCAN00056202: no changes
 *********************************************************************************************************************/
#if !defined (VMM_TYPES_H)
#define VMM_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"  /* Include standard types */
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* message type which shall be handled by the communication control */
#define VMM_MSG_TYPE_COM        1u
#define VMM_MSG_TYPE_NM         2u
#define VMM_MSG_TYPE_ALL        3u

/* channel define for all channels */
#define VMM_ALL_CHANNEL         0xFFu

/* init state type */
#define VMM_INIT_STATE_UNINIT  0u
#define VMM_INIT_STATE_INIT    1u

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/* Inhibition status of the ComM */
typedef uint8 Vmm_MsgType;
typedef uint8 Vmm_InitStateType;

#endif  /* VMM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Vmm_Types.h
 *********************************************************************************************************************/
