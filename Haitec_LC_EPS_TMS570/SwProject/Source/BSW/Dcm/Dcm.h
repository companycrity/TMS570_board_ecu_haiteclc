/* -----------------------------------------------------------------------------
  Filename:    Dcm.h
  Description: Interface of DCM visible to any application.

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

#if !defined(__DCM_H__)
# define __DCM_H__

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

# include "Dcm_Cbk.h"
# include "Dcm_Lcfg.h"



/* -----------------------------------------------------------------------------
    &&&~ Preprocessor constants (defines)
 ----------------------------------------------------------------------------- */

# define DCM_SW_MAJOR_VERSION                                        0x04u
# define DCM_SW_MINOR_VERSION                                        0x07u
# define DCM_SW_PATCH_VERSION                                        0x03u
# define DCM_AR_MAJOR_VERSION                                        0x03u
# define DCM_AR_MINOR_VERSION                                        0x00u
# define DCM_AR_PATCH_VERSION                                        0x00u
/* ##V_CFG_MANAGEMENT ##CQProject : Diag_AsrDcm CQComponent : Implementation */
# define DIAG_ASRDCM_VERSION                                         0x0407u
# define DIAG_ASRDCM_RELEASE_VERSION                                 0x03u
/* Module identifier */
# define DCM_MODULE_ID                                               0x35u
/* Vendor ID */
# define DCM_VENDOR_ID                                               30
/* This magic number provides internal DCM generation process consistency check.All DCM files must have the same one. */
# define DCM_XDECL_INTERFACE_MAGIC_NUMBER                            9001
/*-----------------------------------------------*/
/*                Global DCM API                 */
/*-----------------------------------------------*/
/* ApiIds for DET */
# define DcmServiceId_Init                                           (uint8)0x01

# define DcmServiceId_ProvideRxBuffer                                (uint8)0x02
# define DcmServiceId_RxIndication                                   (uint8)0x03
# define DcmServiceId_ProvideTxBuffer                                (uint8)0x04
# define DcmServiceId_TxConfirmation                                 (uint8)0x05

# define DcmServiceId_GetSesCtrlType                                 (uint8)0x06
# define DcmServiceId_SetSesCtrlType                                 (uint8)0x07

# define DcmServiceId_GetSesChgPermission                            (uint8)0x08
# define DcmServiceId_SesCtrlChgIndication                           (uint8)0x09

# define DcmServiceId_GetSesTimingValues                             (uint8)0x0A
# define DcmServiceId_PrepareSesTimingValue                          (uint8)0x0B
# define DcmServiceId_SetSesTimingValues                             (uint8)0x0C

# define DcmServiceId_GetSecurityLevel                               (uint8)0x0D
# define DcmServiceId_SetSecurityLevel                               (uint8)0x0E
# define DcmServiceId_GetActiveProtocol                              (uint8)0x0F

# define DcmServiceId_ResponseOnEvent                                (uint8)0x10
# define DcmServiceId_ResponseOnOneDataByPeriodicId                  (uint8)0x11

# define DcmServiceId_DiagnosticService                              (uint8)0x12
# define DcmServiceId_SetNegResponse                                 (uint8)0x13
# define DcmServiceId_ProcessingDone                                 (uint8)0x14

# define DcmServiceId_DspConfirmation                                (uint8)0x15
# define DcmServiceId_RteConfirmation                                (uint8)0x16
# define DcmServiceId_RteIndication                                  (uint8)0x17

# define DcmServiceId_StartPagedProcessing                           (uint8)0x18
# define DcmServiceId_UpdatePage                                     (uint8)0x19
# define DcmServiceId_ProcessPage                                    (uint8)0x1A
# define DcmServiceId_CancelPagedBufferProcessing                    (uint8)0x1B

# define DcmServiceId_GetActiveServiceTable                          (uint8)0x1C

# define DcmServiceId_GetSeed                                        (uint8)0x1D
# define DcmServiceId_CompareKey                                     (uint8)0x1E

# define DcmServiceId_ComMNoComModeEntered                           (uint8)0x21
# define DcmServiceId_ComMSilentComModeEntered                       (uint8)0x22
# define DcmServiceId_ComMFullComModeEntered                         (uint8)0x23
# define DcmServiceId_GetVersionInfo                                 (uint8)0x24
# define DcmServiceId_MainFunction                                   (uint8)0x25

# define DcmServiceId_StartProtocol                                  (uint8)0x1F
# define DcmServiceId_StopProtocol                                   (uint8)0x20

/* DCM implementation custom codes */
# define DcmServiceId_DsdDispatcher                                  (uint8)0x50
# define DcmServiceId_SendResponsePending                            (uint8)0x51
# define DcmServiceId_ProcessActivity                                (uint8)0x52
# define DcmServiceId_TriggerTransmit                                (uint8)0x53
# define DcmServiceId_SendResponse                                   (uint8)0x54
# define DcmServiceId_SendSpontaneousResponse                        (uint8)0x55
# define DcmServiceId_ReleaseResource                                (uint8)0x56
# define DcmServiceId_AllocateResource                               (uint8)0x57
# define DcmServiceId_LockDcm                                        (uint8)0x58
# define DcmServiceId_UnLockDcm                                      (uint8)0x59
# define DcmServiceId_GetProgConditions                              (uint8)0x5A
# define DcmServiceId_SetProgConditions                              (uint8)0x5B



/* Error classification */
# define DCM_E_INTERFACE_VALUE_OUT_OF_RANGE                          (Dcm_DevErrorType)0x02
# define DCM_E_UNINIT                                                (Dcm_DevErrorType)0x05
# define DCM_E_PARAM                                                 (Dcm_DevErrorType)0x06

/* Custom types*/
# define DCM_E_ILLEGAL_STATE_REACHED                                 (Dcm_DevErrorType)0x80
# define DCM_E_INTERFACE_ILLEGALLY_USED                              (Dcm_DevErrorType)0x81
# define DCM_E_LIB_CONFIG_MISMATCH                                   (Dcm_DevErrorType)0x82




/* -----------------------------------------------------------------------------
    &&&~ Function prototypes
 ----------------------------------------------------------------------------- */

# define DCM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if (DCM_EXT_CRITICAL_SEC_MGR_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_EnterCriticalSection(void);
extern FUNC(void, DCM_CODE) Dcm_LeaveCriticalSection(void);
# endif

# if (DCM_COPY_RAM2RAM_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_CopyRam2Ram(Dcm_ApplDataPtrType tgtAddr, Dcm_ApplDataPtrType      srcAddr, uint16_least len);
# endif

# if (DCM_COPY_ROM2RAM_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_CopyRom2Ram(Dcm_ApplDataPtrType tgtAddr, Dcm_ApplConstDataPtrType srcAddr, uint16_least len);
# endif

# if (DCM_VERSION_INFO_API == STD_ON)
/* Version info report */
extern FUNC(void, DCM_CODE) Dcm_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo);
# endif

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType( P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType);

# if (DCM_SERVICE_27_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel( P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel);
# endif /* (DCM_SERVICE_27_ENABLED == STD_ON) */
/* Administrative functions */
# if (DCM_CFG_MULTI_ID_INC_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_InitDiagnosticVariant(Dcm_CfgVariantMaskType VariantMask);
# endif
# if (DCM_MULTI_ID_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_Init(P2CONST(Dcm_ConfigType, AUTOMATIC, DCM_CONST) DcmConfigPtr);
# else
extern FUNC(void, DCM_CODE) Dcm_Init(void);
# endif
extern FUNC(void, DCM_CODE) Dcm_MainFunction(void);
extern FUNC(void, DCM_CODE) Dcm_TimerTask(void);
extern FUNC(void, DCM_CODE) Dcm_StateTask(void);

# define DCM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ External function prototypes
 ----------------------------------------------------------------------------- */

# define DCM_APPL_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON))
#  if (DCM_MEMMGR_PARAM_CHECK_ENABLED == STD_OFF)
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_CheckMemory(Dcm_MemMgrOpType MemAccOp,
                                                           uint8            MemoryIdentifier,
                                                           uint32           MemoryAddress,
                                                           uint32           MemorySize,
                                                           Dcm_NegativeResponseCodePtrType ErrorPtr);
#  endif
# endif /* ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_SERVICE_3D_ENABLED == STD_ON)) */
# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
extern FUNC(Dcm_ReturnReadMemoryType, DCM_APPL_CODE) Dcm_ReadMemory(uint8 MemoryIdentifier, uint32 MemoryAddress,uint32 MemorySize, Dcm_MsgType MemoryData);
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_23_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
# if ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF)))
extern FUNC(Dcm_ReturnWriteMemoryType, DCM_APPL_CODE) Dcm_WriteMemory(uint8 MemoryIdentifier, uint32 MemoryAddress, uint32 MemorySize, Dcm_MsgType MemoryData);
# endif /* ((DCM_MEMORY_ACCESS_ASR_40_ENABLED == STD_ON) && ((DCM_SERVICE_3D_ENABLED == STD_ON) || (DCM_CONFIG_PRECOMPILE_ENABLED == STD_OFF))) */
# if (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON)
/* Application callouts */
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_CheckUnspecifiedService(uint8 sid, P2VAR(boolean,AUTOMATIC,DCM_VAR_NOINIT) hasSprmib);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_HandleUnspecifiedService(uint8                           sid
                                                                       ,Dcm_MsgType                     requestPtr
                                                                       ,Dcm_MsgLenType                  reqDataLen
                                                                       ,Dcm_MsgType                     responsePtr
                                                                       ,Dcm_MsgLenPtrType               resDataLenPtr
                                                                       ,Dcm_NegativeResponseCodePtrType errorPtr);

extern FUNC(void, DCM_APPL_CODE) Dcm_PostHandleUnspecifiedService(uint8 sid, Dcm_ConfirmationStatusType status);
# endif /* (DCM_UNSPEC_SERVICE_SUPPORT_ENABLED == STD_ON) */
# if (DCM_FBL_POS_RES_ENABLED == STD_ON)
extern FUNC(void, DCM_APPL_CODE) Dcm_SetProgConditions(Dcm_ProgConditionsPtrType ProgConditions);
extern FUNC(void, DCM_APPL_CODE) Dcm_GetProgConditions(Dcm_ProgConditionsPtrType ProgConditions);
# endif /* (DCM_FBL_POS_RES_ENABLED == STD_ON) */
# define DCM_APPL_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ ROM 32Bit definitions
 ----------------------------------------------------------------------------- */

# define DCM_START_SEC_CONST_32BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
extern CONST(uint32, DCM_CONST) Dcm_GeneratorVersion;
# endif

# define DCM_STOP_SEC_CONST_32BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



/* -----------------------------------------------------------------------------
    &&&~ Macro definitions
 ----------------------------------------------------------------------------- */

/* Avoid compiler warnings on unused local variables or function parameters */
# define DCM_IGNORE_UNREF_PARAM(paramName)                           ((void)paramName)


/*-----------------------------------------------*/
/*                 GlobalUtils                   */
/*-----------------------------------------------*/
/* Data assemble/disassemble macros */
/* compose from byte stream a 16 bit data */
# define Dcm_Make16Bit(hiByte,loByte)                                ((uint16)((((uint16)(hiByte))<<8)| \
                                                                     ((uint16)(loByte))))                 /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
/* compose from byte stream a 32 bit data */
# define Dcm_Make32Bit(hiHiByte,hiLoByte,loHiByte,loLoByte)          ((uint32)((((uint32)(hiHiByte))<<24)| \
                                                                     (((uint32)(hiLoByte))<<16)| \
                                                                     (((uint32)(loHiByte))<<8) | \
                                                                     ((uint32)(loLoByte))))               /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
/* decompose 16 bit data in byte stream */
# define Dcm_GetHiByte(data)                                         ((uint8)(((uint16)(data))>>8))       /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetLoByte(data)                                         ((uint8)(data))                      /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */

/* decompose 32 bit data in byte stream */
# define Dcm_GetHiHiByte(data)                                       ((uint8)(((uint32)(data))>>24))      /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetHiLoByte(data)                                       ((uint8)(((uint32)(data))>>16))      /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetLoHiByte(data)                                       ((uint8)(((uint32)(data))>>8))       /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */
# define Dcm_GetLoLoByte(data)                                       ((uint8)(data))                      /* PRQA S 3453 */ /* MISRA-C:2004 Rule 19.7: A function should be used in preference to a function-like macro. */



#endif /* __DCM_H__ */
