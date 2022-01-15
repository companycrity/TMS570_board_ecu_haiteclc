/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2008-2012 by Vector Informatik GmbH.                                                  All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Vmm.c
 *      Project:  Vehicle Mode Management (Communication Control)
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
 *  Thomas Kuhl                   Pet           Vector Informatik GmbH
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
 *  01.05.01  2012-10-31  Pet                   ESCAN00056202: Memory Mapping section VAR_ZERO_INIT used incorrectly
 *********************************************************************************************************************/
#define VMM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Vmm.h"
#include "Vmm_Dcm.h"
#include "Vmm_BusSM.h"
#include "SchM_Vmm.h"

#if( (!defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )) || (VMM_CRC_CHECK == STD_ON ) )
# include "EcuM_Cbk.h"
#endif

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
#include "Det.h"
#endif

#if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
# include "v_ver.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (VMM_SW_MAJOR_VERSION != (0x01)) \
    || (VMM_SW_MINOR_VERSION != (0x05)) \
    || (VMM_SW_PATCH_VERSION != (0x01)) )
  #error "Vendor specific version numbers of Vmm.c and Vmm.h are inconsistent"
#endif

#if defined (V_EXTENDED_BUILD_LIB_CHECK)
 /**********************************************************************************************************************
 *  BUILD LIB CHECK
 *********************************************************************************************************************/
#  if (VMM_CONFIG_VARIANT == 0x01u)
#    error "Vmm: It is not allowed to create a library with configured confiruration variant PRE-COMPILE!"
#  endif
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/
#define VMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#if ( VMM_DEV_ERROR_DETECT == STD_ON )
STATIC VAR(Vmm_InitStateType, VMM_VAR_ZERO_INIT) Vmm_InitState = 0u;
#endif
#define VMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"    /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
#define VMM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
STATIC VAR(uint16, VMM_VAR_NOINIT) Vmm_ActiveIdentityMask;
#define VMM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define VMM_START_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

CONST(uint8, VMM_CONST) Vmm_MainVersion      = VMM_SW_MAJOR_VERSION;
CONST(uint8, VMM_CONST) Vmm_SubVersion       = VMM_SW_MINOR_VERSION;
CONST(uint8, VMM_CONST) Vmm_ReleaseVersion   = VMM_SW_PATCH_VERSION;

#define VMM_STOP_SEC_CONST_8BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#define VMM_START_SEC_CONST_32BIT
#include "MemMap.h"    /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
CONST( uint32, VMM_CONST ) SYSSERVICE_ASRVMM_LIB_SYMBOL = SYSSERVICE_ASRVMM_LIB_VERSION;
#endif

#define VMM_STOP_SEC_CONST_32BIT
#include "MemMap.h"    /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define VMM_START_SEC_CODE
#include "MemMap.h"   /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

STATIC FUNC(void, VMM_CODE) Vmm_CommControl(NetworkHandleType Channel, Vmm_MsgType msgType, boolean rxState, boolean txState);
STATIC FUNC(void, VMM_CODE) Vmm_SwitchCom(NetworkHandleType Channel, boolean rxState, boolean txState);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

STATIC FUNC(void, VMM_CODE) Vmm_CommControl(NetworkHandleType Channel, Vmm_MsgType msgType, boolean rxState, boolean txState)
{
  switch(msgType)
  {
    case VMM_MSG_TYPE_NM:
      Vmm_SwitchNm(Channel, txState);
      break;
    case VMM_MSG_TYPE_COM:
      Vmm_SwitchCom(Channel, rxState, txState);
      break;

    case VMM_MSG_TYPE_ALL:
      Vmm_SwitchNm(Channel, txState);
      Vmm_SwitchCom(Channel, rxState, txState);
      break;
    default: /* nothing to do */
      break;
  }
}

STATIC FUNC(void, VMM_CODE) Vmm_SwitchCom(NetworkHandleType Channel, boolean rxState, boolean txState)
{
  if(rxState == TRUE)
  {
    /* enable Rx path */
    if(Vmm_ComCtrlComRx[Channel] == TRUE)
    {
      if(Vmm_ComCtrlRxGroup[Channel] != 0xFF)
      {
        Com_IpduGroupStop(Vmm_ComCtrlRxGroup[Channel]);
        Com_DisableReceptionDM(Vmm_ComCtrlRxGroup[Channel]);
      }

      if(Vmm_ComRxState[Channel] == TRUE)
      {
        Com_IpduGroupStart(Vmm_BusSMRxGroup[Channel], Vmm_BusSMInitFlag[Channel]);
        if(Vmm_BusSMDMState[Channel] == TRUE)
        {
          Com_EnableReceptionDM(Vmm_BusSMRxGroup[Channel]);
        }
      }
      else
      {
        /* do nothing */
      }
      Vmm_ComCtrlComRx[Channel] = FALSE;
    }
  }
  else
  {
    /* disable Rx path */
    Com_IpduGroupStop(Vmm_BusSMRxGroup[Channel]);
    Com_DisableReceptionDM(Vmm_BusSMRxGroup[Channel]);

    if(Vmm_ComCtrlRxGroup[Channel] != 0xFF)
    {
      Com_IpduGroupStart(Vmm_ComCtrlRxGroup[Channel], FALSE);
      if(Vmm_BusSMDMState[Channel] == TRUE)
      {
        Com_EnableReceptionDM(Vmm_ComCtrlRxGroup[Channel]);
      }
    }

    Vmm_ComCtrlComRx[Channel] = TRUE;
  }

  if(txState == TRUE)
  {
    /* enable Tx path */
    if(Vmm_ComCtrlComTx[Channel] == TRUE)
    {
      if(Vmm_ComCtrlTxGroup[Channel] != 0xFF)
      {
        Com_IpduGroupStop(Vmm_ComCtrlTxGroup[Channel]);
      }

      if(Vmm_ComTxState[Channel] == TRUE)
      {
        Com_IpduGroupStart(Vmm_BusSMTxGroup[Channel], Vmm_BusSMInitFlag[Channel]);
      }
      else
      {
        /* nothing to do */
      }

      Vmm_ComCtrlComTx[Channel] = FALSE;
    }
  }
  else
  {
    /* disable Tx path */
    Com_IpduGroupStop(Vmm_BusSMTxGroup[Channel]);

    Vmm_ComCtrlComTx[Channel] = TRUE;

    if(Vmm_ComCtrlTxGroup[Channel] != 0xFF)
    {
      Com_IpduGroupStart(Vmm_ComCtrlTxGroup[Channel], FALSE);
    }
  }
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Vmm_InitMemory
 **********************************************************************************************************************/
/*! \brief    Vmm_InitMemory
 *  \context  Function could be called from task level
 *  \note     Pre-Initialization function of Vmm
 **********************************************************************************************************************/
FUNC(void, VMM_CODE) Vmm_InitMemory(void)
{
#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  Vmm_InitState = VMM_INIT_STATE_UNINIT;
#endif
}


/**********************************************************************************************************************
 * Vmm_Init
 **********************************************************************************************************************/
/*! \brief      Vmm_Init
 *  \param[in] 
 *  \pre        Interrupts must be disabled
 *  \context    System Startup
 *  \note       Initilaize the Vmm module.
 **********************************************************************************************************************/
#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
FUNC(void, VMM_CODE)  Vmm_Init( P2CONST(Vmm_ConfigSetType, AUTOMATIC, VMM_CONST) ConfigPtr )
#else
FUNC(void, VMM_CODE)  Vmm_Init( void )
#endif
{
  uint8 index;

#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  if (ConfigPtr == NULL_PTR)
  { 
    Det_ReportError(VMM_MODULE_ID, 0, VVM_INIT_ID, VMM_E_PARAM_POINTER);
  }
#endif
#endif

#if ( VMM_CRC_CHECK == STD_ON )
  if (Vmm_PrecompileCRC != VMM_PRECOMPILE_CRC)
  {
    EcuM_GeneratorCompatibilityError((uint16) VMM_MODULE_ID, (uint8) 0u);
    return;
  }
#endif

#if !defined( V_SUPPRESS_EXTENDED_VERSION_CHECK)
  if(((Vmm_GeneratorVersion & (uint32)0x00FFFF00u)!=
      (((uint32)SYSSERVICE_ASRVMM_GENTOOL_GENY_MAJOR_VERSION<<16) | 
       ((uint32)SYSSERVICE_ASRVMM_GENTOOL_GENY_MINOR_VERSION<<8)))
#  if defined(SYSSERVICE_ASRVMM_GENTOOL_GENY_PATCH_VERSION)
#    if(SYSSERVICE_ASRVMM_GENTOOL_GENY_PATCH_VERSION !=0)
       || ((Vmm_GeneratorVersion & (uint32)0x000000FFu) < SYSSERVICE_ASRVMM_GENTOOL_GENY_PATCH_VERSION)
#    endif
#  endif
       )
  {
    EcuM_GeneratorCompatibilityError((uint16) VMM_MODULE_ID, (uint8) 0);
    return; /* Do not continue with the initialization of the component the Application may be influenced critically. */
  }

#endif

#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  Vmm_ActiveIdentityMask = ConfigPtr->VmmActiveIdentityMask;
#endif

  for(index = 0; index < VMM_ChannelCount; index++)
  {
    Vmm_BusSMInitFlag[index] = FALSE;
    Vmm_ComCtrlComRx[index] = FALSE;
    Vmm_ComCtrlComTx[index] = FALSE;

    Vmm_ComRxState[index] = FALSE;
    Vmm_ComTxState[index] = FALSE;

    Vmm_BusSMDMState[index] = FALSE;
  }

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  Vmm_InitState = VMM_INIT_STATE_INIT;
#endif

}


/**********************************************************************************************************************
 * Vmm_Dcm_CommunicationControl
 **********************************************************************************************************************/
/*! \brief      Vmm_Dcm_CommunicationControl
 *  \param[in]  NetworkHandleType        Channel               network Handle
 *  \param[in]  Vmm_MsgType              msgType               VMM_MSG_TYPE_NM, only NM is affected
                                                               VMM_MSG_TYPE_COM, only Com is affected
                                                               VMM_MSG_TYPE_ALL, Nm and Com are affected
 *  \param[in]  boolean                  rxState               TRUE,  enable Rx path
                                                               FALSE, disable Rx path
 *  \param[in]  boolean                  txState               TRUE,  enable Tx path
                                                               FALSE, disable Tx path
 *  \pre        
 *  \context    Called from the Dcm module
 *  \note       switches off/on the communication in conjunction to the given parameter.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, VMM_CODE) Vmm_Dcm_CommunicationControl( NetworkHandleType Channel, Vmm_MsgType msgType, boolean rxState, boolean txState)
{
  NetworkHandleType VmmChannel;
  Std_ReturnType retValue;

  retValue = E_OK;

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  if (Vmm_InitState == VMM_INIT_STATE_UNINIT)
  { 
    Det_ReportError(VMM_MODULE_ID, 0, VMM_DCM_COMMUNCIATIONCONTROL_ID, VMM_E_UNINIT);
    retValue = E_NOT_OK;
  }
#endif

  SchM_Enter_Vmm(VMM_EXCLUSIVE_AREA_0);

  if(Channel == VMM_ALL_CHANNEL)
  {
    for(VmmChannel = 0; VmmChannel < VMM_ChannelCount; VmmChannel++)
    {
#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((Vmm_IdentityMapping[VmmChannel] & Vmm_ActiveIdentityMask) != 0u)
      {
#endif
        /* ESCAN00030485 */
        Vmm_CommControl(VmmChannel, msgType, rxState, txState);
#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
#endif
    }
  }
  else
  {
    VmmChannel = VMM_BusSMToVmmChannel[Channel];
#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
    if((Vmm_IdentityMapping[VmmChannel] & Vmm_ActiveIdentityMask) != 0u)
    {
#endif
      if(VmmChannel != 0xFF)
      {
        Vmm_CommControl(VmmChannel, msgType, rxState, txState);
      }
#if (VMM_IDENTITY_MANAGER_CONFIG == STD_ON)
    }
#endif
  }

  SchM_Exit_Vmm(VMM_EXCLUSIVE_AREA_0);

  return retValue;
}

/**********************************************************************************************************************
 * Vmm_BusSm_IpduGroupStart
 **********************************************************************************************************************/
/*! \brief      Vmm_BusSm_IpduGroupStart
 *  \param[in]  NetworkHandleType        Channel               network Handle
 *  \param[in]  Com_PduGroupIdType       IpduGroupId           BusSM IPDU group ID
 *  \param[in]  boolean                  Initialize            TRUE,  start with Com default values
                                                               FALSE, start not with Com default values
 *  \pre        
 *  \context    called from BusSM
 *  \note       starts the IPDU group
 **********************************************************************************************************************/
FUNC(void, VMM_CODE) Vmm_BusSm_IpduGroupStart( NetworkHandleType Channel, Com_PduGroupIdType IpduGroupId, boolean Initialize )
{
  NetworkHandleType vmmChannel;

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  if (Vmm_InitState == VMM_INIT_STATE_UNINIT)
  { 
    Det_ReportError(VMM_MODULE_ID, 0, VMM_BUSSM_IPDUGROUPSTART_ID, VMM_E_UNINIT);
  }
#endif

  SchM_Enter_Vmm(VMM_EXCLUSIVE_AREA_0);

  vmmChannel = VMM_BusSMToVmmChannel[Channel];

  if(vmmChannel == (NetworkHandleType)0xFF)
  {
    Com_IpduGroupStart(IpduGroupId, Initialize);
  }
  else
  {
    if(IpduGroupId == Vmm_BusSMRxGroup[vmmChannel])
    {
      if(Vmm_ComCtrlComRx[vmmChannel] == TRUE)
      {
        /* Communication control is active but the Com Rx is disabled
         * store that Rx IPDU group shall be enabled */
        Vmm_BusSMInitFlag[vmmChannel] = Initialize;
      }
      else
      {
        Com_IpduGroupStart(IpduGroupId, Initialize);
      }
      Vmm_ComRxState[vmmChannel] = TRUE;
    }
    else if(IpduGroupId == Vmm_BusSMTxGroup[vmmChannel])
    {
      if(Vmm_ComCtrlComTx[vmmChannel] == TRUE)
      {
        /* Communication control is active but the Com Tx is disabled
         * store that Tx IPDU Group shall be enabled */
        Vmm_BusSMInitFlag[vmmChannel] = Initialize;
      }
      else
      {
        Com_IpduGroupStart(IpduGroupId, Initialize);
      }
      Vmm_ComTxState[vmmChannel] = TRUE;
    }
    else
    {
      /* nothing to do */
    }
  }

  SchM_Exit_Vmm(VMM_EXCLUSIVE_AREA_0);
}

/**********************************************************************************************************************
 * Vmm_BusSm_IpduGroupStop
 **********************************************************************************************************************/
/*! \brief      Vmm_BusSm_IpduGroupStop
 *  \param[in]  NetworkHandleType        Channel               network Handle
 *  \param[in]  Com_PduGroupIdType       IpduGroupId           BusSM IPDU group ID
 *  \pre        
 *  \context    called from BusSM
 *  \note       stops the IPDU group
 **********************************************************************************************************************/
FUNC(void, VMM_CODE) Vmm_BusSm_IpduGroupStop( NetworkHandleType Channel, Com_PduGroupIdType IpduGroupId )
{
  NetworkHandleType vmmChannel;

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  if (Vmm_InitState == VMM_INIT_STATE_UNINIT)
  { 
    Det_ReportError(VMM_MODULE_ID, 0, VMM_BUSSM_IPDUGROUPSTOP_ID, VMM_E_UNINIT);
  }
#endif

  SchM_Enter_Vmm(VMM_EXCLUSIVE_AREA_0);

  vmmChannel = VMM_BusSMToVmmChannel[Channel];

  if(vmmChannel == (NetworkHandleType)0xFF)
  {
    Com_IpduGroupStop(IpduGroupId);
  }
  else
  {
    if(IpduGroupId == Vmm_BusSMRxGroup[vmmChannel])
    {
      if(Vmm_ComCtrlComRx[vmmChannel] == TRUE)
      {
        /* do nothing */
      }
      else
      {
        Com_IpduGroupStop(IpduGroupId);
      }
      Vmm_ComRxState[vmmChannel] = FALSE;
    }
    else if(IpduGroupId == Vmm_BusSMTxGroup[vmmChannel])
    {
      if(Vmm_ComCtrlComTx[vmmChannel] == TRUE)
      {
        /* do nothing */
      }
      else
      {
        Com_IpduGroupStop(IpduGroupId);
      }
      Vmm_ComTxState[vmmChannel] = FALSE;
    }
    else
    {
      /* nothing to do */
    }
  }

  SchM_Exit_Vmm(VMM_EXCLUSIVE_AREA_0);
}


/**********************************************************************************************************************
 * Vmm_BusSm_EnableReceptionDM
 **********************************************************************************************************************/
/*! \brief      Vmm_BusSm_EnableReceptionDM
 *  \param[in]  NetworkHandleType        Channel               network handle
 *  \param[in]  Com_PduGroupIdType       IpduGroupId           BusSM IPDU group ID
 *  \pre        
 *  \context    called from BusSM
 *  \note       enabled deadline monitoring
 **********************************************************************************************************************/
FUNC(void, VMM_CODE) Vmm_BusSm_EnableReceptionDM( NetworkHandleType Channel, Com_PduGroupIdType IpduGroupId)
{
  NetworkHandleType vmmChannel;

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  if (Vmm_InitState == VMM_INIT_STATE_UNINIT)
  { 
    Det_ReportError(VMM_MODULE_ID, 0, VMM_BUSSM_IPDUGROUPSTART_ID, VMM_E_UNINIT);
  }
#endif

  SchM_Enter_Vmm(VMM_EXCLUSIVE_AREA_0);

  vmmChannel = VMM_BusSMToVmmChannel[Channel];

  if(vmmChannel == (NetworkHandleType)0xFF)
  {
    /* Vmm not active on this system channel */
    Com_EnableReceptionDM(IpduGroupId);
  }
  else
  {
    if(IpduGroupId == Vmm_BusSMRxGroup[vmmChannel])
    {
      if(Vmm_ComCtrlComRx[vmmChannel] == FALSE)
      {
        /* com control is inactive, enable BusSM PDU group DM */
        Com_EnableReceptionDM(IpduGroupId);
      }
      else
      {
        /* enable Vmm PDU group DM */
        if(Vmm_ComCtrlRxGroup[vmmChannel] != 0xFF)
        {
          Com_EnableReceptionDM(Vmm_ComCtrlRxGroup[vmmChannel]);
        }
      }
      Vmm_BusSMDMState[vmmChannel] = TRUE;
    }
    else
    {
      /* nothing to do */
    }
  }

  SchM_Exit_Vmm(VMM_EXCLUSIVE_AREA_0);
}

/**********************************************************************************************************************
 * Vmm_BusSm_DisableReceptionDM
 **********************************************************************************************************************/
/*! \brief      Vmm_BusSm_DisableReceptionDM
 *  \param[in]  NetworkHandleType        Channel               network handle
 *  \param[in]  Com_PduGroupIdType       IpduGroupId           BusSM IPDU group ID
 *  \pre        
 *  \context    called from BusSM
 *  \note       disable deadline monitoring
 **********************************************************************************************************************/
FUNC(void, VMM_CODE) Vmm_BusSm_DisableReceptionDM( NetworkHandleType Channel, Com_PduGroupIdType IpduGroupId)
{
  NetworkHandleType vmmChannel;

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  if (Vmm_InitState == VMM_INIT_STATE_UNINIT)
  { 
    Det_ReportError(VMM_MODULE_ID, 0, VMM_BUSSM_IPDUGROUPSTART_ID, VMM_E_UNINIT);
  }
#endif

  SchM_Enter_Vmm(VMM_EXCLUSIVE_AREA_0);

  vmmChannel = VMM_BusSMToVmmChannel[Channel];

  if(vmmChannel == (NetworkHandleType)0xFF)
  {
    Com_DisableReceptionDM(IpduGroupId);
  }
  else
  {
    if(IpduGroupId == Vmm_BusSMRxGroup[vmmChannel])
    {
      if(Vmm_ComCtrlComRx[vmmChannel] == TRUE)
      {
        if(Vmm_ComCtrlRxGroup[vmmChannel] != 0xFF)
        {
          Com_DisableReceptionDM(Vmm_ComCtrlRxGroup[vmmChannel]);
        }
      }
      else
      {
        Com_DisableReceptionDM(IpduGroupId);
      }
      Vmm_BusSMDMState[vmmChannel] = FALSE;
    }
    else
    {
      /* nothing to do */
    }
  }

  SchM_Exit_Vmm(VMM_EXCLUSIVE_AREA_0);
}

#if (VMM_ECU_PASSIVE_HANDLING == STD_ON)
/**********************************************************************************************************************
 * Vmm_Dcm_SetPassiveMode
 **********************************************************************************************************************/
/*! \brief      Vmm_Dcm_SetPassiveMode
 *  \param[in]  boolean                 passiveState          TRUE/FALSE represents the passive state
 *  \pre        
 *  \context    called from DCM
 *  \note       Informs the Vmm about the ECU passive state. The Vmm routes this information to the configured BusSM.
 **********************************************************************************************************************/
FUNC(Std_ReturnType, VMM_CODE) Vmm_Dcm_SetPassiveMode(boolean passiveState)
{
  Std_ReturnType retValue;

  retValue = E_OK;

#if ( VMM_DEV_ERROR_DETECT == STD_ON )
  if (Vmm_InitState == VMM_INIT_STATE_UNINIT)
  { 
    Det_ReportError(VMM_MODULE_ID, 0, VMM_DCM_SETPASSIVEMODE_ID, VMM_E_UNINIT);
    retValue = E_NOT_OK;
  }
#endif

  Vmm_SetPassiveMode(passiveState);

  return retValue;
}
#endif

#define VMM_STOP_SEC_CODE
#include "MemMap.h"    /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: Vmm.C
 *********************************************************************************************************************/
