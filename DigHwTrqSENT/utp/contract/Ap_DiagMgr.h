 /*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DiagMgr.h
* Module Description: This file contains diagmgr function prototypes
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Fri Dec  2 07:36:54 2011
* %version:          1 %
* %derived_by:       nz63rn %
* %date_modified:    Tue Jun 25 09:23:36 2013 %
*---------------------------------------------------------------------------*/
#ifndef AP_DIAGMGR_H
#define AP_DIAGMGR_H


/*** Public Part *************************************/

/* Globally Accessible Status Bits */
#define 	D_TESTFAILEDBIT_CNT_B8							0x01U
#define 	D_TESTFAILEDTHISOPCYCLEBIT_CNT_B8				0x02U

#endif


/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
07/20/2012	1	    LWW       Initial Version
09/20/2012	2	    LWW       Initial version with application support
09/23/2012	3	    LWW       Changed DiagMgr_SCom_GetNTCParamByte to DiagMgr_SCom_GetNTCInfo
11/07/2012	4	    JJW       Initial Det error Id and macro support
02/26/2013	6	    LWW       Made DEMEventActive array size explicit
******************************************************************************/
