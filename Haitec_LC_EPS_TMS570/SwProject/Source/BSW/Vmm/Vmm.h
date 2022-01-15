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
 *         File:  Vmm.h
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
 *  Thomas Kuhl                   Pet            Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2005-05-08  Pet                   Initial Version
 *  01.00.01  2008-08-20  Pet                   ESCAN00028925: Letter case of include is wrong
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

#if !defined (VMM_H)
#define VMM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Vmm_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : SysService_AsrVmm CQComponent : Implementation */
/* Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define SYSSERVICE_ASRVMM_VERSION          (0x0105u)
#define SYSSERVICE_ASRVMM_RELEASE_VERSION  (0x01u)

/* vendor and module identification */
#define VMM_VENDOR_ID              (30u)
#define VMM_MODULE_ID              (226)

/* Component Version Information */
#define VMM_SW_MAJOR_VERSION       (SYSSERVICE_ASRVMM_VERSION >> 8u)
#define VMM_SW_MINOR_VERSION       (SYSSERVICE_ASRVMM_VERSION & 0x00FF)
#define VMM_SW_PATCH_VERSION       SYSSERVICE_ASRVMM_RELEASE_VERSION

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* error codes */
#define VMM_E_UNINIT            0x10u   /* vmm is not initialized */
#define VMM_E_PARAM_POINTER     0x11u   /* Vmm init configuration pointer is NULL pointer */

/* service IDs */
#define VMM_DCM_COMMUNCIATIONCONTROL_ID   0x01u
#define VMM_BUSSM_IPDUGROUPSTART_ID       0x02u
#define VMM_BUSSM_IPDUGROUPSTOP_ID        0x03u
#define VMM_DCM_SETPASSIVEMODE_ID         0x04u
#define VVM_INIT_ID                       0x05u
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define VMM_START_SEC_CONST_8BIT
#include "MemMap.h"    /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

extern CONST(uint8, VMM_CONST) Vmm_MainVersion;
extern CONST(uint8, VMM_CONST) Vmm_SubVersion;
extern CONST(uint8, VMM_CONST) Vmm_ReleaseVersion;

#define VMM_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define VMM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/* Service Functions */
FUNC(void, VMM_CODE) Vmm_InitMemory(void);

#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
FUNC(void, VMM_CODE)  Vmm_Init( P2CONST(Vmm_ConfigSetType, AUTOMATIC, VMM_CONST) ConfigPtr );
#else
FUNC(void, VMM_CODE)  Vmm_Init( void );
#endif

#define VMM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */


#endif  /* VMM_H */

/**********************************************************************************************************************
 *  END OF FILE: Vmm.h
 *********************************************************************************************************************/
