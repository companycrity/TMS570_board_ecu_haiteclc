/* -----------------------------------------------------------------------------
  Filename:    Dcm_Cbk.h
  Description: Interface towards the other components used by DCM.

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

#if !defined(__DCM_CBK_H__)
# define __DCM_CBK_H__

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

# include "Dcm_Types.h"



/* -----------------------------------------------------------------------------
    &&&~ Preprocessor constants (defines)
 ----------------------------------------------------------------------------- */

/* This magic number provides internal DCM generation process consistency check.All DCM files must have the same one. */
# define DCM_ADECL_MAGIC_NUMBER                                      9001


/* -----------------------------------------------------------------------------
    &&&~ Datatype definitions
 ----------------------------------------------------------------------------- */

# if (DCM_PDUROUTER_ENABLED == STD_ON)
typedef P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) DcmPduInfoTypePtr;
# endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */


/* -----------------------------------------------------------------------------
    &&&~ Function prototypes
 ----------------------------------------------------------------------------- */

# define DCM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* COM manager API */
extern FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(void);
extern FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(void);
extern FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(void);

# if (DCM_PDUROUTER_ENABLED == STD_ON)
/* RX PDU_R API */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideRxBuffer(PduIdType DcmRxPduId, PduLengthType TpSduLength, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr);
extern FUNC(void, DCM_CODE) Dcm_RxIndication(PduIdType DcmRxPduId, NotifResultType Result);
/* TX PDU_R API */
extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_ProvideTxBuffer(PduIdType DcmTxPduId, P2VAR(DcmPduInfoTypePtr, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr, PduLengthType Length);
extern FUNC(void, DCM_CODE) Dcm_TxConfirmation(PduIdType DcmTxPduId, NotifResultType Result);

#  if (DCM_PDUR_PERIODIC_TX_TYPE2_ENABLED == STD_ON)
/* Flex Ray and LIN specific workaround */
extern FUNC(void, DCM_CODE) Dcm_TriggerTransmit(PduIdType FrTxPduId, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) FrSduPtr);
#  endif

#  if (DCM_CHANGE_TP_PARAM_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_ChangeParameterConfirmation(PduIdType DcmRxPduId, NotifResultType Result);
#  endif
# endif /* (DCM_PDUROUTER_ENABLED == STD_ON) */
# if (DCM_DIDMGR_EXT_READ_CLIENT_ENABLED == STD_ON)
extern FUNC(Dcm_StatusType, DCM_CODE) Dcm_ReadDid(uint16 did, Dcm_ApplDataPtrType resDataPtr, Dcm_ApplDataLenPtrType resDataLenPtr);
# endif

# define DCM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */



#endif /* __DCM_CBK_H__ */
