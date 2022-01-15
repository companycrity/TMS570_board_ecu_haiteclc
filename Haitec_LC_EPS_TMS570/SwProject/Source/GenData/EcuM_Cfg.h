/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2006-2009 by Vector Informatik GmbH, all rights reserved
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EcuM_Cfg.h
 *    Component:  SysService_AsrEcuM
 *       Module:  EcuM
 *    Generator:  EAD
 *
 *  Description:  The ECU State Manager is responsible for
 *                  - initialization of the entire BSW Modules (including OS and RTE
 *                  - configuration of the entire ECU for sleep mode
 *                  - fast and systematic wakeup behavior
 *                  - shutdown of the ECU
 *
 *                To be very independent of different system designs e.g. different Modules to initialize,
 *                external/internal Watchdog, etc., the ECU State Manager provides over a mechanism named "callouts"
 *                a way to adapt the startup and shutdown behavior. The system designer must fill the proper code into
 *                the callouts.
 *********************************************************************************************************************/

/**********************************************************************************************************************
    Bswmd Version : 4.08.00
    Project       : EPS.ecuc
    Generated     : 2013-08-23 10:35 am
    Licensee      : Nexteer Automotive Corporation (2502600608)
 
    This file is generated by DaVinci Configurator Pro - DAVINCICFG.EXE V4.0.67.0.
    Do not modify this file, otherwise the software may behave in unexpected way.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Christian Marchl              Chm           Vector Informatik GmbH
 *  Bethina Mausz                 Bmz           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  03.00.01  2007-09-26  Chm     ESCAN00022372 Quality assurance activities necessary for Component
 *                                              SysService_EcuM
 *  03.00.02  2007-11-21  Chm     ESCAN00023354 No Changes
 *  03.00.03  2007-12-06  Chm     ESCAN00022871 No changes here
 *                                -             Added Revision History
 *                                -             Added generation tag DEM_INCLUDE_FILE. Needed if a Dem is
 *                                              used for test purposes.
 *  04.00.00  2008-03-01  Chm     ESCAN00024563 No Changes here
 *                                ESCAN00023356 No changes here
 *                                ESCAN00024323 No Changes here
 *                                ESCAN00027863 No Changes here
 *  04.00.01  2008-04-16  Chm     ESCAN00026037 No Changes here
 *                                ESCAN00026537 No Changes here
 *                                ESCAN00026471 No changes here
 *  04.01.00  2008-05-15  Chm     -             No Changes here
 *  04.01.01  2008-06-02  Chm     -             No Changes here
 *  04.01.02  2008-06-06  Chm     ESCAN00027459 No Changes here
 *                                ESCAN00027313 No changes here
 *  04.01.03  2008-06-17  Chm     ESCAN00027659 No Changes here
 *  04.02.00  2008-06-30  Chm     ESCAN00027955 Added version defines for generator library version check
 *  04.03.00  2008-07-23  Chm     ESCAN00028372 No Changes here
 *                                ESCAN00028511 No Changes here
 *  04.03.01  2008-08-08  Bmz     -             No changes here
 *  04.03.02  2008-08-13  Bmz     ESCAN00029221 No changes here
 *  04.03.03  2008-09-01  Chm     ESCAN00029621 No changes here
 *                                ESCAN00029300 No changes here
 *  04.03.04  2008-09-24  Chm     ESCAN00027708 No changes here
 *                                ESCAN00029799 No changes here
 *                                ESCAN00029815 No changes here
 *                                ESCAN00029313 No changes here
 *  04.04.00  2008-10-22  Chm     ESCAN00030516 Added PreCompile Variant support
 *  05.00.00  2008-11-28  Chm     ESCAN00031216 No changes here
 *                                ESCAN00031214 Added file EcuM_PrivateCfg.h to component
 *                                ESCAN00030497 No changes here
 *                                ESCAN00030132 No changes here
 *                                ESCAN00031520 Added precompile switch ECUM_GENERATOR_COMPATIBILITY_ERROR
 *                                ESCAN00031786 No changes here
 *                                ESCAN00031787 No changes here
 *  05.01.00  2009-02-19  Chm     ESCAN00032011 No changes here
 *            2009-02-19  Chm     ESCAN00032502 No changes here
 *            2009-02-19  Chm     ESCAN00033069 No changes here
 *            2009-02-20  Chm     ESCAN00031852 No changes here
 *            2009-02-23  Chm     ESCAN00029165 No changes here
 *            2009-02-24  Chm     ESCAN00031789 No changes here
 *            2009-03-04  Chm     ESCAN00033480 No changes here
 *            2009-03-09  Chm     ESCAN00033718 No changes here
 *            2009-03-16  Chm     ESCAN00033834 No changes here
 *  05.02.00  2009-05-19  Chm     ESCAN00035001 No changes here
 *            2009-07-07  Chm     ESCAN00036192 No changes here
 *  05.03.00  2009-07-13  Chm     ESCAN00036369 No changes here
 *            2009-07-13  Chm     ESCAN00036370 No changes here
 *            2009-07-13  Chm     ESCAN00035287 No changes here
 *            2009-07-15  Chm     ESCAN00036441 Add memory section <MSN>_PBCFG_ROOT
 *            2009-07-16  Chm     ESCAN00035917 No changes here
 *            2009-07-16  Chm     ESCAN00035535 No changes here
 *            2009-07-17  Chm     ESCAN00036348 No changes here
 *            2009-07-16  Chm     ESCAN00035536 No changes here
 *            2009-07-21  Chm     ESCAN00034788 No changes here
 *  05.03.01  2009-10-22  Chm     ESCAN00037381 No changes here
 *  05.03.02  2009-12-11  Chm     ESCAN00039720 No changes here
 *            2009-12-11  Chm     ESCAN00037612 No changes here
 *            2009-12-14  Chm     ESCAN00039748 No changes here
 *            2009-12-15  Chm     ESCAN00034936 No changes here
 *            2009-12-21  Chm     ESCAN00039882 No changes here
 *            2010-02-19  Chm     ESCAN00040987 No changes here
 *            2010-02-23  Chm     ESCAN00041075 No changes here
 *  05.03.03  2010-04-14  Chm     ESCAN00041836 No changes here
 *            2010-04-19  Chm     ESCAN00041426 No changes here
 *            2010-04-24  Chm     ESCAN00041446 No changes here
 *            2010-04-24  Chm     ESCAN00041827 No changes here
 *  05.03.04  2010-07-29  Bmz     ESCAN00044245 No changes here
 *            2010-07-29  Bmz     ESCAN00044246 No changes here
 *            2010-07-29  Bmz     ESCAN00043065 No changes here
 *  05.04.00  2010-10-18  Bmz     ESCAN00044990 No changes here
 *                                ESCAN00046061 No changes here
 *  05.06.00  2010-11-26  Bmz     ESCAN00046158 Added new parameter to enable and disable the Rte-AcK mechanism
 *                                ESCAN00047183 No changes here
 *                                ESCAN00047434 No changes here
 *                                ESCAN00045138 No changes here
 *            2011-01-26  Bmz     Prefix generation for DEM-ERRORS inserted in GenerationS.xml
 *                                G601 updated
 *            2011-02-03  Bmz     ESCAN00048364 No changes here
 *  05.06.01  2011-03-14  Bmz     ESCAN00049201 update version number
 *  05.07.00  2011-04-26  Bmz     ESCAN00049111 No changes here
 *  05.07.01  2011-05-12  Bmz     ESCAN00049989 No changes here
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  PUBLIC SECTION
 *********************************************************************************************************************/
#if (!defined ECUM_CFG_H_PUBLIC)
# define ECUM_CFG_H_PUBLIC

/**********************************************************************************************************************
 *  VERSION IDENTIFICATION
 *********************************************************************************************************************/
# define ECUM_CFG_MAJOR_VERSION    (5u)
# define ECUM_CFG_MINOR_VERSION    (7u)
# define ECUM_CFG_PATCH_VERSION    (1u)

# if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
#  define SYSSERVICE_ASRECUM_GENTOOL_EAD_MAJOR_VERSION                ECUM_CFG_MAJOR_VERSION
#  define SYSSERVICE_ASRECUM_GENTOOL_EAD_MINOR_VERSION                ECUM_CFG_MINOR_VERSION
#  define SYSSERVICE_ASRECUM_GENTOOL_EAD_PATCH_VERSION                ECUM_CFG_PATCH_VERSION
# endif

# define ECUM_VARIANT_PRECOMPILE                                      (1)
# define ECUM_VARIANT_POSTBUILD                                       (3)

/***** Pre-compile switches for EcuM configuration and services ******************************************************/
# define ECUM_DEV_ERROR_DETECT                                        /*<ECUM_DEV_ERROR_DETECT/>*/ (STD_ON)
# define ECUM_INCLUDE_DET                                             /*<ECUM_INCLUDE_DET/>*/ (STD_ON)
# define ECUM_INCLUDE_NVRAM_MGR                                       /*<ECUM_INCLUDE_NVRAM_MGR/>*/ (STD_ON)
# define ECUM_INCLUDE_DEM                                             /*<ECUM_INCLUDE_DEM/>*/ (STD_ON)
# define ECUM_INCLUDE_WDGM                                            /*<ECUM_INCLUDE_WDGM/>*/ (STD_OFF)
# define ECUM_INCLUDE_RTE                                             /*<ECUM_INCLUDE_RTE/>*/ (STD_ON)
# define ECUM_INCLUDE_COMM                                            /*<ECUM_INCLUDE_COMM/>*/ (STD_ON)
# define ECUM_INCLUDE_SCHM                                            /*<ECUM_INCLUDE_SCHM/>*/ (STD_OFF)

# define ECUM_MODE_SWITCH_RTE_ACK                                     /*<ECUM_MODE_SWITCH_RTE_ACK/>*/ (STD_OFF)


/* pre-compile switches for module API */
# define ECUM_VERSION_INFO_API                                        /*<ECUM_VERSION_INFO_API/>*/ (STD_OFF)
# define ECUM_KILL_ALL_RUNREQUEST_API                                 /*<ECUM_KILL_ALL_RUNREQUEST_API/>*/ (STD_ON)
# define ECUM_GET_VALIDATED_WAKEUP_EVENTS_API                         /*<ECUM_GET_VALIDATED_WAKEUP_EVENTS_API/>*/ (STD_ON)
# define ECUM_GET_EXPIRED_WAKEUP_EVENTS_API                           /*<ECUM_GET_EXPIRED_WAKEUP_EVENTS_API/>*/ (STD_ON)
# define ECUM_GET_STATUS_OF_WAKEUP_SOURCE_API                         /*<ECUM_GET_STATUS_OF_WAKEUP_SOURCE_API/>*/ (STD_ON)

/* pre-compile switches for callouts */
# define ECUM_ON_RTESTARTUP_CALLOUT                                   /*<ECUM_ON_RTESTARTUP_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_ENTER_RUN_CALLOUT                                    /*<ECUM_ON_ENTER_RUN_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_EXIT_RUN_CALLOUT                                     /*<ECUM_ON_EXIT_RUN_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_EXIT_POST_RUN_CALLOUT                                /*<ECUM_ON_EXIT_POST_RUN_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_PREP_SHUTDOWN_CALLOUT                                /*<ECUM_ON_PREP_SHUTDOWN_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_GO_SLEEP_CALLOUT                                     /*<ECUM_ON_GO_SLEEP_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_GO_OFF_ONE_CALLOUT                                   /*<ECUM_ON_GO_OFF_ONE_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_GO_OFF_TWO_CALLOUT                                   /*<ECUM_ON_GO_OFF_TWO_CALLOUT/>*/ (STD_ON)
# define ECUM_ON_WAKEUP_REACTION_CALLOUT                              /*<ECUM_ON_WAKEUP_REACTION_CALLOUT/>*/ (STD_ON)
# define ECUM_GENERATOR_COMPATIBILITY_ERROR                           /*<ECUM_GENERATOR_COMPATIBILITY_ERROR/>*/ (STD_OFF)

# if (STD_ON == ECUM_DEV_ERROR_DETECT)

#  define ECUM_CHECK_PARAMETER                                        /*<ECUM_CHECK_PARAMETER/>*/ (STD_ON)
#  define ECUM_CHECK_UNINIT                                           /*<ECUM_CHECK_UNINIT/>*/ (STD_ON)

#  if (STD_ON == ECUM_CHECK_PARAMETER)
#   define ECUM_CHECK_USER_PARAMETER                                  /*<ECUM_CHECK_USER_PARAMETER/>*/ (STD_ON)
#   define ECUM_CHECK_CONFIG_TYPE                                     /*<ECUM_CHECK_CONFIG_TYPE/>*/ (STD_ON)
#   define ECUM_CHECK_POINTER_PARAMETER                               /*<ECUM_CHECK_POINTER_PARAMETER/>*/ (STD_ON)
#   define ECUM_CHECK_STATE_PARAMETER                                 /*<ECUM_CHECK_STATE_PARAMETER/>*/ (STD_ON)
#   define ECUM_CHECK_WK_SOURCE_PARAMETER                             /*<ECUM_CHECK_WK_SOURCE_PARAMETER/>*/ (STD_ON)
#   define ECUM_CHECK_BOOT_TARGET_PARAMETER                           /*<ECUM_CHECK_BOOT_TARGET_PARAMETER/>*/ (STD_ON)
#   define ECUM_CHECK_SLEEP_MODE_PARAMETER                            /*<ECUM_CHECK_SLEEP_MODE_PARAMETER/>*/ (STD_ON)
#  else
#   define ECUM_CHECK_USER_PARAMETER                                  (STD_OFF)
#   define ECUM_CHECK_CONFIG_TYPE                                     (STD_OFF)
#   define ECUM_CHECK_POINTER_PARAMETER                               (STD_OFF)
#   define ECUM_CHECK_STATE_PARAMETER                                 (STD_OFF)
#   define ECUM_CHECK_WK_SOURCE_PARAMETER                             (STD_OFF)
#   define ECUM_CHECK_BOOT_TARGET_PARAMETER                           (STD_OFF)
#   define ECUM_CHECK_SLEEP_MODE_PARAMETER                            (STD_OFF)
#  endif

#  define EcuM_Det_Errorhook(EcuM_FunctionId, EcuM_ErrorCode)         /*<ECUM_DET_ERRORHOOK_FUNCTION>*/(Det_ReportError((ECUM_MODULE_ID), (ECUM_INSTANCE_ID), (EcuM_FunctionId), (EcuM_ErrorCode)))/*</ECUM_DET_ERRORHOOK_FUNCTION>*/
# else
#  define ECUM_CHECK_PARAMETER                                        (STD_OFF)
#  define ECUM_CHECK_UNINIT                                           (STD_OFF)
#  define ECUM_CHECK_USER_PARAMETER                                   (STD_OFF)
#  define ECUM_CHECK_CONFIG_TYPE                                      (STD_OFF)
#  define ECUM_CHECK_POINTER_PARAMETER                                (STD_OFF)
#  define ECUM_CHECK_STATE_PARAMETER                                  (STD_OFF)
#  define ECUM_CHECK_WK_SOURCE_PARAMETER                              (STD_OFF)
#  define ECUM_CHECK_BOOT_TARGET_PARAMETER                            (STD_OFF)
#  define ECUM_CHECK_SLEEP_MODE_PARAMETER                             (STD_OFF)
# endif

# define ECUM_TTII_ENABLED                                            /*<ECUM_TTII_ENABLED/>*/ (STD_OFF)

# define ECUM_WKSOURCE_TTII_TIMER                                     /*<ECUM_WKSOURCE_TTII_TIMER/>*/ 

# define ECUM_ENABLE_PROD_ERROR_REPORTING                             /*<ECUM_ENABLE_PROD_ERROR_REPORTING/>*/ (STD_OFF)

# define ECUM_CONFIG_VARIANT                                          /*<ECUM_CONFIG_VARIANT/>*/ (ECUM_VARIANT_PRECOMPILE)

/* Symbols for accessing WdgM modes */
/*<ECUM_WDGM_MODES>*/
/*</ECUM_WDGM_MODES>*/

/*<ECUM_DEFAULT_APP_MODE>*/
#define ECUM_DEFAULT_APP_MODE               (OSDEFAULTAPPMODE)
/*</ECUM_DEFAULT_APP_MODE>*/

/*<ECUM_DEFAULT_SHUTDOWN_TARGET>*/
#define ECUM_DEFAULT_SHUTDOWN_STATE         (ECUM_STATE_OFF)
#define ECUM_DEFAULT_SHUTDOWN_SLEEP_MODE    (0u)
/*</ECUM_DEFAULT_SHUTDOWN_TARGET>*/

/**
 * The following symbolic symbols are only relevant for the implementation variant VARIANT-PRE-COMPILE.
 * If VARIANT-POST-BUILD is selected these values are not relevant. Do not use these values in the
 * application.
 */
/*<ECUM_COMMON_MIN_MAX_VALUES>*/
#define ECUM_MAX_ECUM_USER_COUNT            (2u)
#define ECUM_MAX_USER_COUNT                 (1u)
#define ECUM_MAX_COMM_USER_COUNT            (1u)
#define ECUM_MAX_WAKEUP_SOURCE_VALUE        (256u)
#define ECUM_MAX_SLEEP_MODES                (1u)
#define ECUM_MAX_WAKEUP_SOURCES             (9u)
#define ECUM_MAX_TTII_SLEEP_MODES           (0u)
#define ECUM_SELF_REQUEST_PERIOD            (10u)
/*</ECUM_COMMON_MIN_MAX_VALUES>*/

/*---- API CFG Constants ---------------------------------------------------*/
# define ECUM_START_SEC_CONST_PBCFG_ROOT
# include "MemMap.h"

/*<ECUM_EXTERN_RUNTIME_DECLARATIONS>*/
/*</ECUM_EXTERN_RUNTIME_DECLARATIONS>*/

# define ECUM_STOP_SEC_CONST_PBCFG_ROOT
# include "MemMap.h"

#endif /*  #if (!defined ECUM_CFG_H_PUBLIC) */
/**********************************************************************************************************************
 *  END OF FILE: ECUM_CFG.H
 *********************************************************************************************************************/
