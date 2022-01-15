/* -----------------------------------------------------------------------------
  Filename:    xcp_par.c
  Description: Toolversion: 11.08.02.01.30.01.24.00.00.00
               
               Serial Number: CBD1300124
               Customer Info: Nexteer Automotive Corporation
                              Package: MSR_Vector_SLP3
                              Micro: TMS570LS30376USC
                              Compiler: TexasInstruments ccs 4.9.2
               
               
               Generator Fwk   : GENy 
               Generator Module: Xcp
               
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

  Generated by , 2013-07-19  08:51:13
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

#if !defined(XCP_PAR_C)
#define XCP_PAR_C

#include "v_inc.h"
#include "XcpProf.h"

#ifdef XCP_ENABLE_MEM_MAPPING
#define XCP_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

CONST(Xcp_TlApiType, XCP_CONST) Xcp_TlApi[1] = 
{
  
  {
    CanXcp_MainFunction /* ApplXcpBackground */, 
    CanXcp_Transmit /* ApplXcpSend */, 
    CanXcp_SendFlush /* ApplXcpSendFlush */
  }
};

/* Events */
CONST(XcpCharType, XCP_CONST) kXcpEventName_0[] = "2ms_DAQ";
CONSTP2CONST(XcpCharType, XCP_CONST, XCP_CONST) kXcpEventName[] = 
{
  &kXcpEventName_0[0]
};
CONST(uint8, XCP_CONST) kXcpEventNameLength[] = 
{
  (uint8) 7
};
CONST(uint8, XCP_CONST) kXcpEventCycle[] = 
{
  (uint8) 2
};
CONST(uint8, XCP_CONST) kXcpEventUnit[] = 
{
  (uint8) DAQ_TIMESTAMP_UNIT_1MS
};
CONST(uint8, XCP_CONST) kXcpEventDirection[] = 
{
  (uint8) DAQ_EVENT_DIRECTION_DAQ
};
/* Online calibration */
/* Flash programming */
#ifdef XCP_ENABLE_MEM_MAPPING
#define XCP_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#endif /* XCP_PAR_C */
