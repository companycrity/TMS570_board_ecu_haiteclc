/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2011 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte_Cbk.h
 *     Workspace:  C:/SynergyProjects/Haitec_LC_EPS_TMS570-nzx5jd/Haitec_LC_EPS_TMS570/Tools/AsrProject/Config/DCF/EPS.dcf
 *   ECU-Project:  EPS
 *
 *     Generator:  MICROSAR RTE Generator Version 2.19.1
 *       License:  License CBD1010124 valid for CBD1010124 Nexteer  Package: BMW MSR SIP BAC3.0     Micro: TI TMS570 TMS570LS30306  Compiler: Code Composer Studio 4.9.0
 *
 *   Description:  COM callback header file
 *********************************************************************************************************************/

/* double include prevention */
#ifndef _RTE_CBK_H
# define _RTE_CBK_H

# include "Com.h"

/* Com.h Compatibility Check */
# ifndef RTE_COM_VERSION
#  if defined (IL_VECTOR_VERSION)
#   define RTE_COM_VERSION 20U
#  else
#   if defined (IL_ASRCOM_VERSION)
#    if (IL_ASRCOM_VERSION < 0x0201U)
#     define RTE_COM_VERSION 20U
#    endif
#   endif
#  endif
#  if defined (COM_AR_MAJOR_VERSION) && defined (COM_AR_MINOR_VERSION)
#   define RTE_COM_VERSION ((COM_AR_MAJOR_VERSION * 10) + COM_AR_MINOR_VERSION)
#  endif
# endif
# ifndef RTE_COM_VERSION
#  define RTE_COM_VERSION 33U
# endif


# define RTE_START_SEC_CODE
# include "MemMap.h"

# define RTE_STOP_SEC_CODE
# include "MemMap.h"


#endif /* _RTE_CBK_H */
