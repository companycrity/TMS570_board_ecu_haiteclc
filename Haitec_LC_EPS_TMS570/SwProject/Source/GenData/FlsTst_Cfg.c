
/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : FlsTst_Cfg.c
* Module Description: Configuration file of FlsTst module
* Product           : Gen II Plus - EA3.0
* Generator         : artt 2.0.2.0
* Generation Time   : 16.12.2014 15:37:06
*****************************************************************************/
/* Version Control:
 * Date Created:      Fri Jul 13 18:34:17 2012
 * %version:          4 %
 * %date_modified:    Fri Jul 19 14:00:54 2013 %
 *---------------------------------------------------------------------------------------------------------------------
 * Date      Rev      Author         Change Description                                                        SCR #
 * -------   -------  --------  ---------------------------------------------------------------------------  ----------
 * 07/13/12   1       JJW       Initial template creation
 * 09/17/12   2       JJW       Remove extra comma in generation of FlsTst_ConfigType definition
 * 11/26/12   3       JJW       Notification funciton generation support added
 */

#include "FlsTst.h" /*[FlsTst003]*/

/* Externally defined symbols */
extern CONST(uint64, AUTOMATIC) CCT_Range_11_Address;
extern CONST(uint64, AUTOMATIC) CCT_Range_11_Start;

extern CONST(uint64, AUTOMATIC) CCT_Range_10_Address;
extern CONST(uint64, AUTOMATIC) CCT_Range_10_Start;

extern CONST(uint64, AUTOMATIC) BootCRC_Address;
extern CONST(uint64, AUTOMATIC) BootCRC_Start;

#define FLSTST_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */

/* FlsTst Notification Function Extern Definitions */
extern FUNC(void, AUTOMATIC) Appl_FlsTstCompletedNotif(void);

/* FlsTst Configuration Definitions */
CONST(FlsTst_MemBlockType, AUTOMATIC) FlsTst_MemBlk_Runtime[ 3u ] = {
	{  /* Cal block config */
		0UL,	/* CRC L32 Init Value */
		0UL,	/* CRC H32 Init Value */
		(P2CONST(uint64, AUTOMATIC, AUTOMATIC))&CCT_Range_11_Address, /*crcPtr*/
		(P2CONST(uint64, AUTOMATIC, AUTOMATIC))&CCT_Range_11_Start, /*startPtr*/
		1U, /* secnum */
		32767u, /* seclength */
		1057u, /* dmaElementCnt */
		31u /* dmaFrameCnt */
	},
	{  /* App block config */
		0UL,	/* CRC L32 Init Value */
		0UL,	/* CRC H32 Init Value */
		(P2CONST(uint64, AUTOMATIC, AUTOMATIC))&CCT_Range_10_Address, /*crcPtr*/
		(P2CONST(uint64, AUTOMATIC, AUTOMATIC))&CCT_Range_10_Start, /*startPtr*/
		1U, /* secnum */
		59388u, /* seclength */
		2828u, /* dmaElementCnt */
		21u /* dmaFrameCnt */
	},
	{  /* Boot block config */
		0UL,	/* CRC L32 Init Value */
		0UL,	/* CRC H32 Init Value */
		(P2CONST(uint64, AUTOMATIC, AUTOMATIC))&BootCRC_Address, /*crcPtr*/
		(P2CONST(uint64, AUTOMATIC, AUTOMATIC))&BootCRC_Start, /*startPtr*/
		1U, /* secnum */
		6142u, /* seclength */
		3071u, /* dmaElementCnt */
		2u /* dmaFrameCnt */
	}
};


CONST(FlsTst_ConfigType, AUTOMATIC) FlsTst_Runtime = {
	3, /* numBgndBlks */
	0, /* numBgndBlks */
	FlsTst_MemBlk_Runtime, /* MemBlk */
	Appl_FlsTstCompletedNotif	/*notifFcn*/
};


#define FLSTST_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */
