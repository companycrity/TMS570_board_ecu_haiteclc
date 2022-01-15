/* -----------------------------------------------------------------------------
  Filename:    Dcm.c
  Description: Implementation of DCM.

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2008-2012 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
    &&&~ History
 ----------------------------------------------------------------------------- */

/* 
------------------------------------------------------------------------------------------------------------------------
                                             A U T H O R   I D E N T I T Y                                              
------------------------------------------------------------------------------------------------------------------------
Initials   Name                  Company                                                                                
---------- --------------------- ---------------------------------------------------------------------------------------
Sa         Mishel Shishmanyan    Vector Informatik GmbH                                                                 
------------------------------------------------------------------------------------------------------------------------
                                            R E V I S I O N   H I S T O R Y                                             
------------------------------------------------------------------------------------------------------------------------
Date       Version  Author Modification type Issue Id      Affects                        Description                    
---------- -------- ------ ----------------- ------------- ------------------------------ -------------------------------
2009-12-01  4.00.00
                    Sa     Fixed             ESCAN00039649 All                            Compile error: Dcm_TriggerTransmit does not use compiler abstraction on local pointer declaration
                    Sa     Fixed             ESCAN00039574 All                            Compiler error for strict compiler options
                    Sa     Modified          ESCAN00039310 All                            Optimized repeater proxy RAM and ROM usage
                    Sa     Modified          ESCAN00040718 All                            Service 0x2F added for DID access synchronisation
                    Sa     Modified          ESCAN00040719 All                            Migration from ISO 14229-1:2006 to ISO 14229-1.7 2009
                    Sa     Modified          ESCAN00040606 All                            Allow return value "E_NOT_OK" for all "DidServices" port interfaces "ReadData" operation
                    Sa     Added             ESCAN00040586 All                            Generate DCM configuration files only on relevant changes
2010-04-30  4.01.00
                    Sa     Added             ESCAN00041773 Vector(UDS)                    Support memory service 0x23 and 0x3D without memory range check
                    Sa     Fixed             ESCAN00042621 All                            Compiler warnings for unreachable statement in Dcm_CheckServiceStateMatch
                    Sa     Fixed             ESCAN00042628 All                            Dynamic FID support does not consider maximum internally supported address and size data type sizes
                    Sa     Fixed             ESCAN00042630 All                            Dynamic FID support does not allow more than 2 byte for memory block size parameter
                    Sa     Fixed             ESCAN00041857 All                            Service 0x22 does not accept any valid DID if service 0x27 is not supported at all
                    Sa     Fixed             ESCAN00041741 All                            Compiler warning stdReturn was set but never used
                    Sa     Fixed             ESCAN00041742 All                            Compiler warning pointless comparison of unsigned integer with zero
                    Sa     Fixed             ESCAN00042365 All                            Service 0x19 0x04/0x05 responded with NRC 0x31 if no DTC FreezeFrame-/SnapshotData is stored
                    Sa     Fixed             ESCAN00042376 All                            Service 0x19 does not enable DTCRecordUpdate if requested with SPRMIB==TRUE
                    Sa     Fixed             ESCAN00042003 All                            Wrong P2 times monitored       
                    Sa     Fixed             ESCAN00042399 All                            Diagnostic instances of services 0x23/0x3D are considered for diagnostic buffer calculation
                    Sa     Modified          ESCAN00042633 All                            Minor run-time optimization of DEM API iterations
                    Sa     Modified          ESCAN00042833 All                            Service 0x28 shall always ignore the reserved bits for message group in the ComParamType
2010-07-26  4.02.00
                    Sa     Fixed             ESCAN00043556 Vector(UDS)                    Compile warning on truncated constant value if service 0x27 not supported in a link-time configuration
                    Sa     Fixed             ESCAN00044188 All                            Compile error invalid inline function usage
                    Sa     Fixed             ESCAN00042644 All                            compiler warning "condition is always true" for if(E_OK == stdResult)
2010-08-10  4.03.00
                    Sa     Fixed             ESCAN00043327 Vector(UDS)                    Compiler Warning for condition always true in Dcm_DspPostReadDataByPeriodicId
                    Sa     Fixed             ESCAN00042645 Vector(UDS)                    Compiler warning "condition is always true" for if(DCM_E_OK == dcmDsdErrorRegister)
                    Sa     Fixed             ESCAN00044671 All                            Service 0x2F responds with NRC 0x31 in precompiled multi variant configuration
                    Sa     Added             ESCAN00043881 All                            Support Unknown Diagnostic Services
2010-10-27  4.04.00
                    Sa     Fixed             ESCAN00045890 Vector(UDS)                    Compile warning:dcm_DebugImplOemId and dcm27_ConfigTypeLib unused
                    Sa     Fixed             ESCAN00046485 Vector(UDS)                    Wrong periodic transmissions on concurrent multi UDS tester environment
                    Sa     Modified          ESCAN00044821 Vector(UDS)                    Optimize periodic connection owner check on single connection configurations
                    Sa     Fixed             ESCAN00045900 All                            Compiler warning: Useless assignment to variable
                    Sa     Fixed             ESCAN00044898 All                            Compile error for missing data type definitions Dcm_ReturnReadMemoryType and Dcm_ReturnWriteMemoryType
                    Sa     Modified          ESCAN00046464 All                            Changed DEM AR version check   
                    Sa     Modified          ESCAN00046467 All                            Optimized DSL transport object management
2010-11-30  4.05.00
                    Sa     Added             ESCAN00046806 Vector(UDS)                    Support HIS FBL interaction    
                    Sa     Fixed             ESCAN00044108 All                            DCM does not fully support split task concept with different task priorities for the timer and state tasks
                    Sa     Fixed             ESCAN00047989 All                            Functional request causes Physical Request to be discontinued
                    Sa     Fixed             ESCAN00048294 All                            Wrong NRC handling on requests's minimum length check
                    Sa     Modified          ESCAN00045441 All                            Improvement of MISRA compliance (AR3-962)
                    Sa     Modified          ESCAN00048097 All                            Pre-compile time code optimization if no hard reset functionality is needed
                    Sa     Modified          ESCAN00048237 All                            Improved memory mapping on external callbacks
                    Sa     Added             ESCAN00046237 All                            Adapt AUTOSAR version check    
2011-04-30  4.06.00
                    Sa     Fixed             ESCAN00050421 Vector(UDS)                    Service 0x2A might not accept request from another tester in a multi client environment
                    Sa     Modified          ESCAN00050424 Vector(UDS)                    Callout Dcm_CheckMemory will not be called for zero memory size or memory range overflow requests
                    Sa     Fixed             ESCAN00050420 All                            Service 0x2C can not append multiple address definitions in a single request
                    Sa     Modified          ESCAN00050348 All                            Improved reliability of SID 0x2F and 0x31 processors
                    Sa     Modified          ESCAN00049673 All                            Improve robustness by initializing all local variables
                    Sa     Modified          ESCAN00050349 All                            Minor run time and code optimizations
                    Sa     Modified          ESCAN00050434 All                            Make number of identities link-time capable
                    Sa     Added             ESCAN00050425 All                            Service 0x19 with SPRMIB=1 will first send RCR-RP response, then final positive response
                    Sa     Added             ESCAN00050426 All                            General services NRC handling update to match ISO 14229-1 2010
2011-05-05  4.07.00
                    Sa     Fixed             ESCAN00050877 Vector(UDS)                    Compile error on MCS12 COSMIC if OBD2 support enabled
                    Sa     Added             ESCAN00050880 Vector(UDS)                    OBD2 support                   
                    Sa     Fixed             ESCAN00050940 All                            Dcm accepts a 'send key' request after a zero seed positive response on an already unlocked security level
2011-11-22  4.07.01
                    Sa     Fixed             ESCAN00054517 Vector(UDS)                    Memory overwritten if SID 0x2A is not supported in a DCM library configuration
                    Sa     Fixed             ESCAN00054077 Vector(UDS)                    DCM supports only TID and not OBDMID-TID specific application calls and UASIDs
2012-02-27  4.07.02
                    -      -                 -             -                              No relevant changes available in this version.
2012-04-23  4.07.03
                    Sa     Fixed             ESCAN00055990 All                            DCM does not support more than 16 session/security access states
------------------------------------------------------------------------------------------------------------------------
 */


/* -----------------------------------------------------------------------------
    &&&~ Includes
 ----------------------------------------------------------------------------- */

#define DCM_SOURCE

#include "Dcm.h"

# include "SchM_Dcm.h"

#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
# include "v_ver.h"
#endif

#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
# include "EcuM_Cbk.h"
#endif

/* Communication manager */
#include "ComM_Dcm.h"
#if defined ( COMM_VENDOR_ID )
# if (COMM_VENDOR_ID == DCM_VENDOR_ID)
#  if ( (COMM_AR_MAJOR_VERSION == 0x02) && (COMM_AR_MINOR_VERSION == 0x00) )
    /* Compatible */
#  else
#   error "Dcm: Unsupported AUTOSAR specification version of Communication manager detected!"
#  endif
# endif
#endif
#if (DCM_PDUROUTER_ENABLED == STD_ON)
/* PDU router */
# include "PduR_Dcm.h"
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if (DCM_PDUROUTER_ENABLED == STD_ON)
# if defined ( PDUR_VENDOR_ID )
#  if (PDUR_VENDOR_ID == DCM_VENDOR_ID)
#   if ( (PDUR_AR_MAJOR_VERSION == 0x02) && (PDUR_AR_MINOR_VERSION == 0x02) )
    /* Compatible */
#   else
#    error "Dcm: Unsupported AUTOSAR specification version of PDU router detected!"
#   endif
#  endif
# endif
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_SERVICE_14_ENABLED == STD_ON) || (DCM_SERVICE_19_ENABLED == STD_ON) || (DCM_SERVICE_85_ENABLED == STD_ON))
/* Diagnostic Event Manager */
# include "Dem.h"
#endif /* ((DCM_SERVICE_14_ENABLED == STD_ON) || (DCM_SERVICE_19_ENABLED == STD_ON) || (DCM_SERVICE_85_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_14_ENABLED == STD_ON) || (DCM_SERVICE_19_ENABLED == STD_ON) || (DCM_SERVICE_85_ENABLED == STD_ON))
# if defined ( DEM_VENDOR_ID )
#  if (DEM_VENDOR_ID == DCM_VENDOR_ID)
#   if ( (DEM_AR_MAJOR_VERSION == 0x02) && (DEM_AR_MINOR_VERSION == 0x02) )
    /* Compatible */
#   else
#    error "Dcm: Unsupported AUTOSAR specification version of Diagnostic Event Manager detected!"
#   endif
#  endif
# endif
#endif /* ((DCM_SERVICE_14_ENABLED == STD_ON) || (DCM_SERVICE_19_ENABLED == STD_ON) || (DCM_SERVICE_85_ENABLED == STD_ON)) */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
/* Development Error Tracer */
# include "Det.h"
#endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
# if defined ( DET_VENDOR_ID )
#  if (DET_VENDOR_ID == DCM_VENDOR_ID)
#   if ( (DET_AR_MAJOR_VERSION == 0x02) && (DET_AR_MINOR_VERSION == 0x02) )
    /* Compatible */
#   else
#    error "Dcm: Unsupported AUTOSAR specification version of Development Error Tracer detected!"
#   endif
#  endif
# endif
#endif /* (DCM_DEV_ERROR_DETECT == STD_ON) */
#if (DCM_HARD_RESET_ENABLED == STD_ON)
/* Microcontroler Unit */
# include "Mcu.h"
#endif /* (DCM_HARD_RESET_ENABLED == STD_ON) */
#if (DCM_HARD_RESET_ENABLED == STD_ON)
# if defined ( MCU_VENDOR_ID )
#  if (MCU_VENDOR_ID == DCM_VENDOR_ID)
#   if ( (MCU_AR_MAJOR_VERSION == 0x02) && (MCU_AR_MINOR_VERSION == 0x02) )
#   elif ( (MCU_AR_MAJOR_VERSION == 0x03) && (MCU_AR_MINOR_VERSION == 0x00) )
    /* Compatible */
#   else
#    error "Dcm: Unsupported AUTOSAR specification version of Microcontroler Unit detected!"
#   endif
#  endif
# endif
#endif /* (DCM_HARD_RESET_ENABLED == STD_ON) */
#if (DCM_SERVICE_28_ENABLED == STD_ON)
/* Vehicle Mode Manager */
# include "Vmm_Dcm.h"
#endif /* (DCM_SERVICE_28_ENABLED == STD_ON) */
#if ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON) || \
    (DCM_SERVICE_04_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON))
/* OBD capable Diagnostic Event Manager */
# include "DemObd.h"
#endif /* ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON) || \
(DCM_SERVICE_04_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON)) */


/* -----------------------------------------------------------------------------
    &&&~ Configuration switches
 ----------------------------------------------------------------------------- */

#if (DCM_SERVICE_2A_ENABLED == STD_ON)
# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_OFF) && \
     ( (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF) || (DCM_NUM_CONNECTIONS_CONST > 1) )
#  define DCM_DSL_PRU_NEEDS_CONNECTION_LOCK                          STD_ON
# else
#  define DCM_DSL_PRU_NEEDS_CONNECTION_LOCK                          STD_OFF
# endif
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_19_ENABLED == STD_ON) && \
    ( (DCM_OBD_SUPPORT_ENABLED    == STD_ON) || \
    (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON) )
# define DCM_DEMMGR_RESMGR_ENABLED                                   STD_ON
#else
# define DCM_DEMMGR_RESMGR_ENABLED                                   STD_OFF
#endif

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
# if (DCM_SERVICE_2A_ENABLED == STD_ON) && \
     (DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) || \
     (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON) || \
     (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
     (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
/* wait until the DynDID read is finished */
#  define DCM_DIDMGR_RESMGR_ENABLED                                  STD_ON
# else
#  define DCM_DIDMGR_RESMGR_ENABLED                                  STD_OFF
# endif
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
# if !defined (DCM_MEMORY_ACCESS_TEST_ENABLED)
#  define DCM_MEMORY_ACCESS_TEST_ENABLED                             STD_OFF
# endif
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
    (DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON))
/* Currently not used */
# define DCM_OBD_REQ_PID_DATA_ENABLED                                STD_OFF
#endif /* ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
(DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON)) */
#if (DCM_SERVICE_19_ENABLED == STD_ON)
/* Determine DEM type */
# if (DEM_VENDOR_ID != DCM_VENDOR_ID)
#  define DCM_VECTOR_DEM_ENABLED                                     STD_OFF
# else
#  define DCM_VECTOR_DEM_ENABLED                                     STD_ON
# endif

# if (DCM_READ_DTC_SUBFUNC_02_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0A_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0F_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_13_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_15_ENABLED == STD_ON)
#  define DCM_19_READ_BY_STATUS_MASK_ENABLED                         STD_ON
# else
#  define DCM_19_READ_BY_STATUS_MASK_ENABLED                         STD_OFF
# endif
# if (DCM_READ_DTC_SUBFUNC_01_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_11_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_12_ENABLED == STD_ON)
#  define DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED                 STD_ON
# else
#  define DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED                 STD_OFF
# endif

# if (DCM_19_SNPSHT_REC_OPT_ENABLED == STD_ON)  || \
     (DCM_19_EXTDAT_REC_OPT_ENABLED == STD_ON)
#  define DCM_19_REC_TBL_ITER_ENABLED                                STD_ON
# else
#  define DCM_19_REC_TBL_ITER_ENABLED                                STD_OFF
# endif

/* Analyze if required snapshot optimized iterations */
# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON)
#  define DCM_19_SNPSHT_REC_ITER_CLIENT_ENABLED                      STD_ON
# else
#  define DCM_19_SNPSHT_REC_ITER_CLIENT_ENABLED                      STD_OFF
# endif

/* Analyze if required extdata optimized iterations */
# if ((DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON))
#  define DCM_19_EXTDAT_REC_ITER_CLIENT_ENABLED                      STD_ON
# else
#  define DCM_19_EXTDAT_REC_ITER_CLIENT_ENABLED                      STD_OFF
# endif

/* Optimize run-time in the iterator operator "next" */
# if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
#  if (DCM_CONFIG_PRECOMPILE_ENABLED == STD_ON)
#   if ((DCM_19_SNPSHT_REC_ITER_CLIENT_ENABLED == STD_ON)&& \
       (DCM_19_EXTDAT_REC_ITER_CLIENT_ENABLED == STD_ON))
#    if ((DCM_19_SNPSHT_REC_OPT_ENABLED == STD_OFF) && \
        (DCM_19_EXTDAT_REC_OPT_ENABLED == STD_ON)) || \
        ((DCM_19_SNPSHT_REC_OPT_ENABLED == STD_ON) && \
        (DCM_19_EXTDAT_REC_OPT_ENABLED == STD_OFF))
/* Precompile but with mixed config -> required */
#     define DCM_19_REC_TBL_CHK_ENABLED                              STD_ON
#    endif
#   endif
#  else
/* At link-time always required since unknown configuration at compile time */
#   define DCM_19_REC_TBL_CHK_ENABLED                                STD_ON
#  endif
# endif

# if !defined (DCM_19_REC_TBL_CHK_ENABLED)
#  define DCM_19_REC_TBL_CHK_ENABLED                                 STD_OFF
# endif
#endif /* (DCM_SERVICE_19_ENABLED == STD_ON) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
/* Default switches */
# if !defined(DCM_22_NVM_SUPPORT_ENABLED)
#  define DCM_22_NVM_SUPPORT_ENABLED                                 STD_OFF
# endif
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
# if (DCM_SERVICE_2A_ENABLED == STD_ON) || \
     (DCM_SERVICE_86_ENABLED == STD_ON)
/* wait until the DynDID read is finished */
#  define DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED                          STD_ON
# else
#  define DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED                          STD_OFF
# endif
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_2E_ENABLED == STD_ON)
/* Default switches */
# if !defined(DCM_2E_NVM_SUPPORT_ENABLED)
#  define DCM_2E_NVM_SUPPORT_ENABLED                                 STD_OFF
# endif
#endif /* (DCM_SERVICE_2E_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
# if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
/* wait until the DynRID read is finished */
#  define DCM_RIDMGR_RESMGR_ENABLED                                  STD_ON
# else
#  define DCM_RIDMGR_RESMGR_ENABLED                                  STD_OFF
# endif
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Preprocessor constants (defines)
 ----------------------------------------------------------------------------- */

#define DSL_COMM_E_OK                                                (Dcm_DslCommStatusType)0
#define DSL_COMM_E_NOT_OK                                            (Dcm_DslCommStatusType)1
#define DSL_COMM_E_NO_COMM                                           (Dcm_DslCommStatusType)2

#define DCM_CONTEXT_STATE_FREE                                       (Dcm_ContextStateType)0x01
#define DCM_CONTEXT_STATE_RX_STARTED                                 (Dcm_ContextStateType)0x02
#define DCM_CONTEXT_STATE_RX_ENDED                                   (Dcm_ContextStateType)0x04
#define DCM_CONTEXT_STATE_PROCESS_STARTED                            (Dcm_ContextStateType)0x08
#define DCM_CONTEXT_STATE_PROCESS_ENDED                              (Dcm_ContextStateType)0x10
#define DCM_CONTEXT_STATE_TX_STARTED                                 (Dcm_ContextStateType)0x20
#define DCM_CONTEXT_STATE_RESERVED                                   (Dcm_ContextStateType)0x40

#define DCM_ACTIVITY_STATE_INACTIVE                                  (Dcm_ActivityStateType)0
#define DCM_ACTIVITY_STATE_ACTIVE                                    (Dcm_ActivityStateType)1
#define DCM_ACTIVITY_STATE_PREP_INACTIVE                             (Dcm_ActivityStateType)2

#define DCM_ACTIVITY_SOURCE_RX_IND                                   (Dcm_ActivityStateTriggerType)0
#define DCM_ACTIVITY_SOURCE_SET_SES                                  (Dcm_ActivityStateTriggerType)1
#define DCM_ACTIVITY_SOURCE_MSG_TX_CONF                              (Dcm_ActivityStateTriggerType)2
#define DCM_ACTIVITY_SOURCE_MSG_TX_END                               (Dcm_ActivityStateTriggerType)3
#define DCM_ACTIVITY_SOURCE_FBL_RESPONDER                            (Dcm_ActivityStateTriggerType)4

#define DCM_COMM_STATE_FULL                                          (Dcm_CommStateType)0
#define DCM_COMM_STATE_SILENT                                        (Dcm_CommStateType)1
#define DCM_COMM_STATE_NONE                                          (Dcm_CommStateType)2

/* Message add info values (bit masked) */
#define DCM_MSGADDINFO_REQ_TYPE                                      (Dcm_MsgAddInfoType)0x01
#define DCM_MSGADDINFO_SUPP_POS_RES                                  (Dcm_MsgAddInfoType)0x02

/* Context abstraction */
#define DCM_CONTEXT_PARAM_TYPE                                       Dcm_ContextIdType
#define DCM_CONTEXT_PARAM_NAME                                       lContext



/* Offline context ID calculation */
#define DCM_NUM_CONTEXTS_UDS                                         1

#if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
    (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
# define DCM_NUM_CONTEXTS_OBD                                        1
#else
# define DCM_NUM_CONTEXTS_OBD                                        0
#endif

#define DCM_CONTEXT_ID_UDS                                           (DCM_CONTEXT_PARAM_TYPE)0
#define DCM_CONTEXT_ID_OBD                                           (DCM_CONTEXT_PARAM_TYPE)(DCM_CONTEXT_ID_UDS + DCM_NUM_CONTEXTS_UDS)
#define DCM_CONTEXT_ID_INVALID                                       (DCM_CONTEXT_PARAM_TYPE)0xFFu


#if(DCM_NUM_CONTEXTS > 1)
# define DCM_CONTEXT_PARAM_DEF_ONLY                                  DCM_CONTEXT_PARAM_TYPE DCM_CONTEXT_PARAM_NAME
# define DCM_CONTEXT_PARAM_DEF_FIRST                                 DCM_CONTEXT_PARAM_DEF_ONLY,
# define DCM_CONTEXT_PARAM_VALUE                                     DCM_CONTEXT_PARAM_NAME
# define DCM_CONTEXT_PARAM_VALUE_ONLY                                DCM_CONTEXT_PARAM_NAME
# define DCM_CONTEXT_PARAM_VALUE_FIRST                               DCM_CONTEXT_PARAM_VALUE_ONLY,
# define DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(value)                    (value)  /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(value)                   DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(value),  /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define DCM_CONTEXT_PARAM_VALUE_WRAP_INDEX(index)                   (index)  /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define DCM_CONTEXT_PARAM_IGNORE                                    (DCM_IGNORE_UNREF_PARAM(DCM_CONTEXT_PARAM_NAME)); /* PRQA S 3412 */ /* QAC 7.0:  Macro defines an unrecognised code-fragment. */ /* It is defined! */
#else
# define DCM_CONTEXT_PARAM_DEF_ONLY                                  void /* PRQA S 3460 */ /* QAC 7.0:  Macro defines a type specifier keyword. */ /* Provides better code readability */
# define DCM_CONTEXT_PARAM_DEF_FIRST
# define DCM_CONTEXT_PARAM_VALUE                                     0
# define DCM_CONTEXT_PARAM_VALUE_ONLY
# define DCM_CONTEXT_PARAM_VALUE_FIRST
# define DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(value)
# define DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(value)
# define DCM_CONTEXT_PARAM_VALUE_WRAP_INDEX(index)                   0
# define DCM_CONTEXT_PARAM_IGNORE
#endif

/* Optimization for WWHOBD context usage */
#if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
# define DCM_NUM_UDS_CONTEXTS                                        2
#else
# define DCM_NUM_UDS_CONTEXTS                                        1
#endif

#if (DCM_NUM_UDS_CONTEXTS > 1)
# define DCM_UDS_CONTEXT_PARAM_DEF_ONLY                              DCM_CONTEXT_PARAM_DEF_ONLY
# define DCM_UDS_CONTEXT_PARAM_DEF_FIRST                             DCM_CONTEXT_PARAM_DEF_FIRST
# define DCM_UDS_CONTEXT_PARAM_VALUE                                 DCM_CONTEXT_PARAM_VALUE
# define DCM_UDS_CONTEXT_PARAM_VALUE_ONLY                            DCM_CONTEXT_PARAM_VALUE_ONLY
# define DCM_UDS_CONTEXT_PARAM_VALUE_FIRST                           DCM_CONTEXT_PARAM_VALUE_FIRST
# define DCM_UDS_CONTEXT_PARAM_VALUE_WRAP_ONLY(value)                DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(value)  /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define DCM_UDS_CONTEXT_PARAM_VALUE_WRAP_FIRST(value)               DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(value)  /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define DCM_UDS_CONTEXT_PARAM_IGNORE                                DCM_CONTEXT_PARAM_IGNORE
# define DCM_UDS_CONTEXT_PARAM_LOCAL_IGNORE                          /* local variable is used - do not ignore it */
#else
# define DCM_UDS_CONTEXT_PARAM_DEF_ONLY                              void /* PRQA S 3460 */ /* QAC 7.0:  Macro defines a type specifier keyword. */ /* Provides better code readability */
# define DCM_UDS_CONTEXT_PARAM_DEF_FIRST
# define DCM_UDS_CONTEXT_PARAM_VALUE                                 0
# define DCM_UDS_CONTEXT_PARAM_VALUE_ONLY
# define DCM_UDS_CONTEXT_PARAM_VALUE_FIRST
# define DCM_UDS_CONTEXT_PARAM_VALUE_WRAP_ONLY(value)
# define DCM_UDS_CONTEXT_PARAM_VALUE_WRAP_FIRST(value)
# define DCM_UDS_CONTEXT_PARAM_IGNORE
# define DCM_UDS_CONTEXT_PARAM_LOCAL_IGNORE                          (DCM_IGNORE_UNREF_PARAM(DCM_CONTEXT_PARAM_NAME)); /* PRQA S 3412 */ /* QAC 7.0:  Macro defines an unrecognised code-fragment. */ /* It is defined! */
#endif
#if (DCM_NUM_CONTEXTS > 1)
# define DCM_CONTEXT_ITER_TYPE                                       uint8_least
# define DCM_CONTEXT_ITER_VALUE                                      contextIter
# define DCM_CONTEXT_ITER_DEF_LOCAL                                  DCM_CONTEXT_ITER_TYPE DCM_CONTEXT_ITER_VALUE; /* PRQA S 3412 */ /* QAC 7.0:  Macro defines an unrecognised code-fragment. */ /* It is defined! */
# define DCM_CONTEXT_ITER_VALUE_INIT                                 DCM_CONTEXT_ITER_VALUE = DCM_NUM_CONTEXTS
# define DCM_CONTEXT_ITER_VALUE_DEC                                  DCM_CONTEXT_ITER_VALUE--
# define DCM_CONTEXT_ITER_LOOP                                       while(DCM_CONTEXT_ITER_VALUE != 0) /* PRQA S 3412 */ /* QAC 7.0:  Macro defines an unrecognised code-fragment. */ /* It is defined! */
#else
# define DCM_CONTEXT_ITER_TYPE
# define DCM_CONTEXT_ITER_VALUE                                      0
# define DCM_CONTEXT_ITER_DEF_LOCAL
# define DCM_CONTEXT_ITER_VALUE_INIT
# define DCM_CONTEXT_ITER_VALUE_DEC
# define DCM_CONTEXT_ITER_LOOP
#endif

#if (DCM_NUM_UDS_CONTEXTS > 1)
# define DCM_UDS_CONTEXT_ITER_TYPE                                   DCM_CONTEXT_ITER_TYPE
# define DCM_UDS_CONTEXT_ITER_VALUE                                  DCM_CONTEXT_ITER_VALUE
# define DCM_UDS_CONTEXT_ITER_VALUE_ONLY                             (DCM_CONTEXT_PARAM_TYPE)DCM_CONTEXT_ITER_VALUE
# define DCM_UDS_CONTEXT_ITER_VALUE_FIRST                            (DCM_CONTEXT_PARAM_TYPE)DCM_CONTEXT_ITER_VALUE,
# define DCM_UDS_CONTEXT_ITER_DEF_LOCAL                              DCM_CONTEXT_ITER_DEF_LOCAL
# define DCM_UDS_CONTEXT_ITER_VALUE_INIT                             DCM_CONTEXT_ITER_VALUE_INIT
# define DCM_UDS_CONTEXT_ITER_VALUE_DEC                              DCM_CONTEXT_ITER_VALUE_DEC
# define DCM_UDS_CONTEXT_ITER_LOOP                                   DCM_CONTEXT_ITER_LOOP
#else
# define DCM_UDS_CONTEXT_ITER_TYPE
# define DCM_UDS_CONTEXT_ITER_VALUE                                  0
# define DCM_UDS_CONTEXT_ITER_VALUE_ONLY
# define DCM_UDS_CONTEXT_ITER_VALUE_FIRST
# define DCM_UDS_CONTEXT_ITER_DEF_LOCAL
# define DCM_UDS_CONTEXT_ITER_VALUE_INIT
# define DCM_UDS_CONTEXT_ITER_VALUE_DEC
# define DCM_UDS_CONTEXT_ITER_LOOP
#endif
/* Variant management */
#if (DCM_COM_MULTI_ID_ENABLED == STD_ON)
# define DCM_COMVARIANT_ID_VALUE                                     (dcmStateMachine.ComVariantId)
#else
# define DCM_COMVARIANT_ID_VALUE                                     0
#endif

/* Some internal function have different optimization on single and multi context */
#if(DCM_NUM_CONTEXTS > 1)
# define CONTEXT_FUNC_LOC                                            STATIC
#else
# define CONTEXT_FUNC_LOC                                            LOCAL_INLINE
#endif

/* This magic number provides internal DCM generation process consistency check.All DCM files must have the same one. */
#define DCM_IMPLEMENTATION_MAGIC_NUMBER                              9001
#define DCM_IMPL_OEM_ID                                              2
#define DCM_DEBUG_INIT_PATTERN                                       (uint16)0xF01A

/* Generation consitency check */
#if (DCM_XDECL_INTERFACE_MAGIC_NUMBER != DCM_IMPLEMENTATION_MAGIC_NUMBER)
# error "Dcm.h doesn't match the Dcm.c creation time!"
#endif


#if (DCM_ADECL_MAGIC_NUMBER != DCM_IMPLEMENTATION_MAGIC_NUMBER)
# error "Dcm_Cbk.h doesn't match the Dcm.c creation time!"
#endif

#if (DCM_TDECL_MAGIC_NUMBER != DCM_IMPLEMENTATION_MAGIC_NUMBER)
# error "Dcm_Types.h doesn't match the Dcm.c creation time!"
#endif

/**********************************************************************************************************************
 *  CONFIGURATION CHECK
 *********************************************************************************************************************/
/* Check DCM OEM to CFG OEM */
#if ( DCM_IMPL_OEM_ID != DCM_CFG_OEM_ID )
# error "The DCM implementation OEM does not match the configuration OEM!"
#endif

#if defined (V_EXTENDED_BUILD_LIB_CHECK)
# if (DCM_CONFIG_PRECOMPILE_ENABLED == STD_ON)
#  error "DCM has been configured with precompile variant, but library build process is active!"
# endif
#endif

/********************************************************************************************************************
*  VERSION CHECK
********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (DCM_SW_MAJOR_VERSION != (0x04)) \
    || (DCM_SW_MINOR_VERSION != (0x07)) \
    || (DCM_SW_PATCH_VERSION != (0x03)) )
# error "Vendor specific version numbers of Dcm.c and Dcm.h are inconsistent!"
#endif
/* AUTOSAR version information check has to match definition in header file */
#if (  (DCM_AR_MAJOR_VERSION != (0x03)) \
    || (DCM_AR_MINOR_VERSION != (0x00)) \
    || (DCM_AR_PATCH_VERSION != (0x00)) )
# error "AUTOSAR specification version numbers of Dcm.c and Dcm.h are inconsistent!"
#endif
/* versions of all included header files shall be checked */
#if (  (DCM_CFG_MAJOR_VERSION != (0x05)) \
    || (DCM_CFG_MINOR_VERSION != (0x84)) )
# error "Version numbers of Dcm.c and Dcm_Cfg.h are inconsistent!"
#endif
#if (  (DCM_LCFG_MAJOR_VERSION != (0x05)) \
    || (DCM_LCFG_MINOR_VERSION != (0x84)) )
# error "Version numbers of Dcm.c and Dcm_Lcfg.h are inconsistent!"
#endif

/* Check that the correct build-lib diagnostic file is used. */
#if defined ( V_EXTENDED_BUILD_LIB_CHECK )
# if defined (DCM_NEW_ECU_1)
#  if (DCM_NEW_ECU_1 != 0x0000)
#   error "DCM will be compiled for LIB, but wrong CDD file version is used for the configuration!"
#  endif
# else
#  error "DCM will be compiled for LIB, but wrong CDD file is used for the configuration!"
# endif
#endif

/* OS simulation */
/* Tasks managment */

/* Always exists */
#define DCM_NUM_STATE_TASKS                                          1

#if (DCM_SERVICE_2A_ENABLED == STD_ON)
# define DCM_NUM_2A_TASKS                                            1
#else
# define DCM_NUM_2A_TASKS                                            0
#endif

#if (DCM_SERVICE_2C_ENABLED == STD_ON)
# define DCM_NUM_2C_TASKS                                            1
#else
# define DCM_NUM_2C_TASKS                                            0
#endif

#if (DCM_PDUROUTER_ENABLED == STD_ON)
# define DCM_NUM_DSL_LL_TASKS                                        1
#else
# define DCM_NUM_DSL_LL_TASKS                                        0
#endif

#if (DCM_SERVICE_27_ENABLED == STD_ON)
# define DCM_NUM_27_TASKS                                            1
#else
# define DCM_NUM_27_TASKS                                            0
#endif

#if (DCM_SERVICE_A0_ENABLED == STD_ON)
# define DCM_NUM_A0_TASKS                                            1
#else
# define DCM_NUM_A0_TASKS                                            0
#endif

#if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
    (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
# define DCM_NUM_OBD_TASKS                                           1
#else
# define DCM_NUM_OBD_TASKS                                           0
#endif

/* Task IDs */
#define DCM_TASK_ID_DSL_LL_STATE                                     (Dcm_TaskIdType)0
#define DCM_TASK_ID_STATE                                            (Dcm_TaskIdType)(DCM_TASK_ID_DSL_LL_STATE    + DCM_NUM_DSL_LL_TASKS)
#define DCM_TASK_ID_SCHEDULER                                        (Dcm_TaskIdType)(DCM_TASK_ID_STATE     + DCM_NUM_STATE_TASKS)
#define DCM_TASK_ID_DYNDID                                           (Dcm_TaskIdType)(DCM_TASK_ID_SCHEDULER + DCM_NUM_2A_TASKS)
#define DCM_TASK_ID_SECACC                                           (Dcm_TaskIdType)(DCM_TASK_ID_DYNDID + DCM_NUM_2C_TASKS)
#define DCM_TASK_ID_SERVICE_A0                                       (Dcm_TaskIdType)(DCM_TASK_ID_SECACC + DCM_NUM_27_TASKS)
#define DCM_TASK_ID_OBD                                              (Dcm_TaskIdType)(DCM_TASK_ID_SERVICE_A0 + DCM_NUM_A0_TASKS)



/* Event management */

/* STATE TASK */
#define DCM_EVENT_SEND_LINEAR_RES                                    (Dcm_EventType)0x01
#define DCM_EVENT_SEND_PAGED_RES                                     (Dcm_EventType)(DCM_EVENT_SEND_LINEAR_RES << 1u)
#define DCM_EVENT_NEW_REQ                                            (Dcm_EventType)(DCM_EVENT_SEND_PAGED_RES << 1u)
#define DCM_EVENT_TX_END                                             (Dcm_EventType)(DCM_EVENT_NEW_REQ << 1u)

#define DCM_EVENT_STATE_TASK_PROXY                                   (Dcm_EventType)(DCM_EVENT_TX_END << 1u)
#define DCM_EVENT_RCRRP_CONFIRM                                      (Dcm_EventType)(DCM_EVENT_STATE_TASK_PROXY << 1u)
#define DCM_EVENT_PB_UPDATE_PAGE                                     (Dcm_EventType)(DCM_EVENT_RCRRP_CONFIRM << 1u)
#define DCM_EVENT_TESTER_TIMEOUT                                     (Dcm_EventType)(DCM_EVENT_PB_UPDATE_PAGE << 1u)

#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
# define DCM_EVENT_PROCESS_FBL_RES                                   (Dcm_EventType)(DCM_EVENT_TESTER_TIMEOUT << 1u)
#else
/* if not used, just continue the event value chain with the last value */
# define DCM_EVENT_PROCESS_FBL_RES                                   (Dcm_EventType)(DCM_EVENT_TESTER_TIMEOUT)
#endif

#if (DCM_USE_SAFE_RESET_ENABLED == STD_ON)
# define DCM_EVENT_PERFORM_RESET                                     (Dcm_EventType)(DCM_EVENT_PROCESS_FBL_RES << 1u)
#else
/* if not used, just continue the event value chain with the last value */
# define DCM_EVENT_PERFORM_RESET                                     (Dcm_EventType)(DCM_EVENT_PROCESS_FBL_RES)
#endif

/* OBD TASK use the UDS events to avoid context specific events */
#define DCM_EVENT_OBD_SEND_LINEAR_RES                                DCM_EVENT_SEND_LINEAR_RES
#define DCM_EVENT_OBD_SEND_PAGED_RES                                 DCM_EVENT_SEND_PAGED_RES
#define DCM_EVENT_OBD_NEW_REQ                                        DCM_EVENT_NEW_REQ
#define DCM_EVENT_OBD_TX_END                                         DCM_EVENT_TX_END

#define DCM_EVENT_OBD_TASK_PROXY                                     DCM_EVENT_STATE_TASK_PROXY /* must have this value to work with the repater proxy mgr!!!*/
#define DCM_EVENT_OBD_PB_UPDATE_PAGE                                 DCM_EVENT_PB_UPDATE_PAGE

/* SCHEDULER TASK */
#define DCM_EVENT_TIMER_00                                           (Dcm_EventType)0x00000001
#define DCM_EVENT_TIMER_01                                           (Dcm_EventType)0x00000002
#define DCM_EVENT_TIMER_02                                           (Dcm_EventType)0x00000004
#define DCM_EVENT_TIMER_03                                           (Dcm_EventType)0x00000008
#define DCM_EVENT_TIMER_04                                           (Dcm_EventType)0x00000010
#define DCM_EVENT_TIMER_05                                           (Dcm_EventType)0x00000020
#define DCM_EVENT_TIMER_06                                           (Dcm_EventType)0x00000040
#define DCM_EVENT_TIMER_07                                           (Dcm_EventType)0x00000080
#define DCM_EVENT_TIMER_08                                           (Dcm_EventType)0x00000100
#define DCM_EVENT_TIMER_09                                           (Dcm_EventType)0x00000200
#define DCM_EVENT_TIMER_10                                           (Dcm_EventType)0x00000400
#define DCM_EVENT_TIMER_11                                           (Dcm_EventType)0x00000800
#define DCM_EVENT_TIMER_12                                           (Dcm_EventType)0x00001000
#define DCM_EVENT_TIMER_13                                           (Dcm_EventType)0x00002000
#define DCM_EVENT_TIMER_14                                           (Dcm_EventType)0x00004000
#define DCM_EVENT_TIMER_15                                           (Dcm_EventType)0x00008000
#define DCM_EVENT_SCHEDULER_TASK_PROXY                               (Dcm_EventType)0x00010000

#define DCM_EVENT_TIMER_ANY                                          (Dcm_EventType)(DCM_EVENT_TIMER_00 | DCM_EVENT_TIMER_01 | DCM_EVENT_TIMER_02 | DCM_EVENT_TIMER_03 | \
                                                                     DCM_EVENT_TIMER_04 | DCM_EVENT_TIMER_05 | DCM_EVENT_TIMER_06 | DCM_EVENT_TIMER_07 | \
                                                                     DCM_EVENT_TIMER_08 | DCM_EVENT_TIMER_09 | DCM_EVENT_TIMER_10 | DCM_EVENT_TIMER_11 | \
                                                                     DCM_EVENT_TIMER_12 | DCM_EVENT_TIMER_13 | DCM_EVENT_TIMER_14 | DCM_EVENT_TIMER_15 )


/* DYNDID TASK */
#define DCM_EVENT_DYNDID_TASK_PROXY                                  (Dcm_EventType)0x01

#define DCM_NUM_TASKS                                                (Dcm_TaskIdType)(DCM_NUM_DSL_LL_TASKS + DCM_NUM_STATE_TASKS + DCM_NUM_2A_TASKS + DCM_NUM_2C_TASKS + DCM_NUM_27_TASKS + DCM_NUM_A0_TASKS + DCM_NUM_OBD_TASKS)

/* DSL LL STATE TASK */
#define DCM_EVENT_DO_SEND                                            (Dcm_EventType)0x01
#define DCM_EVENT_DO_RETRY_TX_ALLOC_UDS                              (Dcm_EventType)0x02
#define DCM_EVENT_DO_RETRY_TX_ALLOC_OBD                              (Dcm_EventType)0x04
#define DCM_EVENT_PPRH_DO_SEND                                       (Dcm_EventType)0x08

/* SECCA STATE TASK - OEM specific */
/* SERVICE_A0 STATE TASK - OEM specific */

/* Context management */
#if (DCM_NUM_CONTEXTS > 1)
# define DCM_CONTEXT_STATE_TASK_ID(contextId)                        dcmEvMgrContextStateTaskId[(contextId)] /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#else
# define DCM_CONTEXT_STATE_TASK_ID(contextId)                        DCM_TASK_ID_STATE
#endif

/* Context management */
#if (DCM_NUM_CONTEXTS > 1)
# define DCM_CONTEXT_P2_TIMER_ID(contextId)                          dcmTmrMgrContextP2TimerId[(contextId)] /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#else
# define DCM_CONTEXT_P2_TIMER_ID(contextId)                          DCM_TIMER_ID_P2
#endif

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/* Client 0x19 always exists */
# define DCM_PB_NUM_CLIENTS_19                                       1

# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
#  define DCM_PB_NUM_CLIENTS_22                                      1
# else
#  define DCM_PB_NUM_CLIENTS_22                                      0
# endif

# if(DCM_OBD_READ_DTC_ENABLED == STD_ON)
#  define DCM_PB_NUM_CLIENTS_OBD                                     1
# else
#  define DCM_PB_NUM_CLIENTS_OBD                                     0
# endif

/* Paged Buffer clients */
# define DCM_PB_CLIENT_19                                            (Dcm_PagedBufferClientType)0x00
# define DCM_PB_CLIENT_22                                            (Dcm_PagedBufferClientType)(DCM_PB_CLIENT_19 + DCM_PB_NUM_CLIENTS_19)
# define DCM_PB_CLIENT_OBD                                           (Dcm_PagedBufferClientType)(DCM_PB_CLIENT_22 + DCM_PB_NUM_CLIENTS_22)

# define DCM_NUM_PB_CLIENTS                                          (Dcm_PagedBufferClientType)(DCM_PB_NUM_CLIENTS_19 + DCM_PB_NUM_CLIENTS_22 + DCM_PB_NUM_CLIENTS_OBD)
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
#if (DCM_PDUROUTER_ENABLED == STD_ON)
# if (DCM_DSL_NUM_TRANSP_OBJ_CONST > 1)
#  define DCM_TRANSP_OBJ_HNDL_ITER_TYPE                              uint8_least
#  define DCM_TRANSP_OBJ_HNDL_ITER_VALUE                             hTraspObjIter
#  define DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL                         DCM_TRANSP_OBJ_HNDL_ITER_TYPE DCM_TRANSP_OBJ_HNDL_ITER_VALUE;  /* PRQA S 3412 */ /* QAC 7.0:  Macro defines an unrecognised code-fragment. */ /* It is defined! */
#  define DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT                        DCM_TRANSP_OBJ_HNDL_ITER_VALUE = DCM_DSL_NUM_TRANSP_OBJ
#  define DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC                         DCM_TRANSP_OBJ_HNDL_ITER_VALUE--
#  define DCM_TRANSP_OBJ_HNDL_ITER_LOOP                              while(DCM_TRANSP_OBJ_HNDL_ITER_VALUE != 0) /* PRQA S 3412 */ /* QAC 7.0:  Macro defines an unrecognised code-fragment. */ /* It is defined! */
# else
#  define DCM_TRANSP_OBJ_HNDL_ITER_TYPE
#  define DCM_TRANSP_OBJ_HNDL_ITER_VALUE                             0
#  define DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL
#  define DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT
#  define DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC
#  define DCM_TRANSP_OBJ_HNDL_ITER_LOOP
# endif
# define DCM_PDU_TX_STATE_FREE                                       (Dcm_TxStateType)0x00
# define DCM_PDU_TX_STATE_INIT                                       (Dcm_TxStateType)0x01
# define DCM_PDU_TX_STATE_RESERVED                                   (Dcm_TxStateType)0x02
# define DCM_PDU_TX_STATE_ON_RX_START                                (Dcm_TxStateType)0x03
# define DCM_PDU_TX_STATE_ON_RX                                      (Dcm_TxStateType)0x04
# define DCM_PDU_TX_STATE_PROCESSING                                 (Dcm_TxStateType)0x05
# define DCM_PDU_TX_STATE_DO_SEND                                    (Dcm_TxStateType)0x06
# define DCM_PDU_TX_STATE_ON_TX                                      (Dcm_TxStateType)0x07
# define DCM_PDU_TX_STATE_PREFETCH                                   (Dcm_TxStateType)0x08


# define DCM_DSL_TOBJ_KIND_MAIN                                      (Dcm_PduTranspObjKindType)0u
# define DCM_DSL_TOBJ_KIND_CONCUR                                    (Dcm_PduTranspObjKindType)1u
# define DCM_DSL_TOBJ_KIND_PERIODIC                                  (Dcm_PduTranspObjKindType)2u
# define DCM_CONN_DIAG_TYPE_UDS                                      (Dcm_ConnectionDiagType)0
# define DCM_CONN_DIAG_TYPE_OBD                                      (Dcm_ConnectionDiagType)1
# define DCM_CONN_DIAG_TYPE_UDSOBD                                   (Dcm_ConnectionDiagType)2

# define DCM_DIAG_SERVICE_GRP_OBD                                    (Dcm_ServiceIdGroupType)0
# define DCM_DIAG_SERVICE_GRP_WWHOBD                                 (Dcm_ServiceIdGroupType)1
# define DCM_DIAG_SERVICE_GRP_UDS                                    (Dcm_ServiceIdGroupType)2
# define DCM_SEMAPHORE_ALLOCATE_TX_FREE                              0
# define DCM_SEMAPHORE_ALLOCATE_TX_LOCKED                            1
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
# define DCM_PERIODIC_CONF_TIMEOUT                                   100 /*ms*/
#endif /* ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
# define DCM_PERIODIC_HANDLE_INVALID                                 (Dcm_MemPeriodicHandleType)0xFF
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#define DCM_ADDR_TYPE_PHYS                                           (Dcm_ReqAddressingType)0
#define DCM_ADDR_TYPE_FUNC                                           (Dcm_ReqAddressingType)1
#define DCM_ADDR_TYPE_UNDEFINED                                      (Dcm_ReqAddressingType)2
#define DSL_RES_TYPE_NONE                                            (Dcm_DslResponseType)0x00
#define DSL_RES_TYPE_RCRRP_AUT                                       (Dcm_DslResponseType)0x01
#define DSL_RES_TYPE_RCRRP_INT                                       (Dcm_DslResponseType)0x02
#define DSL_RES_TYPE_RCRRP_RTE                                       (Dcm_DslResponseType)0x04
#define DSL_RES_TYPE_RCRRP_ANY                                       (Dcm_DslResponseType)(DSL_RES_TYPE_RCRRP_AUT | DSL_RES_TYPE_RCRRP_INT | DSL_RES_TYPE_RCRRP_RTE)
#define DSL_RES_TYPE_RCRRP_FINISHED                                  (Dcm_DslResponseType)0x08

#define DSL_RES_TYPE_FINAL_LINEAR                                    (Dcm_DslResponseType)0x10
#define DSL_RES_TYPE_FINAL_PAGED                                     (Dcm_DslResponseType)0x20
#define DSL_RES_TYPE_FINAL                                           (Dcm_DslResponseType)(DSL_RES_TYPE_FINAL_LINEAR | DSL_RES_TYPE_FINAL_PAGED)
#define DSL_RES_TYPE_SPONTANEOUS                                     (Dcm_DslResponseType)0x40

#define DCM_CONNECTION_ID_INVALID                                    (Dcm_ConnectionRefType)0xFF

#define DCM_STATE_LVL_SID                                            (Dcm_StateLevelType)0
#define DCM_STATE_LVL_PARAM                                          (Dcm_StateLevelType)1
#define DCM_STATE_LVL_SUBFUNC                                        (Dcm_StateLevelType)2

#define DCM_DIAG_PROTOCOL_UDS                                        (Dcm_DiagProtocolType)0x01
#define DCM_DIAG_PROTOCOL_OBD                                        (Dcm_DiagProtocolType)0x02
#define DCM_DIAG_PROTOCOL_WWHOBD                                     (Dcm_DiagProtocolType)0x04

#define DCM_NO_PEND_SESCHG_IDX                                       (uint8)0xFFu

#define DCM_ACC_REQ_PHYS_BIT                                         (Dcm_ServicePropertyType)(0x01)
#define DCM_ACC_REQ_FUNC_BIT                                         (Dcm_ServicePropertyType)(0x02)
#define DCM_RES_REQ_PHYS_BIT                                         (Dcm_ServicePropertyType)(0x04)
#define DCM_RES_REQ_FUNC_BIT                                         (Dcm_ServicePropertyType)(0x08)
#define DCM_SUPP_POS_RES_BIT                                         (Dcm_ServicePropertyType)(0x10)

#if (DCM_SERVICE_19_ENABLED == STD_ON)
# define DCM_DEMMGR_NUM_CLIENT_UDS                                   1
#else
# define DCM_DEMMGR_NUM_CLIENT_UDS                                   0
#endif
#if (DCM_OBD_SUPPORT_ENABLED    == STD_ON) || \
    (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
# define DCM_DEMMGR_NUM_CLIENT_OBD                                   1
#else
# define DCM_DEMMGR_NUM_CLIENT_OBD                                   0
#endif

#define DCM_DEMMGR_NUM_DEM_CLIENTS                                   (Dcm_DemMgrDemClientType)(DCM_DEMMGR_NUM_CLIENT_UDS + DCM_DEMMGR_NUM_CLIENT_OBD)

/* Client IDs */
#define DCM_DEMMGR_CLIENT_ID_UDS                                     (Dcm_DemMgrDemClientType)(0    +   0)
#define DCM_DEMMGR_CLIENT_ID_OBD                                     (Dcm_DemMgrDemClientType)(DCM_DEMMGR_CLIENT_ID_UDS + DCM_DEMMGR_NUM_CLIENT_UDS)


/* DEM OPS */

/* For UDS 14 
 * and 
 * OBD 04 */
#define DCM_DEMMGR_OP_14                                             (Dcm_DemMgrDemOpType)0x01

/* For UDS 19 02, 0A, 0F, 13 and 15 
 * and 
 * OBD 03, 07 and 0A */
#define DCM_DEMMGR_OP_1902                                           (Dcm_DemMgrDemOpType)0x02

/* For UDS 19 04 */
#define DCM_DEMMGR_OP_1904                                           (Dcm_DemMgrDemOpType)0x04

/* For UDS 19 05 
 * and 
 * OBD 02 */
#define DCM_DEMMGR_OP_1905                                           (Dcm_DemMgrDemOpType)0x08

/* For UDS 19 06 and 10 
 * and 
 * OBD 04 */
#define DCM_DEMMGR_OP_1906                                           (Dcm_DemMgrDemOpType)0x10
 /* For UDS 19 Other 
 * and 
 * OBD 04 */
#define DCM_DEMMGR_OP_19XX                                           (Dcm_DemMgrDemOpType)0x80

#define DCM_DEMMGR_OP_ANY_19                                         (Dcm_DemMgrDemOpType)( DCM_DEMMGR_OP_1902 | DCM_DEMMGR_OP_1904 | DCM_DEMMGR_OP_1905 | DCM_DEMMGR_OP_1906 | DCM_DEMMGR_OP_19XX)


#define DCM_DEMMGR_OP_ALL                                            (Dcm_DemMgrDemOpType)(DCM_DEMMGR_OP_14 | DCM_DEMMGR_OP_ANY_19)

#if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
# define DEMMGR_FUNC_LOC                                             STATIC
#else
# define DEMMGR_FUNC_LOC                                             LOCAL_INLINE
#endif

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
# if (DCM_SERVICE_22_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_22                                   1
# else
#  define DCM_DIDMGR_NUM_CLIENT_22                                   0
# endif
# if (DCM_SERVICE_2E_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_2E                                   1
# else
#  define DCM_DIDMGR_NUM_CLIENT_2E                                   0
# endif
# if (DCM_SERVICE_2A_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_2A                                   1
# else
#  define DCM_DIDMGR_NUM_CLIENT_2A                                   0
# endif
# if (DCM_SERVICE_2C_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_2C                                   1
# else
#  define DCM_DIDMGR_NUM_CLIENT_2C                                   0
# endif
# if (DCM_SERVICE_2F_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_2F                                   1
# else
#  define DCM_DIDMGR_NUM_CLIENT_2F                                   0
# endif
# if (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_READ_EXT                             1
# else
#  define DCM_DIDMGR_NUM_CLIENT_READ_EXT                             0
# endif
# if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_OBD                                  1
# else
#  define DCM_DIDMGR_NUM_CLIENT_OBD                                  0
# endif
# if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
#  define DCM_DIDMGR_NUM_CLIENT_22_WWHOBD                            1
# else
#  define DCM_DIDMGR_NUM_CLIENT_22_WWHOBD                            0
# endif

# define DCM_DID_MGR_NUM_DID_CLIENTS                                 (Dcm_DidMgrDidClientType)(DCM_DIDMGR_NUM_CLIENT_22 + \
                                                                     DCM_DIDMGR_NUM_CLIENT_2E + \
                                                                     DCM_DIDMGR_NUM_CLIENT_2A + \
                                                                     DCM_DIDMGR_NUM_CLIENT_2C + \
                                                                     DCM_DIDMGR_NUM_CLIENT_2F + \
                                                                     DCM_DIDMGR_NUM_CLIENT_READ_EXT + \
                                                                     DCM_DIDMGR_NUM_CLIENT_OBD + \
                                                                     DCM_DIDMGR_NUM_CLIENT_22_WWHOBD)

/* Client IDs */
# define DCM_DIDMGR_CLIENT_ID_22                                     (Dcm_DidMgrDidClientType)(0    +   0)
# define DCM_DIDMGR_CLIENT_ID_2E                                     (Dcm_DidMgrDidClientType)(DCM_DIDMGR_CLIENT_ID_22 + DCM_DIDMGR_NUM_CLIENT_22)
# define DCM_DIDMGR_CLIENT_ID_2A                                     (Dcm_DidMgrDidClientType)(DCM_DIDMGR_CLIENT_ID_2E + DCM_DIDMGR_NUM_CLIENT_2E)
# define DCM_DIDMGR_CLIENT_ID_2C                                     (Dcm_DidMgrDidClientType)(DCM_DIDMGR_CLIENT_ID_2A + DCM_DIDMGR_NUM_CLIENT_2A)
# define DCM_DIDMGR_CLIENT_ID_2F                                     (Dcm_DidMgrDidClientType)(DCM_DIDMGR_CLIENT_ID_2C + DCM_DIDMGR_NUM_CLIENT_2C)
# define DCM_DIDMGR_CLIENT_ID_READ_EXT                               (Dcm_DidMgrDidClientType)(DCM_DIDMGR_CLIENT_ID_2F + DCM_DIDMGR_NUM_CLIENT_2F)
# define DCM_DIDMGR_CLIENT_ID_OBD                                    (Dcm_DidMgrDidClientType)(DCM_DIDMGR_CLIENT_ID_READ_EXT + DCM_DIDMGR_NUM_CLIENT_READ_EXT)
# define DCM_DIDMGR_CLIENT_ID_22_WWHOBD                              (Dcm_DidMgrDidClientType)(DCM_DIDMGR_CLIENT_ID_OBD + DCM_DIDMGR_NUM_CLIENT_OBD)
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
# define DCM_MEMMGR_EXTR_INFO_OK                                     (Dcm_MemMgrExtrInfoRsltType)0
# define DCM_MEMMGR_EXTR_INFO_NO_DATA                                (Dcm_MemMgrExtrInfoRsltType)1
# define DCM_MEMMGR_EXTR_INFO_WRONG_FID                              (Dcm_MemMgrExtrInfoRsltType)2
# define DCM_MEMMGR_EXTR_INFO_TOO_SHORT                              (Dcm_MemMgrExtrInfoRsltType)3
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON))
# define DCM_DTC_BIT_DONT_CARE                                       (uint8)0x00
# define DCM_DTC_BIT_TST_FLD                                         (uint8)0x01
# define DCM_DTC_BIT_TST_FLD_CYCL                                    (uint8)0x02
# define DCM_DTC_BIT_PNDG_DTC                                        (uint8)0x04
# define DCM_DTC_BIT_CONF_DTC                                        (uint8)0x08
# define DCM_DTC_BIT_TST_NOT_COMPL_CLR                               (uint8)0x10
# define DCM_DTC_BIT_TST_FLD_CLR                                     (uint8)0x20
# define DCM_DTC_BIT_TST_NOT_COMPL_CYCL                              (uint8)0x40
# define DCM_DTC_BIT_WARN_IND_REQ                                    (uint8)0x80
#endif /* ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
# define DCM_10_FBL_SET_PROG_CONDITIONS                              (Dcm_10_ProgressType)0
# define DCM_10_FBL_WAIT_RCR_RP                                      (Dcm_10_ProgressType)1
#endif /* (DCM_SERVICE_10_ENABLED == STD_ON) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
# define DCM_22_DISPATCH_FIND_DID                                    (Dcm_22_ProgressType)0
# define DCM_22_DISPATCH_GET_LEN                                     (Dcm_22_ProgressType)1
# define DCM_22_DISPATCH_CHECK_DID                                   (Dcm_22_ProgressType)2
# define DCM_22_DISPATCH_END                                         (Dcm_22_ProgressType)3

# define DCM_22_PROCESS_INIT_DID                                     (Dcm_22_ProgressType)4
# define DCM_22_PROCESS_READ_DID                                     (Dcm_22_ProgressType)5
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
# define DCM_2A_DISPATCH_FIND_DID                                    (Dcm_2A_ProgressType)0
# define DCM_2A_DISPATCH_GET_LEN                                     (Dcm_2A_ProgressType)1
# define DCM_2A_DISPATCH_CHECK_DID                                   (Dcm_2A_ProgressType)2
# define DCM_2A_DISPATCH_END                                         (Dcm_2A_ProgressType)3


# define DCM_2A_RATE_TYPE_SLOW                                       (Dcm_2A_MemRateType)0x00
# define DCM_2A_RATE_TYPE_MED                                        (Dcm_2A_MemRateType)0x01
# define DCM_2A_RATE_TYPE_FAST                                       (Dcm_2A_MemRateType)0x02

# define DCM_2A_RATE_TYPE_MASK                                       (Dcm_2A_MemRateType)(DCM_2A_RATE_TYPE_SLOW | DCM_2A_RATE_TYPE_MED | DCM_2A_RATE_TYPE_FAST)

# define DCM_2A_RATE_TYPE_WAIT_STOP                                  (Dcm_2A_MemRateType)0x04
# define DCM_2A_RATE_TYPE_STOPPED                                    (Dcm_2A_MemRateType)0x08
# define DCM_2A_RATE_TYPE_RESERVED                                   (Dcm_2A_MemRateType)0x10
# define DCM_2A_RATE_TYPE_INVALID                                    (Dcm_2A_MemRateType)0x20 /* If you change this - change the generator too!*/
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
# define DCM_2C_DISPATCH_FIND_DID                                    (Dcm_2C_ProgressType)0
# define DCM_2C_DISPATCH_GET_LEN                                     (Dcm_2C_ProgressType)1
# define DCM_2C_DISPATCH_CHECK_DID                                   (Dcm_2C_ProgressType)2
# define DCM_2C_DISPATCH_END                                         (Dcm_2C_ProgressType)3

# define DCM_2C_OP_TYPE_DEF_BY_ID                                    (Dcm_2C_OpType)0
# define DCM_2C_OP_TYPE_DEF_BY_MEM                                   (Dcm_2C_OpType)1
# define DCM_2C_OP_TYPE_CLEAR                                        (Dcm_2C_OpType)2
# define DCM_2C_OP_TYPE_INVALID                                      (Dcm_2C_OpType)0xFF
# define DCM_2C_MEMBER_MASK                                          (Dcm_2C_SequencerType)0x01

# define DCM_2C_MEMBER_SRC_PID                                       (Dcm_2C_SequencerType)0x00
# define DCM_2C_MEMBER_MEM_BLOCK                                     (Dcm_2C_SequencerType)0x01
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_2E_ENABLED == STD_ON)
# define DCM_2E_OEMREPEATERPROXYDATA                                 /* not used */
#endif /* (DCM_SERVICE_2E_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
# if (DCM_SERVICE_31_ENABLED == STD_ON)
#  define DCM_RIDMGR_NUM_CLIENT_31                                   1
# else
#  define DCM_RIDMGR_NUM_CLIENT_31                                   0
# endif
# if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
#  define DCM_RIDMGR_NUM_CLIENT_OBD                                  1
# else
#  define DCM_RIDMGR_NUM_CLIENT_OBD                                  0
# endif
# if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
#  define DCM_RIDMGR_NUM_CLIENT_31_WWHOBD                            1
# else
#  define DCM_RIDMGR_NUM_CLIENT_31_WWHOBD                            0
# endif

# define DCM_RID_MGR_NUM_RID_CLIENTS                                 (Dcm_RidMgrRidClientType)(DCM_RIDMGR_NUM_CLIENT_31 + \
                                                                     DCM_RIDMGR_NUM_CLIENT_OBD + \
                                                                     DCM_RIDMGR_NUM_CLIENT_31_WWHOBD)

/* Client IDs */
# define DCM_RIDMGR_CLIENT_ID_31                                     (Dcm_RidMgrRidClientType)(0    +   0)
# define DCM_RIDMGR_CLIENT_ID_OBD                                    (Dcm_RidMgrRidClientType)(DCM_RIDMGR_CLIENT_ID_31 + DCM_RIDMGR_NUM_CLIENT_31)
# define DCM_RIDMGR_CLIENT_ID_31_WWHOBD                              (Dcm_RidMgrRidClientType)(DCM_RIDMGR_CLIENT_ID_OBD + DCM_RIDMGR_NUM_CLIENT_OBD)
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_85_ENABLED == STD_ON)
# define DCM_CTRL_DTC_ENABLE                                         (uint8)1
# define DCM_CTRL_DTC_DISABLE                                        (uint8)2
#endif /* (DCM_SERVICE_85_ENABLED == STD_ON) */
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
# define DCM_DSP_FBL_GET_PROG_CONDITIONS                             (Dcm_Dsp_OemFblResProgress)0
# define DCM_DSP_FBL_WAIT_FULL_COMM                                  (Dcm_Dsp_OemFblResProgress)1
#endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Datatype definitions
 ----------------------------------------------------------------------------- */

/* Use always this type to avoid different compilers' errors (warnings)*/
typedef uint8            Dcm_MsgAddInfoType;


typedef struct
{
  Dcm_MsgType         reqData;
  Dcm_MsgType         resData;
  Dcm_MsgLenType      reqDataLen;
  Dcm_MsgLenType      resDataLen;
  Dcm_MsgLenType      resMaxDataLen;
  Dcm_MsgAddInfoType  msgAddInfo;
}Dcm_MsgContextType;
#if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
typedef CONSTP2CONST(Dcm_CfgVariantMaskType, AUTOMATIC, DCM_CONST) Dcm_CfgVariantTablePtrType;
#endif
typedef uint8_least Dcm_CommStateType;
typedef uint8_least Dcm_ActivityStateType;
typedef uint8_least Dcm_ActivityStateTriggerType;

typedef struct
{
#if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
  Dcm_CfgVariantMaskType  CfgVariantMask;
#endif
  Dcm_ActivityStateType   ActivityState;
  Dcm_CommStateType       CommState;
#if (DCM_COM_MULTI_ID_ENABLED == STD_ON)
  Dcm_ComVariantIdType    ComVariantId;
#endif
}Dcm_StateMachineType;

typedef uint8_least  Dcm_TaskIdType;



#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
typedef uint8_least Dcm_PagedBufferClientType;
typedef uint8       Dcm_MemPagedBufferClientType;

typedef struct
{
  Dcm_MsgLenType               pageSize;
  Dcm_MsgLenType               readIdx;
  Dcm_MsgLenType               remainingData;
  Dcm_MemPagedBufferClientType clientId;
  Dcm_BitType    isPagedBufferActive : 1;
  Dcm_BitType    isPagedTxStarted    : 1;
  Dcm_BitType    isDataRequested     : 1;
}Dcm_PagedBufferStateType;

typedef P2FUNC(void, DCM_CODE, Dcm_PbUpdateFuncType) (Dcm_MsgType, Dcm_MsgLenType);
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
#if (DCM_PDUROUTER_ENABLED == STD_ON)
typedef P2VAR(Dcm_PduTransportInfoType, AUTOMATIC, DCM_VAR_NOINIT)   Dcm_PduTransportInfoPtrType;
typedef P2VAR(Dcm_PduRxTransportInfoType, AUTOMATIC, DCM_VAR_NOINIT) Dcm_PduRxTransportInfoPtrType;
typedef P2VAR(Dcm_PduTxTransportInfoType, AUTOMATIC, DCM_VAR_NOINIT) Dcm_PduTxTransportInfoPtrType;
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
typedef struct
{
  boolean           isReserved;
}Dcm_PruResourceType;
#endif /* ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
typedef uint8       Dcm_MemPeriodicHandleType;
typedef uint8_least Dcm_PeriodicHandleType;
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
typedef uint8 Dcm_ContextStateType;
typedef uint8 Dcm_DslCommStatusType;
typedef uint8 Dcm_DslResponseType;
typedef uint8 Dcm_StateLevelType;
typedef uint8 Dcm_DiagProtocolType;  /* PRQA S 3205 */ /* QAC 7.0:  The identifier '%s' is not used and could be removed. */ /* Used in specific configurations only! */

typedef struct
{
  Dcm_MsgType                   dataPtr;
  Dcm_MsgLenType                dataLength;
  Dcm_MsgLenType                maxBufferLength;
  Dcm_MsgLenType                maxBusPayloadLength;
#if (DCM_DSL_STORE_RXPDUID_ENABLED == STD_ON)
  PduIdType                     rxPduId;
#endif
  Dcm_ReqAddressingType         addrType;
  Dcm_DslResponseType           resType;
  Dcm_DslResponseType           rcrRpState;
  Dcm_ConnectionRefType         dslHandle;
  Dcm_DslCommStatusType         txConfStatus;
  Dcm_ContextStateType          contextState;
#if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
  boolean                       isConnectionLocked;
#endif
  Dcm_StateTransitionIndexType  stateTransRef;
  uint8                         serviceIndex;
#if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
    (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  Dcm_DiagProtocolType          protocolType;
#endif
  uint8                         pendingSessChgIdx;
}Dcm_DslInfoPoolType;

typedef uint8_least Dcm_DemMgrDemClientType;

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
typedef uint8_least Dcm_DidMgrDidClientType;
typedef struct
{
  uint32               lastDid;
  Dcm_MemDidHandleType did22Handle;
}Dcm_ExtReadDidStateType;/* PRQA S 3205 */ /* QAC 7.0:  The identifier '%s' is not used and could be removed. */ /* Used in specific configurations only! */
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
/* Shared data type for other service processors (e.g. 0x2C), for request analyzation*/
typedef struct
{
  Dcm_MemoryBlockDefType  memBlock;
  Dcm_BitType             addrParamSize : 4;
  Dcm_BitType             lenParamSize  : 4;
# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
  Dcm_MemMgrOpType        memOp;
# endif
  uint8                   protocolLength;
  uint8                   addrSizeBlockLen;
} Dcm_MemoryBlockDescType;

typedef P2VAR(Dcm_MemoryBlockDescType, AUTOMATIC, DCM_VAR_NOINIT) Dcm_MemMgrMemBlockDescPtr;
typedef P2VAR(Dcm_MemoryBlockDefType, AUTOMATIC, DCM_VAR_NOINIT)  Dcm_MemMgrMemBlockDefPtr;
typedef uint8 Dcm_MemMgrExtrInfoRsltType;
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
    (DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON))
typedef uint8 Dcm_MemObdIdHandleType;
typedef uint8_least Dcm_ObdIdHandleType;

typedef struct
{
  Dcm_MemObdIdHandleType handle;
  uint8                  id;
  boolean                isAvailabilityId;
}Dcm_ObdIdListItemType;

typedef P2VAR(Dcm_ObdIdListItemType, AUTOMATIC, DCM_VAR_NOINIT)       Dcm_ObdIdListItemPtrType;

typedef struct
{
  P2CONST(uint8, AUTOMATIC, DCM_CONST)   idLookUpTable;
  Dcm_ObdIdListItemPtrType               idOutList;      /* OUT: The list of supported PIDs to be processed later */
  Dcm_MsgType                            idInList;       /* IN:  The list of requested PIDs to be validated */
  boolean                                isMixedId;      /* OUT: Return wether the request contains mixed type of Ids */
# if(DCM_OBD_REQ_PID_DATA_ENABLED == STD_ON)
  boolean                                idHasReqData;   /* IN: FALSE - only IDs in request, TRUE - [ID + data] or IDs only */
# endif
  uint8                                  idCount;        /* IN: idListSize, OUT: idDescList size */
}Dcm_ObdIdDescType;

typedef P2VAR(Dcm_ObdIdDescType, AUTOMATIC, DCM_VAR_NOINIT)           Dcm_ObdIdDescPtrType;
#endif /* ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
(DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON))
typedef struct
{
  Dcm_MsgType       resData;
  Dcm_MsgLenType    availLen;
  uint8             statusMask;
  Dem_DTCOriginType origin;
}Dcm_ObdDtcRepeaterProxyContextType;
#endif /* ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_09_ENABLED == STD_ON)
typedef struct
{
  Dcm_ObdIdListItemType vidDescList[6];
  Dcm_MemDidHandleType  did22Handle;
  uint8                 vidIter;
}Dcm_09_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_09_ENABLED == STD_ON) */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
typedef uint8 Dcm_10_ProgressType;

typedef struct
{
  Dcm_10_ProgressType  Progress;
}Dcm_10_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_10_ENABLED == STD_ON) */
#if (DCM_SERVICE_11_ENABLED == STD_ON)
typedef struct
{
  uint8 dummy;
}Dcm_11_OemProxyType;
#endif /* (DCM_SERVICE_11_ENABLED == STD_ON) */
#if (DCM_SERVICE_11_ENABLED == STD_ON)
typedef struct
{
  uint8                resetLevel;
  Dcm_11_OemProxyType  oemProxy;
}Dcm_11_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_11_ENABLED == STD_ON) */
#if (DCM_SERVICE_14_ENABLED == STD_ON)
typedef struct
{
  uint32 dtcNum;
}Dcm_14_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_14_ENABLED == STD_ON) */
#if (DCM_SERVICE_19_ENABLED == STD_ON)
typedef struct
{
  Dcm_MsgType       resData;
  Dcm_MsgLenType    availLen;
}Dcm_19_ReadByStatusMaskContextType;

typedef P2CONST(uint8,AUTOMATIC, DCM_CONST) Dcm_19_RecordListPtrType; /* PRQA S 3205 */ /* QAC 7.0:  The identifier '%s' is not used and could be removed. */ /* Used in specific configurations only! */

typedef struct
{
# if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
  Dcm_19_RecordListPtrType  recordList;
# endif
  uint32                    dtcNum;
  Dem_DTCOriginType         origin;
  boolean                   allRecNumbers;
  uint8                     recordIterator;
  uint8                     recordNumber;
  uint8                     recordListSize;
  uint8                     reqRecordNumber;
}Dcm_19_ReadRecNumContextType;

typedef union
{ /* PRQA S 0750 */ /* QAC 7.0: A union type specifier has been defined. */ /* Used unions to save RAM. */
  Dcm_19_ReadRecNumContextType       recordContext;
# if (DCM_19_READ_BY_STATUS_MASK_ENABLED == STD_ON)
  Dcm_19_ReadByStatusMaskContextType maskContext;
# endif
}Dcm_19_SharedContextType;

typedef struct
{
  Dcm_19_SharedContextType  sharedContexts;
  boolean                   needsRecordUpdateDisabling;
}Dcm_19_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_19_ENABLED == STD_ON) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
typedef uint8 Dcm_22_ProgressType;

typedef struct
{
  Dcm_MsgType             ResData;
  Dcm_MsgLenType          DataPos;
  Dcm_22_ProgressType     Progress;
  Dcm_MemDidHandleType    CurDidHandle;
# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
  boolean                 IsFirstTime;
  boolean                 HasPagedDid;
# endif
  uint8                   DidCount;
  uint8                   CurDid;
}Dcm_22_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_23_ENABLED == STD_ON)
typedef struct
{
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
  Dcm_MemoryBlockDefType memBlockDef;
# else
  uint8 dummyItem;
# endif
}Dcm_23_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_23_ENABLED == STD_ON) */
#if (DCM_SERVICE_27_ENABLED == STD_ON)
typedef struct
{
  uint8   SecLevIdxOnGotSeed;
  boolean MayExecuteSendKey;
}Dcm_27_StateType;

typedef struct
{
  boolean IsGetSeedRequest;
  boolean IsZeroSeedRequest;
}Dcm_27_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
#if (DCM_SERVICE_28_ENABLED == STD_ON)
typedef struct
{
  boolean            RxState;
  boolean            TxState;
  uint8              MsgType;
  NetworkHandleType  SubNetId;
}Dcm_28_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_28_ENABLED == STD_ON) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
typedef uint8 Dcm_2A_ProgressType;

typedef struct
{
  uint8                   NumItems;
  uint8                   NextItem;
  uint8                   ProcessingItem;
  Dcm_MemPeriodicHandleType  TxHandle;
}Dcm_2A_StateType;

typedef struct
{
  Dcm_2A_ProgressType     Progress;
  uint8                   DidCount;
  uint8                   CurDid;
  uint8                   DidLength;
  Dcm_ConnectionRefType   reqConnId;
  Dcm_2A_MemRateType      Rate;
  Dcm_MemDidHandleType    Cur22DidHandle;
}Dcm_2A_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
typedef uint8 Dcm_2C_OpType;
typedef uint8 Dcm_2C_ProgressType;

typedef struct
{
  Dcm_2C_ProgressType         Progress;
  uint8                       CurrentItem;
  uint8                       CurDid;
  Dcm_2C_OpType               OpType;
  Dcm_2C_MemDidHandleType     NumOfItems;
  Dcm_2C_MemDidHandleType     CurDynDidHandle;
  Dcm_2C_MemDidHandleType     LastUsedDynDidHandle;
  Dcm_MemDidHandleType        CurDidHandle;
}Dcm_2C_RepeaterProxyContextType;

typedef struct
{
  boolean                 WaitingForReadEnd;
  Dcm_2C_MemDidHandleType CurUsedDidHandle;
  Dcm_2C_MemDidHandleType CurrentItem;
  Dcm_MsgType             ResData;
}Dcm_2C_ReadDataStateType;
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_2E_ENABLED == STD_ON)
typedef struct
{
  DCM_2E_OEMREPEATERPROXYDATA /* palceholder for OEM specific extensions */
  Dcm_MemDidHandleType    CurDid22Handle;
  Dcm_MemDidHandleType    CurDidHandle;
# if (DCM_2E_NVM_SUPPORT_ENABLED == STD_ON)
  boolean                 IsNvmAccessStarted;
# endif
}Dcm_2E_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_2E_ENABLED == STD_ON) */
#if (DCM_SERVICE_2F_ENABLED == STD_ON)
typedef struct
{
  Dcm_2F_MemInstHandleType CurDidHandle;
}Dcm_2F_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_2F_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
typedef uint8_least Dcm_RidMgrRidClientType;
# endif
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
typedef struct
{
# if(DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  Dcm_MemRidHandleType     CurRidHandle;
# endif
  Dcm_MemRidInstHandleType CurRidInstHandle;
}Dcm_31_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
typedef struct
{
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
  Dcm_MemoryBlockDefType memBlockDef;
# else
  uint8 dummyItem;
# endif
}Dcm_3D_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_3D_ENABLED == STD_ON) */
#if (DCM_SERVICE_87_ENABLED == STD_ON)
typedef struct
{
  uint8   linkControlHandle;
}Dcm_87_RepeaterProxyContextType;
#endif /* (DCM_SERVICE_87_ENABLED == STD_ON) */
#if (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON)
typedef struct
{
  uint8 sid;
}Dcm_UnspecSvc_RepeaterProxyContextType;
#endif /* (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON) */
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
typedef uint8 Dcm_Dsp_OemFblResProgress;

typedef struct
{
  Dcm_Dsp_OemFblResProgress Progress;
  Dcm_ConnectionRefType     ConnId;
}Dcm_Dsp_OemFblResContextType;
#endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */
typedef P2FUNC (Std_ReturnType, DCM_CODE, Dcm_RepeaterProxyFuncType) (void);

typedef union
{ /* PRQA S 0750 */ /* QAC 7.0: A union type specifier has been defined. */ /* Used unions to save RAM. */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
  Dcm_10_RepeaterProxyContextType dcm10_ProxyContext;
#endif
#if (DCM_SERVICE_11_ENABLED == STD_ON)
  Dcm_11_RepeaterProxyContextType dcm11_ProxyContext;
#endif
#if (DCM_SERVICE_14_ENABLED == STD_ON)
  Dcm_14_RepeaterProxyContextType dcm14_ProxyContext;
#endif
#if (DCM_SERVICE_19_ENABLED == STD_ON)
  Dcm_19_RepeaterProxyContextType dcm19_ProxyContext;
#endif
#if (DCM_SERVICE_22_ENABLED == STD_ON)
  Dcm_22_RepeaterProxyContextType dcm22_ProxyContext;
#endif
#if (DCM_SERVICE_23_ENABLED == STD_ON)
  Dcm_23_RepeaterProxyContextType dcm23_ProxyContext;
#endif
#if (DCM_SERVICE_27_ENABLED == STD_ON)
  Dcm_27_RepeaterProxyContextType dcm27_ProxyContext;
#endif
#if (DCM_SERVICE_28_ENABLED == STD_ON)
  Dcm_28_RepeaterProxyContextType dcm28_ProxyContext;
#endif
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
  Dcm_2A_RepeaterProxyContextType dcm2A_ProxyContext;
#endif
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
  Dcm_2C_RepeaterProxyContextType dcm2C_ProxyContext;
#endif
#if (DCM_SERVICE_2E_ENABLED == STD_ON)
  Dcm_2E_RepeaterProxyContextType dcm2E_ProxyContext;
#endif
#if (DCM_SERVICE_2F_ENABLED == STD_ON)
  Dcm_2F_RepeaterProxyContextType dcm2F_ProxyContext;
#endif
#if (DCM_SERVICE_31_ENABLED == STD_ON)
  Dcm_31_RepeaterProxyContextType dcm31_ProxyContext;
#endif
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
  Dcm_3D_RepeaterProxyContextType dcm3D_ProxyContext;
#endif
#if (DCM_SERVICE_87_ENABLED == STD_ON)
  Dcm_87_RepeaterProxyContextType dcm87_ProxyContext;
#endif
#if (DCM_SERVICE_A0_ENABLED == STD_ON)
  Dcm_A0_RepeaterProxyContextType dcmA0_ProxyContext;
#endif
#if (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON)
  Dcm_UnspecSvc_RepeaterProxyContextType dcmUnspecSvc_ProxyContext;
#endif
#if (DCM_USER_SERVICE_SUPPORT_ENABLED == STD_ON)
  Dcm_UserSvc_RepeaterProxyContextType   dcmUserSvc_ProxyContext;
#endif
}Dcm_RepeaterProxyContextPoolType;

#if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
# if (DCM_SERVICE_09_ENABLED == STD_ON) || \
     (DCM_OBD_READ_DTC_ENABLED == STD_ON)
typedef union
{ /* PRQA S 0750 */ /* QAC 7.0: A union type specifier has been defined. */ /* Used unions to save RAM. */
#  if (DCM_SERVICE_09_ENABLED == STD_ON)
  Dcm_09_RepeaterProxyContextType    dcm09_ProxyContext;
#  endif
#  if (DCM_OBD_READ_DTC_ENABLED == STD_ON)
  Dcm_ObdDtcRepeaterProxyContextType dcmObdDtc_ProxyContext;
#  endif
}Dcm_ObdRepeaterProxyContextPoolType;
# endif
#endif /* (DCM_OBD_SUPPORT_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Function prototypes
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

STATIC FUNC(void, DCM_CODE) Dcm_MsgContextMoveRel(sint32_least reqSteps, sint32_least resSteps);
#if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
STATIC FUNC(uint8_least, DCM_CODE) Dcm_Uint8LookUp(Dcm_CfgVariantTablePtrType variantTable, CONSTP2CONST(uint8, AUTOMATIC, DCM_CONST) lookUpTable, uint8 value);
#else
STATIC FUNC(uint8_least, DCM_CODE) Dcm_Uint8LookUp(CONSTP2CONST(uint8, AUTOMATIC, DCM_CONST) lookUpTable, uint8 value);
#endif
STATIC FUNC(void, DCM_CODE) Dcm_ProcessActivity(Dcm_ActivityStateTriggerType trigger);

LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DebugInit(void);

/* Event manager */
STATIC FUNC(void, DCM_CODE) Dcm_EvMgrSetEvent(Dcm_TaskIdType taskId, Dcm_EventType ev);
STATIC FUNC(void, DCM_CODE) Dcm_EvMgrClearEvent(Dcm_TaskIdType taskId, Dcm_EventType ev);
LOCAL_INLINE FUNC(Dcm_EventType, DCM_CODE) Dcm_EvMgrGetEvent(Dcm_TaskIdType taskId);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_EvMgrInit(void);

/* Timer manager */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_TmrMgrInit(void);

#if (DCM_RESTART_TIMER_USAGE_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrRestartTimer(Dcm_TimerIdType timerId, Dcm_TimerCounterType ticks);
#endif
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrStartTimer(Dcm_TimerIdType timerId, Dcm_TimerCounterType ticks);
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrNotSafeStartTimer(Dcm_TimerIdType timerId, Dcm_TimerCounterType ticks);
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrStopTimer(Dcm_TimerIdType timerId);
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrNotSafeStopTimer(Dcm_TimerIdType timerId);

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_StartPagedProcessing(Dcm_PagedBufferClientType clientId);
STATIC FUNC(void, DCM_CODE) Dcm_ProcessPage(uint16 FilledPageLen);
LOCAL_INLINE FUNC(void, DCM_CODE) Dsd_PagedBufferDataRequest(DCM_CONTEXT_PARAM_DEF_ONLY);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DcmUpdatePage(DCM_CONTEXT_PARAM_DEF_ONLY);
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
#if (DCM_PDUROUTER_ENABLED == STD_ON)
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_MainProvideTxBuffer(Dcm_PduTxTransportInfoPtrType pTxTranspObj, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length);
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ConcurProvideTxBuffer(Dcm_PduTxTransportInfoPtrType pTxTranspObj, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length);
# endif
STATIC FUNC(Dcm_PduRxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjAllocRxByConnId(Dcm_ConnectionRefType connId);
# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjAllocTxByConnId(Dcm_ConnectionRefType connId);
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjAllocTxByRxTObj(Dcm_PduRxTransportInfoPtrType pRxTranspObj);
# endif
STATIC FUNC(Dcm_PduRxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetRxByConnId(Dcm_ConnectionRefType connId);
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetTxByConnId(Dcm_ConnectionRefType connId);
LOCAL_INLINE FUNC(Dcm_PduRxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetRxByRxPduId(PduIdType DcmRxPduId);
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetTxByTxPduId(PduIdType DcmTxPduId);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_TObjFree(Dcm_PduTransportInfoPtrType pTranspObj);
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CheckAvailableContext(Dcm_PduRxTransportInfoPtrType pRxTranspObj);
CONTEXT_FUNC_LOC FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideContext(Dcm_PduRxTransportInfoPtrType pRxTranspObj);
# if(DCM_NUM_CONTEXTS > 1)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DoDispatchContext(Dcm_PduRxTransportInfoPtrType pRxTranspObj);
# endif
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruReleaseResource(Dcm_PeriodicHandleType handle);
STATIC FUNC(boolean, DCM_CODE) Dcm_PruMayProcessRequest(void);
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_PruProvideTxBuffer(Dcm_PduTxTransportInfoPtrType pTxTranspObj, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length);
#endif /* ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
STATIC FUNC(void, DCM_CODE) Dcm_PruReleaseResource(Dcm_PeriodicHandleType handle);
LOCAL_INLINE FUNC(Dcm_PeriodicHandleType, DCM_CODE) Dcm_PruConvTxPduIdToHandle(PduIdType DcmTxPduId);
#endif /* ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
/* DSL PRU API */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruInit(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruTransmit(Dcm_PeriodicHandleType handle, uint8 length);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruReserveConnection(Dcm_ConnectionRefType connId);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruReleaseConnection(void);
# if (DCM_DSL_PRU_NEEDS_CONNECTION_LOCK == STD_ON)
LOCAL_INLINE FUNC(Dcm_ConnectionRefType, DCM_CODE) Dcm_PruGetUsedConnection(void);
# endif

/* PDU-R API */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruTxConfirmation(PduIdType DcmTxPduId, NotifResultType Result);

/* Virtual functions - to be implemented by the corresponding transmission type class */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruOnInit(void);
LOCAL_INLINE FUNC(Dcm_PeriodicHandleType, DCM_CODE) Dcm_PruAllocateResource(void);
LOCAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_PruGetDataPtr(Dcm_PeriodicHandleType handle);
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_PruDoTransmit(Dcm_PeriodicHandleType handle, uint8 length);
/* To be defined by the concrete transmiter type 
STATIC/LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruReleaseResource(Dcm_PeriodicHandleType handle);
*/
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslInit(void);
STATIC FUNC(void, DCM_CODE) Dcm_DslDoPostProcessing(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslCommStatusType status);
/* DSL Low Level API */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_Init(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_StateTask(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_TimerTask(void);
STATIC FUNC(void, DCM_CODE) Dcm_DslLL_StartTransmission(DCM_CONTEXT_PARAM_DEF_ONLY);
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_AllocateRxResource(Dcm_ConnectionRefType connId);
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DslLL_IsRxResourceLocked(Dcm_ConnectionRefType connId);
#endif
STATIC FUNC(void, DCM_CODE)       Dcm_DslLL_ReleaseRxResource(Dcm_ConnectionRefType connId);
#if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_ReleaseReservedRxResource(Dcm_ConnectionRefType connId);
#endif

/* DSL High Level API */
LOCAL_INLINE FUNC(Dcm_DslCommStatusType, DCM_CODE) Dcm_DslHL_StartReception(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_ConnectionRefType connId);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslHL_ReceptionFinished(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslCommStatusType status);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslHL_TransmissionFinished(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslCommStatusType status);

/* DSL OEM Level API */
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
STATIC FUNC(boolean, DCM_CODE) Dcm_DoLock(Dcm_ConnectionRefType connId);
STATIC FUNC(void, DCM_CODE) Dcm_DoUnLock(Dcm_ConnectionRefType connId);
STATIC FUNC(void, DCM_CODE) Dcm_SendSpontaneousResponse(Dcm_ConnectionRefType connId, Dcm_MsgType dataPtr, Dcm_MsgLenType dataLen);
#endif
STATIC FUNC(void, DCM_CODE) Dcm_SendResponsePending(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslResponseType owner);
#if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_DslFreeSessionOwner(void);
#endif
STATIC FUNC(uint8, DCM_CODE) Dcm_CheckServiceState(Dcm_StateFilterIndexType ref, Dcm_StateLevelType stateLevel, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) pErrorCode);
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckServiceStateMatch(Dcm_StateMaskType cfgStates, uint8_least stateGrpIdx, Dcm_StateLevelType stateLevel);
STATIC FUNC(void, DCM_CODE) Dcm_ExecuteStateTransition(Dcm_StateTransitionIndexType ref);
STATIC FUNC(Dcm_SesCtrlType, DCM_CODE) Dcm_GetCurrentSession(void);

LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DsdDispatcher(DCM_CONTEXT_PARAM_DEF_ONLY);
STATIC FUNC(void, DCM_CODE) Dcm_SetNegResponse(Dcm_NegativeResponseCodeType errorCode);
STATIC FUNC(void, DCM_CODE) Dcm_ProcessingDone(void);

#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DemMgrInit(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DemMgrReleaseDemClient(Dcm_DemMgrDemClientType clientId);
STATIC FUNC(boolean, DCM_CODE) Dcm_DemMgrLockDemUdsClient(Dcm_DemMgrDemOpType demOp);
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DemMgrIsDemClientLocked(Dcm_DemMgrDemOpType demOp, Dcm_DemMgrDemClientType clientId);
# if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
     (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
STATIC FUNC(boolean, DCM_CODE) Dcm_DemMgrStealLockDemUdsClient(Dcm_DemMgrDemOpType demOp);
# endif
#endif
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DemMgrRequestDisableDtcUpdate(Dcm_DemMgrDemClientType clientId);
DEMMGR_FUNC_LOC FUNC(void, DCM_CODE)    Dcm_DemMgrRequestEnableDtcUpdate(Dcm_DemMgrDemClientType clientId);

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
STATIC FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_DidMgrGetDidHandle(uint16 did, Dcm_MemDidHandlePtrType pDidLookUpTable, Dcm_CfgVariantTablePtrType pVariantTable);
# else
STATIC FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_DidMgrGetDidHandle(uint16 did, Dcm_MemDidHandlePtrType pDidLookUpTable);
# endif
STATIC FUNC(boolean, DCM_CODE) Dcm_DidMgrAnalyseDid(Dcm_DidMgrDidClientType clientId, Dcm_StateFilterIndexType StateFilterIdx);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DidMgrInit(void);
# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DidMgrReleaseDidClient(Dcm_DidMgrDidClientType clientId);
STATIC FUNC(boolean, DCM_CODE) Dcm_DidMgrLockDidClient(Dcm_DidHandleType did22Handle, Dcm_DidMgrDidClientType clientId);
# endif

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrReadDid(Dcm_DidHandleType did22Handle, Dcm_MsgType resDataPtr, Dcm_DidMgrDidClientType clientId, Dcm_NegativeResponseCodePtrType pErrorCode);
# if (DCM_SERVICE_2E_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrWriteDid(Dcm_DidHandleType did22Handle, Dcm_DidHandleType did2EHandle, Dcm_MsgType reqDataPtr, Dcm_MsgLenType reqDataLen);
# endif
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_MemAccInit(void);
STATIC FUNC(uint32, DCM_CODE) Dcm_MemAccByteStream2AtomicData(Dcm_MsgType byteStream, uint8_least len);
STATIC FUNC(Dcm_MemMgrExtrInfoRsltType, DCM_CODE) Dcm_MemAccExtractMemoryBlockInfo(Dcm_MemMgrMemBlockDescPtr pMemBlockInfo);

# if (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_MemAccHwAbInit(void);
LOCAL_INLINE FUNC(Dcm_ApplDataPtrType, DCM_CODE) Dcm_MemAccHwAbMakePointer(Dcm_MemAddrType addr);
# endif

# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_MemAccCheckMemBlockState(void);
#  if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_MemAccCheckMemoryBlock(Dcm_MemMgrMemBlockDescPtr        pMemBlockInfo,
                                                       CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) lookUpTable,
                                                       Dcm_CfgVariantTablePtrType       pVariantTable,
                                                       CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable);
#  else
STATIC FUNC(void, DCM_CODE) Dcm_MemAccCheckMemoryBlock(Dcm_MemMgrMemBlockDescPtr        pMemBlockInfo,
                                                       CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) lookUpTable,
                                                       CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable);
#  endif
#  if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_MemAccMemBlockLookUp(CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) pLookUpTable,
                                                                           Dcm_CfgVariantTablePtrType pVariantTable,
                                                              CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable,
                                                                           Dcm_MemMgrMemBlockDefPtr pMemBlockInfo);
#  else
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_MemAccMemBlockLookUp(CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) pLookUpTable,
                                                              CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable,
                                                                           Dcm_MemMgrMemBlockDefPtr pMemBlockInfo);
#  endif
# else
STATIC FUNC(void, DCM_CODE) Dcm_MemAccCheckMemoryBlock(Dcm_MemMgrMemBlockDescPtr pMemBlockInfo);
# endif
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
    (DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON))
STATIC FUNC(void, DCM_CODE) Dcm_ObdMgrParseIds(Dcm_ObdIdDescPtrType idDescPtr);
#endif /* ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
(DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON))
STATIC FUNC(void, DCM_CODE) Dcm_ObdMgrReadDtcByStatusMask(uint8 statusMask, Dem_DTCOriginType origin);
STATIC FUNC(void, DCM_CODE) Dcm_ObdMgrPostReadDtcByStatusMask(void);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_ObdMgrReadDtcRepeaterProxyGetData(void);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_ObdMgrReadDtcRepeaterProxyProcess(void);
# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_DcmUpdatePage_Obd(Dcm_MsgType dataPtr, Dcm_MsgLenType dataLen);
# endif
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ObdMgrGetDtc(P2VAR(Dcm_MsgType, AUTOMATIC,DCM_VAR_NOINIT) pDataPtr, Dcm_MsgLenPtrType availLenPtr);
#endif /* ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_01_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_01_ProcessPid(Dcm_ObdIdListItemPtrType pidDescPtr);
#endif /* (DCM_SERVICE_01_ENABLED == STD_ON) */
#if (DCM_SERVICE_04_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_04_RepeaterProxyProcess(void);
#endif /* (DCM_SERVICE_04_ENABLED == STD_ON) */
#if (DCM_SERVICE_06_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_06_ProcessMid(Dcm_ObdIdListItemPtrType midDescPtr);
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_06_ReadDataId(uint8 midHandle, Dcm_RteDataPtrType resData);
#endif /* (DCM_SERVICE_06_ENABLED == STD_ON) */
#if (DCM_SERVICE_08_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_08_ProcessTid(Dcm_ObdIdListItemPtrType tidDescPtr);
#endif /* (DCM_SERVICE_08_ENABLED == STD_ON) */
#if (DCM_SERVICE_09_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_09_ProcessVid(Dcm_ObdIdListItemPtrType vidDescPtr);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_09_RepeaterProxyProcess(void);
#endif /* (DCM_SERVICE_09_ENABLED == STD_ON) */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_10_RepeaterProxyChanger(void);
# endif
#endif /* (DCM_SERVICE_10_ENABLED == STD_ON) */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_10_RepeaterProxyProcess(void);
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_10_ChgSession(Dcm_SesCtrlType curSession, Dcm_SesCtrlType newSession);
#endif /* (DCM_SERVICE_10_ENABLED == STD_ON) */
#if (DCM_SERVICE_11_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_11_RepeaterProxyProcess(void);
LOCAL_INLINE  FUNC(void, DCM_CODE) Dcm_11_PrepareReset(void);
#endif /* (DCM_SERVICE_11_ENABLED == STD_ON) */
#if (DCM_SERVICE_14_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_14_RepeaterProxyProcess(void);
#endif /* (DCM_SERVICE_14_ENABLED == STD_ON) */
#if (DCM_SERVICE_19_ENABLED == STD_ON)
# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_DcmUpdatePage_19(Dcm_MsgType dataPtr, Dcm_MsgLenType dataLen);
# endif

# if (DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_07_ENABLED == STD_ON)
LOCAL_INLINE FUNC(uint8, DCM_CODE) Dcm_19_GetTranslationFormat(void);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_GetNumDtcByStatusMaskData(Dem_DTCOriginType          origin,
                                                                                            Dem_DTCKindType            dtcKind,
                                                                                            Dem_DTCStatusMaskType      dtcStatusMask,
                                                                                            Dem_FilterWithSeverityType filterWithSeverity,
                                                                                            Dem_DTCSeverityType        dtcSeverity);
# endif

# if (DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_19_ProcessReportNumDtcByStatusMask(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_ProcessNumDtcByStatusMaskData(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind);
# endif

# if (DCM_19_READ_BY_STATUS_MASK_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_19_02_0A_0F_13_15_RepeaterProxyGetData(void);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_02_0A_0F_13_15_GetData(P2VAR(Dcm_MsgType, AUTOMATIC,DCM_VAR_NOINIT) pDataPtr, Dcm_MsgLenPtrType availLenPtr);
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_ReportDtcByStatusMaskData(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind);
# endif

# if (DCM_READ_DTC_SUBFUNC_02_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0F_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_13_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_19_ProcessReportDtcByStatusMask(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind);
# endif

# if (DCM_READ_DTC_SUBFUNC_03_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_03_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr);
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_04_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_04_CopyFreezeFrames(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr, uint8 recId);
LOCAL_INLINE FUNC(Dem_ReturnGetSizeOfFreezeFrameType, DCM_CODE) Dcm_19_04_GetSizeOfFreezeFrames(Dcm_MsgLenPtrType  totalSize);
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_PrepareDtcAndStatusByteReport(Dcm_19_RecordListPtrType iterList, uint8 listSize);
#  else
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_PrepareDtcAndStatusByteReport(void);
#  endif
# endif

# if (DCM_READ_DTC_SUBFUNC_05_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_05_CopyFreezeFrames(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr);
LOCAL_INLINE FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_19_05_GetSizeOfFreezeFrames(void);
# endif

# if (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_19_06_10_Process(Dem_DTCOriginType origin);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_06_10_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_06_10_CopyExtDataRecord(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr, uint8 recId);
LOCAL_INLINE FUNC(Dem_ReturnGetSizeOfExtendedDataRecordByDTCType, DCM_CODE) Dcm_19_06_10_GetSizeOfExtDataRecords(Dcm_MsgLenPtrType totalSize);
# endif

# if (DCM_READ_DTC_SUBFUNC_07_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_07_GetData(Dem_DTCKindType dtcKind);
# endif

# if (DCM_READ_DTC_SUBFUNC_08_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_08_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_08_Process(void);
# endif

# if (DCM_READ_DTC_SUBFUNC_0B_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0C_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0D_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0E_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_19_ProcessReportDtcByOccurrenceTime(Dem_DTCRequestType DTCRequest);
# endif

# if (DCM_READ_DTC_SUBFUNC_14_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_14_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr);
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_14_Process(void);
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_19_RecIdIterInit(uint8 reqRecId, Dcm_19_RecordListPtrType iterList, uint8 listSize);
#  else
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_19_RecIdIterInit(uint8 reqRecId);
#  endif
STATIC FUNC(void, DCM_CODE) Dcm_19_RecIdIterReset(void);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_19_RecIdIterNext(P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) recId);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_19_RecIdIterGoBack(void);
# endif
#endif /* (DCM_SERVICE_19_ENABLED == STD_ON) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_22_RepeaterProxyDispatcher(void);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_22_RepeaterProxyProcess(void);

LOCAL_INLINE FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_22_FindDid(uint16 did);
/* OEM specific virtual calls */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_22_OemInit(DCM_UDS_CONTEXT_PARAM_DEF_ONLY);
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_23_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_23_ReadMemoryBlock(Dcm_MsgType tgtAddr, Dcm_MemMgrMemBlockDefPtr memBlockDef, Dcm_NegativeResponseCodePtrType pErrorCode);
#endif /* (DCM_SERVICE_23_ENABLED == STD_ON) */
#if (DCM_SERVICE_23_ENABLED == STD_ON)
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_23_ReadRepeaterProxy(void);
# endif
#endif /* (DCM_SERVICE_23_ENABLED == STD_ON) */
#if (DCM_SERVICE_27_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_27_RepeaterProxyGetSeed(void);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_27_RepeaterProxySendKey(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_27_OemInit(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_27_StateTask(void);
STATIC FUNC(void, DCM_CODE) Dcm_27_InitSeedKeyState(void);
STATIC FUNC(Dcm_SecLevelType, DCM_CODE) Dcm_GetCurrentSecurityLevel(void);
#endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
#if (DCM_SERVICE_28_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_28_RepeaterProxyProcess(void);
/* virtual functions for service processor 0x28 */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_28_EnableCommunication(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_28_InterpretParams(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_28_PostHandling(void);
# if (DCM_28_ANY_COM_PARAM_ENABLED == STD_ON)
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_28_HasValidParams(void);
# endif
#endif /* (DCM_SERVICE_28_ENABLED == STD_ON) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
/* Tasks */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_StateTask(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerTask(Dcm_EventType ev);

/* Sub-function processors */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_ProcessUpdateScheduler(Dcm_2A_RateType rate);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_ProcessStopScheduler(void);

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2A_RepeaterProxyDispatcher(void);

/* Utils */
LOCAL_INLINE FUNC(Dcm_2A_RateType, DCM_CODE) Dcm_2A_FindSubFunction(uint8 subFuncId);
STATIC FUNC(uint8_least, DCM_CODE) Dcm_2A_SchedulerGetItemPos(Dcm_DidHandleType didHandle22);
LOCAL_INLINE FUNC(uint8_least, DCM_CODE) Dcm_2A_SchedulerGetFreeItemPos(void);

STATIC FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopAll(void);
STATIC FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopItem(uint8_least itemPos);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopDid(Dcm_DidHandleType didHandle2A);
# if (DCM_SERVICE_2C_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopDidById(uint16 did);
# endif
LOCAL_INLINE FUNC(uint8_least, DCM_CODE) Dcm_2A_SchedulerGetAvailItemPos(Dcm_DidHandleType didHandle22);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerEnableAddedDids(Dcm_2A_RateType rate);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerRemoveAddedDids(void);
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_2A_SchedulerIsAlreadyAddedDid(Dcm_DidHandleType didHandle22);
LOCAL_INLINE FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_2A_FindDid(uint16 did);
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_StateTask(void);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2C_RepeaterProxyAddDidDispatcher(void);
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_2C_RepeaterProxyReadData(void);

STATIC FUNC(void, DCM_CODE) Dcm_2C_FinalizeDidDefinition(Dcm_2C_DidHandleType dynDidHandle);
STATIC FUNC(Dcm_2C_DidHandleType, DCM_CODE) Dcm_2C_AnalyzeDynDid(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_ClearDynDid(void);
LOCAL_INLINE FUNC(Dcm_2C_OpType, DCM_CODE) Dcm_2C_FindSubFunction(uint8 subFuncId);
# if (DCM_2C_DEF_DYN_ID_BY_DID_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_DefineDynDidByDid(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_AppendPidDefinition(Dcm_2C_DidHandleType dynDidHandle, Dcm_2C_DidHandleType numOfElements);
# endif
# if (DCM_2C_DEF_DYN_ID_BY_MEM_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_DefineDynDidByMem(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_AppendMemoryDefinition(Dcm_2C_DidHandleType dynDidHandle);
# endif

STATIC FUNC(void, DCM_CODE) Dcm_2C_ClearDynDefTable(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_ClearSingleDid(Dcm_2C_DidHandleType dynDidHandle);
STATIC FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_2C_CalcResDataLen(Dcm_2C_DidHandleType dynDidHandle, Dcm_2C_DidHandleType numOfItems);

STATIC FUNC(boolean, DCM_CODE) Dcm_2C_IsDidAvailable(uint16 did);
LOCAL_INLINE FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_2C_FindDid(uint16 did);
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_2E_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2E_RepeaterProxyDispatcher(void);
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2E_RepeaterProxyProcess(void);

LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2E_OemInit(void);
# if (DCM_2E_OEM_CONDITION_CHECK_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2E_OemConditionCheck(uint16 did, Dcm_NegativeResponseCodePtrType pErrorCode);
# endif
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2E_OemPostProcess(Dcm_ConfirmationStatusType status);
#endif /* (DCM_SERVICE_2E_ENABLED == STD_ON) */
#if (DCM_SERVICE_2F_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2F_RepeaterProxyProcess(void);
LOCAL_INLINE FUNC(Dcm_2F_InstHandleType, DCM_CODE) Dcm_2F_FindSubFunction(uint8 subFuncId, Dcm_DidHandleType didRef);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2F_ReturnControlToECU(void);
#endif /* (DCM_SERVICE_2F_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_RidMgrInit(void);
# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_RidMgrReleaseRidClient(Dcm_RidMgrRidClientType clientId);
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_RidMgrLockRidClient(Dcm_RidHandleType rid31Handle, Dcm_RidMgrRidClientType clientId);
# endif
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_31_RepeaterProxyProcess(void);
LOCAL_INLINE FUNC(Dcm_RidInstHandleType, DCM_CODE) Dcm_31_FindSubFunction(uint8 subFuncId, Dcm_RidHandleType ridRef);
LOCAL_INLINE FUNC(Dcm_RidHandleType, DCM_CODE) Dcm_31_FindRid(uint16 rid);
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_3D_WriteMemoryBlock(Dcm_MsgType srcAddr, Dcm_MemMgrMemBlockDefPtr memBlockDef, Dcm_NegativeResponseCodePtrType pErrorCode);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_3D_WriteData(Dcm_MemMgrMemBlockDefPtr memInfo);
#endif /* (DCM_SERVICE_3D_ENABLED == STD_ON) */
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_3D_WriteDataVirtual(Dcm_MemMgrMemBlockDefPtr memInfo);
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_3D_WriteRepeaterProxy(void);
# endif
#endif /* (DCM_SERVICE_3D_ENABLED == STD_ON) */
#if (DCM_SERVICE_87_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_87_RepeaterProxyProcess(void);
LOCAL_INLINE  FUNC(void, DCM_CODE) Dcm_87_PrepareLinkControl(uint8 linkControlHandle);
#endif /* (DCM_SERVICE_87_ENABLED == STD_ON) */
#if (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_UnspecSvc_RepeaterProxy(void);
#endif /* (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON) */
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DspInit(void);
CONTEXT_FUNC_LOC FUNC(void, DCM_CODE) Dcm_DspStateTask(DCM_CONTEXT_PARAM_DEF_ONLY);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DspConfirmation(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_ConfirmationStatusType status);
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DspOemFblResProcessor(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DspOemFblResInit(void);
#endif
#if (DCM_USE_SAFE_RESET_ENABLED == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DspOemPerformReset(void);
#endif

STATIC FUNC(void, DCM_CODE) Dcm_RegisterRepeaterProxy(Dcm_RepeaterProxyFuncType pProxy);

#define DCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ External function prototypes
 ----------------------------------------------------------------------------- */

#define DCM_APPL_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DCM_SERVICE_23_ENABLED == STD_ON)
# if (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)
#  if (DCM_MEMORY_ACCESS_TEST_ENABLED == STD_ON)
extern FUNC(void, DCM_APPL_CODE) TscDcm_ReadMemAccess(Dcm_MsgType tgtAddr, uint32 srcAddr, uint32 len); /* PRQA S 3447 */ /* QAC 7.0: '%s' has external linkage but this declaration is not in a header file.*/ /* Extern declaration for the testsuite only */
#  endif
# endif
#endif /* (DCM_SERVICE_23_ENABLED == STD_ON) */
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
# if (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)
#  if (DCM_MEMORY_ACCESS_TEST_ENABLED == STD_ON)
extern FUNC(void, DCM_APPL_CODE) TscDcm_WriteMemAccess(uint32 tgtAddr, Dcm_MsgType srcAddr, uint32 len);/* PRQA S 3447 */ /* QAC 7.0: '%s' has external linkage but this declaration is not in a header file.*/ /* Extern declaration for the testsuite only */
#  endif
# endif
#endif /* (DCM_SERVICE_3D_ENABLED == STD_ON) */
#define DCM_APPL_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ Uninitialized RAM 8Bit definitions
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if(DCM_NUM_CONTEXTS > 1)
STATIC VAR(Dcm_ContextIdType, DCM_VAR_NOINIT) dcmCtxtMgrCurContextId;
#endif

STATIC VAR(uint8, DCM_VAR_NOINIT) dcmActiveTimerCounter;

#if (DCM_PDUROUTER_ENABLED == STD_ON)
# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON) && \
     (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_VAR_NOINIT) dcmSemaphoreAllocateTx;
# endif
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
STATIC VAR(uint8, DCM_VAR_NOINIT) dcmPruBuffer[7];/* USDT message can handle up to 7 bytes of data and SID only */
#endif /* ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
STATIC VAR(uint8, DCM_VAR_NOINIT) dcmDslBufferRcrRpTx[DCM_NUM_CONTEXTS][3];

#if (DCM_SERVICE_19_ENABLED == STD_ON)
# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
#  if (DCM_READ_DTC_SUBFUNC_02_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_03_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_08_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_0A_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_13_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_14_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_15_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_42_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_VAR_NOINIT)    dcm19_PbDispSubfunc[DCM_NUM_CONTEXTS];
#  endif
# endif
#endif /* (DCM_SERVICE_19_ENABLED == STD_ON) */
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_VAR_NOINIT) dcmDsp_RespBuffer[7]; /* PRQA S 3218*/ /* File scope static, 'xxx', only accessed in one function. */
#endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */
#define DCM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ Uninitialized RAM 32Bit definitions
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define DCM_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ Uninitialized RAM unspecified definitions
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

STATIC VAR(Dcm_StateMachineType, DCM_VAR_NOINIT) dcmStateMachine;

#if (DCM_DEV_ERROR_DETECT == STD_ON)
STATIC VAR(uint16, DCM_VAR_NOINIT) dcmDebugInitPattern;
#endif

STATIC VAR(Dcm_EventType, DCM_VAR_NOINIT) dcmEvMgrEventRegisters[DCM_NUM_TASKS];
STATIC VAR(uint8, DCM_VAR_NOINIT) dcmEvMgrNumActiveTasks;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
STATIC VAR(Dcm_PagedBufferStateType, DCM_VAR_NOINIT)  dcmPBStateMachine[DCM_NUM_CONTEXTS];
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
#if ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
STATIC VAR(Dcm_PruResourceType, DCM_VAR_NOINIT) dcmPruResource;
#endif /* ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
STATIC VAR(Dcm_ConnectionRefType, DCM_VAR_NOINIT) dcmPruCurrentConnection;
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
STATIC VAR(Dcm_TimerSettingType, DCM_VAR_NOINIT) dcmDslTimerSettings; /* not context specific, since the secondary context always resets the session to the default -> same timings!!!*/
STATIC VAR(Dcm_DslInfoPoolType, DCM_VAR_NOINIT)  dcmDslInfoPool[DCM_NUM_CONTEXTS];

STATIC VAR(Dcm_MsgContextType, DCM_VAR_NOINIT)            dcmDsdMsgContext[DCM_NUM_CONTEXTS];
STATIC VAR(Dcm_NegativeResponseCodeType, DCM_VAR_NOINIT)  dcmDsdErrorRegister[DCM_NUM_CONTEXTS];

#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
STATIC VAR(Dcm_MemDemMgrDemOpType, DCM_VAR_NOINIT)  dcmDemMgrResourceMap[DCM_DEMMGR_NUM_DEM_CLIENTS];
#endif
#if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
STATIC VAR(uint8, DCM_VAR_NOINIT)                   dcmDemMgrDtcUpdateRegister;
#endif

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
STATIC VAR(Dcm_MemDidHandleType, DCM_VAR_NOINIT)  dcmDidMgrResourceMap[DCM_DID_MGR_NUM_DID_CLIENTS];
# endif
# if (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)
STATIC VAR(Dcm_ExtReadDidStateType, DCM_VAR_NOINIT)  dcmDidMgrExtReadDidState;
# endif
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON))
# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
STATIC VAR(boolean, DCM_VAR_NOINIT) dcmObdMgr_PbIsFirstTime;
# endif
#endif /* ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_27_ENABLED == STD_ON)
STATIC VAR(Dcm_27_StateType, DCM_VAR_NOINIT) dcmSeedKeyProxyParam;
#endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
/* Local context information storing (for each DID) */
STATIC VAR(Dcm_2A_StateType, DCM_VAR_NOINIT) dcm2A_ProcessorState;
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
STATIC VAR(Dcm_2C_ReadDataStateType, DCM_VAR_NOINIT)  dcm2C_ReadDataState;
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
STATIC VAR(Dcm_MemRidHandleType, DCM_VAR_NOINIT)  dcmRidMgrResourceMap[DCM_RID_MGR_NUM_RID_CLIENTS];
# endif
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
STATIC VAR(Dcm_Dsp_OemFblResContextType, DCM_VAR_NOINIT)  dcmDsp_OemFblResponderContext;
#endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */
STATIC VAR(Dcm_RepeaterProxyFuncType, DCM_VAR_NOINIT) dcmRepeatedProxyCallBack[DCM_NUM_CONTEXTS];
/* Repeater shared context storage */
STATIC VAR(Dcm_RepeaterProxyContextPoolType, DCM_VAR_NOINIT) dcmRepeatedProxyContexts[DCM_NUM_UDS_CONTEXTS]; /* PRQA S 0759 */ /* QAC 7.0: An object of union type has been defined. */ /* Used unions to save RAM. */

#if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
# if (DCM_SERVICE_09_ENABLED == STD_ON) || \
     (DCM_OBD_READ_DTC_ENABLED == STD_ON)
/* Repeater shared context storage */
STATIC VAR(Dcm_ObdRepeaterProxyContextPoolType, DCM_VAR_NOINIT) dcmObdRepeatedProxyContexts; /* PRQA S 0759 */ /* QAC 7.0: An object of union type has been defined. */ /* Used unions to save RAM. */
# endif
#endif /* (DCM_OBD_SUPPORT_ENABLED == STD_ON) */
#define DCM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ ROM 8Bit definitions
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DCM_PDUROUTER_ENABLED == STD_ON)
# if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
     (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
STATIC CONST(Dcm_ContextIdType, DCM_CONST) dcmDslLLClientSvc2ContextMap[3][3]= /* PRQA S 3218*/ /* File scope static, 'xxx', only accessed in one function. */
{
  {DCM_CONTEXT_ID_INVALID, DCM_CONTEXT_ID_OBD,      DCM_CONTEXT_ID_OBD}, /* OBD SIDs 0x00-0x0f */
  {DCM_CONTEXT_ID_UDS,     DCM_CONTEXT_ID_OBD,      DCM_CONTEXT_ID_UDS}, /* WWH-OBD SIDs 0x14, 0x19, 0x22 and 0x31 */
  {DCM_CONTEXT_ID_UDS,     DCM_CONTEXT_ID_INVALID,  DCM_CONTEXT_ID_UDS}  /* Other UDS services */
};
# endif

# if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
     (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
STATIC CONST(uint8, DCM_CONST) dcmDslLLClientSvc2Protocol[3][3]= /* PRQA S 3218*/ /* File scope static, 'xxx', only accessed in one function. */
{
  {DCM_DIAG_PROTOCOL_OBD,  DCM_DIAG_PROTOCOL_OBD,     DCM_DIAG_PROTOCOL_OBD}, /* OBD SIDs 0x00-0x0f */
  {DCM_DIAG_PROTOCOL_UDS,  DCM_DIAG_PROTOCOL_WWHOBD,  DCM_DIAG_PROTOCOL_UDS}, /* WWH-OBD SIDs 0x14, 0x19, 0x22 and 0x31 */
  {DCM_DIAG_PROTOCOL_UDS,  DCM_DIAG_PROTOCOL_UDS,     DCM_DIAG_PROTOCOL_UDS}  /* Other UDS services */
};
# endif
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
/* default memory info extraction to NRC mapping */
STATIC CONST(Dcm_NegativeResponseCodeType, DCM_CONST) dcmMemMgrExtrInfo2NrcMap[] =
{
  DCM_E_OK,                                    /*DCM_MEMMGR_EXTR_INFO_OK*/
  DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT, /*DCM_MEMMGR_EXTR_INFO_NO_DATA*/
  DCM_E_REQUESTOUTOFRANGE,                     /*DCM_MEMMGR_EXTR_INFO_WRONG_FID*/
  DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT  /*DCM_MEMMGR_EXTR_INFO_TOO_SHORT*/
};
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#define DCM_STOP_SEC_CONST_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ ROM 32Bit definitions
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#ifndef V_SUPPRESS_EXTENDED_VERSION_CHECK
/* The name of this const variable is defined via v_ver.h and depends on the version of the C file. The value of the const variable is also defined externally and is used for consistency checks, too. */
CONST(uint32, DCM_CONST) DIAG_ASRDCM_LIB_SYMBOL = DIAG_ASRDCM_LIB_VERSION; /* PRQA S 3408 */ /* QAC 7.0: '%s' has external linkage but is being defined without any previous declaration.*/ /* Extern declaration in sip_check.c */
#endif

#define DCM_STOP_SEC_CONST_32BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ ROM unspecified definitions
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Context management */
#if (DCM_NUM_CONTEXTS > 1)
STATIC CONST(Dcm_TaskIdType, DCM_CONST) dcmEvMgrContextStateTaskId[DCM_NUM_CONTEXTS] =
{
  DCM_TASK_ID_STATE /* UDS StateTask */
 ,DCM_TASK_ID_OBD   /* OBD StateTask */
};
#endif

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
STATIC CONST(Dcm_PbUpdateFuncType, DCM_CONST) dcmPagedBufferClients[DCM_NUM_PB_CLIENTS] = /* PRQA S 3218*/ /* File scope static, 'xxx', only accessed in one function. */
{
   Dcm_DcmUpdatePage_19
# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
  ,Dcm_DcmUpdatePage_22
# endif
# if(DCM_OBD_READ_DTC_ENABLED == STD_ON)
  ,Dcm_DcmUpdatePage_Obd
# endif
};
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ Macro definitions
 ----------------------------------------------------------------------------- */

/*-----------------------------------------------*/
/*                 GlobalUtils                   */
/*-----------------------------------------------*/
#define Dcm_GetStateMaskOfIdx(stateIter)                             ((Dcm_StateMaskType)(((Dcm_StateMaskType)0x01u)<<(stateIter)))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */

# define Dcm_EnterCritical()                                         SchM_Enter_Dcm(DCM_EXCLUSIVE_AREA_0)
# define Dcm_LeaveCritical()                                         SchM_Exit_Dcm(DCM_EXCLUSIVE_AREA_0)

#define _Dcm_Time2Ticks(msec)                                        ((uint16_least)((msec) / DCM_TASK_TIME))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
/* Operations */
#define _Dcm_OpValue(tgt, tgtType, value, op)                        ((tgt) = (tgtType)((tgt) op (value)))  /* PRQA S 3410 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */ /* PRQA S 3453 */ /* "op" can not be enclosed, otherwise compile error! */
#define Dcm_AddValue(tgt, tgtType, value)                            (_Dcm_OpValue(tgt, tgtType, value, +)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#define Dcm_SubValue(tgt, tgtType, value)                            (_Dcm_OpValue(tgt, tgtType, value, -)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#define Dcm_MulValue(tgt, tgtType, value)                            (_Dcm_OpValue(tgt, tgtType, value, *)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#define Dcm_DivValue(tgt, tgtType, value)                            (_Dcm_OpValue(tgt, tgtType, value, /)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
# define Dcm_FindValueUint8(variantTbl,lookUpTbl,value)              (Dcm_Uint8LookUp((variantTbl), (lookUpTbl), (value))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#else
# define Dcm_FindValueUint8(variantTbl,lookUpTbl,value)              (Dcm_Uint8LookUp((lookUpTbl), (value)))               /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif
#if(DCM_NUM_CONTEXTS > 1)
# define Dcm_CtxtMgrSetActiveContext(ctxtId)                         (dcmCtxtMgrCurContextId = (ctxtId)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_CtxtMgrGetCurContextId()                                dcmCtxtMgrCurContextId
#else
# define Dcm_CtxtMgrSetActiveContext(ctxtId)                         /* Not used */
# define Dcm_CtxtMgrGetCurContextId()                                DCM_CONTEXT_ID_UDS
#endif

#if (DCM_NUM_UDS_CONTEXTS > 1)
# define Dcm_CtxtMgrGetCurUdsContextId()                             (Dcm_CtxtMgrGetCurContextId())
#else
# define Dcm_CtxtMgrGetCurUdsContextId()                             DCM_CONTEXT_ID_UDS
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
# define Dcm_DetRegisterError(ApiId, ErrorId)                        (Det_ReportError((uint16)(DCM_MODULE_ID), (uint8)0, (uint8)(ApiId), (uint8)(ErrorId)))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_CheckValueRangeFailed(ApiId)                            (Dcm_DetRegisterError((ApiId),DCM_E_INTERFACE_VALUE_OUT_OF_RANGE))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_CheckApiValueRangeFailed(Cond, ApiId)                   if(!(Cond)){Dcm_CheckValueRangeFailed(ApiId); }/* PRQA S 3412 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */ /* PRQA S 3453 */
# define Dcm_BoolCheckValueRangeFailed(Cond, ApiId)                  if(!(Cond)){Dcm_CheckValueRangeFailed(ApiId); }/* PRQA S 3412 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */ /* PRQA S 3453 */
# define Dcm_StateCheckValueRangeFailed(Cond, ApiId)                 if(!(Cond)){Dcm_DetRegisterError((ApiId),DCM_E_ILLEGAL_STATE_REACHED); }/* PRQA S 3412 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */ /* PRQA S 3453 */
# define Dcm_CheckAlwaysFailed(ApiId)                                (Dcm_DetRegisterError((ApiId),DCM_E_ILLEGAL_STATE_REACHED)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_CheckApiUsageFailed(ApiId)                              (Dcm_DetRegisterError((ApiId),DCM_E_INTERFACE_ILLEGALLY_USED)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_CheckDcmInit(ApiId)                                     if(!(DCM_DEBUG_INIT_PATTERN == dcmDebugInitPattern)){Dcm_DetRegisterError((ApiId),DCM_E_UNINIT);}/* PRQA S 3412 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */ /* PRQA S 3453 */
# define Dcm_CheckConfigTypeFailed(Cond, ApiId)                      if(!(Cond)){Dcm_DetRegisterError((ApiId),DCM_E_LIB_CONFIG_MISMATCH); }/* PRQA S 3412 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */ /* PRQA S 3453 */
#else
# define Dcm_DetRegisterError(ApiId, ErrorId)                        /* Not active */
# define Dcm_CheckValueRangeFailed(ApiId)                            /* Not active */
# define Dcm_CheckApiValueRangeFailed(cond, ApiId)                   /* Not active */
# define Dcm_BoolCheckValueRangeFailed(cond, ApiId)                  /* Not active */
# define Dcm_StateCheckValueRangeFailed(cond, ApiId)                 /* Not active */
# define Dcm_CheckAlwaysFailed(ApiId)                                /* Not active */
# define Dcm_CheckApiUsageFailed(ApiId)                              /* Not active */
# define Dcm_CheckDcmInit(ApiId)                                     /* Not active */
# define Dcm_CheckConfigTypeFailed(cond, ApiId)                      /* Not active */
#endif

#if (DCM_PDUROUTER_ENABLED == STD_ON)
/* backward compatibility to older interfaces not supporting E_PENDING */
# if defined(E_PENDING)
#  define Dcm_DslLL_IsPduRTxAccepted(result)                         ((E_OK == (result))||(E_PENDING == (result))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# else
#  define Dcm_DslLL_IsPduRTxAccepted(result)                         (E_OK == (result)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# endif
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if(DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
# define Dcm_DemMgrConvUdsContextId2Clientid(lContext)               (Dcm_DemMgrDemClientType)(((lContext)==DCM_CONTEXT_ID_UDS)?DCM_DEMMGR_CLIENT_ID_UDS:DCM_DEMMGR_CLIENT_ID_OBD) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#else
# define Dcm_DemMgrConvUdsContextId2Clientid(lContext)               DCM_DEMMGR_CLIENT_ID_UDS /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
#  define Dcm_DidMgrFindDid(value, lookUpTbl, variantTbl)            (Dcm_DidMgrGetDidHandle((value), (lookUpTbl), (variantTbl))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# else
#  define Dcm_DidMgrFindDid(value, lookUpTbl, variantTbl)            (Dcm_DidMgrGetDidHandle((value),(lookUpTbl)))                /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# endif
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_ON)
#  if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
#   define Dcm_MemAccFindMemBlock(lookUpTbl, variantTbl, stateInfoTable, value) (Dcm_MemAccMemBlockLookUp((lookUpTbl), (variantTbl), (stateInfoTable), (value))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#   define Dcm_MemAccAnalyseMemBlock(value, lookUpTbl, variantTbl, stateInfoTbl) (Dcm_MemAccCheckMemoryBlock((value),(lookUpTbl), (variantTbl), (stateInfoTbl))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#  else
#   define Dcm_MemAccFindMemBlock(lookUpTbl, variantTbl, stateInfoTable, value) (Dcm_MemAccMemBlockLookUp((lookUpTbl), (stateInfoTable), (value))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#   define Dcm_MemAccAnalyseMemBlock(value, lookUpTbl, variantTbl, stateInfoTbl) (Dcm_MemAccCheckMemoryBlock((value),(lookUpTbl), (stateInfoTbl))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#  endif
# else
#  define Dcm_MemAccFindMemBlock(lookUpTbl, variantTbl, stateInfoTable, value) /* Not used */
#  define Dcm_MemAccAnalyseMemBlock(value, lookUpTbl, variantTbl, stateInfoTbl) (Dcm_MemAccCheckMemoryBlock(value)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# endif
# define Dcm_MemByAddrGetMemBlockLenSize(formatByte)                 (uint8)(((formatByte) >> 4) & 0x0Fu)/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_MemByAddrGetMemBlockAddrSize(formatByte)                (uint8)((formatByte) & 0x0Fu)/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
    (DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON))
/* Check if it is an available ID at all: (id MOD 0x20) == 0 */
# define Dcm_ObdMgrIsAvailabilityId(obdId)                           ((boolean)(((obdId) & 0x1Fu) == 0)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_ObdMgrAvailabilityIdIdx(obdId)                          ((uint8)((obdId) >>5)) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif /* ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
(DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON) || \
    (DCM_SERVICE_04_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON))
# define Dcm_ObdDemWrapGetDtcOfFFRecord(dtcFF, dtcOrigin, dtcKind, dtc) (DemObd_GetDTCOfFreezeFrameRecord((dtcFF), (dtcOrigin), (dtcKind), (dtc))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_ObdDemWrapSetDtcFilter(dtcSM, dtcKind, dtcOrigin, useSev, dtcSev, useFdc) (DemObd_SetDTCFilter((dtcSM), (dtcKind), (dtcOrigin), (useSev), (dtcSev), (useFdc))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_ObdDemWrapGetNumFilteredDtc(pNumDtc)                    (DemObd_GetNumberOfFilteredDTC((pNumDtc))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_ObdDemWrapGetNextFilteredDtc(pDtc, pDtcSM)              (DemObd_GetNextFilteredDTC((pDtc), (pDtcSM))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_ObdDemWrapClearDtc(dtc, dtcOrigin, dtcKind)             (DemObd_ClearDTC((dtc), (dtcOrigin), (dtcKind))) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif /* ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON) || \
(DCM_SERVICE_04_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON)) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
# if(DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
#  define Dcm_22_UdsContextId2Clientid(lContext)                     (Dcm_DidMgrDidClientType)(((lContext)==DCM_CONTEXT_ID_UDS)?DCM_DIDMGR_CLIENT_ID_22:DCM_DIDMGR_CLIENT_ID_22_WWHOBD) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# else
#  define Dcm_22_UdsContextId2Clientid(lContext)                     DCM_DIDMGR_CLIENT_ID_22 /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# endif
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
# define Dcm_2A_MakeEventOfTimerIdx(timerId)                         ((Dcm_EventType)(0x01 << (timerId)))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
# define Dcm_2C_GetMemBlockFmtItemSize(formatByte)                   (uint8)(Dcm_MemByAddrGetMemBlockLenSize(formatByte) + Dcm_MemByAddrGetMemBlockAddrSize(formatByte))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */

# define Dcm_2C_SequencedDefMod8(value)                              ((uint8_least)((value) & (8-1)))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_2C_SequencedDefDiv8(value)                              ((uint8_least)((value) >> 3))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */

/* Queue the current reference of PID */
# define Dcm_2C_AddPidDefToSequencerAt(dynDidHndl, pos)              (dcm2C_DynDidInfoRefTable[dynDidHndl].pItemTypes[Dcm_2C_SequencedDefDiv8(pos)] &= (Dcm_2C_SequencerType)(~(Dcm_2C_SequencerType)(DCM_2C_MEMBER_MASK << Dcm_2C_SequencedDefMod8(pos))))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_2C_AddMemDefToSequencerAt(dynDidHndl, pos)              (dcm2C_DynDidInfoRefTable[dynDidHndl].pItemTypes[Dcm_2C_SequencedDefDiv8(pos)] |=                        (Dcm_2C_SequencerType)(DCM_2C_MEMBER_MASK << Dcm_2C_SequencedDefMod8(pos)))/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_2C_IsDidRefDefinitionAt(dynDidHndl, pos)                ((dcm2C_DynDidInfoRefTable[dynDidHndl].pItemTypes[Dcm_2C_SequencedDefDiv8(pos)] & (Dcm_2C_SequencerType)(DCM_2C_MEMBER_MASK << Dcm_2C_SequencedDefMod8(pos))) == 0)/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# define Dcm_2C_GetDefinitionAt(dynDidHndl, pos)                     (Dcm_2C_SequencerType)((Dcm_2C_SequencerType)(dcm2C_DynDidInfoRefTable[dynDidHndl].pItemTypes[Dcm_2C_SequencedDefDiv8(pos)] >> Dcm_2C_SequencedDefMod8(pos)) & DCM_2C_MEMBER_MASK)/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
# if(DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
#  define Dcm_31_UdsContextId2Clientid(lContext)                     (Dcm_RidMgrRidClientType)(((lContext)==DCM_CONTEXT_ID_UDS)?DCM_RIDMGR_CLIENT_ID_31:DCM_RIDMGR_CLIENT_ID_31_WWHOBD) /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# else
#  define Dcm_31_UdsContextId2Clientid(lContext)                     DCM_RIDMGR_CLIENT_ID_31 /* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
# endif
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_HARD_RESET_ENABLED == STD_ON)
# define Dcm_DspPerformReset(resetType)                              (Mcu_PerformReset())/* PRQA S 3453 */ /* QAC 7.0:  A function could probably be used instead of this function-like macro. */ /* Macro is more efficient! */
#endif /* (DCM_HARD_RESET_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Inlined code implementation
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  Dcm_DebugInit
 **********************************************************************************************************************/
/*! \brief      Initializes the debug sub-component of DCM.
 *  \pre        All interrupts (global) must be disabled.
 *  \context    Called during the DCM initialization.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DebugInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
#if (DCM_DEV_ERROR_DETECT == STD_ON)
  dcmDebugInitPattern = DCM_DEBUG_INIT_PATTERN;
#endif

#if (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)
# if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
/* Check the LCfg Configuration. The detailed implementation may differ. The check tests that major and minor version in the library are valid. The patch version */
 if( (((uint16)(Dcm_GeneratorVersion >> 8)) != Dcm_Make16Bit(DIAG_ASRDCM_IMPLEMENTATION_MAJOR_VERSION,DIAG_ASRDCM_IMPLEMENTATION_MINOR_VERSION)) /* PRQA S 3356 */ /* QAC 7.0:  The result of this logical operation is always 'false'. */ /* Link time check */
#  if (DIAG_ASRDCM_IMPLEMENTATION_PATCH_VERSION != 0)
   ||((uint8)(Dcm_GeneratorVersion) < DIAG_ASRDCM_IMPLEMENTATION_PATCH_VERSION) /* PRQA S 3356 */ /* QAC 7.0:  The result of this logical operation is always 'false'. */ /* Link time check */
#  endif
   )
  {
    /* Call the Vector specific EcuM Error callback and do NOT Call Det_ReportError. */
    EcuM_GeneratorCompatibilityError((uint16) DCM_MODULE_ID, (uint8) 0);
  }
# endif
  Dcm_CheckConfigTypeFailed((DCM_IMPL_OEM_ID == dcm_DebugLCfgOemId), DcmServiceId_Init); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
#endif
}

/***********************************************************************************************************************
 *  Dcm_EvMgrInit
 **********************************************************************************************************************/
/*! \brief      Init all event registers.
 *  \context    Function must be called within disabled all interrupts.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_EvMgrInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_TaskIdType iter = DCM_NUM_TASKS;
  while(iter != 0)
  {
    iter--;
    dcmEvMgrEventRegisters[iter] = 0;
  }
  dcmEvMgrNumActiveTasks = 0;
}

/***********************************************************************************************************************
 *  Dcm_EvMgrGetEvent
 **********************************************************************************************************************/
/*! \brief      Get a task event register.
 *  \param[in]  taskId                        Task Id
 *  \return     The current event register content
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_EventType, DCM_CODE) Dcm_EvMgrGetEvent(Dcm_TaskIdType taskId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return dcmEvMgrEventRegisters[taskId];
}

/***********************************************************************************************************************
 *  Dcm_TmrMgrInit
 **********************************************************************************************************************/
/*! \brief      Init all timers.
 *  \context    Function must be called within disabled all interrupts.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_TmrMgrInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_TimerIdType iter = DCM_NUM_TIMERS;
  while(iter != 0)
  {
    iter--;
    dcmTimerEngine[iter] = 0;
  }
  dcmActiveTimerCounter = 0;
}

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DcmUpdatePage
 **********************************************************************************************************************/
/*! \brief      Dispatches the UpdatePage call
 *  \context    Function must be call on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DcmUpdatePage(DCM_CONTEXT_PARAM_DEF_ONLY)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* delegate */
  dcmPagedBufferClients[dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].clientId](&dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr[dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].pageSize],
                                                                             (Dcm_MsgLenType)(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].maxBufferLength - dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].pageSize));
}

/***********************************************************************************************************************
 *  Dsd_PagedBufferDataRequest
 **********************************************************************************************************************/
/*! \brief      Requests new data chunk.
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dsd_PagedBufferDataRequest(DCM_CONTEXT_PARAM_DEF_ONLY)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].isDataRequested = 1;
  Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_PARAM_VALUE), DCM_EVENT_PB_UPDATE_PAGE);
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
/***********************************************************************************************************************
 *  Dcm_DslHL_StartReception
 **********************************************************************************************************************/
/*! \brief      HighLevel reception start notification.
 *  \return     Acceptance of the new request
 *  \retval     DSL_COMM_E_OK - accepted
 *  \retval     DSL_COMM_E_NOT_OK - rejected
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_DslCommStatusType, DCM_CODE) Dcm_DslHL_StartReception(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(connId);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */ /* for the non-PPRH case */

  if(dcmStateMachine.CommState == DCM_COMM_STATE_NONE)
  {
    return DSL_COMM_E_NO_COMM;
  }

  if(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState == DCM_CONTEXT_STATE_FREE)
  {
#if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
    if((FALSE  == dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].isConnectionLocked)||
       (connId == dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dslHandle))
#endif
    {
      dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState = DCM_CONTEXT_STATE_RX_STARTED;
      Dcm_TmrMgrStopTimer(DCM_TIMER_ID_S3);
      return DSL_COMM_E_OK;
    }
  }
  return DSL_COMM_E_NOT_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

#if (DCM_PDUROUTER_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslLL_Init
 **********************************************************************************************************************/
/*! \brief      LowLevel initialization.
 *  \context    Function must be called withing disabled all interrupts context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_Init(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL

  DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT;

  DCM_TRANSP_OBJ_HNDL_ITER_LOOP
  {
    DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC;
    dcmPduRxTransportInfo[DCM_TRANSP_OBJ_HNDL_ITER_VALUE].base.state = DCM_PDU_TX_STATE_FREE;
# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
    dcmPduRxTransportInfo[DCM_TRANSP_OBJ_HNDL_ITER_VALUE].base.isReserved = FALSE;
# endif
# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
    dcmPduTxTransportInfo[DCM_TRANSP_OBJ_HNDL_ITER_VALUE].base.state = DCM_PDU_TX_STATE_FREE;
#  if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
    dcmPduTxTransportInfo[DCM_TRANSP_OBJ_HNDL_ITER_VALUE].base.isReserved = FALSE;
#  endif
# endif
  }

# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON) && \
     (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  dcmSemaphoreAllocateTx = DCM_SEMAPHORE_ALLOCATE_TX_FREE;
# endif
}

/***********************************************************************************************************************
 *  Dcm_DslLL_StateTask
 **********************************************************************************************************************/
/*! \brief      LowLevel job processing task.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_StateTask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EventType ev;

  ev = Dcm_EvMgrGetEvent(DCM_TASK_ID_DSL_LL_STATE);

  if(ev != 0)
  {
    Dcm_EvMgrClearEvent(DCM_TASK_ID_DSL_LL_STATE, ev);

# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
#  if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
      (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
    if((ev & DCM_EVENT_DO_RETRY_TX_ALLOC_OBD) != 0)
    {
      Dcm_DslLL_StartTransmission(DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(DCM_CONTEXT_ID_OBD));
    }
#  endif

    if((ev & DCM_EVENT_DO_RETRY_TX_ALLOC_UDS) != 0)
    {
      Dcm_DslLL_StartTransmission(DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(DCM_CONTEXT_ID_UDS));
    }
# endif

# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
    if((ev & DCM_EVENT_PPRH_DO_SEND) != 0)
    {
      Dcm_PduRxTransportInfoPtrType pRxTranspObj;
      Dcm_PduTxTransportInfoPtrType pTxTranspObj;

      /* Find transport object(s) to send */
      DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL

      DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT;

      DCM_TRANSP_OBJ_HNDL_ITER_LOOP
      {
        DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC;
        pRxTranspObj = &dcmPduRxTransportInfo[DCM_TRANSP_OBJ_HNDL_ITER_VALUE];

        if(DCM_PDU_TX_STATE_DO_SEND == pRxTranspObj->base.state)
        {
#  if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_OFF)
          pTxTranspObj = pRxTranspObj;
#  else
          pTxTranspObj = Dcm_DslLL_TObjAllocTxByConnId(pRxTranspObj->base.connId);

          if(pTxTranspObj != NULL_PTR)
#  endif
          {
#  if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
            /* Transfer base part */
            pTxTranspObj->base = pRxTranspObj->base;
            pRxTranspObj->base.state = DCM_PDU_TX_STATE_PROCESSING; /* do not retry sending on this connection */
#  endif
            /* Compose the NR 0x7F 0xSID 0x21 */
            pTxTranspObj->base.pduInfo.SduLength = 3;
            pTxTranspObj->base.pduInfo.SduDataPtr[0] = 0x7F;
            pTxTranspObj->base.pduInfo.SduDataPtr[1] = pRxTranspObj->sid;
            pTxTranspObj->base.pduInfo.SduDataPtr[2] = DCM_E_BUSYREPEATREQUEST;
            pTxTranspObj->base.state = DCM_PDU_TX_STATE_DO_SEND;

            ev |= DCM_EVENT_DO_SEND;/* Enforce immediate transmission! */
          }
        }
      }
    }
# endif
    if((ev & DCM_EVENT_DO_SEND) != 0)
    {
      Dcm_PduTxTransportInfoPtrType pTxTranspObj;

      /* Find transport object(s) to send */
      DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL

      DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT;

      DCM_TRANSP_OBJ_HNDL_ITER_LOOP
      {
        DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC;
        pTxTranspObj = &dcmPduTxTransportInfo[DCM_TRANSP_OBJ_HNDL_ITER_VALUE];

        if(DCM_PDU_TX_STATE_DO_SEND == pTxTranspObj->base.state)
        {
          Std_ReturnType stdReturn;

          pTxTranspObj->base.state = DCM_PDU_TX_STATE_ON_TX;
          stdReturn= PduR_DcmTransmit(dcmDslPduConnectionInfoTable[pTxTranspObj->base.connId].mainTxPduId, &pTxTranspObj->base.pduInfo);

          if(!Dcm_DslLL_IsPduRTxAccepted(stdReturn))
          {
            pTxTranspObj->base.state = DCM_PDU_TX_STATE_DO_SEND;
            Dcm_EvMgrSetEvent(DCM_TASK_ID_DSL_LL_STATE, DCM_EVENT_DO_SEND);
          }
        }
      }
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_DslLL_TimerTask
 **********************************************************************************************************************/
/*! \brief      LowLevel timer processing task.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_TimerTask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Not used */
}

/***********************************************************************************************************************
 *  Dcm_DslLL_TObjFree
 **********************************************************************************************************************/
/*! \brief      Releases a transport object.
 *  \param[in]  pTranspObj   The transport object to be released
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_TObjFree(Dcm_PduTransportInfoPtrType pTranspObj)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
  if(FALSE != pTranspObj->isReserved)
  {
    pTranspObj->state = DCM_PDU_TX_STATE_RESERVED;
  }
  else
# endif
  {
    pTranspObj->state = DCM_PDU_TX_STATE_FREE;
  }
}

# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_ConcurProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief      Provides response data copy processing on the concurent service response.
 *  \param[in]  pTxTranspObj              The Tx transport object handle on the current response transmission
 *  \param[in]  Length                    The required data length from the lower layer (shall be 0)
 *  \param[out] PduInfoPtr                Pointer to the chunk data pointer and current chunk length
 *  \return     Operation result
 *  \retval     0 - BUFREQ_OK
 *  \retval     >0 - failed for some reason
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ConcurProvideTxBuffer(Dcm_PduTxTransportInfoPtrType pTxTranspObj, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(Length);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */ /* for the non-debug case */

  Dcm_CheckApiValueRangeFailed((Length == 0)||(Length >= 3), DcmServiceId_ProvideTxBuffer); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  *PduInfoPtr = &pTxTranspObj->base.pduInfo;
  return BUFREQ_OK;
}
# endif

/***********************************************************************************************************************
 *  Dcm_MainProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief      Provides response data copy processing on the main service response.
 *  \param[in]  pTxTranspObj              The transport object handle on the current response transmission
 *  \param[in]  Length                    The required data length from the lower layer (shall be 0)
 *  \param[out] PduInfoPtr                Pointer to the chunk data pointer and current chunk length
 *  \return     Operation result
 *  \retval     0 - BUFREQ_OK
 *  \retval     >0 - failed for some reason
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_MainProvideTxBuffer(Dcm_PduTxTransportInfoPtrType pTxTranspObj, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  BufReq_ReturnType result = BUFREQ_OK;
# if(DCM_NUM_CONTEXTS > 1)
  DCM_CONTEXT_PARAM_DEF_ONLY = pTxTranspObj->base.iContext;
# endif

  Dcm_CheckDcmInit(DcmServiceId_ProvideTxBuffer);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  DCM_IGNORE_UNREF_PARAM(Length); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType == DSL_RES_TYPE_FINAL_PAGED)
  {
    if(Length == 0)
    {
      Length = (PduLengthType)(dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].pageSize - dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].readIdx);
    }

    /* Check for minimum length available and not empty page buffer */
    if((Length <= (dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].pageSize - dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].readIdx)) &&
       (Length != 0))
    {
      /* Just update the size and the data pointer */
      pTxTranspObj->base.pduInfo.SduLength = Length;
      pTxTranspObj->base.pduInfo.SduDataPtr = &dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr[dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].readIdx];
      Dcm_AddValue(dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].readIdx , Dcm_MsgLenType, Length);
    }
    else
    {
      result = BUFREQ_E_BUSY;
      /* Request new data */
      if(dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].isDataRequested == 0)
      {
        /* Defragment data page */
        Dcm_SubValue(dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].pageSize , Dcm_MsgLenType, dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].readIdx);
        Dcm_CopyRam2Ram(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr, &dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr[dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].readIdx], dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].pageSize);
        /* Start reading from the beginning */
        dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].readIdx = 0;

        Dsd_PagedBufferDataRequest(DCM_CONTEXT_PARAM_VALUE_ONLY);
      }
    }
  }
# endif
  *PduInfoPtr = &pTxTranspObj->base.pduInfo;
  return result;
}

# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslLL_AllocateRxResource
 **********************************************************************************************************************/
/*! \brief      Reserves a resource
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_AllocateRxResource(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduRxTransportInfoPtrType pRxTranspObj = Dcm_DslLL_TObjAllocRxByConnId(connId);
  /* A transport object must exist */
  Dcm_StateCheckValueRangeFailed((pRxTranspObj != NULL_PTR), DcmServiceId_AllocateResource); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  pRxTranspObj->base.kind  = DCM_DSL_TOBJ_KIND_MAIN; /* PRQA S 0505 */ /* QAC 7.0:  [U] Dereferencing pointer value that is apparently NULL. */ /* If NULL, DCM reaches point of no return! */
  pRxTranspObj->base.state = DCM_PDU_TX_STATE_PROCESSING; /* PRQA S 0505 */ /* QAC 7.0:  [U] Dereferencing pointer value that is apparently NULL. */ /* If NULL, DCM reaches point of no return! */
}
# endif

# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslLL_IsRxResourceLocked
 **********************************************************************************************************************/
/*! \brief      Checks if the resource is locked for this rxId
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DslLL_IsRxResourceLocked(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduRxTransportInfoPtrType pRxTranspObj = Dcm_DslLL_TObjGetRxByConnId(connId);
  return (boolean)(pRxTranspObj != NULL_PTR);
}
# endif

/***********************************************************************************************************************
 *  Dcm_DslLL_TObjGetRxByRxPduId
 **********************************************************************************************************************/
/*! \brief      Returns a transport object handle if the RxPduId is already in use.
 *  \param[in]  DcmRxPduId     RxPduId
 *  \return     Operation result
 *  \retval     >0       - valid object
 *  \retval     NULL_PTR - failed to find any object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_PduRxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetRxByRxPduId(PduIdType DcmRxPduId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return Dcm_DslLL_TObjGetRxByConnId(DcmDslRxPdu2ConnMap(DcmRxPduId,DCM_COMVARIANT_ID_VALUE));
}

/***********************************************************************************************************************
 *  Dcm_CheckAvailableContext
 **********************************************************************************************************************/
/*! \brief      Request reception data manager
 *  \param[inout] pTranspObj              Current transportObject
 *  \return     Operation result
 *  \retval     0 - BUFREQ_OK
 *  \retval     >0 - failed for some reason
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CheckAvailableContext(Dcm_PduRxTransportInfoPtrType pRxTranspObj)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  BufReq_ReturnType result = BUFREQ_OK;
  Dcm_DslCommStatusType dslHLResult;

# if(DCM_NUM_CONTEXTS > 1)
  DCM_CONTEXT_PARAM_DEF_ONLY = pRxTranspObj->base.iContext;
# endif

  dslHLResult = Dcm_DslHL_StartReception(DCM_CONTEXT_PARAM_VALUE_FIRST pRxTranspObj->base.connId);
  if(dslHLResult == DSL_COMM_E_OK)
  {
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataLength = pRxTranspObj->totalRequestLength;
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dslHandle  = pRxTranspObj->base.connId;
# if (DCM_DSL_STORE_RXPDUID_ENABLED == STD_ON)
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].rxPduId    = pRxTranspObj->rxPduId;
# endif
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].addrType   = dcmDslRxPduInfoTable[pRxTranspObj->rxPduId].addrType;
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].maxBufferLength = dcmDslPduProtocolInfoTable[0].mainBufferSize;
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].maxBusPayloadLength = dcmDslPduConnectionInfoTable[pRxTranspObj->base.connId].maxBusPayloadLength;

# if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
     (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].protocolType = dcmDslLLClientSvc2Protocol[pRxTranspObj->svcIdGroup][dcmDslPduConnectionInfoTable[pRxTranspObj->base.connId].diagType];
# endif

    pRxTranspObj->base.state = DCM_PDU_TX_STATE_PROCESSING;
# if (DCM_NUM_CONTEXTS > 1)
    if(DCM_CONTEXT_ID_UDS != DCM_CONTEXT_PARAM_VALUE)
    {
      pRxTranspObj->base.pduInfo.SduDataPtr = dcmDslPduProtocolInfoTable[0].pObdBuffer;
    }
    else
# endif
    {
      pRxTranspObj->base.pduInfo.SduDataPtr = dcmDslPduProtocolInfoTable[0].pMainBuffer;
    }
    /* Set the working buffer pointer */
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr = pRxTranspObj->base.pduInfo.SduDataPtr;

# if (DCM_NUM_CONTEXTS > 1)
    /* Move the content to the corresponding buffer*/
    Dcm_CopyRam2Ram(pRxTranspObj->base.pduInfo.SduDataPtr, pRxTranspObj->tempBuffer, pRxTranspObj->base.pduInfo.SduLength);
    pRxTranspObj->base.pduInfo.SduDataPtr = &pRxTranspObj->base.pduInfo.SduDataPtr[pRxTranspObj->base.pduInfo.SduLength];
    /* Override default buffer and size */
    pRxTranspObj->base.pduInfo.SduLength  = (uint16)(dcmDslPduProtocolInfoTable[0].mainBufferSize - pRxTranspObj->base.pduInfo.SduLength);
# else
    /* Override default buffer and size */
    pRxTranspObj->base.pduInfo.SduLength  = dcmDslPduProtocolInfoTable[0].mainBufferSize;
# endif
    pRxTranspObj->base.kind = DCM_DSL_TOBJ_KIND_MAIN;
  }
  else
  {
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
    if(dslHLResult != DSL_COMM_E_NO_COMM)
    {
      /* The addressed DCM context is busy - reply with NRC 0x21 */
#  if (DCM_DSL_REQUEST_PREFETCH_ENABLED == STD_ON)
      pRxTranspObj->base.pduInfo.SduLength = DCM_DSL_CONCUR_BUFF_SIZE_CONST;
      pRxTranspObj->base.state = DCM_PDU_TX_STATE_ON_RX; /* skip the on RX start since SID already copied */
#  else
      pRxTranspObj->base.state = DCM_PDU_TX_STATE_ON_RX_START;
#  endif
      pRxTranspObj->base.kind = DCM_DSL_TOBJ_KIND_CONCUR;
    }
    else
# endif
    {
      result = BUFREQ_E_NOT_OK;
    }
  }
  return result;
}

# if(DCM_NUM_CONTEXTS > 1)
/***********************************************************************************************************************
 *  Dcm_DoDispatchContext
 **********************************************************************************************************************/
/*! \brief      Request reception data manager
  * \param[inout] pRxTranspObj              Current transportObject
  * \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE  FUNC(void, DCM_CODE) Dcm_DoDispatchContext(Dcm_PduRxTransportInfoPtrType pRxTranspObj)
/*--------------------------------------------------------------------------------------------------------------------*/
{
#  if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
  /* "(pRxTranspObj->sid >= 0x00)&&" always true since unsigned value */
  if(pRxTranspObj->sid <= 0x0F)
  {
    pRxTranspObj->svcIdGroup = DCM_DIAG_SERVICE_GRP_OBD;
  }
  else
#  endif
  {
#  if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
    /* allow only WWHOBD services in parallel execution */
    switch(pRxTranspObj->sid)
    {
    case 0x14:
    case 0x19: /* fall through */
    case 0x22: /* fall through */
    case 0x31: /* fall through */
      pRxTranspObj->svcIdGroup = DCM_DIAG_SERVICE_GRP_WWHOBD;
      break;
    default:
      /* any other UDS services - reroute to the UDS context */
      pRxTranspObj->svcIdGroup = DCM_DIAG_SERVICE_GRP_UDS;
      break;
    }
#  else
    {
      pRxTranspObj->svcIdGroup = DCM_DIAG_SERVICE_GRP_UDS;
    }
#  endif
  }

  pRxTranspObj->base.iContext = dcmDslLLClientSvc2ContextMap[pRxTranspObj->svcIdGroup][dcmDslPduConnectionInfoTable[pRxTranspObj->base.connId].diagType];
}
# endif

/***********************************************************************************************************************
 *  Dcm_ProvideContext
 **********************************************************************************************************************/
/*! \brief      Request reception data manager
 *  \param[in]  DcmRxPduId                The RxPduId on the current request transmission
 *  \param[inout] pRxTranspObj              Current transportObject
 *  \return     Operation result
 *  \retval     0 - BUFREQ_OK
 *  \retval     >0 - failed for some reason
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
CONTEXT_FUNC_LOC FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideContext(Dcm_PduRxTransportInfoPtrType pRxTranspObj)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  BufReq_ReturnType result;

# if(DCM_NUM_CONTEXTS > 1)
  Dcm_DoDispatchContext(pRxTranspObj);

  /* Check wether the client may access the requested services */
  if(pRxTranspObj->base.iContext == DCM_CONTEXT_ID_INVALID)
  {
    result = BUFREQ_E_NOT_OK;
  }
  else
# endif
  {
    /* try to get free context */
    result = Dcm_CheckAvailableContext(pRxTranspObj);
  }
  return result;
}

# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslLL_ReleaseReservedRxResource
 **********************************************************************************************************************/
/*! \brief      Request reception data manager
 *  \param[in]  connId                The connection id to be released
  *  \return     Operation result
 *  \retval     0 - BUFREQ_OK
 *  \retval     >0 - failed for some reason
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslLL_ReleaseReservedRxResource(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduRxTransportInfoPtrType pRxTranspObj = Dcm_DslLL_TObjGetRxByConnId(connId);

  if(NULL_PTR != pRxTranspObj) /* possible that already released! */
  {
    if(DCM_PDU_TX_STATE_RESERVED == pRxTranspObj->base.state) /* Do not cut through the branch you are sitting on :) */
    {
      pRxTranspObj->base.isReserved = FALSE;
      Dcm_DslLL_TObjFree(&(pRxTranspObj->base));
    }
  }
}
# endif
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  Dcm_PruOnInit
 **********************************************************************************************************************/
/*! \brief      Initilizes the PeriodicResponderUnit
 *  \context    Function must be called with disabled interrupt context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruOnInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmPruResource.isReserved = FALSE;
  dcmPruBuffer[0] = 0x6Au;
}

/***********************************************************************************************************************
 *  Dcm_PruAllocateResource
 **********************************************************************************************************************/
/*! \brief      Allocates a resource (data buffer) for periodic transmission
 *  \return     A transmit resource handle
 *  \retval     <DCM_PERIODIC_HANDLE_INVALID  - corresponding resource handle for later usage
 *  \retval     DCM_PERIODIC_HANDLE_INVALID - failed no free resource found
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_PeriodicHandleType, DCM_CODE) Dcm_PruAllocateResource(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PeriodicHandleType handle = DCM_PERIODIC_HANDLE_INVALID;
  Dcm_CheckApiValueRangeFailed(dcmPruCurrentConnection != DCM_CONNECTION_ID_INVALID, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  if(FALSE == dcmPruResource.isReserved)
  {
    boolean mayProceed = Dcm_PruMayProcessRequest();
    if(FALSE != mayProceed)
    {
      dcmPruResource.isReserved = TRUE;
      handle = 0;
    }
  }
  return handle;
}

/***********************************************************************************************************************
 *  Dcm_PruGetDataPtr
 **********************************************************************************************************************/
/*! \brief      Gets the data pointer associated with the resource handle
 *  \param[in]  handle                      The resource handle got at "allocate" time.
 *  \return     Pointer to the response data buffer
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_PruGetDataPtr(Dcm_PeriodicHandleType handle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(handle);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  return &(dcmPruBuffer[1]);/* leave place for the ResSID (0x6A)*/
}

/***********************************************************************************************************************
 *  Dcm_PruDoTransmit
 **********************************************************************************************************************/
/*! \brief      Allocates a resource (data buffer) for periodic transmission
 *  \param[in]  handle                     The resource handle got at "allocate" time.
 *  \param[in]  length                     The length of the response data.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_PruDoTransmit(Dcm_PeriodicHandleType handle, uint8 length)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn = E_NOT_OK;
  boolean mayProceed = Dcm_PruMayProcessRequest();

  DCM_IGNORE_UNREF_PARAM(handle);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  if(FALSE != mayProceed) /* if already RxInd called, no periodic transmission shall be initiated */
  {
    Dcm_PduTxTransportInfoPtrType pTxTranspObj = Dcm_DslLL_TObjAllocTxByConnId(dcmPruCurrentConnection);
    if(pTxTranspObj != NULL_PTR)
    {
      ++length; /*Don't forget the SID byte in the response! */

      pTxTranspObj->base.pduInfo.SduDataPtr = &(dcmPruBuffer[0]);
      pTxTranspObj->base.pduInfo.SduLength = length;
      pTxTranspObj->base.state = DCM_PDU_TX_STATE_ON_TX;
      pTxTranspObj->base.kind  = DCM_DSL_TOBJ_KIND_PERIODIC;
      stdReturn = PduR_DcmTransmit(dcmDslPduConnectionInfoTable[dcmPruCurrentConnection].mainTxPduId, &pTxTranspObj->base.pduInfo);

      if(!Dcm_DslLL_IsPduRTxAccepted(stdReturn))
      {
        /* release immediately */
        Dcm_DslLL_TObjFree(&(pTxTranspObj->base));
      }
    }
  }
  return stdReturn;
}

/***********************************************************************************************************************
 *  Dcm_PruReleaseResource
 **********************************************************************************************************************/
/*! \brief      Timeout of periodic transmission (no confirmation
 *  \param[in]  handle                     The resource handle got at "allocate" time.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruReleaseResource(Dcm_PeriodicHandleType handle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(handle);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  dcmPruResource.isReserved = FALSE;
}

/***********************************************************************************************************************
 *  Dcm_PruProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief      Data copy function.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(BufReq_ReturnType, DCM_CODE) Dcm_PruProvideTxBuffer(Dcm_PduTxTransportInfoPtrType pTxTranspObj, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(Length);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  Dcm_CheckApiValueRangeFailed( (dcmPruCurrentConnection == pTxTranspObj->base.connId), DcmServiceId_ProvideTxBuffer); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  Dcm_CheckApiValueRangeFailed( (Length == 0) || (Length <= 7), DcmServiceId_ProvideTxBuffer); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  Dcm_CheckApiValueRangeFailed( (Length == 0) || (Length == pTxTranspObj->base.pduInfo.SduLength), DcmServiceId_ProvideTxBuffer); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Assign the only data DCM has */
  *PduInfoPtr = &pTxTranspObj->base.pduInfo;
  return BUFREQ_OK;
}

/***********************************************************************************************************************
 *  Dcm_PruTxConfirmation
 **********************************************************************************************************************/
/*! \brief      End of UUDT transmission
 *  \param[in]  TxPduId    The connId of the currently sent message.
 *  \param[in]  Result     The transmission result.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruTxConfirmation(PduIdType DcmTxPduId, NotifResultType Result)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(DcmTxPduId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  DCM_IGNORE_UNREF_PARAM(Result); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  Dcm_PruReleaseResource(0);
}
#endif /* ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  Dcm_PruOnInit
 **********************************************************************************************************************/
/*! \brief      Initilizes the PeriodicResponderUnit
 *  \context    Function must be called with disabled interrupt context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruOnInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PeriodicHandleType iter = DCM_PRU_NUM_RESOURCES;
  while(iter != 0)
  {
    iter--;
    /* Currenlty only single protocol supported !!! */
    dcmPruResourceTable[iter].txPduInfo.SduDataPtr = &dcmDslPduProtocolInfoTable[0].pPeriodicBufferPool[iter << 3];
    dcmPruResourceTable[iter].isReserved = FALSE;
  }
}

/***********************************************************************************************************************
 *  Dcm_PruAllocateResource
 **********************************************************************************************************************/
/*! \brief      Allocates a resource (data buffer) for periodic transmission
 *  \return     A transmit resource handle
 *  \retval     <DCM_PERIODIC_HANDLE_INVALID  - corresponding resource handle for later usage
 *  \retval     DCM_PERIODIC_HANDLE_INVALID - failed no free resource found
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_PeriodicHandleType, DCM_CODE) Dcm_PruAllocateResource(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PeriodicHandleType iter;

  Dcm_CheckApiValueRangeFailed(dcmPruCurrentConnection != DCM_CONNECTION_ID_INVALID, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  iter = dcmDslPduConnectionInfoTable[dcmPruCurrentConnection].numPerPduIds;
  while(iter != 0)
  {
    iter--;
    if(dcmPruResourceTable[iter].isReserved == FALSE)
    {
      dcmPruResourceTable[iter].isReserved = TRUE;
      return iter;
    }
  }

  return DCM_PERIODIC_HANDLE_INVALID;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_PruGetDataPtr
 **********************************************************************************************************************/
/*! \brief      Gets the data pointer associated with the resource handle
 *  \param[in]  handle                      The resource handle got at "allocate" time.
 *  \return     Pointer to the response data buffer
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_PruGetDataPtr(Dcm_PeriodicHandleType handle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return dcmPruResourceTable[handle].txPduInfo.SduDataPtr;
}

/***********************************************************************************************************************
 *  Dcm_PruDoTransmit
 **********************************************************************************************************************/
/*! \brief      Allocates a resource (data buffer) for periodic transmission
 *  \param[in]  handle                     The resource handle got at "allocate" time.
 *  \param[in]  length                     The length of the response data.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_PruDoTransmit(Dcm_PeriodicHandleType handle, uint8 length)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_USE_STATIC_8BYTE_UUDT_ENABLED == STD_ON)
  while(length < 8)
  {
    dcmPruResourceTable[handle].txPduInfo.SduDataPtr[length] = 0xAA;
    length++;
  }
# endif
  dcmPruResourceTable[handle].txPduInfo.SduLength = length;

  Dcm_TmrMgrStartTimer((Dcm_TimerIdType)(DCM_TIMER_ID_PERIODICTX_0 + handle), _Dcm_Time2Ticks(DCM_PERIODIC_CONF_TIMEOUT));
  return PduR_DcmTransmit(dcmDslPduConnectionInfoTable[dcmPruCurrentConnection].pPeriodicTxPduIds[handle]
                         ,&dcmPruResourceTable[handle].txPduInfo);
}

/***********************************************************************************************************************
 *  Dcm_PruConvTxPduIdToHandle
 **********************************************************************************************************************/
/*! \brief      Timeout of periodic transmission (no confirmation
 *  \param[in]  DcmTxPduId                  The TxPduId of the currently sent message.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_PeriodicHandleType, DCM_CODE) Dcm_PruConvTxPduIdToHandle(PduIdType DcmTxPduId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  P2CONST(Dcm_PduConnectionType, AUTOMATIC, DCM_CONST) pConnection;
  Dcm_PeriodicHandleType iter;

  Dcm_CheckApiValueRangeFailed(dcmPruCurrentConnection == dcmTxPduToConnTable[DcmTxPduId], DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  pConnection = &dcmDslPduConnectionInfoTable[dcmPruCurrentConnection];
  iter = pConnection->numPerPduIds;
  while(iter != 0)
  {
    iter--;
    if(DcmTxPduId == pConnection->pPeriodicTxPduIds[iter])
    {
      return (Dcm_PeriodicHandleType)iter;
    }
  }
  /* assert*/
  return DCM_PERIODIC_HANDLE_INVALID;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_PruTxConfirmation
 **********************************************************************************************************************/
/*! \brief      End of UUDT transmission
 *  \param[in]  TxPduId    The connId of the currently sent message.
 *  \param[in]  Result     The transmission result.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruTxConfirmation(PduIdType DcmTxPduId, NotifResultType Result)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PeriodicHandleType lHandle;
  lHandle = Dcm_PruConvTxPduIdToHandle(DcmTxPduId);
  DCM_IGNORE_UNREF_PARAM(Result); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  if(lHandle != DCM_PERIODIC_HANDLE_INVALID)
  {
    Dcm_PruReleaseResource(lHandle);
  }
}
#endif /* ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_PruReserveConnection
 **********************************************************************************************************************/
/*! \brief      Registers a new woring conencetion id
 *  \param[in]  connId                    The ConnId of the current periodic request
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruReserveConnection(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmPruCurrentConnection = connId;
}

/***********************************************************************************************************************
 *  Dcm_PruReleaseConnection
 **********************************************************************************************************************/
/*! \brief      Registers a new woring conencetion id
 *  \param[in]  connId                    The ConnId of the current periodic request
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruReleaseConnection(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmPruCurrentConnection = DCM_CONNECTION_ID_INVALID;
}

# if (DCM_DSL_PRU_NEEDS_CONNECTION_LOCK == STD_ON)
/***********************************************************************************************************************
 *  Dcm_PruGetUsedConnection
 **********************************************************************************************************************/
/*! \brief      Returns the currently used connection id
 *  \return     Currently used connection handle
 *  \retval     <DCM_CONNECTION_ID_INVALID - corresponding connection id for later usage
 *  \retval     DCM_CONNECTION_ID_INVALID  - still not set
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_ConnectionRefType, DCM_CODE) Dcm_PruGetUsedConnection(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return dcmPruCurrentConnection;
}
# endif

/***********************************************************************************************************************
 *  Dcm_PruInit
 **********************************************************************************************************************/
/*! \brief      Initilizes the PeriodicResponderUnit
 *  \context    Function must be called with disabled interrupt context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PruReleaseConnection();
  Dcm_PruOnInit();
}

/***********************************************************************************************************************
 *  Dcm_PruTransmit
 **********************************************************************************************************************/
/*! \brief      Allocates a resource (data buffer) for periodic transmission
 *  \param[in]  handle                     The resource handle got at "allocate" time.
 *  \param[in]  length                     The length of the response data.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_PruTransmit(Dcm_PeriodicHandleType handle, uint8 length)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn = E_NOT_OK;

  Dcm_CheckApiValueRangeFailed(dcmPruCurrentConnection != DCM_CONNECTION_ID_INVALID, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Only if full communication is active may send */
  if(dcmStateMachine.CommState == DCM_COMM_STATE_FULL)
  {
    stdReturn = Dcm_PruDoTransmit(handle, length);
  }

  if(!Dcm_DslLL_IsPduRTxAccepted(stdReturn))
  {
    /* Call directly release, since at this time the handle is still valid */
    Dcm_PruReleaseResource(handle);
  }
}
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
/***********************************************************************************************************************
 *  Dcm_DslInit
 **********************************************************************************************************************/
/*! \brief      DSL initalization
 *  \context    Function must be called within disabled all interrupts.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_INACTIVE;
  dcmStateMachine.CommState     = DCM_COMM_STATE_NONE;

  /* Not needed since each request resets these elements
   * dcmDslInfoPool[DCM_CONTEXT_ID_UDS].serviceIndex = 0;
   */
  /* Set default timings */
  dcmDslTimerSettings.timeOutP2   = dcm10_ServiceInfoTable[0].TickTime.timeOutP2;
  dcmDslTimerSettings.timeOutP2Ex = dcm10_ServiceInfoTable[0].TickTime.timeOutP2Ex;

  /* Context specific initialisation */
  {
    DCM_CONTEXT_ITER_DEF_LOCAL

    DCM_CONTEXT_ITER_VALUE_INIT;
    DCM_CONTEXT_ITER_LOOP
    {
      DCM_CONTEXT_ITER_VALUE_DEC;

      /* Prepare RCR-RP response info pool */
      dcmDslBufferRcrRpTx[DCM_CONTEXT_ITER_VALUE][0] = 0x7Fu;
      dcmDslBufferRcrRpTx[DCM_CONTEXT_ITER_VALUE][2] = 0x78u;

      /* Init response type */
      dcmDslInfoPool[DCM_CONTEXT_ITER_VALUE].resType = DSL_RES_TYPE_NONE;
      /* Not needed since each request resets these elements
       * dcmDslInfoPool[DCM_CONTEXT_ITER_VALUE].rcrRpState =  DSL_RES_TYPE_NONE;
       */
      dcmDslInfoPool[DCM_CONTEXT_ITER_VALUE].contextState  = DCM_CONTEXT_STATE_FREE;
#if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
      dcmDslInfoPool[DCM_CONTEXT_ITER_VALUE].isConnectionLocked = FALSE;
#endif
    }
  }

  /*Init state machine*/
  {
    uint8_least iter = DCM_NUM_STATE_GROUPS;

    while(iter != 0)
    {
      iter--;
      dcmCurrentStateInfo[iter] = 0;/* Set to default states */
    }
  }

  Dcm_DslLL_Init();
}

/***********************************************************************************************************************
 *  Dcm_DslHL_ReceptionFinished
 **********************************************************************************************************************/
/*! \brief      HighLevel reception end notification.
 *  \param[in]  status  Reception status.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslHL_ReceptionFinished(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslCommStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  boolean doIgnoreRequest = FALSE;

  Dcm_CheckDcmInit(DcmServiceId_RxIndication);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  /* Only from RxStart */
  if(DCM_CONTEXT_STATE_RX_STARTED == dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState)
  {
    if(status == DSL_COMM_E_OK)
    {
      /*1.Start S3 timer if status != OK*/
      /* Check functional tester present */
      if((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr[0] == 0x3E)&&(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].addrType == DCM_ADDR_TYPE_FUNC))
      {
        /* Check for SPRMIB availability */
        if((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr[1] == 0x80)&&(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataLength == 2))
        {
          doIgnoreRequest = TRUE;
        }
      }
    }
    else
    {
      doIgnoreRequest = TRUE;
    }

    if(doIgnoreRequest == TRUE)
    {
      /* Clear queued STOP event if not processed. If already processed makes no difference. */
      /* No check for VirtualRequests since the 0x3E tester shall be able to restart the S3 Timer!!! 
       * Virtual requests can no land here !!! */
      Dcm_TmrMgrStartTimer(DCM_TIMER_ID_S3, DCM_TIMEOUT_S3);

      Dcm_DslLL_ReleaseRxResource(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dslHandle);
      dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState = DCM_CONTEXT_STATE_FREE;
    }
    else
    {
      /* Prepare for RCR-RP response -before- starting the P2 timer */
      dcmDslBufferRcrRpTx[DCM_CONTEXT_PARAM_VALUE][1] = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr[0];
      dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].rcrRpState  =  DSL_RES_TYPE_NONE;
      dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState = DCM_CONTEXT_STATE_RX_ENDED;

      /*2.Call DSD with the new data*/
      Dcm_TmrMgrStartTimer(DCM_CONTEXT_P2_TIMER_ID(DCM_CONTEXT_PARAM_VALUE), dcmDslTimerSettings.timeOutP2);

      Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_PARAM_VALUE), DCM_EVENT_NEW_REQ);

      /* Process the activity */
      Dcm_ProcessActivity(DCM_ACTIVITY_SOURCE_RX_IND);
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_DslHL_TransmissionFinished
 **********************************************************************************************************************/
/*! \brief      HighLevel transmission end notification.
 *  \param[in]  status                      Reception status.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DslHL_TransmissionFinished(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslCommStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_TxConfirmation);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  if((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType & DSL_RES_TYPE_RCRRP_ANY) != 0)
  {
    /* Store the status for this case only */
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].txConfStatus = status;
    /* Remember a rcrrp is done sending - even if tx failed continue as if succeeded */
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].rcrRpState = DSL_RES_TYPE_RCRRP_FINISHED;

    if((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType & DSL_RES_TYPE_RCRRP_RTE) != 0)
    {
      Dcm_EvMgrSetEvent(DCM_TASK_ID_STATE, DCM_EVENT_RCRRP_CONFIRM);
    }
  }
  else
  {
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
    if((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType & DSL_RES_TYPE_SPONTANEOUS) != 0)
    {
      /* Unlock DCM */
      /* Dectivate COM */
      Dcm_ProcessActivity(DCM_ACTIVITY_SOURCE_FBL_RESPONDER);
      Dcm_DoUnLock(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dslHandle);
    }
    else
#endif
    {
      Dcm_DslDoPostProcessing(DCM_CONTEXT_PARAM_VALUE_FIRST status);
    }
  }

  dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType = DSL_RES_TYPE_NONE;
}

/***********************************************************************************************************************
 *  Dcm_DsdDispatcher
 **********************************************************************************************************************/
/*! \brief      Service ID dispathier
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DsdDispatcher(DCM_CONTEXT_PARAM_DEF_ONLY)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least sidIter;
  boolean     hasSprmib = FALSE;

  dcmDsdErrorRegister[DCM_CONTEXT_PARAM_VALUE] = DCM_E_OK;

  dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].msgAddInfo = 0;
  /* Init always here because of the negative response during service validation */
  if(DCM_ADDR_TYPE_FUNC == dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].addrType)
  {
    dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].msgAddInfo |= DCM_MSGADDINFO_REQ_TYPE;
  }
  dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].resMaxDataLen      = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].maxBufferLength;
  dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].resDataLen         = 0;
  dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqData       = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr;
  dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].resData       = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr;
  dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqDataLen    = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataLength;

  /* Prepare for invalid service */
  dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].serviceIndex = DCM_NUM_SERVICES;
  sidIter = Dcm_FindValueUint8(dcmDspServiceIdCfgVariant, dcmDspServiceIdTypeList, dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqData[0]);

#if (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON)
  if(0 == sidIter) /* Not found */
  {
    Std_ReturnType stdReturn;

    stdReturn = Dcm_CheckUnspecifiedService(dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqData[0], &hasSprmib);
    if(DCM_E_OK == stdReturn)
    {
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcmUnspecSvc_ProxyContext.sid = dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqData[0];
      sidIter = DCM_NUM_SERVICES;/* Redirect to the unspec service handle (last in the config table) */
    }
  }
#endif
  if(sidIter != 0)
  {
    sidIter--;

    /* Check SID execution state precondition(s)*/
    (void)Dcm_CheckServiceState(dcmDspServiceInfoTable[sidIter].StateFilterIdx, DCM_STATE_LVL_SID, &dcmDsdErrorRegister[DCM_CONTEXT_PARAM_VALUE]);

    if(dcmDsdErrorRegister[DCM_CONTEXT_PARAM_VALUE] == DCM_E_OK)
    {
#if (DCM_NUM_CONTEXTS > 1)
# if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
     (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
      /* Execute only if necessary */
      if( (dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX] != 0)
        &&((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].protocolType & (Dcm_DiagProtocolType)(DCM_DIAG_PROTOCOL_WWHOBD|DCM_DIAG_PROTOCOL_OBD)) != 0) )
      {
        /* Enforce entering into the default session 
         * Make it after the exec precondition check to allow SID state filtering (e.g. ProgrammingMode) 
         */
        Dcm_ExecuteStateTransition(DCM_DEFAULT_SESSION_STATE_TRANS_IDX);
#  if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
        Dcm_DslFreeSessionOwner();
#  endif
      }
# endif
#endif
      /* Check if minimum length and if total available (!= 0) are there */
      if((dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqDataLen >= dcmDspServiceInfoTable[sidIter].MinReqLength)&&
         ((dcmDspServiceInfoTable[sidIter].TotalReqLength == 0)||
          (dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqDataLen == dcmDspServiceInfoTable[sidIter].TotalReqLength)))
      {
        hasSprmib =(boolean)((FALSE != hasSprmib) || ((dcmDspServiceInfoTable[sidIter].SvcProperty & DCM_SUPP_POS_RES_BIT)!= 0));
        Dcm_MsgContextMoveRel(1,1);

        if( (FALSE != hasSprmib)
         &&((dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqData[0] & 0x80)!=0))
        {
          dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].msgAddInfo |= DCM_MSGADDINFO_SUPP_POS_RES;
          dcmDsdMsgContext[DCM_CONTEXT_PARAM_VALUE].reqData[0] &= (Dcm_MsgItemType)0x7F;
        }

        /* By default - no transition */
        dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].stateTransRef = DCM_NUM_STATE_TRANSITIONS;
        dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].serviceIndex  = (uint8)sidIter;
        dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].pendingSessChgIdx = DCM_NO_PEND_SESCHG_IDX;
        /* Call service-handler */
        dcmDspServiceInfoTable[sidIter].ServiceProcessor();
        /* Skip since processing done can be called inside the main-handler */
        return;
      }
      else
      {
        /* Too short service length */
        dcmDsdErrorRegister[DCM_CONTEXT_PARAM_VALUE] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
    }
  }
  else
  {
    dcmDsdErrorRegister[DCM_CONTEXT_PARAM_VALUE] = DCM_E_SERVICENOTSUPPORTED;
  }

  /* Here always error case */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DemMgrReleaseDemClient
 **********************************************************************************************************************/
/*! \brief      Release locked resource
 *  \param[in]  clientId       clientId to release
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DemMgrReleaseDemClient(Dcm_DemMgrDemClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmDemMgrResourceMap[clientId] = 0;
}
#endif

#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DemMgrIsDemClientLocked
 **********************************************************************************************************************/
/*! \brief      Check if concrete operations(s) are locked by a client
 *  \param[in]  clientId       clientId to release
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_DemMgrIsDemClientLocked(Dcm_DemMgrDemOpType demOp, Dcm_DemMgrDemClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return (boolean)((dcmDemMgrResourceMap[clientId] & demOp) != 0);
}
#endif

#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DemMgrInit
 **********************************************************************************************************************/
/*! \brief      DEM Manager initialization
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DemMgrInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DemMgrDemClientType clientIter = DCM_DEMMGR_NUM_DEM_CLIENTS;

  while(clientIter != 0)
  {
    clientIter--;
    Dcm_DemMgrReleaseDemClient(clientIter);
  }
# if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  dcmDemMgrDtcUpdateRegister = 0;
# endif
}
#endif

/***********************************************************************************************************************
 *  Dcm_DemMgrRequestDisableDtcUpdate
 **********************************************************************************************************************/
/*! \brief      Managed disable DTC record update
 *  \param[in]  clientId    Client Id that requests access
 *  \return     Reservation result
 *  \retval     E_OK - success the DEM has acepted the operation
 *  \retval     E_NOT_OK - failed (DEM not able to lock)
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DemMgrRequestDisableDtcUpdate(Dcm_DemMgrDemClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdResult = DCM_E_OK; /* PRQA S 3197 */ /* QAC 7.0:  The initialiser for 'stdReturn' is always modified before being used. */ /* Safety code */

#if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  if(dcmDemMgrDtcUpdateRegister == 0)
#endif
  {
    stdResult = Dem_DisableDTCRecordUpdate();
  }

#if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  dcmDemMgrDtcUpdateRegister |= (uint8)(0x01 << clientId);
#endif

  DCM_IGNORE_UNREF_PARAM(clientId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  return stdResult;
}

/***********************************************************************************************************************
 *  Dcm_DemMgrRequestEnableDtcUpdate
 **********************************************************************************************************************/
/*! \brief      Managed enable DTC record update
 *  \param[in]  clientId    Client Id that requests access
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
DEMMGR_FUNC_LOC FUNC(void, DCM_CODE) Dcm_DemMgrRequestEnableDtcUpdate(Dcm_DemMgrDemClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
#if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  /* Unregister user */
  dcmDemMgrDtcUpdateRegister &= (uint8)(~(uint8)(0x01 << clientId));
  if(dcmDemMgrDtcUpdateRegister == 0)
#endif
  {
    (void)Dem_EnableDTCRecordUpdate();
  }
  DCM_IGNORE_UNREF_PARAM(clientId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
}

#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DemMgrLockDemUdsClient
 **********************************************************************************************************************/
/*! \brief      Locks a DEM resourse for the UDS client (i.e. 0x19)
 *  \param[in]  demOp       Handle to a DEM located in the service 19 table to be locked
 *  \return     Reservation result
 *  \retval     TRUE - success (free place found)
 *  \retval     FALSE - failed (already locked)
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(boolean, DCM_CODE) Dcm_DemMgrLockDemUdsClient(Dcm_DemMgrDemOpType demOp)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if(DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  if(DCM_CONTEXT_ID_OBD == lContext)
  {
    return Dcm_DemMgrStealLockDemUdsClient(demOp);
  }
# endif
  /* Check if OBD is doing something */
  if((dcmDemMgrResourceMap[DCM_DEMMGR_CLIENT_ID_OBD] & demOp) == 0)
  {
     /* Lock the resource */
     dcmDemMgrResourceMap[DCM_DEMMGR_CLIENT_ID_UDS] = (Dcm_MemDemMgrDemOpType)demOp;
     return TRUE;
  }
  return FALSE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DidMgrReleaseDidClient
 **********************************************************************************************************************/
/*! \brief      Release locked resource
 *  \param[in]  clientId       clientId to release
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DidMgrReleaseDidClient(Dcm_DidMgrDidClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmDidMgrResourceMap[clientId] = (Dcm_MemDidHandleType)DCM_NUM_DIDS;
}
# endif

/***********************************************************************************************************************
 *  Dcm_DidMgrInit
 **********************************************************************************************************************/
/*! \brief      DID Manager initialization
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DidMgrInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
  Dcm_DidMgrDidClientType clientIter = DCM_DID_MGR_NUM_DID_CLIENTS;

  while(clientIter != 0)
  {
    clientIter--;
    Dcm_DidMgrReleaseDidClient(clientIter);
  }
# endif
# if (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)
  dcmDidMgrExtReadDidState.lastDid = Dcm_Make32Bit(0x80,0,0,0); /* mark first comparison */
# endif
}

# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DidMgrLockDidClient
 **********************************************************************************************************************/
/*! \brief      Locks a DID resourse for one client (e.g. 0x22, 0x2A or 0x2C)
 *  \param[in]  did22Handle       Handle to a DID located in the service 0x22 table to be locked
 *  \param[in]  clientId          Client Id that requests access
 *  \return     Reservation result
 *  \retval     TRUE - success (free place found)
 *  \retval     FALSE - failed (already locked)
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(boolean, DCM_CODE) Dcm_DidMgrLockDidClient(Dcm_DidHandleType did22Handle, Dcm_DidMgrDidClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  if(dcmDidMgrResourceMap[clientId] == (Dcm_MemDidHandleType)DCM_NUM_DIDS)
  {
    Dcm_DidMgrDidClientType iter = DCM_DID_MGR_NUM_DID_CLIENTS;

    /* this client does not own a DID yet - find another owner for this DID */
    while(iter != 0)
    {
      iter--;
      if(dcmDidMgrResourceMap[iter] == did22Handle)
      {
        /* FALSE since it can not be the current client */
        return FALSE;
      }
    }
    /* Lock the resource */
    dcmDidMgrResourceMap[clientId] = (Dcm_MemDidHandleType)did22Handle; /* PRQA S 3689 */ /* Not possible to have out of boundary access since 
                                                                                             * the number of cuncurent clients is equal to the number of resources. Assertion checks this during development.*/
  }
  else
  {
    /* it must be the same did22Handle since no parallel processing of the client is possible */
    Dcm_BoolCheckValueRangeFailed((dcmDidMgrResourceMap[clientId] == (Dcm_MemDidHandleType)did22Handle), DcmServiceId_DsdDispatcher); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  }

  return TRUE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) && (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)) )
/***********************************************************************************************************************
 *  Dcm_MemAccHwAbInit
 **********************************************************************************************************************/
/*! \brief      Generic memory access byte stream to data type converter
 *  \param[in]  byteStream      byte stream to be converted
 *  \param[in]  len             byte stream length
 *  \return     packed value of the stream
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_MemAccHwAbInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* not used */
}

/***********************************************************************************************************************
 *  Dcm_MemAccHwAbMakePointer
 **********************************************************************************************************************/
/*! \brief      Converts INT to valid HW specific pointer
 *  \param[in]  addr      physical address
 *  \return     HW address
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_ApplDataPtrType, DCM_CODE) Dcm_MemAccHwAbMakePointer(Dcm_MemAddrType addr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return (Dcm_ApplDataPtrType)(addr);
}
#endif /* ((((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) && (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)) && !defined (C_COMP_ANSI_CANOE)) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  Dcm_MemAccInit
 **********************************************************************************************************************/
/*! \brief      Initialization of the memory access manager 
 *  \context    Function must be called within disabled interrupt context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_MemAccInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)
  Dcm_MemAccHwAbInit();
# endif
}

# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_MemAccMemBlockLookUp
 **********************************************************************************************************************/
/*! \brief      Generic memory access memory block look-up routine
 *  \param[in]  pLookUpTable          look-up table with memory blocks
 *  \param[in]  pVariantTable         configuration variant assignment table
 *  \param[in]  pMemBlockInfo         memory address and size to be found
 *  \return     Look up result
 *  \retval     TRUE  - success
 *  \retval     FALSE - failed
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
#  if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_MemAccMemBlockLookUp(CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) pLookUpTable,
                                                                           Dcm_CfgVariantTablePtrType pVariantTable,
                                                              CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable,
                                                                           Dcm_MemMgrMemBlockDefPtr pMemBlockInfo)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
#  else
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_MemAccMemBlockLookUp(CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) pLookUpTable,
                                                              CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable,
                                                                           Dcm_MemMgrMemBlockDefPtr pMemBlockInfo)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
#  endif
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MemBlockHandleType iter;
  boolean isFound;

  iter = 1; /* skip the table size entry */
#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
  isFound = FALSE;
  for(;iter <= pLookUpTable[0];iter++)
  {
    if (dcmMemBlockInfoTable[pLookUpTable[iter]].MemId == pMemBlockInfo->memId)
    {
      isFound = TRUE;
      break;/* first MID found! */
    }
  }

  if(FALSE != isFound)
#  endif
  {
    isFound = FALSE; /* reset */

    /* Check for address overflow or no data required (length == 0)*/
    if( (pMemBlockInfo->length == 0) ||
        ( ((Dcm_MemAddrType)(0xFFFFFFFFu) - pMemBlockInfo->address) < (Dcm_MemSizeType)(pMemBlockInfo->length-1) )
      )
    {
      /* invalid parameter values ! */
    }
    else
    {
      /* Any chance to find a memory Block? */
      if (dcmMemBlockInfoTable[pLookUpTable[iter]].StartAddr <= pMemBlockInfo->address)
      {
        /* Find start position block */
        for(;iter <= pLookUpTable[0];iter++)
        {
          CONSTP2CONST(Dcm_MemoryBlockInfoType, AUTOMATIC, DCM_CONST) pMemBlockEntry = &dcmMemBlockInfoTable[pLookUpTable[iter]];

#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
          /* Still on the same MID? */
          if (pMemBlockEntry->MemId != pMemBlockInfo->memId)
          {
            break;/*  that was it */
          }
#  endif
          if ( (0 == pMemBlockEntry->Length) ||
               ( (pMemBlockEntry->StartAddr + (pMemBlockEntry->Length - 1)) >= pMemBlockInfo->address ) )
          {
#  if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
            if((pVariantTable[iter] & dcmStateMachine.CfgVariantMask) != 0)
#  endif
            {
              isFound = TRUE;
            }
            break; /* PRQA S 0771 */ /* QAC 7.0:  More than one break statement is being used to terminate an iteration statement. */ /* Required in order to avoid additional local variables and 'if' tests */
          }
        }/* for end */

        /* Scan for consequtive matching ranges if start position found */
        if(FALSE != isFound)
        {
          Dcm_MemAddrType lastEnd = dcmMemBlockInfoTable[pLookUpTable[iter]].StartAddr;
          Dcm_MemAddrType reqBlockEnd = (Dcm_MemAddrType)(pMemBlockInfo->address + (pMemBlockInfo->length - 1));/* -1 to avoid overflow - just point to the last cell in this range!*/
          uint8_least stateGrpIter = DCM_NUM_STATE_GROUPS;

          /* Prepare for state group merge - open it for all states */
          do
          {
            --stateGrpIter;
            dcmMemMgrReqBlockStatePrecond[stateGrpIter] = (Dcm_StateMaskType)0xFFFFFFFFu;
          }
          while(stateGrpIter != 0);

          isFound = FALSE;/* reset */

          for(;iter <= pLookUpTable[0];iter++)
          {
            CONSTP2CONST(Dcm_MemoryBlockInfoType, AUTOMATIC, DCM_CONST) pMemBlockEntry = &dcmMemBlockInfoTable[pLookUpTable[iter]];

#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
            if (pMemBlockEntry->MemId != pMemBlockInfo->memId)
            {
              /* that was it. */
              break;
            }
#  endif
            if( (pMemBlockEntry->StartAddr != lastEnd) /* Not a consequtive block? */
#  if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
              ||( (pVariantTable[iter] & dcmStateMachine.CfgVariantMask) == 0) /* Not active? */
#  endif
              )
            {
              break;/* PRQA S 0771 */ /* not found - there is a gap */ /* QAC 7.0:  More than one break statement is being used to terminate an iteration statement. */ /* Required in order to avoid additional local variables and 'if' tests */
            }/* else - go on */

            /* Merge states of current block */
            {
              Dcm_StateFilterIndexType ref = stateInfoTable[iter-1];
              stateGrpIter = DCM_NUM_STATE_GROUPS;

              do
              {
                --stateGrpIter;
                dcmMemMgrReqBlockStatePrecond[stateGrpIter] &= DcmServiceStateFilterPool(ref,stateGrpIter);
              }
              while(stateGrpIter != 0);
            }
            Dcm_AddValue(lastEnd , Dcm_MemAddrType, pMemBlockEntry->Length);/* possible overflow? Yes, but if so, then it was the last iteration - don't care about overflow. */
            /* Test for loop end condition */
            if( (0 == pMemBlockEntry->Length) || /* Check for open ended range */
                ( ((Dcm_MemAddrType)(lastEnd - 1) >= reqBlockEnd) ) /* -1: compare end addresses of a range, not the next start address*/
              )
            {
              /*  End scan... */
              isFound = TRUE;
              break; /* PRQA S 0771 */ /* QAC 7.0:  More than one break statement is being used to terminate an iteration statement. */ /* Required in order to avoid additional local variables and 'if' tests */
            }/* else - Still on scan... */
          }/* for end */
        }/* No start address found - exit */
      }/* else - lowest mem block start address do not match the request */
    }/* invalid parameter value range */
  }/* else - no MID found */
  return isFound;
}
# endif

# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_MemAccCheckMemBlockState
 **********************************************************************************************************************/
/*! \brief      State execution condition check on a memory block
 *  \return     NRC of the state check
 *  \context    Function must be called on task level only.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_MemAccCheckMemBlockState(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least stateGrpIter;
  Dcm_NegativeResponseCodeType errorCode;

  errorCode = DCM_E_OK;
  /* Iterate the state groups considering their order! */
  for(stateGrpIter = 0; (stateGrpIter < DCM_NUM_STATE_GROUPS)&&(DCM_E_OK == errorCode); stateGrpIter++)
  {
    errorCode = Dcm_CheckServiceStateMatch(dcmMemMgrReqBlockStatePrecond[stateGrpIter], stateGrpIter, DCM_STATE_LVL_PARAM);
  }
  return errorCode;
}
# endif
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#if (DCM_SERVICE_01_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_01_ProcessPid
 **********************************************************************************************************************/
/*! \brief      Processes a single PID
 *  \param[in]  pidDescPtr          The PID descriptor to be processed
 *  \return     Result
 *  \retval     E_OK - success
 *  \retval     != E_OK - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_01_ProcessPid(Dcm_ObdIdListItemPtrType pidDescPtr)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  Dcm_MsgLenType dataLen = 1;/* don't forget the PID */

  dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[0] = pidDescPtr->id; /* skip the size item */

  stdReturn = dcm01_ServiceInfoTable[pidDescPtr->handle].ReadData((Dcm_RteDataPtrType)(&dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[1]));/* PRQA S 0310 */ /* PRQA S 0308 */
  Dcm_AddValue(dataLen, Dcm_MsgLenType, dcm01_ServiceInfoTable[pidDescPtr->handle].Length);

  Dcm_MsgContextMoveRel(0, (sint32_least)dataLen);

  return stdReturn;
}
#endif /* (DCM_SERVICE_01_ENABLED == STD_ON) */
#if (DCM_SERVICE_06_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_06_ReadDataId
 **********************************************************************************************************************/
/*! \brief      Service 0x06 reader
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_06_ReadDataId(uint8 midHandle, Dcm_RteDataPtrType resData)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  uint16 lTestValue;
  uint16 lMinLimit;
  uint16 lMaxLimit;
  uint8  lStatus;
  uint8  lMid;
  Dcm_MsgType lResData;

  P2CONST(Dcm_ObdMidMgrTidInfoType, AUTOMATIC, DCM_CONST) tidObject;
  uint8_least tidIter;

  lResData = (Dcm_MsgType)(*resData);
  lMid = dcm06_MidLookUpTable[midHandle + 1];/* skip the size item */

  tidObject = &dcmObdMidMgr_TidInfoTable[dcmObdMidMgr_MidIndTable[dcm06_ServiceInfoTable[midHandle].TidRefList]];

  tidIter = dcm06_ServiceInfoTable[midHandle].NumTids;
  while(tidIter != 0)
  {
    --tidIter;
    stdReturn = tidObject->GetDtrValue(&lTestValue, &lMinLimit, &lMaxLimit, &lStatus);

    if(DCM_E_OK != stdReturn)
    {
      return DCM_E_NOT_OK;
    }

    if(DCM_DTRSTATUS_INVISIBLE == lStatus)
    {
      lTestValue = 0;
      lMinLimit = 0;
      lMaxLimit = 0;
    }

    /* Copy data */
    lResData[0] = lMid;

    lResData[1] = tidObject->TestId;

    lResData[2] = tidObject->UnitAndScalingId;

    lResData[3] = Dcm_GetHiByte(lTestValue);
    lResData[4] = Dcm_GetLoByte(lTestValue);

    lResData[5] = Dcm_GetHiByte(lMinLimit);
    lResData[6] = Dcm_GetLoByte(lMinLimit);

    lResData[7] = Dcm_GetHiByte(lMaxLimit);
    lResData[8] = Dcm_GetLoByte(lMaxLimit);

    lResData = &lResData[9];/* next data block */

    tidObject = &tidObject[1];/* next MIDTID object */
  }

  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_06_ProcessMid
 **********************************************************************************************************************/
/*! \brief      Processes a single MID
 *  \param[in]  midDescPtr          The MID descriptor to be processed
 *  \return     Result
 *  \retval     E_OK - success
 *  \retval     != E_OK - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_06_ProcessMid(Dcm_ObdIdListItemPtrType midDescPtr)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  Dcm_MsgLenType dataLen = 0;

  if(FALSE != midDescPtr->isAvailabilityId)
  { /* Supported MID */
    /* Copy the MID */
    dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[0] = midDescPtr->id;
    /* Supported TID (calculate offset since if this code reached - ID is supported */
    stdReturn = Dcm_ObdMgrReadSupportedId(dcm06_SupportedMidMask[Dcm_ObdMgrAvailabilityIdIdx(midDescPtr->id)], (Dcm_RteDataPtrType)&dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[1]);/* PRQA S 0310 */ /* PRQA S 0308 */
    Dcm_AddValue(dataLen, Dcm_MsgLenType, 5);
  }
  else
  {
    /* Data MID */
    uint8 numTids = dcm06_ServiceInfoTable[midDescPtr->handle].NumTids;
    stdReturn = Dcm_06_ReadDataId(midDescPtr->handle, (Dcm_RteDataPtrType)(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData));/* PRQA S 0310 */ /* PRQA S 0308 */
    /* Total length = 9 * TidCount = 8 * TidCount +  TidCount*/
    Dcm_AddValue(dataLen, Dcm_MsgLenType, (Dcm_MsgLenType)((numTids << 3) + numTids));
  }

  Dcm_MsgContextMoveRel(0, (sint32_least)dataLen);

  return stdReturn;
}
#endif /* (DCM_SERVICE_06_ENABLED == STD_ON) */
#if (DCM_SERVICE_08_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_08_ProcessTid
 **********************************************************************************************************************/
/*! \brief      Processes a single TID
 *  \param[in]  tidDescPtr          The TID descriptor to be processed
 *  \return     Result
 *  \retval     E_OK - success
 *  \retval     != E_OK - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_08_ProcessTid(Dcm_ObdIdListItemPtrType tidDescPtr)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  Dcm_MsgLenType dataLen = 1;/* don't forget the TID */

  dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[0] = tidDescPtr->id; /* skip the size item */

  if(FALSE != tidDescPtr->isAvailabilityId)
  {
    /* Supported TID (calculate offser since if this code reached - ID is supported */
    stdReturn = Dcm_ObdMgrReadSupportedId(dcm08_SupportedTidMask[Dcm_ObdMgrAvailabilityIdIdx(tidDescPtr->id)], (Dcm_RteDataPtrType)&dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[1]);/* PRQA S 0310 */ /* PRQA S 0308 */
    Dcm_AddValue(dataLen , Dcm_MsgLenType, 4);
  }
  else
  {
    /* Control TID */
    stdReturn = dcm08_ServiceInfoTable[tidDescPtr->handle].Control();
  }

  Dcm_MsgContextMoveRel(0, (sint32_least)dataLen);

  return stdReturn;
}
#endif /* (DCM_SERVICE_08_ENABLED == STD_ON) */
#if (DCM_SERVICE_09_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_09_ProcessVid
 **********************************************************************************************************************/
/*! \brief      Processes a single VID
 *  \param[in]  vidDescPtr          The VID descriptor to be processed
 *  \return     Result
 *  \retval     E_OK - success
 *  \retval     != E_OK - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_09_ProcessVid(Dcm_ObdIdListItemPtrType vidDescPtr)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  /* Copy the VID */
  dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[0] = vidDescPtr->id;

  {
    /* Data or supported VID */
    Dcm_MsgLenType dataLen = 1;/* don't forget the VID */
    /* Possible collision with some other DIDs ? */
    if(dcmObdRepeatedProxyContexts.dcm09_ProxyContext.did22Handle < DCM_NUM_DIDS)
    {
      boolean lIsReserved;
      lIsReserved = Dcm_DidMgrLockDidClient(dcmObdRepeatedProxyContexts.dcm09_ProxyContext.did22Handle, DCM_DIDMGR_CLIENT_ID_OBD);
      if(FALSE == lIsReserved)
      {
        return DCM_E_PENDING; /* Try again */
      }
    }

    stdReturn = dcm09_ServiceInfoTable[vidDescPtr->handle].ReadData((Dcm_RteDataPtrType)(&dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[1]));/* PRQA S 0310 */ /* PRQA S 0308 */
    Dcm_AddValue(dataLen  , Dcm_MsgLenType, dcm09_ServiceInfoTable[vidDescPtr->handle].Length);
    if(DCM_E_PENDING == stdReturn)
    {
      /* do nothing - wait for next call */
    }
    else
    {
      /* unlock any time if reading has been finished */
      Dcm_DidMgrReleaseDidClient(DCM_DIDMGR_CLIENT_ID_OBD);

      if(DCM_E_OK == stdReturn)
      {
        /* Data written - move on */
        Dcm_MsgContextMoveRel(0, (sint32_least)dataLen);
      }
    }
  }

  return stdReturn;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_09_ENABLED == STD_ON) */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_10_RepeaterProxyChanger
 **********************************************************************************************************************/
/*! \brief      Service 0x10 changer polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_10_RepeaterProxyChanger(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  switch(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm10_ProxyContext.Progress)
  {
    /*-----------------------------------------*/
      case DCM_10_FBL_SET_PROG_CONDITIONS:
    /*-----------------------------------------*/
        {
          Dcm_ProgConditionsType progConds;

          progConds.EcuStartMode = DCM_WARM_START;
          progConds.Sid = 0x10;
          progConds.SubFncId = 0x02;
          progConds.TesterSourceAddr = dcmDslPduConnectionInfoTable[dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dslHandle].sourceAddr;

          Dcm_SetProgConditions(&progConds);

          Dcm_SendResponsePending(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(DCM_CONTEXT_ID_UDS) DSL_RES_TYPE_RCRRP_INT);
          /* Prepare next step */
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm10_ProxyContext.Progress = DCM_10_FBL_WAIT_RCR_RP;
        }
    /*-----------------------------------------*/
      case DCM_10_FBL_WAIT_RCR_RP: /* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */
    /*-----------------------------------------*/
        if(dcmDslInfoPool[DCM_CONTEXT_ID_UDS].rcrRpState == DSL_RES_TYPE_RCRRP_FINISHED)
        {
          /* wait until after confirmation */
          Dcm_DspPerformReset(DCM_HARD_RESET);
          return DCM_E_OK;/* wait for reset */
        }
        /* try again */
        return DCM_E_PENDING;
    /*-----------------------------------------*/
      default:
    /*-----------------------------------------*/
        /* Shall be never reached */
        Dcm_CheckAlwaysFailed(DcmServiceId_SetProgConditions);
        break;
  }
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

/***********************************************************************************************************************
 *  Dcm_10_ChgSession
 **********************************************************************************************************************/
/*! \brief      Service 0x10 default session changer
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE  FUNC(Std_ReturnType, DCM_CODE) Dcm_10_ChgSession(Dcm_SesCtrlType curSession, Dcm_SesCtrlType newSession)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(curSession); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  DCM_IGNORE_UNREF_PARAM(newSession); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
  if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
  {
    if(0x02 == newSession)
    {
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm10_ProxyContext.Progress = DCM_10_FBL_SET_PROG_CONDITIONS;
      Dcm_RegisterRepeaterProxy(Dcm_10_RepeaterProxyChanger);
      return DCM_E_OK;
    }
  }
# endif
  /* Finish the service processing */
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_10_ENABLED == STD_ON) */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_10_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x10 polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_10_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  Dcm_NegativeResponseCodeType  errorCode = DCM_E_OK;
  Dcm_SesCtrlType curSession;

  curSession = Dcm_GetCurrentSession();

  /* The record options are in the resDataBuffer already!!! */
  stdReturn = dcm10_SesChgPermFunc(curSession, (Dcm_SesCtrlType)*dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData);

  /* Important: no sync usage any more! */
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      /* Send the prepared pos response */
      break;
  /*------------------*/
    case DCM_E_SESSION_NOT_ALLOWED:/*fall through*/
    case DCM_E_NOT_OK:
  /*------------------*/
      errorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;
  /*------------------*/
    case DCM_E_FORCE_RCRRP:/* fall through */
  /*------------------*/
      Dcm_SendResponsePending(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(DCM_CONTEXT_ID_UDS) DSL_RES_TYPE_RCRRP_RTE);

  /*------------------*/
    case DCM_E_PENDING:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      errorCode = DCM_E_GENERALREJECT;
      break;
  }

  Dcm_SetNegResponse(errorCode);

  /* Delegate job always */
  return Dcm_10_ChgSession(curSession, (Dcm_SesCtrlType)*dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData);
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_10_ENABLED == STD_ON) */
#if (DCM_SERVICE_11_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_11_PrepareReset
 **********************************************************************************************************************/
/*! \brief      Service 0x11 default rset prepare
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_11_PrepareReset(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Close the processing */
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_11_ENABLED == STD_ON) */
#if (DCM_SERVICE_11_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_11_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x11 polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_11_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  Dcm_NegativeResponseCodeType  errorCode = DCM_E_OK;

  /* The record options are in the resDataBuffer already!!! */
  stdReturn = dcm11_EcuResetPermFunc(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm11_ProxyContext.resetLevel, &errorCode);

  /* Important: no sync usage any more! */
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      /* Send the prepared pos response */
      break;
  /*------------------*/
    case DCM_E_NOT_OK:
  /*------------------*/
      errorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      errorCode = DCM_E_GENERALREJECT;
      break;
  }

  if(DCM_E_OK != errorCode)
  {
    Dcm_SetNegResponse(errorCode);
    Dcm_ProcessingDone();
  }
  else
  {
    /* delegate the job */
    Dcm_11_PrepareReset();
  }
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_11_ENABLED == STD_ON) */
#if (DCM_SERVICE_14_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_14_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x14 polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_14_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_ReturnClearDTCType resultClrDtc;
  Dcm_NegativeResponseCodeType errorCode = DCM_E_OK;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();


  resultClrDtc = Dem_ClearDTC(dcmRepeatedProxyContexts[lContext].dcm14_ProxyContext.dtcNum,
                  DEM_DTC_KIND_ALL_DTCS,
                  DEM_DTC_ORIGIN_PRIMARY_MEMORY);

  /* variable initialized in each switch-case */
  switch(resultClrDtc)
  {
    case DEM_CLEAR_FAILED:
      /* Clear DTC failed */
      errorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;
    case DEM_CLEAR_OK:
      /* Good case do nothing */
      break;
    case DEM_DTC_PENDING:
      /* try again later */
      return DCM_E_PENDING;
    default:
      /* Any other fault with negative response */
      errorCode = DCM_E_REQUESTOUTOFRANGE;
      break;
  }
# if (DCM_SERVICE_14_STATE_TRANS_ENABLED == STD_ON)
    /* Prepare state transition */
  dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = Dcm_14_GetStateTransitionRef(0);
# endif
  /* dcmDsdMsgContext[lContext].resDataLen = 0;  Set by default from the Dcm_DsdDispatcher. */
  /* Processing finished. */
  Dcm_SetNegResponse(errorCode);
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_14_ENABLED == STD_ON) */
#if (DCM_SERVICE_19_ENABLED == STD_ON)

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_RecIdIterInit
 **********************************************************************************************************************/
/*! \brief      Initializes the record id iteration
 *  \param[in]  reqRecId           Requested record Id
 *  \param[in]  iterList           Record type specific list (snapshot or extended data).
 *  \param[in]  listSize           Record type specific list (snapshot or extended data) size.
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_19_RecIdIterInit(uint8 reqRecId, Dcm_19_RecordListPtrType iterList, uint8 listSize)
#  else
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_19_RecIdIterInit(uint8 reqRecId)
#  endif
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.reqRecordNumber = reqRecId;

#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_OFF)
  dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordListSize = 0xFEu;
#  endif
  if(reqRecId == 0xFF)
  {
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.allRecNumbers = TRUE;
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordList = iterList;
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordListSize = listSize;
#  endif
  }
  else
  {
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.allRecNumbers = FALSE;
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordList = NULL_PTR;
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordListSize = 0xFEu;
#  endif
  }
}
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_RecIdIterGoBack
 **********************************************************************************************************************/
/*! \brief      Navigates the record id iteration one step back.
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_19_RecIdIterGoBack(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();
  dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordNumber--;
  dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordIterator++;
}
# endif


# if (DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_07_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_GetTranslationFormat
 **********************************************************************************************************************/
/*! \brief      Extracts on DEM version dependent way the translation format
 *  \return     Translation format
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(uint8, DCM_CODE) Dcm_19_GetTranslationFormat(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8 result;
  /* evaluate the DTCFormatIdentifier */
  result = Dem_GetTranslationType();

#  if defined(DEM_DTC_TRANSLATION_ISO15031_6) || \
      defined(DEM_DTC_TRANSLATION_J1939_73)   || \
      defined(DEM_DTC_TRANSLATION_ISO11992_4) || \
      defined(DEM_DTC_TRANSLATION_ISO14229_1) || \
      defined(DEM_DTC_TRANSLATION_J2012DA_WWHOBD) || \
      defined(DEM_DTC_TRANSLATION_CUSTOMER)   || \
      defined(DEM_DTC_TRANSLATION_INTERNAL)
  /* Map AUTOSAR TranslationFormat into UDS */
  switch(result)
  {
#   if defined(DEM_DTC_TRANSLATION_ISO15031_6)
  case DEM_DTC_TRANSLATION_ISO15031_6:
    result = 0x00;
    break;
#   endif
#   if defined(DEM_DTC_TRANSLATION_J1939_73)
  case DEM_DTC_TRANSLATION_J1939_73:
    result = 0x02;
    break;
#   endif
#   if defined(DEM_DTC_TRANSLATION_ISO11992_4)
  case DEM_DTC_TRANSLATION_ISO11992_4:
    result = 0x03;
    break;
#   endif
#   if defined(DEM_DTC_TRANSLATION_J2012DA_WWHOBD)
  case DEM_DTC_TRANSLATION_J2012DA_WWHOBD:
    result = 0x04;
    break;
#   endif
#   if defined(DEM_DTC_TRANSLATION_ISO14229_1)
  case DEM_DTC_TRANSLATION_ISO14229_1:
    result = 0x01;
    break;
#   endif
#   if defined(DEM_DTC_TRANSLATION_CUSTOMER)
  case DEM_DTC_TRANSLATION_CUSTOMER:
    result = 0x01;
    break;
#   endif
#   if defined(DEM_DTC_TRANSLATION_INTERNAL)
  case DEM_DTC_TRANSLATION_INTERNAL:
    result = 0x01;
    break;
#   endif
   default:
    /* Return the DEM value directly! */
    Dcm_CheckAlwaysFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
    break;
  }
#  else
  /* no explicit enumeration - use the old code for backward compatibility */

  /* Map AUTOSAR TranslationFormat into UDS */
  /* 2 byte ISO15031-6 DTC */
  if((result & 0x01) != 0)
  {
    result = 0x00u;
  }
  else
  {
    /* 
       3 byte ISO14229-1 DTC 
       Customer specific DTC
       SAEJ1939
       WWH-OBD-format
     */
    result = 0x01u;
  }
#  endif
  return result;
}
# endif

# if (DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_07_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_GetNumDtcByStatusMaskData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  origin                  DTC origin
 *  \param[in]  dtcStatusMask           DTC status mask
 *  \param[in]  filterWithSeverity      Specify to search with or without severity
 *  \param[in]  dtcSeverity             If severity specific search - define the severity level
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_GetNumDtcByStatusMaskData( Dem_DTCOriginType          origin,
                                                                                            Dem_DTCKindType            dtcKind,
                                                                                            Dem_DTCStatusMaskType      dtcStatusMask,
                                                                                            Dem_FilterWithSeverityType filterWithSeverity,
                                                                                            Dem_DTCSeverityType        dtcSeverity)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType      errorCode;
  Dem_ReturnSetDTCFilterType        resultSetDtcFilter;
  Std_ReturnType                    stdResult;
  uint16                            numDtc;
  uint8                             translationFormat;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* All error cases will return 0x22 */
  errorCode = DCM_E_CONDITIONSNOTCORRECT;
  /* prepare for positive case */
  Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, 4);

  /* Copy the status availability mask (in any case) */
  stdResult = Dem_GetDTCStatusAvailabilityMask(dcmDsdMsgContext[lContext].resData);

  if(E_OK == stdResult)
  {
    /* evaluate the DTCFormatIdentifier */
    translationFormat = Dcm_19_GetTranslationFormat();
    /* Form the relevant status bits */
    dtcStatusMask &= dcmDsdMsgContext[lContext].resData[0];
    if (dtcStatusMask != 0)
    {
      resultSetDtcFilter = Dem_SetDTCFilter(dtcStatusMask,
                                            dtcKind,
                                            origin,
                                            filterWithSeverity,
                                            dtcSeverity,
                                            DEM_FILTER_FOR_FDC_NO);
      if(resultSetDtcFilter == DEM_FILTER_ACCEPTED)
      {
        stdResult = Dem_GetNumberOfFilteredDTC(&numDtc);
        if(E_OK == stdResult)
        {
          dcmDsdMsgContext[lContext].resData[1] = translationFormat;
          dcmDsdMsgContext[lContext].resData[2] = Dcm_GetHiByte(numDtc);
          dcmDsdMsgContext[lContext].resData[3] = Dcm_GetLoByte(numDtc);

          errorCode = DCM_E_OK;
        }
      }
    }
    else
    { /* dtcStatusMask == 0 */
      dcmDsdMsgContext[lContext].resData[1] = translationFormat;
      dcmDsdMsgContext[lContext].resData[2] = 0;
      dcmDsdMsgContext[lContext].resData[3] = 0;

      errorCode = DCM_E_OK;
    }
  }

  return errorCode;
}
# endif

# if (DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_ProcessNumDtcByStatusMaskData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  origin                  DTC origin
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_ProcessNumDtcByStatusMaskData(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  return Dcm_19_GetNumDtcByStatusMaskData(origin,
                                          dtcKind,
                                          (Dem_DTCStatusMaskType)dcmDsdMsgContext[lContext].reqData[0],
                                          DEM_FILTER_WITH_SEVERITY_NO,
                                          DEM_SEVERITY_NO_SEVERITY);
}
# endif

# if (DCM_19_READ_BY_STATUS_MASK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_02_0A_0F_13_15_GetData
 **********************************************************************************************************************/
/*! \brief      Data processor of service (0x19 02/0A).
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_02_0A_0F_13_15_GetData(P2VAR(Dcm_MsgType, AUTOMATIC,DCM_VAR_NOINIT) pDataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint16_least           lAvailLen;
  uint32                 reqDtc;
  Dem_DTCStatusMaskType  dtcStatusMask;
  Dcm_MsgType            lDataPtr = *pDataPtr;
#  if (DCM_19_ITER_LIMITATION_ENABLED == STD_ON)
  uint8_least            iterLimiter = DCM_19_MAX_NUM_ITERATIONS;
#  endif
  Dcm_NegativeResponseCodeType lResult;

  Dem_ReturnGetNextFilteredDTCType resultGetNextDtc = DEM_FILTERED_OK;

  lAvailLen = *availLenPtr;

  /* Gather the DTC info */
  while((lAvailLen >= 4)
#  if (DCM_19_ITER_LIMITATION_ENABLED == STD_ON)
      &&((iterLimiter != 0)||(DCM_19_MAX_NUM_ITERATIONS == 0))
#  endif
      )
  {
    resultGetNextDtc = Dem_GetNextFilteredDTC(&reqDtc,
                                              &dtcStatusMask);
    if(resultGetNextDtc != DEM_FILTERED_OK)
    {
      /* Skip the decrement on no matching DTC */
      break;
    }

    /* Put onto the response buffer */
    lDataPtr[0] = Dcm_GetHiLoByte(reqDtc);
    lDataPtr[1] = Dcm_GetLoHiByte(reqDtc);
    lDataPtr[2] = Dcm_GetLoLoByte(reqDtc);
    lDataPtr[3] = (uint8)dtcStatusMask;

    /* Prepare the next data */
    lDataPtr = &lDataPtr[4];
    Dcm_SubValue(lAvailLen  , Dcm_MsgLenType, 4);
#  if (DCM_19_ITER_LIMITATION_ENABLED == STD_ON)
    iterLimiter--;/* decrement always (even if no limitation available (max == 0)*/
#  endif
  }

  /* Update the length and the new pointer only if success - otherwise undo (do not change) */
  *availLenPtr = (Dcm_MsgLenType)lAvailLen;
  *pDataPtr = lDataPtr;


  switch(resultGetNextDtc)
  {
    case DEM_FILTERED_NO_MATCHING_DTC:
      lResult = DCM_E_OK; /* end of iteration process */
      break;
    case DEM_FILTERED_OK:
#  if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
      lResult = DCM_E_PENDING;
#  else
      lResult = DCM_E_OK;
#  endif
      break;
    default:
      lResult = DCM_E_CONDITIONSNOTCORRECT;
      break;
  }
  return lResult;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_03_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_03_GetData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_03_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_ReturnGetNextFilteredDTCType    resultGetNextDtc;
  Dem_DTCType                         Dtc;
  uint8                               SnapshotRecord;
  uint16_least                        lAvailLen;

  lAvailLen = *availLenPtr;

  resultGetNextDtc = DEM_FILTERED_OK;
  while (lAvailLen >= 4)
  {
    resultGetNextDtc = Dem_GetNextFilteredRecord(&Dtc, &SnapshotRecord);
    if(DEM_FILTERED_OK != resultGetNextDtc)
    {
      /* Skip decrement */
      break;
    }
    dataPtr[0] = Dcm_GetHiLoByte(Dtc);
    dataPtr[1] = Dcm_GetLoHiByte(Dtc);
    dataPtr[2] = Dcm_GetLoLoByte(Dtc);
    dataPtr[3] = SnapshotRecord;
    /* adjust the response properties */
    dataPtr    = &dataPtr[4];
    Dcm_SubValue(lAvailLen , Dcm_MsgLenType, 4);
  }

  /* Update the length */
  *availLenPtr = (Dcm_MsgLenType)lAvailLen;

  return (Dcm_NegativeResponseCodeType)(((resultGetNextDtc == DEM_FILTERED_NO_MATCHING_DTC)||
                                         (resultGetNextDtc == DEM_FILTERED_OK))?DCM_E_OK:DCM_E_CONDITIONSNOTCORRECT);
}
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_04_CopyFreezeFrames
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \param[in]     recordId                The record id to be read.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_04_CopyFreezeFrames(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr, uint8 recId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType                    errorCode;
  Dem_ReturnGetFreezeFrameDataByDTCType           resultGetFreezeFrameData;
  Dem_ReturnGetFreezeFrameDataIdentifierByDTCType resultGetFreezeFrameIds;
  uint8                                           bufSize;
  uint8                                           numDataIds;
  P2CONST(uint16, AUTOMATIC, DEM_PBCFG)           pDataIds;
  uint16_least                                    lAvailLen;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  errorCode = DCM_E_GENERALREJECT;

  lAvailLen = *availLenPtr;

  if(lAvailLen >= 2)
  {
    /* Optimize usage */
    errorCode = DCM_E_REQUESTOUTOFRANGE;

    /* Get all data Ids to the requested DTC */
    resultGetFreezeFrameIds = Dem_GetFreezeFrameDataIdentifierByDTC(dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.dtcNum,
                                                                    DEM_DTC_KIND_ALL_DTCS,
                                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                    recId,
                                                                    &numDataIds,
                                                                    &pDataIds);
    if(DEM_GET_ID_OK == resultGetFreezeFrameIds)
    {
      if(numDataIds > 0)
      {
        /* Compose single recordNumber block */
        dataPtr[0] = recId;
        dataPtr[1] = numDataIds;

        dataPtr   = &dataPtr[2];
        Dcm_SubValue(lAvailLen  , Dcm_MsgLenType, 2);

        /* Prepare for the maximum value total buffer minus 4Byte */
        bufSize = (uint8)((lAvailLen > 0xFF)?0xFF:lAvailLen);

        resultGetFreezeFrameData = Dem_GetFreezeFrameDataByDTC( dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.dtcNum,
                                                                DEM_DTC_KIND_ALL_DTCS,
                                                                DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                recId,
                                                                DEM_GET_FFDATA_ID_ALL,
                                                                dataPtr,
                                                                &bufSize);
        /* Adjust the response properties */
        /* Dcm_AddValue(dataPtr  , Dcm_MsgType, bufSize); - not used */
        Dcm_SubValue(lAvailLen , Dcm_MsgLenType, bufSize);


        if(resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_OK)
        {
          /* No error except buffer too small shall occur */
          errorCode = DCM_E_GENERALREJECT;
        }
        else
        {
          /* Everything went ok */
          errorCode = DCM_E_OK;
          if(bufSize > 0)
          {
            /* Update the length only if success - otherwise undo (do not change) */
            *availLenPtr = (Dcm_MsgLenType)lAvailLen;
          }
        }
      }
      else
      {
        /* Everything went ok - no data stored  */
        errorCode = DCM_E_OK;
      }
    }/* else: DCM_E_REQUESTOUTOFRANGE */
  }/* else: DCM_E_GENERALREJECT */

  return errorCode;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_04_GetData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_04_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;
  Dcm_MsgLenType dataLen;
  uint8  recId;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  errorCode = DCM_E_OK;
  dataLen = *availLenPtr;

  while(Dcm_19_RecIdIterNext(&recId) == DCM_E_OK) /* PRQA S 3326 */ /* QAC 7.0:  An assignment operator is being used in a boolean expression. */ /* Makes the code more efficient (avoid two calls of the function)! */
  {
    errorCode = Dcm_19_04_CopyFreezeFrames(dataPtr, &dataLen, recId);
    /* Optimize the all record iterations */
    if(errorCode != DCM_E_REQUESTOUTOFRANGE)
    {
      if(errorCode == DCM_E_OK)
      {
        dataPtr = &dataPtr[(*availLenPtr - dataLen)];
        /* Update the length only if success - otherwise undo (do not change) */
        *availLenPtr = dataLen;
      }
      else
      {
        /* unrecoverable error */
        Dcm_19_RecIdIterGoBack();
        break;/* also skip the iterator and record number manipulations */
      }
    }
  }

  if((errorCode == DCM_E_REQUESTOUTOFRANGE)&&
     (dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.allRecNumbers != FALSE))
  {
    errorCode = DCM_E_OK;
  }

  return errorCode;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_04_GetSizeOfFreezeFrames
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[out] totalSize                 Pointer to the reported response data length
 *  \return     NRC
 *  \retval     0  - DEM_GET_SIZEOFFF_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dem_ReturnGetSizeOfFreezeFrameType, DCM_CODE) Dcm_19_04_GetSizeOfFreezeFrames(Dcm_MsgLenPtrType  totalSize)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint16                              SizeOfFreezeFrame;
  Dem_ReturnGetSizeOfFreezeFrameType  returnGetSizeOfFF;
  boolean                             getSizeOk;
  uint8                               recId;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  *totalSize = 0;
  getSizeOk = FALSE;
  returnGetSizeOfFF = DEM_GET_SIZEOFFF_OK;

  Dcm_19_RecIdIterReset();

  while(Dcm_19_RecIdIterNext(&recId) == DCM_E_OK) /* PRQA S 3326 */ /* QAC 7.0:  An assignment operator is being used in a boolean expression. */ /* Makes the code more efficient (avoid two calls of the function)! */
  {
    returnGetSizeOfFF = Dem_GetSizeOfFreezeFrame((Dem_DTCType)dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.dtcNum,
                                                 DEM_DTC_KIND_ALL_DTCS,
                                                 DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                 recId,
                                                 &SizeOfFreezeFrame);

    if (DEM_GET_SIZEOFFF_OK == returnGetSizeOfFF)
    {
      getSizeOk = TRUE;
      if (SizeOfFreezeFrame > 0)
      {
        /* add 2 for RecordNumber and NumberOfIdentifiers */
        Dcm_AddValue(*totalSize, Dcm_MsgLenType, 2 + SizeOfFreezeFrame);
      }
      /* else: valid request but (currently) no data stored */
    }
    else if (DEM_GET_SIZEOFFF_WRONG_RNUM == returnGetSizeOfFF)
    { /* continue loop */
      getSizeOk = TRUE;
    }
    else
    { /* invalid DTC, DTCORIGIN or DTCKIND */
      /* abort loop */
      *totalSize = 0;
      break;
    }
  }

  if ((FALSE != getSizeOk)&&
      (dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.allRecNumbers != FALSE))
  {
    returnGetSizeOfFF = DEM_GET_SIZEOFFF_OK;
  }
  return returnGetSizeOfFF;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_05_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_05_CopyFreezeFrames
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_05_CopyFreezeFrames(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType                    errorCode;
  Dem_ReturnGetFreezeFrameDataByDTCType           resultGetFreezeFrameData;
  Dem_ReturnGetFreezeFrameDataIdentifierByDTCType resultGetFreezeFrameIds;
  uint8                                           bufSize;
  uint8                                           numDataIds;
  P2CONST(uint16, AUTOMATIC, DEM_PBCFG)           pDataIds;
  Dem_ReturnGetDTCOfFreezeFrameRecordType         returnGetDtcOfFFRecord;
  Dem_DTCType                                     Dtc;
  Dem_ReturnGetStatusOfDTCType                    resultGetStatus;
  Dem_DTCStatusMaskType                           dtcStatusMask;
  uint16_least                                    lAvailLen;

  lAvailLen = *availLenPtr;
  /* Optimize usage */
  errorCode = DCM_E_REQUESTOUTOFRANGE;

  /* get the DTC Number for the requested RecordNumber */
  returnGetDtcOfFFRecord = Dem_GetDTCOfFreezeFrameRecord(
    (uint8)0x00,
    DEM_DTC_ORIGIN_PRIMARY_MEMORY,
    DEM_DTC_KIND_ALL_DTCS,
    &Dtc);

  if (DEM_GET_DTCOFFF_OK == returnGetDtcOfFFRecord)
  {
    /* Get all data Ids to the requested DTC, first get the 'LocalDIDs': */
    resultGetFreezeFrameIds = Dem_GetFreezeFrameDataIdentifierByDTC(Dtc,
                                                                    DEM_DTC_KIND_ALL_DTCS,
                                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                    (uint8)0x00,
                                                                    &numDataIds,
                                                                    &pDataIds);
    resultGetStatus = Dem_GetStatusOfDTC(Dtc,
                                         DEM_DTC_KIND_ALL_DTCS,
                                         DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                         &dtcStatusMask);

    if ((DEM_GET_ID_OK == resultGetFreezeFrameIds) && (DEM_STATUS_OK == resultGetStatus))
    {
      if(numDataIds > 0)
      {
        /* there must be enough place */
        Dcm_StateCheckValueRangeFailed((lAvailLen >= 6), DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

        {
          /* Compose single recordNumber block */
          dataPtr[0] = (Dcm_MsgItemType)0x00;
          dataPtr[1] = Dcm_GetHiLoByte(Dtc);
          dataPtr[2] = Dcm_GetLoHiByte(Dtc);
          dataPtr[3] = Dcm_GetLoLoByte(Dtc);
          dataPtr[4] = (Dcm_MsgItemType) dtcStatusMask;
          dataPtr[5] = numDataIds;

          dataPtr  = &dataPtr[6];
          Dcm_SubValue(lAvailLen , Dcm_MsgLenType, 6); /* PRQA S 0291 */ /* QAC 7.0: An integer expression with a value that is apparently negative is being converted to an unsigned type. */ /* If < 6, DCM reaches point of no return! */

          /* Prepare for the maximum value total (remaining) buffer */
          bufSize = (uint8)((lAvailLen > 0xFF)?0xFF:lAvailLen);

          resultGetFreezeFrameData = Dem_GetFreezeFrameDataByDTC( Dtc,
                                                                  DEM_DTC_KIND_ALL_DTCS,
                                                                  DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                  (uint8)0x00,
                                                                  DEM_GET_FFDATA_ID_ALL,
                                                                  dataPtr,
                                                                  &bufSize);
          /* Adjust the response properties */
          /* Dcm_AddValue(dataPtr  , Dcm_MsgType, bufSize); - not used */
          Dcm_SubValue(lAvailLen , Dcm_MsgLenType, bufSize);


          if(resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_OK)
          {
            /* No error except buffer too small can occur -> but buffer size is always calculated to match here -> DET */
            Dcm_CheckAlwaysFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
          }
          else
          {
            /* Everything went ok */
            errorCode = DCM_E_OK;
            if(bufSize > 0)
            {
              /* Update the length only if success - otherwise undo (do not change) */
              *availLenPtr = (Dcm_MsgLenType)lAvailLen;
            }
          }
        }
      }
      else
      {
        /* Everything went ok - nothing stored */
        errorCode = DCM_E_OK;
      }
    }
  }
  return errorCode;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_05_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_05_GetSizeOfFreezeFrames
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \return     freeze frame length
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_19_05_GetSizeOfFreezeFrames(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_ReturnGetDTCOfFreezeFrameRecordType   returnGetDtcOfFFRecord;
  Dem_DTCType                               Dtc;
  Dem_ReturnGetSizeOfFreezeFrameType        returnGetSizeOfFF;
  Dcm_MsgLenType                            totalSize;

  totalSize = 0;

  returnGetDtcOfFFRecord = Dem_GetDTCOfFreezeFrameRecord(
    (uint8)0x00,
    DEM_DTC_ORIGIN_PRIMARY_MEMORY,
    DEM_DTC_KIND_ALL_DTCS,
    &Dtc);

  if (DEM_GET_DTCOFFF_OK == returnGetDtcOfFFRecord)
  {
    returnGetSizeOfFF = Dem_GetSizeOfFreezeFrame(
      Dtc,
      DEM_DTC_KIND_ALL_DTCS,
      DEM_DTC_ORIGIN_PRIMARY_MEMORY,
      (uint8)0x00,
      &totalSize);

    if (DEM_GET_SIZEOFFF_OK == returnGetSizeOfFF)
    {
      if (totalSize > 0)
      {
         /* add 6 for RecordNumber, DTC, DTCStatus and NumberOfIdentifiers */
        Dcm_AddValue(totalSize, Dcm_MsgLenType, 6);
      }
      /* else: valid request but (currently) no data stored */
    }
    else if (DEM_GET_SIZEOFFF_WRONG_RNUM == returnGetSizeOfFF)
    {
      /* recordNumber 0x00 must exist */
      Dcm_CheckAlwaysFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
    }
    else
    {
      /* invalid DTC, DTCORIGIN or DTCKIND */
    }
  }
  /* else: invalid recordNr or DEM is non operable or no FF stored or ... */

  return totalSize;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_06_10_CopyExtDataRecord
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_06_10_CopyExtDataRecord(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr, uint8 recId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType              errorCode;
  Dem_ReturnGetExtendedDataRecordByDTCType  resultGetExtendedDataRecord;
  uint8                                     bufSize;
  uint16_least                              lAvailLen;
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Optimize usage */
  errorCode = DCM_E_GENERALREJECT;
  lAvailLen = *availLenPtr;

  if(lAvailLen > 0)
  {
    /* Compose single recordNumber block */
    dataPtr[0] = recId;
    dataPtr=&dataPtr[1];
    lAvailLen--;


    /* Prepare for the maximum value total buffer */
    bufSize = (uint8)((lAvailLen > 0xFF)?0xFF:lAvailLen);

    resultGetExtendedDataRecord = Dem_GetExtendedDataRecordByDTC(dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.dtcNum,
                                                                 DEM_DTC_KIND_ALL_DTCS,
                                                                 dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.origin,
                                                                 recId,
                                                                 dataPtr,
                                                                 &bufSize);
    /* Update the buffer usage */
    Dcm_SubValue(lAvailLen , Dcm_MsgLenType, bufSize);

    /* Interpret the DEM status */
    switch(resultGetExtendedDataRecord)
    {
      case DEM_RECORD_OK:
        if(bufSize > 0)
        {
          *availLenPtr = (Dcm_MsgLenType)lAvailLen;/* return actualized buffer usage */
        }
        errorCode = DCM_E_OK;
        break;
      case DEM_RECORD_WRONG_DTC:
      case DEM_RECORD_WRONG_DTCORIGIN:
      case DEM_RECORD_WRONG_DTCKIND:
      case DEM_RECORD_WRONG_NUMBER:
        errorCode = DCM_E_REQUESTOUTOFRANGE;
        break;
      case DEM_RECORD_WRONG_BUFFERSIZE:
        errorCode = DCM_E_GENERALREJECT;
        break;
      default:
        errorCode = DCM_E_CONDITIONSNOTCORRECT;
        break;
    }
  }

  return errorCode;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_06_10_GetData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_06_10_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;
  Dcm_MsgLenType dataLen;
  uint8          recId;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  errorCode = DCM_E_OK;
  dataLen = *availLenPtr;

  while(Dcm_19_RecIdIterNext(&recId) == DCM_E_OK) /* PRQA S 3326 */ /* QAC 7.0:  An assignment operator is being used in a boolean expression. */ /* Makes the code more efficient (avoid two calls of the function)! */
  {
    errorCode = Dcm_19_06_10_CopyExtDataRecord(dataPtr, &dataLen, recId);
    /* Optimize the all record iterations */
    if(errorCode != DCM_E_REQUESTOUTOFRANGE)
    {
      if(errorCode == DCM_E_OK)
      {
        dataPtr = &dataPtr[(*availLenPtr - dataLen)];
        /* Update the length only if success - otherwise undo (do not change) */
        *availLenPtr = dataLen;
      }
      else
      {
        /* unrecoverable error */
        Dcm_19_RecIdIterGoBack();
        break;/* also skip the iterator and record number manipulations */
      }
    }
  }

  if((errorCode == DCM_E_REQUESTOUTOFRANGE)&&
     (dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.allRecNumbers != FALSE))
  {
    errorCode = DCM_E_OK;
  }

  return errorCode;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_06_10_GetSizeOfExtDataRecords
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[out] totalSize                 Pointer to the reported response data length
 *  \return     NRC
 *  \retval     0  - DEM_GET_DTCOFFF_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dem_ReturnGetSizeOfExtendedDataRecordByDTCType, DCM_CODE) Dcm_19_06_10_GetSizeOfExtDataRecords(Dcm_MsgLenPtrType totalSize)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_ReturnGetSizeOfExtendedDataRecordByDTCType  resultGetSize;
  uint8                               recId;
  boolean                             getSizeOk;
  uint16                              tempsize;
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  *totalSize  = 0;
  getSizeOk = FALSE;
  resultGetSize = DEM_GET_SIZEOFEDRBYDTC_OK;

  Dcm_19_RecIdIterReset();
  /* Calculate size */
  while(Dcm_19_RecIdIterNext(&recId) == DCM_E_OK) /* PRQA S 3326 */ /* QAC 7.0:  An assignment operator is being used in a boolean expression. */ /* Makes the code more efficient (avoid two calls of the function)! */
  {
    resultGetSize = Dem_GetSizeOfExtendedDataRecordByDTC (dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.dtcNum,
                                                          DEM_DTC_KIND_ALL_DTCS,
                                                          dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.origin,
                                                          recId,
                                                          &tempsize);
    if (DEM_GET_SIZEOFEDRBYDTC_OK == resultGetSize)
    {
      /* tempsize +1 --> add Size of DTCExtendedDataRecordNumber*/
      if (tempsize != 0)
      {
        /* tempsize +1 --> add Size of DTCExtendedDataRecordNumber*/
        Dcm_AddValue(*totalSize, Dcm_MsgLenType, tempsize +1);
      }
      /* mark that at least one (or exactly one rec number has been found)*/
      getSizeOk = TRUE;
    }
  }
  if(FALSE != getSizeOk)
  {
    resultGetSize = DEM_GET_SIZEOFEDRBYDTC_OK;
  }
  return resultGetSize;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_07_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_07_GetData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_07_GetData(Dem_DTCKindType dtcKind)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  return Dcm_19_GetNumDtcByStatusMaskData(DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                          dtcKind,
                                          (Dem_DTCStatusMaskType)dcmDsdMsgContext[lContext].reqData[1],
                                          DEM_FILTER_WITH_SEVERITY_YES,
                                          (Dem_DTCSeverityType)dcmDsdMsgContext[lContext].reqData[0]);
}
# endif /* DCM_READ_DTC_SUBFUNC_07_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_08_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_08_GetData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_08_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint32                            reqDtc;
  Dem_DTCStatusMaskType             dtcStatusMask;
  Dem_DTCSeverityType               dtcSeverity;
  Dem_ReturnGetNextFilteredDTCType  resultGetNextDtc;
  uint16_least                      lAvailLen;
  uint8                             dtcFuncUnit;


  lAvailLen = *availLenPtr;
  resultGetNextDtc  = DEM_FILTERED_OK;
  /* Gather the DTC info */
  while(lAvailLen >= 6)
  {
    resultGetNextDtc = Dem_GetNextFilteredDTCAndSeverity(&reqDtc,
                                                         &dtcStatusMask,
                                                         &dtcSeverity,
                                                         &dtcFuncUnit);
    if((DEM_FILTERED_OK != resultGetNextDtc))
    {
      /* Skip decrement */
      break;
    }
    /* Put onto the response buffer */
    dataPtr[0] = (uint8)dtcSeverity;
    dataPtr[1] = dtcFuncUnit;
    dataPtr[2] = Dcm_GetHiLoByte(reqDtc);
    dataPtr[3] = Dcm_GetLoHiByte(reqDtc);
    dataPtr[4] = Dcm_GetLoLoByte(reqDtc);
    dataPtr[5] = (uint8)dtcStatusMask;

    /* Prepare the next data */
    dataPtr = &dataPtr[6];
    Dcm_SubValue(lAvailLen  , Dcm_MsgLenType, 6);
  }

  /* Update the length */
  *availLenPtr = (Dcm_MsgLenType)lAvailLen;

  return (Dcm_NegativeResponseCodeType)(((resultGetNextDtc == DEM_FILTERED_NO_MATCHING_DTC)||
                                         (resultGetNextDtc == DEM_FILTERED_OK))
                                       ?DCM_E_OK:DCM_E_CONDITIONSNOTCORRECT);
}
# endif

# if (DCM_READ_DTC_SUBFUNC_08_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_08_Process
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_08_Process(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_DTCStatusMaskType             dtcStatusMask;
  Dcm_NegativeResponseCodeType      result;
  Dem_ReturnSetDTCFilterType        resultSetDtcFilter;
  Std_ReturnType                    stdResult;
  uint16                            numDtc;
  Dem_DTCSeverityType               dtcSeverityMask;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* All error cases will return 0x22 */
  result = DCM_E_CONDITIONSNOTCORRECT;
  dtcSeverityMask = (Dem_DTCSeverityType)dcmDsdMsgContext[lContext].reqData[0];
  dtcStatusMask   = (Dem_DTCStatusMaskType)dcmDsdMsgContext[lContext].reqData[1];

  /* Copy the status availability mask (in any case) */
  stdResult = Dem_GetDTCStatusAvailabilityMask(dcmDsdMsgContext[lContext].resData);

  if(E_OK == stdResult)
  {
    /* Form the relevant status bits */
    dtcStatusMask &= dcmDsdMsgContext[lContext].resData[0];
    /* Prepare for DTC response list */
    Dcm_MsgContextMoveRel(0,1);

    resultSetDtcFilter = Dem_SetDTCFilter(dtcStatusMask,
                                          DEM_DTC_KIND_ALL_DTCS,
                                          DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                          DEM_FILTER_WITH_SEVERITY_YES,
                                          dtcSeverityMask,
                                          DEM_FILTER_FOR_FDC_NO);
    if(resultSetDtcFilter == DEM_FILTER_ACCEPTED)
    {
      stdResult = Dem_GetNumberOfFilteredDTC(&numDtc);
      if(E_OK == stdResult)
      {
        /* everything went ok */
        /* MUL 6 */
        numDtc = (uint16)((numDtc<<2) + (numDtc<<1));
        Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, numDtc);

#  if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
        /* Check for enough linear buffer (leave place for the SID + sub-func) */
        if(numDtc <= dcmDsdMsgContext[lContext].resMaxDataLen)
        {
          result = Dcm_19_08_GetData(dcmDsdMsgContext[lContext].resData, &dcmDsdMsgContext[lContext].resMaxDataLen);
        }
        else
        {
          result = DCM_E_RESPONSE_TOO_LONG;
        }
#  else
        /* Starting iterations */
        dcm19_PbDispSubfunc[lContext] = (uint8)(0x08|0x80);
        /* Set a special error code for behavior differentiation */
        result = DCM_E_TRANSFERDATASUSPENDED;
        Dcm_StartPagedProcessing(DCM_PB_CLIENT_19);
#  endif

      }
    }
  }

  return result;
}
# endif /* DCM_READ_DTC_SUBFUNC_08_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_14_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_14_GetData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_14_GetData(Dcm_MsgType dataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint16_least   lAvailLen;
  uint32         reqDtc;
  Dem_ReturnGetNextFilteredDTCType  resultGetNextDtc = DEM_FILTERED_OK;
  sint8          faultDetectionCounter;

  lAvailLen = *availLenPtr;

  /* Gather the DTC info */
  while(lAvailLen >= 4)
  {
    resultGetNextDtc = Dem_GetNextFilteredDTCAndFDC(&reqDtc,
                                                    &faultDetectionCounter);
    if(DEM_FILTERED_OK != resultGetNextDtc)
    {
      /* skip decrement */
      break;
    }
    /* Put onto the response buffer */
    dataPtr[0] = Dcm_GetHiLoByte(reqDtc);
    dataPtr[1] = Dcm_GetLoHiByte(reqDtc);
    dataPtr[2] = Dcm_GetLoLoByte(reqDtc);
    dataPtr[3] = (Dcm_MsgItemType)faultDetectionCounter;

    /* Prepare the next data */
    dataPtr = &dataPtr[4];
    Dcm_SubValue(lAvailLen  , Dcm_MsgLenType, 4);
  }

  /* Update the length  */
  *availLenPtr = (Dcm_MsgLenType)lAvailLen;

  return (Dcm_NegativeResponseCodeType)(((resultGetNextDtc == DEM_FILTERED_NO_MATCHING_DTC)||
                                         (resultGetNextDtc == DEM_FILTERED_OK))?DCM_E_OK:DCM_E_CONDITIONSNOTCORRECT);
}
# endif

# if (DCM_READ_DTC_SUBFUNC_14_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_14_Process
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_14_Process(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType      result;
  Dem_ReturnSetDTCFilterType        resultSetDtcFilter;
  Std_ReturnType                    stdResult;
  uint16                            numDtc;
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();


  /* All error cases will return 0x22 */
  result = DCM_E_CONDITIONSNOTCORRECT;

  /* Prepare for DTC response list */
  resultSetDtcFilter = Dem_SetDTCFilter(0x00, /*all DTCs */
                                        DEM_DTC_KIND_ALL_DTCS,
                                        DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                        DEM_FILTER_WITH_SEVERITY_NO,
                                        DEM_SEVERITY_NO_SEVERITY,
                                        DEM_FILTER_FOR_FDC_YES);
  if(resultSetDtcFilter == DEM_FILTER_ACCEPTED)
  {
    stdResult = Dem_GetNumberOfFilteredDTC(&numDtc);
    if(E_OK == stdResult)
    {
      /* everything went ok */
      /* MUL 4 */
      numDtc <<=2;
      Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, numDtc);

#  if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
      /* Check for enough linear buffer (leave place for the SID + sub-func) */
      if(numDtc <= dcmDsdMsgContext[lContext].resMaxDataLen)
      {
        result = Dcm_19_14_GetData(dcmDsdMsgContext[lContext].resData, &dcmDsdMsgContext[lContext].resMaxDataLen);
      }
      else
      {
        result = DCM_E_RESPONSE_TOO_LONG;
      }
#  else
      /* Starting iterations */
      dcm19_PbDispSubfunc[lContext] = (uint8)(0x14|0x80);
      /* Set a special error code for behavior differentiation */
      result = DCM_E_TRANSFERDATASUSPENDED;
      Dcm_StartPagedProcessing(DCM_PB_CLIENT_19);
#  endif

    }
  }

  return result;
}
# endif /* DCM_READ_DTC_SUBFUNC_14_ENABLED */

# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DcmUpdatePage_19
 **********************************************************************************************************************/
/*! \brief      A paged buffer call-back.
 *  \param[out] dataPtr                 Pointer to the response data
 *  \param[in]  dataLen                 Maximum size of the available buffer
 *  \context    Function could be called from interrupt or task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_DcmUpdatePage_19(Dcm_MsgType dataPtr, Dcm_MsgLenType dataLen)
/*--------------------------------------------------------------------------------------------------------------------*/
{
#  if (DCM_19_READ_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_03_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_08_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_14_ENABLED == STD_ON) || \
      (DCM_READ_DTC_SUBFUNC_42_ENABLED == STD_ON)

  Dcm_MsgLenType  pbIter = dataLen;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

#   if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  boolean isLocked;
  isLocked = Dcm_DemMgrIsDemClientLocked(DCM_DEMMGR_OP_ANY_19, Dcm_DemMgrConvUdsContextId2Clientid(lContext));
  /* Still locked by owner ? */
  if(FALSE != isLocked)
#   endif
  {
    boolean isFirstTime = FALSE;

#   if (DCM_19_READ_BY_STATUS_MASK_ENABLED == STD_ON)
    if((dcm19_PbDispSubfunc[lContext] & 0x7F) == 0x02)
    {
      /* Gather the DTC info */
      dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.resData = dataPtr;
      dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.availLen = pbIter;
      Dcm_RegisterRepeaterProxy(Dcm_19_02_0A_0F_13_15_RepeaterProxyGetData);
      return;/* let the repeater prody finish the page processing */
    }
#   endif

    if((dcm19_PbDispSubfunc[lContext] & 0x80) != 0)
    {
      /* Clear the ctrl flag */
      dcm19_PbDispSubfunc[lContext] &= 0x7F;
      isFirstTime = TRUE;
    }

    switch (dcm19_PbDispSubfunc[lContext])
    {
#   if (DCM_READ_DTC_SUBFUNC_03_ENABLED == STD_ON)
    /*----------------------*/
    case 0x03:
    /*----------------------*/
      /* For the first iteration consider the sub-function is already copied */
      if(isFirstTime != FALSE)
      {
        /* Sub-func is already copied - skip */
        Dcm_SubValue(pbIter  , Dcm_MsgLenType, 1);
        dataPtr=&dataPtr[1];
      }
      /* Fill the buffer */
      /* abort the transfer in error case by just copying no data */
      (void) Dcm_19_03_GetData(dataPtr, &pbIter);
      break;
#   endif
#   if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON)
    /*----------------------*/
    case 0x04:
    /*----------------------*/
      /* For the first iteration consider the sub-function, DTC and the Status are already copied */
      if(isFirstTime != FALSE)
      {
        /* Sub-func/DTC/Status is already copied - skip */
        Dcm_SubValue(pbIter  , Dcm_MsgLenType, 5);
        dataPtr = &dataPtr[5];
      }

      (void)Dcm_19_04_GetData(dataPtr, &pbIter);
      break;
#   endif
#   if (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
       (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
    /*----------------------*/
    case 0x06:
    /*----------------------*/
      /* For the first iteration consider the sub-function and the SAM are already copied */
      if(isFirstTime != FALSE)
      {
        /* Sub-func + DTC + SAM are already copied - skip */
        Dcm_SubValue(pbIter  , Dcm_MsgLenType, 5);
        dataPtr = &dataPtr[5];
      }

      /* Gather the DTC info */
      (void)Dcm_19_06_10_GetData(dataPtr, &pbIter);
      break;
#   endif
#   if (DCM_READ_DTC_SUBFUNC_08_ENABLED == STD_ON)
    /*----------------------*/
    case 0x08:
    /*----------------------*/
      /* For the first iteration consider the sub-function and the SAM are already copied */
      if(isFirstTime != FALSE)
      {
        /* Sub-func + SAM are already copied - skip */
        Dcm_SubValue(pbIter  , Dcm_MsgLenType, 2);
        dataPtr = &dataPtr[2];
      }

      (void)Dcm_19_08_GetData(dataPtr, &pbIter);
      break;
#   endif
#   if (DCM_READ_DTC_SUBFUNC_14_ENABLED == STD_ON)
    /*----------------------*/
    case 0x14:
    /*----------------------*/
      /* For the first iteration consider the sub-function is already copied */
      if(isFirstTime != FALSE)
      {
        /* Sub-func is already copied - skip */
        Dcm_SubValue(pbIter  , Dcm_MsgLenType, 1);
        dataPtr=&dataPtr[1];
      }

      (void)Dcm_19_14_GetData(dataPtr, &pbIter);
      break;
#   endif
#   if (DCM_READ_DTC_SUBFUNC_42_ENABLED == STD_ON)
    /*----------------------*/
    case 0x42:
    /*----------------------*/
      /* For the first iteration consider the sub-function is already copied */
      if(isFirstTime != FALSE)
      {
        /* Sub-func, FGID, STAM, SVAM, FID  are already copied - skip */
        Dcm_SubValue(pbIter  , Dcm_MsgLenType, 5);
        dataPtr=&dataPtr[5];
      }
      /* Fill the buffer */
      /* abort the transfer in error case by just copying no data */
      (void) Dcm_19_42_GetData(dataPtr, &pbIter);
      break;
#   endif
    /*----------------------*/
    default:
    /*----------------------*/
      break;
    }
  }
  /* Paged buffer processing done */
  Dcm_ProcessPage((uint16)(dataLen - pbIter));

  /* reenable the DEM after the last page was written */
  if((dcmPBStateMachine[lContext].remainingData == 0) &&
     (FALSE != dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.needsRecordUpdateDisabling))
  {
    Dcm_DemMgrRequestEnableDtcUpdate(Dcm_DemMgrConvUdsContextId2Clientid(lContext));
  }

#  else
  /* Avoid warnings */
  DCM_IGNORE_UNREF_PARAM(dataPtr); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  DCM_IGNORE_UNREF_PARAM(dataLen); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
#  endif
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif
#endif /* (DCM_SERVICE_19_ENABLED == STD_ON) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_22_OemInit
 **********************************************************************************************************************/
/*! \brief      Service 0x22 OEM initializiation
 *  \context    Function is called at module init time.
 **********************************************************************************************************************/
 /*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_22_OemInit(DCM_UDS_CONTEXT_PARAM_DEF_ONLY)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_UDS_CONTEXT_PARAM_IGNORE /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  /* nothing to init */
}
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_22_FindDid
 **********************************************************************************************************************/
/*! \brief      Check if a DID is for service 0x22 relevant
 *  \param[in]  did          The DID to be searched for
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_22_FindDid(uint16 did)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return Dcm_DidMgrFindDid(did, dcm22_DidHandleTable, dcm22_DidCfgVariants);
}

/***********************************************************************************************************************
 *  Dcm_22_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x22 polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_22_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DidHandleType didHandle;
  Std_ReturnType    stdReturn;
  uint16_least      lDid;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  do
  {
    /* Cache the reference */
    didHandle = dcm22_DidList[lContext][dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid];

    switch(dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress)
    {
      /*-----------------------------------------*/
        case DCM_22_PROCESS_INIT_DID:
      /*-----------------------------------------*/
        /* Put the DID inside */
        lDid = dcmDidLookUpTable[dcm22_DidHandleTable[didHandle+1]];
        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.ResData[0] = Dcm_GetHiByte(lDid);
        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.ResData[1] = Dcm_GetLoByte(lDid);
        Dcm_AddValue(dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.ResData , Dcm_MsgType, 2);/* PRQA S 0488 */ /* QAC 7.0: Performing pointer arithmetic. */ /* Better readability */
        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress = DCM_22_PROCESS_READ_DID;

      /*-----------------------------------------*/
        case DCM_22_PROCESS_READ_DID:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */
      /*-----------------------------------------*/
        stdReturn = Dcm_DidMgrReadDid(didHandle, dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.ResData, Dcm_22_UdsContextId2Clientid(lContext), &dcmDsdErrorRegister[lContext]);
# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
        if(DCM_E_PAGED_DATA_OK == stdReturn)
        {
          /* delegate job to the PagedBuffer processor */
          dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.IsFirstTime = TRUE;
          Dcm_StartPagedProcessing(DCM_PB_CLIENT_22);
          return DCM_E_OK;
        }
# endif
        if(DCM_E_PENDING == stdReturn)
        {
          /* try again */
          return DCM_E_PENDING;
        }

        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
      /*-----------------------------------------*/
      default:
      /*-----------------------------------------*/
        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
    }

    Dcm_AddValue(dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.ResData, /* PRQA S 0488 */ /* QAC 7.0: Performing pointer arithmetic. */ /* Better readability */
                 Dcm_MsgType,
                 dcm22_DidResLen[lContext][dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid]);

    /* Process next DID */
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid++;
    /* Execute the next DID */
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress = DCM_22_PROCESS_INIT_DID;
  }
  while( (dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid <
          dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.DidCount)
       &&(DCM_E_OK == dcmDsdErrorRegister[lContext]) );


  /* Go on with the response */
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_22_RepeaterProxyDispatcher
 **********************************************************************************************************************/
/*! \brief      Service 0x22 polling dispatcher
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_22_RepeaterProxyDispatcher(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType     stdReturn;
  Dcm_RteDataLenType didLength;
# if (DCM_SERVICE_2C_ENABLED == STD_ON)
  boolean            dynDidDefined;
# endif

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Req data len contains still the count of the DIDs */
  /* Process all DIDs until an error has been detected */
  while((dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid != 0)&&
        (dcmDsdErrorRegister[lContext] == DCM_E_OK))
  {
    switch(dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress)
    {
    /*-----------------------------------------*/
      case DCM_22_DISPATCH_FIND_DID:/* fall through */
    /*-----------------------------------------*/
        /* Find DID (use main pool since each read-able DID is accessible by 0x22)*/
        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle = (Dcm_MemDidHandleType)Dcm_22_FindDid(Dcm_Make16Bit(dcmDsdMsgContext[lContext].reqData[0],dcmDsdMsgContext[lContext].reqData[1]));
# if (DCM_SERVICE_2C_ENABLED == STD_ON)
        /* Check DynDID availability */
        dynDidDefined = Dcm_2C_IsDidAvailable(Dcm_Make16Bit(dcmDsdMsgContext[lContext].reqData[0],
                                                            dcmDsdMsgContext[lContext].reqData[1]));
        if(dynDidDefined == FALSE)
        {
          /* DynDid is not defined */
          dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle = DCM_NUM_DIDS;
        }
# endif

        dcmDsdMsgContext[lContext].reqData =&dcmDsdMsgContext[lContext].reqData[2];
        /* If found */
        if(dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle >= DCM_NUM_DIDS)
        {
          dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid--;
          break;/* PRQA S 3333 */ /* Check next DID */  /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
        }

        /* Perform DID specific state checks */
        {
          boolean doSkipDid = Dcm_DidMgrAnalyseDid(Dcm_22_UdsContextId2Clientid(lContext), dcm22_DidStateInfoTable[dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle]);
          if(doSkipDid != FALSE)
          {
            dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid--;
            break;/* PRQA S 3333 */ /* Check next DID */  /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
          }
          /* From now on prepare for next DID */
          dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.DidCount++;

          if(DCM_E_OK != dcmDsdErrorRegister[lContext])
          {
            break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
          }
        }
        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress = DCM_22_DISPATCH_GET_LEN;

    /*-----------------------------------------*/
      case DCM_22_DISPATCH_GET_LEN:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* fall through in OK case only */
    /*-----------------------------------------*/
        didLength = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle].Length;
        if(0 == didLength)
        {
          stdReturn = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle].GetDataLen(&didLength);

          switch(stdReturn)
          {
          /*------------------*/
            case DCM_E_OK:
          /*------------------*/
              break;
          /*------------------*/
            case DCM_E_PENDING:
          /*------------------*/
              /* try again */
              return DCM_E_PENDING;
          /*------------------*/
            default:
          /*------------------*/
              Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
              dcmDsdErrorRegister[lContext] = DCM_E_GENERALREJECT;
              break;
          }
        }
        if(DCM_E_OK != dcmDsdErrorRegister[lContext])
        {
          break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
        }

        dcm22_DidList[lContext][dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.DidCount-1] = (Dcm_MemDidHandleType)dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle;
        dcm22_DidResLen[lContext][dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.DidCount-1] = didLength;
        /* Add the current DID response dataLen to the total response */
        Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen , Dcm_MsgLenType, (Dcm_MsgLenType)(didLength + 2));

        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress = DCM_22_DISPATCH_CHECK_DID;

    /*-----------------------------------------*/
      case DCM_22_DISPATCH_CHECK_DID:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */
    /*-----------------------------------------*/
        /* Check RTE conditions */
        stdReturn = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDidHandle].CheckCondition(&dcmDsdErrorRegister[lContext]);

        switch(stdReturn)
        {
# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
          /*------------------*/
          case DCM_E_PAGED_DATA_OK:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* Fall through */
          /*------------------*/
            /* Mark avalability of paged DID */
            dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.HasPagedDid = TRUE;
# endif
        /*------------------*/
          case DCM_E_OK: /* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* Fall through */
        /*------------------*/
            break;
        /*------------------*/
          case DCM_E_PENDING:
        /*------------------*/
            /* try again */
            return DCM_E_PENDING;
        /*------------------*/
          default:
        /*------------------*/
            Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
            dcmDsdErrorRegister[lContext] = DCM_E_GENERALREJECT;
            break;
        }

        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid--;
        dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress = DCM_22_DISPATCH_FIND_DID;
        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
    /*-----------------------------------------*/
      default:
    /*-----------------------------------------*/
        Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
    }
  }/* LOOP */

  /* If not found - no more elements */
  if(dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.DidCount == 0)
  {
    /* May be no DID found - negative response */
    dcmDsdErrorRegister[lContext] = DCM_E_REQUESTOUTOFRANGE;
  }

  /* Check bus's buffer overflow (consider the SID byte in the resDataLen */
  if((dcmDsdMsgContext[lContext].resDataLen > (Dcm_MsgLenType)(dcmDsdMsgContext[lContext].resMaxDataLen + 1))
# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
   &&(dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.HasPagedDid == FALSE)
# endif
     )
  {
    /* Accept only bus specific length */
    /* Important : use the function call to avoid overwriting of the NRC if previously set */
    Dcm_SetNegResponse(DCM_E_RESPONSE_TOO_LONG);
  }

  /* Check if any error was found */
  if(DCM_E_OK == dcmDsdErrorRegister[lContext])
  {
    /* Process the first DID 
     * stack utilization optimization */
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress = DCM_22_PROCESS_INIT_DID;
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.ResData = dcmDsdMsgContext[lContext].resData;
    Dcm_RegisterRepeaterProxy(Dcm_22_RepeaterProxyProcess);
  }
  else
  {
    Dcm_ProcessingDone();
  }

  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_27_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_27_OemInit
 **********************************************************************************************************************/
/*! \brief      Service 0x27 OEM initialization
 *  \context    Function must be called within disabled interrupt context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_27_OemInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* nothing to init */
}

/***********************************************************************************************************************
 *  Dcm_27_StateTask
 **********************************************************************************************************************/
/*! \brief      Service 0x27 processing task
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_27_StateTask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* nothing to do */
}

/***********************************************************************************************************************
 *  Dcm_27_RepeaterProxyGetSeed
 **********************************************************************************************************************/
/*! \brief      Service 0x27 <seed> polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_27_RepeaterProxyGetSeed(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  /* The record options are in the resDataBuffer already!!! */
  stdReturn = dcm27_ServiceInfoTable[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].GetSeedCallBack((Dcm_RteDataPtrType)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData, (Dcm_RteDataPtrType)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]); /* PRQA S 0310 */ /* PRQA S 0308 */
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      /* Allow "send key" */
      break;
  /*------------------*/
    case DCM_E_NOT_OK:
  /*------------------*/
      /* error code may be already set */
      Dcm_SetNegResponse(DCM_E_CONDITIONSNOTCORRECT);
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_GENERALREJECT;
      break;
  }
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_27_RepeaterProxySendKey
 **********************************************************************************************************************/
/*! \brief      Service 0x27 <key> polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_27_RepeaterProxySendKey(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  /* The record options are in the resDataBuffer already!!! */
  stdReturn = dcm27_ServiceInfoTable[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].SendKeyCallBack((Dcm_RteDataPtrType)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData); /* PRQA S 0310 */ /* PRQA S 0308 */

  /* Important: no sync usage any more! */
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      break;
  /*------------------*/
    case DCM_E_NOT_OK:
  /*------------------*/
      /* error code may be already set */
      Dcm_SetNegResponse(DCM_E_CONDITIONSNOTCORRECT);
      break;
  /*------------------*/
    case DCM_E_COMPARE_KEY_FAILED:
  /*------------------*/
# if (DCM_27_ATTEMPT_DELAY_ENABLED == STD_ON)
      dcm27_SecLevelStateEngine[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].AttemptCounter++;
      /* Insert a time delay? */ /* check if attempt counter is supported */
      if((dcm27_ServiceInfoTable[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].NumMaxAttDelay != 0) &&
         (dcm27_SecLevelStateEngine[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].AttemptCounter >=
          dcm27_ServiceInfoTable[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].NumMaxAttDelay))
      {
#  if (DCM_27_TOTAL_ATTEMPTS_ENABLED == STD_ON)
        dcm27_SecLevelStateEngine[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].TotalAttemptCounter++;
#  endif
        dcm27_SecLevelStateEngine[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].AttemptCounter = 0;
        Dcm_TmrMgrStartTimer(DCM_TIMER_ID_SA,
                             dcm27_ServiceInfoTable[dcmSeedKeyProxyParam.SecLevIdxOnGotSeed].DelayInvKey);

        dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_EXCEEDNUMBEROFATTEMPTS;
      }
      else
# endif
      {
        dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INVALIDKEY;
      }
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_GENERALREJECT;
      break;
  }

  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
#if (DCM_SERVICE_28_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_28_InterpretParams
 **********************************************************************************************************************/
/*! \brief      Service 0x28 interpret extracted parameters
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_28_InterpretParams(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Interpret UDS parameter -> Vmm */
  if(0x00u == dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId)
  {
    /* All sub-networks */
    dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId = VMM_ALL_CHANNEL;
  }
  else
  {
    /* The sub-network on which the request is received */
    dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId = dcmDslPduConnectionInfoTable[dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dslHandle].commChannel;
  }
}

# if (DCM_28_ANY_COM_PARAM_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_28_HasValidParams
 **********************************************************************************************************************/
/*! \brief      Service 0x28 extract communication parameter type
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_28_HasValidParams(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* No sub-network specific number is supported (only ALL and CURR_CHANNEL)*/
  return (boolean)( ( (dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId == 0x00u)
                   || (dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId == 0x0Fu) ) /* Currently no channel information available!*/
                &&  ( (dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.MsgType <= 0x03u)
                   && (dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.MsgType != 0x00u) ) );
}
# endif

/***********************************************************************************************************************
 *  Dcm_28_EnableCommunication
 **********************************************************************************************************************/
/*! \brief      Service 0x28 enable communication through internal code.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_28_EnableCommunication(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  stdReturn = Vmm_Dcm_CommunicationControl(VMM_ALL_CHANNEL,
                                           VMM_MSG_TYPE_ALL,
                                           TRUE,
                                           TRUE);
  Dcm_StateCheckValueRangeFailed((stdReturn == E_OK), DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  DCM_IGNORE_UNREF_PARAM(stdReturn); /* PRQA S 3112 */ /* Ignore warnings in non-debug mode */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
}

/***********************************************************************************************************************
 *  Dcm_28_PostHandling
 **********************************************************************************************************************/
/*! \brief      Service 0x28 post processing
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_28_PostHandling(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  stdReturn = Vmm_Dcm_CommunicationControl(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId,
                                           dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.MsgType,
                                           dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.RxState,
                                           dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.TxState);
  Dcm_StateCheckValueRangeFailed((stdReturn == E_OK), DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  DCM_IGNORE_UNREF_PARAM(stdReturn); /* PRQA S 3112 */ /* Ignore warnings in non-debug mode */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
}
#endif /* (DCM_SERVICE_28_ENABLED == STD_ON) */
#if (DCM_SERVICE_28_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_28_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x28 polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_28_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  Dcm_NegativeResponseCodeType  errorCode = DCM_E_OK;

  /* The record options are in the resDataBuffer already!!! */
  stdReturn = dcm28_ComControlPermFunc(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId,
                                       dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.MsgType,
                                       dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.RxState,
                                       dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.TxState);

  /* Important: no sync usage any more! */
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      /* Send the prepared pos response */
      break;
  /*------------------*/
    case DCM_E_COM_CTRL_NOT_ACCEPTED:
  /*------------------*/
      errorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      errorCode = DCM_E_GENERALREJECT;
      break;
  }

  Dcm_SetNegResponse(errorCode);
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_28_ENABLED == STD_ON) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2A_FindDid
 **********************************************************************************************************************/
/*! \brief      Check if a DID is for service 0x2A relevant
 *  \param[in]  did          The DID to be searched for
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_2A_FindDid(uint16 did)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return Dcm_DidMgrFindDid(did, dcm2A_DidHandleTable, dcm2A_DidCfgVariants);
}

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerStopDid
 **********************************************************************************************************************/
/*! \brief      Stops a specific DID
 *  \param[in]  didHandle2A         a periodic DID handle to be stopped
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopDid(Dcm_DidHandleType didHandle2A)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Avoid array out of boundary access */
  if(didHandle2A < DCM_2A_NUM_DIDS)
  {
    uint8_least didPos = Dcm_2A_SchedulerGetItemPos(dcm2A_2ATo22Handle[didHandle2A]);
    if(didPos < DCM_2A_SCHEDULER_SIZE)
    {
      Dcm_2A_SchedulerStopItem(didPos);
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerGetFreeItemPos
 **********************************************************************************************************************/
/*! \brief      Finds the first free position in the scheduler
 *  \return     The first free position
 *  \retval     0 - (DCM_2A_SCHEDULER_SIZE - 1) - success
 *  \retval     DCM_2A_SCHEDULER_SIZE           - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(uint8_least, DCM_CODE) Dcm_2A_SchedulerGetFreeItemPos(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least iter = DCM_2A_SCHEDULER_SIZE;
  while(iter != 0)
  {
    iter--;
    if(dcm2A_SchedulerTable[iter].Rate == DCM_2A_RATE_TYPE_STOPPED)
    {
      return iter;
    }
  }

  return DCM_2A_SCHEDULER_SIZE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerGetAvailItemPos
 **********************************************************************************************************************/
/*! \brief      Finds the first free position in the scheduler but considers if the DID is already available inside
 *  \param[in]  didHandle         a 0x22 service DID handle to be stopped
 *  \return     The first free position
 *  \retval     0 - (DCM_2A_SCHEDULER_SIZE - 1) - success (DID already inside or free place found)
 *  \retval     DCM_2A_SCHEDULER_SIZE           - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(uint8_least, DCM_CODE) Dcm_2A_SchedulerGetAvailItemPos(Dcm_DidHandleType didHandle22)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least itemPos = Dcm_2A_SchedulerGetItemPos(didHandle22);
  if(itemPos == DCM_2A_SCHEDULER_SIZE)
  {
    itemPos = Dcm_2A_SchedulerGetFreeItemPos();
  }
  return itemPos;
}

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerIsAlreadyAddedDid
 **********************************************************************************************************************/
/*! \brief      Checks if the DID is already added within the current scheduler update operation
 *  \param[in]  didHandle         a service 0x22 DID handle to be stopped
 *  \return     Result of operation
 *  \retval     TRUE      - DID already added during this update request
 *  \retval     FALSE     - DID not during yet this update request
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_2A_SchedulerIsAlreadyAddedDid(Dcm_DidHandleType didHandle22)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  boolean result = FALSE;
  uint8_least itemPos = Dcm_2A_SchedulerGetItemPos(didHandle22);
  if(itemPos < DCM_2A_SCHEDULER_SIZE)
  {
    /* Make */
    result = (boolean)((dcm2A_SchedulerTable[itemPos].Rate & DCM_2A_RATE_TYPE_RESERVED)!= 0);
  }
  return result;
}

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerRemoveAddedDids
 **********************************************************************************************************************/
/*! \brief      Undoes all updates done during current request execution
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerRemoveAddedDids(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least iter = DCM_2A_SCHEDULER_SIZE;
  while(iter != 0)
  {
    iter--;
    /* Stop only reserved but not already scheduled dids */
    dcm2A_SchedulerTable[iter].Rate &= (Dcm_2A_MemRateType)(~DCM_2A_RATE_TYPE_RESERVED); /* PRQA S 0277 */ /* Needed for consistent clear bit operation */
  }
}

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerEnableAddedDids
 **********************************************************************************************************************/
/*! \brief      All prepared DIDs for (re-)schedulling will be enabled.
 *  \param[in]  rate         the new transmission rate to be used
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerEnableAddedDids(Dcm_2A_RateType rate)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least iter = DCM_2A_SCHEDULER_SIZE;
  while(iter != 0)
  {
    iter--;
    /* Update all reserved entries (also those that were already scheduled) */
    if((dcm2A_SchedulerTable[iter].Rate & DCM_2A_RATE_TYPE_RESERVED) != 0)
    {
      if((dcm2A_SchedulerTable[iter].Rate & DCM_2A_RATE_TYPE_STOPPED) != 0)
      {
        dcm2A_ProcessorState.NumItems++;
      }
      dcm2A_SchedulerTable[iter].Rate = (Dcm_2A_MemRateType)rate;
      /* Enforce immediate timeout */
      Dcm_EvMgrSetEvent(DCM_TASK_ID_SCHEDULER, Dcm_2A_MakeEventOfTimerIdx(iter));
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerTask
 **********************************************************************************************************************/
/*! \brief      Processing task for periodic reading and transmission
 *  \param[in]  ev         current 0x2A state task event content (timer timeouts)
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_SchedulerTask(Dcm_EventType ev)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EventType     scanner;
  Std_ReturnType    stdReturn;
  Dcm_MsgType       lResData;
  Dcm_DidHandleType didHandle22;
  uint8_least itemIter = DCM_2A_SCHEDULER_SIZE;
  uint8_least timerIter = dcm2A_ProcessorState.NextItem;
  boolean           doSendData;

  /* Assure only one scheduler pass to give control to the other tasks */
  while((ev != 0)&&(itemIter != 0))
  {
    itemIter--;
    scanner = Dcm_2A_MakeEventOfTimerIdx(timerIter);

    if((scanner & ev) != 0)
    {
      doSendData = TRUE;
      /* Check for stop event (on wait still do the processing till the end!!!) */
      if((dcm2A_SchedulerTable[timerIter].Rate & DCM_2A_RATE_TYPE_STOPPED) == 0)
      {
        if(DCM_PERIODIC_HANDLE_INVALID == dcm2A_ProcessorState.TxHandle)
        {
          dcm2A_ProcessorState.TxHandle = (Dcm_MemPeriodicHandleType)Dcm_PruAllocateResource();
          /* If no resource - skip this task */
          if(DCM_PERIODIC_HANDLE_INVALID == dcm2A_ProcessorState.TxHandle)
          {
            /* try again later */
            break;
          }
        }

        lResData = Dcm_PruGetDataPtr(dcm2A_ProcessorState.TxHandle);

        didHandle22 = dcm2A_SchedulerTable[timerIter].DidHandle;
        /* Get the DID itself */
        lResData[0] = Dcm_GetLoByte(dcmDidLookUpTable[dcm22_DidHandleTable[didHandle22+1]]);

        /* Mark currently processing item (for stop and update)*/
        dcm2A_ProcessorState.ProcessingItem = (uint8)timerIter;
        stdReturn = Dcm_DidMgrReadDid(didHandle22, &lResData[1], DCM_DIDMGR_CLIENT_ID_2A, NULL_PTR);
        if(DCM_E_PENDING == stdReturn)
        {
          /* try again later */
          break; /* PRQA S 0771 */ /* QAC 7.0:  More than one break statement is being used to terminate an iteration statement. */ /* Required in order to avoid additional local variables and 'if' tests */
        }
        else
        {
          if(DCM_E_OK != stdReturn)
          {
            doSendData = FALSE;
          }
        }
      }

      /* UnMark currently processing item (for stop and update)*/
      dcm2A_ProcessorState.ProcessingItem = DCM_2A_SCHEDULER_SIZE;
      /* Mark as processed */
      Dcm_EvMgrClearEvent(DCM_TASK_ID_SCHEDULER, scanner);
      /* Clear in the copy too  */
      ev &= (Dcm_EventType)(~scanner);

      if((dcm2A_SchedulerTable[timerIter].Rate & (Dcm_2A_MemRateType)(DCM_2A_RATE_TYPE_WAIT_STOP | DCM_2A_RATE_TYPE_STOPPED)) == 0)
      {
        if(doSendData != FALSE)
        {
          /* Transmit data
           *-------------------- */
          Dcm_PruTransmit(dcm2A_ProcessorState.TxHandle, (uint8)(dcm2A_SchedulerTable[timerIter].Length + 1));
        }
        else
        {
          /* Release resource
           *--------------------*/
          Dcm_PruReleaseResource(dcm2A_ProcessorState.TxHandle);
        }

        /* Start current DID's timer again */
        Dcm_TmrMgrStartTimer((Dcm_TimerIdType)(DCM_TIMER_ID_SCHEDULER_0 + timerIter), dcm2A_TimingPeriods[(dcm2A_SchedulerTable[timerIter].Rate & DCM_2A_RATE_TYPE_MASK)]);
      }
      else
      {
        dcm2A_ProcessorState.NumItems--;
        if(dcm2A_ProcessorState.NumItems == 0)
        {
          /* Release the ownership */
          Dcm_PruReleaseConnection();
        }

        dcm2A_SchedulerTable[timerIter].Rate |= DCM_2A_RATE_TYPE_STOPPED;

        if(DCM_PERIODIC_HANDLE_INVALID != dcm2A_ProcessorState.TxHandle)
        {
          /* Release resource
           *--------------------*/
          Dcm_PruReleaseResource(dcm2A_ProcessorState.TxHandle);
        }
      }
      /* Prepare for new data resource */
      dcm2A_ProcessorState.TxHandle = DCM_PERIODIC_HANDLE_INVALID;

    }
    /* wrap around */
    if(timerIter == 0)
    {
      timerIter = DCM_2A_SCHEDULER_SIZE;
    }
    timerIter--;
  }
  /* Store next item position */
  dcm2A_ProcessorState.NextItem = (uint8)timerIter;
}

/***********************************************************************************************************************
 *  Dcm_2A_StateTask
 **********************************************************************************************************************/
/*! \brief      Service 0x2A processing task
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_StateTask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EventType ev;

  ev = Dcm_EvMgrGetEvent(DCM_TASK_ID_SCHEDULER);

  if(ev != 0)
  {
    /* Do not clear any of the timer events!!! 
     * This API could be called in the future: 
     *      Dcm_EvMgrClearEvent(DCM_TASK_ID_SCHEDULER, (Dcm_EventType)(ev & DCM_EVENT_TIMER_ANY));
     * but for now not required. */
    if((ev & DCM_EVENT_TIMER_ANY) != 0)
    {
      Dcm_2A_SchedulerTask((Dcm_EventType)(ev & DCM_EVENT_TIMER_ANY));
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_2A_FindSubFunction
 **********************************************************************************************************************/
/*! \brief      Service 0x2A sub-function look-up
 *  \param[in]  subFuncId           searched sub-function
 *  \return     Sub-function reference handle
 *  \retval     0 - 3                       -  success
 *  \retval     DCM_2A_RATE_TYPE_INVALID    -  failed
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_2A_RateType, DCM_CODE) Dcm_2A_FindSubFunction(uint8 subFuncId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_2A_RateType lResult = DCM_2A_RATE_TYPE_INVALID;
  /* Valid sub-function at all (top limit)? (0x1, 0x2, 0x3 and 0x4 only)*/
  if(subFuncId <= 0x04u)
  {
    /* Is supported at all? */
    subFuncId = dcm2A_SubFuncToCtrlTypeMap[subFuncId];
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
    if(subFuncId < 0x04u)
# endif
    {
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
      if((dcm2A_SubFuncCfgVariant[subFuncId] & dcmStateMachine.CfgVariantMask) != 0)
# endif
      {
        lResult = subFuncId;
      }
    }
  }
  return lResult;
}

/***********************************************************************************************************************
 *  Dcm_2A_RepeaterProxyDispatcher
 **********************************************************************************************************************/
/*! \brief      Service 0x2A polling dispatcher
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2A_RepeaterProxyDispatcher(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType    stdReturn;

  /* Req data len contains still the count of the DIDs */
  /* Process all DIDs until an error has been detected */
  while((dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.CurDid != 0)&&
        (dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] == DCM_E_OK))
  {
    switch(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Progress)
    {
    /*-----------------------------------------*/
      case DCM_2A_DISPATCH_FIND_DID:/* fall through */
    /*-----------------------------------------*/
        {
# if (DCM_SERVICE_2C_ENABLED == STD_ON)
          boolean dynDidDefined;
# endif
          Dcm_DidHandleType didHandle2A;
          /* Find DID (use main pool since each read-able DID is accessible by 0x2A)*/
          didHandle2A = (Dcm_MemDidHandleType)Dcm_2A_FindDid(Dcm_Make16Bit(0xF2, dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0]));
# if (DCM_SERVICE_2C_ENABLED == STD_ON)
          /* Check DynDID availability */
          dynDidDefined = Dcm_2C_IsDidAvailable(Dcm_Make16Bit(0xF2,dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0]));
          if(dynDidDefined == FALSE)
          {
            /* DynDid is not defined */
            didHandle2A = DCM_NUM_DIDS;
          }
# endif
          dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData=&dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1];/* ptr++ */

          /* Check whether found */
          if(didHandle2A < DCM_NUM_DIDS)
          {
            boolean doSkipDid;
            /* Perform DID specific state checks */
            doSkipDid = Dcm_DidMgrAnalyseDid(DCM_DIDMGR_CLIENT_ID_2A, dcm2A_DidStateInfoTable[didHandle2A]);
            if( (FALSE == doSkipDid)&&
                (DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]) )
            {
              /* Check for duplicate (only 0x22 handles are stored!) */
              boolean isDuplicate;
              isDuplicate = Dcm_2A_SchedulerIsAlreadyAddedDid(dcm2A_2ATo22Handle[didHandle2A]);

              if(FALSE == isDuplicate)
              {
                /* DID is supported - register it */
                dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.DidCount++;
                dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Progress = DCM_2A_DISPATCH_GET_LEN;
                /* Store only the DID handle of service 0x22 */
                dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Cur22DidHandle = dcm2A_2ATo22Handle[didHandle2A];
              }
            }
          }

          /* If DID not relevant (still FIND_DID state active) - skip next steps */
          if(DCM_2A_DISPATCH_FIND_DID == dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Progress)
          {
            /* exit validation DID lookup */
            dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.CurDid--;
            break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
          }
        }
    /*-----------------------------------------*/
      case DCM_2A_DISPATCH_GET_LEN:        /* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* fall through in OK case only */
    /*-----------------------------------------*/
        {
          Dcm_MsgLenType didLength;
          didLength = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Cur22DidHandle].Length;
          if(0 == didLength)
          {
            stdReturn = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Cur22DidHandle].GetDataLen(&didLength);
            switch(stdReturn)
            {
            /*------------------*/
              case DCM_E_OK:
            /*------------------*/
                break;
            /*------------------*/
              case DCM_E_PENDING:
            /*------------------*/
                /* try again */
                return DCM_E_PENDING;
            /*------------------*/
              default:
            /*------------------*/
                Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
                dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_GENERALREJECT;
                break;
            }
          }

          if(DCM_E_OK != dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
          {
            /* Loop break too (errorRegister != OK)*/
            break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
          }

          /* Periodic DIDs have up to 7 Bytes (SF or UUDT msg length) */
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.DidLength = (uint8)didLength;
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Progress = DCM_2A_DISPATCH_CHECK_DID;
        }
    /*-----------------------------------------*/
      case DCM_2A_DISPATCH_CHECK_DID:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */
    /*-----------------------------------------*/
        /* Check RTE conditions */
        stdReturn = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Cur22DidHandle].CheckCondition(&dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);

        switch(stdReturn)
        {
        /*------------------*/
          case DCM_E_OK:
        /*------------------*/
            break;
        /*------------------*/
          case DCM_E_PENDING:
        /*------------------*/
            /* try again */
            return DCM_E_PENDING;
        /*------------------*/
          default:
        /*------------------*/
            Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
            Dcm_SetNegResponse(DCM_E_GENERALREJECT);/* keep the original one if set */
            break;
        }

        if(DCM_E_OK != dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
        {
          /* Loop break too (errorRegister != OK) */
          break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
        }

        /* Add new DID to the scheduler (still not comitted) */
        {
          uint8_least itemPos;
          /* Prepare for scheduling */
          itemPos = Dcm_2A_SchedulerGetAvailItemPos(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Cur22DidHandle);

          /* else If stopped or already scheduled - update */
          dcm2A_SchedulerTable[itemPos].Rate |= DCM_2A_RATE_TYPE_RESERVED;
          dcm2A_SchedulerTable[itemPos].DidHandle = dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Cur22DidHandle;
          dcm2A_SchedulerTable[itemPos].Length = dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.DidLength;
        }

        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.CurDid--;
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Progress = DCM_2A_DISPATCH_FIND_DID;
        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
    /*-----------------------------------------*/
      default:
    /*-----------------------------------------*/
        Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
    }
  }/* LOOP */

  /* If not found - no more elements */
  if(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.DidCount == 0)
  {
    /* May be no DID found - negative response */
    /* Important : avoid overwriting of the NRC if previously set! */
    Dcm_SetNegResponse(DCM_E_REQUESTOUTOFRANGE);
  }

  /* ready - let the post process do its job */
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_2A_ProcessUpdateScheduler
 **********************************************************************************************************************/
/*! \brief      Service 0x2A 0x01-0x03 processor
 *  \param[in]  rate            new periodic speed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_ProcessUpdateScheduler(Dcm_2A_RateType rate)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* At least one DID must be there */
  if ( (dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen > 0) &&
       (dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen <= DCM_2A_MAX_DID_LIST_LEN) /* limit single request processing (avoid too long run-time on big scheduler tables) */
      )
  {
    if( dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen <= (uint8)(DCM_2A_SCHEDULER_SIZE - dcm2A_ProcessorState.NumItems) ) /* check if the scheduler table can accept all of the DIDs */
    {
      /* Dispatch all DIDs */
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.CurDid = (uint8)(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen);
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.DidCount = 0;
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Rate = (Dcm_2A_MemRateType)rate;
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Progress = DCM_2A_DISPATCH_FIND_DID;
      /* delegate further processing to the dispatcher */
      Dcm_RegisterRepeaterProxy(Dcm_2A_RepeaterProxyDispatcher);
      return;
    }
    else
    {
      /* scheduler full - ISO 14229-1 04-2011 Ed 2.*/
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
    /* too long */
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_2A_ProcessStopScheduler
 **********************************************************************************************************************/
/*! \brief      Service 0x2A 0x04 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2A_ProcessStopScheduler(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DidHandleType didHandle2A;
  uint8_least       iter;
  uint8_least       supportedDids = 0;
  if(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 0)
  {
    /* Stop all */
    Dcm_2A_SchedulerStopAll();
  }
  else
  {
    if(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen <= DCM_2A_MAX_DID_LIST_LEN)
    {
      iter = (uint8_least)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen;
      while(iter != 0)
      {
        iter--;
        didHandle2A = Dcm_2A_FindDid(Dcm_Make16Bit(0xF2, dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[iter]));
        if(didHandle2A < DCM_NUM_DIDS)
        {
          supportedDids++;
          Dcm_2A_SchedulerStopDid(didHandle2A);
        }
      }

      if(0 == supportedDids)
      {
        dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2C_StateTask
 **********************************************************************************************************************/
/*! \brief      Dedicated processing task for service 0x2C
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_StateTask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Not used */
}

/***********************************************************************************************************************
 *  Dcm_2C_FindDid
 **********************************************************************************************************************/
/*! \brief      Check if a DID is for service 0x2C relevant
 *  \param[in]  did          The DID to be searched for
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_2C_FindDid(uint16 did)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return Dcm_DidMgrFindDid(did, dcm2C_DidHandleTable, dcm2C_DidCfgVariants);
}

/***********************************************************************************************************************
 *  Dcm_2C_ClearSingleDid
 **********************************************************************************************************************/
/*! \brief      Clear a DDDID definition
 *  \param[in]  dynDidHandle          handle to the DDDID to be cleared
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_ClearSingleDid(Dcm_2C_DidHandleType dynDidHandle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  *(dcm2C_DynDidInfoRefTable[dynDidHandle].pNumOfItems) = 0;
  dcm2C_DynDidTempInfoTable[dynDidHandle].ResDataLen = 0;
}

# if (DCM_2C_DEF_DYN_ID_BY_MEM_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2C_AppendMemoryDefinition
 **********************************************************************************************************************/
/*! \brief      Append memory definition(s)
 *  \param[in]  dynDidHandle          handle to the DDDID to be appended to
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_AppendMemoryDefinition(Dcm_2C_DidHandleType dynDidHandle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MemoryBlockDescType    memBlockDesc;
  Dcm_MemMgrExtrInfoRsltType memExtrRslt;

  /* Enforce FID extraction */
  memBlockDesc.addrParamSize = 0;
#  if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
  memBlockDesc.memOp = DCM_MEM_OP_READ;
#  endif

  memExtrRslt = Dcm_MemAccExtractMemoryBlockInfo(&memBlockDesc);

  /* if no error - just writes E_OK to the memory */
  dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = dcmMemMgrExtrInfo2NrcMap[memExtrRslt];

  if (DCM_MEMMGR_EXTR_INFO_OK == memExtrRslt)
  {
    Dcm_MemMgrMemBlockDefPtr pDynDidMemBlockItemRef;
    Dcm_2C_DidHandleType numOfElements;
    boolean doLoopAgain = FALSE;
    /* data length MOD blockSize must be zero */
    if((dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen % memBlockDesc.addrSizeBlockLen) == 0)
    {
      /* already skipped the first memory block info -> +1 !!! */
      /* element count is = length DIV blockSize + 1 */
      numOfElements = (Dcm_2C_DidHandleType)((dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen / memBlockDesc.addrSizeBlockLen) + 1);
      /* Check free space */
      if((*dcm2C_DynDidInfoRefTable[dynDidHandle].pNumOfItems + numOfElements) <= DCM_2C_NUM_DYN_DID_DEFS)
      {
        /* Use last known good size */
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems = *dcm2C_DynDidInfoRefTable[dynDidHandle].pNumOfItems;
        /* allow iteration over the memory blocks */
        doLoopAgain = TRUE;
      }
      else
      {
        dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    while(doLoopAgain != FALSE)
    {
      doLoopAgain = FALSE; /* assume no more iterations */

      /* evaluate the memory area by service 0x23 */
      Dcm_MemAccAnalyseMemBlock(&memBlockDesc, dcm23_MemBlockHandleTable, dcm23_MemBlockCfgVariants, dcm23_MemBlockStateInfoTable);

      /* Everything fine ? */
      if (DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
      {
#  if (DCM_2C_MULTI_DEF_SUPPORT_ENABLED == STD_ON)
        /* Set the type of the element (memory address reference)*/
        Dcm_2C_AddMemDefToSequencerAt(dynDidHandle, dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems);
#  endif
        /* Use such data type to be able to use the generic convertion function */
        pDynDidMemBlockItemRef = &(dcm2C_DynDidInfoRefTable[dynDidHandle].pItems[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems].MemBlock);

        /* Transfer into the dynamic description */
#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
        pDynDidMemBlockItemRef->memId      = memBlockDesc.memBlock.memId;
#  endif
        pDynDidMemBlockItemRef->address    = memBlockDesc.memBlock.address;
        pDynDidMemBlockItemRef->length     = memBlockDesc.memBlock.length;
        /* Add temporary this element */
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems++;
        /* One element less */
        numOfElements--; /* PRQA S 3353 */ /* QAC 7.0:  The variable '%s' is possibly unset at this point. */ /* Guaranteed by dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] == E_OK! */
        if(numOfElements != 0)
        {
          /* Check the new block */
          doLoopAgain = TRUE;
          /* Extract the requested memory block information */
          (void)Dcm_MemAccExtractMemoryBlockInfo(&memBlockDesc);
        }
      }
    }
  }

  Dcm_2C_FinalizeDidDefinition(dynDidHandle);
}
# endif

/***********************************************************************************************************************
 *  Dcm_2C_ClearDynDid
 **********************************************************************************************************************/
/*! \brief      Service 0x2C 0x03 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_ClearDynDid(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  if(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 0)
  {
# if (DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED == STD_ON)
    uint8_least iter;
    iter = DCM_2C_NUM_DYN_DEF_IDS;
    while(iter != 0)
    {
      iter--;
      /* Run-time optimization - is the DynDID defined? */
      if(*dcm2C_DynDidInfoRefTable[iter].pNumOfItems != 0)
      {
        /* Stop always (not critical) */
#  if (DCM_SERVICE_2A_ENABLED == STD_ON)
        Dcm_2A_SchedulerStopDidById(dcmDidLookUpTable[dcm2C_DidHandleTable[iter+1]]);
#  endif
      }
    }

    if(dcm2C_ReadDataState.CurUsedDidHandle != DCM_2C_NUM_DYN_DEF_IDS)
    {
      /* The DID is in use - wait till DynDID processing end */
      dcm2C_ReadDataState.WaitingForReadEnd = TRUE;
      /* Let the DynDID reading finish */
      return;
    }
# endif /* DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED == STD_ON */
  }
  else if (dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 2)
  {
# if (DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED == STD_ON)
    Dcm_2C_DidHandleType dynDidHandle;
    dynDidHandle = Dcm_2C_AnalyzeDynDid();
# else
    (void)Dcm_2C_AnalyzeDynDid();
# endif
    if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
    {
# if (DCM_SERVICE_2A_ENABLED == STD_ON)
      Dcm_2A_SchedulerStopDidById(dcmDidLookUpTable[dcm2C_DidHandleTable[dynDidHandle+1]]);
# endif
# if (DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED == STD_ON)
      if(dcm2C_ReadDataState.CurUsedDidHandle == dynDidHandle)
      {
        /* The DID is in use - wait till DynDID processing end */
        dcm2C_ReadDataState.WaitingForReadEnd = TRUE;
        return;
      }
# endif
    }
  }
  else
  {
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

# if (DCM_2C_DEF_DYN_ID_BY_MEM_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2C_DefineDynDidByMem
 **********************************************************************************************************************/
/*! \brief      Service 0x2C 0x02 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_DefineDynDidByMem(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_2C_DidHandleType dynDidHandle;

  dynDidHandle = Dcm_2C_AnalyzeDynDid();
  if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
  {
    Dcm_2C_AppendMemoryDefinition(dynDidHandle);
  }
  else
  {
    Dcm_ProcessingDone();
  }
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

/***********************************************************************************************************************
 *  Dcm_2C_FindSubFunction
 **********************************************************************************************************************/
/*! \brief      Service 0x2C sub-function look-up
 *  \param[in]  subFuncId         sub-function value to be searched for
 *  \return     Sub-function handle
 *  \retval     0-2                    - success
 *  \retval     DCM_2C_OP_TYPE_INVALID - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_2C_OpType, DCM_CODE) Dcm_2C_FindSubFunction(uint8 subFuncId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Valid sub-function at all (top limit)? (0x1, 0x2, and 0x3 )*/
  if(subFuncId < 0x04u)
  {
    /* Is supported at all? */
    subFuncId = dcm2C_SubFuncToCtrlTypeMap[subFuncId];
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
    if(subFuncId < 0x04u)
# endif
    {
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
      if((dcm2C_SubFuncCfgVariant[subFuncId] & dcmStateMachine.CfgVariantMask) != 0)
# endif
      {
        return subFuncId;
      }
    }
  }
  return DCM_2C_OP_TYPE_INVALID;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

# if (DCM_2C_DEF_DYN_ID_BY_DID_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2C_RepeaterProxyAddDidDispatcher
 **********************************************************************************************************************/
/*! \brief      Service 0x2C 0x01 polling dispatcher 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2C_RepeaterProxyAddDidDispatcher(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType    stdReturn;
  uint16            didLength;
  uint16            lDid;
  P2VAR(Dcm_2C_SrcDidItemInfoType, AUTOMATIC, DCM_VAR_NOINIT) pDynDidSrcDidItemRef;

  /* Req data len contains still the count of the DIDs */
  /* Process all DIDs until an error has been detected */
  while((dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDid != 0)&&
        (dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] == DCM_E_OK))
  {
    pDynDidSrcDidItemRef = &(dcm2C_DynDidInfoRefTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDynDidHandle].pItems[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems].SrcDid);

    switch(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.Progress)
    {
    /*-----------------------------------------*/
      case DCM_2C_DISPATCH_FIND_DID:/* fall through in OK case only */
    /*-----------------------------------------*/
        lDid = Dcm_Make16Bit(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0], dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1]);

        /* Is the PID available (also dynamic DIDs can be asked) ? */
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDidHandle = (Dcm_MemDidHandleType)Dcm_22_FindDid(lDid);
        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData = &dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[2];

        /* If found */
        if(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDidHandle >= DCM_NUM_DIDS)
        {
          /* At least one DID is illegal */
          dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
          break;/* PRQA S 3333 */ /* exit */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
        }

        {
          Dcm_DidHandleType tempHandle;
          /* Check if dyn defined PID referenced */
          tempHandle = Dcm_2C_FindDid(lDid);

          if(tempHandle < DCM_NUM_DIDS)
          {
            /* Reject dyn DID references */
            dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
            break;/* PRQA S 3333 */ /* exit */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
          }
        }

        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.Progress = DCM_2C_DISPATCH_GET_LEN;

    /*-----------------------------------------*/
      case DCM_2C_DISPATCH_GET_LEN:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* fall through om OK case only */
    /*-----------------------------------------*/
        didLength = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDidHandle].Length;
        if(0 == didLength)
        {
          stdReturn = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDidHandle].GetDataLen(&didLength);
          switch(stdReturn)
          {
          /*------------------*/
            case DCM_E_OK:
          /*------------------*/
              break;
          /*------------------*/
            case DCM_E_PENDING:
          /*------------------*/
              /* try again */
              return DCM_E_PENDING;
          /*------------------*/
            default:
          /*------------------*/
              Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
              dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_GENERALREJECT;
              break;
          }
        }

        pDynDidSrcDidItemRef->did22Handle = dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDidHandle;
        pDynDidSrcDidItemRef->offset    =  dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0];
        pDynDidSrcDidItemRef->size      =  dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1];
        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData = &dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[2];

        /* Do not consider underflow (0 - 1) since the zero case is checked additionally.*/
        if((((Dcm_2C_SrcDidOffsetType)(pDynDidSrcDidItemRef->offset - 1) + pDynDidSrcDidItemRef->size) > didLength) ||
            (pDynDidSrcDidItemRef->offset == 0) ||
            (pDynDidSrcDidItemRef->size == 0))
        {
          /* This DID is illegally referenced */
          dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
          break;/* PRQA S 3333 */ /* exit */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
        }
        else
        {
          /* Correct the start position to zero based offset (UDS specifies: src Byte 1 => offset 1 */
          pDynDidSrcDidItemRef->offset--;
          (void)Dcm_DidMgrAnalyseDid(DCM_DIDMGR_CLIENT_ID_2C, dcm22_DidStateInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDidHandle]);
          if(DCM_E_OK != dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
          {
            break;/* PRQA S 3333 */ /* exit */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
          }

          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.Progress = DCM_2C_DISPATCH_CHECK_DID;
        }

    /*-----------------------------------------*/
      case DCM_2C_DISPATCH_CHECK_DID:/* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* fall through om OK case only */
    /*-----------------------------------------*/
        /* Check RTE conditions */
        stdReturn = dcm22_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDidHandle].CheckCondition(&dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);

        switch(stdReturn)
        {
        /*------------------*/
          case DCM_E_OK:
        /*------------------*/
            break;
        /*------------------*/
          case DCM_E_PENDING:
        /*------------------*/
            /* try again */
            return DCM_E_PENDING;
        /*------------------*/
          default:
        /*------------------*/
            Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
            dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_GENERALREJECT;
            break;
        }

        if(DCM_E_OK != dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
        {
          /* Loop break too (errorRegister != OK)*/
          break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
        }
        /* Add temporary this element */
        Dcm_2C_AddPidDefToSequencerAt(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDynDidHandle,
                                      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems);

        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems++;
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDid--;

        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.Progress = DCM_2C_DISPATCH_FIND_DID;
        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
    /*-----------------------------------------*/
      default:
    /*-----------------------------------------*/
        Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
        break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
    }
  }/* LOOP */


  /* ready */
  Dcm_2C_FinalizeDidDefinition(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDynDidHandle);
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_2C_DEF_DYN_ID_BY_DID_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2C_AppendPidDefinition
 **********************************************************************************************************************/
/*! \brief      Service 0x2C 0x01 processor
 *  \param[in]  dynDidHandle          handle to the DDDID to be appended to
 *  \param[in]  numOfElements         number of definitions to be appended
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_AppendPidDefinition(Dcm_2C_DidHandleType dynDidHandle, Dcm_2C_DidHandleType numOfElements)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDynDidHandle = (Dcm_2C_MemDidHandleType)dynDidHandle;
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurDid          = (Dcm_2C_MemDidHandleType)numOfElements;
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.Progress = DCM_2C_DISPATCH_FIND_DID;
  Dcm_RegisterRepeaterProxy(Dcm_2C_RepeaterProxyAddDidDispatcher);
}
# endif

# if (DCM_2C_DEF_DYN_ID_BY_DID_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2C_DefineDynDidByDid
 **********************************************************************************************************************/
/*! \brief      Service 0x2C 0x01 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2C_DefineDynDidByDid(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_2C_DidHandleType dynDidHandle;
  dynDidHandle = Dcm_2C_AnalyzeDynDid();
  if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
  {
    /* data length MOD 4 must be zero */
    if(((dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen & 0x03) == 0)&&
        (dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen > 0))
    {
      /* element count is = length DIV 4 */
      dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen >>= 2;
      /* Check free space */
      if((*dcm2C_DynDidInfoRefTable[dynDidHandle].pNumOfItems + dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen) <= DCM_2C_NUM_DYN_DID_DEFS)
      {
        /* Use last known good size */
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems = *dcm2C_DynDidInfoRefTable[dynDidHandle].pNumOfItems;
        Dcm_2C_AppendPidDefinition(dynDidHandle, (Dcm_2C_DidHandleType)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen);
        return;
      }
      else
      {
        dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

/***********************************************************************************************************************
 *  Dcm_2C_RepeaterProxyReadData
 **********************************************************************************************************************/
/*! \brief      Service 0x2C polling read DDDID processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_2C_RepeaterProxyReadData(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  /* Check the type of the definition (by DID or mem address)*/
  while((dcm2C_ReadDataState.CurrentItem < *dcm2C_DynDidInfoRefTable[dcm2C_ReadDataState.CurUsedDidHandle].pNumOfItems)
        &&(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]))
  {
# if (DCM_2C_MULTI_DEF_SUPPORT_ENABLED == STD_ON)
    if(Dcm_2C_IsDidRefDefinitionAt(dcm2C_ReadDataState.CurUsedDidHandle, dcm2C_ReadDataState.CurrentItem))
# endif
    {
# if (DCM_2C_DEF_DYN_ID_BY_DID_ENABLED == STD_ON)
      P2VAR(Dcm_2C_SrcDidItemInfoType, AUTOMATIC, DCM_VAR_NOINIT) pDynDidSrcDidItemRef;
      pDynDidSrcDidItemRef = &(dcm2C_DynDidInfoRefTable[dcm2C_ReadDataState.CurUsedDidHandle].pItems[dcm2C_ReadDataState.CurrentItem].SrcDid);

      stdReturn = Dcm_DidMgrReadDid(pDynDidSrcDidItemRef->did22Handle, dcm2C_DefItemDataBuffer, DCM_DIDMGR_CLIENT_ID_2C, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
      if(DCM_E_PENDING == stdReturn)
      {
        return DCM_E_PENDING;
      }

      /* Copy data */
      Dcm_CopyRam2Ram(dcm2C_ReadDataState.ResData, &dcm2C_DefItemDataBuffer[pDynDidSrcDidItemRef->offset], pDynDidSrcDidItemRef->size);
      /* Prepare next write position */
      dcm2C_ReadDataState.ResData = &dcm2C_ReadDataState.ResData[pDynDidSrcDidItemRef->size];
# endif
    }
# if (DCM_2C_MULTI_DEF_SUPPORT_ENABLED == STD_ON)
    else
# endif
    {
# if (DCM_2C_DEF_DYN_ID_BY_MEM_ENABLED == STD_ON)
      Dcm_MemMgrMemBlockDefPtr pDynDidMemBlockItemRef;
      pDynDidMemBlockItemRef = &(dcm2C_DynDidInfoRefTable[dcm2C_ReadDataState.CurUsedDidHandle].pItems[dcm2C_ReadDataState.CurrentItem].MemBlock);

      stdReturn = Dcm_23_ReadMemoryBlock(&dcm2C_ReadDataState.ResData[0], pDynDidMemBlockItemRef, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
      if(DCM_E_PENDING == stdReturn)
      {
        return DCM_E_PENDING;
      }
      /* Prepare next write position */
      dcm2C_ReadDataState.ResData = &dcm2C_ReadDataState.ResData[pDynDidMemBlockItemRef->length];
# endif
    }
    dcm2C_ReadDataState.CurrentItem++;
  }

# if (DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED == STD_ON)
  /* may be cleared */
  if(dcm2C_ReadDataState.WaitingForReadEnd == TRUE)
  {
    /*dcm2C_ReadDataState.Waiting... will be cleared on next read trigger */
    Dcm_ProcessingDone();
  }
# endif

  /* Mark as invalid */
  dcm2C_ReadDataState.CurUsedDidHandle = DCM_2C_NUM_DYN_DEF_IDS;
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_2E_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2E_OemInit
 **********************************************************************************************************************/
/*! \brief      Service 0x2E OEM initializiation
 *  \context    Function is called at module init time.
 **********************************************************************************************************************/
 /*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2E_OemInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* nothing to init */
}

/***********************************************************************************************************************
 *  Dcm_2E_OemPostProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x2E OEM write access post processing
 *  \param[in]  status       Post operation status
 *  \context    Function is called from Dcm_StateTask context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2E_OemPostProcess(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
}
#endif /* (DCM_SERVICE_2E_ENABLED == STD_ON) */
#if (DCM_SERVICE_2F_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2F_FindSubFunction
 **********************************************************************************************************************/
/*! \brief      SubFunction look-up
 *  \param[in]  subFuncId                 searched sub-function
 *  \param[in]  didRef                    DID reference handle
 *  \return     service instance reference handle
 *  \retval     0-(DCM_2F_NUM_DID_INST-1)  - success    
 *  \retval     DCM_2F_NUM_DID_INST        - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_2F_InstHandleType, DCM_CODE) Dcm_2F_FindSubFunction(uint8 subFuncId, Dcm_DidHandleType didRef)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_2F_InstHandleType lResult = DCM_2F_NUM_DID_INST;
  /* Valid sub-function at all (top limit)? (0x0, 0x1, 0x2 or 0x3 only)*/
  if(subFuncId < 4)
  {
    subFuncId = dcm2F_SubFuncToCtrlTypeMap[subFuncId];
    /* IO operation supported ? */
    if(subFuncId < DCM_2F_NUM_IO_OP_CONST)
    {
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
      if((dcm2F_SubFuncCfgVariant[subFuncId] & dcmStateMachine.CfgVariantMask) != 0)
# endif
      {
        lResult = dcm2F_DidControlTypeInfo[didRef][subFuncId];
      }
    }
  }
  return lResult;
}

/***********************************************************************************************************************
 *  Dcm_2F_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x2F polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2F_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  /* Give the control to the application */
  stdReturn = dcm2F_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2F_ProxyContext.CurDidHandle].IoControl((Dcm_RteDataPtrType)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData, /* PRQA S 0310 */ /* PRQA S 0308 */
                                                                                                         dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen,
                                                                                                         (Dcm_RteDataPtrType)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData, /* PRQA S 0310 */ /* PRQA S 0308 */
                                                                                                         &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]); /* PRQA S 0310 */ /* PRQA S 0308 */

  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_GENERALREJECT;
      break;
  }

  Dcm_AddValue(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resDataLen , Dcm_MsgLenType, dcm2F_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2F_ProxyContext.CurDidHandle].ResLength);
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_2F_ENABLED == STD_ON) */
#if (DCM_SERVICE_2F_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2F_ReturnControlToECU
 **********************************************************************************************************************/
/*! \brief      API for returning the control to the ECU.
 *  \context    Function is called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_2F_ReturnControlToECU(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* not used */
}
#endif /* (DCM_SERVICE_2F_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_RidMgrReleaseRidClient
 **********************************************************************************************************************/
/*! \brief      Release locked resource
 *  \param[in]  clientId       clientId to release
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_RidMgrReleaseRidClient(Dcm_RidMgrRidClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmRidMgrResourceMap[clientId] = (Dcm_MemRidHandleType)DCM_NUM_RIDS;
}
# endif

/***********************************************************************************************************************
 *  Dcm_RidMgrInit
 **********************************************************************************************************************/
/*! \brief      RID Manager initialization
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_RidMgrInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
  Dcm_RidMgrRidClientType clientIter = DCM_RID_MGR_NUM_RID_CLIENTS;

  while(clientIter != 0)
  {
    clientIter--;
    Dcm_RidMgrReleaseRidClient(clientIter);
  }
# endif
}

# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_RidMgrLockRidClient
 **********************************************************************************************************************/
/*! \brief      Locks a RID resourse for one client (e.g. 0x31)
 *  \param[in]  rid31Handle       Handle to a RID located in the service 0x31 table to be locked
 *  \param[in]  clientId          Client Id that requests access
 *  \return     Reservation result
 *  \retval     TRUE - success (free place found)
 *  \retval     FALSE - failed (already locked)
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(boolean, DCM_CODE) Dcm_RidMgrLockRidClient(Dcm_RidHandleType rid31Handle, Dcm_RidMgrRidClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  if(dcmRidMgrResourceMap[clientId] == (Dcm_MemRidHandleType)DCM_NUM_RIDS)
  {
    Dcm_RidMgrRidClientType iter = DCM_RID_MGR_NUM_RID_CLIENTS;

    /* this client does not own a RID yet - find another owner for this RID */
    while(iter != 0)
    {
      iter--;
      if(dcmRidMgrResourceMap[iter] == rid31Handle)
      {
        /* FALSE since it can not be the current client */
        return FALSE;
      }
    }
    /* Lock the resource */
    dcmRidMgrResourceMap[clientId] = (Dcm_MemRidHandleType)rid31Handle; /* PRQA S 3689 */ /* Not possible to have out of boundary access since 
                                                                                             * the number of cuncurent clients is equal to the number of resources. Assertion checks this during development.*/
  }
  else
  {
    /* it must be the same rid31Handle since no parallel processing of the client is possible */
    Dcm_BoolCheckValueRangeFailed((dcmRidMgrResourceMap[clientId] == (Dcm_MemRidHandleType)rid31Handle), DcmServiceId_DsdDispatcher); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  }

  return TRUE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_31_FindSubFunction
 **********************************************************************************************************************/
/*! \brief      SubFunction look-up
 *  \param[in]  subFuncId                 searched sub-function
 *  \param[in]  ridRef                    RID reference handle
 *  \return     service instance reference handle
 *  \retval     0-(DCM_NUM_RID_INST-1)  - success    
 *  \retval     DCM_NUM_RID_INST        - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_RidInstHandleType, DCM_CODE) Dcm_31_FindSubFunction(uint8 subFuncId, Dcm_RidHandleType ridRef)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_RidInstHandleType lResult = DCM_NUM_RID_INST;
  /* Valid sub-function at all (top limit)? (0x1, 0x2 or 0x3 only)*/
  if(subFuncId < 4)
  {
    /* Is supported at all? */
    subFuncId = dcm31_SubFuncToCtrlTypeMap[subFuncId];

    if(subFuncId < DCM_31_NUM_SUBFUNC_CONST)
    {
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
      if((dcm31_SubFuncCfgVariant[subFuncId] & dcmStateMachine.CfgVariantMask) != 0)
# endif
      {
        lResult = dcm31_ControlTypeInfo[ridRef][subFuncId];
      }
    }
  }
  return lResult;
}

/***********************************************************************************************************************
 *  Dcm_31_FindRid
 **********************************************************************************************************************/
/*! \brief      RID look-up
 *  \param[in]  rid                       searched RID
 *  \return     RID reference handle
 *  \retval     >0 - success    
 *  \retval     0  - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_RidHandleType, DCM_CODE) Dcm_31_FindRid(uint16 rid)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_RidHandleType ridHandle = (Dcm_RidHandleType)dcmRidLookUpTable[0];

  while((ridHandle != 0)&&(rid != dcmRidLookUpTable[ridHandle]))
  {
    ridHandle--;
  }
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
  return (Dcm_RidHandleType)(((dcm31_RidCfgVariants[ridHandle] & dcmStateMachine.CfgVariantMask) != 0)?ridHandle:0);
# else
  return ridHandle;
# endif
}

/***********************************************************************************************************************
 *  Dcm_31_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x31 polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_31_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType      stdReturn;
  Dcm_RteDataLenType  appResDataLen = 0;
  Dcm_MsgLenType      cfgResDataLen;

  Dcm_ContextIdType   lContext = Dcm_CtxtMgrGetCurUdsContextId();

# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
  boolean lIsReserved;
  lIsReserved = Dcm_RidMgrLockRidClient(dcmRepeatedProxyContexts[lContext].dcm31_ProxyContext.CurRidHandle, Dcm_31_UdsContextId2Clientid(lContext));
  if(FALSE == lIsReserved)
  {
    /* try again */
    return DCM_E_PENDING;
  }
# endif

  /* Give the control to the application */
  stdReturn = dcm31_ServiceInfoTable[dcmRepeatedProxyContexts[lContext].dcm31_ProxyContext.CurRidInstHandle].Control((Dcm_RteDataPtrType)dcmDsdMsgContext[lContext].reqData, /* PRQA S 0310 */ /* PRQA S 0308 */
                                                                                                                      dcmDsdMsgContext[lContext].reqDataLen,
                                                                                                                      (Dcm_RteDataPtrType)dcmDsdMsgContext[lContext].resData, /* PRQA S 0310 */ /* PRQA S 0308 */
                                                                                                                      &appResDataLen,
                                                                                                                      &dcmDsdErrorRegister[lContext]);
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      Dcm_SetNegResponse(DCM_E_GENERALREJECT);/* keep the old NRC if set */
      break;
  }

# if (DCM_RIDMGR_RESMGR_ENABLED == STD_ON)
  /* No more needed */
  Dcm_RidMgrReleaseRidClient(Dcm_31_UdsContextId2Clientid(lContext));
# endif

  cfgResDataLen = dcm31_ServiceInfoTable[dcmRepeatedProxyContexts[lContext].dcm31_ProxyContext.CurRidInstHandle].ResLength;

  /* avoid application tricks to change the response length */
  if(cfgResDataLen != 0)
  {
    /* If static length the OUT parameter shall be either zero or match the configured length */
    Dcm_CheckApiValueRangeFailed(((appResDataLen == cfgResDataLen)||(appResDataLen == 0)), DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
    appResDataLen = cfgResDataLen;
  }

  Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen , Dcm_MsgLenType, appResDataLen);

  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_3D_WriteMemoryBlock
 **********************************************************************************************************************/
/*! \brief      Service 0x3D common write access 
 *  \param[out] memBlockDef      Target memory block descriptor.
 *  \param[in]  srcAddr          Source memory address - diag buffer.
 *  \param[out] errorRegister    The operation result
 *  \context    Function shall be called on task level only.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_3D_WriteMemoryBlock(Dcm_MsgType srcAddr, Dcm_MemMgrMemBlockDefPtr memBlockDef, Dcm_NegativeResponseCodePtrType pErrorCode)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* No additional data after address and length */
  /* Response data pointer already correct */
  DCM_IGNORE_UNREF_PARAM(pErrorCode); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
  {
    Dcm_ReturnWriteMemoryType result;
    result = Dcm_WriteMemory(
#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
                            memBlockDef->memId,
#  else
                            0,
#  endif
                            memBlockDef->address,
                            memBlockDef->length,
                            srcAddr
                            );
    switch(result)
    {
      /*--------------------*/
      case DCM_WRITE_OK:
      /*--------------------*/
        break;
      /*--------------------*/
      case DCM_WRITE_PENDING:
      /*--------------------*/
        return DCM_E_PENDING;
      /*--------------------*/
      case DCM_WRITE_FAILED:
      /*--------------------*/
        *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        return DCM_E_NOT_OK;
      default:
        *pErrorCode = DCM_E_GENERALREJECT;
        Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
        return DCM_E_NOT_OK;
    }
  }
# endif
# if (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)
#  if (DCM_MEMORY_ACCESS_TEST_ENABLED == STD_ON)
  TscDcm_WriteMemAccess(memBlockDef->address, srcAddr, memBlockDef->length);
#  else
  {
    Dcm_ApplDataPtrType lDataPtr;
    lDataPtr = Dcm_MemAccHwAbMakePointer(memBlockDef->address);
    Dcm_CopyRam2Ram(lDataPtr, srcAddr, memBlockDef->length);
  }
#  endif
# endif
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_3D_WriteData
 **********************************************************************************************************************/
/*! \brief      Service 0x3D OEM writer 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_3D_WriteData(Dcm_MemMgrMemBlockDefPtr memInfo) /* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
  /* Transfer the info to the global proxy context */
#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm3D_ProxyContext.memBlockDef.memId = memInfo->memId;
#  endif
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm3D_ProxyContext.memBlockDef.address = memInfo->address;
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm3D_ProxyContext.memBlockDef.length = memInfo->length;
  Dcm_RegisterRepeaterProxy(Dcm_3D_WriteRepeaterProxy);
# else
  (void)Dcm_3D_WriteMemoryBlock(&dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0], memInfo, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
  /* Close the processing */
  Dcm_ProcessingDone();
# endif
}
#endif /* (DCM_SERVICE_3D_ENABLED == STD_ON) */
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_3D_WriteDataVirtual
 **********************************************************************************************************************/
/*! \brief      Service 0x3D default writer 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_3D_WriteDataVirtual(Dcm_MemMgrMemBlockDefPtr memInfo)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* just delegate the job to the default writer */
  Dcm_3D_WriteData(memInfo);
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_3D_ENABLED == STD_ON) */
#if (DCM_SERVICE_87_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_87_PrepareReset
 **********************************************************************************************************************/
/*! \brief      Service 0x87 default rset prepare
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE  FUNC(void, DCM_CODE) Dcm_87_PrepareReset(uint8 linkControlHandle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(linkControlHandle); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  /* Close the processing */
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_87_ENABLED == STD_ON) */
#if (DCM_SERVICE_87_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_87_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x87 polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_87_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  Dcm_NegativeResponseCodeType  errorCode = DCM_E_OK;

  /* The record options are in the resDataBuffer already!!! */
  stdReturn = dcm87_LinkControlPermFunc((uint8)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0], &errorCode);

  /* Important: no sync usage any more! */
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      /* Send the prepared pos response */
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      errorCode = DCM_E_GENERALREJECT;
      break;
  }

  if(DCM_E_OK != errorCode)
  {
    Dcm_SetNegResponse(errorCode);
    Dcm_ProcessingDone();
  }
  else
  {
    /* delegate the job */
    Dcm_87_PrepareLinkControl((uint8)dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0]);
  }
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_87_ENABLED == STD_ON) */
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspOemFblResInit
 **********************************************************************************************************************/
/*! \brief      DSP Default FBL init
 *  \context    Function must be called with disabled interrupts.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DspOemFblResInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmDsp_RespBuffer[0] = 0; /* mark "send no response" */
  dcmDsp_OemFblResponderContext.Progress = DCM_DSP_FBL_GET_PROG_CONDITIONS;
  /* Prepare for after reset check */
  Dcm_EvMgrSetEvent(DCM_TASK_ID_STATE, DCM_EVENT_PROCESS_FBL_RES);
  /* Start Performance timer - use P2*_ProgrammingSession since the FBL has reset the ECU from the ProgrSession
   * Prog session index is always 0x01, since the only valid session prior it is the default one (at index 0x00)*/
  Dcm_TmrMgrStartTimer(DCM_TIMER_ID_FBL_RES, dcm10_ServiceInfoTable[1].TickTime.timeOutP2Ex);
}

/***********************************************************************************************************************
 *  Dcm_DspOemFblResProcessor
 **********************************************************************************************************************/
/*! \brief      DSP Default FBL responder
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DspOemFblResProcessor(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  switch(dcmDsp_OemFblResponderContext.Progress)
  {
    /*-----------------------------------------*/
      case DCM_DSP_FBL_GET_PROG_CONDITIONS:
    /*-----------------------------------------*/
        {
          Dcm_ProgConditionsType progConds;
          Dcm_GetProgConditions(&progConds);
          if(DCM_WARM_START == progConds.EcuStartMode)
          {
            /* Compose response */
            switch(progConds.Sid)
            {
              /*---------------*/
              case 0x10u:
              /*---------------*/
                dcmDsp_RespBuffer[0] = 6;
                dcmDsp_RespBuffer[1] = 0x50u;
                dcmDsp_RespBuffer[2] = 0x01u;
                dcmDsp_RespBuffer[3] = Dcm_GetHiByte(dcm10_ServiceInfoTable[0].ResponseTime.timeOutP2);
                dcmDsp_RespBuffer[4] = Dcm_GetLoByte(dcm10_ServiceInfoTable[0].ResponseTime.timeOutP2);
                dcmDsp_RespBuffer[5] = Dcm_GetHiByte(dcm10_ServiceInfoTable[0].ResponseTime.timeOutP2Ex);
                dcmDsp_RespBuffer[6] = Dcm_GetLoByte(dcm10_ServiceInfoTable[0].ResponseTime.timeOutP2Ex);
                /* Must be the default session */
                Dcm_CheckApiValueRangeFailed((progConds.SubFncId == 0x01), DcmServiceId_GetProgConditions);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
                break;
              /*---------------*/
              case 0x11u:
              /*---------------*/
                dcmDsp_RespBuffer[0] = 2;
                dcmDsp_RespBuffer[1] = 0x51u;
                dcmDsp_RespBuffer[2] = progConds.SubFncId;
                /* Must not be one of the rapid-shutdowns */
                Dcm_CheckApiValueRangeFailed((progConds.SubFncId != 0x04u) && (progConds.SubFncId != 0x05u), DcmServiceId_GetProgConditions);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
                break;
              /*---------------*/
              default:
              /*---------------*/
                /* Unexpected SID */
                Dcm_CheckAlwaysFailed(DcmServiceId_GetProgConditions);
                return DCM_E_NOT_OK;
            }
            /* Find corresponding connection */
            {
              uint8_least connIter = DCM_NUM_CONNECTIONS;
              dcmDsp_OemFblResponderContext.ConnId = 0xFFu;
              /* Get Tx PduId */
              while(connIter != 0)
              {
                connIter--;
                if(dcmDslPduConnectionInfoTable[connIter].sourceAddr == progConds.TesterSourceAddr)
                {
                  dcmDsp_OemFblResponderContext.ConnId = (Dcm_ConnectionRefType)connIter; /* we actually iterate through all RxPduIds */
                  connIter = 0;/* break */
                }
              }

              if(0xFF == dcmDsp_OemFblResponderContext.ConnId)
              {
                /* No valid connection found */
                Dcm_CheckAlwaysFailed(DcmServiceId_GetProgConditions);
                return DCM_E_NOT_OK;
              }

              /* Still time to send the response ?*/
              if(dcmTimerEngine[DCM_TIMER_ID_FBL_RES] != 0)
              {
                boolean lockResult;
                lockResult = Dcm_DoLock(dcmDsp_OemFblResponderContext.ConnId);
                if(FALSE == lockResult)
                {
                  return DCM_E_NOT_OK;/* DCM already busy with new request - forget pos Response */
                }

                /* Activate COMM */
                Dcm_ProcessActivity(DCM_ACTIVITY_SOURCE_FBL_RESPONDER);
                dcmDsp_OemFblResponderContext.Progress = DCM_DSP_FBL_WAIT_FULL_COMM;
              }
              else
              {
                /* time expired - forget pos response */
                return DCM_E_OK;/* DCM already busy with new request - forget pos Response */
              }
            }
          }
          else
          {
            return DCM_E_OK;/* nothing to do - skip next steps immediately */
          }
        }
    /*-----------------------------------------*/
      case DCM_DSP_FBL_WAIT_FULL_COMM: /* fall through to save time */
    /*-----------------------------------------*/
        /* Still time to send the response ?*/
        if(dcmTimerEngine[DCM_TIMER_ID_FBL_RES] != 0)
        {
          /* Already in Full Comm ? */
          if(DCM_COMM_STATE_FULL != dcmStateMachine.CommState)
          {
            return DCM_E_PENDING;
          }

          /* Send response */
          Dcm_SendSpontaneousResponse(dcmDsp_OemFblResponderContext.ConnId,
                                     &dcmDsp_RespBuffer[1], dcmDsp_RespBuffer[0]);
          /* END of sequence - do not call this function again */
        }
        else
        {
          /* Dectivate COM */
          Dcm_ProcessActivity(DCM_ACTIVITY_SOURCE_FBL_RESPONDER);
          Dcm_DoUnLock(dcmDsp_OemFblResponderContext.ConnId);
          /* END of sequence - do not call this function again */
        }
        break;
    /*-----------------------------------------*/
      default:
    /*-----------------------------------------*/
        break;
  }

  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */
/***********************************************************************************************************************
 *  Dcm_DspInit
 **********************************************************************************************************************/
/*! \brief      Init the DSP.
 *  \context    Function must be called within disabled all interrupts.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DspInit(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least iter = DCM_NUM_SERVICES;
  while(iter != 0)
  {
    iter--;
    dcmDspServiceInfoTable[iter].ServiceInit();
  }

#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
  Dcm_DspOemFblResInit();
#endif

#if (DCM_SERVICE_23_ENABLED == STD_ON) || \
    (DCM_SERVICE_3D_ENABLED == STD_ON)
  Dcm_MemAccInit();
#endif
#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  Dcm_DemMgrInit();
#endif
}

/***********************************************************************************************************************
 *  Dcm_DspConfirmation
 **********************************************************************************************************************/
/*! \brief      Postprocessing of a service.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DspConfirmation(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DspConfirmation);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  if(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].serviceIndex < DCM_NUM_SERVICES)
  {
    if(DCM_RES_POS_OK == status)
    {
      if(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].stateTransRef < DCM_NUM_STATE_TRANSITIONS)
      {
        Dcm_ExecuteStateTransition(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].stateTransRef);
      }
    }
    /* Now execute post handlers */
    dcmDspServiceInfoTable[dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].serviceIndex].ServicePostProcessor(status);
  }
}

/***********************************************************************************************************************
 *  Dcm_DspStateTask
 **********************************************************************************************************************/
/*! \brief      DCM Task for service processing.
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
CONTEXT_FUNC_LOC FUNC(void, DCM_CODE) Dcm_DspStateTask(DCM_CONTEXT_PARAM_DEF_ONLY)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EventType ev;
  Dcm_EventType postEv = 0;

  ev = Dcm_EvMgrGetEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_PARAM_VALUE));

  Dcm_CtxtMgrSetActiveContext(DCM_CONTEXT_PARAM_VALUE);

  while(ev != 0)
  {
    Dcm_EvMgrClearEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_PARAM_VALUE), ev);

#if (DCM_USE_SAFE_RESET_ENABLED == STD_ON)
    /* Try to invoke a reset */
    if((ev & DCM_EVENT_PERFORM_RESET) != 0)
    {
      Std_ReturnType result;
      result = Dcm_DspOemPerformReset();
      if(DCM_E_PENDING == result)
      {
        /* Retry next cycle with the same parameter*/
        postEv |= DCM_EVENT_PERFORM_RESET;
      }
    }
#endif

    /* tester time out is high priority */
    if((ev & DCM_EVENT_TESTER_TIMEOUT) != 0)
    {
      /* Check the session here (not at start):
       * 1. Saves runtime on confirmation 
       * 2. Avoids lack of S3 monitoring after starting a non default session.(saves code for explicit start)
       */
      if(dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX] != 0)
      {
        Dcm_ExecuteStateTransition(DCM_DEFAULT_SESSION_STATE_TRANS_IDX);
#if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
        /* Release always since in non-default session is set */
        Dcm_DslFreeSessionOwner();
#endif
      }
    }

    if((ev & DCM_EVENT_STATE_TASK_PROXY) != 0)
    {
      Std_ReturnType result;
      result = dcmRepeatedProxyCallBack[DCM_CONTEXT_PARAM_VALUE]();
      if(DCM_E_PENDING == result)
      {
        /* Retry next cycle with the same parameter*/
        postEv |= DCM_EVENT_STATE_TASK_PROXY;
      }
    }

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    if((ev & DCM_EVENT_PB_UPDATE_PAGE) != 0)
    {
      Dcm_DcmUpdatePage(DCM_CONTEXT_PARAM_VALUE_ONLY);
    }
#endif

    if((ev & (DCM_EVENT_SEND_PAGED_RES | DCM_EVENT_SEND_LINEAR_RES)) != 0)
    {
      Dcm_EnterCritical(); /* Prevent interruption by timer task */
      if(DSL_RES_TYPE_NONE == dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType)
      {
        /* Now we can stop the timer */
        Dcm_TmrMgrNotSafeStopTimer(DCM_CONTEXT_P2_TIMER_ID(DCM_CONTEXT_PARAM_VALUE));
        Dcm_LeaveCritical();

        dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType = (Dcm_DslResponseType)(((ev & DCM_EVENT_SEND_LINEAR_RES) != 0)?DSL_RES_TYPE_FINAL_LINEAR:DSL_RES_TYPE_FINAL_PAGED);
        dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState = DCM_CONTEXT_STATE_TX_STARTED;
        Dcm_DslLL_StartTransmission(DCM_CONTEXT_PARAM_VALUE_ONLY);
      }
      else
      {
        Dcm_LeaveCritical();
        /* Retry first at the next task call */
        postEv |= (Dcm_EventType)(ev & (DCM_EVENT_SEND_PAGED_RES | DCM_EVENT_SEND_LINEAR_RES));
      }
    }

    if((ev & DCM_EVENT_RCRRP_CONFIRM) != 0)
    {
      Std_ReturnType stdReturn;
      stdReturn = dcm10_RcrRpConfFunc((Dcm_ConfirmationStatusType)((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].txConfStatus == DSL_COMM_E_OK)
                                                                  ?DCM_RES_NEG_OK:DCM_RES_NEG_NOT_OK));
      Dcm_CheckApiValueRangeFailed((stdReturn == DCM_E_OK)||(stdReturn == DCM_E_NOT_OK), DcmServiceId_MainFunction); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      DCM_IGNORE_UNREF_PARAM(stdReturn); /* PRQA S 3112 */ /* avoid warnings in non-DET mode */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
    }

    if((ev & DCM_EVENT_TX_END) != 0)
    {
      Dcm_ConfirmationStatusType status = DCM_RES_POS_OK;
      if(dcmDsdErrorRegister[DCM_CONTEXT_PARAM_VALUE] != DCM_E_OK)
      {
        /* Bit 1 = neg response */
        status |= (Dcm_ConfirmationStatusType)0x2;
      }

      if(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].txConfStatus != DSL_COMM_E_OK)
      {
        /* Bit 0 = tx failure */
        status |= (Dcm_ConfirmationStatusType)0x01;
      }

      Dcm_DspConfirmation(DCM_CONTEXT_PARAM_VALUE_FIRST status);

      /* Process the activity */
      Dcm_ProcessActivity(DCM_ACTIVITY_SOURCE_MSG_TX_END);
    }

    if((ev & DCM_EVENT_NEW_REQ) != 0)
    {
      dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState = DCM_CONTEXT_STATE_PROCESS_STARTED;
      Dcm_DsdDispatcher(DCM_CONTEXT_PARAM_VALUE_ONLY);
    }

#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
    /* FBL responses are lower priority than external */
    if((ev & DCM_EVENT_PROCESS_FBL_RES) != 0)
    {
      Std_ReturnType result;
      result = Dcm_DspOemFblResProcessor();
      if(DCM_E_PENDING == result)
      {
        /* Retry next cycle with the same parameter*/
        postEv |= DCM_EVENT_PROCESS_FBL_RES;
      }
    }
#endif

    /* Still anything to do (no loop events (retry!!!)) */
    ev = Dcm_EvMgrGetEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_PARAM_VALUE));
  }/* end of active events */

  /* runtime optimization since cyclically called */
  if(postEv != 0)
  {
    Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_PARAM_VALUE), postEv);
  }
}

/***********************************************************************************************************************
 *  Dcm_RegisterRepeaterProxy
 **********************************************************************************************************************/
/*! \brief      Registers a repeater proxy.
 *  \param[in]  proxyId                     Id of the proxy caller.
 *  \param[in]  pProxy                      Function pointer of the polling processor
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_RegisterRepeaterProxy(Dcm_RepeaterProxyFuncType pProxy)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurContextId();

  dcmRepeatedProxyCallBack[lContext] = pProxy;
  /* Set event */
  Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(lContext), DCM_EVENT_STATE_TASK_PROXY);
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ Internal implementation
 ----------------------------------------------------------------------------- */

#define DCM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (DCM_EXT_CRITICAL_SEC_MGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_EnterCriticalSection
 **********************************************************************************************************************/
/*! \brief      Unlocks the interrupts for critical section
 *  \context    Function could be called from interrupt level or from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_EnterCriticalSection(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EnterCritical();
}
#endif

#if (DCM_EXT_CRITICAL_SEC_MGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_LeaveCriticalSection
 **********************************************************************************************************************/
/*! \brief      Unlocks the interrupts for critical section
 *  \context    Function could be called from interrupt level or from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_LeaveCriticalSection(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_LeaveCritical();
}
#endif

#if (DCM_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  Dcm_GetVersionInfo
 **********************************************************************************************************************/
/*! \brief      Reports  component's version information
 *  \param[out] versioninfo             pointer to the application structure
 *  \context    Function could be called from interrupt level or from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  versioninfo->vendorID = DCM_VENDOR_ID;
  versioninfo->moduleID = DCM_MODULE_ID;
  versioninfo->instanceID = 0;
  versioninfo->sw_major_version = DCM_SW_MAJOR_VERSION;
  versioninfo->sw_minor_version = DCM_SW_MINOR_VERSION;
  versioninfo->sw_patch_version = DCM_SW_PATCH_VERSION;
}
#endif

/***********************************************************************************************************************
 *  Dcm_Uint8LookUp
 **********************************************************************************************************************/
/*! \brief      Searches a byte table for an element.
 *  \param[in]  variantTable            Variant table for this look up run, if NULL_PTR -> no variant selection required
 *  \param[in]  lookUpTable             Value to be found (one byte)
 *  \param[in]  value                   Pointer to the tabel to be scanned
 *  \return     Returns the position of found item
 *  \retval     0  - look up failed (no match)
 *  \retval     >0 - success, index of the matched position
 *  \pre        Table pointer must not be NULL_PTR.
 *  \context    Function could be called from interrupt level or from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
#if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
STATIC FUNC(uint8_least, DCM_CODE) Dcm_Uint8LookUp(Dcm_CfgVariantTablePtrType variantTable, CONSTP2CONST(uint8, AUTOMATIC, DCM_CONST) lookUpTable, uint8 value)
#else
STATIC FUNC(uint8_least, DCM_CODE) Dcm_Uint8LookUp(CONSTP2CONST(uint8, AUTOMATIC, DCM_CONST) lookUpTable, uint8 value)
#endif
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least iter = lookUpTable[0];/* very first key is the size of array */
  while((iter != 0)&&(lookUpTable[iter] != value))
  {
    iter--;
  }
#if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
  /* has variants ? */
  if(variantTable != NULL_PTR)
  {
    if((variantTable[iter] & dcmStateMachine.CfgVariantMask) == 0)
    {
      /* not supported in the variant */
      iter = 0;
    }
  }
#endif
  return iter;
}

#if (DCM_COPY_RAM2RAM_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_CopyRam2Ram
 **********************************************************************************************************************/
/*! \brief      Copies data from one RAM location to another.
 *  \param[in]  in                      Start RAM-address of the source location
 *  \param[in]  in                      Number of bytes to be copied
 *  \param[out] inOut                   Start RAM-address of the target location
 *  \pre        None of the pointers must be NULL_PTR.
 *  \context    Function could be called from interrupt level or from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_CopyRam2Ram(Dcm_ApplDataPtrType tgtAddr, Dcm_ApplDataPtrType srcAddr, uint16_least len) /* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  while(len != 0)
  {
    len--;
    tgtAddr[len]= srcAddr[len];
  }
}
#endif

#if (DCM_COPY_ROM2RAM_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_CopyRom2Ram
 **********************************************************************************************************************/
/*! \brief      Copies data from a ROM location to RAM.
 *  \param[in]  in                      Start ROM-address of the source location
 *  \param[in]  in                      Number of bytes to be copied
 *  \param[out] inOut                   Start RAM-address of the target location
 *  \pre        None of the pointers must be NULL_PTR.
 *  \context    Function could be called from interrupt level or from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_CopyRom2Ram(Dcm_ApplDataPtrType tgtAddr, Dcm_ApplConstDataPtrType srcAddr, uint16_least len)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  while(len != 0)
  {
    len--;
    tgtAddr[len]= srcAddr[len];
  }
}
#endif

/***********************************************************************************************************************
 *  Dcm_MsgContextMoveRel
 **********************************************************************************************************************/
/*! \brief      Consistent movement over the message context
 *  \param[in]  reqSteps      Request position offset (-n or +n)
 *  \param[in]  resSteps      Response position offset (-k or +k)
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_MsgContextMoveRel(sint32_least reqSteps, sint32_least resSteps)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurContextId();

  Dcm_StateCheckValueRangeFailed( (((sint32_least)((uint32_least)dcmDsdMsgContext[lContext].reqDataLen) - reqSteps) >= 0), DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  Dcm_StateCheckValueRangeFailed( (((sint32_least)((uint32_least)dcmDsdMsgContext[lContext].resDataLen) + resSteps) >= 0), DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  Dcm_StateCheckValueRangeFailed( (((sint32_least)((uint32_least)dcmDsdMsgContext[lContext].resMaxDataLen) - resSteps) >= 0), DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  dcmDsdMsgContext[lContext].reqData         = &dcmDsdMsgContext[lContext].reqData[reqSteps];
  dcmDsdMsgContext[lContext].reqDataLen      = (Dcm_MsgLenType)(dcmDsdMsgContext[lContext].reqDataLen - reqSteps);
  dcmDsdMsgContext[lContext].resData         = &dcmDsdMsgContext[lContext].resData[resSteps];
  dcmDsdMsgContext[lContext].resDataLen      = (Dcm_MsgLenType)(dcmDsdMsgContext[lContext].resDataLen + resSteps);
  dcmDsdMsgContext[lContext].resMaxDataLen   = (Dcm_MsgLenType)(dcmDsdMsgContext[lContext].resMaxDataLen - resSteps);
}

/***********************************************************************************************************************
 *  Dcm_EvMgrSetEvent
 **********************************************************************************************************************/
/*! \brief      Set new event(s) to a task.
 *  \param[in]  taskId                        Task Id
 *  \param[in]  ev                            Event(s) to be set
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_EvMgrSetEvent(Dcm_TaskIdType taskId, Dcm_EventType ev)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EnterCritical();
  if(dcmEvMgrEventRegisters[taskId] == 0)
  {
    dcmEvMgrNumActiveTasks++;
  }
  dcmEvMgrEventRegisters[taskId] |= ev;
  Dcm_LeaveCritical();
}

/***********************************************************************************************************************
 *  Dcm_EvMgrClearEvent
 **********************************************************************************************************************/
/*! \brief      Clear event(s) of a task.
 *  \param[in]  taskId                        Task Id
 *  \param[in]  ev                            Event(s) to be cleared
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_EvMgrClearEvent(Dcm_TaskIdType taskId, Dcm_EventType ev)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EnterCritical();
  /* Clear event */
  dcmEvMgrEventRegisters[taskId] &= (Dcm_EventType)(~ev);
  if(dcmEvMgrEventRegisters[taskId] == 0)
  {
    dcmEvMgrNumActiveTasks--;
  }
  Dcm_LeaveCritical();
}

/***********************************************************************************************************************
 *  Dcm_TimerTask
 **********************************************************************************************************************/
/*! \brief      Provides the timing management of DCM.
 *              Could be used together with Dcm_StateTask() to achive best 
 *              CPU utilization by splitting the timing management from the job processing.
 *  \pre        DCM must be initialized.
 *  \context    Function can be called from a higher priority task level to achive better timing accuracy.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_TimerTask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_MainFunction);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

 /* DSL TIMER */
  if(dcmActiveTimerCounter != 0)
  {
    Dcm_TimerEventType tmrTo = 0;
    Dcm_TimerEventType tmrShift = (Dcm_TimerEventType)(0x01 << (DCM_NUM_TIMERS - 1));
    Dcm_TimerIdType    iter = DCM_NUM_TIMERS;

    /* enter critical section */
    Dcm_EnterCritical();
    while(iter != 0)
    {
      iter--;
      if(dcmTimerEngine[iter] != 0)
      {
        dcmTimerEngine[iter]--;
        if(dcmTimerEngine[iter] == 0)
        {
          /* Unregister timer */
          dcmActiveTimerCounter--;
          /* Set timeout */
          tmrTo |= tmrShift;
        }
      }
      tmrShift>>=1;
    }
    /* leave critical section */
    Dcm_LeaveCritical();

    /* iter = 0; already counted down to 0! */
    while(tmrTo != 0)
    {
      /* check for timeout */
      if((tmrTo & 0x01) != 0)
      {
        /* Notify the application */
        dcmTimerManagerInfo[iter](iter);
      }
      iter++;
      /* Get next timer */
      tmrTo >>=1;
    }
  }

  Dcm_DslLL_TimerTask();
}

/***********************************************************************************************************************
 *  Dcm_TmrMgrStartTimer
 **********************************************************************************************************************/
/*! \brief      Starts a timer.
 *  \param[in]  timerId                        Timer Id
 *  \param[in]  ticks                          Timer cycles
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrStartTimer(Dcm_TimerIdType timerId, Dcm_TimerCounterType ticks)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EnterCritical();
  Dcm_TmrMgrNotSafeStartTimer(timerId, ticks);
  Dcm_LeaveCritical();
}

/***********************************************************************************************************************
 *  Dcm_TmrMgrNotSafeStartTimer
 **********************************************************************************************************************/
/*! \brief      Starts a timer without consistency protection.
 *  \param[in]  timerId                        Timer Id
 *  \param[in]  ticks                          Timer cycles
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrNotSafeStartTimer(Dcm_TimerIdType timerId, Dcm_TimerCounterType ticks)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  if((dcmTimerEngine[timerId] == 0) &&
     (ticks != 0))
  {
    dcmActiveTimerCounter++;
  }
  dcmTimerEngine[timerId] = ticks;
}

#if (DCM_RESTART_TIMER_USAGE_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_TmrMgrRestartTimer
 **********************************************************************************************************************/
/*! \brief      ReStarts a timer if already running.
 *  \param[in]  timerId                        Timer Id
 *  \param[in]  ticks                          Timer cycles
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrRestartTimer(Dcm_TimerIdType timerId, Dcm_TimerCounterType ticks)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EnterCritical();
  if(dcmTimerEngine[timerId] != 0)
  {
    Dcm_TmrMgrNotSafeStartTimer(timerId, ticks);
  }
  Dcm_LeaveCritical();
}
#endif

/***********************************************************************************************************************
 *  Dcm_TmrMgrStopTimer
 **********************************************************************************************************************/
/*! \brief      Stops a timer.
 *  \param[in]  timerId                        Timer Id
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrStopTimer(Dcm_TimerIdType timerId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EnterCritical();
  Dcm_TmrMgrNotSafeStopTimer(timerId);
  Dcm_LeaveCritical();
}

/***********************************************************************************************************************
 *  Dcm_TmrMgrNotSafeStopTimer
 **********************************************************************************************************************/
/*! \brief      Stops a timer without consistency protection.
 *  \param[in]  timerId                        Timer Id
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_TmrMgrNotSafeStopTimer(Dcm_TimerIdType timerId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  if((dcmActiveTimerCounter   != 0)&&
     (dcmTimerEngine[timerId] != 0))
  {
    dcmActiveTimerCounter--;
  }
  dcmTimerEngine[timerId] = 0;
}


#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_StartPagedProcessing
 **********************************************************************************************************************/
/*! \brief      Initiates PB processing.
 *  \param[in]  clientId                   Paged Buffer client ID.
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_StartPagedProcessing(Dcm_PagedBufferClientType clientId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurContextId();

  Dcm_CheckDcmInit(DcmServiceId_StartPagedProcessing);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  Dcm_EnterCritical();
  if ( ((dcmDsdMsgContext[lContext].msgAddInfo & DCM_MSGADDINFO_SUPP_POS_RES) != 0)
    && (dcmDslInfoPool[lContext].rcrRpState == DSL_RES_TYPE_NONE) )
  {
    /* Request 'SuppressResponse' and no RCR-RP has been sent */
    /* We must stop the P2 timer here, else a timeout can cause an RCR-RP response before processing is finalized */
    Dcm_TmrMgrNotSafeStopTimer(DCM_CONTEXT_P2_TIMER_ID(lContext));
    Dcm_LeaveCritical();

    /* Invalidate SPRMIB = 1 -> send RCR-RP, wait that it has been sent*/
    Dcm_SendResponsePending(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(lContext) DSL_RES_TYPE_RCRRP_INT);
  }
  else
  {
    /* no SuppressResponse or a RRC-RP has already been attempted */
    Dcm_LeaveCritical();
  }

  /* Make at the same time a send request. DCM core will wait until the RCR RP response is sent and then process the 
   * Paged buffer response immediately.
   */

  /* if final response can not be sent on this bus -> reject service */
  if(dcmDsdMsgContext[lContext].resDataLen > dcmDslInfoPool[lContext].maxBusPayloadLength)
  {
    /* Processing done catches this case and sets the NRC to 0x14 */
    Dcm_ProcessingDone();
  }
  else
  {
    /* Compose response header */
    Dcm_AddValue(dcmDslInfoPool[lContext].dataPtr[0] , Dcm_MsgItemType, 0x40);
    dcmDslInfoPool[lContext].dataLength = dcmDsdMsgContext[lContext].resDataLen;

    /* Init paged buffer engine */
    {
      dcmPBStateMachine[lContext].isPagedBufferActive  = 1;
      dcmPBStateMachine[lContext].isPagedTxStarted     = 0;
      dcmPBStateMachine[lContext].isDataRequested      = 0;
      dcmPBStateMachine[lContext].readIdx              = 0;
      dcmPBStateMachine[lContext].pageSize             = 1;/* For the SID */
      dcmPBStateMachine[lContext].clientId             = (Dcm_MemPagedBufferClientType)clientId;
      dcmPBStateMachine[lContext].remainingData = (Dcm_MsgLenType)(dcmDslInfoPool[lContext].dataLength - 1);
    }

    Dsd_PagedBufferDataRequest(DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(lContext));
  }
}

/***********************************************************************************************************************
 *  Dcm_ProcessPage
 **********************************************************************************************************************/
/*! \brief      Acknowledge for processed page.
 *  \param[in]  FilledPageLen                   Current paged buffer copied data length.
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_ProcessPage(uint16 FilledPageLen)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurContextId();

  Dcm_CheckDcmInit(DcmServiceId_ProcessPage);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  Dcm_StateCheckValueRangeFailed((dcmPBStateMachine[lContext].remainingData  >= FilledPageLen), DcmServiceId_ProcessPage); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  Dcm_EnterCritical();
  Dcm_SubValue(dcmPBStateMachine[lContext].remainingData , Dcm_MsgLenType, FilledPageLen);
  Dcm_AddValue(dcmPBStateMachine[lContext].pageSize , Dcm_MsgLenType, FilledPageLen);
  dcmPBStateMachine[lContext].isDataRequested = 0;
  Dcm_LeaveCritical();

  if(dcmPBStateMachine[lContext].isPagedTxStarted == 0)
  {
    dcmPBStateMachine[lContext].isPagedTxStarted = 1;
    Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(lContext), DCM_EVENT_SEND_PAGED_RES);
  }
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
#if (DCM_PDUROUTER_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslLL_ReleaseRxResource
 **********************************************************************************************************************/
/*! \brief      Releases all request resources object.
 *  \param[in]  connId        The RxPduID of the transport object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_DslLL_ReleaseRxResource(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduRxTransportInfoPtrType pRxTranspObj = Dcm_DslLL_TObjGetRxByConnId(connId);
  /* A transport object must exist */
  Dcm_StateCheckValueRangeFailed((pRxTranspObj != NULL_PTR), DcmServiceId_ReleaseResource); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
  pRxTranspObj->base.isReserved = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE_WRAP_INDEX(pRxTranspObj->base.iContext)].isConnectionLocked; /* PRQA S 0505 */ /* QAC 7.0:  [U] Dereferencing pointer value that is apparently NULL. */ /* If NULL, DCM reaches point of no return! */
# endif
  Dcm_DslLL_TObjFree(&(pRxTranspObj->base));  /* PRQA S 0505 */ /* QAC 7.0:  [U] Dereferencing pointer value that is apparently NULL. */ /* If NULL, DCM reaches point of no return! */
}

/***********************************************************************************************************************
 *  Dcm_DslLL_TObjAllocRxByConnId
 **********************************************************************************************************************/
/*! \brief      Allocates a transport object.
 *  \param[in]  connId   The RxPduId specific ConnId to which the transport object will be assigned
 *  \return     Dcm_PduTransportInfoPtrType     Pointer to a free transport object
 *  \retval     >0 - valid object
 *  \retval     NULL_PTR  - failed to find any free object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_PduRxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjAllocRxByConnId(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduRxTransportInfoPtrType pRxTranspObj;

# if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL
# endif

# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_NUM_CONTEXTS > 1)
  Dcm_MsgType pDataBuffer;
# endif

# if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT;
# endif

# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_NUM_CONTEXTS > 1)
#  if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  pDataBuffer = &dcmPduTransportBuffer[0];
#  else
  pDataBuffer = &dcmPduTransportBuffer[connId*DCM_DSL_CONCUR_BUFF_SIZE_CONST];
#  endif
# endif
# if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  pRxTranspObj = &dcmPduRxTransportInfo[0];
# else
  pRxTranspObj = &dcmPduRxTransportInfo[connId];
# endif

# if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  DCM_TRANSP_OBJ_HNDL_ITER_LOOP
  {
    DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC;
# endif
    if(DCM_PDU_TX_STATE_FREE == pRxTranspObj->base.state)
    {
      pRxTranspObj->base.state = DCM_PDU_TX_STATE_INIT;
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_NUM_CONTEXTS > 1)
      pRxTranspObj->base.pduInfo.SduDataPtr = pDataBuffer;
      pRxTranspObj->base.pduInfo.SduLength  = DCM_DSL_CONCUR_BUFF_SIZE_CONST;
# endif
      pRxTranspObj->base.connId = connId;
# if (DCM_NUM_CONTEXTS > 1)
      pRxTranspObj->tempBuffer = pDataBuffer;
# endif
      return pRxTranspObj;
    }
# if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
#  if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
      (DCM_NUM_CONTEXTS > 1)
    /* Calculate next buffer */
    pDataBuffer = &pDataBuffer[DCM_DSL_CONCUR_BUFF_SIZE_CONST];
#  endif
    ++pRxTranspObj; /* PRQA S 0489 */ /* QAC 7.0: Increment or decrement operation performed on pointer.*/ /* Better readability */
  }
# endif
  return NULL_PTR;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslLL_TObjAllocTxByConnId
 **********************************************************************************************************************/
/*! \brief      Allocates a transport object.
 *  \param[in]  connId   The RxPduId specific ConnId to which the transport object will be assigned
 *  \return     Dcm_PduTxTransportInfoPtrType     Pointer to a free transport object
 *  \retval     >0 - valid object
 *  \retval     NULL_PTR  - failed to find any free object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjAllocTxByConnId(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduTxTransportInfoPtrType pTxTranspObj;

#  if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  Dcm_PduTxTransportInfoPtrType pTempTxTranspObj;
  DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL

  pTxTranspObj = NULL_PTR;

  Dcm_EnterCritical();
  if (dcmSemaphoreAllocateTx != DCM_SEMAPHORE_ALLOCATE_TX_FREE)
  {
    /* Function called reentrant. The second caller loses the race. */
    Dcm_LeaveCritical();
    return NULL_PTR;
  }
  else
  {
    dcmSemaphoreAllocateTx = DCM_SEMAPHORE_ALLOCATE_TX_LOCKED;
  }
  Dcm_LeaveCritical();

  pTempTxTranspObj = dcmPduTxTransportInfo;

  DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT;
  DCM_TRANSP_OBJ_HNDL_ITER_LOOP
  {
    DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC;

    if(DCM_PDU_TX_STATE_FREE != pTempTxTranspObj->base.state)
    {
      if(pTempTxTranspObj->base.connId == connId)
      {
        dcmSemaphoreAllocateTx = DCM_SEMAPHORE_ALLOCATE_TX_FREE;
        return NULL_PTR; /* Connection already in use */
      }
    }
    else
    {
      /* Store temporary a potential free place */
      pTxTranspObj = pTempTxTranspObj;
    }
    ++pTempTxTranspObj; /* PRQA S 0489 */ /* QAC 7.0: Increment or decrement operation performed on pointer.*/ /* Better readability */
  }

  if(NULL_PTR != pTxTranspObj)
  {
    pTxTranspObj->base.state = DCM_PDU_TX_STATE_INIT;
    pTxTranspObj->base.connId = connId;
  }

  dcmSemaphoreAllocateTx = DCM_SEMAPHORE_ALLOCATE_TX_FREE;

#  else /* ... static transport object assignment */
  pTxTranspObj = &dcmPduTxTransportInfo[connId];

  Dcm_EnterCritical();
  if(DCM_PDU_TX_STATE_FREE == pTxTranspObj->base.state)
  {
    /* Store temporary a potential free place */
    pTxTranspObj->base.state = DCM_PDU_TX_STATE_INIT;
    pTxTranspObj->base.connId = connId;
  }
  else
  {
    pTxTranspObj = NULL_PTR;
  }
  Dcm_LeaveCritical();
#  endif

  return pTxTranspObj;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslLL_TObjAllocTxByRxTObj
 **********************************************************************************************************************/
/*! \brief      Allocates a transport object.
 *  \param[in]  connId   The RxPduId specific ConnId to which the transport object will be assigned
 *  \return     Dcm_PduTxTransportInfoPtrType     Pointer to a free transport object
 *  \retval     >0 - valid object
 *  \retval     NULL_PTR  - failed to find any free object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjAllocTxByRxTObj(Dcm_PduRxTransportInfoPtrType pRxTranspObj) /* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* Avoiding problems with embedded compilers. */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduTxTransportInfoPtrType pTxTranspObj;
  pTxTranspObj = Dcm_DslLL_TObjAllocTxByConnId(pRxTranspObj->base.connId);

  if(pTxTranspObj != NULL_PTR)
  {
    pTxTranspObj->base = pRxTranspObj->base;
  }
  return pTxTranspObj;
}
# endif

/***********************************************************************************************************************
 *  Dcm_DslLL_TObjGetRxByConnId
 **********************************************************************************************************************/
/*! \brief      Returns a transport object handle if the ConnectionId is already in use.
 *  \param[in]  DcmConnId     Connection Id
 *  \return     Operation result
 *  \retval     >0       - valid object
 *  \retval     NULL_PTR - failed to find any object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_PduRxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetRxByConnId(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduRxTransportInfoPtrType pRxTranspObj;

# if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL

  DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT;

  pRxTranspObj = dcmPduRxTransportInfo;

  DCM_TRANSP_OBJ_HNDL_ITER_LOOP
  {
    DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC;
    if(DCM_PDU_TX_STATE_FREE != pRxTranspObj->base.state)
    {
      if(connId == pRxTranspObj->base.connId)
      {
        return pRxTranspObj;
      }
    }
    ++pRxTranspObj; /* PRQA S 0489 */ /* QAC 7.0: Increment or decrement operation performed on pointer.*/ /* Better readability */
  }
# else
  pRxTranspObj = &dcmPduRxTransportInfo[connId];
  if(DCM_PDU_TX_STATE_FREE != pRxTranspObj->base.state)
  {
    return pRxTranspObj;
  }
# endif
  return NULL_PTR;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DslLL_TObjGetTxByConnId
 **********************************************************************************************************************/
/*! \brief      Returns a transport object handle if the ConnectionId is already in use.
 *  \param[in]  DcmConnId     Connection Id
 *  \return     Operation result
 *  \retval     >0       - valid object
 *  \retval     NULL_PTR - failed to find any object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetTxByConnId(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduTxTransportInfoPtrType pTxTranspObj;

# if (DCM_DSL_DYN_CONN2TRANSP_ALLOC_ENABLED == STD_ON)
  DCM_TRANSP_OBJ_HNDL_ITER_DEF_LOCAL

  DCM_TRANSP_OBJ_HNDL_ITER_VALUE_INIT;

  pTxTranspObj = dcmPduTxTransportInfo;

  DCM_TRANSP_OBJ_HNDL_ITER_LOOP
  {
    DCM_TRANSP_OBJ_HNDL_ITER_VALUE_DEC;
    if(DCM_PDU_TX_STATE_FREE != pTxTranspObj->base.state)
    {
      if(connId == pTxTranspObj->base.connId)
      {
        return pTxTranspObj;
      }
    }
    ++pTxTranspObj;/* PRQA S 0489 */ /* QAC 7.0: Increment or decrement operation performed on pointer.*/ /* Better readability */
  }
# else
  pTxTranspObj = &dcmPduTxTransportInfo[connId];
  if(DCM_PDU_TX_STATE_FREE != pTxTranspObj->base.state)
  {
    return pTxTranspObj;
  }
# endif
  return NULL_PTR;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DslLL_TObjGetTxByTxPduId
 **********************************************************************************************************************/
/*! \brief      Returns a transport object handle if the TxPduId is already in use.
 *  \param[in]  DcmTxPduId     TxPduId
 *  \return     Operation result
 *  \retval     >0       - valid object
 *  \retval     NULL_PTR - failed to find any object
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_PduTxTransportInfoPtrType, DCM_CODE) Dcm_DslLL_TObjGetTxByTxPduId(PduIdType DcmTxPduId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  return Dcm_DslLL_TObjGetTxByConnId(dcmTxPduToConnTable[DcmTxPduId]);
}

/***********************************************************************************************************************
 *  Dcm_DslLL_StartTransmission
 **********************************************************************************************************************/
/*! \brief      LowLevel transmit routine
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_DslLL_StartTransmission(DCM_CONTEXT_PARAM_DEF_ONLY)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  PduIdType lDcmTxPduId;
  Dcm_PduTxTransportInfoPtrType pTxTranspObj;
# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
  Dcm_PduRxTransportInfoPtrType pRxTranspObj;


  pRxTranspObj = Dcm_DslLL_TObjGetRxByConnId(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dslHandle);
  Dcm_StateCheckValueRangeFailed((pRxTranspObj != NULL_PTR), DcmServiceId_SendResponse); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  pTxTranspObj = Dcm_DslLL_TObjAllocTxByRxTObj(pRxTranspObj); /* PRQA S 0505 */ /* QAC 7.0:  [U] Dereferencing pointer value that is apparently NULL. */ /* If NULL, DCM reaches point of no return! */
# else
  pTxTranspObj = Dcm_DslLL_TObjGetTxByConnId(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dslHandle);
# endif

# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
  /* A transport object must exist */
  if(pTxTranspObj == NULL_PTR)
  {
    Dcm_EventType resendEv = DCM_EVENT_DO_RETRY_TX_ALLOC_UDS;
#  if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
      (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
    if(DCM_CONTEXT_PARAM_VALUE != DCM_CONTEXT_ID_UDS)
    {
      resendEv = DCM_EVENT_DO_RETRY_TX_ALLOC_OBD;
    }
#  endif

    Dcm_EvMgrSetEvent(DCM_TASK_ID_DSL_LL_STATE, resendEv);
    return;
  }
# else
  /* Must exist */
  Dcm_StateCheckValueRangeFailed((pTxTranspObj != NULL_PTR), DcmServiceId_SendResponse); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
# endif

  lDcmTxPduId = dcmDslPduConnectionInfoTable[pTxTranspObj->base.connId].mainTxPduId; /* PRQA S 0505 */ /* QAC 7.0:  [U] Dereferencing pointer value that is apparently NULL. */ /* If NULL, DCM reaches point of no return! */

  /* Only if full communication is active may send */
  if(dcmStateMachine.CommState == DCM_COMM_STATE_FULL)
  {
    if((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType & DSL_RES_TYPE_RCRRP_ANY) != 0)
    {
      /* Copy bus info type of the request */
      pTxTranspObj->base.pduInfo.SduDataPtr = dcmDslBufferRcrRpTx[DCM_CONTEXT_PARAM_VALUE];/* PRQA S 0505 */ /* QAC 7.0:  [U] Dereferencing pointer value that is apparently NULL. */ /* If NULL, DCM reaches point of no return! */
      pTxTranspObj->base.pduInfo.SduLength  = 3u;
    }
    else
    {
      /* Only final response can be here */
      Dcm_StateCheckValueRangeFailed(((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType & (DSL_RES_TYPE_FINAL | DSL_RES_TYPE_SPONTANEOUS)) != 0), DcmServiceId_SendResponse); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

      pTxTranspObj->base.pduInfo.SduDataPtr = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataPtr;
      pTxTranspObj->base.pduInfo.SduLength  = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dataLength;
    }
    /* Start immediate sending */
    pTxTranspObj->base.state = DCM_PDU_TX_STATE_ON_TX;
    stdReturn= PduR_DcmTransmit(lDcmTxPduId, &pTxTranspObj->base.pduInfo);

    if(!Dcm_DslLL_IsPduRTxAccepted(stdReturn))
    {
      pTxTranspObj->base.state = DCM_PDU_TX_STATE_DO_SEND;
      Dcm_EvMgrSetEvent(DCM_TASK_ID_DSL_LL_STATE, DCM_EVENT_DO_SEND);
    }
  }
  else
  {
    /* may not send - finalize */
    Dcm_TxConfirmation(lDcmTxPduId, NTFRSLT_E_NOT_OK);
  }
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

# if (DCM_PDUR_PERIODIC_TX_TYPE2_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_TriggerTransmit
 **********************************************************************************************************************/
/*! \brief      Copies application data into the FlexRay message buffer
 *  \param[in]  FrTxPduId                 The TxPduId on the current response transmission
 *  \param[out] FrSduPtr                  Pointer to the FlexRayBuffer to copy to.
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_TriggerTransmit(PduIdType FrTxPduId, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) FrSduPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduTxTransportInfoPtrType pTxTranspObj = Dcm_DslLL_TObjGetTxByTxPduId(FrTxPduId);

  Dcm_CheckDcmInit(DcmServiceId_TriggerTransmit);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  DCM_IGNORE_UNREF_PARAM(FrTxPduId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_CopyRam2Ram(FrSduPtr, pTxTranspObj->base.pduInfo.SduDataPtr, pTxTranspObj->base.pduInfo.SduLength);
}
# endif

/***********************************************************************************************************************
 *  Dcm_ProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief      Dispatches the response data copy processing.
 *  \param[in]  DcmTxPduId                The TxPduId on the current response transmission
 *  \param[in]  Length                    The required data length from the lower layer (shall be 0)
 *  \param[out] PduInfoPtr                Pointer to the chunk data pointer and current chunk length
 *  \return     Operation result
 *  \retval     0 - BUFREQ_OK
 *  \retval     >0 - failed for some reason
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideTxBuffer(PduIdType DcmTxPduId, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  BufReq_ReturnType  lResult = BUFREQ_E_NOT_OK;
  Dcm_PduTxTransportInfoPtrType pTxTranspObj = Dcm_DslLL_TObjGetTxByTxPduId(DcmTxPduId);

  DCM_IGNORE_UNREF_PARAM(DcmTxPduId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  if(pTxTranspObj != NULL_PTR)
  {
    /* Delegate this call */
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
    if(DCM_DSL_TOBJ_KIND_MAIN == pTxTranspObj->base.kind)
# endif
    {
      lResult = Dcm_MainProvideTxBuffer(pTxTranspObj, PduInfoPtr, Length);
    }
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
    else if(DCM_DSL_TOBJ_KIND_CONCUR == pTxTranspObj->base.kind)
    {
      lResult = Dcm_ConcurProvideTxBuffer(pTxTranspObj, PduInfoPtr, Length);
    }
# endif
# if ((DCM_SERVICE_2A_ENABLED == STD_ON) && (DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON))
    else
    {
      /* Only 0x2A has no transport object, try its API */
      lResult = Dcm_PruProvideTxBuffer(pTxTranspObj, PduInfoPtr, Length);
    }
# endif
  }
  return lResult;
}

/***********************************************************************************************************************
 *  Dcm_TxConfirmation
 **********************************************************************************************************************/
/*! \brief      Transmission end notification
 *  \param[in]  DcmTxPduId                The TxPduId on the current response transmission
 *  \param[in]  Result                    Transmission result
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_TxConfirmation(PduIdType DcmTxPduId, NotifResultType Result)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_SERVICE_2A_ENABLED == STD_ON) || \
     (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_NUM_CONTEXTS > 1) || \
     (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
  Dcm_ConnectionRefType lConnId = dcmTxPduToConnTable[DcmTxPduId];
# endif

  DCM_IGNORE_UNREF_PARAM(DcmTxPduId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  /* Delegate this call */
# if ((DCM_SERVICE_2A_ENABLED == STD_ON) && (DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON))
  if(DcmTxPduId == dcmDslPduConnectionInfoTable[lConnId].mainTxPduId)
# endif
  {
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_NUM_CONTEXTS > 1) || \
     (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
    Dcm_PduTxTransportInfoPtrType pTxTranspObj = Dcm_DslLL_TObjGetTxByConnId(lConnId);

    if(pTxTranspObj != NULL_PTR)
# endif
    {
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
      if(DCM_DSL_TOBJ_KIND_MAIN == pTxTranspObj->base.kind)
# endif
      {
        Dcm_DslHL_TransmissionFinished(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(pTxTranspObj->base.iContext) (Dcm_DslCommStatusType)((Result == NTFRSLT_OK)?DSL_COMM_E_OK:DSL_COMM_E_NOT_OK));
      }
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
      else if(DCM_DSL_TOBJ_KIND_CONCUR == pTxTranspObj->base.kind)
      {
        /* Release always */
        Dcm_DslLL_TObjFree(&(pTxTranspObj->base));
      }
# endif
# if ((DCM_SERVICE_2A_ENABLED == STD_ON) && (DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON))
      else /* if(DCM_DSL_TOBJ_KIND_PERIODIC == pTxTranspObj->base.kind) */
      {
        Dcm_PruTxConfirmation(DcmTxPduId, Result);
      }
# endif
# if (DCM_DSL_SHARED_TX_CONN_ENABLED == STD_ON)
      /* Release always since any transmission allocates it again */
      Dcm_DslLL_TObjFree(&(pTxTranspObj->base));
# endif
    }
  }
# if ((DCM_SERVICE_2A_ENABLED == STD_ON) && (DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON))
  else
  {
    Dcm_PruTxConfirmation(DcmTxPduId, Result);
  }
# endif
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_ProvideRxBuffer
 **********************************************************************************************************************/
/*! \brief      Request reception data manager
 *  \param[in]  DcmRxPduId                The RxPduId on the current request transmission
 *  \param[in]  TpSduLength               The required data length from the lower layer 
 *  \param[out] PduInfoPtr                Pointer to the request buffer pointer and buffer size
 *  \return     Operation result
 *  \retval     0 - BUFREQ_OK
 *  \retval     >0 - failed for some reason
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideRxBuffer(PduIdType DcmRxPduId, PduLengthType TpSduLength, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  BufReq_ReturnType result = BUFREQ_E_NOT_OK;
  Dcm_PduRxTransportInfoPtrType pRxTranspObj;
  Dcm_ConnectionRefType lConnId;

  *PduInfoPtr = NULL_PTR;
  lConnId = DcmDslRxPdu2ConnMap(DcmRxPduId,DCM_COMVARIANT_ID_VALUE);


  /* Must have an assigned connection */
  Dcm_CheckApiValueRangeFailed(lConnId < DCM_CONNECTION_ID_INVALID, DcmServiceId_ProvideRxBuffer); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON) || \
     (DCM_DSL_REQUEST_PREFETCH_ENABLED == STD_ON)
  /* For the second and further iterations of this function - do not allocated, but check if already allocated and proceed with the same object */
  pRxTranspObj = Dcm_DslLL_TObjGetRxByConnId(lConnId);

  if(NULL_PTR == pRxTranspObj)
# endif
  {
    pRxTranspObj = Dcm_DslLL_TObjAllocRxByConnId(lConnId);
  }

  if(pRxTranspObj != NULL_PTR)
  {
    *PduInfoPtr = &pRxTranspObj->base.pduInfo;
    /* first/next data portion will be provided */
    switch(pRxTranspObj->base.state)
    {
# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
      /*----------------------------*/
      case DCM_PDU_TX_STATE_RESERVED:
      /*----------------------------*/
        /* use the reserved object */
#  if(DCM_NUM_CONTEXTS > 1)
        /* must again assign the temp buffer */
        pRxTranspObj->base.pduInfo.SduDataPtr = pRxTranspObj->tempBuffer;
        pRxTranspObj->base.pduInfo.SduLength  = DCM_DSL_CONCUR_BUFF_SIZE_CONST;
#  endif
# endif
      /*----------------------------*/
      case DCM_PDU_TX_STATE_INIT:  /* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* fall through on reserved objects */
      /*----------------------------*/
        if(TpSduLength > dcmDslPduProtocolInfoTable[0].mainBufferSize)
        {
          Dcm_DslLL_TObjFree(&(pRxTranspObj->base));
          result = BUFREQ_E_OVFL;
          break; /* PRQA S 3333 */ /* QAC 7.0: A break statement is being used to exit from a switch case block but is not the final statement in the block. */ /* Optimization */
        }
        pRxTranspObj->rxPduId = DcmRxPduId;
        pRxTranspObj->totalRequestLength = TpSduLength;
# if(DCM_DSL_REQUEST_PREFETCH_ENABLED == STD_ON)
        pRxTranspObj->base.state = DCM_PDU_TX_STATE_PREFETCH;
        result = BUFREQ_OK;
        break;
      /*----------------------------*/
      case DCM_PDU_TX_STATE_PREFETCH:
      /*----------------------------*/
        if(pRxTranspObj->rxPduId == DcmRxPduId) /* consider parallel requests (e.g. functional to a multi-frame physical) of the same connection */
        {
          pRxTranspObj->sid = pRxTranspObj->base.pduInfo.SduDataPtr[0];
# endif
          /* try to get free context */
          result = Dcm_ProvideContext(pRxTranspObj);
          if(BUFREQ_OK != result)
          {
            Dcm_DslLL_TObjFree(&(pRxTranspObj->base));
          }
# if(DCM_DSL_REQUEST_PREFETCH_ENABLED == STD_ON)
        }
# endif
        break;
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
#  if(DCM_DSL_REQUEST_PREFETCH_ENABLED == STD_ON)
        /* SID already copied in the DoDispatchContext API */
#  else
      /*----------------------------*/
      case DCM_PDU_TX_STATE_ON_RX_START:
      /*----------------------------*/
        if(pRxTranspObj->rxPduId == DcmRxPduId) /* consider parallel requests (e.g. functional to a multi-frame physical) of the same connection */
        {
          pRxTranspObj->sid = pRxTranspObj->base.pduInfo.SduDataPtr[0];
          pRxTranspObj->base.state = DCM_PDU_TX_STATE_ON_RX;
        }
#  endif
      /*----------------------------*/
      case DCM_PDU_TX_STATE_ON_RX: /* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* Fall through */
      /*----------------------------*/
        if(pRxTranspObj->rxPduId == DcmRxPduId) /* consider parallel requests (e.g. functional to a multi-frame physical) of the same connection */
        {
          /* continue data transfer - set the new buffer size */
          pRxTranspObj->base.pduInfo.SduLength = DCM_DSL_CONCUR_BUFF_SIZE_CONST;
          result = BUFREQ_OK;
        }
        break;
# endif
      /*----------------------------*/
      default:
      /*----------------------------*/
        /* The transport object is in use */
        break;/* return BUFREQ_NOT_OK; */
    }
  }
  return result;
}

/***********************************************************************************************************************
 *  Dcm_RxIndication
 **********************************************************************************************************************/
/*! \brief      Request reception data manager
 *  \param[in]  DcmRxPduId                The RxPduId on the current request transmission
 *  \param[in]  Result                    The reception result
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_RxIndication(PduIdType DcmRxPduId, NotifResultType Result)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_PduRxTransportInfoPtrType pRxTranspObj;

  pRxTranspObj = Dcm_DslLL_TObjGetRxByRxPduId(DcmRxPduId);

  /* a transport object for this ID must be allocated */
  if(NULL_PTR != pRxTranspObj)
  {
    if( pRxTranspObj->rxPduId == DcmRxPduId ) /* consider parallel requests (e.g. functional to a multi-frame physical) of the same connection */
    {
# if(DCM_DSL_REQUEST_PREFETCH_ENABLED == STD_ON)
      if(DCM_PDU_TX_STATE_PREFETCH == pRxTranspObj->base.state)
      {
        BufReq_ReturnType result;

        /* Copy prefetched data */
        pRxTranspObj->sid = pRxTranspObj->base.pduInfo.SduDataPtr[0];

        result = Dcm_ProvideContext(pRxTranspObj);
        if(BUFREQ_OK != result)
        {
          Dcm_DslLL_TObjFree(&(pRxTranspObj->base));
          return;
        }
      }
# endif
# if (DCM_DSL_PPRH_SUPPORT_ENABLED == STD_ON)
      if(DCM_DSL_TOBJ_KIND_CONCUR == pRxTranspObj->base.kind)
      {
        if(Result == NTFRSLT_OK)
        {
#  if(DCM_DSL_REQUEST_PREFETCH_ENABLED == STD_ON)
          /* SID already copied in the DoDispatchContext API */
#  else
          /* Check if buffer has not been overwritten (multiple calls of ProvideRxBuffer) */
          if(DCM_PDU_TX_STATE_ON_RX_START == pRxTranspObj->base.state)
          {
            pRxTranspObj->sid = pRxTranspObj->base.pduInfo.SduDataPtr[0];
          }
#  endif
          pRxTranspObj->base.state = DCM_PDU_TX_STATE_DO_SEND;
          Dcm_EvMgrSetEvent(DCM_TASK_ID_DSL_LL_STATE, DCM_EVENT_PPRH_DO_SEND);
        }
        else
        {
          Dcm_DslLL_TObjFree(&(pRxTranspObj->base));
        }
      }
      else
# endif
      {
        Dcm_DslHL_ReceptionFinished(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(pRxTranspObj->base.iContext) (Dcm_DslCommStatusType)((Result == NTFRSLT_OK)?DSL_COMM_E_OK:DSL_COMM_E_NOT_OK));
      }
    }
  }
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
#if ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  Dcm_PruMayProcessRequest
 **********************************************************************************************************************/
/*! \brief      Checks whether any DCM context has something to do.
 *  \return     Current state of all context
 *  \retval     TRUE  - DCM is idelling for now.
 *  \retval     FALSE - at least one context is currently busy.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(boolean, DCM_CODE) Dcm_PruMayProcessRequest(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextStateType mergedContextState;
  mergedContextState = dcmDslInfoPool[DCM_CONTEXT_ID_UDS].contextState;
# if(DCM_NUM_CONTEXTS > 1)
  /* Merge context states */
  mergedContextState |= dcmDslInfoPool[DCM_CONTEXT_ID_OBD].contextState;
# endif
  /* DCM is NOT in use? */
  return (boolean)(mergedContextState == DCM_CONTEXT_STATE_FREE);
}
#endif /* ((DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  DcmOnTimeoutPeriodicTx
 **********************************************************************************************************************/
/*! \brief      Timeout of periodic transmission (no confirmation
 *  \param[in]  timerId                    The resource handle got at "allocate" time.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) DcmOnTimeoutPeriodicTx(Dcm_TimerIdType timerId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_EnterCritical();
  /* Cancel transmission via PduR */
  Dcm_PruReleaseResource((Dcm_PeriodicHandleType)(timerId - DCM_TIMER_ID_PERIODICTX_0));
  Dcm_LeaveCritical();
}

/***********************************************************************************************************************
 *  Dcm_PruReleaseResource
 **********************************************************************************************************************/
/*! \brief      Timeout of periodic transmission (no confirmation
 *  \param[in]  handle                     The resource handle got at "allocate" time.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_PruReleaseResource(Dcm_PeriodicHandleType handle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_TmrMgrStopTimer((Dcm_TimerIdType)(DCM_TIMER_ID_PERIODICTX_0 + handle));
  dcmPruResourceTable[handle].isReserved = FALSE;
}
#endif /* ((DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON) && (DCM_SERVICE_2A_ENABLED == STD_ON)) */
#if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DslFreeSessionOwner
 **********************************************************************************************************************/
/*! \brief      If the session owner will be released
  * \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_DslFreeSessionOwner(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  if(FALSE != dcmDslInfoPool[DCM_CONTEXT_ID_UDS].isConnectionLocked)
  {
    Dcm_EnterCritical();
    /* reset always */
    dcmDslInfoPool[DCM_CONTEXT_ID_UDS].isConnectionLocked = FALSE;
    Dcm_DslLL_ReleaseReservedRxResource(dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dslHandle);
    Dcm_LeaveCritical();
  }
}
#endif

/***********************************************************************************************************************
 *  Dcm_SendResponsePending
 **********************************************************************************************************************/
/*! \brief      Forces immediate RCR-RP transmission.
 *  \param[in]  owner           Specifies if the response is internal or application
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_SendResponsePending(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslResponseType owner)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_SendResponsePending);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Only during active service is allowed to use this API */
  Dcm_BoolCheckValueRangeFailed((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState != DCM_CONTEXT_STATE_FREE), DcmServiceId_SendResponsePending); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  /* Only prior sending the final response is allowed to use the API */
  Dcm_BoolCheckValueRangeFailed(((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType == DSL_RES_TYPE_NONE)||
                                ((dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType & DSL_RES_TYPE_RCRRP_ANY) != 0)), DcmServiceId_SendResponsePending);

  Dcm_EnterCritical();
 /* Consider both cases:
  * A: no response is ongoing - the response type will be set now.
  * B: there is already ongoing RCR-RP response - add the new client without sending a physical message
  */

  {
    Dcm_DslResponseType last_type;
    last_type = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType;

    /* Store the RCR-RP types sent */
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].resType |= owner;
    /* Store an RCR-RP was attempted, which is irrelevant */
    dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].rcrRpState = DSL_RES_TYPE_RCRRP_ANY;

    if(DSL_RES_TYPE_NONE == last_type)
    {
      /* Reload timer */
      Dcm_TmrMgrNotSafeStartTimer(DCM_CONTEXT_P2_TIMER_ID(DCM_CONTEXT_PARAM_VALUE), dcmDslTimerSettings.timeOutP2Ex);
      Dcm_LeaveCritical();
      /* Try to send */
      Dcm_DslLL_StartTransmission(DCM_CONTEXT_PARAM_VALUE_ONLY);
    }
    else
    {
      Dcm_LeaveCritical();
    }
  }
}

#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DoLock
 **********************************************************************************************************************/
/*! \brief      
 *  \param[in]  connId           A TAG value for the transmission channel
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(boolean, DCM_CODE) Dcm_DoLock(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  boolean result = FALSE;
  Dcm_CheckDcmInit(DcmServiceId_LockDcm);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  Dcm_EnterCritical();
  {
    boolean isResLocked;
    isResLocked = Dcm_DslLL_IsRxResourceLocked(connId);
    if((FALSE == isResLocked)&&
       (dcmDslInfoPool[DCM_CONTEXT_ID_UDS].contextState == DCM_CONTEXT_STATE_FREE))
    {
      /* Lock DCM */
      dcmDslInfoPool[DCM_CONTEXT_ID_UDS].contextState = DCM_CONTEXT_STATE_RESERVED;
      Dcm_DslLL_AllocateRxResource(connId);
      result = TRUE;
    }
  }
  Dcm_LeaveCritical();
  return result;
}
#endif

#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DoUnLock
 **********************************************************************************************************************/
/*! \brief      -
 *  \param[in]  connId           A TAG value for the transmission channel
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_DoUnLock(Dcm_ConnectionRefType connId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_UnLockDcm);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* UnLock DCM */
  Dcm_EnterCritical();
  Dcm_DslLL_ReleaseRxResource(connId);
  dcmDslInfoPool[DCM_CONTEXT_ID_UDS].contextState = DCM_CONTEXT_STATE_FREE;
  Dcm_LeaveCritical();
}
#endif

#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_SendSpontaneousResponse
 **********************************************************************************************************************/
/*! \brief      Forces an immediate spontaneous transmission.
 *  \param[in]  connId         A TAG value for the transmission channel
 *  \param[in]  dataPtr        Pointer to the response data
 *  \param[in]  dataLen        Total length of the response data
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_SendSpontaneousResponse(Dcm_ConnectionRefType connId, Dcm_MsgType dataPtr, Dcm_MsgLenType dataLen)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_SendSpontaneousResponse);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Only prior sending the final response is allowed to use the API */
  Dcm_BoolCheckValueRangeFailed((dcmDslInfoPool[DCM_CONTEXT_ID_UDS].resType == DSL_RES_TYPE_NONE), DcmServiceId_SendSpontaneousResponse); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Set context state DCM */
  dcmDslInfoPool[DCM_CONTEXT_ID_UDS].contextState = DCM_CONTEXT_STATE_TX_STARTED;

  dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dataPtr = dataPtr;
  dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dataLength = dataLen;
  dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dslHandle = connId;
  dcmDslInfoPool[DCM_CONTEXT_ID_UDS].resType = DSL_RES_TYPE_SPONTANEOUS;
  /* Send */
  Dcm_DslLL_StartTransmission(DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(DCM_CONTEXT_ID_UDS));
}
#endif

/***********************************************************************************************************************
 *  DcmOnTimeoutSession
 **********************************************************************************************************************/
/*! \brief      Notification for timeout on S3
 *  \param[in]  timerId                     Expired timer's Id 
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) DcmOnTimeoutSession(Dcm_TimerIdType timerId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(timerId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_ID_UDS), DCM_EVENT_TESTER_TIMEOUT);
}

/***********************************************************************************************************************
 *  DcmOnTimeoutResponsePending
 **********************************************************************************************************************/
/*! \brief      Notification for timeout on P2/P2Star
 *  \param[in]  timerId                     Expired timer's Id 
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) DcmOnTimeoutResponsePending(Dcm_TimerIdType timerId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(timerId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_SendResponsePending(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(DCM_CONTEXT_ID_UDS) DSL_RES_TYPE_RCRRP_AUT);
}

/***********************************************************************************************************************
 *  Dcm_DslDoPostProcessing
 **********************************************************************************************************************/
/*! \brief      Service post processing event.
 *  \param[in]  status                      Reception status.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_DslDoPostProcessing(DCM_CONTEXT_PARAM_DEF_FIRST Dcm_DslCommStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  dcmPBStateMachine[DCM_CONTEXT_PARAM_VALUE].isPagedBufferActive = 0;
#endif
  dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].txConfStatus = status;
  /* StartS3 timer again (only for real requests) */
  Dcm_TmrMgrStartTimer(DCM_TIMER_ID_S3, DCM_TIMEOUT_S3);
  Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(DCM_CONTEXT_PARAM_VALUE), DCM_EVENT_TX_END);

  {
    uint8 sesChgIdx = dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].pendingSessChgIdx;
    if(sesChgIdx != DCM_NO_PEND_SESCHG_IDX)
    {
      if( (status == DSL_COMM_E_OK)
        &&(dcmDsdErrorRegister[DCM_CONTEXT_PARAM_VALUE] == DCM_E_OK ))
      {
        /* Update P2 timings for the new session */
        dcmDslTimerSettings.timeOutP2   = dcm10_ServiceInfoTable[sesChgIdx].TickTime.timeOutP2;
        dcmDslTimerSettings.timeOutP2Ex = dcm10_ServiceInfoTable[sesChgIdx].TickTime.timeOutP2Ex;
      }
    }
  }

  /* release resources */
  Dcm_DslLL_ReleaseRxResource(dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].dslHandle);
  /* Process the activity */
  Dcm_ProcessActivity(DCM_ACTIVITY_SOURCE_MSG_TX_CONF);
  /* Release DCM */
  dcmDslInfoPool[DCM_CONTEXT_PARAM_VALUE].contextState = DCM_CONTEXT_STATE_FREE;
}

/***********************************************************************************************************************
 *  Dcm_GetCurrentSession
 **********************************************************************************************************************/
/*! \brief      Returns the current session state.
 *  \result     Current session.
 *  \retval     Session Ids.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_SesCtrlType, DCM_CODE) Dcm_GetCurrentSession(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_GetSesCtrlType);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  return dcmStateGroupInfo[DCM_SESSION_STATE_GRP_IDX].StateValuePtr[dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX]];
}

/***********************************************************************************************************************
 *  Dcm_GetSesCtrlType
 **********************************************************************************************************************/
/*! \brief      Returns the current session state.
 *  \param[out] SessionCtrlType                 Current session.
 *  \result     Operation status.
 *  \retval     0 - E_OK
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType( P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  *SessionCtrlType = Dcm_GetCurrentSession();
  return DCM_E_OK;
}

/***********************************************************************************************************************
 *  DcmOnChgStateSession
 **********************************************************************************************************************/
/*! \brief      Session transition notification
 *  \param[in]  stateGroupIdx                 Index of the state group, the transition belongs to.
 *  \param[in]  newStateIdx                   Index of the new state.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) DcmOnChgStateSession(uint8_least stateGroupIdx, uint8 newStateIdx)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least sesIndex = dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX];

  Dcm_CheckDcmInit(DcmServiceId_SetSesCtrlType);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  DCM_IGNORE_UNREF_PARAM(stateGroupIdx); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  /* Notify the RTE */
  (void)dcm10_SesChgIndFunc((Dcm_SesCtrlType)dcmStateGroupInfo[DCM_SESSION_STATE_GRP_IDX].StateValuePtr[sesIndex],
                            (Dcm_SesCtrlType)dcmStateGroupInfo[DCM_SESSION_STATE_GRP_IDX].StateValuePtr[newStateIdx]);

  /* Which transition is made -> default OR -> non default */
  if(newStateIdx == 0)
  {
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
    Dcm_2A_SchedulerStopAll();
#endif
#if (DCM_SERVICE_19_ENABLED == STD_ON)
    /* Try to restore always for default session */
    (void)Dem_EnableDTCStorage(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
#endif
#if (DCM_SERVICE_28_ENABLED == STD_ON)
    Dcm_28_EnableCommunication();
#endif
#if (DCM_SERVICE_2F_ENABLED == STD_ON)
    Dcm_2F_ReturnControlToECU();
#endif
  }

#if (DCM_SERVICE_27_ENABLED == STD_ON)
  Dcm_27_InitSeedKeyState();
#endif

  /* Make the transition here because of the process activity needs it now!!! */
  dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX] = newStateIdx;
  /* Process the activity */
  Dcm_ProcessActivity(DCM_ACTIVITY_SOURCE_SET_SES);
}

/***********************************************************************************************************************
 *  Dcm_ComM_NoComModeEntered
 **********************************************************************************************************************/
/*! \brief      COM Manager notification for entering no-comm-mode
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_ComMNoComModeEntered);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  dcmStateMachine.CommState = DCM_COMM_STATE_NONE;
}

/***********************************************************************************************************************
 *  Dcm_ComM_SilentComModeEntered
 **********************************************************************************************************************/
/*! \brief      COM Manager notification for entering listen-only-mode
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_ComMSilentComModeEntered);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  dcmStateMachine.CommState = DCM_COMM_STATE_SILENT;
}

/***********************************************************************************************************************
 *  Dcm_ComM_FullComModeEntered
 **********************************************************************************************************************/
/*! \brief      COM Manager notification for entering full-comm-mode
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_ComMFullComModeEntered);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  dcmStateMachine.CommState = DCM_COMM_STATE_FULL;
}

/***********************************************************************************************************************
 *  Dcm_ProcessActivity
 **********************************************************************************************************************/
/*! \brief      DCM-activity state-machine manager
 *  \param[in]  trigger                   The state change trigger.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_ProcessActivity(Dcm_ActivityStateTriggerType trigger)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextStateType mergedContextState;
  Dcm_CheckDcmInit(DcmServiceId_ProcessActivity);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Lock interrupts to guarantee consistent processing */
  Dcm_EnterCritical();

  mergedContextState = dcmDslInfoPool[DCM_CONTEXT_ID_UDS].contextState;
#if(DCM_NUM_CONTEXTS > 1)
  /* Merge context states */
  mergedContextState |= dcmDslInfoPool[DCM_CONTEXT_ID_OBD].contextState;
#endif
  switch(dcmStateMachine.ActivityState)
  {
    /*===================================*/
    case DCM_ACTIVITY_STATE_INACTIVE:
    /*===================================*/
      switch(trigger)
      {
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_SET_SES:
        /*-----------------------------------*/
          if(dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX] != 0)
          {
            ComM_DCM_ActiveDiagnostic();
            dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_ACTIVE;
          }
          break;
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_RX_IND:
        /*-----------------------------------*/
          if(dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX] == 0)
          {
            ComM_DCM_ActiveDiagnostic();
            dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_ACTIVE;
          }
          break;
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_FBL_RESPONDER:
        /*-----------------------------------*/
          ComM_DCM_ActiveDiagnostic();
          dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_ACTIVE;
          break;
#endif
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_MSG_TX_END:
        /*-----------------------------------*/
#if(DCM_NUM_CONTEXTS > 1)
          /* another context may notify about this state - just ignore (we are already in "inactive") */
          break;
#else
         /* No MsgConfirmation in state inactive - fall through */
#endif
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_MSG_TX_CONF: /* No Tx Confirmation expected here - fall through */
        /*-----------------------------------*/
        /*-----------------------------------*/
        default:
        /*-----------------------------------*/
          Dcm_CheckAlwaysFailed(DcmServiceId_ProcessActivity); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
          break;
      }
      break;
    /*===================================*/
    case DCM_ACTIVITY_STATE_PREP_INACTIVE:
    /*===================================*/
      switch(trigger)
      {
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_SET_SES: /* fall through */
        /*-----------------------------------*/
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_RX_IND:
        /*-----------------------------------*/
          /* Not relevant */
          break;
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_MSG_TX_END:
        /*-----------------------------------*/
          if((dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX] == 0) &&
             ((mergedContextState & (Dcm_ContextStateType)~(DCM_CONTEXT_STATE_FREE | DCM_CONTEXT_STATE_RX_STARTED)) == 0))/* PRQA S 0277 */ /* all of the contexts are in idle or rx start */ /* Needed for consistent clear bit operation */
          {
            ComM_DCM_InactiveDiagnostic();
            dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_INACTIVE;
          }
          else
          {
            dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_ACTIVE;
          }
          break;
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_FBL_RESPONDER:/* Shall not be invoked in this state - fall through */
        /*-----------------------------------*/
#endif
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_MSG_TX_CONF:/* No MsgConfirmation in state inactive -  fall through */
        /*-----------------------------------*/
#if(DCM_NUM_CONTEXTS > 1)
          /* another context may notify about this state - just ignore (we are already in "prepare inactive") */
          break;
#endif
        /*-----------------------------------*/
        default:
        /*-----------------------------------*/
          Dcm_CheckAlwaysFailed(DcmServiceId_ProcessActivity); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
          break;
      }
      break;
    /*===================================*/
    case DCM_ACTIVITY_STATE_ACTIVE:
    /*===================================*/
      switch(trigger)
      {
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_RX_IND:
        /*-----------------------------------*/
          /* Not relevant */
          break;
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_MSG_TX_CONF:
        /*-----------------------------------*/
          dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_PREP_INACTIVE;
          break;
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_SET_SES:
        /*-----------------------------------*/
          if((dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX] == 0) &&
             ((mergedContextState & (Dcm_ContextStateType)~(DCM_CONTEXT_STATE_FREE | DCM_CONTEXT_STATE_RX_STARTED)) == 0))/* PRQA S 0277 */ /* all of the contexts are in idle or rx start */ /* Needed for consistent clear bit operation */
          {
            ComM_DCM_InactiveDiagnostic();
            dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_INACTIVE;
          }
          break;
#if (DCM_FBL_POS_RES_ENABLED == STD_ON)
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_FBL_RESPONDER:
        /*-----------------------------------*/
          /* No check for transition or RxEvent since DCM shall be locked here */
          ComM_DCM_InactiveDiagnostic();
          dcmStateMachine.ActivityState = DCM_ACTIVITY_STATE_INACTIVE;
          break;
#endif
        /*-----------------------------------*/
        case DCM_ACTIVITY_SOURCE_MSG_TX_END:
        /*-----------------------------------*/
#if(DCM_NUM_CONTEXTS > 1)
          /* another context may notify about this state - just ignore (we are already in "active") */
          break;
#else
         /* No MsgConfirmation in state active - fall through */
#endif
        /*-----------------------------------*/
        default:
        /*-----------------------------------*/
          Dcm_CheckAlwaysFailed(DcmServiceId_ProcessActivity); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
          break;
      }
      break;
    default:
      Dcm_CheckAlwaysFailed(DcmServiceId_ProcessActivity); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      break;
  }
  /* Restore interrupts */
  Dcm_LeaveCritical();
}

/***********************************************************************************************************************
 *  Dcm_CheckServiceStateMatch
 **********************************************************************************************************************/
/*! \brief      State execution condition check on service and sub-service level
 *  \param[in]  cfgStates                   Concrete state group states from the service configuration
 *  \param[in]  stateGrpIdx                 State group index
 *  \param[in]  stateLevel                  Give a special view on the state NRC assignment
 *  \return     The result NRC of the check
 *  \context    Function must be called on task level only.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckServiceStateMatch(Dcm_StateMaskType cfgStates, uint8_least stateGrpIdx, Dcm_StateLevelType stateLevel)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType errorCode;

  errorCode = DCM_E_OK;
  if((cfgStates & Dcm_GetStateMaskOfIdx(dcmCurrentStateInfo[stateGrpIdx])) == 0)
  {
    errorCode = dcmStateGroupInfo[stateGrpIdx].Nrc;
    /* Special handling on session state group */
    if(DCM_SESSION_STATE_GRP_IDX == stateGrpIdx)
    {
      switch(stateLevel)
      {
      case DCM_STATE_LVL_SID:
        return DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
      case DCM_STATE_LVL_PARAM:
        return DCM_E_REQUESTOUTOFRANGE;
      case DCM_STATE_LVL_SUBFUNC:
        return DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
      default: /* fall through */
        break;
      }
    }
  }
  return errorCode;/* iterator value is not important in case E_OK!!! */
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_CheckServiceState
 **********************************************************************************************************************/
/*! \brief      State execution condition check on service and sub-service level
 *  \param[in]  ref                         Reference to a state precondition entry
 *  \param[in]  stateLevel                  Give a special view on the state NRC assignment
 *  \param[out] pErrorCode                  Returns the result as NRC
 *  \return     state group index caused the NRC
 *  \context    Function must be called on task level only.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint8, DCM_CODE) Dcm_CheckServiceState(Dcm_StateFilterIndexType ref, Dcm_StateLevelType stateLevel, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) pErrorCode)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least stateGrpIter;

  *pErrorCode = DCM_E_OK;
  /* Iterate the state groups considering their order! */
  for(stateGrpIter = 0; (stateGrpIter < DCM_NUM_STATE_GROUPS)&&(DCM_E_OK == *pErrorCode); stateGrpIter++)
  {
    *pErrorCode = Dcm_CheckServiceStateMatch(DcmServiceStateFilterPool(ref, stateGrpIter), stateGrpIter, stateLevel);
  }
  stateGrpIter--; /* compensate the post increment in the loop */
  return (uint8)(stateGrpIter);/* iterator value is not important in case E_OK!!! */
}

/***********************************************************************************************************************
 *  Dcm_ExecuteStateTransition
 **********************************************************************************************************************/
/*! \brief      Executes (if necessary) a state transition (for all groups).
 *  \param[in]  ref                         Reference to a state precondition entry
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_ExecuteStateTransition(Dcm_StateTransitionIndexType ref)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least stateGrpIter;
  for(stateGrpIter = 0; stateGrpIter < DCM_NUM_STATE_GROUPS; stateGrpIter++)
  {
    if((DcmStateTransPrecondInfo(ref,stateGrpIter) & Dcm_GetStateMaskOfIdx(dcmCurrentStateInfo[stateGrpIter])) != 0)
    {
      /* Notify about the new state */
      dcmStateGroupInfo[stateGrpIter].OnChgCallBack(stateGrpIter, DcmStateTransTargetInfo(ref, stateGrpIter));
      dcmCurrentStateInfo[stateGrpIter] = DcmStateTransTargetInfo(ref, stateGrpIter);
    }
  }
}

#if ((DCM_OBD_SUPPORT_ENABLED == STD_ON) || (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  DcmOnTimeoutObdResponsePending
 **********************************************************************************************************************/
/*! \brief      Notification for timeout on P2/P2Star
 *  \param[in]  timerId                     Expired timer's Id 
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) DcmOnTimeoutObdResponsePending(Dcm_TimerIdType timerId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(timerId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_SendResponsePending(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(DCM_CONTEXT_ID_OBD) DSL_RES_TYPE_RCRRP_AUT);
}
#endif /* ((DCM_OBD_SUPPORT_ENABLED == STD_ON) || (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)) */
/***********************************************************************************************************************
 *  Dcm_SetNegResponse
 **********************************************************************************************************************/
/*! \brief      Registers the first error.
 *  \param[in]  errorCode                   Negative response code
 *  \context    Function could be called from interrupt context or task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_SetNegResponse(Dcm_NegativeResponseCodeType errorCode)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurContextId();

  Dcm_CheckDcmInit(DcmServiceId_SetNegResponse);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  if(dcmDsdErrorRegister[lContext] == DCM_E_OK)
  {
    dcmDsdErrorRegister[lContext] = errorCode;
  }
}

/***********************************************************************************************************************
 *  Dcm_ProcessingDone
 **********************************************************************************************************************/
/*! \brief      Finilizes the current service processing.
 *  \context    Function could be called from interrupt context or task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_ProcessingDone(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  boolean doSendResponse = TRUE;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurContextId();

  Dcm_CheckDcmInit(DcmServiceId_ProcessingDone);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* While still waiting for RCR-RP confirmation no ProcessingDone allowed!!! */
  Dcm_StateCheckValueRangeFailed(((Dcm_EvMgrGetEvent(DCM_CONTEXT_STATE_TASK_ID(lContext)) & DCM_EVENT_RCRRP_CONFIRM) == 0), DcmServiceId_ProcessingDone); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  dcmDslInfoPool[lContext].contextState = DCM_CONTEXT_STATE_PROCESS_ENDED;

#if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
  /* On any error - just suppress the response!!! */
  if( (dcmDslInfoPool[lContext].protocolType & DCM_DIAG_PROTOCOL_OBD) != 0)
  {
    /* Catch any (uncatched by the service processor) out of boundary responses */
    if((dcmDsdMsgContext[lContext].resDataLen > dcmDslInfoPool[lContext].maxBufferLength) ||
       (dcmDsdMsgContext[lContext].resDataLen > dcmDslInfoPool[lContext].maxBusPayloadLength))
    {
      /* Overwrite always the last error */
      dcmDsdErrorRegister[lContext] = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
#endif
  {
    /* If bus system maximum length is exceeded - send a negative response */
    if(dcmDsdMsgContext[lContext].resDataLen > dcmDslInfoPool[lContext].maxBusPayloadLength)
    {
      dcmDsdErrorRegister[lContext] = DCM_E_RESPONSE_TOO_LONG;
    }

    /* Catch any (uncatched by the service processor) out of boundary responses */
    if((dcmDsdMsgContext[lContext].resDataLen > dcmDslInfoPool[lContext].maxBufferLength)
     &&(dcmDsdErrorRegister[lContext] != DCM_E_RESPONSE_TOO_LONG))
    {
      /* Overwrite always the last error */
      dcmDsdErrorRegister[lContext] = DCM_E_GENERALREJECT;
    }
  }

#if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
    (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
  /* Positive or negative response on UDS */
  if( (dcmDslInfoPool[lContext].protocolType & DCM_DIAG_PROTOCOL_UDS) != 0)
  {
    if(dcmDsdErrorRegister[lContext] == DCM_E_OK)
    {
      switch(dcmDslInfoPool[lContext].dataPtr[0])
      {
        case 0x10:
          /* If there is something in processing in the (WWH)OBD context - reject the service */
          if((dcmDslInfoPool[DCM_CONTEXT_ID_OBD].contextState & DCM_CONTEXT_STATE_FREE) == 0)
          {
            dcmDsdErrorRegister[lContext] = 0x22; /* Enforce session execution failed if an OBD service is ongoing */
          }
          break;
# if (DCM_SERVICE_27_ENABLED == STD_ON) || \
     (DCM_SERVICE_28_ENABLED == STD_ON) || \
     (DCM_SERVICE_2A_ENABLED == STD_ON)

#  if (DCM_SERVICE_27_ENABLED == STD_ON)
        case 0x27: /* fall through */
#  endif
#  if (DCM_SERVICE_28_ENABLED == STD_ON)
        case 0x28: /* fall through */
#  endif
#  if (DCM_SERVICE_2A_ENABLED == STD_ON)
        case 0x2A: /* fall through */
#  endif
        if(0 == dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX])/* OBD changes to the default session -> skip post-processing if default session */
        {
          dcmDsdErrorRegister[lContext] = 0x7F; /* Enforce wrong session execution */
        }
        break;
# endif
       default:
         /* process normally */
         break;
      }
    }
  }
#endif
  /* Positive or negative response */
  if(dcmDsdErrorRegister[lContext] == DCM_E_OK)
  {
    /* Pos response */
    Dcm_AddValue(dcmDslInfoPool[lContext].dataPtr[0] , Dcm_MsgItemType, 0x40);
    dcmDslInfoPool[lContext].dataLength = dcmDsdMsgContext[lContext].resDataLen;

    if((dcmDsdMsgContext[lContext].msgAddInfo & DCM_MSGADDINFO_SUPP_POS_RES) != 0)
    {
      doSendResponse = FALSE;
    }
  }
  else
  {
#if (DCM_IGNORE_RESPONSE_SID_ENABLED == STD_ON)
    /* NRC 0x11 (it can be only NRC 0x11!!!) on SID in range: [0x40, 0x7F]U[0xC0, 0xFF] will not be responded at all */
    if((dcmDslInfoPool[lContext].dataPtr[0] & 0x40) != 0)
    {
      doSendResponse = FALSE;
    }
    else
#endif
    {
      /* Neg response */
      dcmDslInfoPool[lContext].dataPtr[1] = dcmDslInfoPool[lContext].dataPtr[0];
      dcmDslInfoPool[lContext].dataPtr[0] = 0x7F;
      dcmDslInfoPool[lContext].dataPtr[2] = (Dcm_MsgItemType)dcmDsdErrorRegister[lContext];
      dcmDslInfoPool[lContext].dataLength = 3;

      if((dcmDsdMsgContext[lContext].msgAddInfo & DCM_MSGADDINFO_REQ_TYPE)!= 0)
      {
        switch(dcmDsdErrorRegister[lContext])
        {
          case DCM_E_SERVICENOTSUPPORTED: /* fall through */
          case DCM_E_SUBFUNCTIONNOTSUPPORTED: /* fall through */
          case DCM_E_REQUESTOUTOFRANGE: /* fall through */
            doSendResponse = FALSE;
            break;
          default:
#if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
            if( (dcmDslInfoPool[lContext].protocolType & DCM_DIAG_PROTOCOL_OBD) != 0)
            {
              /* Allow only NRCs 0x21 and 0x22 on functional requests */
              switch(dcmDsdErrorRegister[lContext])
              {
                case DCM_E_CONDITIONSNOTCORRECT: /* fall through */
                case DCM_E_BUSYREPEATREQUEST: /* fall through */
                  /* go on with NRC response */
                  break;
                default:
                  doSendResponse = FALSE;
                  break;
              }
            }
#endif
            break;
        }
      }
    }
  }

  /* Send no response only if no RCR-RP has been sent */
  Dcm_EnterCritical();/* Guarantee no interruption by the TimerTask if split task concept is used */
  if( (doSendResponse == FALSE) &&                                 /* No suppress bit was set */
      ( (DSL_RES_TYPE_NONE == dcmDslInfoPool[lContext].rcrRpState) /* Suppress only if RcrRp was not even attempted */
#if (DCM_OBD_SUPPORT_ENABLED == STD_ON)
      || ( (dcmDslInfoPool[lContext].protocolType & DCM_DIAG_PROTOCOL_OBD) != 0) /* OBD shall not be responded in any case!!! */
#endif
      ) )
  {
    /* Now we must stop the timer (for suppressed responses!)*/
    Dcm_TmrMgrNotSafeStopTimer(DCM_CONTEXT_P2_TIMER_ID(lContext));
    Dcm_LeaveCritical();
    /* Do immediate "transmission" post-processing (DCM is released) */
    Dcm_DslDoPostProcessing(DCM_CONTEXT_PARAM_VALUE_WRAP_FIRST(lContext) DSL_COMM_E_OK);
  }
  else
  {
    Dcm_LeaveCritical();
    Dcm_EvMgrSetEvent(DCM_CONTEXT_STATE_TASK_ID(lContext), DCM_EVENT_SEND_LINEAR_RES);
  }
}

#if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DemMgrStealLockDemUdsClient
 **********************************************************************************************************************/
/*! \brief      Steals a lock of the UDS client if not clearing DTC is ongoing for OBD i.e. (0x02, 0x03, 0x07, 0x0A) 
 *  \param[in]  demOp       Handle to a DEM located in the service 19 table to be locked
 *  \return     Reservation result
 *  \retval     TRUE - success (free place found)
 *  \retval     FALSE - failed (already locked)
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(boolean, DCM_CODE) Dcm_DemMgrStealLockDemUdsClient(Dcm_DemMgrDemOpType demOp)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Check if UDS is doing something */
  if((dcmDemMgrResourceMap[DCM_DEMMGR_CLIENT_ID_UDS] & demOp) != 0)
  {
    if((dcmDemMgrResourceMap[DCM_DEMMGR_CLIENT_ID_UDS] & DCM_DEMMGR_OP_14) != 0)
    {
      /* Can not steel the lock since CLEAR operations is ongoing */
      return FALSE;
    }
    /* Release all other clients */
    Dcm_DemMgrReleaseDemClient(DCM_DEMMGR_CLIENT_ID_UDS);
  }
  /* Lock the resource */
  dcmDemMgrResourceMap[DCM_DEMMGR_CLIENT_ID_OBD] = (Dcm_MemDemMgrDemOpType)demOp;
  return TRUE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif

#if ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
    (DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
    (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  Dcm_DidMgrReadDid
 **********************************************************************************************************************/
/*! \brief      Synchronized DID read access
 *  \param[in]  did22Handle       the DID handle of service 0x22
 *  \param[out] resDataPtr        Target data pointer
 *  \param[in]  clientId          The DID client id requesting the read access
 *  \param[out] errorRegister     The operation result
 *  \return     Read operation result
 *  \retval     DCM_E_OK      - success
 *  \retval     DCM_E_PENDING - try later
 *  \retval     other         - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrReadDid(Dcm_DidHandleType did22Handle, Dcm_MsgType resDataPtr, Dcm_DidMgrDidClientType clientId, Dcm_NegativeResponseCodePtrType pErrorCode)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
  boolean lIsReserved;
  lIsReserved = Dcm_DidMgrLockDidClient(did22Handle, clientId);
  if(FALSE == lIsReserved)
  {
    /* try again */
    return DCM_E_PENDING;
  }
# endif

  DCM_IGNORE_UNREF_PARAM(clientId); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  /* Give the control to the application */
  stdReturn = dcm22_ServiceInfoTable[did22Handle].ReadData((Dcm_RteDataPtrType)resDataPtr); /* PRQA S 0310 */ /* PRQA S 0308 */

  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_NOT_OK:
  /*------------------*/
      if(NULL_PTR != pErrorCode)
      {
        *pErrorCode = DCM_E_GENERALREJECT; /* use this code to notify the tool about an unhandled error */
      }
  /*------------------*/
    case DCM_E_OK: /* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */ /* Fall through */
  /*------------------*/
      break;
# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
  /*------------------*/
    case DCM_E_PAGED_DATA_OK:
  /*------------------*/
      /* delegate to paged processor */
# endif
  /*------------------*/
    case DCM_E_PENDING: /* PRQA S 2003 */ /* QAC 7.0:  The preceding non-empty 'case' or 'default' clause does not end with an explicit 'break' or 'return' statement. */ /* Optimal state machine implementation */
  /*------------------*/
      /* try again */
      return stdReturn; /* Return the original value */
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      if(NULL_PTR != pErrorCode)
      {
        *pErrorCode = DCM_E_GENERALREJECT;
      }
      break;
  }
# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
  /* No more needed */
  Dcm_DidMgrReleaseDidClient(clientId);
# endif
  return stdReturn;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

# if (DCM_SERVICE_2E_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DidMgrWriteDid
 **********************************************************************************************************************/
/*! \brief      Synchronized DID read access
 *  \param[in]  did22Handle       the DID handle of service 0x22
 *  \param[out] resDataPtr        Target data pointer
 *  \return     Read operation result
 *  \retval     DCM_E_OK      - success
 *  \retval     DCM_E_PENDING - try later
 *  \retval     other         - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Std_ReturnType, DCM_CODE) Dcm_DidMgrWriteDid(Dcm_DidHandleType did22Handle, Dcm_DidHandleType did2EHandle, Dcm_MsgType reqDataPtr, Dcm_MsgLenType reqDataLen)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

#  if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
  boolean lIsReserved;

  /* Makes sence to lock only if the DID is readable (currenly no concurent write accesses!!) */
  if(did22Handle < DCM_NUM_DIDS)
  {
    lIsReserved = Dcm_DidMgrLockDidClient(did22Handle, DCM_DIDMGR_CLIENT_ID_2E);
    if(FALSE == lIsReserved)
    {
      /* try again */
      return DCM_E_PENDING;
    }
  }
#  endif

  DCM_IGNORE_UNREF_PARAM(did22Handle); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  /* Give the control to the application */
  stdReturn = dcm2E_ServiceInfoTable[did2EHandle].WriteData((Dcm_RteDataPtrType)reqDataPtr, reqDataLen, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]); /* PRQA S 0310 */ /* PRQA S 0308 */

  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      Dcm_SetNegResponse(DCM_E_GENERALREJECT);/* Keep the original one if set */
      break;
  }
#  if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
  /* No more needed - release always even if not reserved */
  Dcm_DidMgrReleaseDidClient(DCM_DIDMGR_CLIENT_ID_2E);
#  endif
  return stdReturn;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_ReadDid
 **********************************************************************************************************************/
/*! \brief         External read DID access
 *  \param[in]     did             the searched DID
 *  \param[out]    resDataPtr      pointer to the target buffer
 *  \param[inout]  resDataLenPtr   in:the expected data len (0 = no expectation (dynamic len)), out:real length
 *  \return        Operation result
 *  \retval        DCM_E_OK             - success
 *  \retval        DCM_E_PENDING        - try later
 *  \retval        DCM_E_DID_NOT_FOUND  - DID not supported
 *  \retval        DCM_E_DID_BUFFER_TOO_SMALL - DID data will not fit into the buffer 
 *  \retval        DCM_E_NOT_OK         - DID supported but can not be read
 *  \context       Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Dcm_StatusType, DCM_CODE) Dcm_ReadDid(uint16 did, Dcm_ApplDataPtrType resDataPtr, Dcm_ApplDataLenPtrType resDataLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  if(dcmDidMgrExtReadDidState.lastDid != (uint32)did)
  {
    Dcm_DidHandleType didHandle; /* use separated handle storage to keep the global did and didHandle always synchronized */

    didHandle = Dcm_22_FindDid(did);
    if(DCM_NUM_DIDS <= didHandle)
    {
      return DCM_E_DID_NOT_FOUND;
    }
    /* store for next time */
    dcmDidMgrExtReadDidState.lastDid = did;
    dcmDidMgrExtReadDidState.did22Handle = (Dcm_MemDidHandleType)didHandle;

    /* Static Length != 0 -> must fit
     * Dynamic Length == 0 -> will fit */
    if(*resDataLenPtr < dcm22_ServiceInfoTable[didHandle].Length)
    {
      return DCM_E_DID_BUFFER_TOO_SMALL;
    }
  }

  /* Delegate to the reader */
  stdReturn = Dcm_DidMgrReadDid(dcmDidMgrExtReadDidState.did22Handle, (Dcm_MsgType)resDataPtr, DCM_DIDMGR_CLIENT_ID_READ_EXT, NULL_PTR);

  /* Set real length (actually necessary for OK or NOT_OK only) */
  *resDataLenPtr = dcm22_ServiceInfoTable[dcmDidMgrExtReadDidState.did22Handle].Length;

  return (Dcm_StatusType)stdReturn;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif


/***********************************************************************************************************************
 *  Dcm_DidMgrGetDidHandle
 **********************************************************************************************************************/
/*! \brief      Guided DID binary look-up routine
 *  \param[in]  did               the searched DID
 *  \param[in]  pDidLookUpTable   the guidance table (e.g. 0x2A, 0x22...)
 *  \return     DID reference handle
 *  \retval     0 - (DCM_NUM_DIDS - 1)   - success
 *  \retval     DCM_NUM_DIDS             - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
STATIC FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_DidMgrGetDidHandle(uint16 did, Dcm_MemDidHandlePtrType pDidLookUpTable, Dcm_CfgVariantTablePtrType pVariantTable)
# else
STATIC FUNC(Dcm_DidHandleType, DCM_CODE) Dcm_DidMgrGetDidHandle(uint16 did, Dcm_MemDidHandlePtrType pDidLookUpTable)
# endif
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_NUM_DIDS_CONST > 32767)
#  error "Too many DIDs!"
# endif
  uint16_least       loIdx;
  uint16_least       hiIdx;
  Dcm_DidHandleType  didHandle;
  Dcm_DidHandleType  lResult = DCM_NUM_DIDS;

  /* Init look-up */
  loIdx= 1;
  hiIdx= pDidLookUpTable[0];

  while (loIdx <= hiIdx)
  {
    /* Examine one concrete serviceInstanceHeader */
    /* ------------------------------------------ */
    didHandle = (Dcm_DidHandleType)((hiIdx + loIdx) >> 1);

    /* Check for matching element */
    if(dcmDidLookUpTable[pDidLookUpTable[didHandle]] == did)
    {
      /* Bingoooo :) */
      didHandle--;
# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
      /* if not active in current config - return NOT_FOUND as result! */
      if((pVariantTable[didHandle] & dcmStateMachine.CfgVariantMask) != 0)
# endif
      {
        lResult = didHandle;/* assign result handle */
      }
      break;
    }
    /* Determine which half shall be taken */
    if (did < dcmDidLookUpTable[pDidLookUpTable[didHandle]])
    {
      /* not needed didHandle zero value check, since the loIdx min value is 1 -> didHandle could be at least 1 */
      hiIdx = (uint16_least)(didHandle - 1);
    }
    else
    {
      /* Use upper half of interval... */
      loIdx = (uint16_least)(didHandle + 1);
    }
  }
  return lResult;
}

/***********************************************************************************************************************
 *  Dcm_DidMgrAnalyseDid
 **********************************************************************************************************************/
/*! \brief      Analyzes whether a DID can be executed under current circumstances (session, security, etc.)
 *  \param[in]  StateFilterIdx    state precondition reference handle
 *  \param[in]  StateFilterIdx    state precondition reference handle
 *  \return     Information whether the DID shall be skipped.
 *  \retval     FALSE - do not skip the DID
 *  \retval     TRUE  - treat the DID as unsupported
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(boolean, DCM_CODE) Dcm_DidMgrAnalyseDid(Dcm_DidMgrDidClientType clientId, Dcm_StateFilterIndexType StateFilterIdx)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType errorCode;
  uint8 stateGrpIdx   = Dcm_CheckServiceState(StateFilterIdx, DCM_STATE_LVL_PARAM, &errorCode);

  /* on DID session state violation do special handling */
  if(errorCode != DCM_E_OK)
  {
    if(stateGrpIdx == DCM_SESSION_STATE_GRP_IDX)
    {
      switch(clientId)
      {
      case DCM_DIDMGR_CLIENT_ID_22:
# if(DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
      case DCM_DIDMGR_CLIENT_ID_22_WWHOBD: /* fall through */
# endif
# if (DCM_SERVICE_2A_ENABLED == STD_ON)
      case DCM_DIDMGR_CLIENT_ID_2A: /* fall through */
# endif
        /* Just skip the DID */
        return TRUE;
      default:
        break;
      }
    }
    /* any other service or state group - must register the NRC */
    Dcm_SetNegResponse(errorCode);
  }
  return FALSE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* ((DCM_SERVICE_09_ENABLED == STD_ON) || (DCM_SERVICE_22_ENABLED == STD_ON) || (DCM_SERVICE_2A_ENABLED == STD_ON) || \
(DCM_SERVICE_2C_ENABLED == STD_ON) || (DCM_SERVICE_2F_ENABLED == STD_ON) || (DCM_SERVICE_2E_ENABLED == STD_ON) || \
(DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  Dcm_MemAccByteStream2AtomicData
 **********************************************************************************************************************/
/*! \brief      Generic memory access byte stream to data type converter
 *  \param[in]  byteStream      byte stream to be converted
 *  \param[in]  len             byte stream length
 *  \return     packed value of the stream
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint32, DCM_CODE) Dcm_MemAccByteStream2AtomicData(Dcm_MsgType byteStream, uint8_least len) /* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint32 result = 0;
  while(len != 0)
  {
    len--;
    result <<= 8;
    result |= *byteStream;
    byteStream = &byteStream[1]; /* ptr++ */
  }
  return result;
}

# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_MemAccCheckMemoryBlock
 **********************************************************************************************************************/
/*! \brief      Generic memory access memory block analyzer
 *  \param[out] pMemBlockInfo         extracted memory block properties
 *  \param[in]  lookUpTable           look-up table with memory blocks
 *  \param[in]  stateInfoTable        state precondition table
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
#  if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_MemAccCheckMemoryBlock(Dcm_MemMgrMemBlockDescPtr        pMemBlockInfo,
                                                       CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) lookUpTable,
                                                       Dcm_CfgVariantTablePtrType       pVariantTable,
                                                       CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable)
#  else
STATIC FUNC(void, DCM_CODE) Dcm_MemAccCheckMemoryBlock(Dcm_MemMgrMemBlockDescPtr        pMemBlockInfo,
                                                       CONSTP2CONST(Dcm_MemMemBlockHandleType, AUTOMATIC, DCM_CONST) lookUpTable,
                                                       CONSTP2CONST(Dcm_StateFilterIndexType, AUTOMATIC, DCM_CONST)  stateInfoTable)
#  endif
/*--------------------------------------------------------------------------------------------------------------------*/
{
  boolean isFound;
  /* Memory block supported ?*/
  isFound = Dcm_MemAccFindMemBlock(lookUpTable, pVariantTable, stateInfoTable, &pMemBlockInfo->memBlock);
  if(FALSE != isFound)
  {
    /* Check mem block state precondition */
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = Dcm_MemAccCheckMemBlockState();
  }
  else
  {
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
  }
}
# endif

# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
/***********************************************************************************************************************
 *  Dcm_MemAccCheckMemoryBlock
 **********************************************************************************************************************/
/*! \brief      Generic memory access memory block analyzer
 *  \param[in]  pMemBlockInfo         extracted memory block properties
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_MemAccCheckMemoryBlock(Dcm_MemMgrMemBlockDescPtr pMemBlockInfo) /* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Check for address overflow or no data required (length == 0)*/
  if( (pMemBlockInfo->memBlock.length == 0) ||
      ( ((Dcm_MemAddrType)(0xFFFFFFFFu) - pMemBlockInfo->memBlock.address) < (Dcm_MemSizeType)(pMemBlockInfo->memBlock.length-1) )
    )
  {
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    Std_ReturnType stdReturn;
    stdReturn = Dcm_CheckMemory(
                                pMemBlockInfo->memOp,
#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
                                pMemBlockInfo->memBlock.memId,
#  else
                                0,
#  endif
                                pMemBlockInfo->memBlock.address,

                                pMemBlockInfo->memBlock.length,
                                &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
    if(DCM_E_OK != stdReturn)
    {
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_GENERALREJECT;
    }
  }
}
# endif

/***********************************************************************************************************************
 *  Dcm_MemAccExtractMemoryBlockInfo
 **********************************************************************************************************************/
/*! \brief      Generic memory access memory block property extractor
 *  \param[out] pMemBlockInfo         extracted memory block properties
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_MemMgrExtrInfoRsltType, DCM_CODE) Dcm_MemAccExtractMemoryBlockInfo(Dcm_MemMgrMemBlockDescPtr pMemBlockInfo)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  P2VAR(Dcm_MsgContextType,AUTOMATIC, DCM_VAR_NOINIT) pContext = &dcmDsdMsgContext[DCM_CONTEXT_ID_UDS];
  Dcm_MsgType    lReqData    = pContext->reqData;
  Dcm_MsgLenType lReqDataLen = pContext->reqDataLen;

  if (lReqDataLen == 0)
  {
    return DCM_MEMMGR_EXTR_INFO_NO_DATA;
  }
  {
    pMemBlockInfo->protocolLength = 0;

    /* FID already extracted? */
    if(pMemBlockInfo->addrParamSize == 0)
    {
      /* Skip the FID */
      pMemBlockInfo->protocolLength++;
      pMemBlockInfo->addrParamSize = Dcm_MemByAddrGetMemBlockAddrSize(lReqData[0]); /* Consider also available MID */
      pMemBlockInfo->lenParamSize = Dcm_MemByAddrGetMemBlockLenSize(lReqData[0]);
      pMemBlockInfo->addrSizeBlockLen = (uint8)(pMemBlockInfo->addrParamSize + pMemBlockInfo->lenParamSize);
# if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
      pMemBlockInfo->addrParamSize--; /* now remove the mid */
# endif

# if (DCM_MEMMGR_FID_LOOKUP_ENABLED == STD_ON)
      uint8_least foundIdx;
      /* FIDs are always available (no variant selection) */
      foundIdx = Dcm_FindValueUint8(NULL_PTR, dcmMemFidLookUpTable, lReqData[0]);
      if (foundIdx == 0)
# else
      /* accept only values in the valid range: [1,4] */
      if( ((pMemBlockInfo->addrParamSize == 0) || (pMemBlockInfo->addrParamSize > (uint8)sizeof(Dcm_MemAddrType)) ) ||
          ((pMemBlockInfo->lenParamSize == 0) || (pMemBlockInfo->lenParamSize > (uint8)sizeof(Dcm_MemSizeType)) ) )
# endif
      {
        return DCM_MEMMGR_EXTR_INFO_WRONG_FID;
      }
      lReqData = &lReqData[1]; /* ptr++ */ /* Skip the FID */
      lReqDataLen--;
    }

    {
      if (lReqDataLen < pMemBlockInfo->addrSizeBlockLen)
      {
        return DCM_MEMMGR_EXTR_INFO_TOO_SHORT;
      }
      else
      {
        Dcm_AddValue(pMemBlockInfo->protocolLength, uint8, pMemBlockInfo->addrSizeBlockLen);
# if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
        pMemBlockInfo->memBlock.memId = lReqData[0];
        lReqData = &lReqData[1]; /* ptr++ */ /* Skip the MID */
        /* lReqDataLen--;  not used */
# endif
        /* Already prepare application call - the callee does not need addrSize/lenSize that way */
        pMemBlockInfo->memBlock.address = (Dcm_MemAddrType)Dcm_MemAccByteStream2AtomicData(&lReqData[0],(uint8_least)pMemBlockInfo->addrParamSize);
        pMemBlockInfo->memBlock.length  = (Dcm_MemSizeType)Dcm_MemAccByteStream2AtomicData(&lReqData[0 + pMemBlockInfo->addrParamSize],(uint8_least)pMemBlockInfo->lenParamSize);
        /* Skip the protocol information */
        Dcm_MsgContextMoveRel((sint32_least)pMemBlockInfo->protocolLength, 0);
      }
    }
  }
  return DCM_MEMMGR_EXTR_INFO_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
#if (DCM_SHARED_OBDIDMGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_ObdReadSupportedId
 **********************************************************************************************************************/
/*! \brief      OBD Service "supported ID" reader
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ObdMgrReadSupportedId(Dcm_Uint32ConstDataConstPtrType pMaskData, Dcm_RteDataPtrType resData)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MsgType lResData = (Dcm_MsgType)(*resData);
  uint32 maskValue;

# if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
  {
    uint8_least varId = 0;
    Dcm_CfgVariantMaskType activeVars = dcmStateMachine.CfgVariantMask;

    maskValue = 0;
    /* Scan for active variant(s) */
    while(activeVars != 0)
    {
      if((activeVars & 0x01) != 0)
      {
        /* This variant is currently selected - add its IDs */
        maskValue |= pMaskData[varId];
      }
      /* update variant id */
      varId++;
      /* update bit scaner */
      activeVars>>=1;
    }
  }
# else
  maskValue = *pMaskData;
# endif
  lResData[0] = Dcm_GetHiHiByte(maskValue);
  lResData[1] = Dcm_GetHiLoByte(maskValue);
  lResData[2] = Dcm_GetLoHiByte(maskValue);
  lResData[3] = Dcm_GetLoLoByte(maskValue);
  return DCM_E_OK;
}
#endif /* (DCM_SHARED_OBDIDMGR_ENABLED == STD_ON) */
#if ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
    (DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON))
/***********************************************************************************************************************
 *  Dcm_ObdMgrParseIds
 **********************************************************************************************************************/
/*! \brief      Processes a list of IDs
 *  \param[in]  idList          The list of requested PIDs to be validated
 *  \param[out] idDescList      The list of supported PIDs to be processed
 *  \param[inout] idDescPtr     IN: idListSize, OUT: idDescList size
 *  \return     Is mixed request
 *  \retval     TRUE - mixed availability and data PIDs
 *  \retval     FASLE- only one kind of PIDs
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_ObdMgrParseIds(Dcm_ObdIdDescPtrType idDescPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ObdIdHandleType idSrcIter = idDescPtr->idCount;
  Dcm_ObdIdHandleType idIdx;
  Dcm_ObdIdListItemPtrType lIdOutList = idDescPtr->idOutList;
  uint8 lId;
  uint8 idTypeMask = 0x00;

  idDescPtr->idCount = 0;/* reset count */
  while(idSrcIter != 0)
  {
    idSrcIter--;

    lId = idDescPtr->idInList[idSrcIter];
    /* analyze single PID */

    /* Check for valid data Id */
    idIdx = Dcm_FindValueUint8(NULL_PTR, idDescPtr->idLookUpTable, lId);
    /* Found ? */
    if(idIdx != 0)
    {
      idIdx--;
      idDescPtr->idCount++;
      /* Common processing */
      lIdOutList->handle = (Dcm_MemObdIdHandleType)idIdx;
      lIdOutList->id = lId;
      lIdOutList->isAvailabilityId = Dcm_ObdMgrIsAvailabilityId(lId);

      /* Always mark the type of the PID */
      idTypeMask |= (uint8)((FALSE != lIdOutList->isAvailabilityId)?0x01:0x02);

# if(DCM_OBD_REQ_PID_DATA_ENABLED == STD_ON)
      if( (lIdOutList->isAvailabilityId == FALSE)
          && (idDescPtr->idHasReqData != FALSE) )
      {
        /* if has data - only one ID is allowed in the request.
         * If prev a SuppPid is found -> the service processor will ignore the request!
         */
        idSrcIter = 0; /* break; */
      }
# endif
      /* Prepare for next item */
      lIdOutList = &lIdOutList[1];
    }
  }
  idDescPtr->isMixedId = (boolean)(0x03u == idTypeMask);
}
#endif /* ((DCM_SERVICE_01_ENABLED == STD_ON) || (DCM_SERVICE_02_ENABLED == STD_ON) || (DCM_SERVICE_06_ENABLED == STD_ON) || \
(DCM_SERVICE_08_ENABLED == STD_ON) || (DCM_SERVICE_09_ENABLED == STD_ON)) */
#if ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON))
# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DcmUpdatePage_Obd
 **********************************************************************************************************************/
/*! \brief      A paged buffer call-back.
 *  \param[out] dataPtr                 Pointer to the response data
 *  \param[in]  dataLen                 Maximum size of the available buffer
 *  \context    Function could be called from interrupt or task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_DcmUpdatePage_Obd(Dcm_MsgType dataPtr, Dcm_MsgLenType dataLen)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Gather the DTC info */
  dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.resData = dataPtr;
  dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.availLen = dataLen;
  Dcm_RegisterRepeaterProxy(Dcm_ObdMgrReadDtcRepeaterProxyGetData);
}
# endif

/***********************************************************************************************************************
 *  Dcm_ObdMgrGetDtc
 **********************************************************************************************************************/
/*! \brief      Data processor of service (0x03/0x07/0x0A).
 *  \param[in,out] dataPtr                 Pointer to the response data
 *  \param[in,out] availLenPtr             Pointer to the the available buffer size
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
LOCAL_INLINE FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ObdMgrGetDtc(P2VAR(Dcm_MsgType, AUTOMATIC,DCM_VAR_NOINIT) pDataPtr, Dcm_MsgLenPtrType availLenPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MsgLenType         lAvailLen;
  uint32                 reqDtc;
  Dem_DTCStatusMaskType  dtcStatusMask;
  Dcm_MsgType            lDataPtr = *pDataPtr;
# if (DCM_19_ITER_LIMITATION_ENABLED == STD_ON)
  uint8_least            iterLimiter = DCM_19_MAX_NUM_ITERATIONS;
# endif

  Dem_ReturnGetNextFilteredDTCType resultGetNextDtc = DEM_FILTERED_OK;

  lAvailLen = *availLenPtr;

  /* Gather the DTC info */
  while((lAvailLen >= 2)
# if (DCM_19_ITER_LIMITATION_ENABLED == STD_ON)
      &&((iterLimiter != 0)||(DCM_19_MAX_NUM_ITERATIONS == 0))
# endif
      )
  {
    resultGetNextDtc = Dcm_ObdDemWrapGetNextFilteredDtc(&reqDtc,
                                                        &dtcStatusMask);
    if(resultGetNextDtc != DEM_FILTERED_OK)
    {
      /* Skip the decrement on no matching DTC or error */
      break;
    }

    /* Put onto the response buffer */
    lDataPtr[0] = Dcm_GetHiLoByte(reqDtc);
    lDataPtr[1] = Dcm_GetLoHiByte(reqDtc);

    /* Prepare the next data */
    lDataPtr = &lDataPtr[2];
    Dcm_SubValue(lAvailLen  , Dcm_MsgLenType, 2);
# if (DCM_19_ITER_LIMITATION_ENABLED == STD_ON)
    iterLimiter--;/* decrement always (even if no limitation available (max == 0)*/
# endif
  }

  /* Update new parameters */
  *availLenPtr = lAvailLen;
  *pDataPtr = lDataPtr;

  switch(resultGetNextDtc)
  {
    case DEM_FILTERED_NO_MATCHING_DTC:
      return DCM_E_OK; /* end of iteration process */
    case DEM_FILTERED_OK:
# if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
      return DCM_E_PENDING;
# else
      return DCM_E_OK;
# endif
    default:
      return DCM_E_CONDITIONSNOTCORRECT;
  }
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */


/***********************************************************************************************************************
 *  Dcm_ObdMgrReadDtcRepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      DTC reader polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_ObdMgrReadDtcRepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType errorCode = DCM_E_CONDITIONSNOTCORRECT;
  boolean boolResult;

# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  boolResult = Dcm_DemMgrStealLockDemUdsClient(DCM_DEMMGR_OP_1902);
  if(FALSE == boolResult)
  {
    return DCM_E_PENDING; /* try again later */
  }
  else
# endif
  {
    Dem_ReturnSetDTCFilterType  resultSetDtcFilter;

    resultSetDtcFilter = Dcm_ObdDemWrapSetDtcFilter(dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.statusMask,
                                                    DEM_DTC_KIND_EMISSION_REL_DTCS,
                                                    dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.origin,
                                                    DEM_FILTER_WITH_SEVERITY_NO,
                                                    DEM_SEVERITY_NO_SEVERITY,
                                                    DEM_FILTER_FOR_FDC_NO);

    if(resultSetDtcFilter == DEM_FILTER_ACCEPTED)
    {
      Std_ReturnType stdResult;
      uint16 numDtc;

      stdResult = Dcm_ObdDemWrapGetNumFilteredDtc(&numDtc);
      if(E_OK == stdResult)
      {
        if(numDtc <= 255)
        {
          dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[0] = (uint8)numDtc; /* cast is allowed since the maximum value here is 255!*/
          /* Prepare for DTC response list */
          Dcm_MsgContextMoveRel(0,1);

          /* everything went ok */
          /* MUL 2 */
          numDtc <<=1;
          Dcm_AddValue(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resDataLen , Dcm_MsgLenType, numDtc);

# if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
          /* Check for enough linear buffer (leave place for the SID + sub-func + 4 bytes for at least one end check iteration) */
          if((numDtc + 4) <= dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resMaxDataLen)
          {
            /* Init linear use case */
            dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.resData  = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData;
            dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.availLen = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resMaxDataLen;
            Dcm_RegisterRepeaterProxy(Dcm_ObdMgrReadDtcRepeaterProxyGetData);
            /* Set a special error code for behavior differentiation */
            return DCM_E_OK;
          }
          /* else NRC 0x22 (already set) */
# else
          dcmObdMgr_PbIsFirstTime = TRUE;
          /* Starting iterations */
          Dcm_StartPagedProcessing(DCM_PB_CLIENT_OBD);
          return DCM_E_OK;
# endif
        }
        /* else NRC 0x22 (already set) */
      }
      /* else NRC 0x22 (already set) */
    }
    /* else NRC 0x22 (already set) */
  }
  /* If any error */
  Dcm_SetNegResponse(errorCode);
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_ObdMgrReadDtcRepeaterProxyGetData
 **********************************************************************************************************************/
/*! \brief      A deffered DTC read repeater proxy. 
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_ObdMgrReadDtcRepeaterProxyGetData(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType result;

# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  Dcm_MsgLenType dataLen = dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.availLen;
# endif

# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* For the first iteration consider the sub-function and the SAM are already copied */
  if(dcmObdMgr_PbIsFirstTime != FALSE)
  {
    /* Clear the ctrl flag */
    dcmObdMgr_PbIsFirstTime = FALSE;
    /* NumDTC is already copied - skip */
    dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.availLen--;
    dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.resData++;/* PRQA S 0489 */ /* QAC 7.0: Increment or decrement operation performed on pointer.*/ /* Better readability */
  }
# endif

  result = Dcm_ObdMgrGetDtc(&dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.resData,
                            &dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.availLen);

# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Paged buffer processing done */
  Dcm_ProcessPage((uint16)(dataLen - dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.availLen));

  DCM_IGNORE_UNREF_PARAM(result);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
# else

  if(DCM_E_PENDING == result)
  {
    return DCM_E_PENDING;
  }

  /* If any error */
  Dcm_SetNegResponse(result);
  /* End of iterations */
  Dcm_ProcessingDone();
# endif
  /* deactivate the repeater in any case (also paged buffer, since the UpdatePage function will trigger it again) */
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_ObdMgrReadDtcByStatusMask
 **********************************************************************************************************************/
/*! \brief      Processes a single PID
 *  \param[in]  statusMask  The status mask to be processed
 *  \param[in]  origin      The DTC origin
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_ObdMgrReadDtcByStatusMask(uint8 statusMask, Dem_DTCOriginType origin)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.statusMask  = statusMask;
  dcmObdRepeatedProxyContexts.dcmObdDtc_ProxyContext.origin = origin;
  Dcm_RegisterRepeaterProxy(Dcm_ObdMgrReadDtcRepeaterProxyProcess);
}

/***********************************************************************************************************************
 *  Dcm_ObdMgrPostReadDtcByStatusMask
 **********************************************************************************************************************/
/*! \brief      OBD DTC Services post processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_ObdMgrPostReadDtcByStatusMask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  Dcm_DemMgrReleaseDemClient(DCM_DEMMGR_CLIENT_ID_OBD);
# endif
}
#endif /* ((DCM_SERVICE_03_ENABLED == STD_ON) || (DCM_SERVICE_07_ENABLED == STD_ON) || (DCM_SERVICE_0A_ENABLED == STD_ON)) */
#if (DCM_SERVICE_01_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService01
 **********************************************************************************************************************/
/*! \brief      Service 0x01 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService01(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_REQUESTOUTOFRANGE;

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* At maximum 6 PID can be requested */
  if(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen <= 6)
  {
    Dcm_ObdIdListItemType pidDescList[6];
    Dcm_ObdIdDescType     pidDesc;

    pidDesc.idInList      = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqData;
    pidDesc.idOutList     = pidDescList;
    pidDesc.idCount       = (uint8)dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen;
    pidDesc.idLookUpTable = dcm01_PidLookUpTable;
# if(DCM_OBD_REQ_PID_DATA_ENABLED == STD_ON)
    pidDesc.idHasReqData  = FALSE;
# endif
    /* Get supported PIDs only */
    Dcm_ObdMgrParseIds(&pidDesc);

    /* Ignore mixed requests or where no PID is supported */
    if((pidDesc.idCount != 0)&&
       (FALSE == pidDesc.isMixedId))
    {
      Std_ReturnType stdReturn;
      uint8_least pidIter = pidDesc.idCount;

      /* prepare for OK */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_OK;

      do
      {
        pidIter--;
        stdReturn = Dcm_01_ProcessPid(&pidDescList[pidIter]);
      }
      while((pidIter != 0)&&
            (DCM_E_OK == stdReturn));

      if(DCM_E_OK != stdReturn)
      {
        dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
  }
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_01_ENABLED == STD_ON) */
#if (DCM_SERVICE_02_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService02
 **********************************************************************************************************************/
/*! \brief      Service 0x02 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService02(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ObdIdHandleType pidIter = (Dcm_ObdIdHandleType)dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen;

  dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_REQUESTOUTOFRANGE;

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* At maximum 3 PID + 3 FF can be requested */
  if((pidIter <= 6)&&
     ((pidIter & 0x01) == 0))/* request length must be an even number */
  {
    uint8 pidList[6];
    uint8 freezeFrameId;
    uint8 pid;
    uint8 processedPids = 0;
    uint8_least pidTypeMask = 0x00;

# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
    boolean lIsReserved;
    lIsReserved = Dcm_DemMgrStealLockDemUdsClient(DCM_DEMMGR_OP_1905);
    if(FALSE == lIsReserved)
    {
      /* reject the execution - no 0x78 shall be used since NRC 0x31 is possible after that!!! */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_BUSYREPEATREQUEST;
    }
    else
# endif
    {
      /* Store the requested data */
      Dcm_CopyRam2Ram(pidList, dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqData, pidIter);

      do
      {
        pidIter--;/* navigate to the FF */
        freezeFrameId = pidList[pidIter];
        pidIter--;/* navigate to the PIF */
        pid = pidList[pidIter];

        dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[0] = pid;
        dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[1] = 0x00; /* Only FF 0x00 is supported */

        /* Accept only FF = 0 */
        if(freezeFrameId == 0x00)
        {
          if(0x02 == pid)
          {
            Dem_DTCType Dtc;
            Dem_ReturnGetDTCOfFreezeFrameRecordType demResult;
            demResult = Dcm_ObdDemWrapGetDtcOfFFRecord(0x00,
                                                      DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                      DEM_DTC_KIND_EMISSION_REL_DTCS,
                                                      &Dtc);
            if(DEM_GET_DTCOFFF_OK == demResult)
            {
              dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[2] = Dcm_GetHiLoByte(Dtc);
              dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[3] = Dcm_GetLoHiByte(Dtc);

              processedPids++;
              Dcm_MsgContextMoveRel(0,4);
            }
            /* Mark PID 0x02 as data PID */
            pidTypeMask |= 0x02;
          }
          else
          {
            Std_ReturnType stdReturn;
            boolean isAvailPid;
            uint8 bufSize;

            bufSize = (uint8)((dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resMaxDataLen > 0xFFu)
                              ?0xFFu:dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resMaxDataLen);

            /* Other data PID */
            stdReturn = Dem_GetOBDFreezeFrameData(pid,
                                                  &(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resData[2]),
                                                  &bufSize);
            if(E_OK == stdReturn)
            {
              uint16 totalLength = (uint16)(bufSize + 2);

              processedPids++;
              Dcm_MsgContextMoveRel(0,(uint16_least)totalLength);/* PRQA S 3750 */ /* QAC 7.0: Implicit conversion: unsigned short to long.*/ /* Use also unsigned 16 to clear the sign bits*/
            }

            /* Distinguish type */
            isAvailPid = Dcm_ObdMgrIsAvailabilityId(pid);
            pidTypeMask |= (uint8_least)((isAvailPid!=FALSE)
                                          ?0x01 /* mark availability PId found */
                                          :0x02);/* mark data PId found */
          }
        }
      }
      while(pidIter != 0);

      /* At least one processed PID */
      if(processedPids != 0)
      {
        /* PIDs of one type detected */
        if(0x03 != pidTypeMask)
        {
          dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_OK;
        }
      }
# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
      Dcm_DemMgrReleaseDemClient(DCM_DEMMGR_CLIENT_ID_OBD);
# endif
    }
  }
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_02_ENABLED == STD_ON) */
#if (DCM_SERVICE_03_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService03
 **********************************************************************************************************************/
/*! \brief      Service 0x03 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService03(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  Dcm_ObdMgrReadDtcByStatusMask(DCM_DTC_BIT_CONF_DTC, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
}

/***********************************************************************************************************************
 *  Dcm_DspPostProcessOBDService03
 **********************************************************************************************************************/
/*! \brief      Service 0x03 post processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostProcessOBDService03(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_ObdMgrPostReadDtcByStatusMask();
}
#endif /* (DCM_SERVICE_03_ENABLED == STD_ON) */
#if (DCM_SERVICE_04_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_04_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x04 polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_04_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  boolean lIsReserved;
  lIsReserved = Dcm_DemMgrStealLockDemUdsClient(DCM_DEMMGR_OP_ALL);
  if(FALSE == lIsReserved)
  {
    return DCM_E_PENDING;/* try later */
  }
  else
# endif
  {
    Dem_ReturnClearDTCType resultClrDtc;

    resultClrDtc = Dcm_ObdDemWrapClearDtc(0xFFFFFFu,
                                          DEM_DTC_KIND_ALL_DTCS,
                                          DEM_DTC_ORIGIN_PRIMARY_MEMORY);

    /* variable initialized in each switch-case */
    switch(resultClrDtc)
    {
      case DEM_CLEAR_OK:
        /* Good case do nothing */
        break;
      case DEM_DTC_PENDING:
        /* try again later */
        return DCM_E_PENDING;
      case DEM_CLEAR_FAILED:
        /* Clear DTC failed */
      default: /* Any other error - fall through */
        dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_CONDITIONSNOTCORRECT;
        break;
    }
  }
  /* dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].resDataLen = 0;  Set by default from the Dcm_DsdDispatcher. */
  /* Processing finished. */
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService04
 **********************************************************************************************************************/
/*! \brief      Service 0x04 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService04(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  {
    /* Length already checked in DsdDispatcher !!! */
    Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

    Dcm_RegisterRepeaterProxy(Dcm_04_RepeaterProxyProcess);
    /* Wait for application */
  }
}

/***********************************************************************************************************************
 *  Dcm_DspPostProcessOBDService04
 **********************************************************************************************************************/
/*! \brief      Service 0x04 post-processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostProcessOBDService04(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  Dcm_DemMgrReleaseDemClient(DCM_DEMMGR_CLIENT_ID_OBD);
# endif
}
#endif /* (DCM_SERVICE_04_ENABLED == STD_ON) */
#if (DCM_SERVICE_06_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService06
 **********************************************************************************************************************/
/*! \brief      Service 0x06 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService06(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MsgLenType lReqDataLen;

  dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_REQUESTOUTOFRANGE;

  lReqDataLen = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen;

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(lReqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */


  /* At maximum 6 MID can be requested */
  if(lReqDataLen <= 6)
  {
    Dcm_ObdIdListItemType midDescList[6];
    Dcm_ObdIdDescType     midDesc;

    midDesc.idInList      = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqData;
    midDesc.idOutList     = midDescList;
    midDesc.idCount       = (uint8)lReqDataLen;
    midDesc.idLookUpTable = dcm06_MidLookUpTable;
# if(DCM_OBD_REQ_PID_DATA_ENABLED == STD_ON)
    midDesc.idHasReqData  = FALSE;
# endif

    /* Get supported MIDs only */
    Dcm_ObdMgrParseIds(&midDesc);

    /* Ignore mixed requests or where no MID is supported */
    if((midDesc.idCount != 0)&& /* not an empty list */
       (FALSE == midDesc.isMixedId)&& /* not an mixed MID type request */
       ((FALSE != midDescList[0].isAvailabilityId) || /* if availability MID -> up to 6*/
        (1 == lReqDataLen)) /* if not an availability MID -> up to 1 (supported and unsupported)*/
       )
    {
      Std_ReturnType stdReturn;
      uint8_least midIter = midDesc.idCount;

      do
      {
        midIter--;
        stdReturn = Dcm_06_ProcessMid(&midDescList[midIter]);
      }
      while((midIter != 0)&&
            (DCM_E_OK == stdReturn));

      if(DCM_E_OK == stdReturn)
      {
        dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_OK;
      }
    }
  }
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_06_ENABLED == STD_ON) */
#if (DCM_SERVICE_07_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService07
 **********************************************************************************************************************/
/*! \brief      Service 0x07 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService07(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  Dcm_ObdMgrReadDtcByStatusMask(DCM_DTC_BIT_PNDG_DTC, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
}

/***********************************************************************************************************************
 *  Dcm_DspPostProcessOBDService07
 **********************************************************************************************************************/
/*! \brief      Service 0x07 post processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostProcessOBDService07(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_ObdMgrPostReadDtcByStatusMask();
}
#endif /* (DCM_SERVICE_07_ENABLED == STD_ON) */
#if (DCM_SERVICE_08_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_08_StartControlId
 **********************************************************************************************************************/
/*! \brief      Service 0x08 reader
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_08_StartControlId(uint8 tidHandle, Dcm_NegativeResponseCodePtrType errorCodePtr)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  stdReturn = dcm08_ServiceInfoTable[tidHandle].Control();
  if(DCM_E_OK != stdReturn)
  {
    /* Make the port behavior compliant to service 0x31 */
    *errorCodePtr = DCM_E_CONDITIONSNOTCORRECT;
  }
  return DCM_E_OK;
}

/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService08
 **********************************************************************************************************************/
/*! \brief      Service 0x08 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService08(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MsgLenType lReqDataLen;

  dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_REQUESTOUTOFRANGE;

  lReqDataLen = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen;

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(lReqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* At maximum 6 TID can be requested */
  if(lReqDataLen <= 6)
  {
    Dcm_ObdIdListItemType tidDescList[6];
    Dcm_ObdIdDescType     tidDesc;

    tidDesc.idInList      = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqData;
    tidDesc.idOutList     = tidDescList;
    tidDesc.idCount       = (uint8)lReqDataLen;
    tidDesc.idLookUpTable = dcm08_TidLookUpTable;
# if(DCM_OBD_REQ_PID_DATA_ENABLED == STD_ON)
    tidDesc.idHasReqData  = TRUE;
# endif


    /* Get supported TIDs only */
    Dcm_ObdMgrParseIds(&tidDesc);

    /* Ignore mixed requests or where no TID is supported */
    if((tidDesc.idCount != 0)&& /* not an empty list */
       (FALSE == tidDesc.isMixedId)&& /* not an mixed TID type request */
       ((FALSE != tidDescList[0].isAvailabilityId) || /* if availability TID -> up to 6*/
        (1 == lReqDataLen)) /* if not an availability TID -> up to 1*/
       )
    {
      Std_ReturnType stdReturn;
      uint8_least tidIter = tidDesc.idCount;

      /* Prepare for OK */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_OK;

      do
      {
        tidIter--;
        stdReturn = Dcm_08_ProcessTid(&tidDescList[tidIter]);
      }
      while((tidIter != 0)&&
            (DCM_E_OK == stdReturn));

      if(DCM_E_OK != stdReturn)
      {
        /* The routine could not be executed. */
        dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
  }
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_08_ENABLED == STD_ON) */
#if (DCM_SERVICE_09_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_09_RepeaterProxyProcess
 **********************************************************************************************************************/
/*! \brief      Service 0x09 polling processor 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_09_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  uint8_least lVidIter = dcmObdRepeatedProxyContexts.dcm09_ProxyContext.vidIter;

  do
  {
    lVidIter--;
    stdReturn = Dcm_09_ProcessVid(&dcmObdRepeatedProxyContexts.dcm09_ProxyContext.vidDescList[lVidIter]);
  }
  while((lVidIter != 0)&&
        (DCM_E_OK == stdReturn));

  switch(stdReturn)
  {
    /*-------------*/
    case DCM_E_OK:
    /*-------------*/
      break;
    /*-------------*/
    case DCM_E_PENDING:
    /*-------------*/
      dcmObdRepeatedProxyContexts.dcm09_ProxyContext.vidIter = (uint8)(lVidIter + 1);/* undo decrement */
      return DCM_E_PENDING;
    /*-------------*/
    case DCM_E_NOT_OK:
    /*-------------*/
    /*-------------*/
    default: /* fall through */
    /*-------------*/
      dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_CONDITIONSNOTCORRECT;
      break;
  }

  /* Processing finished. */
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService09
 **********************************************************************************************************************/
/*! \brief      Service 0x09 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService09(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MsgLenType lReqDataLen;

  dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_REQUESTOUTOFRANGE;

  lReqDataLen = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen;

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(lReqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* At maximum 6 VID can be requested */
  if(lReqDataLen <= 6)
  {
    Dcm_ObdIdDescType     vidDesc;

    vidDesc.idInList      = dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqData;
    vidDesc.idOutList     = dcmObdRepeatedProxyContexts.dcm09_ProxyContext.vidDescList;
    vidDesc.idCount       = (uint8)lReqDataLen;
    vidDesc.idLookUpTable = dcm09_VidLookUpTable;
# if(DCM_OBD_REQ_PID_DATA_ENABLED == STD_ON)
    vidDesc.idHasReqData  = FALSE;
# endif

    /* Get supported VIDs only */
    Dcm_ObdMgrParseIds(&vidDesc);

    /* Ignore mixed requests or where no VID is supported */
    if((vidDesc.idCount != 0)&& /* not an empty list */
       (FALSE == vidDesc.isMixedId)&& /* not an mixed VID type request */
       ((FALSE != vidDesc.idOutList[0].isAvailabilityId) || /* if availability VID -> up to 6*/
        (1 == lReqDataLen)) /* if not an availability VID -> up to 1*/
       )
    {
      /* check for data collision */
      dcmObdRepeatedProxyContexts.dcm09_ProxyContext.did22Handle = (Dcm_MemDidHandleType)Dcm_22_FindDid(Dcm_Make16Bit(0xF8,vidDesc.idOutList[0].id));
      dcmDsdErrorRegister[DCM_CONTEXT_ID_OBD] = DCM_E_OK;/* prepare for positive response */
      dcmObdRepeatedProxyContexts.dcm09_ProxyContext.vidIter = vidDesc.idCount;
      Dcm_RegisterRepeaterProxy(Dcm_09_RepeaterProxyProcess);
      /* Wait for application */
      return;
    }
  }
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_09_ENABLED == STD_ON) */
#if (DCM_SERVICE_0A_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspProcessOBDService0A
 **********************************************************************************************************************/
/*! \brief      Service 0x0A processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspProcessOBDService0A(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_OBD].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  Dcm_ObdMgrReadDtcByStatusMask(DCM_DTC_BIT_DONT_CARE, DEM_DTC_ORIGIN_PERMANENT);
}

/***********************************************************************************************************************
 *  Dcm_DspPostProcessOBDService0A
 **********************************************************************************************************************/
/*! \brief      Service 0x0A post processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostProcessOBDService0A(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  Dcm_ObdMgrPostReadDtcByStatusMask();
}
#endif /* (DCM_SERVICE_0A_ENABLED == STD_ON) */
#if (DCM_SERVICE_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspDiagSessionControl
 **********************************************************************************************************************/
/*! \brief      Service 0x10 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspDiagSessionControl(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least    sesIter;
  Dcm_NegativeResponseCodeType  errorCode;

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  {
    sesIter = Dcm_FindValueUint8(dcm10_SubFuncCfgVariants, dcm10_SubFuncLookUpTable, *dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData);

    if(sesIter != 0)
    {
      sesIter--;
      (void)Dcm_CheckServiceState(dcm10_ServiceInfoTable[sesIter].StateFilterIdx, DCM_STATE_LVL_SUBFUNC, &errorCode);
      if(DCM_E_OK == errorCode)
      {
        /* Compose positive response */
        /* Sub-function already placed */
        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1] = Dcm_GetHiByte(dcm10_ServiceInfoTable[sesIter].ResponseTime.timeOutP2);
        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[2] = Dcm_GetLoByte(dcm10_ServiceInfoTable[sesIter].ResponseTime.timeOutP2);
        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[3] = Dcm_GetHiByte(dcm10_ServiceInfoTable[sesIter].ResponseTime.timeOutP2Ex);
        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[4] = Dcm_GetLoByte(dcm10_ServiceInfoTable[sesIter].ResponseTime.timeOutP2Ex);
        Dcm_AddValue(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resDataLen , Dcm_MsgLenType, 5);

        /* Prepare transition */
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = dcm10_ServiceInfoTable[sesIter].TransIndex;
# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].isConnectionLocked = TRUE;
# endif
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].pendingSessChgIdx = (uint8)sesIter;
        Dcm_RegisterRepeaterProxy(Dcm_10_RepeaterProxyProcess);
        return;/* Wait for application */
      }
    }
    else
    {
      errorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
  }

  Dcm_SetNegResponse(errorCode);
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspPostDiagSessionControl
 **********************************************************************************************************************/
/*! \brief      Service 0x10 post-processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostDiagSessionControl(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  DCM_IGNORE_UNREF_PARAM(status);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

# if (DCM_DSL_PPRH_SESSION_SUPPORT_ENABLED == STD_ON)
  {
    if(0 == dcmCurrentStateInfo[DCM_SESSION_STATE_GRP_IDX]) /* Still in the default session (failed tx on non-default session) or just gone to the default session */
    {
      Dcm_DslFreeSessionOwner(); /* Do it here for the case the final positive response could not be sent or it was a negative response sent */
    }
  }
# endif
}
#endif /* (DCM_SERVICE_10_ENABLED == STD_ON) */
#if (DCM_SERVICE_11_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspPostEcuReset
 **********************************************************************************************************************/
/*! \brief      Service 0x11 post-processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostEcuReset(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  /* even if the positive response could not be sent - do reset (there is no RTE operation undo)!!!*/
  if((status == DCM_RES_POS_OK) ||
     (status == DCM_RES_POS_NOT_OK))
  {
    Dcm_DspPerformReset(DCM_HARD_RESET);
  }
}
#endif /* (DCM_SERVICE_11_ENABLED == STD_ON) */
#if (DCM_SERVICE_11_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspEcuReset
 **********************************************************************************************************************/
/*! \brief      Service 0x11 processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspEcuReset(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least sfIter;

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

# if (DCM_11_SUBFUNC_USER_ENABLED == STD_ON)
  /* Initialize the resetLevel here to know in the post-handler whether to call the application user handler or not.*/
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm11_ProxyContext.resetLevel= (uint8)0xFFu; /* no sub-function can have value above 0x7F!!!*/
# endif

  sfIter = Dcm_FindValueUint8(dcm11_SubFuncCfgVariants, dcm11_SubFuncLookUpTable, *dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData);

  if(sfIter != 0)
  {
    sfIter--;
# if (DCM_SERVICE_11_STATE_TRANS_ENABLED == STD_ON)
    /* Prepare state transition */
    dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = Dcm_11_GetStateTransitionRef(sfIter);
# endif
    (void)Dcm_CheckServiceState(dcm11_ServiceInfoTable[sfIter], DCM_STATE_LVL_SUBFUNC, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
    if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
    {
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm11_ProxyContext.resetLevel=(uint8)*dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData;
      /* Return the sub-function */
      Dcm_MsgContextMoveRel(1,1);
# if (DCM_RESET_DELAY_TIME_ENABLED == STD_ON)
      /* Start parallel count down for the delay */
      Dcm_TmrMgrStartTimer(DCM_TIMER_ID_RST_DELAY, DCM_RESET_DELAY_TIME);
# endif
      Dcm_RegisterRepeaterProxy(Dcm_11_RepeaterProxyProcess);
      return;/* Wait for application */
    }
  }
  else
  {
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  }
  /* Reaching this point means diagnostic error was found */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_11_ENABLED == STD_ON) */
#if (DCM_SERVICE_14_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspClearDiagInfo
 **********************************************************************************************************************/
/*! \brief      Service 0x14 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspClearDiagInfo(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  boolean lIsReserved;
  lIsReserved = Dcm_DemMgrLockDemUdsClient(DCM_DEMMGR_OP_ALL);
  if(FALSE == lIsReserved)
  {
    /* reject the execution */
    dcmDsdErrorRegister[lContext] = DCM_E_BUSYREPEATREQUEST;
    Dcm_ProcessingDone();
  }
  else
# endif
  {
    /* Length already checked in DsdDispatcher !!! */
    Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 3, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

    dcmRepeatedProxyContexts[lContext].dcm14_ProxyContext.dtcNum = Dcm_Make32Bit(0, dcmDsdMsgContext[lContext].reqData[0], dcmDsdMsgContext[lContext].reqData[1], dcmDsdMsgContext[lContext].reqData[2]);

    Dcm_RegisterRepeaterProxy(Dcm_14_RepeaterProxyProcess);
    /* Wait for application */
  }
}

/***********************************************************************************************************************
 *  Dcm_DspPostClearDiagInfo
 **********************************************************************************************************************/
/*! \brief      Service 0x14 post-processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostClearDiagInfo(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  {
    Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();
    DCM_IGNORE_UNREF_PARAM(lContext); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
    Dcm_DemMgrReleaseDemClient(Dcm_DemMgrConvUdsContextId2Clientid(lContext));
  }
# endif
}
#endif /* (DCM_SERVICE_14_ENABLED == STD_ON) */
#if (DCM_SERVICE_19_ENABLED == STD_ON)
# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_RecIdIterReset
 **********************************************************************************************************************/
/*! \brief      Resets an already initialized record id iterator
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_19_RecIdIterReset(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  if(dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.allRecNumbers != FALSE)
  {
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordIterator = dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordListSize;
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordNumber = 0x00;
  }
  else
  {
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordIterator = 1; /* prepare for single iteration */
    dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.recordNumber = dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.reqRecordNumber;
  }
}
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_RecIdIterNext
 **********************************************************************************************************************/
/*! \brief      Returns the next record id (if any) or marks end of iteration.
 *  \param[out] recId   The next record id.
 *  \return     Result of next step iteration.
 *  \retval     DCM_E_OK  - the returned record Id is valid
 *  \retval     DCM_E_NOT_OK  - no more record Ids found.
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_19_RecIdIterNext(P2VAR(uint8, AUTOMATIC, DCM_VAR_NOINIT) recId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn = DCM_E_NOT_OK;
  P2VAR(Dcm_19_ReadRecNumContextType, AUTOMATIC, DCM_VAR_NOINIT) pRecContext;
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  pRecContext = &dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext;

  if(pRecContext->recordIterator != 0)
  {
    pRecContext->recordIterator--;

    stdReturn = DCM_E_OK;

#  if(DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
#   if(DCM_19_REC_TBL_CHK_ENABLED == STD_ON)
    if(pRecContext->recordListSize < 0xFEu)
#   endif
    {
      if(pRecContext->allRecNumbers != FALSE)
      {
        *recId = pRecContext->recordList[pRecContext->recordIterator];
        return DCM_E_OK;
      }
    }
#  endif
    /* Just increment the record number */
    *recId = pRecContext->recordNumber;
    pRecContext->recordNumber++;
  }
  return stdReturn;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_ProcessReportNumDtcByStatusMask
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  origin   Dtc origin.
 *  \param[in]  dtcKind  Dtc Kind.
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_19_ProcessReportNumDtcByStatusMask(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType errorCode;
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  DCM_IGNORE_UNREF_PARAM(lContext);  /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */ /* Avoid warnings in case of no DET support */

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  errorCode = Dcm_19_ProcessNumDtcByStatusMaskData(origin, dtcKind);

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}
# endif

# if (DCM_19_READ_BY_STATUS_MASK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_02_0A_0F_13_15_RepeaterProxyGetData
 **********************************************************************************************************************/
/*! \brief      A deffered DTC read repeater proxy. 
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_19_02_0A_0F_13_15_RepeaterProxyGetData(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType result;
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();
#  if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  Dcm_MsgLenType dataLen = dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.availLen;
#  endif

#  if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* The UpdatePage takes care of this check - skip */
#  else
#   if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  boolean isLocked;
  isLocked = Dcm_DemMgrIsDemClientLocked(DCM_DEMMGR_OP_1902, Dcm_DemMgrConvUdsContextId2Clientid(lContext));
  result = DCM_E_CONDITIONSNOTCORRECT; /* enforce negative response */
  /* Still not lock by the owner ? */
  if(FALSE != isLocked)
#   endif
#  endif
  {
#  if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* For the first iteration consider the sub-function and the SAM are already copied */
    if((dcm19_PbDispSubfunc[lContext] & 0x80) != 0)
    {
      /* Clear the ctrl flag */
      dcm19_PbDispSubfunc[lContext] &= 0x7F;
      /* Sub-func + SAM are already copied - skip */
      Dcm_SubValue(dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.availLen , Dcm_MsgLenType, 2);
      Dcm_AddValue(dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.resData, Dcm_MsgType, 2);/* PRQA S 0488 */ /* QAC 7.0: Performing pointer arithmetic. */ /* Better readability */
    }
#  endif

    result = Dcm_19_02_0A_0F_13_15_GetData(&dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.resData,
                                           &dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.availLen);
  }
#  if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Paged buffer processing done */
  Dcm_ProcessPage((uint16)(dataLen - dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.availLen));

  DCM_IGNORE_UNREF_PARAM(result);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
#  else

  if(DCM_E_PENDING == result)
  {
    return DCM_E_PENDING;
  }

  /* If any error */
  Dcm_SetNegResponse(result);
  /* End of iterations */
  Dcm_ProcessingDone();
#  endif
  /* deactivate the repeater in any case (also paged buffer, since the UpdatePage function will trigger it again) */
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif


# if (DCM_19_READ_BY_STATUS_MASK_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_ReportDtcByStatusMaskData
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  origin                     Dtc origin.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_ReportDtcByStatusMaskData(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_DTCStatusMaskType             dtcStatusMask;
  Dcm_NegativeResponseCodeType      result;
  Dem_ReturnSetDTCFilterType        resultSetDtcFilter;
  Std_ReturnType                    stdResult;
  uint16                            numDtc;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* All error cases will return 0x22 */
  result = DCM_E_CONDITIONSNOTCORRECT;
  dtcStatusMask = (Dem_DTCStatusMaskType)dcmDsdMsgContext[lContext].reqData[0];
  /* Copy the status availability mask (in any case) */
  stdResult = Dem_GetDTCStatusAvailabilityMask(dcmDsdMsgContext[lContext].resData);

  if(E_OK == stdResult)
  {
    /* Form the relevant status bits */
    dtcStatusMask &= dcmDsdMsgContext[lContext].resData[0];
    /* Prepare for DTC response list */
    Dcm_MsgContextMoveRel(0,1);

    resultSetDtcFilter = Dem_SetDTCFilter(dtcStatusMask,
                                          dtcKind,
                                          origin,
                                          DEM_FILTER_WITH_SEVERITY_NO,
                                          DEM_SEVERITY_NO_SEVERITY,
                                          DEM_FILTER_FOR_FDC_NO);
    if(resultSetDtcFilter == DEM_FILTER_ACCEPTED)
    {
      stdResult = Dem_GetNumberOfFilteredDTC(&numDtc);
      if(E_OK == stdResult)
      {
        /* everything went ok */
        /* MUL 4 */
        numDtc <<=2;
        Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen , Dcm_MsgLenType, numDtc);
#  if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
        /* Check for enough linear buffer (leave place for the SID + sub-func + 4 bytes for at least one end check iteration) */
        if((numDtc + 4) <= dcmDsdMsgContext[lContext].resMaxDataLen)
        {
          /* Init linear use case */
          dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.resData = dcmDsdMsgContext[lContext].resData;
          dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.maskContext.availLen = dcmDsdMsgContext[lContext].resMaxDataLen;
          Dcm_RegisterRepeaterProxy(Dcm_19_02_0A_0F_13_15_RepeaterProxyGetData);
          /* Set a special error code for behavior differentiation */
          result = DCM_E_TRANSFERDATASUSPENDED;
        }
        else
        {
          result = DCM_E_RESPONSE_TOO_LONG;
        }
#  else
        /* Starting iterations */
        dcm19_PbDispSubfunc[lContext] = (uint8)(0x02|0x80);
        /* Set a special error code for behavior differentiation */
        result = DCM_E_TRANSFERDATASUSPENDED;
        Dcm_StartPagedProcessing(DCM_PB_CLIENT_19);
#  endif
      }
    }
  }

  return result;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_02_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0F_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_13_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_ProcessReportDtcByStatusMask
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  origin                     Dtc origin.
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_19_ProcessReportDtcByStatusMask(Dem_DTCOriginType origin, Dem_DTCKindType dtcKind)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;
  Std_ReturnType                stdResult;
  Dem_DTCStatusMaskType         statusAvailabilityMask;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();


  errorCode = DCM_E_OK;
  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    /* Get the status availability mask (in any case) */
    stdResult = Dem_GetDTCStatusAvailabilityMask(&statusAvailabilityMask);
    if(E_OK == stdResult)
    {
      /* Check non-zero status mask from the request */
      if((dcmDsdMsgContext[lContext].reqData[0] & (uint8) statusAvailabilityMask) != 0)
      {
        {
          errorCode = Dcm_19_ReportDtcByStatusMaskData(origin, dtcKind);
          if(errorCode == DCM_E_TRANSFERDATASUSPENDED)
          {
            /* Let the page-buffer/debouncer to do the job */
            return;
          }
        }
      }
      else
      {
        /* Copy the status availability mask (in any case) and update response length */
        dcmDsdMsgContext[lContext].resDataLen++;
        dcmDsdMsgContext[lContext].resData[0] = (uint8) statusAvailabilityMask;
      }
    }
    else
    {
      errorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_PrepareDtcAndStatusByteReport
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  origin                     Dtc origin.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_PrepareDtcAndStatusByteReport(Dcm_19_RecordListPtrType iterList, uint8 listSize)
#  else
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_19_PrepareDtcAndStatusByteReport(void)
#  endif
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_DTCStatusMaskType         dtcStatusMask;
  Dem_ReturnGetStatusOfDTCType  resultGetStatus;
  Dcm_NegativeResponseCodeType  result = DCM_E_REQUESTOUTOFRANGE;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
  Dcm_19_RecIdIterInit(dcmDsdMsgContext[lContext].reqData[3], iterList, listSize);
#  else
  Dcm_19_RecIdIterInit(dcmDsdMsgContext[lContext].reqData[3]);
#  endif

  dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.dtcNum = Dcm_Make32Bit(0, dcmDsdMsgContext[lContext].reqData[0], dcmDsdMsgContext[lContext].reqData[1], dcmDsdMsgContext[lContext].reqData[2]);

  resultGetStatus = Dem_GetStatusOfDTC(dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.dtcNum,
                                       DEM_DTC_KIND_ALL_DTCS,
                                       dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.origin,
                                       &dtcStatusMask);
  if(DEM_STATUS_OK == resultGetStatus)
  {
    result = DCM_E_OK;
    /* Shared buffer 
    dcmDsdMsgContext[lContext].resData[0] = Dcm_GetHiLoByte(reqDtc);
    dcmDsdMsgContext[lContext].resData[1] = Dcm_GetLoHiByte(reqDtc);
    dcmDsdMsgContext[lContext].resData[2] = Dcm_GetLoLoByte(reqDtc);
    */
    dcmDsdMsgContext[lContext].resData[3] = (Dcm_MsgItemType)dtcStatusMask;

    /* Adjust the context for rest of response */
    Dcm_MsgContextMoveRel(0,4);
  }

  return result;
}
# endif

# if (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_06_10_Process
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  origin                     Dtc origin.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_19_06_10_Process(Dem_DTCOriginType origin)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType                    errorCode;
  Dem_ReturnGetSizeOfExtendedDataRecordByDTCType  resultGetSize;
  uint16                                          sizeOfExtDataRecord;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /*Set the origin for global usage */
  dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.origin = origin;
  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 4, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    {
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
#   if (DCM_19_EXTDAT_REC_OPT_ENABLED == STD_ON)
      errorCode = Dcm_19_PrepareDtcAndStatusByteReport(dcm19_UsedExtDatRecIds, DCM_19_NUM_EXTDAT_REC);
#   else
      errorCode = Dcm_19_PrepareDtcAndStatusByteReport(NULL_PTR, DCM_19_NUM_EXTDAT_REC);
#   endif
#  else
      errorCode = Dcm_19_PrepareDtcAndStatusByteReport();
#  endif

      if(errorCode == DCM_E_OK)
      {
        resultGetSize = Dcm_19_06_10_GetSizeOfExtDataRecords(&sizeOfExtDataRecord);

        if (DEM_GET_SIZEOFEDRBYDTC_OK == resultGetSize)
        {
          Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen , Dcm_MsgLenType, sizeOfExtDataRecord);
          /* Prepare to iterate */
          Dcm_19_RecIdIterReset();

#  if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
          /* Check for enough linear buffer (leave place for the SID + sub-func) */
          if(sizeOfExtDataRecord <= dcmDsdMsgContext[lContext].resMaxDataLen)
          {
            /* Fill the buffer */
            errorCode = Dcm_19_06_10_GetData(dcmDsdMsgContext[lContext].resData, &dcmDsdMsgContext[lContext].resMaxDataLen);
          }
          else
          { /* IMPROVEMENT: add pagebuffer support (currently 16byte diag buffer needed)*/
            errorCode = DCM_E_RESPONSE_TOO_LONG;
          }
#  else
          /* Starting iterations */
          dcm19_PbDispSubfunc[lContext] = (uint8)(0x06|0x80);
          Dcm_StartPagedProcessing(DCM_PB_CLIENT_19);
          /* Let the page-buffer to do the job */
          return;
#  endif
        }
        else
        {
          if(DEM_GET_SIZEOFEDRBYDTC_W_RNUM == resultGetSize)
          {
            /* Invalid record number */
            errorCode = DCM_E_REQUESTOUTOFRANGE;
          }
        }
      }
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_READ_DTC_SUBFUNC_0B_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0C_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0D_ENABLED == STD_ON) || \
     (DCM_READ_DTC_SUBFUNC_0E_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_19_ProcessReportDtcByOccurrenceTime
 **********************************************************************************************************************/
/*! \brief      A subfunction utility of readDtcInfo.
 *  \param[in]  DTCRequest                   Dtc request type.
 *  \return     NRC
 *  \retval     0  - DCM_E_OK
 *  \retval     >0 - failed
 *  \context    Function must be called from task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_19_ProcessReportDtcByOccurrenceTime(Dem_DTCRequestType DTCRequest)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_DTCType                           Dtc;
  Dem_DTCStatusMaskType                 dtcStatusMask, dtcStatus;
  Dem_ReturnGetDTCByOccurrenceTimeType  returnGetDtc;
  Dcm_NegativeResponseCodeType          errorCode;
  Std_ReturnType                        stdResult;
  Dem_ReturnGetStatusOfDTCType          resultGetStatus;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Check for correct request message length */
  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  {
    errorCode = DCM_E_CONDITIONSNOTCORRECT;

    stdResult = Dem_GetDTCStatusAvailabilityMask(&dtcStatusMask);
    if(E_OK == stdResult)
    {
      {
        returnGetDtc = Dem_GetDTCByOccurrenceTime(DTCRequest, DEM_DTC_KIND_ALL_DTCS, &Dtc);

        if (DEM_OCCURR_OK == returnGetDtc)
        {
           resultGetStatus = Dem_GetStatusOfDTC(Dtc, DEM_DTC_KIND_ALL_DTCS,DEM_DTC_ORIGIN_PRIMARY_MEMORY, &dtcStatus);
           if(DEM_STATUS_OK == resultGetStatus)
           {
             dcmDsdMsgContext[lContext].resData[0] = dtcStatusMask;
             dcmDsdMsgContext[lContext].resData[1] = Dcm_GetHiLoByte(Dtc);
             dcmDsdMsgContext[lContext].resData[2] = Dcm_GetLoHiByte(Dtc);
             dcmDsdMsgContext[lContext].resData[3] = Dcm_GetLoLoByte(Dtc);
             dcmDsdMsgContext[lContext].resData[4] = dtcStatus;
             Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen , Dcm_MsgLenType, 5);
             /* Everything went fine, set positive errorCode */
             errorCode  = DCM_E_OK;
           }
        }
        else
        {
          if (DEM_OCCURR_FAILED == returnGetDtc)
          {
            dcmDsdMsgContext[lContext].resData[0] = dtcStatusMask;
            dcmDsdMsgContext[lContext].resDataLen++;
            /* Everything went fine, but no stored DTC, set positive errorCode and send response with status availability mask only */
            errorCode  = DCM_E_OK;
          }
        }
      }
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}
# endif /*DCM_READ_DTC_SUBFUNC_0B/0C/0D/0E_ENABLED */
#endif /* (DCM_SERVICE_19_ENABLED == STD_ON) */
#if (DCM_SERVICE_19_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcInfo
 **********************************************************************************************************************/
/*! \brief      Service 0x19 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcInfo(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least subFuncIter;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.needsRecordUpdateDisabling = FALSE;
  {
    /* Find sub-function */
    subFuncIter = Dcm_FindValueUint8(dcm19_SubFuncCfgVariants, dcm19_SubFuncLookUpTable, dcmDsdMsgContext[lContext].reqData[0]);

    if(subFuncIter != 0)
    {
      subFuncIter--;

      (void)Dcm_CheckServiceState(dcm19_ServiceInfoTable[subFuncIter].StateFilterIdx, DCM_STATE_LVL_SUBFUNC, &dcmDsdErrorRegister[lContext]);
      if(DCM_E_OK == dcmDsdErrorRegister[lContext])
      {
        /* Skip the sub-function parameters */
        Dcm_MsgContextMoveRel(1, 1);

        if(dcmDsdMsgContext[lContext].reqDataLen == dcm19_ServiceInfoTable[subFuncIter].ReqDataLength)
        {
# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
          boolean lIsReserved;
          lIsReserved = Dcm_DemMgrLockDemUdsClient(dcm19_ServiceInfoTable[subFuncIter].DemOpType);

          if(FALSE == lIsReserved)
          {
            /* reject the execution */
            dcmDsdErrorRegister[lContext] = DCM_E_BUSYREPEATREQUEST;
          }
          else
# endif
          {
            boolean        result;
            Std_ReturnType stdResult = DCM_E_OK;


            result = (boolean)((dcm19_ServiceInfoTable[subFuncIter].DemOpType & (Dcm_DemMgrDemOpType)(DCM_DEMMGR_OP_1904|DCM_DEMMGR_OP_1905|DCM_DEMMGR_OP_1906)) != 0);

            /* Is record update disabling required? */
            if(FALSE != result)
            {
              stdResult = Dcm_DemMgrRequestDisableDtcUpdate(Dcm_DemMgrConvUdsContextId2Clientid(lContext));
              result = (boolean)(stdResult == E_OK);
            }

            /* Story current state */
            dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.needsRecordUpdateDisabling = result;

            if(DCM_E_OK == stdResult)
            {
# if (DCM_SERVICE_19_STATE_TRANS_ENABLED == STD_ON)
              /* Prepare state transition */
              dcmDslInfoPool[lContext].stateTransRef = Dcm_19_GetStateTransitionRef(subFuncIter);
# endif
              /* Call the corresponding sub-function */
              dcm19_ServiceInfoTable[subFuncIter].DtcSubFunction();

              /* If no paged buffer is used or just NRC shall be sent or the SPRMIB was set - enable immediately DTC setting again */
              if((DCM_CONTEXT_STATE_PROCESS_STARTED != dcmDslInfoPool[lContext].contextState) &&
                 (FALSE != dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.needsRecordUpdateDisabling))
              {
                /* re-enable the DEM */
                Dcm_DemMgrRequestEnableDtcUpdate(Dcm_DemMgrConvUdsContextId2Clientid(lContext));
              }
              return;
            }
            else
            {
              dcmDsdErrorRegister[lContext] = DCM_E_CONDITIONSNOTCORRECT;
            }
          }
        }
        else
        {
          dcmDsdErrorRegister[lContext] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
    }
    else
    {
      dcmDsdErrorRegister[lContext] = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
  }
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspPostReadDtcInfo
 **********************************************************************************************************************/
/*! \brief      Service 0x19 post-processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostReadDtcInfo(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  DCM_UDS_CONTEXT_PARAM_LOCAL_IGNORE /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

# if (DCM_DEMMGR_RESMGR_ENABLED == STD_ON)
  Dcm_DemMgrReleaseDemClient(Dcm_DemMgrConvUdsContextId2Clientid(lContext));
# endif

# if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(FALSE != dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.needsRecordUpdateDisabling)
  {
    /* enable always */
    Dcm_DemMgrRequestEnableDtcUpdate(Dcm_DemMgrConvUdsContextId2Clientid(lContext));
  }
# endif
}

# if (DCM_READ_DTC_SUBFUNC_01_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRNODTCBSM
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x01 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRNODTCBSM(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportDtcByStatusMask in primary memory processor*/
  Dcm_19_ProcessReportNumDtcByStatusMask(DEM_DTC_ORIGIN_PRIMARY_MEMORY, DEM_DTC_KIND_ALL_DTCS);
}
# endif

# if (DCM_READ_DTC_SUBFUNC_02_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCBSM
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x02 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCBSM(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportDtcByStatusMask in primary memory processor*/
  Dcm_19_ProcessReportDtcByStatusMask(DEM_DTC_ORIGIN_PRIMARY_MEMORY, DEM_DTC_KIND_ALL_DTCS);
}
# endif

# if (DCM_READ_DTC_SUBFUNC_03_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCSSI
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x03 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCSSI(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;
  Dem_ReturnSetDTCFilterType    resultSetDtcFilter;
  uint16                        NumberOfFilteredRecords;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    {
      resultSetDtcFilter = Dem_SetDTCFilterForRecords(&NumberOfFilteredRecords);
      if (DEM_FILTER_ACCEPTED == resultSetDtcFilter)
      {
        /* everything went ok */
        /* MUL 4 */
        NumberOfFilteredRecords <<=2;
        Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, NumberOfFilteredRecords);

#  if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
        /* Check for enough linear buffer (leave place for the SID + sub-func + 4 byte buffer for at least one iteration for end check) */
        if((NumberOfFilteredRecords + 4)< dcmDsdMsgContext[lContext].resMaxDataLen)
        {
          /* Fill the buffer */
          errorCode = Dcm_19_03_GetData(dcmDsdMsgContext[lContext].resData, &dcmDsdMsgContext[lContext].resMaxDataLen);
        }
        else
        {
          errorCode = DCM_E_RESPONSE_TOO_LONG;
        }
#  else
        /* Starting iterations */
        dcm19_PbDispSubfunc[lContext] = (uint8)(0x03|0x80);
        Dcm_StartPagedProcessing(DCM_PB_CLIENT_19);
        /* Let the page-buffer to do the job */
        return;
#  endif
      }
      else
      { /* DEM_WRONG_FILTER */
        errorCode = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_READ_DTC_SUBFUNC_04_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCSSBDTC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x04 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCSSBDTC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType       errorCode;
  Dem_ReturnGetSizeOfFreezeFrameType status;
  uint16                             snapshotLength;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 4, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    {
      dcmRepeatedProxyContexts[lContext].dcm19_ProxyContext.sharedContexts.recordContext.origin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
#  if (DCM_19_REC_TBL_ITER_ENABLED == STD_ON)
#   if (DCM_19_SNPSHT_REC_OPT_ENABLED == STD_ON)
      errorCode = Dcm_19_PrepareDtcAndStatusByteReport(dcm19_UsedSnpshtRecIds, DCM_19_NUM_SNPSHT_REC);
#   else
      errorCode = Dcm_19_PrepareDtcAndStatusByteReport(NULL_PTR, DCM_19_NUM_SNPSHT_REC);
#   endif
#  else
      errorCode = Dcm_19_PrepareDtcAndStatusByteReport();
#  endif

      if(errorCode == DCM_E_OK)
      {
        status = Dcm_19_04_GetSizeOfFreezeFrames(&snapshotLength);

        if (status != DEM_GET_SIZEOFFF_OK)
        { /* valid dtc but invalid record number */
          errorCode = DCM_E_REQUESTOUTOFRANGE;
        }
        else
        {
          Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, snapshotLength);

          /* Prepare to iterate */
          Dcm_19_RecIdIterReset();
#  if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
          /* Check for enough linear buffer (leave place for the SID + sub-func) */
          if(snapshotLength <= dcmDsdMsgContext[lContext].resMaxDataLen)
          {
            errorCode = Dcm_19_04_GetData(dcmDsdMsgContext[lContext].resData, &dcmDsdMsgContext[lContext].resMaxDataLen);
          }
          else
          {
            errorCode = DCM_E_RESPONSE_TOO_LONG;
          }
#  else
          /* get multiple freezeframes via page buffer */
          /* Starting iterations */
          dcm19_PbDispSubfunc[lContext] = (uint8)(0x04|0x80);
          Dcm_StartPagedProcessing(DCM_PB_CLIENT_19);
          /* Let the page-buffer to do the job */
          return;
#  endif
        }
      }
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_READ_DTC_SUBFUNC_05_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCSSBRN
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x05 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCSSBRN(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode = DCM_E_OK;
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    if(dcmDsdMsgContext[lContext].reqData[0] == 0x00) /* accept only OBD FreezeFrame 0x00 */
    {
      Dcm_MsgLenType  snapshotLength;

      snapshotLength = Dcm_19_05_GetSizeOfFreezeFrames();

      if (0 == snapshotLength)
      { /* if there is no record stored, then return the DTCSnapshotRecordNumber */
        /* dcmDsdMsgContext[lContext].resData[0] = dcmDsdMsgContext[lContext].reqData[0]; */
        dcmDsdMsgContext[lContext].resDataLen++;
      }
      else
      {
        Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, snapshotLength);

        /* Check for enough linear buffer (leave place for the SID + sub-func) */
        if(snapshotLength <= dcmDsdMsgContext[lContext].resMaxDataLen)
        {
          errorCode = Dcm_19_05_CopyFreezeFrames(dcmDsdMsgContext[lContext].resData, &dcmDsdMsgContext[lContext].resMaxDataLen);
        }
        else
        {
          errorCode = DCM_E_RESPONSE_TOO_LONG;
        }
      }
    }
    else
    {
      /* Wrong FF number */
      errorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_READ_DTC_SUBFUNC_06_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCEDRBDN
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x06 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCEDRBDN(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportDtcByStatusMask in primary memory processor*/
  Dcm_19_06_10_Process(DEM_DTC_ORIGIN_PRIMARY_MEMORY);
}
# endif

# if (DCM_READ_DTC_SUBFUNC_07_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRNODTCBSMR
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x07 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRNODTCBSMR(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType errorCode;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Check for correct request message length */
  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 2, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  DCM_UDS_CONTEXT_PARAM_LOCAL_IGNORE /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  errorCode = Dcm_19_07_GetData(DEM_DTC_KIND_ALL_DTCS);

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}
# endif /* DCM_READ_DTC_SUBFUNC_07_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_08_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCBSMR
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x08 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCBSMR(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;
  Std_ReturnType                stdResult;
  Dem_DTCStatusMaskType         statusAvailabilityMask;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 2, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  errorCode = DCM_E_OK;
  {
    /* Get the status availability mask (in any case) */
    stdResult = Dem_GetDTCStatusAvailabilityMask(&statusAvailabilityMask);
    if(E_OK == stdResult)
    {
      /* Check non-zero status mask from the request */
      if((dcmDsdMsgContext[lContext].reqData[1] & (uint8) statusAvailabilityMask) != 0)
      {
        {
          errorCode = Dcm_19_08_Process();
#  if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
          if(errorCode == DCM_E_TRANSFERDATASUSPENDED)
          {
            /* Let the page-buffer to do the job */
            return;
          }
#  endif
        }
      }
      else
      {
        /* Copy the status availability mask (in any case) and update response length */
        dcmDsdMsgContext[lContext].resDataLen++;
        dcmDsdMsgContext[lContext].resData[0] = (uint8) statusAvailabilityMask;
      }
    }
    else
    {
      errorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif /* DCM_READ_DTC_SUBFUNC_08_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_09_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRSIODTC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x09 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRSIODTC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_DTCType                     Dtc;
  Dem_DTCSeverityType             dtcSeverity;
  Dem_ReturnGetSeverityOfDTCType  dtcSeverityReturn;
  Dcm_NegativeResponseCodeType    errorCode;
  Dem_DTCStatusMaskType           dtcStatusAvailabilityMask;
  Dem_DTCStatusMaskType           dtcStatus;
  Dem_ReturnGetStatusOfDTCType    returnGetStatus;
  Dem_ReturnGetViewIDOfDTCType    returnGetViewId;
  Dem_ViewIdType                  viewId;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Check for correct request message length */
  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 3, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* assemble DTC */
  Dtc = (Dem_DTCType)Dcm_Make32Bit(0,dcmDsdMsgContext[lContext].reqData[0], dcmDsdMsgContext[lContext].reqData[1], dcmDsdMsgContext[lContext].reqData[2]);

  errorCode = DCM_E_REQUESTOUTOFRANGE;

  dtcSeverityReturn = Dem_GetSeverityOfDTC(Dtc, &dtcSeverity);
  if (DEM_GET_SEVERITYOFDTC_OK == dtcSeverityReturn)
  {
    (void)Dem_GetDTCStatusAvailabilityMask(&dtcStatusAvailabilityMask);
    returnGetStatus = Dem_GetStatusOfDTC(Dtc, DEM_DTC_KIND_ALL_DTCS, DEM_DTC_ORIGIN_PRIMARY_MEMORY, &dtcStatus);
    if (DEM_STATUS_OK == returnGetStatus)
    {
      returnGetViewId = Dem_GetViewIDOfDTC(Dtc, DEM_DTC_KIND_ALL_DTCS, &viewId);
      if (DEM_VIEWID_OK == returnGetViewId)
      {
        dcmDsdMsgContext[lContext].resData[0] = (Dcm_MsgItemType) dtcStatusAvailabilityMask;
        dcmDsdMsgContext[lContext].resData[1] = (Dcm_MsgItemType) dtcSeverity;
        dcmDsdMsgContext[lContext].resData[2] = (Dcm_MsgItemType) viewId;
        dcmDsdMsgContext[lContext].resData[3] = Dcm_GetHiLoByte(Dtc);
        dcmDsdMsgContext[lContext].resData[4] = Dcm_GetLoHiByte(Dtc);
        dcmDsdMsgContext[lContext].resData[5] = Dcm_GetLoLoByte(Dtc);
        dcmDsdMsgContext[lContext].resData[6] = (Dcm_MsgItemType) dtcStatus;
        Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, 7);
        /* Everything went fine, set PosResponse */
        errorCode  = DCM_E_OK;
      }
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}
# endif /* DCM_READ_DTC_SUBFUNC_09_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_0A_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRSUPDTC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x0A Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRSUPDTC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Simulate read by status ("any status" by setting StatusMask to 0) */
  dcmDsdMsgContext[lContext].reqData[0] = 0x00;
  /* Read all errors */
  errorCode = Dcm_19_ReportDtcByStatusMaskData(DEM_DTC_ORIGIN_PRIMARY_MEMORY, DEM_DTC_KIND_ALL_DTCS);
  if(errorCode == DCM_E_TRANSFERDATASUSPENDED)
  {
    /* Let the page-buffer/debouncer to do the job */
    return;
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif /* (DCM_READ_DTC_SUBFUNC_0A_ENABLED == STD_ON) */

# if (DCM_READ_DTC_SUBFUNC_0B_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRFTFDTC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x0B Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRFTFDTC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate the job to the common processor function */
  Dcm_19_ProcessReportDtcByOccurrenceTime(DEM_FIRST_FAILED_DTC);
}
# endif /* DCM_READ_DTC_SUBFUNC_0B_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_0C_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRFCDTC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x0C Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRFCDTC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate the job to the common processor function */
  Dcm_19_ProcessReportDtcByOccurrenceTime(DEM_FIRST_DET_CONFIRMED_DTC);
}
# endif /* DCM_READ_DTC_SUBFUNC_0C_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_0D_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRMRTFDTC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x0D Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRMRTFDTC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate the job to the common processor function */
  Dcm_19_ProcessReportDtcByOccurrenceTime(DEM_MOST_RECENT_FAILED_DTC);
}
# endif /* DCM_READ_DTC_SUBFUNC_0D_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_0E_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRMRCDTC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x0E Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRMRCDTC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate the job to the common processor function */
  Dcm_19_ProcessReportDtcByOccurrenceTime(DEM_MOST_REC_DET_CONFIRMED_DTC);
}
# endif /* DCM_READ_DTC_SUBFUNC_0E_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_0F_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRMMDTCBSM
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x0F Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRMMDTCBSM(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportDtcByStatusMask in mirror memory processor*/
  Dcm_19_ProcessReportDtcByStatusMask(DEM_DTC_ORIGIN_MIRROR_MEMORY, DEM_DTC_KIND_ALL_DTCS);
}
# endif /* DCM_READ_DTC_SUBFUNC_0F_ENABLED */

# if (DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRMDEDRBDN
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x10 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRMDEDRBDN(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportDtcByStatusMask in mirror memory processor*/
  Dcm_19_06_10_Process(DEM_DTC_ORIGIN_MIRROR_MEMORY);
}
# endif /*(DCM_READ_DTC_SUBFUNC_10_ENABLED == STD_ON)*/

# if (DCM_READ_DTC_SUBFUNC_11_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRNOMMDTCBSM
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x11 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRNOMMDTCBSM(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportNumDtcByStatusMask in mirror memory processor*/
  Dcm_19_ProcessReportNumDtcByStatusMask(DEM_DTC_ORIGIN_MIRROR_MEMORY, DEM_DTC_KIND_ALL_DTCS);
}
# endif /* (DCM_READ_DTC_SUBFUNC_11_ENABLED == STD_ON) */

# if (DCM_READ_DTC_SUBFUNC_12_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRNOOBDDTCBSM
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x12 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRNOOBDDTCBSM(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportNumDtcByStatusMask in primary memory processor*/
  Dcm_19_ProcessReportNumDtcByStatusMask(DEM_DTC_ORIGIN_PRIMARY_MEMORY, DEM_DTC_KIND_EMISSION_REL_DTCS);
}
# endif /* (DCM_READ_DTC_SUBFUNC_12_ENABLED == STD_ON) */

# if (DCM_READ_DTC_SUBFUNC_13_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcROBDDTCBSM
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x13 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcROBDDTCBSM(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate to ReportNumDtcByStatusMask in permanent memory processor*/
  Dcm_19_ProcessReportDtcByStatusMask(DEM_DTC_ORIGIN_PRIMARY_MEMORY, DEM_DTC_KIND_EMISSION_REL_DTCS);
}
# endif /* (DCM_READ_DTC_SUBFUNC_13_ENABLED == STD_ON) */

# if (DCM_READ_DTC_SUBFUNC_14_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCFDC
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x14 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCFDC(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  DCM_UDS_CONTEXT_PARAM_LOCAL_IGNORE /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  /* Read all errors */
  errorCode = Dcm_19_14_Process();
#  if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(errorCode == DCM_E_TRANSFERDATASUSPENDED)
  {
    /* Let the page-buffer to do the job */
    return;
  }
#  endif

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif

# if (DCM_READ_DTC_SUBFUNC_15_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspReadDtcRDTCWPS
 **********************************************************************************************************************/
/*! \brief      Service 0x19 0x15 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDtcRDTCWPS(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_NegativeResponseCodeType  errorCode;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  /* Length already checked in Dcm_DspReadDtcInfo !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen == 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Simulate read by status ("any status" by setting StatusMask to 0) */
  dcmDsdMsgContext[lContext].reqData[0] = 0x00;
  /* Read all errors */
  errorCode = Dcm_19_ReportDtcByStatusMaskData(DEM_DTC_ORIGIN_PERMANENT, DEM_DTC_KIND_EMISSION_REL_DTCS);
  if(errorCode == DCM_E_TRANSFERDATASUSPENDED)
  {
    /* Let the page-buffer/debouncer to do the job */
    return;
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
# endif /* (DCM_READ_DTC_SUBFUNC_15_ENABLED == STD_ON) */
#endif /* (DCM_SERVICE_19_ENABLED == STD_ON) */
#if (DCM_SERVICE_22_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspInitReadDataById
 **********************************************************************************************************************/
/*! \brief      Service 0x22 initialization
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspInitReadDataById(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DidMgrInit();
  {
    DCM_UDS_CONTEXT_ITER_DEF_LOCAL

    DCM_UDS_CONTEXT_ITER_VALUE_INIT;
    DCM_UDS_CONTEXT_ITER_LOOP
    {
      DCM_UDS_CONTEXT_ITER_VALUE_DEC;
# if (DCM_22_NVM_SUPPORT_ENABLED == STD_ON)
      Dcm_22_InitReadNvmData(DCM_UDS_CONTEXT_ITER_VALUE_ONLY);
# endif
      Dcm_22_OemInit(DCM_UDS_CONTEXT_ITER_VALUE_ONLY);
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_DspReadDataById
 **********************************************************************************************************************/
/*! \brief      Service 0x22 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDataById(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8 numDids;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();
  /* Check if at least one DID is available (at least 2 Byte) */
  /* Check if the length is multiple of 2, since each DID is 2 Byte.*/

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen > 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  numDids = (uint8)(dcmDsdMsgContext[lContext].reqDataLen >> 1);
  if( ((dcmDsdMsgContext[lContext].reqDataLen & 0x01) == 0) &&
        /* Also the capacity of the ECU shall not be exceeded */
      (numDids <= DCM_22_MAX_DID_LIST_LEN) )
  {
    /* Dispatch all DIDs */
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.CurDid   = numDids;
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.DidCount = 0;
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.Progress = DCM_22_DISPATCH_FIND_DID;
# if(DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
    dcmRepeatedProxyContexts[lContext].dcm22_ProxyContext.HasPagedDid = FALSE;
# endif
    Dcm_RegisterRepeaterProxy(Dcm_22_RepeaterProxyDispatcher);
    return;
  }
  else
  {
    /* Invalid length */
    dcmDsdErrorRegister[lContext] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  /* Reaching this point means diagnostic error was found */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspPostReadDataById
 **********************************************************************************************************************/
/*! \brief      Service 0x22 post-processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostReadDataById(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status);/* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON) && \
     (DCM_22_INT_PB_USAGE_ENABLED == STD_ON)
  {
    Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();
    /* No more needed - release always here */
    Dcm_DidMgrReleaseDidClient(Dcm_22_UdsContextId2Clientid(lContext));
  }
# endif
}
#endif /* (DCM_SERVICE_22_ENABLED == STD_ON) */
#if (DCM_SERVICE_23_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_23_ReadMemoryBlock
 **********************************************************************************************************************/
/*! \brief      Service 0x23 common read access 
 *  \param[out] tgtAddr          Pointer to the buffer where the memory content will be copied to.
 *  \param[in]  memBlockDef      The source memory block descriptor
 *  \param[out] errorRegister    The operation result
 *  \context    Function shall be called on task level only.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_23_ReadMemoryBlock(Dcm_MsgType tgtAddr, Dcm_MemMgrMemBlockDefPtr memBlockDef, Dcm_NegativeResponseCodePtrType pErrorCode)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* No additional data after address and length */
  /* Response data pointer already correct */
  DCM_IGNORE_UNREF_PARAM(pErrorCode); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
  {
    Dcm_ReturnReadMemoryType result;
    result = Dcm_ReadMemory(
#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
                            memBlockDef->memId,
#  else
                            0,
#  endif
                            memBlockDef->address,
                            memBlockDef->length,
                            tgtAddr
                            );
    switch(result)
    {
      /*--------------------*/
      case DCM_READ_OK:
      /*--------------------*/
        break;
      /*--------------------*/
      case DCM_READ_PENDING:
      /*--------------------*/
        return DCM_E_PENDING;
      /*--------------------*/
      case DCM_READ_FAILED:
      /*--------------------*/
        *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        return DCM_E_NOT_OK;
      default:
        *pErrorCode = DCM_E_GENERALREJECT;
        Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
        return DCM_E_NOT_OK;
    }
  }
# endif

# if (DCM_MEMORY_ACCESS_DIRECT_ENABLED == STD_ON)
#  if (DCM_MEMORY_ACCESS_TEST_ENABLED == STD_ON)
  TscDcm_ReadMemAccess(tgtAddr, memBlockDef->address, memBlockDef->length);
#  else

  {
    Dcm_ApplDataPtrType lDataPtr;
    lDataPtr = Dcm_MemAccHwAbMakePointer(memBlockDef->address);
    Dcm_CopyRam2Ram(tgtAddr, lDataPtr, memBlockDef->length);
  }
#  endif
# endif
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_23_ENABLED == STD_ON) */
#if (DCM_SERVICE_23_ENABLED == STD_ON)
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_23_ReadRepeaterProxy
 **********************************************************************************************************************/
/*! \brief      Service 0x23 read polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_23_ReadRepeaterProxy(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn = Dcm_23_ReadMemoryBlock(&dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData[0], &dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm23_ProxyContext.memBlockDef, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
  if(DCM_E_PENDING != stdReturn)
  {
    /* Error or OK Case -> end */
    Dcm_ProcessingDone();
  }
  return stdReturn;
}
# endif

/***********************************************************************************************************************
 *  Dcm_DspReadMemoryByAddress
 **********************************************************************************************************************/
/*! \brief      Service 0x23 processor
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadMemoryByAddress(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MemoryBlockDescType    memBlockDesc;
  Dcm_MemMgrExtrInfoRsltType memExtrRslt;

  /* Enforce FID extraction */
  memBlockDesc.addrParamSize = 0;
# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
  memBlockDesc.memOp = DCM_MEM_OP_READ;
# endif
  /* Extract the requested memory block information */
  memExtrRslt = Dcm_MemAccExtractMemoryBlockInfo(&memBlockDesc);

  /* if no error - just writes E_OK to the memory */
  dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = dcmMemMgrExtrInfo2NrcMap[memExtrRslt];

  if (DCM_MEMMGR_EXTR_INFO_OK == memExtrRslt)
  {
    if (dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 0)
    {
      /* Analyze the requested memory block */
      Dcm_MemAccAnalyseMemBlock(&memBlockDesc, dcm23_MemBlockHandleTable, dcm23_MemBlockCfgVariants, dcm23_MemBlockStateInfoTable);
      if (DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
      {
        if(memBlockDesc.memBlock.length <= dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resMaxDataLen)
        {
          /* prepare the positive response */
          Dcm_AddValue(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resDataLen , Dcm_MsgLenType, memBlockDesc.memBlock.length);
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
          /* Transfer the info to the global proxy context */
#  if (DCM_MEMMGR_MID_SUPPORT_ENABLED == STD_ON)
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm23_ProxyContext.memBlockDef.memId = memBlockDesc.memBlock.memId;
#  endif
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm23_ProxyContext.memBlockDef.address = memBlockDesc.memBlock.address;
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm23_ProxyContext.memBlockDef.length = memBlockDesc.memBlock.length;
          Dcm_RegisterRepeaterProxy(Dcm_23_ReadRepeaterProxy);
          return;
# else
          (void)Dcm_23_ReadMemoryBlock(&dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData[0], &(memBlockDesc.memBlock), &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
# endif
        }
        else
        {
          dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_RESPONSE_TOO_LONG;
        }
      }
    }
    else
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }

  /* Error Case */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_23_ENABLED == STD_ON) */
#if (DCM_SERVICE_27_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspInitSecurityAccess
 **********************************************************************************************************************/
/*! \brief      Service 0x27 initialization
 *  \context    Function must be called within disabled interrupt context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspInitSecurityAccess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_27_InitSeedKeyState();
# if (DCM_CONFIG_PRECOMPILE_ENABLED == STD_ON)
/* always up to date */
# else
  Dcm_CheckConfigTypeFailed((DCM_27_CONFIG_TYPE == dcm27_ConfigTypeLCfg), DcmServiceId_Init); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
# endif
  {
# if (DCM_27_ATTEMPT_DELAY_ENABLED == STD_ON)
    uint8_least iter = dcm27_SubFuncLookUpTable[0];/* Number of relevant states is here !!! */
    while(iter != 0)
    {
      iter--;
      dcm27_SecLevelStateEngine[iter].AttemptCounter = 0;
#  if (DCM_27_TOTAL_ATTEMPTS_ENABLED == STD_ON)
      dcm27_SecLevelStateEngine[iter].TotalAttemptCounter = 0;
#  endif
    }
# endif
  }
  Dcm_27_OemInit();
}

/***********************************************************************************************************************
 *  Dcm_GetCurrentSecurityLevel
 **********************************************************************************************************************/
/*! \brief      Provides access to the currently active security level value
 *  \return     Current security level
 *  \context    Function must be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_SecLevelType, DCM_CODE) Dcm_GetCurrentSecurityLevel(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_GetSecurityLevel);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  return dcmStateGroupInfo[DCM_SECACCESS_STATE_GRP_IDX].StateValuePtr[dcmCurrentStateInfo[DCM_SECACCESS_STATE_GRP_IDX]];
}

/***********************************************************************************************************************
 *  Dcm_GetSecurityLevel
 **********************************************************************************************************************/
/*! \brief      Provides access to the currently active security level value
 *  \param[out] SecLevel      Will contain the current secrtiy level
 *  \return     Operation status
 *  \retVal     DCM_E_OK      - success
 *  \context    Function must be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel( P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  *SecLevel = Dcm_GetCurrentSecurityLevel();
  return DCM_E_OK;
}
#endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
#if (DCM_SERVICE_27_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_27_InitSeedKeyState
 **********************************************************************************************************************/
/*! \brief      Initialize the seed-key state
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_27_InitSeedKeyState(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcmSeedKeyProxyParam.MayExecuteSendKey = FALSE;
  dcmSeedKeyProxyParam.SecLevIdxOnGotSeed = 0;
}

/***********************************************************************************************************************
 *  DcmOnChgStateSecurityAccess
 **********************************************************************************************************************/
/*! \brief      Notification function for security access level change
 *  \param[in]  stateGroupIdx                 Index of the state group, the transition belongs to.
 *  \param[in]  newStateIdx                   Index of the new state.
 *  \context    Function could be called on task level or interrupt level (higher task prio).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) DcmOnChgStateSecurityAccess(uint8_least stateGroupIdx, uint8 newStateIdx)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_SetSecurityLevel);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  DCM_IGNORE_UNREF_PARAM(stateGroupIdx); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
  DCM_IGNORE_UNREF_PARAM(newStateIdx); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */

  Dcm_27_InitSeedKeyState();
}

/***********************************************************************************************************************
 *  Dcm_DspSecurityAccess
 **********************************************************************************************************************/
/*! \brief      Serivce 0x27 processor
 *  \context    Function could be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspSecurityAccess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least                   secIter;
  Dcm_NegativeResponseCodeType  errorCode = DCM_E_OK; /* PRQA S 3197 */ /* QAC 7.0:  The initialiser for 'stdReturn' is always modified before being used. */ /* Safety code */

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Prepare for positive response */
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    uint8 secLevel;
    /* SA Level == get_Seed sub-function */
    secLevel = dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0];
    /* Check for even number (send key) (exclude zero sub-function) */
    if(((secLevel & 0x01) == 0)&&(secLevel != 0))
    {
      secLevel--;
    }

    secIter = Dcm_FindValueUint8(dcm27_SubFuncCfgVariants, dcm27_SubFuncLookUpTable, secLevel);
    /* Found ? */
    if(secIter != 0)
    {
      /* Compensate the offset */
      secIter--;
      /* Prepare */
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm27_ProxyContext.IsGetSeedRequest = (boolean)((dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0] & 0x01) != 0);
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm27_ProxyContext.IsZeroSeedRequest = FALSE; /* per default - real seed request ! */

      Dcm_MsgContextMoveRel(1, 1);

      /* Distinguish between seed and key requests */
      if(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm27_ProxyContext.IsGetSeedRequest != FALSE)
      {
          /*-------------------------------*/
          /*      Process GET_SEED         */
          /*-------------------------------*/
        /* Prepare transition */
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = dcm27_ServiceInfoTable[secIter].SeedTransIndex;
        if(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == dcm27_ServiceInfoTable[secIter].SeedRecordLength)
        {
# if (DCM_27_ATTEMPT_DELAY_ENABLED == STD_ON)
          /* Check unlock permition */
          if(dcmTimerEngine[DCM_TIMER_ID_SA] == 0)
          {
#  if (DCM_27_TOTAL_ATTEMPTS_ENABLED == STD_ON)
            if((dcm27_SecLevelStateEngine[secIter].TotalAttemptCounter < dcm27_ServiceInfoTable[secIter].NumMaxAttLock)&&
               (dcm27_ServiceInfoTable[secIter].NumMaxAttLock != 0))
#  endif
# endif
            {
              (void)Dcm_CheckServiceState(dcm27_ServiceInfoTable[secIter].SeedStateFilterIdx, DCM_STATE_LVL_SUBFUNC, &errorCode);
              if(DCM_E_OK == errorCode)
              {
                uint8 currSecLevelId;
                currSecLevelId = Dcm_GetCurrentSecurityLevel();

                /* Store current "request seed" level for later check on the "send key"*/
                dcmSeedKeyProxyParam.SecLevIdxOnGotSeed = (uint8)secIter;
                /* Dont't forget the sub-function */
                Dcm_AddValue(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resDataLen , Dcm_MsgLenType, dcm27_ServiceInfoTable[secIter].SeedLength);

                /* Check for unlocked (compare seed level with the current level) */
                if(secLevel == currSecLevelId)
                {
                  uint16_least seedIter = DCM_27_MAX_SEED_LENGTH;
                  while(seedIter != 0)
                  {
                    seedIter--;
                    dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resData[seedIter] = 0x00;
                  }
                  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm27_ProxyContext.IsZeroSeedRequest = TRUE; /* do not await key after that seed! */
                }
                else
                {
                  Dcm_RegisterRepeaterProxy(Dcm_27_RepeaterProxyGetSeed);
                  return;/* Wait for application */
                }
              }
              /* else error code already set */
            }
# if (DCM_27_ATTEMPT_DELAY_ENABLED == STD_ON)
#  if (DCM_27_TOTAL_ATTEMPTS_ENABLED == STD_ON)
            else
            {
              errorCode = DCM_E_EXCEEDNUMBEROFATTEMPTS;
            }
#  endif
          }
          else
          {
            errorCode = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
          }
# endif
        }
        else
        {
          errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
      else
      {
        /*-------------------------------*/
        /*      Process SEND_KEY         */
        /*-------------------------------*/
        /* Prepare transition */
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = dcm27_ServiceInfoTable[secIter].KeyTransIndex;

        if(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == dcm27_ServiceInfoTable[secIter].KeyLength)
        {
          (void)Dcm_CheckServiceState(dcm27_ServiceInfoTable[secIter].KeyStateFilterIdx, DCM_STATE_LVL_SUBFUNC, &errorCode);
          if(DCM_E_OK == errorCode)
          {
            if((dcmSeedKeyProxyParam.MayExecuteSendKey != FALSE) &&
               (dcmSeedKeyProxyParam.SecLevIdxOnGotSeed == secIter))
            {
              Dcm_RegisterRepeaterProxy(Dcm_27_RepeaterProxySendKey);
              return;/* Wait for application */
            }
            else
            {
              errorCode = DCM_E_REQUESTSEQUENCEERROR;
            }
          }
          /* else - error code already set */
        }
        else
        {
          errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
    }
    else
    {
      errorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
  }

  Dcm_SetNegResponse(errorCode); /* DCM_E_OK gives PosResponse */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspPostSecurityAccess
 **********************************************************************************************************************/
/*! \brief      Service 0x27 post-processor
 *  \param[in]  status       service and response status
 *  \context    Function must be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostSecurityAccess(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  if(status == DCM_RES_POS_OK)
  {
    dcmSeedKeyProxyParam.MayExecuteSendKey =(boolean)( (dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm27_ProxyContext.IsGetSeedRequest != FALSE)
                                                     &&(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm27_ProxyContext.IsZeroSeedRequest == FALSE));
  }
  else
  {
    Dcm_27_InitSeedKeyState();
  }
}
#endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
#if (DCM_SERVICE_28_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspCommunicationControl
 **********************************************************************************************************************/
/*! \brief      Service 0x28 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspCommunicationControl(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least    luPos;
  boolean        lvalidParams;
  Dcm_NegativeResponseCodeType  errorCode;

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  /* Min Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    luPos = Dcm_FindValueUint8(dcm28_SubFuncCfgVariants, dcm28_SubFuncLookUpTable, *dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData);

    if(luPos != 0)
    {
      luPos--;
      (void)Dcm_CheckServiceState(dcm28_StateInfoTable[luPos], DCM_STATE_LVL_SUBFUNC, &errorCode);
      if(DCM_E_OK == errorCode)
      {
# if (DCM_SERVICE_28_STATE_TRANS_ENABLED == STD_ON)
        /* Prepare state transition */
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = Dcm_28_GetStateTransitionRef(luPos);
# endif
        /* Extract operation type */
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.RxState = (boolean)((*dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData & 0x02) == 0);
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.TxState = (boolean)((*dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData & 0x01) == 0);
        /* Echo sub-func in response */
        Dcm_MsgContextMoveRel(1,1);

        /* Only the CommParam shall remain */
        if(1 == dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen)
        {
          /* Extract parameters */
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.SubNetId = (uint8)((*dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData & 0xF0) >> 4);
          dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm28_ProxyContext.MsgType =  (uint8)(*dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData & 0x0F);

# if (DCM_28_ANY_COM_PARAM_ENABLED == STD_ON)
          lvalidParams = Dcm_28_HasValidParams();
# else
          luPos = Dcm_FindValueUint8(dcm28_ComParamCfgVariants, dcm28_ComParamLookUpTable, *dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData);
          lvalidParams = (boolean)(luPos != 0);
# endif
          if(lvalidParams != FALSE)
          {
            Dcm_28_InterpretParams();
            Dcm_RegisterRepeaterProxy(Dcm_28_RepeaterProxyProcess);
            return;/* Wait for application */
          }
          else
          {
            /* Wrong comm param value */
            errorCode = DCM_E_REQUESTOUTOFRANGE;
          }
        }
        else
        {
          /* Too many/less parameters */
          errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
    }
    else
    {
      errorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
  }

  Dcm_SetNegResponse(errorCode);
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspPostCommunicationControl
 **********************************************************************************************************************/
/*! \brief      Service 0x28 post-processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostCommunicationControl(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  if(status == DCM_RES_POS_OK)
  {
    Dcm_28_PostHandling();
  }
}
#endif /* (DCM_SERVICE_28_ENABLED == STD_ON) */
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2A_SchedulerStopAll
 **********************************************************************************************************************/
/*! \brief      Stops all scheduled DIDs
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopAll(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least iter = DCM_2A_SCHEDULER_SIZE;
  while(iter != 0)
  {
    iter--;
    Dcm_2A_SchedulerStopItem(iter);
  }
}

# if (DCM_SERVICE_2C_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2A_SchedulerStopDidById
 **********************************************************************************************************************/
/*! \brief      Stops all scheduled DIDs
 *  \param[in]  did       the DID to be stopped
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopDidById(uint16 did)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Find DID (use main pool since each read-able DID is accessible by 0x2A)*/
  Dcm_DidHandleType didHandle2A;

  didHandle2A = Dcm_2A_FindDid(did);
  Dcm_2A_SchedulerStopDid(didHandle2A);
}
# endif

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerStopItem
 **********************************************************************************************************************/
/*! \brief      Stops a specific scheduler entry
 *  \param[in]  itemPos       entry reference to be stopped
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_2A_SchedulerStopItem(uint8_least itemPos)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Stop only active items */
  if(dcm2A_SchedulerTable[itemPos].Rate < DCM_2A_RATE_TYPE_WAIT_STOP)
  {
    /* Stop the timer */
    Dcm_TmrMgrStopTimer((Dcm_TimerIdType)(DCM_TIMER_ID_SCHEDULER_0 + itemPos));

    if(itemPos == dcm2A_ProcessorState.ProcessingItem)
    {
      dcm2A_SchedulerTable[itemPos].Rate = DCM_2A_RATE_TYPE_WAIT_STOP;
    }
    else
    {
      dcm2A_SchedulerTable[itemPos].Rate = DCM_2A_RATE_TYPE_STOPPED;
      /* Enforce immediate timeout to release the resources */
      Dcm_EvMgrSetEvent(DCM_TASK_ID_SCHEDULER, Dcm_2A_MakeEventOfTimerIdx(itemPos));
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_2A_SchedulerGetItemPos
 **********************************************************************************************************************/
/*! \brief      Stops a specific scheduler entry
 *  \param[in]  didHandle       a handle to periodic 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(uint8_least, DCM_CODE) Dcm_2A_SchedulerGetItemPos(Dcm_DidHandleType didHandle22)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  if(didHandle22 < DCM_NUM_DIDS)
  {
    uint8_least iter = DCM_2A_SCHEDULER_SIZE;
    while(iter != 0)
    {
      iter--;
      if((dcm2A_SchedulerTable[iter].Rate != DCM_2A_RATE_TYPE_STOPPED) &&
         (dcm2A_SchedulerTable[iter].DidHandle == didHandle22))
      {
        return iter;
      }
    }
  }
  return DCM_2A_SCHEDULER_SIZE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspInitReadDataByPeriodicId
 **********************************************************************************************************************/
/*! \brief      Service 0x2A initialization
 *  \context    Function must be called with interrupt disabled context.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspInitReadDataByPeriodicId(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  dcm2A_ProcessorState.TxHandle = DCM_PERIODIC_HANDLE_INVALID;
  dcm2A_ProcessorState.NextItem = 0;
  dcm2A_ProcessorState.NumItems = 0;
  dcm2A_ProcessorState.ProcessingItem = DCM_2A_SCHEDULER_SIZE;

  {
    uint8_least iter = DCM_2A_SCHEDULER_SIZE;
    while(iter != 0)
    {
      iter--;
      dcm2A_SchedulerTable[iter].Rate = DCM_2A_RATE_TYPE_STOPPED;
      /* Initialized later:
      dcm2A_SchedulerTable[iter].DidHandle = DCM_NUM_DIDS;
      dcm2A_SchedulerTable[iter].Length = 0;
      */
    }
  }

  /* Init transmission unit */
  Dcm_PruInit();
}


/***********************************************************************************************************************
 *  DcmOnTimeoutScheduler
 **********************************************************************************************************************/
/*! \brief      Timeout handler for all scheduled DIDs
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) DcmOnTimeoutScheduler(Dcm_TimerIdType timerId)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Timeout on timer x -> activate scheduler task */
  Dcm_EvMgrSetEvent(DCM_TASK_ID_SCHEDULER, Dcm_2A_MakeEventOfTimerIdx((Dcm_TimerIdType)(timerId - DCM_TIMER_ID_SCHEDULER_0)));
}

/***********************************************************************************************************************
 *  Dcm_DspPostReadDataByPeriodicId
 **********************************************************************************************************************/
/*! \brief      Service 0x2A post-processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostReadDataByPeriodicId(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Only in case of fast, med, slow */
  if(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Rate < DCM_2A_RATE_TYPE_WAIT_STOP)
  {
    if(status == DCM_RES_POS_OK)
    {
      /* add to the scheduler */
      Dcm_2A_SchedulerEnableAddedDids(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Rate);
      /* Register (again) the new connection id */
      Dcm_PruReserveConnection(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.reqConnId);
    }
    else
    {
      /* Undo added DIDs */
      Dcm_2A_SchedulerRemoveAddedDids();
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_DspReadDataByPeriodicId
 **********************************************************************************************************************/
/*! \brief      Service 0x2A processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspReadDataByPeriodicId(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Init always for the post-handler */
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.reqConnId = dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dslHandle;
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2A_ProxyContext.Rate = DCM_2A_RATE_TYPE_INVALID;

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen > 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* If single connection 
   * or 
   * single session owner - no check required! */
  {
# if (DCM_DSL_PRU_NEEDS_CONNECTION_LOCK == STD_ON)
    Dcm_ConnectionRefType lCurConnId;

    lCurConnId = Dcm_PruGetUsedConnection();
    /* Check if already owned by a tester */
    if((lCurConnId != DCM_CONNECTION_ID_INVALID)&&
       (lCurConnId != dcmDslInfoPool[DCM_CONTEXT_ID_UDS].dslHandle))
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
# endif
    {
      uint8           subFuncId;
      Dcm_2A_RateType rate;

      subFuncId = dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0];
      /* "SubFunction" available ? */
      rate = Dcm_2A_FindSubFunction(subFuncId);

      if(rate < DCM_2A_RATE_TYPE_INVALID)
      {
        /* Prepare service specific data */
        Dcm_MsgContextMoveRel(1, 0);

        /* Delegate to the corresponding sub-function processor */
        if(subFuncId != 0x04u)
        {
          Dcm_2A_ProcessUpdateScheduler(rate);
        }
        else
        {
          Dcm_2A_ProcessStopScheduler();
        }
        return;
      }
      else
      {
        /* Invalid "SubFunction" = ID -> 0x31 */
        dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
      }
    }
  }
  /* Reaching this point means diagnostic error was found */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_2A_ENABLED == STD_ON) */
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_2C_IsDidAvailable
 **********************************************************************************************************************/
/*! \brief      Check if a DDDID is already defined
 *  \param[in]  did         a DID to be checked
 *  \return     Operation result
 *  \retval     TRUE  - DDDID is defined or if it is not DDDID at all
 *  \retval     FALSE - it is a DDDID but is currently not defined
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(boolean, DCM_CODE) Dcm_2C_IsDidAvailable(uint16 did)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DidHandleType dynDidHandle;

  /* Check DynDID availability */
  dynDidHandle = Dcm_2C_FindDid(did);
  if(dynDidHandle < DCM_NUM_DIDS)
  {
    if(dcm2C_DynDidTempInfoTable[dynDidHandle].ResDataLen == 0)
    {
      /* DynDid is defined */
      return FALSE;
    }
  }
  return TRUE;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_2C_CommonDynDidReadDataLength
 **********************************************************************************************************************/
/*! \brief      Check if a DDDID is already defined
 *  \param[out] resDataLen         a pointer to the result length
 *  \param[in]  dynDidHandle       handle to the DDDID to be appended to
 *  \return     Operation result
 *  \retval     DCM_E_OK  - success
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_2C_CommonDynDidReadDataLength(Dcm_RteDataLenPtrType resDataLen, Dcm_2C_DidHandleType dynDidHandle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  *resDataLen = dcm2C_DynDidTempInfoTable[dynDidHandle].ResDataLen;
  return DCM_E_OK;
}

/***********************************************************************************************************************
 *  Dcm_2C_CommonDynDidReadData
 **********************************************************************************************************************/
/*! \brief      Read DDDID content processor
 *  \param[out] resData            a pointer to the response data
 *  \param[in]  dynDidHandle       handle to the DDDID to be read
 *  \return     Operation result
 *  \retval     DCM_E_OK       - success
 *  \retval     DCM_E_PENDING  - try later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_2C_CommonDynDidReadData(Dcm_RteDataPtrType resData, Dcm_2C_DidHandleType dynDidHandle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* DynDID read processor free? */
  if(DCM_2C_NUM_DYN_DEF_IDS == dcm2C_ReadDataState.CurUsedDidHandle)
  {
    /* Store the working pid reference */
    dcm2C_ReadDataState.CurUsedDidHandle = (Dcm_2C_MemDidHandleType)dynDidHandle;
    dcm2C_ReadDataState.ResData = (Dcm_MsgType)resData; /* PRQA S 0310 */ /* PRQA S 0308 */
    /* Start from the begining */
    dcm2C_ReadDataState.CurrentItem = 0;
    /* Lock the PID processing */
# if (DCM_2C_CLEAR_DYN_DID_WAIT_ENABLED == STD_ON)
    dcm2C_ReadDataState.WaitingForReadEnd = FALSE;
# endif
  }
  else
  {
    /* Parallel 2C request? (same DynDID is guaranteed by the LockReadDid) */
    if(dynDidHandle != dcm2C_ReadDataState.CurUsedDidHandle)
    {
      /* Try later */
      return DCM_E_PENDING;
    }
  }

  return Dcm_2C_RepeaterProxyReadData();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_2C_CalcResDataLen
 **********************************************************************************************************************/
/*! \brief      Calculates the total DDDID length
 *  \param[in]  dynDidHandle       handle to the DDDID to be read
 *  \param[in]  numOfItems         only the first N items will be considered
 *  \return     The total response length
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_2C_CalcResDataLen(Dcm_2C_DidHandleType dynDidHandle, Dcm_2C_DidHandleType numOfItems)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MsgLenType result;

  result = 0;

  while(numOfItems != 0)
  {
    numOfItems--;
# if (DCM_2C_MULTI_DEF_SUPPORT_ENABLED == STD_ON)
    if(Dcm_2C_IsDidRefDefinitionAt(dynDidHandle, numOfItems))
# endif
    {
# if (DCM_2C_DEF_DYN_ID_BY_DID_ENABLED == STD_ON)
      /*DCM_2C_MEMBER_SRC_PID*/
      Dcm_AddValue(result , Dcm_MsgLenType, dcm2C_DynDidInfoRefTable[dynDidHandle].pItems[numOfItems].SrcDid.size);
# endif
    }
# if (DCM_2C_MULTI_DEF_SUPPORT_ENABLED == STD_ON)
    else
# endif
    {
# if (DCM_2C_DEF_DYN_ID_BY_MEM_ENABLED == STD_ON)
      /*DCM_2C_MEMBER_MEM_BLOCK*/
      Dcm_AddValue(result , Dcm_MsgLenType, dcm2C_DynDidInfoRefTable[dynDidHandle].pItems[numOfItems].MemBlock.length);
# endif
    }
  }
  return result;
}

/***********************************************************************************************************************
 *  Dcm_2C_ClearDynDefTable
 **********************************************************************************************************************/
/*! \brief      Clears the whole definition table
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_2C_ClearDynDefTable(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_2C_DidHandleType iter;
  iter = DCM_2C_NUM_DYN_DEF_IDS;
  while(iter != 0)
  {
    iter--;
    Dcm_2C_ClearSingleDid(iter);
  }
}

/***********************************************************************************************************************
 *  Dcm_DspInitDynamicallyDefineDataId
 **********************************************************************************************************************/
/*! \brief      Service 0x31 initialization
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspInitDynamicallyDefineDataId(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_2C_ClearDynDefTable();

  /**
   *Not needed to be init since the at request run-time will be done.
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.CurrentItem = 0;
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle = 0;
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.curReqContextHandle = 0;
   */
  /* Mark as invalid */
  dcm2C_ReadDataState.CurUsedDidHandle = DCM_2C_NUM_DYN_DEF_IDS;
}

/***********************************************************************************************************************
 *  Dcm_DspPostDynamicallyDefineDataId
 **********************************************************************************************************************/
/*! \brief      Service 0x2C post-processing
 *  \param[in]  status        response transmission and service processing status
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostDynamicallyDefineDataId(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  if(status == DCM_RES_POS_OK)
  {
    if(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.OpType == DCM_2C_OP_TYPE_CLEAR)
    {
      /* Clear both temp and permanent PID informations */
      if(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle < DCM_2C_NUM_DYN_DEF_IDS)
      {
        Dcm_2C_ClearSingleDid(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle);
      }
      else
      {
        /* Clear the table */
        Dcm_2C_ClearDynDefTable();
      }
    }
    else
    {
      /* Allow the new PID information access */
      *dcm2C_DynDidInfoRefTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle].pNumOfItems = dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems;
      dcm2C_DynDidTempInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle].ResDataLen = Dcm_2C_CalcResDataLen(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle, dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems);
    }
  }
}

/***********************************************************************************************************************
 *  Dcm_2C_AnalyzeDynDid
 **********************************************************************************************************************/
/*! \brief      Service 0x2C DID look-up and evaluation routine
 *  \return     DDDID handle reference
 *  \retval     0 - (DCM_NUM_DIDS-1) - success
 *  \retval     DCM_NUM_DIDS         - failed
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Dcm_2C_DidHandleType, DCM_CODE) Dcm_2C_AnalyzeDynDid(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DidHandleType didHandle = DCM_NUM_DIDS;

  /* At least a DID must be in the request */
  if(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen >= 2)
  {
    /* Find out if the DID exists and... */
    didHandle = Dcm_2C_FindDid(Dcm_Make16Bit(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0],
                                             dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1]));

    if(didHandle < DCM_NUM_DIDS)
    {
      /* Echoe the request DID parameter */
      /* Substract the DID word */
      Dcm_MsgContextMoveRel(2,2);

      /* Store for the post-procesing */
      dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle = (Dcm_2C_MemDidHandleType)didHandle;
      /* Dispatch the 0x2C DID */
      (void)Dcm_DidMgrAnalyseDid(DCM_DIDMGR_CLIENT_ID_2C, dcm2C_DidStateInfoTable[didHandle]);
    }
    else
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  return (Dcm_2C_DidHandleType)didHandle;
}

/***********************************************************************************************************************
 *  Dcm_2C_FinalizeDidDefinition
 **********************************************************************************************************************/
/*! \brief      Finalization of the DDDID append operation
 *  \param[in]  dynDidHandle       handle to the DDDID to be finalized
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(void, DCM_CODE) Dcm_2C_FinalizeDidDefinition(Dcm_2C_DidHandleType dynDidHandle)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Check the total response length if fits in a TP message or in a single frame for 0x2C */
  if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
  {
    uint16  resLen;
# if (DCM_SERVICE_2A_ENABLED == STD_ON)
    Dcm_DidHandleType didHandle;
    boolean           isPeriodicDid = FALSE;
# endif
    /* Use the temp table since there is the total new num ot items !!! */
    resLen = Dcm_2C_CalcResDataLen(dynDidHandle, dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.NumOfItems);
# if (DCM_SERVICE_2A_ENABLED == STD_ON)
    didHandle = Dcm_2A_FindDid(dcmDidLookUpTable[dcm2C_DidHandleTable[dynDidHandle+1]]);
    if(didHandle < DCM_NUM_DIDS)
    {
      isPeriodicDid = TRUE;
    }
# endif
    /* Allow only linear buffer access */
    if((resLen > (uint8)(dcmDslInfoPool[DCM_CONTEXT_ID_UDS].maxBufferLength - 3)) /* Substract the 3 bytes for SID and DID */
# if (DCM_SERVICE_2A_ENABLED == STD_ON)
      || ((isPeriodicDid != FALSE) &&
#  if (DCM_PERIODIC_TRANS_TYPE2_ENABLED == STD_ON)
      /* Use this API Dcm_PruGetMaxDataLen() instead of 8 */
      (resLen > (uint8)(8 - 1)) /* Substract the 1 Byte for the PID */
#  endif
#  if (DCM_PERIODIC_TRANS_TYPE1_ENABLED == STD_ON)
      /* Use this API PduRMaxSFDataLen(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].busInfo) instead of 5/4 */
      (resLen > (uint8)(7 - 2)) /* Substract the 2 bytes for SID and DID (only low Byte is sent) */
#  endif
      )/* && */
# endif
      )/* || */
    {
      /* later calling Dcm_SetNegResponse this error will be ignored if the above
      * append functions have detected another error!!!*/
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  Dcm_ProcessingDone();
}

/***********************************************************************************************************************
 *  Dcm_DspDynamicallyDefineDataId
 **********************************************************************************************************************/
/*! \brief      Service 0x2C processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspDynamicallyDefineDataId(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Set it here to process in post handler the right clear operation !! */
  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.LastUsedDynDidHandle = DCM_2C_NUM_DYN_DEF_IDS;
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen > 0, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.OpType = Dcm_2C_FindSubFunction(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0]);
  /* Skip the sub-function */
  /* Echo the request sub-function parameter */
  Dcm_MsgContextMoveRel(1,1);

  switch(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2C_ProxyContext.OpType)
  {
# if (DCM_2C_DEF_DYN_ID_BY_DID_ENABLED == STD_ON)
  /*-------------------------------*/
  case DCM_2C_OP_TYPE_DEF_BY_ID:
  /*-------------------------------*/
    Dcm_2C_DefineDynDidByDid();
    break;
# endif
# if (DCM_2C_DEF_DYN_ID_BY_MEM_ENABLED == STD_ON)
  /*-------------------------------*/
  case DCM_2C_OP_TYPE_DEF_BY_MEM:
  /*-------------------------------*/
    Dcm_2C_DefineDynDidByMem();
    break;
# endif
  /*-------------------------------*/
  case DCM_2C_OP_TYPE_CLEAR:
  /*-------------------------------*/
    Dcm_2C_ClearDynDid();
    break;
  default:
    /* Unknown sub-function - exit immediately */
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    Dcm_ProcessingDone();
    break;
  }
}
#endif /* (DCM_SERVICE_2C_ENABLED == STD_ON) */
#if (DCM_SERVICE_2E_ENABLED == STD_ON)
/*  ********************************************************************************
 * Function name:Dcm_DspInitWriteDataById
 * Description: 
 * Returns:  
 * Parameter(s): none
 * Particularitie(s) and limitation(s):none
 ********************************************************************************  */
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspInitWriteDataById(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_2E_OemInit();
}

/*  ********************************************************************************
 * Function name:Dcm_2E_RepeaterProxyProcess
 * Description: 
 * Returns:  
 * Parameter(s): none
 * Particularitie(s) and limitation(s):none
 ********************************************************************************  */
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2E_RepeaterProxyProcess(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType   stdReturn;

  stdReturn = Dcm_DidMgrWriteDid(dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2E_ProxyContext.CurDid22Handle,
                                 dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2E_ProxyContext.CurDidHandle,
                                 dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData,
                                 dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen);

  if(DCM_E_PENDING == stdReturn)
  {
    return DCM_E_PENDING;
  }
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/*  ********************************************************************************
 * Function name:Dcm_2E_RepeaterProxyDispatcher
 * Description: 
 * Returns:  
 * Parameter(s): none
 * Particularitie(s) and limitation(s):none
 ********************************************************************************  */
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_2E_RepeaterProxyDispatcher(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType   stdReturn;


  stdReturn = dcm2E_ServiceInfoTable[dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2E_ProxyContext.CurDidHandle].CheckCondition(&dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      Dcm_SetNegResponse(DCM_E_GENERALREJECT);
      break;
  }

  /* Check if any error was found */
  if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
  {
    /* Process the first DID 
     * stack utilization optimization */
    Dcm_RegisterRepeaterProxy(Dcm_2E_RepeaterProxyProcess);
  }
  else
  {
    Dcm_ProcessingDone();
  }
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/*  ********************************************************************************
 * Function name:Dcm_DspWriteDataById
 * Description: 
 * Returns:  
 * Parameter(s): none
 * Particularitie(s) and limitation(s):none
 ********************************************************************************  */
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspWriteDataById(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DidHandleType didHandle;
  uint16 did;

  /* Check if at least one DID is available and at least one data byte */
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen > 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    /* Also the capacity of the ECU shall not be exceeded */
    /* Dispatch all DIDs */
    /* Find DID (use main pool since each write-able DID is accessible by 0x2E)*/
    did = Dcm_Make16Bit(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0],
                        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1]);
    didHandle = Dcm_DidMgrFindDid(did, dcm2E_DidHandleTable, dcm2E_DidCfgVariants);
    if(didHandle < DCM_NUM_DIDS)
    {
      /* Skip the DID */
      /* Return the DID */
      Dcm_MsgContextMoveRel(2,2);
      /* Check DID specific length */
      if((dcm2E_ServiceInfoTable[didHandle].MinLength <= dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen)&&
         (dcm2E_ServiceInfoTable[didHandle].MaxLength >= dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen))
      {
        (void)Dcm_DidMgrAnalyseDid(DCM_DIDMGR_CLIENT_ID_2E, dcm2E_DidStateInfoTable[didHandle]);
        if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
        {
# if (DCM_2E_OEM_CONDITION_CHECK_ENABLED == STD_ON)
          Dcm_2E_OemConditionCheck(did, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
          if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
# endif
          {
# if (DCM_SERVICE_2E_STATE_TRANS_ENABLED == STD_ON)
            /* Prepare state transition */
            dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = Dcm_2E_GetStateTransitionRef(didHandle);
# endif
# if (DCM_2E_NVM_SUPPORT_ENABLED == STD_ON)
            dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2E_ProxyContext.IsNvmAccessStarted = FALSE;
# endif
            dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2E_ProxyContext.CurDidHandle = (Dcm_MemDidHandleType)didHandle;
# if (DCM_DIDMGR_RESMGR_ENABLED == STD_ON)
            dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2E_ProxyContext.CurDid22Handle = (Dcm_MemDidHandleType)Dcm_22_FindDid(did);
# endif
            Dcm_RegisterRepeaterProxy(Dcm_2E_RepeaterProxyDispatcher);
            return;/* Wait for application */
          }
        }
      }
      else
      {
        /* Invalid length */
        dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
    }
    else
    {
      /* Too many DIDs */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  /* Reaching this point means diagnostic error was found */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */


/*  ********************************************************************************
 * Function name:Dcm_DspPostWriteDataById
 * Description: 
 * Returns:  
 * Parameter(s): none
 * Particularitie(s) and limitation(s):none
 ********************************************************************************  */
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostWriteDataById(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  Dcm_2E_OemPostProcess(status);
}
#endif /* (DCM_SERVICE_2E_ENABLED == STD_ON) */
#if (DCM_SERVICE_2F_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspIoControlById
 **********************************************************************************************************************/
/*! \brief      Service 0x2F processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspIoControlById(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_DidHandleType didHandle;
  Dcm_NegativeResponseCodeType errorCode = DCM_E_REQUESTOUTOFRANGE;

  /* Check minimum length (SubFunction and DID must be inside) */
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen > 2, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    didHandle = Dcm_DidMgrFindDid(Dcm_Make16Bit(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0],
                                                dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1]),
                                  dcm2F_DidHandleTable,dcm2F_DidCfgVariants);

    /* Is the DID supported? */
    if(didHandle < DCM_NUM_DIDS)
    {
      /* analyze the DID specific information */
      (void)Dcm_DidMgrAnalyseDid(DCM_DIDMGR_CLIENT_ID_2F, dcm2F_DidStateInfoTable[didHandle]);
      /* Dispatching successful?*/
      if(dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] == DCM_E_OK)
      {
        Dcm_2F_InstHandleType didInstRef;
        /* Check if sub-function valid (at all and for DID) */
        didInstRef = Dcm_2F_FindSubFunction(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[2], didHandle);

        /* Does the DID support the control type? */
        if(didInstRef < DCM_2F_NUM_DID_INST)
        {
          /* Skip the routine Id and sub-function */
          Dcm_MsgContextMoveRel(3,3);
          /* Check DID specific length */
          if((dcm2F_ServiceInfoTable[didInstRef].ReqMinLength <= dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen)&&
             (dcm2F_ServiceInfoTable[didInstRef].ReqMaxLength >= dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen))
          {
            /* analyze the sub-function specific information */
            (void)Dcm_CheckServiceState(dcm2F_SubFuncStateInfoTable[didInstRef], DCM_STATE_LVL_PARAM, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);

            /* Dispatching successful?*/
            if(dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] == DCM_E_OK)
            {
# if (DCM_SERVICE_2F_STATE_TRANS_ENABLED == STD_ON)
              /* Prepare state transition */
              dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = Dcm_2F_GetStateTransitionRef(didInstRef);
# endif
              /* Call the main-handler */
              dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm2F_ProxyContext.CurDidHandle = (Dcm_2F_MemInstHandleType)didInstRef;
              Dcm_RegisterRepeaterProxy(Dcm_2F_RepeaterProxyProcess);
              /* Let the application to take care about the service */
              return;
            }
            /*else - NRC is already registered */
          }
          else
          {
            /* Invalid service length */
            dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
          }
        }
        /*else - NRC 0x31 is already registered */
      }
      /*else - NRC XX is already registered */
    }
    /*else - NRC 0x31 is already registered */
  }
  /* Error Case */
  Dcm_SetNegResponse(errorCode);
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_2F_ENABLED == STD_ON) */
#if (DCM_SERVICE_31_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspInitRoutineControl
 **********************************************************************************************************************/
/*! \brief      Service 0x31 initialization
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspInitRoutineControl(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_RidMgrInit();
}

/***********************************************************************************************************************
 *  Dcm_DspRoutineControl
 **********************************************************************************************************************/
/*! \brief      Service 0x31 processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspRoutineControl(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_RidHandleType ridHandle;

  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Check minimum length (SubFunction and RID must be inside) */
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[lContext].reqDataLen > 2, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  {
    ridHandle = Dcm_31_FindRid(Dcm_Make16Bit(dcmDsdMsgContext[lContext].reqData[1], dcmDsdMsgContext[lContext].reqData[2]));

    /* Is the RID supported? */
    if(ridHandle != 0)
    {
      ridHandle--;
      /* analyze the RID specific information */
      (void)Dcm_CheckServiceState(dcm31_RidStateInfoTable[ridHandle], DCM_STATE_LVL_PARAM, &dcmDsdErrorRegister[lContext]);
      /* Dispatching successful?*/
      if(dcmDsdErrorRegister[lContext] == DCM_E_OK)
      {
        Dcm_RidInstHandleType  ridInstRef;
        /* Check if sub-function valid (at all and for RID) */
        ridInstRef = Dcm_31_FindSubFunction(dcmDsdMsgContext[lContext].reqData[0], ridHandle);

        /* Does the RID support the control type? */
        if(ridInstRef < DCM_NUM_RID_INST)
        {
          /* analyze the sub-function specific information */
          (void)Dcm_CheckServiceState(dcm31_SubFuncStateInfoTable[ridInstRef], DCM_STATE_LVL_SUBFUNC, &dcmDsdErrorRegister[lContext]);
          /* Dispatching successful?*/
          if(dcmDsdErrorRegister[lContext] == DCM_E_OK)
          {
            /* Skip the routine Id and sub-function */
            Dcm_MsgContextMoveRel(3,3);
            /* If dynamic request length OR valid one - process the service */
            if((dcm31_ServiceInfoTable[ridInstRef].ReqMinLength <= dcmDsdMsgContext[lContext].reqDataLen)&&
               (dcm31_ServiceInfoTable[ridInstRef].ReqMaxLength >= dcmDsdMsgContext[lContext].reqDataLen))
            {
# if (DCM_SERVICE_31_STATE_TRANS_ENABLED == STD_ON)
              /* Prepare state transition */
              dcmDslInfoPool[lContext].stateTransRef = Dcm_31_GetStateTransitionRef(ridInstRef);
# endif
# if (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
              dcmRepeatedProxyContexts[lContext].dcm31_ProxyContext.CurRidHandle     = (Dcm_MemRidHandleType)ridHandle;
# endif
              dcmRepeatedProxyContexts[lContext].dcm31_ProxyContext.CurRidInstHandle = (Dcm_MemRidInstHandleType)ridInstRef;
              /* Call the main-handler */
              Dcm_RegisterRepeaterProxy(Dcm_31_RepeaterProxyProcess);
              /* Let the application to take care about the service */
              return;
            }
            else
            {
              /* Invalid service length */
              dcmDsdErrorRegister[lContext] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
          }/*else - NRC is already registered */
        }
        else
        {
          /* the RID is available but the sub-function not */
          dcmDsdErrorRegister[lContext] = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
      }
      /*else - NRC is already registered */
    }
    else
    {
      /* the RID is not available but the sub-function not */
      dcmDsdErrorRegister[lContext] = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  /* Error Case */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_31_ENABLED == STD_ON) */
#if (DCM_SERVICE_3D_ENABLED == STD_ON)
# if (DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_3D_WriteRepeaterProxy
 **********************************************************************************************************************/
/*! \brief      Service 0x23 read polling processor
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_3D_WriteRepeaterProxy(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;

  stdReturn = Dcm_3D_WriteMemoryBlock(&dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0], &dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm3D_ProxyContext.memBlockDef, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
  if(DCM_E_PENDING != stdReturn)
  {
    /* Error or OK Case -> end */
    Dcm_ProcessingDone();
  }
  return stdReturn;
}
# endif

/***********************************************************************************************************************
 *  Dcm_DspWriteMemoryByAddress
 **********************************************************************************************************************/
/*! \brief      Service 0x3D processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspWriteMemoryByAddress(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_MemoryBlockDescType    memBlockDesc;
  Dcm_MemMgrExtrInfoRsltType memExtrRslt;

  /* Enforce FID extraction */
  memBlockDesc.addrParamSize = 0;
# if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
  memBlockDesc.memOp = DCM_MEM_OP_WRITE;
# endif
  /* Extract the requested memory block information */
  memExtrRslt = Dcm_MemAccExtractMemoryBlockInfo(&memBlockDesc);

  /* if no error - just writes E_OK to the memory */
  dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = dcmMemMgrExtrInfo2NrcMap[memExtrRslt];

  if (DCM_MEMMGR_EXTR_INFO_OK == memExtrRslt)
  {
    if (dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == memBlockDesc.memBlock.length)
    {
      /* Analyze the requested memory block */
      Dcm_MemAccAnalyseMemBlock(&memBlockDesc, dcm3D_MemBlockHandleTable, dcm3D_MemBlockCfgVariants, dcm3D_MemBlockStateInfoTable);
      if (DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
      {
        /* The whole data is present after address and length */
        /* Set up response data pointer (which should not be used!) */
        Dcm_AddValue(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resDataLen , Dcm_MsgLenType, memBlockDesc.protocolLength);
        /* Delegate to the writer */
        Dcm_3D_WriteDataVirtual(&memBlockDesc.memBlock);
        return;/* allow asynchronous writing */
      }
    }
    else
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }

  /* Error Case */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_3D_ENABLED == STD_ON) */
#if (DCM_SERVICE_3E_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspTesterPresent
 **********************************************************************************************************************/
/*! \brief      Service 0x3E processor
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspTesterPresent(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  {
    dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resDataLen++;
    if(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0] != 0x00)
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
  }
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_3E_ENABLED == STD_ON) */
#if (DCM_SERVICE_85_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspControlDtcSetting
 **********************************************************************************************************************/
/*! \brief      Service 0x85 Processor
 *  \context    Function may be called from task level
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspControlDtcSetting(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dem_ReturnControlDTCStorageType resultDtcStorage;
  Dem_DTCGroupType                dtcGroup;
  uint8_least                     sfIter;
  Dcm_MsgItemType                 sfId;

  /* Length already checked in DsdDispatcher !!! */
# if (DCM_85_REQUEST_DTC_GROUP_ENABLED == STD_ON)
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
# else
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen == 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  dtcGroup = DEM_DTC_GROUP_ALL_DTCS;
# endif
  /* Cache the SF */
  sfId = dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0];
  /* Skip the sub-function parameter */
  Dcm_MsgContextMoveRel(1, 1);

  sfIter = Dcm_FindValueUint8(dcm85_SubFuncCfgVariants, dcm85_SubFuncLookUpTable, sfId);
  if(sfIter != 0)
  {
    sfIter--;
# if (DCM_85_REQUEST_DTC_GROUP_ENABLED == STD_ON)
    if(3 == dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen) /* DTCgrp */
    {
      /* Extract request data */
      dtcGroup = (Dem_DTCGroupType)Dcm_Make32Bit(0, dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[0],dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[1],dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData[2]);
# endif
      /* Check sub-function specific states */
      (void)Dcm_CheckServiceState(dcm85_StateInfoTable[sfIter], DCM_STATE_LVL_SUBFUNC, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
      if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
      {
        /* ---- Common code ---- */
# if (DCM_SERVICE_85_STATE_TRANS_ENABLED == STD_ON)
        /* Prepare state transition */
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = Dcm_85_GetStateTransitionRef(sfIter);
# endif
        resultDtcStorage = DEM_CONTROL_DTC_STORAGE_OK;

        /* check explicitely for disable to avoid incidental disabling of the fault memory! */
        if(DCM_CTRL_DTC_DISABLE == sfId)
        {
          resultDtcStorage = Dem_DisableDTCStorage(dtcGroup, DEM_DTC_KIND_ALL_DTCS);
        }
        else
        {
          resultDtcStorage = Dem_EnableDTCStorage(dtcGroup, DEM_DTC_KIND_ALL_DTCS);
        }

        if(resultDtcStorage != DEM_CONTROL_DTC_STORAGE_OK)
        {
# if (DCM_85_REQUEST_DTC_GROUP_ENABLED == STD_ON)
          if(resultDtcStorage == DEM_CONTROL_DTC_WRONG_DTCGROUP)
          {
            dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_REQUESTOUTOFRANGE;
          }
          else
# endif
          {
            dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_CONDITIONSNOTCORRECT;
          }
        }
      }
# if (DCM_85_REQUEST_DTC_GROUP_ENABLED == STD_ON)
    }
    else
    {
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
# endif
  }
  else
  {
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  }
  Dcm_ProcessingDone();
}
#endif /* (DCM_SERVICE_85_ENABLED == STD_ON) */
#if (DCM_SERVICE_87_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_DspLinkControl
 **********************************************************************************************************************/
/*! \brief      Service 0x87 processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspLinkControl(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  uint8_least  sfIter;

  Dcm_CheckDcmInit(DcmServiceId_DiagnosticService);/* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  /* Length already checked in DsdDispatcher !!! */
  Dcm_StateCheckValueRangeFailed(dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen >= 1, DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */

  sfIter = Dcm_FindValueUint8(dcm87_SubFuncCfgVariants, dcm87_SubFuncLookUpTable, *dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqData);

  if(sfIter != 0)
  {
    sfIter--;
    /* Check data length + sub-function byte */
    if(dcm87_ServiceInfoTable[sfIter].ReqDataLength == dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].reqDataLen)
    {
      (void)Dcm_CheckServiceState(dcm87_ServiceInfoTable[sfIter].StateFilterIdx, DCM_STATE_LVL_SUBFUNC, &dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS]);
      if(DCM_E_OK == dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS])
      {
# if (DCM_SERVICE_87_STATE_TRANS_ENABLED == STD_ON)
        /* Prepare state transition */
        dcmDslInfoPool[DCM_CONTEXT_ID_UDS].stateTransRef = Dcm_87_GetStateTransitionRef(sfIter);
# endif
        /* Return the sub-function */
        dcmDsdMsgContext[DCM_CONTEXT_ID_UDS].resDataLen ++;
        dcmRepeatedProxyContexts[DCM_CONTEXT_ID_UDS].dcm87_ProxyContext.linkControlHandle=(uint8)sfIter;
        Dcm_RegisterRepeaterProxy(Dcm_87_RepeaterProxyProcess);
        return;/* Wait for application */
      }
    }
    else
    {
      /* Wrong length */
      dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }
  else
  {
    dcmDsdErrorRegister[DCM_CONTEXT_ID_UDS] = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  }
  /* Reaching this point means diagnostic error was found */
  Dcm_ProcessingDone();
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_SERVICE_87_ENABLED == STD_ON) */
#if (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_UnspecSvc_RepeaterProxy
 **********************************************************************************************************************/
/*! \brief      Unspecified service polling proxy 
 *  \return     Operation result
 *  \retval     DCM_E_OK - success
 *  \retval     DCM_E_PENDING - try again later
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_UnspecSvc_RepeaterProxy(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType     stdReturn;
  Dcm_RteDataLenType lAppResDataLen = 0;
  Dcm_ContextIdType  lContext = Dcm_CtxtMgrGetCurUdsContextId();  /* Use context specific access in case an OBD service is handled here !!! */


  stdReturn = Dcm_HandleUnspecifiedService(dcmRepeatedProxyContexts[lContext].dcmUnspecSvc_ProxyContext.sid,
                                           dcmDsdMsgContext[lContext].reqData,
                                           dcmDsdMsgContext[lContext].reqDataLen,
                                           dcmDsdMsgContext[lContext].resData,
                                           &lAppResDataLen,
                                           &dcmDsdErrorRegister[lContext]);
  switch(stdReturn)
  {
  /*------------------*/
    case DCM_E_OK:
  /*------------------*/
      break;
  /*------------------*/
    case DCM_E_PENDING:
  /*------------------*/
      /* try again */
      return DCM_E_PENDING;
  /*------------------*/
    default:
  /*------------------*/
      Dcm_CheckValueRangeFailed(DcmServiceId_DiagnosticService); /* PRQA S 3109 */ /* QAC 7.0:  Empty statement (';' on its own) - if this is deliberate, it is best to put ';' on a line by itself. */ /* Macros used for better efficiency! */
      Dcm_SetNegResponse(DCM_E_GENERALREJECT);/* keep the old NRC if set */
      break;
  }

  Dcm_AddValue(dcmDsdMsgContext[lContext].resDataLen, Dcm_MsgLenType, lAppResDataLen);
  Dcm_ProcessingDone();
  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */

/***********************************************************************************************************************
 *  Dcm_DspUnknownService
 **********************************************************************************************************************/
/*! \brief      Common unknown service processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspUnknownService(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Start unspecified service execution */
  Dcm_RegisterRepeaterProxy(Dcm_UnspecSvc_RepeaterProxy);
}

/***********************************************************************************************************************
 *  Dcm_DspPostUnknownService
 **********************************************************************************************************************/
/*! \brief      Common unknown service post-processor 
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostUnknownService(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Delegate job to the application */

  /* Use context specific access in case an OBD service is handled here !!! */
  Dcm_ContextIdType lContext = Dcm_CtxtMgrGetCurUdsContextId();

  Dcm_PostHandleUnspecifiedService(dcmRepeatedProxyContexts[lContext].dcmUnspecSvc_ProxyContext.sid, status);
}
#endif /* (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON) */
#if (DCM_OBD_MID_MGR_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_22_MidReadDataId
 **********************************************************************************************************************/
/*! \brief      Service 0x22 0xF601 - 0xF7FF reader
 *  \context    Function must be called on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_22_MidReadDataId(Dcm_ObdMidMgrMidIndHandleType midHandle, Dcm_RteDataPtrType resData)/* PRQA S 3673 */ /* QAC 7.0:  The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'. */ /* The API is generic */
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Std_ReturnType stdReturn;
  uint16 lTestValue;
  uint16 lMinLimit;
  uint16 lMaxLimit;
  uint8  lStatus;
  Dcm_MsgType lResData;
  P2CONST(Dcm_ObdMidMgrTidInfoType, AUTOMATIC, DCM_CONST) tidObject;
  uint8_least tidIter;

  lResData = (Dcm_MsgType)(*resData);

  tidIter = (uint8_least)(  dcmObdMidMgr_MidIndTable[midHandle + 1u]
                          - dcmObdMidMgr_MidIndTable[midHandle + 0u]);

  tidObject = &dcmObdMidMgr_TidInfoTable[dcmObdMidMgr_MidIndTable[midHandle]];

  while(tidIter != 0)
  {
    --tidIter;
    stdReturn = tidObject->GetDtrValue(&lTestValue, &lMinLimit, &lMaxLimit, &lStatus);

    if(DCM_E_OK != stdReturn)
    {
      return DCM_E_NOT_OK;
    }

    if(DCM_DTRSTATUS_INVISIBLE == lStatus)
    {
      lTestValue = 0;
      lMinLimit = 0;
      lMaxLimit = 0;
    }

    /* Copy data */
    lResData[0] = tidObject->TestId;

    lResData[1] = tidObject->UnitAndScalingId;

    lResData[2] = Dcm_GetHiByte(lTestValue);
    lResData[3] = Dcm_GetLoByte(lTestValue);

    lResData[4] = Dcm_GetHiByte(lMinLimit);
    lResData[5] = Dcm_GetLoByte(lMinLimit);

    lResData[6] = Dcm_GetHiByte(lMaxLimit);
    lResData[7] = Dcm_GetLoByte(lMaxLimit);

    lResData = &lResData[8]; /* next data block */
    tidObject = &tidObject[1];/* next MIDTID object */
  }

  return DCM_E_OK;
}/* PRQA S 2006 */ /* QAC 7.0:  '%s' has more than one 'return' path. */ /* Optimization */
#endif /* (DCM_OBD_MID_MGR_ENABLED == STD_ON) */
/***********************************************************************************************************************
 *  Dcm_DspInitDummyService
 **********************************************************************************************************************/
/*! \brief      Dummy service initialization function to avoid explicit check for NULL_PTR
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspInitDummyService(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Called in case a service does not need an initialization */
}

/***********************************************************************************************************************
 *  Dcm_DspInitDummyService
 **********************************************************************************************************************/
/*! \brief      Dummy service post-processing function to avoid explicit check for NULL_PTR
 *  \context    Function could be called in interrupt context or on task level.
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_DspPostDummyService(Dcm_ConfirmationStatusType status)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  DCM_IGNORE_UNREF_PARAM(status); /* PRQA S 3112 */ /* QAC 7.0: This statement has no side-effect - it can be removed. */
}

#if (DCM_CFG_MULTI_ID_INC_ENABLED == STD_ON)
/***********************************************************************************************************************
 *  Dcm_InitDiagnosticVariant
 **********************************************************************************************************************/
/*! \brief      Initializes the DCM component variant.
 *  \param[in]  VariantMask  The new variant mask
 *  \pre        All interrupts (global) must be disabled. Must be called prior Dcm_Init
 *  \context    Function could be called from task level.
 **********************************************************************************************************************/
 /*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_InitDiagnosticVariant(Dcm_CfgVariantMaskType VariantMask)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Init variants first */
  dcmStateMachine.CfgVariantMask = VariantMask;
}
#endif

/***********************************************************************************************************************
 *  Dcm_Init
 **********************************************************************************************************************/
/*! \brief      Initializes the DCM component.
 *  \param[in]  DcmConfigPtr  Pointer to the current configuration structure
 *  \pre        All interrupts (global) must be disabled.
 *  \context    Function could be called from task level.
 **********************************************************************************************************************/
#if (DCM_MULTI_ID_ENABLED == STD_ON)
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_Init(P2CONST(Dcm_ConfigType, AUTOMATIC, DCM_CONST) DcmConfigPtr)
/*--------------------------------------------------------------------------------------------------------------------*/
#else
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_Init(void)
/*--------------------------------------------------------------------------------------------------------------------*/
#endif
{
#if (DCM_COM_MULTI_ID_ENABLED == STD_ON)
  /* Init variants first */
  dcmStateMachine.ComVariantId = DcmConfigPtr->ComVariant;
#endif
#if (DCM_CFG_MULTI_ID_ENABLED == STD_ON)
# if (DCM_CFG_MULTI_ID_EXC_ENABLED == STD_ON)
  dcmStateMachine.CfgVariantMask = DcmConfigPtr->CfgVariantMask;
# endif

# if (DCM_CFG_MULTI_ID_INC_ENABLED == STD_ON)
  dcmStateMachine.CfgVariantMask |= DcmConfigPtr->CfgVariantMask;
# endif
#endif
  /* Init debug code */
  Dcm_DebugInit();
  /* Event manager init */
  Dcm_EvMgrInit();
  /* Timer manager init */
  Dcm_TmrMgrInit();
  /* DSL INIT */
  Dcm_DslInit();
  /* DSD INIT */

  /* DSP INIT */
  Dcm_DspInit();
}

/***********************************************************************************************************************
 *  Dcm_MainFunction
 **********************************************************************************************************************/
/*! \brief      DCM task function
 *              Could be called in case a single task concept is used
 *  \pre        DCM must be initialized
 *  \context    Function must be called from task level (background loop).
 *  \note       Has the same prio as Dcm_StateTask().
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_MainFunction(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  Dcm_TimerTask();
  Dcm_StateTask();
}

/***********************************************************************************************************************
 *  Dcm_StateTask
 **********************************************************************************************************************/
/*! \brief      Provides the job processing of DCM.
 *              Could be used together with Dcm_TimerTask() to achive best 
 *              CPU utilization by splitting the timing management from the job processing.
 *  \pre        DCM must be initialized.
 *  \context    Function must be called from task level (background loop).
 **********************************************************************************************************************/
/*--------------------------------------------------------------------------------------------------------------------*/
FUNC(void, DCM_CODE) Dcm_StateTask(void)
/*--------------------------------------------------------------------------------------------------------------------*/
{
  /* Run-time optimization for Idle mode */
  if(dcmEvMgrNumActiveTasks != 0)
  {
#if (DCM_OBD_SUPPORT_ENABLED == STD_ON) || \
    (DCM_WWHOBD_SUPPORT_ENABLED == STD_ON)
    /* Give first priority to OBD */
    Dcm_DspStateTask(DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(DCM_CONTEXT_ID_OBD));
#endif
    Dcm_DspStateTask(DCM_CONTEXT_PARAM_VALUE_WRAP_ONLY(DCM_CONTEXT_ID_UDS));
#if (DCM_SERVICE_27_ENABLED == STD_ON)
    Dcm_27_StateTask();
#endif
#if (DCM_SERVICE_2A_ENABLED == STD_ON)
    Dcm_2A_StateTask();
#endif
#if (DCM_SERVICE_2C_ENABLED == STD_ON)
    Dcm_2C_StateTask();
#endif
#if (DCM_SERVICE_A0_ENABLED == STD_ON)
    Dcm_A0_StateTask();
#endif
    Dcm_DslLL_StateTask();
  }
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



