/*****************************************************************************
* Copyright 2010 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_DfltConfigData.c
* Module Description:
* Product           : Gen II Plus - EA3.0
* Author            : Owen Tosh
*****************************************************************************/
/* Version Control:
* %version:          EA3#50 %
* %derived_by:       fzh7xw %
*---------------------------------------------------------------------------------------------------------------------
* Date       Rev     Author   Change Description                                                               SCR #
* --------   ------  -------  ------------------------------------------------------------------------------  -------
* 07/18/13    1      OT       Initial Version
* 07/30/13    2      OT       Removed T_InitMtrPosSnsr_EOLData
* 07/31/13    3      OT       Removed T_InitHwTrqScaleData
* 08/02/13    4      OT       Updated software release number to 01.00.01
* 08/12/13    5      OT       Updated software release number to 01.00.02
* 08/15/13    6      OT       Updated software release number to 01.00.03
* 09/03/13    7      OT       Updated software release number to 01.01.00
* 09/05/13    8      OT       Updated software release number to 01.01.01
* 09/24/13    9      OT       Added deprecated NvM block
* 09/24/13   10      OT       Updated software release number to 01.01.02
* 10/07/13   11      OT       Updated software release number to 01.01.03
* 10/11/13   12      OT       Updated software release number to 01.01.04
* 10/24/13   13      OT       Updated software release number to 01.01.05
* 10/29/13   14      OT       Updated software release number to 01.01.06
* 11/15/13   15      OT       Updates for bootloader changes, updated software release number to 01.02.00
* 11/26/13   16      OT       Rollback bootloader changes, changed software release number to 01.01.07
* 12/05/13   17      OT       Updated software release number to 01.01.08
* 12/11/13   18      OT       Updated software release number to 01.01.09
* 01/10/14   19      OT       Changed NvM initialization routine for NvM Proxy usage
* 01/15/14   20      OT       Added memmap section directives
* 01/16/14   21      OT       Updated software release number to 02.00.00
* 01/29/14   22      OT       Updated references to NvM blocks
* 01/29/14   23      OT       Updated software release number to 02.00.01
* 02/28/14   24      OT       Updated software release number to 02.00.02
* 04/17/14   25      OT       Added SetRamBlockStatus calls to NvM block checks
* 04/28/14   26      OT       Updated software release number to 02.00.03
* 05/22/13   27      OT       Added deprecated NvM blocks for NvM security implementation
* 05/28/13   28      OT       Updated boot compatibility number
* 06/02/14   29      OT       Updated software release number to 02.01.00
* 07/21/14   30      OT       Updated software release number to 02.01.01
* 09/09/14   31      OT       Updated software release number to 02.01.02
* 10/20/14   32      OT       Updated software release number to 02.01.03
* 10/28/14   33      OT       Updated NvM initialization blocks and deprecated blocks
* 10/28/14   34      OT       Updated software release number to 02.01.04
* 11/10/14   35      OT       Updated software release number to 02.02.00
* 12/18/14   36      OT       Updated software release number to 02.02.01, updated block version check,
*                               updated boot compatibilty nubmer, and added dummy vars for compiler warnings
* 02/18/15   37      OT       Updated software release number to 03.00.00, updated block version check,
*                               updated boot compatibilty nubmer
* 03/03/15   38      OT       Updated software release number to 03.00.01
* 03/11/15   39      OT       Updated software release number to 03.01.00, updated block version check,
*                               updated boot compatibilty nubmer
* 03/26/15   40      OT       Updated software release number to 03.01.01, updated block version check
* 04/23/15   41      OT       Updated software release number to 03.02.00, updated block version check
* 05/13/15   42      OT       Updated software release number to 03.02.01, updated block version check
* 06/26/15   43      OT       Cleaned up deprecated blocks
* 06/29/15   44      OT       Updated software release number to 03.03.00, updated block version check
* 07/08/15   45      OT       Updated software release number to 03.03.01, updated block version check
* 09/10/15   46      OT       Updated software release number to 03.04.00, updated block version check
* 10/16/15   47      OT       Updated software release number to 03.05.00, updated block version check
* 01/25/16   48      OT       Updated software release number to 03.06.00, updated block version check
* 03/16/16   49      OT       Updated software release number to 03.07.00, updated block version check
* 08/25/16   50      WH       Updated software release number to 03.08.00
*/


#include "Ap_DfltConfigData.h"
#include "EPS_DiagSrvcs_SrvcLUTbl.h"


/* Select the release suffix based on the build type*/
#if	defined(ENABLE_UTILIZATION_MONITOR)
	#define D_SUFFIX    "_U"
#elif defined(ENABLE_CPUUSE_METRICS)
	#define D_SUFFIX    "_T"
#elif defined(ENABLE_METRICS)
	#define D_SUFFIX    "_O"
#elif defined(SWEEPBUILD)
	#define D_SUFFIX    "_SWP1"
#else
	#define D_SUFFIX
#endif


#define D_BLOCKVERSIONCHECK_CNT_U16		26u
#define D_BOOTCOMPATIBILITY_CNT_U16		5u

#define T_PRESENCEPATTERN_CNT_U08		{ 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, \
										  0x5A,0xF0,0xA5,0x0F,0x11,0x22,0x33,0x44, \
										  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF }

#define T_STARTTAG_CNT_U08				{ 0x74,0xEB,0xE6,0x12 }


/* Current Sw Release Number (from CM Synergy) - multiple strings are combined at compile time */
#pragma DATA_SECTION(k_SWRelNum_Cnt_u8,".SWRelNum");
CONST(uint8, AP_DFLTCONFIGDATA_CONST) k_SWRelNum_Cnt_u8[] = "Haitec_LC_03.08.00" D_SUFFIX;


/* Set up headers for logical blocks */
#pragma DATA_SECTION(T_AppPresencePattern_Cnt_u08,".AppPresencePattern");
CONST(uint8,  AP_DFLTCONFIGDATA_CONST) T_AppPresencePattern_Cnt_u08[24] = T_PRESENCEPATTERN_CNT_U08;
#pragma DATA_SECTION(T_AppBlockVersionCheck_Cnt_u16,".AppBlockVersionCheck");
CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_AppBlockVersionCheck_Cnt_u16 = D_BLOCKVERSIONCHECK_CNT_U16;
#pragma DATA_SECTION(T_CalPresencePattern_Cnt_u08,".CalPresencePattern");
CONST(uint8,  AP_DFLTCONFIGDATA_CONST) T_CalPresencePattern_Cnt_u08[24] = T_PRESENCEPATTERN_CNT_U08;
#pragma DATA_SECTION(T_CalBlockVersionCheck_Cnt_u16,".CalBlockVersionCheck");
CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_CalBlockVersionCheck_Cnt_u16 = D_BLOCKVERSIONCHECK_CNT_U16;


/* Set up boot validity table for dynamic block mapping */

typedef struct
{
	uint8	StartTag_Cnt_u08[4];
	uint16	BlockCount_Cnt_u16;
	uint16	BootCompatibility_Cnt_u16;
	uint32	AppBlockInfo_Cnt_u32[2];
	uint32	CalBlockInfo_Cnt_u32[2];
} BootValTableType;

#pragma DATA_SECTION(T_BootValidityTable_Cnt_str,".bootvaltable");
CONST(BootValTableType, AP_DFLTCONFIGDATA_CONST) T_BootValidityTable_Cnt_str = {
													T_STARTTAG_CNT_U08,
													2u,
													D_BOOTCOMPATIBILITY_CNT_U16,
													{(uint32)&Lnk_AppBlock_Start, (uint32)&Lnk_AppBlock_Length},
													{(uint32)&Lnk_CalBlock_Start, (uint32)&Lnk_CalBlock_Length} };

#pragma DATA_SECTION(T_BootValidityCRC_Cnt_u16,".bootvalcrc");
CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_BootValidityCRC_Cnt_u16 = 0u;


/* Dummy TypeH variables to remove compiler warnings */
#pragma DATA_SECTION(TypeHDummyAp0_Cnt_G_u08, ".ossDataAp_0:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp0_Cnt_G_u08;
#pragma DATA_SECTION(TypeHDummyAp8_Cnt_G_u08, ".ossDataAp_8:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp8_Cnt_G_u08;
#pragma DATA_SECTION(TypeHDummyAp9_Cnt_G_u08, ".ossDataAp_9:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp9_Cnt_G_u08;
#pragma DATA_SECTION(TypeHDummyAp10_Cnt_G_u08, ".ossDataAp_10:noinit:typeH")
VAR(uint8, AP_DFLTCONFIGDATA_VAR) TypeHDummyAp10_Cnt_G_u08;


/* Initialized locally */

static CONST(uint8, AP_DFLTCONFIGDATA_CONST) T_InitNMEC_Cnt_u8 = 0xFEu;

static CONST(uint8, AP_DFLTCONFIGDATA_CONST) T_InitSystemPolarity_Cnt_b08[2] = { 0x30u, 0x00u };


/* Initialized in driver */

CONST(PhaseCurrCal_DataType, AP_DFLTCONFIGDATA_CONST) T_ShCurrCalInit_Cnt_str =
					{ 53200.0f, 2.5f, 100.0f, 100.0f, 2.5f, 0.0f, 0.0f };

CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_CogTrqCalInit_Cnt_u16[512] =
					  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
						0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

CONST(uint16, AP_DFLTCONFIGDATA_CONST) T_CogTrqRplCompInit_Cnt_u16[9] =
					  { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };

CONST(float32, AP_DFLTCONFIGDATA_CONST) T_TorqueCmdSFInit_Uls_f32 = 1.0f;

CONST(EOTLearned_DataType, AP_DFLTCONFIGDATA_CONST) T_LearnedEOTInit_Cnt_str =
					  { 0.0f, 0.0f, FALSE, FALSE };

CONST(AvgFricLrnType, AP_DFLTCONFIGDATA_CONST) T_AvgFricLrnDataInit_Cnt_str =
					  { 0.0f,
						0.0f,
						FALSE,
						TRUE,
						1u,
						{ {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u},
						  {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u}, {0u, 0u, 0u} },
						{ {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
						  {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
						  {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f},
						  {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f} },
						{0.0f, 0.0f, 0.0f, 0.0f} };

CONST(EOLHwPosTrimType, AP_DFLTCONFIGDATA_CONST) T_EOLVehCntrOffsetInit_Cnt_str =
					  { 20000.0f, 0u };


/* Rte-defined per instance memory buffers */
extern VAR(uint8, RTE_VAR_DEFAULT_RTE_PIM_GROUP) NvMP_Rte_TrqCmdScl_TorqueCmdSF_Uls_f32[4];
extern VAR(uint8, RTE_VAR_DEFAULT_RTE_PIM_GROUP) NvMP_Rte_Polarity_Polarity_Cnt_Str[2];


/* Processing Functions */
FUNC(void, CDD_PARTNUMBER_CODE) DfltConfigData_Init1(void)
{
	VAR(NvM_RequestResultType, AUTOMATIC) BlockStatus = 0;
	VAR(ManufModeType, AUTOMATIC) NxtrMEC_Uls_T_enum;
	
	/* Nexteer MEC */
	NvM_GetErrorStatus(NVM_BLOCK_CMS_NXTRMEC, &BlockStatus);
	if (BlockStatus != NVM_REQ_OK)
	{
		Nvm_NMEC_Cnt_u8 = T_InitNMEC_Cnt_u8;
	}
	
	if( Nvm_NMEC_Cnt_u8 == 0u )
	{
		CDD_EOLSrlComSvcDft_Cnt_G_b32 = 0ul;
	}
	
	EPS_DiagSrvcs_Init();
	
	/* Read MEC */
	NxtrMEC_Uls_T_enum = NxtrMEC_Uls_G_enum;
	
	/* The following section are block checks that require the MEC to be set in Manufacturing Mode */
	if (NxtrMEC_Uls_T_enum == ManufacturingMode )
	{
		
		/* EOL Polarity */
		NvM_GetErrorStatus(Rte_NvmBlock_Polarity_Polarity_Cnt_Str, &BlockStatus);
		if (BlockStatus != NVM_REQ_OK)
		{
			NvMP_Rte_Polarity_Polarity_Cnt_Str[0] = T_InitSystemPolarity_Cnt_b08[0];
			NvMP_Rte_Polarity_Polarity_Cnt_Str[1] = T_InitSystemPolarity_Cnt_b08[1];
			NvM_SetRamBlockStatus(Rte_NvmBlock_Polarity_Polarity_Cnt_Str, TRUE);
		}
		
	}
	
}


