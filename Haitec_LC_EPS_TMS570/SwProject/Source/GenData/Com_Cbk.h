/* -----------------------------------------------------------------------------
  Filename:    Com_Cbk.h
  Description: Toolversion: 11.08.02.01.30.01.24.00.00.00
               
               Serial Number: CBD1300124
               Customer Info: Nexteer Automotive Corporation
                              Package: MSR_Vector_SLP3
                              Micro: TMS570LS30376USC
                              Compiler: TexasInstruments ccs 4.9.2
               
               
               Generator Fwk   : GENy 
               Generator Module: Com
               
               Configuration   : C:\Temp\Haitec_LC_EPS_TMS570\Haitec_LC_EPS_TMS570\Tools\AsrProject\Config\ECUC\EPS.ecuc.vdsxml
               
               ECU: 
                       TargetSystem: Hw_Tms470/570Cpu (Dcan)
                       Compiler:     TexasInstruments
                       Derivates:    TMS570LS30316U
               
               Channel "CAN00":
                       Databasefile: 
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         CanStateManagerConfiguration

  Generated by , 2013-07-19  12:22:09
 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2011 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(COM_CBK_H)
#define COM_CBK_H

#include "PduR_Com.h"
#define COM_START_SEC_CODE
/* PRQA S 5087 1 */ /*RULE 19.1: The memory abstraction concept uses includes of MemMap.h at any place in the source code. This is required by AUTOSAR. */
#include "MemMap.h"

#define COM_RXIND_PARA    SduPtr
#define COM_RXIND_TYPE    P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)
/**********************************************************************************************************************
  Com_RxIndication
**********************************************************************************************************************/
/** \brief    This function is called by the lower layer after an I-PDU has been received.
    \param    ComRxPduId      ID of AUTOSAR COM I-PDU that has been received. Identifies the data that has been received.
                              Range: 0..(maximum number of I-PDU IDs received by AUTOSAR COM) - 1
    \param    COM_RXIND_PARA
              SduPtr          Pointer to the received I-PDU data.\n
                              This Parameter is used, if COM_USE_PDUINFOTYPE is defined to STD_OFF.\n
              PduInfoPtr      Payload information of the received I-PDU (pointer to data and data length).\n
                              This Parameter is used, if COM_USE_PDUINFOTYPE is defined to STD_ON.    
    \return   none
    \context  The function can be called on interrupt and task level. It is not allowed to use CAT1 interrupts with Rte (BSW00326]). Due to this, the interrupt context shall be configured to a CAT2 interrupt if an Rte is used. 
    \note     The function is called by the lower layer.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_RxIndication(PduIdType ComRxPduId, COM_RXIND_TYPE COM_RXIND_PARA);

/**********************************************************************************************************************
  Com_TxConfirmation
**********************************************************************************************************************/
/** \brief    This function is called by the lower layer after the PDU has been transmitted on the network.
              A confirmation that is received for an I-PDU that does not require a confirmation is silently discarded.
    \param    ComTxPduId    ID of AUTOSAR COM I-PDU that has been transmitted.
                            Range: 0..(maximum number of I-PDU IDs transmitted by AUTOSAR COM) - 1
    \return   none
    \context  The function can be called on interrupt and task level. It is not allowed to use CAT1 interrupts with Rte (BSW00326]). Due to this, the interrupt context shall be configured to a CAT2 interrupt if an Rte is used. 
    \note     The function is called by the lower layer.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TxConfirmation(PduIdType ComTxPduId);

#define COM_TT_PARA      SduPtr
#define COM_TT_TYPE      P2VAR(uint8, AUTOMATIC, COM_APPL_VAR)
#define COM_TT_RETURN    void
/**********************************************************************************************************************
  Com_TriggerTransmit
**********************************************************************************************************************/
/** \brief    This function is called by the lower layer when an AUTOSAR COM I-PDU shall be transmitted.
              Within this function, AUTOSAR COM shall copy the contents of its I-PDU transmit buffer
              to the L-PDU buffer given by SduPtr.
              Use case:
              This function is used e.g. by the LIN Master for sending out a LIN frame. In this case, the trigger transmit
              can be initiated by the Master schedule table itself or a received LIN header.
              This function is also used by the FlexRay Interface for requesting PDUs to be sent in static part
              (synchronous to the FlexRay global time). Once the I-PDU has been successfully sent by the lower layer
              (PDU-Router), the lower layer must call Com_TxConfirmation().
    \param    ComTxPduId    ID of AUTOSAR COM I-PDU that is requested to be transmitted by AUTOSAR COM.
    \param    COM_TT_PARA
              SduPtr              Pointer to the received I-PDU data.\n
                                  This Parameter is used, if COM_USE_PDUINFOTYPE is defined to STD_OFF.\n
              PduInfoPtr          Payload information of the received I-PDU (pointer to data and data length).\n
                                  This Parameter is used, if COM_USE_PDUINFOTYPE is defined to STD_ON.
    \return   COM_TT_RETURN
              none                No return value.\n
                                  This return value is used, if COM_USE_PDUINFOTYPE is defined to STD_OFF.\n
              Std_ReturnType      This  return value is used, if COM_USE_PDUINFOTYPE is defined to STD_ON.
                                  E_OK:     The SDU has been copied and the SduLength indicates
                                            the number of copied bytes.\n
                                  E_NOT_OK: The SDU has not been copied and the SduLength has not been set.                                  
    \context  The function can be called on interrupt and task level. It is not allowed to use CAT1 interrupts with Rte (BSW00326]). Due to this, the interrupt context shall be configured to a CAT2 interrupt if an Rte is used. 
    \note     The function is called by the lower layer.
**********************************************************************************************************************/
FUNC(COM_TT_RETURN, COM_CODE) Com_TriggerTransmit(PduIdType ComTxPduId, COM_TT_TYPE COM_TT_PARA);

/**********************************************************************************************************************
  Com_TpProvideRxBuffer
**********************************************************************************************************************/
/** \brief    This function called by the lower layer to query for a receive buffer that is required to recive 
              a TP layer I-PDU. COM will always provides a buffer that allows the TP layer to store the
              complete TP I-PDU.
              The TpSduLength must match with the COM I-PDU length to allow COM to receive the I-PDU.
    \param    ComRxPduId  ID of AUTOSAR COM I-PDU that will be received.
    \param    TpSduLength Length of the I-PDU that will be received.
    \param    PduInfoPtr**  Reference where COM will locate a pointer to the data buffer that will be used as Rx buffer.
    \return   BUFREQ_OK if COM accepts the reception. If COM cannot receive the I-PDU BUFREQ_E_NOT_OK is returned.
    \context  The function can be called on interrupt and task level. It is not allowed to use CAT1 interrupts with Rte (BSW00326]). Due to this, the interrupt context shall be configured to a CAT2 interrupt if an Rte is used. 
    \note     The function is called by the lower layer.
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, COM_CODE) Com_TpProvideRxBuffer(PduIdType ComRxPduId, PduLengthType TpSduLength, P2VAR(PduInfoTypeApplPtr, AUTOMATIC, COM_APPL_VAR) PduInfoPtr);

/**********************************************************************************************************************
  Com_TpRxIndication
**********************************************************************************************************************/
/** \brief    This function is called by the lower layer after a COM TP layer I-PDU has been received completely
              (Result has to indicate NTFRSLT_OK) or if the TP layer has canceled the reception due to any error.
              In this case, Result has to indicate the type of error.
    \param    ComRxPduId  ID of AUTOSAR COM I-PDU that has been received.
    \param    Result NTFRSLT_OK indicates that the reception was successfull. Any other value is handled
              as an error by COM.
    \return   none
    \context  The function can be called on interrupt and task level. It is not allowed to use CAT1 interrupts with Rte (BSW00326]). Due to this, the interrupt context shall be configured to a CAT2 interrupt if an Rte is used. 
    \note     The function is called by the lower layer.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TpRxIndication(PduIdType ComRxPduId, NotifResultType Result);

/**********************************************************************************************************************
  Com_TpProvideTxBuffer
**********************************************************************************************************************/
/** \brief    This function called by the lower layer to query for a transmit buffer containing the I-PDU data
              that is to be transmitted. COM will always provide a buffer that allows the TP layer
              to transmit the complete TP I-PDU without querying for a further buffer.
              The requested buffer size (Length) must either be zero (any size) or must indicate the exact length of
              the COM I-PDU that is to be transmitted.
    \param    ComTxPduId     ID of AUTOSAR COM I-PDU that will be transmitted.
    \param    PduInfoPtr**  Reference where COM will locate a pointer to the data that will be transmitted
    \param    Length              Number of bytes required by the lower layer. 0 is handed as wild card.
    \return   BUFREQ_OK if COM   has provided the requested buffer.
              BUFREQ_E_NOT_OK    indicates an error
    \context  The function can be called on interrupt and task level. It is not allowed to use CAT1 interrupts with Rte (BSW00326]). Due to this, the interrupt context shall be configured to a CAT2 interrupt if an Rte is used. 
    \note     The function is called by the lower layer.
**********************************************************************************************************************/
FUNC(BufReq_ReturnType, COM_CODE) Com_TpProvideTxBuffer(PduIdType ComTxPduId, P2VAR(PduInfoTypeApplPtr, AUTOMATIC, COM_APPL_VAR) PduInfoPtr, uint16 Length);

/**********************************************************************************************************************
  Com_TpTxConfirmation
**********************************************************************************************************************/
/** \brief    This function is called by the lower layer after a COM TP layer I-PDU has been transmitted completely
              (Result has to indicate NTFRSLT_OK) or if the TP layer has canceled the transmission due to any error.
              In this case, Result has to indicate the type of error.
    \param    ComTxPduId    ID of AUTOSAR COM I-PDU that has been transmitted.
    \param    Result        Indicates if the transmission has been successfull (NTFRSLT_OK) or not
    \return   none
    \context  The function can be called on interrupt and task level. It is not allowed to use CAT1 interrupts with Rte (BSW00326]). Due to this, the interrupt context shall be configured to a CAT2 interrupt if an Rte is used. 
    \note     The function is called by the lower layer.
**********************************************************************************************************************/
FUNC(void, COM_CODE) Com_TpTxConfirmation(PduIdType ComTxPduId, NotifResultType Result);



#define COM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /*RULE 19.1: The memory abstraction concept uses includes of MemMap.h at any place in the source code. This is required by AUTOSAR. */
#include "MemMap.h"


#define COM_START_SEC_APPL_CODE
/* PRQA S 5087 1 */ /*RULE 19.1: The memory abstraction concept uses includes of MemMap.h at any place in the source code. This is required by AUTOSAR. */
#include "MemMap.h"

/**********************************************************************************************************************
  I-PDU Callout Prototypes
**********************************************************************************************************************/
FUNC(boolean, COM_APPL_CODE) Appl_COMCout_Pdu_EPAS1__CAN00(PduIdType ComTxPduId, P2VAR(uint8, AUTOMATIC, COM_VAR_NOINIT) SduPtr);

#define COM_STOP_SEC_APPL_CODE
/* PRQA S 5087 1 */ /*RULE 19.1: The memory abstraction concept uses includes of MemMap.h at any place in the source code. This is required by AUTOSAR. */
#include "MemMap.h"



#endif /* COM_CBK_H */