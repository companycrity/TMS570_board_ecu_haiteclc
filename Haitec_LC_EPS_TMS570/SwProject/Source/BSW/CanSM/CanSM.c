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
         File:  CanSM.c
    Component:  CAN State Manager
       Module:  -
    Generator:  -

  Description:  Implementation of the CAN State Manager AUTOSAR Release 3.0
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
  00.01.00  2007-11-05  mfi     -             Initial version
  01.00.00  2008-01-23  mfi     -             ASR 3.0 release version of SWS, CanIf still on ASR 2.1
                                ESCAN00025949 The CanSM isn't affected. The CanSM handles the DEM already in the Lcfg.c (No access on "DEM-events" via DEM created and exported constant values)
  01.01.00  2008-02-04  mfi     ESCAN00024939 New Transition T00 (UNINIT to FULL),
                                ESCAN00024941 Set Transceiver to SILENT only if Controller is in SLEEP
  01.02.00  2008-02-25  mfi     ESCAN00024924 CAN not performs bus-off recovery
  01.03.00  2008-02-28  mfi     ESCAN00024985 Deadline monitoring not active in FULL communication and may be active in NO communication. Switched DL on in T00 and T02. Switched DL off in T03.
  01.04.00  2008-03-03  mfi     ESCAN00025095 Memory Mapping and Compiler Abstraction added
                                ESCAN00025096 Check if the configuration contains same NW index multiple times.
                                ESCAN00024943 The CanSM passes wrong parameter to the ComM. The parameter list in the function calls are switched.
                                ESCAN00025099 Activate Transceiver before Controller
                                ESCAN00025100 Version defines and version checks added/modified
                                ESCAN00025101 Switched API ComM_BusSM_ModeIndication and header file ComM_BusSM.h
                                ESCAN00025111 Adapt CanSM to ASR 3.0 CanIf, CanSM is still able to handle CanIf 2.1 too. API becomes chosen automatically
                                ESCAN00025138 API prototype GetVersionInfo in wrong header file
                                ESCAN00025139 First bus-off recovery time of level 2 may be to short
  01.05.00  2008-03-31  mfi     ESCAN00025653 CA _STATIC_ substituted by ASR 3.0 STATIC; doubled semicolon removed
                                ESCAN00025677 Include all CanSM headers, to check the version number
                                ESCAN00026039 Compiler error "Unrecognized token ';'" issued (... CanSm_Config_Ptr = NULL_PTR;;)
  01.06.00  2008-04-04  mfi     ESCAN00025892 Simplify the set controller mode algorithm of the CanSM
                                ESCAN00025893 Implement a check if E_OK has the value 0
                                ESCAN00025894 Reduce complexity of bus-off value handling
                                ESCAN00025895 Speedup evaluation of the conditions in the bus-off state machine
                                ESCAN00025896 Modified the return value of CanSM_RequestComMode
                                ESCAN00026000 Modify compiler abstraction according Newsletter
                                ESCAN00026001 Extend error handling to the case a transition fails and the mode request changes before recovering of the transition.
                                ESCAN00026002 Add an error counter and a DEM event triggered by the counter
                                ESCAN00026003 MetaStates of BOR SM shifted in NW SM
                                ESCAN00026110 Channel specific transceiver handling
                                ESCAN00026111 Switched form SW number to ASR number to check the version of the CanIf
                                ESCAN00026112 CanSM has defined wrong ASR version number
                                ESCAN00026122 The values of the pre-compile switch CANSM_BOR_DISABLE_RX_DL_MONITORING are interchanged
                                ESCAN00026176 Extension for MSR3.0 LinkTime checks
                                ESCAN00026347 Remove Compiler warning "condition is always true" in CanSM_Init
                                ESCAN00026269 Rename files and #include statements according coding styles
  01.07.00  2008-05-26  mfi     ESCAN00026502 Extension for MSR3.0 generator version checks
                                ESCAN00027533 CanSM don't report a Dem error if error counter exceeded
                                ESCAN00027592 Remove unnecessary if statement
  01.07.01  2008-06-04  mfi     ESCAN00028140 Extension for MSR3.0 generator version checks, changes added (typecast, stop init)
                                ESCAN00028247 The values of the preprocessor switch CanSMBorDisableRxDlMonitoring are switched.
  01.08.00  2008-07-24  mfi     ESCAN00028853 General improvements (pointer to the current channel data; defines instead of explicit value;  remove unused variable)
                                ESCAN00028328 Remove compatibility to CanIf ASR 2.1
                                ESCAN00027977 Resource and Runtime optimization at DET calls
                                ESCAN00028851 CanSM_GetCurrentComMode returns illegal E_NOT_OK
                                ESCAN00029339 Pointer for ComM_BusSM_ModeIndication as parameter
                                ESCAN00029365 Configuration switch "Rx deadline monitoring" changeable at linktime too
                                ESCAN00029501 Boolean type CanSm_IsInitialized changed to uint8
                                ESCAN00028889 The CAN controller not started in second level of the bus-off recovery ==> T07, T13, T12 are similar and joined ==> BOR SM modified
                                ESCAN00028814 Add brackets that CANSM_LeaveCritical and CANSM_EnterCritical look like functions
                                ESCAN00028323 Remove the redundant check CANSM_BOR_CHECK_INIT in Transition T09
                                ESCAN00028885 Resource and Runtime optimization at transceiver calls
  01.09.00  2008-09-23  mfi     ESCAN00030248 Use UpperCamelCase notation for the configuration parameter
                                ESCAN00030000 PreCompile and Linktime CRC check [BR]
                                ESCAN00029792 Resource and Runtime optimization at controller calls
                                ESCAN00030492 CAN bus specific bus-off configuration parameter
                                ESCAN00030619 Add support for the ECU passive mode (CanSM_SetEcuPassive) [022]
                                ESCAN00030656 Remove unused defines
                                ESCAN00030657 Add ASR short name prefix to defines
                                ESCAN00030658 Correct the pointer and memory class in the compiler abstraction macros
                                ESCAN00030659 Remove the init value of UNINIT variable
                                ESCAN00030663 Add compiler abstraction for function local pointers to data defined in the link or post build files
  01.10.00  2008-11-13  mfi     ESCAN00031381 CanSM includes wrong header ("Platform_Types.h" instead Std_Types.h)
                                ESCAN00031377 CanSM uses wrong compiler abstraction
                                ESCAN00031378 Error detection related code not encapsulated in pre-processor switches
                                ESCAN00031582 Deadline Monitoring not started
                                ESCAN00031970 Missing function declaration because of unknown define value
  01.11.00  2009-02-13  mfi     ESCAN00033112 Conditional skip transceiver mode set during initialization [023]
                                ESCAN00033173 Compiler abstraction and memory mapping for local variables are missing.
  01.11.01  2009-03-23  mfi     ESCAN00033501 Compiler Warnings CanSM_TransceiverMode, "CanSM_TransceiverMode" was declared but never referenced
                                ESCAN00034044 Compiler Warning "pointless comparison of unsigned integer with zero"
                                ESCAN00034070 Move CanSM passive mode API into CanSM.h file
                                ESCAN00034158 Wrong memory mapping for pointers to CanSM_LocalClusterDataType variables
  01.12.00  2009-05-27  mfi     ESCAN00034660 The type CanSM_NetworkModeStateType and CanSM_BusOffRecoveryStateType is not implemented correct
                                ESCAN00035004 CAN bus does not react on external wakeup interrupts ==> No repetition if set Trcv mode fail in the transition T03 OR T01
                                ESCAN00035856 CanSM increases the repetition error counter twice if transceiver produces a negative return value in T02
                                ESCAN00036045 Inform the application about a present bus-off [010]
                                ESCAN00036438 Misra violation Rule 5.6; Name Spaces of Identifiers
                                ESCAN00036095 Pre-processor checks for building the library
  01.12.01  2009-09-09  mfi     ESCAN00037693 Dcm throws Det error during initialization of the CanSM
  01.12.02  2009-10-23  mfi     ESCAN00038504 Wrong compiler abstraction
  01.12.03  2010-03-03  mfi     ESCAN00041368 Interrupt locks take very long during state changes
  01.13.00  2010-04-23  mfi     ESCAN00041156 Naming of CanSM functions and macros is inconsistent
  01.14.00  2010-07-13  mfi     ESCAN00043552 Submitted Add support for XCP shutdown
  01.15.00  2010-10-03  mfi     ESCAN00045704 Disable DeadlineMonitoring in state CANSM_SILENT_COMMUNICATION
                                ESCAN00045815 CanSM tries to call missing functions;  encapsulate DM in CANSM_BOR_DISABLE_RX_DL_MONITORING
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

#define CANSM_SOURCE

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
/* PRQA S 0857 NumberOfMacroDefinitions */ /* MD_MSR_1.1 */
#include "CanSM.h"
#include "CanSM_Cbk.h"
#include "CanSM_ComM.h"
#include "CanSM_EcuM.h"
#include "CanSM_SchM.h"

#if ( STD_ON == CANSM_BSWM_COMMODE_INDICATION )
#include "CanSM_BswM.h"
#include "BswM_CanSM.h"
#endif /* if ( STD_ON == CANSM_BSWM_COMMODE_INDICATION ) */

#include "CanIf.h"
#include "ComM_BusSM.h"

/* Maps the critical section handling */
/* interrupts blocked by standard library */
# include "SchM_CanSM.h"
/* interrupts blocked by vector solution */


/* #include "Dem.h shifted to CanSM_Cfg.h needed for the Dem_ReportErrorStatus() and Dem_EventStatusType */

#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
# include "Det.h"
#endif

#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
# include "v_ver.h"
# include "EcuM_Cbk.h"
#elif ( STD_ON == CANSM_CRC_CHECK )
# include "EcuM_Cbk.h"
#endif




/**********************************************************************************************************************
  VERSION CHECK
 **********************************************************************************************************************/

#if ( (0x01u != CANSM_SW_MAJOR_VERSION) || (0x16u != CANSM_SW_MINOR_VERSION) || (0x03u != CANSM_SW_PATCH_VERSION) )
# error "File CanSM.c: Source and CanSM.h file are inconsistent!"
#endif

#if ( (CCL_ASRSMCAN_VERSION != CCL_ASRSMCAN_CALLBACK_HEADER_VERSION) || (CCL_ASRSMCAN_RELEASE_VERSION != CCL_ASRSMCAN_CALLBACK_HEADER_RELEASE_VERSION) )
# error "File CanSM.c: Source and CanSM_Cbk.h file are inconsistent!"
#endif

#if ( (CCL_ASRSMCAN_VERSION != CCL_ASRSMCAN_COMM_HEADER_VERSION) || (CCL_ASRSMCAN_RELEASE_VERSION != CCL_ASRSMCAN_COMM_HEADER_RELEASE_VERSION) )
# error "File CanSM.c: Source and CanSM_ComM.h file are inconsistent!"
#endif

#if ( (CCL_ASRSMCAN_VERSION != CCL_ASRSMCAN_ECUM_HEADER_VERSION) || (CCL_ASRSMCAN_RELEASE_VERSION != CCL_ASRSMCAN_ECUM_HEADER_RELEASE_VERSION) )
# error "File CanSM.c: Source and CanSM_EcuM.h file are inconsistent!"
#endif

#if ( (CCL_ASRSMCAN_VERSION != CCL_ASRSMCAN_SCHM_HEADER_VERSION) || (CCL_ASRSMCAN_RELEASE_VERSION != CCL_ASRSMCAN_SCHM_HEADER_RELEASE_VERSION) )
# error "File CanSM.c: Source and CanSM_SchM.h file are inconsistent!"
#endif

#if ( STD_ON == CANSM_BSWM_COMMODE_INDICATION )
# if ( (CCL_ASRSMCAN_VERSION != CCL_ASRSMCAN_BSWM_HEADER_VERSION) || (CCL_ASRSMCAN_RELEASE_VERSION != CCL_ASRSMCAN_BSWM_HEADER_RELEASE_VERSION) )
#  error "File CanSM.c: Source and CanSM_BswM.h file are inconsistent!"
# endif
#endif /* if ( STD_ON == CANSM_BSWM_COMMODE_INDICATION ) */

#if defined (V_EXTENDED_BUILD_LIB_CHECK)
/**********************************************************************************************************************
 *  BUILD LIB CHECK
 *********************************************************************************************************************/
# if (CANSM_CONFIG_VARIANT == 0x01u )
#  error "CanSM: It is not allowed to create a library with configured configuration variant PRE-COMPILE!"
# endif
#endif

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/




/* CanSM_BusOffRecoveryStateType: States of the internal CanSm bus-off-recovery state machine */
#define CANSM_BOR_IDLE                                                (0x00u)
#define CANSM_BOR_CHECK_INIT                                          (0x01u)
#define CANSM_BOR_TXOFF_L1                                            (0x03u)
#define CANSM_BOR_CHECK_L1                                            (0x04u)
#define CANSM_BOR_TXOFF_L2                                            (0x05u)
#define CANSM_BOR_CHECK_L2                                            (0x06u)


#define CANSM_BOR_NO_BUS_OFF                                          (0x02u)
#define CANSM_BOR_STATE_CHECK                                         CANSM_BOR_CHECK_L1
#define CANSM_BOR_STATE_TXOFF                                         CANSM_BOR_TXOFF_L1


#define CANSM_E_MODE_CHANGE                                           (0x00u)
#define CANSM_E_BUSOFF                                                (0x01u)
#if ( STD_ON == CANSM_TRANSCEIVER_HANDLING )
# define CANSM_E_TRANSCEIVERMODE                                      (0x02u)
#endif



#define CANSM_LAST_TRANSITION_OK                                      (0x00u)

#define CANSM_MAX_VALUE_BOR_COUNTER                                   (0xFFu)

/* CanSm_IsInitialized values */
#define CANSM_INITFUNCTION_NOT_CALLED                                 (0x00u)
#define CANSM_INITFUNCTION_CALLED                                     (0x01u)
#define CANSM_PROCEED_INITIALIZATION                                  (0x02u)


/* Set the CAN Channel to Sleep    during initialization */
#define CANSM_SET_BUS_SLEEP_MODE                                      (0x00u)
#define CANSM_PREVENT_BUS_SLEEP_MODE                                  (0x01u)


/* configuration variant */
#define CANSM_PRE_COMPILE                                             (0x01u)
#define CANSM_LINK_TIME                                               (0x02u)
#define CANSM_POST_BUILD                                              (0x03u)


#define CANSM_CAN_OFFLINE                                             (0x00u)
#define CANSM_CAN_ONLINE                                              (0x01u)

#if ( 0 != E_OK )
# error "The return value E_OK in not 0. The CanSM needs the positive return value equal to zero"
#endif


/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/* (De)activate the production error notification to the Dem */
#if ( STD_ON == CANSM_PROD_ERROR_DETECT )
# define CanSm_DemReportErrorStatus( CanSm_CanNetworkIndex, CanSm_EventId, CanSm_DemStatus ) CanSm_Dem_ReportErrorEvent( (CanSm_CanNetworkIndex), (CanSm_EventId), (CanSm_DemStatus) );   /* PRQA S 3412 */ /* MD_MSR_19.4 */
#else
# define CanSm_DemReportErrorStatus( CanSm_CanNetworkIndex, CanSm_EventId, CanSm_DemStatus )
#endif


#if ( STD_ON == CANSM_BSWM_COMMODE_INDICATION )
/* Activate the  notification to the BswM */
# define BswM_CanSM_Indication( CanSM_CanNetworkIndex, CanSM_ComMode ) BswM_CanSM_CurrentState( (CanSM_CanNetworkIndex), (CanSM_ComMode) );   /* PRQA S 3412 */ /* MD_MSR_19.4 */
#else
/* Deactivate the  notification to the BswM */
# define BswM_CanSM_Indication( CanSm_CanNetworkIndex, CanSM_ComMode )
#endif /* if ( STD_ON == CANSM_BSWM_COMMODE_INDICATION ) */


/* Maps the critical section handling */
/* Critical_0 is used to an automatic state change of the CAN controller and of the CAN transceiver */
/* Critical_1 is used to block a task interrupt by an operating system */
/* interrupts blocked by ASR SchM */
# define CANSM_EnterCritical_1()                                      SchM_Enter_CanSM(CANSM_EXCLUSIVE_AREA_1)
# define CANSM_LeaveCritical_1()                                      SchM_Exit_CanSM(CANSM_EXCLUSIVE_AREA_1)
# define CANSM_EnterCritical_2()                                      SchM_Enter_CanSM(CANSM_EXCLUSIVE_AREA_2)
# define CANSM_LeaveCritical_2()                                      SchM_Exit_CanSM(CANSM_EXCLUSIVE_AREA_2)
# define CANSM_EnterCritical_3()                                      SchM_Enter_CanSM(CANSM_EXCLUSIVE_AREA_3)
# define CANSM_LeaveCritical_3()                                      SchM_Exit_CanSM(CANSM_EXCLUSIVE_AREA_3)
# define CANSM_EnterCritical_4()                                      SchM_Enter_CanSM(CANSM_EXCLUSIVE_AREA_4)
# define CANSM_LeaveCritical_4()                                      SchM_Exit_CanSM(CANSM_EXCLUSIVE_AREA_4)
# define CANSM_EnterCritical_5()                                      SchM_Enter_CanSM(CANSM_EXCLUSIVE_AREA_5)
# define CANSM_LeaveCritical_5()                                      SchM_Exit_CanSM(CANSM_EXCLUSIVE_AREA_5)



/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/


#define CANSM_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
STATIC VAR(uint8, CANSM_VAR_ZERO_INIT) CanSm_IsInitialized = CANSM_INITFUNCTION_NOT_CALLED;
#define CANSM_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */


#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
# define CANSM_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
STATIC VAR(boolean, CANSM_VAR_NOINIT) CanSM_EcuPassiveMode;
# define CANSM_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif /* ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */


#define CANSM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
STATIC P2CONST(CanSM_ConfigType, AUTOMATIC, CANSM_PBCFG) CanSm_Config_Ptr;
#define CANSM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */


#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
# define CANSM_START_SEC_CONST_32BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
CONST(uint32, CANSM_CONST) CCL_ASRSMCAN_LIB_SYMBOL = CCL_ASRSMCAN_LIB_VERSION;   /* PRQA S 3408 */ /* MD_CANSM_8.8 */
# define CANSM_STOP_SEC_CONST_32BIT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define CANSM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */

STATIC FUNC(void, CANSM_CODE) CanSm_NetworkModeStateMachine(P2VAR(CanSM_LocalClusterDataType, AUTOMATIC, CANSM_VAR_NOINIT) CanSm_CurrentClusterDataSetPtr, uint8 CanSm_CanNetworkIdx);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */

/**********************************************************************************************************************
  LOCAL FUNCTIONS
 **********************************************************************************************************************/

#define CANSM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*********************************************************************************************************************
  FUNCTION: CanSm_NetworkModeStateMachine
----------------------------------------------------------------------------------------------------------------------
  API     Type                              Name                            Description
----------------------------------------------------------------------------------------------------------------------
   Input: CanSM_LocalClusterDataType      * CanSm_CurrentClusterDataSetPtr
          uint8                             CanSm_CanNetworkIdx
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: CanSM_RequestComMode
                CanSM_MainFunction (if errors occurred)

  The function realize the network state machine
*********************************************************************************************************************/
STATIC FUNC( void, CANSM_CODE) CanSm_NetworkModeStateMachine( P2VAR( CanSM_LocalClusterDataType, AUTOMATIC, CANSM_VAR_NOINIT) CanSm_CurrentClusterDataSetPtr, uint8 CanSm_CanNetworkIdx )
{
  VAR( Std_ReturnType, AUTOMATIC )              CanSm_StdReturnValue      = E_OK;
  VAR( CanIf_ControllerModeType, AUTOMATIC )    CanSM_CanIfControllerMode = CANIF_CS_UNINIT;
#if ( STD_ON == CANSM_TRANSCEIVER_HANDLING )
  VAR( CanIf_TransceiverModeType, AUTOMATIC )   CanSM_TransceiverMode     = CANIF_TRCV_MODE_SLEEP;
#endif



  /*******************************
   * Network mode state machine
   ******************************/
  /*  T00,T02 + T04 */
  if ( COMM_FULL_COMMUNICATION == (*CanSm_CurrentClusterDataSetPtr).CanSm_RequestedComMode )
  {

    /* Transition T04 ( SILENT to FULL_COM )  Condition: [ CanSM_RequestComMode(return,NetworkHandle,ComM_Mode := COMM_FULL_COMMUNICATION) ] */
    if  (  ( COMM_SILENT_COMMUNICATION == (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState ) &&  ( CANSM_LAST_TRANSITION_OK == (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter )  )
    {
      (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_ONLINE );
      CanSm_SwitchIpduGroup( CanSm_CanNetworkIdx, CANSM_PDU_TX_START );
#if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING )
# if ( STD_ON == CANSM_DISABLE_DM_IN_SILENT_COM )
      CanSm_EnableReceptionDM( CanSm_CanNetworkIdx );
# endif/* if ( STD_ON == CANSM_DISABLE_DM_IN_SILENT_COM ) */
#endif  /* if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING ) */

      (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState   = COMM_FULL_COMMUNICATION;
      BswM_CanSM_Indication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], CANSM_BSWM_FULL_COMMUNICATION )
      ComM_BusSM_ModeIndication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], &((*CanSm_CurrentClusterDataSetPtr).CanSM_CommState) );
#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
      if ( FALSE == CanSM_EcuPassiveMode )
#endif  /* if ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */
      {
        CanSM_Xcp_SetPduMode( CanSm_CanNetworkIdx,  CANSM_CAN_ONLINE );
      }

      /* Transition T16 ( IDLE to CHECK )  Condition: [ " "full communication"   CanSM FullCom RequestedFullCom " ] */
      (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter  = 0;
      (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer    = 0;
      (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState    = CANSM_BOR_STATE_CHECK;

    } /* End Transition T04 ( SILENT to FULL_COM ) */
    /* Transition T02 ( NO to FULL_COM )        Condition: [ state NO_COM && CanSM_RequestComMode(return,NetworkHandle,ComM_Mode := COMM_FULL_COMMUNICATION) ] */
    /* Transition T00 ( UNINITED to FULL_COM )  Condition: [ State UNINIT && CanSM_RequestComMode(return,NetworkHandle,ComM_Mode := COMM_FULL_COMMUNICATION) ] */
    else
    {

#if ( STD_ON == CANSM_TRANSCEIVER_HANDLING )
      if ( TRUE == CanSMNetworkTransceiverHandling[ CanSm_CanNetworkIdx ] )
      {
        CanSm_StdReturnValue += CanIf_GetTransceiverMode( CanSMTransceiverId[ CanSm_CanNetworkIdx ], &CanSM_TransceiverMode );
        if (  CANIF_TRCV_MODE_NORMAL != CanSM_TransceiverMode )
        {
          CanSm_StdReturnValue += CanIf_SetTransceiverMode( CanSMTransceiverId[ CanSm_CanNetworkIdx ], CANIF_TRCV_MODE_NORMAL );
          CanSm_StdReturnValue += CanIf_GetTransceiverMode( CanSMTransceiverId[ CanSm_CanNetworkIdx ], &CanSM_TransceiverMode );
        }
      } /* end if CanSMNetworkTransceiverHandling */
#endif /* end  if ( STD_ON == CANSM_TRANSCEIVER_HANDLING ) */

#if ( STD_ON == CANSM_TRANSCEIVER_HANDLING )
      if (  (  ( E_OK == CanSm_StdReturnValue ) && ( CANIF_TRCV_MODE_NORMAL == CanSM_TransceiverMode )  ) || ( FALSE == CanSMNetworkTransceiverHandling[ CanSm_CanNetworkIdx ] )   )
      {
#endif
        CanSm_StdReturnValue += CanIf_GetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], &CanSM_CanIfControllerMode );

        if ( CANIF_CS_STOPPED == CanSM_CanIfControllerMode )
        {
          CanSm_StdReturnValue += CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STARTED );
          CanSm_StdReturnValue += CanIf_GetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], &CanSM_CanIfControllerMode );
        }
        else if ( CANIF_CS_STARTED != CanSM_CanIfControllerMode )
        {
          CanSm_StdReturnValue += CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STOPPED );
          CanSm_StdReturnValue += CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STARTED );
          CanSm_StdReturnValue += CanIf_GetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], &CanSM_CanIfControllerMode );
        }
        else
        {
          /* desired controller state CANIF_CS_STARTED already reached, nothing to do */
        }

        if (  ( E_OK == CanSm_StdReturnValue ) && ( CANIF_CS_STARTED == CanSM_CanIfControllerMode )  )
        {
          /* Controller is in the estimated state */
          (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_ONLINE );
          CanSm_SwitchIpduGroup( CanSm_CanNetworkIdx, CANSM_PDU_RX_START );
          CanSm_SwitchIpduGroup( CanSm_CanNetworkIdx, CANSM_PDU_TX_START );
#if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING )
          CanSm_EnableReceptionDM( CanSm_CanNetworkIdx );
#endif  /* if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING ) */

          (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter  = CANSM_LAST_TRANSITION_OK;
          (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState         = COMM_FULL_COMMUNICATION;
          BswM_CanSM_Indication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], CANSM_BSWM_FULL_COMMUNICATION )
          ComM_BusSM_ModeIndication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], &((*CanSm_CurrentClusterDataSetPtr).CanSM_CommState) );
#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
          if ( FALSE == CanSM_EcuPassiveMode )
#endif  /* if ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */
          {
            CanSM_Xcp_SetPduMode( CanSm_CanNetworkIdx,  CANSM_CAN_ONLINE );
          }

          /* Transition T16 ( IDLE to CHECK )  Condition: [ " "full communication"   CanSM FullCom RequestedFullCom " ] */
#if ( STD_ON == CANSM_BUSOFF_NOTIFICATION )
          (*CanSm_CurrentClusterDataSetPtr).CanSM_BusOffNotificationCounter = 0;
#endif /* if ( STD_ON == CANSM_BUSOFF_NOTIFICATION ) */
          (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter  = 0;
          (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer    = 0;
          (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState    = CANSM_BOR_STATE_CHECK;

        } /* end if transition successfull, COMM_FULL_COMMUNICATION reached */
        else
        {
          (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter++;
        } /* end if transition failed ==> controller Mode */
#if ( STD_ON == CANSM_TRANSCEIVER_HANDLING )
      } /* end if transceiver has reached desired state */
      else
      {
        (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter++;
        CanSm_DemReportErrorStatus( CanSm_CanNetworkIdx, CANSM_E_TRANSCEIVERMODE, DEM_EVENT_STATUS_FAILED )
      } /* end if transition failed ==> transceiver Mode */
#endif

    } /* End Transition T02 ( NO to FULL_COM ) T00 ( UNINITED to FULL_COM ) */

#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
    if (  ( TRUE == CanSM_EcuPassiveMode ) && ( CANSM_LAST_TRANSITION_OK == (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter )  )
    {
      (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_OFFLINE );
      (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_OFFLINE_ACTIVE );
    } /* end if ECU passive mode is activated */
#endif  /* if ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */

  } /* end if FullCom is requested */
  /* NoCom or Silent is requested */
  else
  {
    /* Transition T05 ( FULL to SILENT_COM )  Condition: [ ! CanSM_RequestComMode(return,NetworkHandle,ComM_Mode := COMM_FULL_COMMUNICATION) ] */
    if ( COMM_FULL_COMMUNICATION == (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState )
    {
      CanSm_SwitchIpduGroup( CanSm_CanNetworkIdx, CANSM_PDU_TX_STOP );
      (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_OFFLINE );

      (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState    = COMM_SILENT_COMMUNICATION;
      ComM_BusSM_ModeIndication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], &((*CanSm_CurrentClusterDataSetPtr).CanSM_CommState) );
      BswM_CanSM_Indication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], CANSM_BSWM_SILENT_COMMUNICATION )
#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
      if ( FALSE == CanSM_EcuPassiveMode )
#endif  /* if ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */
      {
        CanSM_Xcp_SetPduMode( CanSm_CanNetworkIdx,  CANSM_CAN_OFFLINE );
      }
#if ( STD_ON == CANSM_BUSOFF_NOTIFICATION )
      if ( CANSM_BOR_STATE_TXOFF == (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState )
      {
        Appl_CanSM_BusOffEnd( CanSMNetworkHandle[ CanSm_CanNetworkIdx ] ); /* informs application about a recovered busoff */
      } /* end if  state TxOff */
#endif /* if ( STD_ON == CANSM_BUSOFF_NOTIFICATION ) */
      /* Transition T17 ( Meta state: Recovery enabled to IDLE )  Condition: [ No "full communication" ] */
#if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING )
# if ( STD_ON == CANSM_DISABLE_DM_IN_SILENT_COM )
      CanSm_DisableReceptionDM( CanSm_CanNetworkIdx );
# else
      if ( TRUE == CanSMBusOffRxDM[ CanSm_CanNetworkIdx ] )
      {
        CanSm_EnableReceptionDM( CanSm_CanNetworkIdx );
      }
# endif  /* if ( STD_ON == CANSM_DISABLE_DM_IN_SILENT_COM ) */
#endif  /* if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING ) */
    } /* end Transition T05 ( FULL to SILENT_COM )  end BORSM Transition T17 */

    /* NOT in State FULL */
    else
    {
      /* Transition T03 ( SILENT   to NO_COM )  Condition: [ CanSM_RequestComMode(return,NetworkHandle,ComM_Mode := COMM_NO_COMMUNICATION) ] */
      if (  ( COMM_SILENT_COMMUNICATION == (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState ) && ( CANSM_LAST_TRANSITION_OK == (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter )  )
      {
        /* T03 exclusive part */
        CanSm_SwitchIpduGroup( CanSm_CanNetworkIdx, CANSM_PDU_RX_STOP );
#if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING )
# if ( STD_ON == CANSM_DISABLE_DM_IN_SILENT_COM )
        /* DisableReceptionDM already executed in T05 Full to Silent */
# else
        CanSm_DisableReceptionDM( CanSm_CanNetworkIdx );
# endif  /* if ( STD_ON == CANSM_DISABLE_DM_IN_SILENT_COM ) */
#endif  /* if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING ) */
        (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_RX_OFFLINE );
      }
      /* Transition T01 ( UNINITED to NO_COM )  Condition: [ Initialization  ] */
      /* T03 second part */
      if (  ( COMM_SILENT_COMMUNICATION == (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState ) || ( CANSM_LAST_TRANSITION_OK != (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter )  || ( CANSM_PROCEED_INITIALIZATION == CanSm_IsInitialized )  )
      {


        CANSM_EnterCritical_4(); /* CanIR BO */
        if ( TRUE == (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred )
        {
#if ( STD_ON == CANSM_BUSOFF_NOTIFICATION )
          Appl_CanSM_BusOffEnd( CanSMNetworkHandle[ CanSm_CanNetworkIdx ] ); /* informs application about a recovered busoff */
#endif /* if ( STD_ON == CANSM_BUSOFF_NOTIFICATION ) */
          (void)CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STARTED );
        }
        CanSm_StdReturnValue += CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STOPPED );
        CANSM_LeaveCritical_4(); /* CanIR BO */
        (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred = FALSE;

#if ( STD_ON == CANSM_PARTIAL_NETWORK )
        if ( TRUE == (*CanSm_Config_Ptr).CanSM_IsPartialNetworkChannelPtr[ CanSm_CanNetworkIdx ] )
        {
          CANSM_EnterCritical_5(); /* Trcv WU */
          CanSm_StdReturnValue += CanIf_SetTransceiverMode( CanSMTransceiverId[ CanSm_CanNetworkIdx ], CANIF_TRCV_MODE_STANDBY );
          CanSm_StdReturnValue += CanIf_GetTransceiverMode( CanSMTransceiverId[ CanSm_CanNetworkIdx ], &CanSM_TransceiverMode );
          CANSM_LeaveCritical_5(); /* Trcv WU */
          if (  ( E_OK == CanSm_StdReturnValue ) && ( CANIF_TRCV_MODE_STANDBY == CanSM_TransceiverMode )  )
          {
            /* set Trcv mode was successfull */

            CANSM_EnterCritical_4(); /* Ctrl WU */
            CanSm_StdReturnValue += CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_SLEEP );
            CanSm_StdReturnValue += CanIf_GetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], &CanSM_CanIfControllerMode );
            CANSM_LeaveCritical_4(); /* Ctrl WU */
            if (  ( E_OK == CanSm_StdReturnValue ) && ( CANIF_CS_SLEEP == CanSM_CanIfControllerMode )  )
            {

              (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter    = CANSM_LAST_TRANSITION_OK;
            } /* end if controller switched successfully. */
            else
            {
              (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter++;
            } /* end if transition failed ==> Controller Mode */

          } /* end if transceiver switched successfully. NO error occurred in whole transition, switch to next state */
          else
          { /* No repetition if the set transceiver mode fails. Throw DEM fail instead */
            CanSm_DemReportErrorStatus( CanSm_CanNetworkIdx, CANSM_E_TRANSCEIVERMODE, DEM_EVENT_STATUS_FAILED )
            (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter    = CANSM_LAST_TRANSITION_OK;
          } /* end if transition failed ==> transceiver Mode */
        } /* PN Partial Network activated on current channel */
        else
        {
#endif /* if ( STD_ON == CANSM_PARTIAL_NETWORK ) */
          CANSM_EnterCritical_4(); /* Ctrl WU */
          CanSm_StdReturnValue += CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_SLEEP );
          CanSm_StdReturnValue += CanIf_GetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], &CanSM_CanIfControllerMode );
          CANSM_LeaveCritical_4(); /* Ctrl WU */

          if (  ( E_OK == CanSm_StdReturnValue ) && ( CANIF_CS_SLEEP == CanSM_CanIfControllerMode )  )
          {
# if ( STD_ON == CANSM_TRANSCEIVER_HANDLING )
            if ( TRUE == CanSMNetworkTransceiverHandling[ CanSm_CanNetworkIdx ] )
            {
              /* switch the transceiver to STANDBY only if the controller has reached CANIF_CS_SLEEP. */
              CANSM_EnterCritical_5(); /* Trcv WU */
              CanSm_StdReturnValue += CanIf_SetTransceiverMode( CanSMTransceiverId[ CanSm_CanNetworkIdx ], CANIF_TRCV_MODE_STANDBY );
              CanSm_StdReturnValue += CanIf_GetTransceiverMode( CanSMTransceiverId[ CanSm_CanNetworkIdx ], &CanSM_TransceiverMode );
              CANSM_LeaveCritical_5(); /* Trcv WU */
              if (  ( E_OK == CanSm_StdReturnValue ) && ( CANIF_TRCV_MODE_STANDBY == CanSM_TransceiverMode )  )
              {
                /* set Trcv mode was successfull */
              } /* end if transceiver switched successfully. NO error occurred in whole transition, switch to next state */
              else
              { /* No repetition if the set transceiver mode fails. Throw DEM fail instead */
                CanSm_DemReportErrorStatus( CanSm_CanNetworkIdx, CANSM_E_TRANSCEIVERMODE, DEM_EVENT_STATUS_FAILED )
              } /* end if transition failed ==> transceiver Mode */
            } /* end if  TRUE == CanSMNetworkTransceiverHandling[ CanSm_CanNetworkIdx ]  */
# endif /* ( STD_ON == CANSM_TRANSCEIVER_HANDLING ) */
#if ( STD_OFF == CANSM_PARTIAL_NETWORK )
            (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState           = COMM_NO_COMMUNICATION;
            if ( CANSM_INITFUNCTION_CALLED == CanSm_IsInitialized )
            {
              ComM_BusSM_ModeIndication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], &((*CanSm_CurrentClusterDataSetPtr).CanSM_CommState) );
              BswM_CanSM_Indication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], CANSM_BSWM_NO_COMMUNICATION )
            }
# endif /* ( STD_OFF == CANSM_TRANSCEIVER_HANDLING ) */
            (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter    = CANSM_LAST_TRANSITION_OK;

          } /* end if controller switched successfully. */
          else
          {
            (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter++;
          } /* end if transition failed ==> Controller Mode */
#if ( STD_ON == CANSM_PARTIAL_NETWORK )
        } /* PN Partial Network activated on current channel */

        if ( CANSM_LAST_TRANSITION_OK == (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter )
        {
          (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState           = COMM_NO_COMMUNICATION;
          if ( CANSM_INITFUNCTION_CALLED == CanSm_IsInitialized )
          {
            ComM_BusSM_ModeIndication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], &((*CanSm_CurrentClusterDataSetPtr).CanSM_CommState) );
            BswM_CanSM_Indication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], CANSM_BSWM_NO_COMMUNICATION )
          }
        }
#endif        /* end  elif ( STD_ON == CANSM_PARTIAL_NETWORK ) */


      } /* end T01 + T03  */

    } /* end if   NOT in State FULL */

  } /* end if   NoCom or Silent is requested */

#if ( STD_ON == CANSM_PROD_ERROR_DETECT )
  /* The CanSM counts the number of sequenced, failed transitions and reports a DEM error if the specified number is exceeded. */
  if ( CanSMNwSmMaxRepetitions <= (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter )
  {
    CanSm_DemReportErrorStatus( CanSm_CanNetworkIdx, CANSM_E_MODE_CHANGE, DEM_EVENT_STATUS_FAILED )
  }
#endif

} /* end CanSm_NetworkModeStateMachine() */










/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

/*********************************************************************************************************************
  FUNCTION: CanSM_InitMemory
----------------------------------------------------------------------------------------------------------------------
  API     Type                              Name                            Description
----------------------------------------------------------------------------------------------------------------------
   Input: void                              -                               -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: EcuM / Application

     Function to initialize some global variables which has to be set before the Init has been called (e.g. after ECU reset without power up)
*********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_InitMemory( void )
{
  VAR( uint8, AUTOMATIC )              CanSm_CanNetworkIdx;

  /* blocks the calling of API function (except CanSM_Init) */
  CanSm_IsInitialized = CANSM_INITFUNCTION_NOT_CALLED;

  /*lint -e442  -e440 */
  for ( CanSm_CanNetworkIdx = 0; CanSMCountOfCanNetworks > CanSm_CanNetworkIdx; CanSm_CanNetworkIdx++ ) /*lint +e442 +e440 */
  {
    CanSM_EnableSetBusSleep[ CanSm_CanNetworkIdx ] = CANSM_SET_BUS_SLEEP_MODE;
  } /* end for (each CAN channel index) */

} /* end CanSM_InitMemory() */


/*********************************************************************************************************************
  FUNCTION: CanSM_Init
----------------------------------------------------------------------------------------------------------------------
  API     Type                              Name                            Description
----------------------------------------------------------------------------------------------------------------------
   Input: void / CanSM_ConfigType           - / *CanSM_ConfigPtr            configuration data structure (depends on configuration variant)
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: EcuM

  The API function to Initialize the CAN State Manager
*********************************************************************************************************************/
#if ( ( CANSM_POST_BUILD == CANSM_CONFIG_VARIANT ) || ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )  )
FUNC( void, CANSM_CODE ) CanSM_Init(  P2CONST( CanSM_ConfigType, AUTOMATIC, CANSM_PBCFG ) CanSM_ConfigPtr )
{
  VAR( uint8, AUTOMATIC )              CanSm_CanNetworkIdx;

# if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  if ( NULL_PTR != CanSM_ConfigPtr )
  {
# endif
    CanSm_Config_Ptr      = CanSM_ConfigPtr;
    CanSm_IsInitialized   = CANSM_PROCEED_INITIALIZATION;
# if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  }
  /* error parameter CanSM_ConfigPtr is a NULL pointer */
  else
  {
    Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_INIT_SERVICE_ID, CANSM_E_PARAM_POINTER );
    CanSm_IsInitialized   = CANSM_INITFUNCTION_NOT_CALLED;
  }
# endif
 /* end if PostBuild (CANSM_POST_BUILD) configuration OR MultiIdentity (CANSM_IDENTITY_MANAGER_CONFIG)  */
#elif (  ( CANSM_PRE_COMPILE == CANSM_CONFIG_VARIANT ) || ( CANSM_LINK_TIME == CANSM_CONFIG_VARIANT )  )
FUNC( void, CANSM_CODE ) CanSM_Init( void )
{
  VAR( uint8, AUTOMATIC )              CanSm_CanNetworkIdx;

  CanSm_Config_Ptr        = &CanSMConfiguration;
  CanSm_IsInitialized     = CANSM_PROCEED_INITIALIZATION;
#endif /* end if pre-compile (0x01u) OR link time 0x02u) configuration */




#if ( STD_ON == CANSM_CRC_CHECK  )
  if ( (*CanSm_Config_Ptr).CanSMPrecompileCRC != CANSM_PRECOMPILE_CRC )
  {
    EcuM_GeneratorCompatibilityError( (uint16)CANSM_MODULE_ID, (uint8) 0u);
    return; /* PRQA S 2006 */ /* MD_MSR_14.7 */
  }
  if ( (*CanSm_Config_Ptr).CanSMLinktimeCRC != CanSM_LinktimeCRC )
  {
    EcuM_GeneratorCompatibilityError( (uint16)CANSM_MODULE_ID, (uint8) 0u);
    return; /* PRQA S 2006 */ /* MD_MSR_14.7 */
  }
#endif


#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
  /* Check the PBCfg Configuration. The check tests that major and minor version in the library are valid. */
#if ( ( CANSM_POST_BUILD == CANSM_CONFIG_VARIANT ) || ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )  )
  if(    (   ( CanSm_Config_Ptr->CanSMGeneratorVersion & 0x00FFFF00 ) != (  ( (uint32)CCL_ASRSMCAN_GENTOOL_GENY_MAJOR_VERSION<<16 ) | ( (uint32)CCL_ASRSMCAN_GENTOOL_GENY_MINOR_VERSION<<8 )  )   )
#  if defined ( CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION )
#   if ( 0x00u != CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION )
      || (  ( CanSm_Config_Ptr->CanSMGeneratorVersion & 0x000000FF ) < CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION  )
#   endif /* 0x00u == CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION */
#  endif /* if defined ( CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION )  */
    )
# else /* ( CANSM_CONFIG_VARIANT == CANSM_POST_BUILD ) */
  if(    (   ( CanSMConfiguration.CanSMGeneratorVersion & 0x00FFFF00 ) != (  ( (uint32)CCL_ASRSMCAN_GENTOOL_GENY_MAJOR_VERSION<<16 ) | ( (uint32)CCL_ASRSMCAN_GENTOOL_GENY_MINOR_VERSION<<8 )  )   )
#  if defined ( CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION )
#   if ( 0x00u != CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION )
      || (  ( CanSMConfiguration.CanSMGeneratorVersion & 0x000000FF ) < CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION  )
#   endif /* 0x00u == CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION */
#  endif /* if defined ( CCL_ASRSMCAN_GENTOOL_GENY_PATCH_VERSION )  */
    )
# endif /* ( CANSM_CONFIG_VARIANT == CANSM_POST_BUILD ) */
  {
    EcuM_GeneratorCompatibilityError( (uint16)CANSM_MODULE_ID, (uint8) 0u);
    return; /* PRQA S 2006 */ /* MD_MSR_14.7 */
    /* Not continue with the initialization of the component otherwise the Application may be influenced critically. */
  }
#endif /* End Check the PBCfg Configuration. */



#if ( ( CANSM_POST_BUILD == CANSM_CONFIG_VARIANT ) || ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )  )
  if ( CANSM_PROCEED_INITIALIZATION == CanSm_IsInitialized )
  {
#endif /* end if PostBuild configuration. Needed cause of (Tricore) compiler warning: "533/14] condition is always true" */
    /* ConfigurationPointer is valid */


#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )  /*lint -e539 */
    CanSM_EcuPassiveMode                      = FALSE;
#endif /* ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */

    /*lint -e442  -e440 */
    for ( CanSm_CanNetworkIdx = 0; CanSMCountOfCanNetworks > CanSm_CanNetworkIdx; CanSm_CanNetworkIdx++ ) /*lint +e442 +e440 */
    {
#if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )
      if (  0 != ( CanSM_Identitymapping[CanSm_CanNetworkIdx] & (*CanSm_Config_Ptr).CanSM_ActiveIdentityMask )  )
      {
#endif  /* if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG ) */
        P2VAR( CanSM_LocalClusterDataType, AUTOMATIC, CANSM_VAR_NOINIT)  CanSm_CurrentClusterDataSetPtr =   &CanSM_ClusterState[ CanSm_CanNetworkIdx ];

        (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState           = COMM_NO_COMMUNICATION;
        (*CanSm_CurrentClusterDataSetPtr).CanSm_RequestedComMode    = COMM_NO_COMMUNICATION;
        (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred = FALSE;
        (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter    = CANSM_LAST_TRANSITION_OK;

        if ( CANSM_SET_BUS_SLEEP_MODE ==  CanSM_EnableSetBusSleep[ CanSm_CanNetworkIdx ] )
        {
          /* calls NW SM to perform Transition T01 ( UNINITED to NO_COM )  Condition: [ Initialization  ] */
          { /*  enter ExclusiveArea, InterruptsBlocked */
            CanSm_NetworkModeStateMachine( CanSm_CurrentClusterDataSetPtr, CanSm_CanNetworkIdx );
          } /* Exit ExclusiveArea, InterruptsEnabled */
        }
        else
        {
          /* Skip modification of controller and transceiver  */
          (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState           = COMM_NO_COMMUNICATION;
        }
#if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )
      } /* end if  channel is active in current Identity CanSM_Identitymapping  CanSM_ActiveIdentityMask  */
#endif  /* if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG ) */

    } /* end for (each CAN channel index) */

    CanSm_IsInitialized   = CANSM_INITFUNCTION_CALLED;
#if ( ( CANSM_POST_BUILD == CANSM_CONFIG_VARIANT ) || ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )  )
  } /* end if init configuration pointer is valid */     /*lint +e539 */
#endif /* end if PostBuild configuration. Needed cause of compiler warning  "533/14] condition is always true */

} /* PRQA S 2006 */ /* MD_MSR_14.7 */
/* end CanSM_Init() */


/*********************************************************************************************************************
  FUNCTION: CanSM_MainFunction
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: CanSM_LocalClusterDataType  CanSM_ClusterState[]        modifies the actual system state
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: SchM
  Precondition: have to be called cyclically with a cycle time that is shorter than or equal to the CAN cycle.

  The API function executes the state machines, the time and the counter. Basic Software Scheduler directly calls these function.
*********************************************************************************************************************/
FUNC(void, CANSM_CODE) CanSM_MainFunction( void )
{
  VAR( uint8, AUTOMATIC )              CanSm_CanNetworkIdx;


  if ( CANSM_INITFUNCTION_CALLED != CanSm_IsInitialized )
  {
#if ( STD_ON == CANSM_DEV_ERROR_DETECT ) && ( STD_OFF == CANSM_IDENTITY_MANAGER_CONFIG )
    Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_MAINFUNCTION_SERVICE_ID, CANSM_E_UNINIT);
#endif
  }
  else
  {

    /* Performs an independent BOR SM for each CanSm_CanNetworkIdx  and eventually the NW SM too */  /*lint -e442  -e440 */
    for ( CanSm_CanNetworkIdx = 0; CanSMCountOfCanNetworks > CanSm_CanNetworkIdx; CanSm_CanNetworkIdx++ ) /*lint +e442 +e440 */
    {
#if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )
      if (  0 != ( CanSM_Identitymapping[CanSm_CanNetworkIdx] & (*CanSm_Config_Ptr).CanSM_ActiveIdentityMask )  )
      {
#endif  /* if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG ) */
        P2VAR( CanSM_LocalClusterDataType, AUTOMATIC, CANSM_VAR_NOINIT) CanSm_CurrentClusterDataSetPtr =   &CanSM_ClusterState[ CanSm_CanNetworkIdx ];


        if (   ( COMM_SILENT_COMMUNICATION != (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState )  ||  ( FALSE == (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred )    )
        {
          /* Normal case: No BusOffEvent in SilentCom */
        }
        else
        {    /* restart CAN */
          CANSM_EnterCritical_1(); /* Req, Passive */
          if ( COMM_SILENT_COMMUNICATION == (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState ) /* BullsEye covered True but not false; state COMM_SILENT_COMMUNICATION is checked again to avoid interrupt lock, testsuite couldn't produce interrupts  */
          { /*  enter ExclusiveArea, InterruptsBlocked */
            (void)CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STARTED );
          } /* Exit ExclusiveArea, InterruptsEnabled */
          CANSM_LeaveCritical_1();  /* Req, Passive */
          (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred = FALSE;
#if ( STD_ON == CANSM_BUSOFF_NOTIFICATION )
          Appl_CanSM_BusOffEnd( CanSMNetworkHandle[ CanSm_CanNetworkIdx ] ); /* informs application about a recovered busoff */
#endif /* if ( STD_ON == CANSM_BUSOFF_NOTIFICATION ) */
        }

        if (  ( (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState == (*CanSm_CurrentClusterDataSetPtr).CanSm_RequestedComMode ) && ( CANSM_LAST_TRANSITION_OK == (*CanSm_CurrentClusterDataSetPtr).CanSm_NwSmErrorCounter )  )
        {
          /* Normal case: state change already done after mode request, nothing to do */
        }
        else
        {
          CANSM_EnterCritical_1();
          { /*  enter ExclusiveArea, InterruptsBlocked */
            CanSm_NetworkModeStateMachine( CanSm_CurrentClusterDataSetPtr, CanSm_CanNetworkIdx );
          } /* Exit ExclusiveArea, InterruptsEnabled */
          CANSM_LeaveCritical_1();
        }



        /******************************************************************************
         *
         * Bus-off recovery state machine   BOR SM
         *
         ******************************************************************************
         * 1. FullCom ==> Recovery enable
         * 2. state BOR_IDLE handled as a normal Recovery enable state
         * else leave Recovery enable ( if state != BOR_IDLE )
         ******************************************************************************/
        CANSM_EnterCritical_1();
        { /*  enter ExclusiveArea, InterruptsBlocked
because: BOR SM runs preemptive interrupt More Request triggers NW SM, BOR SM continues. e.g. NW MS set controller to CANIF_CS_SLEEP and BOR SM continues T13 and sets controller to CANIF_CS_STARTED */



          if (   ( COMM_FULL_COMMUNICATION != (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState )  ||  (  ( CANSM_BOR_NO_BUS_OFF == (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState ) && ( FALSE == (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred )  )   )
          {
            /* nothing to do in the BOR SM
             *    NW SM is NOT in FullCom   XOR
             *    BOR SM is in StateNoBusOff and No bus-off is available */

            /* if Full_Com NOT active, CANSM_FULL_COMMUNICATION != (*CanSm_CurrentClusterDataSetPtr).CanSm_NetworkState */

            /*******************************************************************
             * Meta state: Recovery DISabled equal to CANSM_BOR_IDLE
             *******************************************************************/

            /* Transition T17 shifted to T05 (StateNoCom ==> StateSilentCom) of the NW SM  */

          }
          /* FullCom AND BOR SM has work to do (recover a new or preceding bus-off) */
          else
          {
            /*******************************************************************
             * Meta state: Recovery enable
             *******************************************************************/

            /* run BOR timer */
            (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer++;


            if ( CANSM_BOR_STATE_TXOFF == (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState )
            {
              /* Transition T11 ( TXOFF_L1 to CHECK_L1 )  Condition: [ Timer >= CanSMBorTimeL1 ] */
              /* Transition T14 ( TXOFF_L2 to CHECK_L2 )  Condition: [ Timer >= CanSMBorTimeL2 ] */
              /* T11, T14 differs in the wait time till they are triggered. To discriminate between between level 1 and 2 the counter value is used. */
              if (   (  ( (*CanSm_Config_Ptr).CanSMBorCounterL1ToL2Ptr[ CanSm_CanNetworkIdx ] > (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter ) &&  ( (*CanSm_Config_Ptr).CanSMBorTimeL1Ptr[ CanSm_CanNetworkIdx ] <= (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer )  ) || (  ( (*CanSm_Config_Ptr).CanSMBorCounterL1ToL2Ptr[ CanSm_CanNetworkIdx ] <= (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter ) && ( (*CanSm_Config_Ptr).CanSMBorTimeL2Ptr[ CanSm_CanNetworkIdx ] <= (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer )  )   )
              {
                /* TX_ONLINE  */
#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
                if ( TRUE == CanSM_EcuPassiveMode )
                {
                  (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_OFFLINE_ACTIVE );
                } /* end if ECU passive mode is activated */
                else
#endif /* ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */
                {
                  (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_ONLINE );
                  CanSM_Xcp_SetPduMode( CanSm_CanNetworkIdx,  CANSM_CAN_ONLINE );
                }

                (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState = CANSM_BOR_STATE_CHECK;
                (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer = 0;
                BswM_CanSM_Indication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], CANSM_BSWM_FULL_COMMUNICATION )
#if ( STD_ON == CANSM_BUSOFF_NOTIFICATION )
                Appl_CanSM_BusOffEnd( CanSMNetworkHandle[ CanSm_CanNetworkIdx ] ); /* informs application about a recovered busoff */
#endif /* if ( STD_ON == CANSM_BUSOFF_NOTIFICATION ) */
                ComM_BusSM_ModeIndication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], &((*CanSm_CurrentClusterDataSetPtr).CanSM_CommState) );

                if ( CANSM_MAX_VALUE_BOR_COUNTER > (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter )
                {
                  (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter++;
                }
              } /* end if TIME Level 1 or 2 expired, end T11  T14 */
            } /* end if  state TxOff */
            else  /* NOT CANSM_BOR_TXOFF_L1 && NOT CANSM_BOR_TXOFF_L2 */
            {
              if ( TRUE == (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred )
              {
                (*CanSm_CurrentClusterDataSetPtr).CanSm_BusOffEventOccurred = FALSE;
                /* Transition T13  ( CHECK_L1 to TXOFF_L1 ) [ counter <  CanSMBorCounterL1ToL2 ] */
                /* Transition T12  ( CHECK_L1 to TXOFF_L2 ) [ counter >= CanSMBorCounterL1ToL2 ] */
                /* Transition T07a ( CHECK_L2 to TXOFF_L2 ) [ counter >= CanSMBorCounterL2Err ] */
                /* Transition T07b ( CHECK_L2 to TXOFF_L2 ) */
                /* Transition T10  ( CHECK to TXOFF_L1 ) */
                /* Transition T06  ( NO_BUS_OFF to TXOFF_L1 ) */

                /* Transition T07b, T07a, T12, T13, T10, T06 Condition: [ Bus-off event ] */
                /* restart CAN */
                (void)CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STOPPED );
                (void)CanIf_SetControllerMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_CS_STARTED );
                (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_OFFLINE );
                (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_RX_ONLINE );
#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
                if ( FALSE == CanSM_EcuPassiveMode )
#endif  /* if ( STD_ON == CANSM_ECU_PASSIVE_MODE ) */
                {
                  CanSM_Xcp_SetPduMode( CanSm_CanNetworkIdx,  CANSM_CAN_OFFLINE );
                }

                /* T07a Dem failed ( second part), COUNTER_L1_TO_L2 threshold has to be exceeded AND COUNTER_L2_TO_ERR threshold has to be exceeded AND counter >= 2 (T11 once and T14 once) */
                if (  ( (*CanSm_Config_Ptr).CanSMBorCounterL2ErrPtr[ CanSm_CanNetworkIdx ] <= (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter ) && ( (*CanSm_Config_Ptr).CanSMBorCounterL1ToL2Ptr[ CanSm_CanNetworkIdx ] < (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter ) && ( 2 <= (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter )  )
                {
                  CanSm_DemReportErrorStatus( CanSm_CanNetworkIdx, CANSM_E_BUSOFF, DEM_EVENT_STATUS_FAILED )
                }     /* end if T07a */

#if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING )
                /* T10, T06 first Bus-off event */
                if (  ( 0 == (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter ) && ( TRUE == CanSMBusOffRxDM[ CanSm_CanNetworkIdx ] )  )
                {
                  CanSm_DisableReceptionDM( CanSm_CanNetworkIdx );
                }   /* end if T10, T06 */
#endif  /* if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING ) */

                (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState    = COMM_SILENT_COMMUNICATION;
                ComM_BusSM_ModeIndication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], &((*CanSm_CurrentClusterDataSetPtr).CanSM_CommState) );
                (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState    = COMM_FULL_COMMUNICATION;

                (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer    = 0;
                (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState    = CANSM_BOR_STATE_TXOFF;
                BswM_CanSM_Indication( CanSMNetworkHandle[ CanSm_CanNetworkIdx ], CANSM_BSWM_BUS_OFF )
              }    /* end   T07b, T07a, T12, T13, T10, T06 */
              else /* NO BO    CANSM_BOR_STATE_CHECK */
              {
                /* State CANSM_BOR_NO_BUS_OFF is excluded above */
                if ( (*CanSm_Config_Ptr).CanSMBorTimeTxEnsuredPtr[ CanSm_CanNetworkIdx ] <= (*CanSm_CurrentClusterDataSetPtr).CanSm_BorTimer )
                {
                  /* Transition T09 ( CHECK to NO_BUS_OFF ) */
                  /* Transition T08 ( CHECK_L1 to NO_BUS_OFF ) */
                  /* Transition T15 ( CHECK_L2 to NO_BUS_OFF ) */
                  /* T09, T08, T15  Condition: [ "No bus-off, timer >= CanSMBorTimeTxEnsured" ] */
                  /* DEM PASS */
                  CanSm_DemReportErrorStatus( CanSm_CanNetworkIdx, CANSM_E_BUSOFF, DEM_EVENT_STATUS_PASSED )

                  /* T08, T15 ( second part)  Bus-off recovered */
                  if ( 0 < (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter )   /* PRQA S 0715 */ /* MD_MSR_1.1 */
                  {
#if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING )
                    /* Enable DM */
                    if ( TRUE == CanSMBusOffRxDM[ CanSm_CanNetworkIdx ] )    /* PRQA S 0715 */ /* MD_MSR_1.1 */
                    {
                      CanSm_EnableReceptionDM( CanSm_CanNetworkIdx );
                    }
#endif  /* if ( STD_ON == CANSM_BOR_DISABLE_RX_DL_MONITORING ) */
                    (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter = 0;
#if ( STD_ON == CANSM_BUSOFF_NOTIFICATION )
                    (*CanSm_CurrentClusterDataSetPtr).CanSM_BusOffNotificationCounter = 0;
#endif /* if ( STD_ON == CANSM_BUSOFF_NOTIFICATION ) */
                  } /* end if T08, T15 */
                  (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState = CANSM_BOR_NO_BUS_OFF;

                }   /* end if BOR_TIME_TX_ENSURED */
              } /* end else if NO BO (T09, T08, T15) */
            }   /* end if TXOFF (T11, T14) */

          } /* end if Full_Com */

          /*******************************************************************
           * end Bus-off recovery state machine   BOR SM
           *******************************************************************/
        } /* Exit ExclusiveArea, InterruptsEnabled */
        CANSM_LeaveCritical_1();


#if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )
      } /* end if  channel is active in current Identity CanSM_Identitymapping  CanSM_ActiveIdentityMask  */
#endif  /* if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG ) */
    } /* end for (each ClusterIdx) */

  } /* MulitID */


} /* end CanSM_MainFunction() */


/*********************************************************************************************************************
  FUNCTION: CanSM_RequestComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType           CanSm_NetworkHandle,        which network/cluster shall be handled
          ComM_ModeType               CanSm_ComM_Mode             which mode the system shall take up
  Output: ComM_ModeType               CanSm_RequestedComMode      modifies the actual system state
  Return: Std_ReturnType              E_OK                        Request was successful
          Std_ReturnType              E_NOT_OK                    Request was not successful, any error occurred
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: ComM
  Precondition: CanSM has to be initialized.

  This API function is used by the ComM to startup or shutdown the communication.
*********************************************************************************************************************/
FUNC( Std_ReturnType, CANSM_CODE ) CanSM_RequestComMode( NetworkHandleType CanSm_NetworkHandle, ComM_ModeType CanSm_ComM_Mode )
{
  P2VAR( CanSM_LocalClusterDataType, AUTOMATIC, CANSM_VAR_NOINIT) CanSm_CurrentClusterDataSetPtr;
  VAR( uint8, AUTOMATIC )                                  CanSm_CanNetworkIdx;
  VAR( Std_ReturnType, AUTOMATIC )                         CanSm_StdReturnValue            = E_NOT_OK;


#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  if ( CANSM_INITFUNCTION_CALLED == CanSm_IsInitialized )
  {
#endif

    /*lint -e442  -e440 */
    for ( CanSm_CanNetworkIdx = 0; CanSMCountOfCanNetworks > CanSm_CanNetworkIdx; CanSm_CanNetworkIdx++ ) /*lint +e442 +e440 */
    {
      if (  CanSMNetworkHandle[ CanSm_CanNetworkIdx ] == CanSm_NetworkHandle )
      {
        CanSm_StdReturnValue                                     =  E_OK;
        CanSm_CurrentClusterDataSetPtr                           = &CanSM_ClusterState[ CanSm_CanNetworkIdx ];
        (*CanSm_CurrentClusterDataSetPtr).CanSm_RequestedComMode =  CanSm_ComM_Mode;

        if ( (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState != (*CanSm_CurrentClusterDataSetPtr).CanSm_RequestedComMode )
        {
          CANSM_EnterCritical_2();
          { /*  enter ExclusiveArea, InterruptsBlocked */
            CanSm_NetworkModeStateMachine( CanSm_CurrentClusterDataSetPtr, CanSm_CanNetworkIdx );
          } /* Exit ExclusiveArea, InterruptsEnabled */
          CANSM_LeaveCritical_2();
        }

        break;

      } /* NetworkHandle index in list ==> NetworkHandle valid  */
    } /* end search for (each ClusterIdx) of current network handle */


#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
    if ( E_OK == CanSm_StdReturnValue )
    {
      /* NetworkHandle found in the array CanSMNetworkHandle[] */
    }
    else
    {
      /* error parameter NetworkHandle is NOT VALID because CanSm_StdReturnValue was not modified to E_OK */
      Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_REQUESTCOMMODE_SERVICE_ID, CANSM_E_INVALID_NETWORK_HANDLE );
    }

  }
  /* error CanSm InitFunction not called */
  else
  {
    Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_REQUESTCOMMODE_SERVICE_ID, CANSM_E_UNINIT );
  }
#endif /* end if ( STD_ON == CANSM_DEV_ERROR_DETECT ) */

  return  CanSm_StdReturnValue;

} /* end CanSM_RequestComMode() */


/*********************************************************************************************************************
  FUNCTION: CanSM_GetCurrentComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType           CanSm_NetworkHandle         Which network/cluster shall be handled
          ComM_ModeType               ComM_ModePtr                Pointer to the memory location where the current communication mode shall be stored
  Output: -
  Return: Std_ReturnType              E_OK                        Request was successful
          Std_ReturnType              E_NOT_OK                    Request was not successful, any error occurred
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer BSW
  Precondition: CanSM has to be initialized.

  This API function reports the current communication mode of the specified network.
*********************************************************************************************************************/
FUNC( Std_ReturnType, CANSM_CODE ) CanSM_GetCurrentComMode( NetworkHandleType CanSm_NetworkHandle, P2VAR( ComM_ModeType, AUTOMATIC, CANSM_APPL_VAR ) ComM_ModePtr)
{
  VAR( uint8, AUTOMATIC )                       CanSm_CanNetworkIdx;
  VAR( Std_ReturnType, AUTOMATIC )              CanSm_StdReturnValue      = E_NOT_OK;

#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  if ( CANSM_INITFUNCTION_CALLED == CanSm_IsInitialized )
  {
    if ( NULL_PTR != ComM_ModePtr )
    {
#endif /* end if ( STD_ON == CANSM_DEV_ERROR_DETECT ) */
      /*lint -e442 -e440 */
      for ( CanSm_CanNetworkIdx = 0; CanSMCountOfCanNetworks > CanSm_CanNetworkIdx; CanSm_CanNetworkIdx++ ) /*lint +e442 +e440 */
      {
        if (  CanSMNetworkHandle[ CanSm_CanNetworkIdx ] == CanSm_NetworkHandle )
        {

          CanSm_StdReturnValue   = E_OK;

          if ( CANSM_BOR_STATE_TXOFF !=  CanSM_ClusterState[ CanSm_CanNetworkIdx ].CanSm_BorState )
          {
            *ComM_ModePtr = CanSM_ClusterState[ CanSm_CanNetworkIdx ].CanSM_CommState;
          }
          else
          {
            *ComM_ModePtr = COMM_SILENT_COMMUNICATION;
          }

          break;
        } /* NetworkHandle index in list  */
      } /* end search for (CanNetworkIdx) of current network handle */


#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
      if ( E_OK == CanSm_StdReturnValue )
      {
        /* NetworkHandle found in the array CanSMNetworkHandle[] */
      }
      else
      {
        /* error parameter NetworkHandle is NOT VALID */
        Det_ReportError( CANSM_MODULE_ID,  CANSM_INSTANCE_ID, CANSM_GETCURRENTCOMMODE_SERVICE_ID, CANSM_E_INVALID_NETWORK_HANDLE );
      }

    } /* end if NO NULL pointer */
    /* error parameter ComM_ModePtr is a NULL pointer */
    else
    {
      Det_ReportError( CANSM_MODULE_ID,  CANSM_INSTANCE_ID, CANSM_GETCURRENTCOMMODE_SERVICE_ID, CANSM_E_PARAM_POINTER );
    } /* end else of    if ( NULL_PTR != ComM_ModePtr ) */
  }  /* end if ( CANSM_INITFUNCTION_CALLED == CanSm_IsInitialized ) */
  else
  {
    Det_ReportError( CANSM_MODULE_ID,  CANSM_INSTANCE_ID, CANSM_GETCURRENTCOMMODE_SERVICE_ID, CANSM_E_UNINIT );
  }   /* error CanSm InitFunction not called */
#endif /* end if ( STD_ON == CANSM_DEV_ERROR_DETECT ) */

  return  CanSm_StdReturnValue;

} /* end CanSM_GetCurrentComMode() */


/*********************************************************************************************************************
  FUNCTION: CanSM_ControllerBusOff
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
  Input:  uint8                       CanSm_ControllerId
  Output: CanSm_BusOffEventType       CanSm_BusOffEventOccurred   modifies the actual system state
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: CanIf

  This API function is used to notify the CanSM about a bus-off event
*********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_ControllerBusOff( uint8 CanSm_ControllerId )
{

#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  if ( CANSM_INITFUNCTION_CALLED == CanSm_IsInitialized )
  {
    if ( CanSMCountOfCanNetworks > CanSm_ControllerId )
    {
      /* NO error found */
#endif
      CanSM_ClusterState[ CanSm_ControllerId ].CanSm_BusOffEventOccurred = TRUE;
#if ( STD_ON == CANSM_BUSOFF_NOTIFICATION )
      if ( CANSM_MAX_VALUE_BOR_COUNTER > CanSM_ClusterState[ CanSm_ControllerId ].CanSM_BusOffNotificationCounter )
      {
        CanSM_ClusterState[ CanSm_ControllerId ].CanSM_BusOffNotificationCounter++;
      }
      Appl_CanSM_BusOffBegin( CanSMNetworkHandle[ CanSm_ControllerId ], CanSM_ClusterState[ CanSm_ControllerId ].CanSM_BusOffNotificationCounter ); /* callback informs application about a occurred busoff */
#endif /* if ( STD_ON == CANSM_BUSOFF_NOTIFICATION ) */

#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
    }
    /* error parameter ControllerId is out of range */
    else
    {
      Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_CONTROLLERBUSOFF_SERVICE_ID, CANSM_E_PARAM_CONTROLLER );
    }
  }
  /* error CanSm InitFunction not called */
  else
  {
    Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_CONTROLLERBUSOFF_SERVICE_ID, CANSM_E_UNINIT );
  }
#endif /* end if ( STD_ON == CANSM_DEV_ERROR_DETECT ) */

} /* end CanSM_ControllerBusOff() */



#if ( STD_ON == CANSM_VERSION_INFO_API )
/*********************************************************************************************************************
  FUNCTION: CanSM_GetVersionInfo
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
   Input: Std_VersionInfoType         *versioninfo                Pointer to where to store the version information of this module.
  Output:
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: CanSm has to be initialized.

  This service returns the version information of this module. The version information includes:
  - Module Id
  - Vendor Id
  - Vendor specific version numbers (BSW00407).
*********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CANSM_APPL_VAR ) versioninfo )
{

# if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  if ( NULL_PTR != versioninfo )
  {
# endif
    (*versioninfo).vendorID         = (uint16)CANSM_VENDOR_ID;
    (*versioninfo).moduleID         =  (uint8)CANSM_MODULE_ID;
    (*versioninfo).sw_major_version =  (uint8)CANSM_SW_MAJOR_VERSION;
    (*versioninfo).sw_minor_version =  (uint8)CANSM_SW_MINOR_VERSION;
    (*versioninfo).sw_patch_version =  (uint8)CANSM_SW_PATCH_VERSION;
# if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  }
  /* error parameter versioninfo is a NULL pointer */
  else
  {
    Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_GETVERSIONINFO_SERVICE_ID, CANSM_E_PARAM_POINTER );
  }
# endif /* end if ( STD_ON == CANSM_DEV_ERROR_DETECT ) */


} /* end CanSM_GetVersionInfo() */
#endif


#if ( STD_ON == CANSM_ECU_PASSIVE_MODE )
/*********************************************************************************************************************
  FUNCTION: CanSM_SetEcuPassive
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
   Input: boolean           CanSM_TxOfflineActive         Which network/cluster shall be handled
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer BSW
  Precondition: CanSM has to be initialized.

  This API function notifies the CanSM if ECU has to be set in passive mode
*********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_SetEcuPassive( boolean CanSM_TxOfflineActive )
{
  VAR( uint8, AUTOMATIC )                                  CanSm_CanNetworkIdx;


  /*lint -e442  -e440 */
  for ( CanSm_CanNetworkIdx = 0; CanSMCountOfCanNetworks > CanSm_CanNetworkIdx; CanSm_CanNetworkIdx++ ) /*lint +e442 +e440 */
  {
#if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )
    if (  0 != ( CanSM_Identitymapping[CanSm_CanNetworkIdx] & (*CanSm_Config_Ptr).CanSM_ActiveIdentityMask )  )
    {
#endif  /* if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG ) */
      P2VAR( CanSM_LocalClusterDataType, AUTOMATIC, CANSM_VAR_NOINIT) CanSm_CurrentClusterDataSetPtr =   &CanSM_ClusterState[ CanSm_CanNetworkIdx ];

      CANSM_EnterCritical_3();
      if (  ( COMM_FULL_COMMUNICATION == (*CanSm_CurrentClusterDataSetPtr).CanSM_CommState ) && ( 0 == (*CanSm_CurrentClusterDataSetPtr).CanSm_BorCounter ) && ( CANSM_BOR_STATE_TXOFF != (*CanSm_CurrentClusterDataSetPtr).CanSm_BorState ) && ( CanSM_TxOfflineActive != CanSM_EcuPassiveMode )  )
      { /* BOR SM not running a recovery, State IS ONLINE, PASSIVE mide is changed */

        if ( TRUE == CanSM_TxOfflineActive )
        { /* Activate ECU passive mode immediately */
          (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_OFFLINE );
          (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_OFFLINE_ACTIVE );
        }
        else
        { /* DeActivate ECU passive mode immediately */
          (void)CanIf_SetPduMode( CanSMControllerId[ CanSm_CanNetworkIdx ], CANIF_SET_TX_ONLINE );
        }

        CanSM_Xcp_SetPduMode( CanSm_CanNetworkIdx,  CanSM_EcuPassiveMode ); /* CANXCP_SET_OFFLINE = 0, CANXCP_SET_ONLINE 1 */

      }    /* end if full Com && BOR SM not running a recovery */
      CANSM_LeaveCritical_3();

      /* else If NOT FullCom XOR bus-off recovery is running ==> */
      /* T02 and T04: If(CanSM_TxOfflineActive) CanIf_SetPduMode CANIF_SET_RX_ONLINE, CANIF_SET_TX_OFFLINE, CANIF_SET_TX_OFFLINE_ACTIVE */
      /* T11 and T14: If(CanSM_TxOfflineActive) CanIf_SetPduMode CANIF_SET_TX_OFFLINE_ACTIVE */

#if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG )
    } /* end if  channel is active in current Identity CanSM_Identitymapping  CanSM_ActiveIdentityMask  */
#endif  /* if ( STD_ON == CANSM_IDENTITY_MANAGER_CONFIG ) */
  } /* end for (each CAN channel index) */



  CanSM_EcuPassiveMode = CanSM_TxOfflineActive;


} /* end CanSM_SetEcuPassive() */
#endif /* STD_ON == CANSM_ECU_PASSIVE_MODE  */


/*********************************************************************************************************************
  FUNCTION: CanSM_PreventBusSleepAtStartUp
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType           CanSm_NetworkHandle         Specifies the communication channel
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: EcuM
  Precondition: CanSM_Init must NOT be initialized.

  This API function receives network handle of the CAN channel which must NOT set to sleep during the initialization
*********************************************************************************************************************/
FUNC( Std_ReturnType, CANSM_CODE ) CanSM_PreventBusSleepAtStartUp( NetworkHandleType CanSM_NetworkHandle )
{
  VAR( uint8, AUTOMATIC )                       CanSm_CanNetworkIdx;
  VAR( Std_ReturnType, AUTOMATIC )              CanSm_StdReturnValue      = E_NOT_OK;


#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
  if ( CANSM_INITFUNCTION_NOT_CALLED == CanSm_IsInitialized )
  {
#endif

    /*lint -e442  -e440 */
    for ( CanSm_CanNetworkIdx = 0; CanSMCountOfCanNetworks > CanSm_CanNetworkIdx; CanSm_CanNetworkIdx++ ) /*lint +e442 +e440 */
    {
      if ( CanSMNetworkHandle[ CanSm_CanNetworkIdx ] == CanSM_NetworkHandle )
      {
        CanSM_EnableSetBusSleep[ CanSm_CanNetworkIdx ] = CANSM_PREVENT_BUS_SLEEP_MODE;
        CanSm_StdReturnValue                           = E_OK;
      } /* NetworkHandle index in list ==> NetworkHandle valid => E_OK */
    } /* end search for (each ClusterIdx) of current network handle */

#if ( STD_ON == CANSM_DEV_ERROR_DETECT )
    if ( E_OK == CanSm_StdReturnValue )
    {
      /* NetworkHandle found in the array CanSMNetworkHandle[] */
    }
    else
    {
      /* error parameter NetworkHandle is NOT VALID because CanSm_StdReturnValue was not modified to E_OK */
      Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_PREVENTBUSSLEEPATSTARTUP_SERVICE_ID, CANSM_E_INVALID_NETWORK_HANDLE );
    }

  }
  /* error CanSM InitFunction allready called */
  else
  {
    Det_ReportError( CANSM_MODULE_ID, CANSM_INSTANCE_ID, CANSM_PREVENTBUSSLEEPATSTARTUP_SERVICE_ID, CANSM_E_INITLIZED );
  }
#endif /* end if ( STD_ON == CANSM_DEV_ERROR_DETECT ) */

  return CanSm_StdReturnValue;

} /* end CanSM_PreventBusSleepAtStartUp() */


#define CANSM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* PRQA L:NumberOfMacroDefinitions */ /* MD_MSR_1.1 */

/*******************************************************************************
 * Organi check
 *******************************************************************************/

/* module specific MISRA deviations:
MD_CANSM_8.8
    Reason:     Implemented according basic design spec. The warnig " 'CCL_ASRSMCAN_LIB_SYMBOL' has external linkage but is being defined without any previous declaration" is caused by stub test enviroment.
    Risk:       none
    Prevention: Covered by code review.
MD_CANSM_8.12
    Reason:     Avoid libraries with arrays which contains only one single element caused by compiler optimization.
    Risk:       none
    Prevention: Covered by code review.
*/





/**********************************************************************************************************************
  END OF FILE: CanSM.c
 **********************************************************************************************************************/
/*  *****   STOPSINGLE_OF_MULTIPLE_COMMENT    *****  */
