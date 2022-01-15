/********************************************************************************************************************
|    File Name: CANIF_TYPES.H
|
|  Description: Type definitions of the AUTOSAR CAN Interface
|--------------------------------------------------------------------------------------------------------------------
|               C O P Y R I G H T
|--------------------------------------------------------------------------------------------------------------------
| Copyright (c) 1996-2011 by Vector Informatik GmbH.       All rights reserved.
|
| This software is copyright protected and proprietary
| to Vector Informatik GmbH. Vector Informatik GmbH
| grants to you only those rights as set out in the
| license conditions. All other rights remain with
| Vector Informatik GmbH.
|
|--------------------------------------------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|--------------------------------------------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Ard          Thomas Arnold             Vector Informatik GmbH
| Rna          Ruediger Naas             Vector Informatik GmbH
| Seu          Eugen Stripling           Vector Informatik GmbH
| Bir          Holger Birke              Vector Informatik GmbH
|--------------------------------------------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|--------------------------------------------------------------------------------------------------------------------
| Date        Version   Author  Description
| ----------  --------  ------  -------------------------------------------------------------------------------------
| 2005-09-12  0.01      Ard     - first implementation
| 2006-02-09  0.02      Ard     - Add DET error CANIF_E_FATAL
| 2006-02-13  0.03      Ard     - activate Tx queue per default
| 2006-03-30  0.04      Ard     - Add const qualifier to type definition of
|                                 CanIf_RxIndicationFctType1
| 2006-04-05  0.05      Ard     - Remove controller state check in CanIf_Init()
| 2006-04-25  0.06      Ard     - Activate Tx Queue by default (fix)
| 2006-05-24  2.00      Ard     - AUTOSAR 2.0
| 2006-05-31  2.01      Ard     - DET support
|                                 rename CANIF_CS_STOP mode
| 2006-06-22  2.02      Ard     - Add CANIF_E_PARAM_NETWORK
| 2006-07-03  2.03      Ard     - Change EcuM and ComM header includes
| 2006-07-05  2.04      Ard     - Change EcuM and ComM header includes
|                                 Add redefinition to CANIF_READRXPDU_DATA_API
| 2006-07-12  2.05      Ard     - Move redefinition to CANIF_READRXPDU_DATA_API to CanIf.h
| 2006-09-18  2.06      Ard     - Change API ID defines
| 2006-11-17  2.07      Ard     - Support postbuild configurations
| 2006-12-20  2.08      Ard     - Change CanIf_ConfigType
| 2007-03-12  3.00      Ard     - AUTOSAR 2.1
| 2007-09-11  3.01      Ard     - ESCAN00022291: Fix memory qualifiers
| 2007-10-18  3.02      Ard     - ESCAN00022824: Remove UpperLayerPduId from CanIf_TxPduConfigType
| 2007-11-05  3.03      Ard     - ESCAN00023167: Introduce binary search
|                                 ESCAN00023168: Support extended IDs
| 2008-02-22  4.00      Ard     - ESCAN00024947: AUTOSAR 3.0 
| 2008-04-21  4.01      Ard     - ESCAN00026257: Fix spelling of include filenames
| 2008-07-29  4.02      Ard     - ESCAN00027656: Support wake up validation
|                                 ESCAN00029110: Remove channel specific bus off notification function
|                                 ESCAN00029315: Change version definitions
| 2008-09-19  4.03      Ard     - ESCAN00029828: Support precompile and link-time CRC check
| 2009-03-03  4.04      Ard     - ESCAN00032595: Support transceiver state transition to normal during wake up
|                                 ESCAN00033608: Support new requirements (DEM to DET, ApplDlcErrorNotification)
| 2009-04-09  4.05      Ard     - ESCAN00034547: Support new requirements (TxPduId Mapping)
| 2009-07-01  4.06      Rna     - ESCAN00034553: Provide Hash Search algorithm
| 2009-07-23  4.07      Rna     - ESCAN00036101: pre-processor checks for building the library
| 2010-01-11  4.08      Rna     - ESCAN00039888: @CanIf_HlIndication() incompatible near pointer cast (changes only for CanIf_Types.h)
| 2010-01-20  4.09      Rna     - ESCAN00040264: Support 8 and 16 bit CanIf_HwHandleType for variable Hrh
| 2010-03-08  4.10      Rna     - ESCAN00041353: Support dynamic Tx objects
| 2010-07-14  4.11      Rna     - ESCAN00043501: Support Tx Bitqueue
| 2010-10-04  4.12      Rna     - ESCAN00045749: Support "Teilnetzbetrieb"
| 2011-02-17            Rna       ESCAN00048762: type "vuintX" is undefined
|*******************************************************************************************************************/
#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

/*******************************************************************************************************************/
/*  CanIf_Types.h is only allowed to be included by CanIf_Cfg.h                                                    */
/*******************************************************************************************************************/

#include "ComStack_Types.h"
#include "Can.h"
#include "EcuM_Cbk.h"


/*******************************************************************************************************************/
/*  Compatibility / Defaults                                                                                       */
/*******************************************************************************************************************/
#if (CAN_GEN_BASE_VERSION >= 0x0105u)
#define CanIf_HwHandleType Can_HwHandleType
#else
#define CanIf_HwHandleType uint8
#endif


#if !defined (CANIF_CRC_CHECK)
# define CANIF_CRC_CHECK                      STD_OFF
#endif

#if !defined (CANIF_COMPATIBILITY_AUTOSAR21)
# define CANIF_COMPATIBILITY_AUTOSAR21        STD_OFF
#endif

#if !defined (CANIF_TRCV_WAKEUPSTATETRANSITION)
# define CANIF_TRCV_WAKEUPSTATETRANSITION     STD_OFF
#endif

#if !defined (CANIF_DEMTODET_E_FULL_TX_BUFFER)
# define CANIF_DEMTODET_E_FULL_TX_BUFFER      STD_OFF
#endif

#if !defined (CANIF_DEMTODET_E_STOPPED)
# define CANIF_DEMTODET_E_STOPPED             STD_OFF
#endif

#if !defined (CANIF_ENABLE_TX_LPDU_REMAPPING)
# define CANIF_ENABLE_TX_LPDU_REMAPPING       STD_OFF
#endif

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
# include "CanIf_ComM.h"
#endif

/*******************************************************************************************************************/
/*  Defines                                                                                                        */
/*******************************************************************************************************************/
/*Configuration variants*/
#define CANIF_CFGVAR_PRECOMPILETIME       1u
#define CANIF_CFGVAR_LINKTIME             2u
#define CANIF_CFGVAR_POSTBUILDTIME        3u

/* Version */

/* Version of CanIf_Types header */
#define CANIF_TYPES_MAJOR_VERSION     0x04
#define CANIF_TYPES_MINOR_VERSION     0x12
#define CANIF_TYPES_PATCH_VERSION     0x00


/* Development Errors */

#define CANIF_E_PARAM_CANID                   10
#define CANIF_E_PARAM_DLC                     11
#define CANIF_E_PARAM_LPDU                    12
#define CANIF_E_PARAM_HRH                     13
#define CANIF_E_PARAM_CHANNEL                 14
#define CANIF_E_PARAM_CONTROLLER              15

/*
#define CANIF_E_PARAM_NETWORK                 16
#define CANIF_E_PARAM_MODEREQUEST             17
*/

#define CANIF_E_PARAM_POINTER                 20
#define CANIF_E_UNINIT                        30
#define CANIF_E_NOK_NOSUPPORT                 40

#define CANIF_TRCV_E_TRANSCEIVER              50

#define CANIF_TRCV_E_TRCV_NOT_STANDBY         60
#define CANIF_TRCV_E_TRCV_NOT_NORMAL          70
#define CANIF_E_INVALID_TXPDUID               80
#define CANIF_E_INVALID_RXPDUID               90

/* Not defined by AUTOSAR */
#define CANIF_E_CONFIG                        45
#define CANIF_E_FATAL                         46




/* Production Errors */

/* DEM Errors - defined external */
/*

#define CANIF_E_INVALID_DLC                   51
#define CANIF_E_STOPPED                       52
#define CANIF_E_FULL_TX_BUFFER                53

*/

#if (CANIF_DEMTODET_E_STOPPED == STD_ON)
# define CANIF_E_STOPPED                      110
#endif
 
#if (CANIF_DEMTODET_E_FULL_TX_BUFFER == STD_ON)
# define CANIF_E_FULL_TX_BUFFER               120
#endif



/* Module ID of CAN Interface */
#define CANIF_MODULE_ID                       60

/* Vendor ID of CAN Interface */
#define CANIF_VENDOR_ID                       0x001E

/* Search algorithm */
#define CANIF_LINEAR                          1
#define CANIF_BINARY                          2
#define CANIF_DOUBLE_HASH                     3

/* Invalid PDU handles */
#define CanIf_TxPduHnd_INVALID                ((PduIdType)-1)
#define CanIf_RxPduHnd_INVALID                ((PduIdType)-1)

#define CanIf_TrcvIndex_INVALID               ((uint8)-1)



/* ApiIDs for Error Reporting */
#define CANIF_INIT_API                        1
#define CANIF_INITCONTROLLER_API              2
#define CANIF_SETCONTROLLERMODE_API           3
#define CANIF_GETCONTROLLERMODE_API           4
#define CANIF_TRANSMIT_API                    5
#define CANIF_READRXDATA_API                  6

/* #define CANIF_READTXNOTIFSTATUS_API           7 */
/* #define CANIF_READRXNOTIFSTATUS_API           8 */

#define CANIF_SETPDUMODE_API                  9
#define CANIF_GETPDUMODE_API                  10
#define CANIF_GETVERSIONINFO_API              11

/* #define CANIF_SETDYNAMICTXID_API              12 */

#define CANIF_SETTRANSCEIVERMODE_API          13
#define CANIF_GETTRANSCEIVERMODE_API          14
#define CANIF_TRCVWAKEUPREASON_API            15
#define CANIF_SETTRANSCEIVERWAKEUPMODE_API    16

#define CANIF_CHECKWAKEUP_API                 17

#define CANIF_CHECKVALIDATIONUP_API           18

#define CANIF_TXCONFIRMATION_API              19
#define CANIF_RXINDICATION_API                20

#define CANIF_CANCELTXCONFIRMATION_API        21

#define CANIF_CONTROLLERBUSOFF_API            22

/* Not defined by AUTOSAR */
#define CANIF_CANCELTRANSMIT_API              250
#define CANIF_TXNOTIFICATION_API              251



/*******************************************************************************************************************/
/*  Data types                                                                                                     */
/*******************************************************************************************************************/


typedef enum {
  CANIF_CS_UNINIT = 0,
  CANIF_CS_STOPPED,
  CANIF_CS_STARTED,
  CANIF_CS_SLEEP
} CanIf_ControllerModeType;


typedef enum {
  CANIF_SET_OFFLINE = 0,
  CANIF_SET_RX_OFFLINE,
  CANIF_SET_RX_ONLINE,
  CANIF_SET_TX_OFFLINE,
  CANIF_SET_TX_ONLINE,
  CANIF_SET_ONLINE,
  CANIF_SET_TX_OFFLINE_ACTIVE
} CanIf_PduSetModeType;

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
typedef CanIf_PduSetModeType CanIf_ChannelSetModeType;
#endif

typedef enum {
  CANIF_GET_OFFLINE = 0,
  CANIF_GET_RX_ONLINE,
  CANIF_GET_TX_ONLINE,
  CANIF_GET_ONLINE,
  CANIF_GET_OFFLINE_ACTIVE,
  CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE
} CanIf_PduGetModeType;

#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
typedef CanIf_PduGetModeType CanIf_ChannelGetModeType;
#endif

typedef enum {
  CANIF_RxBasicCANMailbox = 0,
  CANIF_RxFullCANMailbox,
  CANIF_TxBasicCANMailbox,
  CANIF_TxFullCANMailbox,
  CANIF_UnusedCANMailbox
} CanIf_MailBoxTypeType;


typedef enum {
  CanIf_SimpleRxIndicationLayout = 0,
  CanIf_AdvancedRxIndicationLayout,
  CanIf_NmOsekRxIndicationLayout
} CanIf_RxIndicationLayoutType;


typedef enum {
  CANIF_NO_NOTIFICATION = 0,
  CANIF_TX_RX_NOTIFICATION
} CanIf_NotifStatusType;


typedef enum {
  CANIF_TRCV_MODE_NORMAL = 0,
  CANIF_TRCV_MODE_STANDBY,
  CANIF_TRCV_MODE_SLEEP
} CanIf_TransceiverModeType;


typedef enum {
  CANIF_TRCV_WU_ERROR = 0,
  CANIF_TRCV_WU_NOT_SUPPORTED,
  CANIF_TRCV_WU_BY_BUS,
  CANIF_TRCV_WU_INTERNALLY,
  CANIF_TRCV_WU_RESET,
  CANIF_TRCV_WU_POWER_ON
} CanIf_TrcvWakeupReasonType;


typedef enum {
  CANIF_TRCV_WU_ENABLE = 0,
  CANIF_TRCV_WU_DISABLE,
  CANIF_TRCV_WU_CLEAR
} CanIf_TrcvWakeupModeType;


typedef enum 
{
  CANIF_WAKEUPREQUEST_NONE = 0,
  CANIF_WAKEUPREQUEST_CAN  = 1,
  CANIF_WAKEUPREQUEST_TRCV = 2
} CanIf_WakeUpTargetType;



typedef enum
{
  CANIF_WUVALIDATION_IDLE     = 0,
  CANIF_WUVALIDATION_ARMED    = 1,
  CANIF_WUVALIDATION_DETECTED = 2
} CanIf_WakeUpValidationStateType;


/* Type of confirmation function */
/* typedef void (*CanIf_TxConfirmationFctType)(PduIdType CanTxPduId); */
typedef P2FUNC(void, CANIF_APPL_MSG_CODE, CanIf_TxConfirmationFctType) (VAR(PduIdType, AUTOMATIC) CanTxPduId);


/* Type of indication function */
/* Simple type for CanNm, PduR */
/* typedef void (*CanIf_SimpleRxIndicationFctType)(PduIdType CanRxPduId, const uint8 *CanSduPtr); */
typedef P2FUNC(void, CANIF_APPL_MSG_CODE, CanIf_SimpleRxIndicationFctType) (VAR(PduIdType, AUTOMATIC) CanRxPduId, P2CONST(uint8, AUTOMATIC, CANIF_UL_STANDARD_VAR) CanSduPtr);

/* Advanced type for CanTP */
/* typedef void (*CanIf_AdvancedRxIndicationFctType)(PduIdType CanRxPduId, const PduInfoType *PduInfoPtr);  */
/* PduInfoPtr is created on stack -> AUTOMATIC */
typedef P2FUNC(void, CANIF_APPL_MSG_CODE, CanIf_AdvancedRxIndicationFctType) (VAR(PduIdType, AUTOMATIC) CanRxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_UL_ADVANCED_VAR) PduInfoPtr);

/* NmOsek type */
/* typedef void (*CanIf_NmOsekRxIndicationFctType)(PduIdType CanRxPduId, const uint8 *CanSduPtr, Can_IdType CanId); */
typedef P2FUNC(void, CANIF_APPL_MSG_CODE, CanIf_NmOsekRxIndicationFctType) (VAR(PduIdType, AUTOMATIC) CanRxPduId, P2CONST(uint8, AUTOMATIC, CANIF_UL_OSEKNM_VAR) CanSduPtr, VAR(Can_IdType, AUTOMATIC) CanId);


/* BusOff Notification */
#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* typedef void (*CanIf_BusOffNotificationFctType)(ComM_ChannelHandleType CanNetwork) */
typedef P2FUNC(void, CANIF_APPL_STATE_CODE, CanIf_BusOffNotificationFctType) (VAR(ComM_ChannelHandleType, AUTOMATIC) CanNetwork);
#else
/* typedef void (*CanIf_BusOffNotificationFctType)(uint8 Controller); */
typedef P2FUNC(void, CANIF_APPL_STATE_CODE, CanIf_BusOffNotificationFctType) (VAR(uint8, AUTOMATIC) Controller);
#endif

/* WakeUp Event */
/* typedef void (*CanIf_WakeUpEventFctType)(EcuM_WakeupSourceType CanWakeupEvents); */
typedef P2FUNC(void, CANIF_APPL_STATE_CODE, CanIf_WakeUpEventFctType) (VAR(EcuM_WakeupSourceType, AUTOMATIC) CanWakeupEvents);

/* WakeUp Validation */
/* typedef void (*CanIf_WakeUpValidationFctType)(EcuM_WakeupSourceType, CanWakeupEvents); */
typedef P2FUNC(void, CANIF_APPL_STATE_CODE, CanIf_WakeUpValidationFctType) (VAR(EcuM_WakeupSourceType, AUTOMATIC) CanWakeupEvents);

/* DLC error notification */
/* typedef void (*CanIf_WakeUpValidationFctType)(EcuM_WakeupSourceType, CanWakeupEvents); */
typedef P2FUNC(void, CANIF_APPL_MSG_CODE, CanIf_DlcErrorNotifictionFctType) (VAR(PduIdType, AUTOMATIC) CanRxPduId);


#if (CANIF_COMPATIBILITY_AUTOSAR21 == STD_ON)
/* CanTrcv_SetOpMode */
/* typedef void (*CanIf_CanTrcv_InitFctType)(void); */
typedef P2FUNC(void, CANIF_CBK_TRCV_CODE, CanIf_CanTrcv_InitFctType) (void);
#endif

/* CanTrcv_CB_WakeupByBus */
/* typedef Std_ReturnType (*CanIf_CanTrcv_CB_WakeupByBusFctType)(uint8 transceiver); */
typedef P2FUNC(Std_ReturnType, CANIF_CBK_TRCV_CODE, CanIf_CanTrcv_CB_WakeupByBusFctType) (VAR(uint8, AUTOMATIC) transceiver);

/* CanTrcv_SetOpMode */
/* typedef Std_ReturnType (*CanIf_CanTrcv_SetOpModeFctType)(CanIf_TransceiverModeType OpMode, uint8 transceiver); */
typedef P2FUNC(Std_ReturnType, CANIF_CBK_TRCV_CODE, CanIf_CanTrcv_SetOpModeFctType) (VAR(CanIf_TransceiverModeType, AUTOMATIC) OpMode, VAR(uint8, AUTOMATIC) transceiver);

/* CanTrcv_GetOpMode */
/* typedef Std_ReturnType (*CanIf_CanTrcv_GetOpModeFctType)(CanIf_TransceiverModeType *OpMode, uint8 transceiver); */
typedef P2FUNC(Std_ReturnType, CANIF_CBK_TRCV_CODE, CanIf_CanTrcv_GetOpModeFctType) (P2VAR(CanIf_TransceiverModeType, AUTOMATIC, CANIF_APPL_STATE_VAR) OpMode, VAR(uint8, AUTOMATIC) transceiver);

/* CanTrcv_GetBusWuReason */
/* typedef Std_ReturnType (*CanIf_CanTrcv_GetBusWuReasonFctType)(uint8 transceiver, CanIf_TrcvWakeupReasonType *Reason); */
typedef P2FUNC(Std_ReturnType, CANIF_CBK_TRCV_CODE, CanIf_CanTrcv_GetBusWuReasonFctType) (VAR(uint8, AUTOMATIC) transceiver, P2VAR(CanIf_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_STATE_VAR)Reason);

/* CanTrcv_SetWakeupMode */
/* typedef Std_ReturnType (*CanIf_CanTrcv_SetWakeupModeFctType)(CanIf_TrcvWakeupModeType TrcvWakeupMode, uint8 transceiver); */
typedef P2FUNC(Std_ReturnType, CANIF_CBK_TRCV_CODE, CanIf_CanTrcv_SetWakeupModeFctType) (CanIf_TrcvWakeupModeType TrcvWakeupMode, VAR(uint8, AUTOMATIC) transceiver);



typedef union {
  CanIf_SimpleRxIndicationFctType     eSimpleRxIndicationType;
  CanIf_AdvancedRxIndicationFctType   eAdvancedRxIndicationType;
  CanIf_NmOsekRxIndicationFctType     eNmOsekRxIndicationType;
} CanIf_RxIndicationFctType;


typedef struct sCanIf_RxIndicationFctStructType {
  CanIf_RxIndicationFctType           eRxIndicationFct;
  CanIf_RxIndicationLayoutType        eRxIndicationLayout;
} CanIf_RxIndicationFctStructType;


typedef struct sCanIf_ControllerConfigType 
{
  PduIdType eTxBCStartIndex;                /* Startindex of normal Tx handles in CanIf_TxPduConfig table   */
  PduIdType eTxBCStopIndex;                 /* Startindex of normal Tx handles in CanIf_TxPduConfig table   */
} CanIf_ControllerConfigType;



typedef struct sCanIf_TxQueueType 
{
  uint8         eSdu[8];                              /* const 64 bit                      */
  PduLengthType eSduLength;                           /* uint8: defined in comstack_types  */
  uint8         eQueued;                              /* queued flag                       */
} CanIf_TxQueueType;


typedef struct sCanIf_TxBitQueueType 
{
  uint8         eSdu[8];                              /* const 64 bit                      */
  PduLengthType eSduLength;                           /* uint8: defined in comstack_types  */
} CanIf_TxBitQueueType;


#if ( CPU_TYPE == CPU_TYPE_32 )
typedef uint32 CanIf_TxQueueFlagType;
#endif
#if ( CPU_TYPE == CPU_TYPE_16 )
typedef uint16 CanIf_TxQueueFlagType;
#endif
#if ( CPU_TYPE == CPU_TYPE_8 )
typedef uint8  CanIf_TxQueueFlagType;
#endif


typedef struct sCanIf_MailBoxConfigType 
{
  PduIdType             ePduIdFirst;                /* First entry of PDU list  */
  PduIdType             ePduIdLast;                 /* Last entry of PDU list   */
  CanIf_MailBoxTypeType eMailBoxType;               /* Mailbox Type             */
  uint8                 eController;                /* Can Controller           */
} CanIf_MailBoxConfigType;


typedef struct sCanIf_RxPduConfigType 
{
  PduIdType                       eUpperPduId;      /* Pdu ID defined by upper layer */
  uint8                           eDlc;             /* Data Length Code              */
  uint8                           eRxIndication;    /* indication function call back */
} CanIf_RxPduConfigType;


typedef struct sCanIf_TxPduConfigType 
{
  Can_IdType                      eId;              /* 16 bit / 32 bit                    */
  uint8                           eController;      /* Controller / Channel               */
  CanIf_HwHandleType              eHth;             /* Hardware transmit handle           */
  uint8                           eLength;          /* DLC                                */
  uint8                           eTxConfirmation;  /* confirmation function              */
#if (CANIF_ENABLE_TX_LPDU_REMAPPING == STD_ON)
  PduIdType                       eMappedPduId;     /* Mapped PduID for TX LPDU remapping */
#endif
} CanIf_TxPduConfigType;


typedef struct sCanIf_WakeUpConfigType 
{
  EcuM_WakeupSourceType           eWakeUpSource;                  /* Wake Up source identifier                                */
  CanIf_WakeUpTargetType          eWakeUpTargetModule;            /* Target for CAN If (trcv / drv)                           */
  uint8                           eWakeUpTargetAddress;           /* Index to address target with                             */
  uint8                           eController;                    /* CAN Controller which is connected to the wake up source  */
} CanIf_WakeUpConfigType;


typedef struct sCanIf_TransceiverMapType
{
  uint8                           eDriverIndex;
  uint8                           eDriverAddress;
} CanIf_TransceiverMapType;


/* typedef V_MEMROM1 boolean V_MEMROM2 V_MEMROM3  *CanIf_PNControllerConfigPtrType; */
typedef P2CONST(uint8, TYPEDEF, CANIF_CONST) CanIf_PNControllerConfigPtrType;

/* typedef V_MEMROM1 uint8 V_MEMROM2 V_MEMROM3  *CanIf_ConfigLinkType; */
typedef P2CONST(uint8, TYPEDEF, CANIF_CONST) CanIf_ConfigLinkType;

/* typedef V_MEMROM1 CanIf_ControllerConfigType V_MEMROM2 V_MEMROM3  *CanIf_ControllerConfigPtrType; */
typedef P2CONST(CanIf_ControllerConfigType, TYPEDEF, CANIF_PBCFG) CanIf_ControllerConfigPtrType;

/* typedef V_MEMROM1 CanIf_RxPduConfigType V_MEMROM2 V_MEMROM3       *CanIf_RxPduConfigPtrType; */
typedef P2CONST(CanIf_RxPduConfigType, TYPEDEF, CANIF_PBCFG) CanIf_RxPduConfigPtrType;

/* typedef V_MEMROM1 Can_IdType V_MEMROM2 V_MEMROM3                  *CanIf_CanIdPtrType; */
typedef P2CONST(Can_IdType, TYPEDEF, CANIF_PBCFG) CanIf_CanIdPtrType;

/* typedef V_MEMROM1 CanIf_TxPduConfigType V_MEMROM2 V_MEMROM3       *CanIf_TxPduConfigPtrType; */
typedef P2CONST(CanIf_TxPduConfigType, TYPEDEF, CANIF_PBCFG) CanIf_TxPduConfigPtrType;

/* typedef V_MEMROM1 CanIf_MailBoxConfigType V_MEMROM2 V_MEMROM3     *CanIf_MailBoxConfigPtrType; */
typedef P2CONST(CanIf_MailBoxConfigType, TYPEDEF, CANIF_PBCFG) CanIf_MailBoxConfigPtrType;

/* typedef V_MEMROM1 Can_ConfigType V_MEMROM2 V_MEMROM3              *CanIf_CanConfigPtrType; */
typedef P2CONST(Can_ConfigType, TYPEDEF, CANIF_APPL_PBCFG) CanIf_CanConfigPtrType;

/* typedef V_MEMROM1 Can_ControllerConfigType V_MEMROM2 V_MEMROM3    *CanIf_CanControllerConfigPtrType; */
typedef P2CONST(Can_ControllerConfigType, TYPEDEF, CANIF_APPL_PBCFG) CanIf_CanControllerConfigPtrType;

/* typedef V_MEMROM1 PduIdType V_MEMROM2 V_MEMROM3                   *CanIf_PduIdPtrType; */
typedef P2CONST(PduIdType, TYPEDEF, CANIF_PBCFG) CanIf_PduIdPtrType;

/* typedef V_MEMROM1 CanIf_WakeUpConfigType V_MEMROM2 V_MEMROM3      *CanIf_WakeUpConfigPtrType; */
typedef P2CONST(CanIf_WakeUpConfigType, TYPEDEF, CANIF_PBCFG) CanIf_WakeUpConfigPtrType;

/* typedef V_MEMROM1 TxQueueStartIndexType V_MEMROM2 V_MEMROM3       *TxQueueStartIndexType;   */     
typedef P2CONST(uint8, TYPEDEF, CANIF_PBCFG) TxQueueStartIndexType;

/* typedef V_MEMROM1 vuint16 V_MEMROM2 V_MEMROM3                     *CanIf_VersionPtrType; */
typedef P2CONST(uint16, TYPEDEF, CANIF_PBCFG) CanIf_VersionPtrType;

/* typedef V_MEMROM1 CanIf_TransceiverMapType V_MEMROM2 V_MEMROM3    *CanIf_TransceiverMapPtrType; */
typedef P2CONST(CanIf_TransceiverMapType, TYPEDEF, CANIF_PBCFG) CanIf_TransceiverMapPtrType;

/* typedef uint8 *CanIf_ControllerToTrcvMapPtrType */
typedef P2CONST(uint8, TYPEDEF, CANIF_PBCFG) CanIf_ControllerToTrcvMapPtrType;

/* typedef PduIdType *CanIf_TxPduMapPtrType; */
typedef P2CONST(PduIdType, TYPEDEF, CANIF_PBCFG) CanIf_TxPduMapPtrType;

typedef struct sCanIf_ConfigType 
{
  uint32                            eGeneratorVersion;        /* Generator DLL Version                            */
#if (CANIF_CRC_CHECK == STD_ON)
  uint32                            eCanIfPrecompileCRC;      /* Checksum for precompile data                     */
  uint32                            eCanIfLinktimeCRC;        /* Checksum for link-time data                      */
#endif
  CanIf_ControllerConfigPtrType     eControllerConfig;        /* Pointer to controller specific configuration     */
  CanIf_RxPduConfigPtrType          eRxPduConfig;             /* Pointer to Rx PDU properties table               */
  CanIf_CanIdPtrType                eRxPduId;                 /* Pointer to Rx PDU ID table                       */
  CanIf_CanIdPtrType                eRxPduMask;               /* Pointer to Rx PDU mask table                     */
  CanIf_TxPduConfigPtrType          eTxPduConfig;             /* Pointer to Tx PDU properties table               */
  CanIf_PduIdPtrType                eTxPduQueueIndex;         /* Pointer to Tx Queue index table                  */
  CanIf_MailBoxConfigPtrType        eMailBoxConfig;           /* Pointer to mail box configuration                */
  CanIf_WakeUpConfigPtrType         eWakeUpConfig;            /* Pointer to wake up configuration                 */
  CanIf_TransceiverMapPtrType       eTransceiverMap;          /* Pointer to transceiver mapping                   */
  CanIf_PduIdPtrType                eNPB2CanIfPduId;          /* Pointer to non post build conversion table       */
#if (CANIF_TRCV_HANDLING == STD_ON)
# if (CANIF_TRCV_WAKEUPSTATETRANSITION == STD_ON)
  CanIf_ControllerToTrcvMapPtrType  eControllerToTrcvMap;     /* Pointer to Controller to Transceiver Index Map   */
# endif
#endif
#if (CANIF_ENABLE_TX_LPDU_REMAPPING == STD_ON)
  CanIf_TxPduMapPtrType             eTxPduMap;                /* Pointer to TxPdu Map                             */                             
#endif
  CanIf_CanControllerConfigPtrType  eCan_ControllerConfig;    /* Pointer to CAN Driver's controller configuration */
#if (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH)
  CanIf_CanIdPtrType                eCanIf_RxDHRandomNumber1;
  CanIf_CanIdPtrType                eCanIf_RxDHRandomNumber2;
  CanIf_PduIdPtrType                eCanIf_RxDHAdjust;
#endif
#if (CANIF_SETDYNAMICTXID_API == STD_ON)
  CanIf_PduIdPtrType                eCanIf_TxPduStatic2DynamicIndirection;
#endif
#if (CANIF_BITQUEUE == STD_ON)
  TxQueueStartIndexType             eCanIf_TxQueueStartIndex;
  CanIf_PduIdPtrType                eCanIf_TxQueuePadBits;					
#endif
  CanIf_VersionPtrType              eMagicNumber;             /* Pointer to MagicNumber                           */
  PduIdType                         eMaxRxPDUHandle;          /* Number of Rx PDUs                                */
#if (CANIF_SEARCH_ALGORITHM == CANIF_DOUBLE_HASH)
  PduIdType                         eCanIf_RxDHAdjustcount;   /* CANIF_DH_ADJUSTCOUNT                             */
#endif
  PduIdType                         eMaxTxPDUHandle;          /* Number of Tx PDUs                                */
  PduIdType                         eMaxNPBTxPDUHandle;       /* Number of Non post build Tx PDUs                 */
#if (CANIF_ENABLE_TX_LPDU_REMAPPING == STD_ON)
  PduIdType                         eMaxMappedTxPDUs;         /* Number of Mapped TxPdus ( eTxPduMap )            */
  PduIdType                         eMapTxPduOffset;          /* TxPdu Map Offset                                 */
#endif
  uint8                             eMaxController;           /* Number of Controllers                            */
  CanIf_HwHandleType                eMaxMailBox;              /* Number of Mailboxes                              */
  uint8                             eMaxTxConfirmation;       /* Number of TxConfirmation functions               */
  uint8                             eMaxRxIndication;         /* Number of RxIndication functions                 */
  uint8                             eMaxWakeUpSources;        /* Number of relevant WakeUpSources                 */
  uint8                             eMaxTransceivers;         /* Number of transceivers in system                 */
#if (CANIF_PARTIAL_NETWORK ==  STD_ON)
  CanIf_PNControllerConfigPtrType   eCanIf_WUTxPDU_Filter;     /* WU TxPdu filter active/not active on this channel*/  
  CanIf_PduIdPtrType                eCanIf_PnWakeupTxPduHandle;/* Handle of Tx PDU to be passed   */
#endif
  uint16                            eVersion;                 /* Code / Gendata compatibility version             */
  uint16                            eMagic;                   /* Magic Number                                     */
} CanIf_ConfigType;



/* const required - MEMORY qualifier not possible */
/* typedef const uint8  *SduPtrType;  */
typedef P2CONST(uint8, TYPEDEF, CANIF_APPL_MSG_VAR) SduPtrType;

/* typedef boolean CanIf_CancelResultType; */
typedef VAR(boolean, TYPEDEF) CanIf_CancelResultType;

#endif
