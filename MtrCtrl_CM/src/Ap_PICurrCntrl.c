/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Ap_PICurrCntrl.c
 *     Workspace:  C:/Documents and Settings/nzt9hv/My Documents/Synergy/ccm_wa/ESG_Dev_65/MtrCtrl_CM-nzt9hv/MtrCtrl_CM/autosar
 *     SW-C Type:  Ap_PICurrCntrl
 *  Generated at:  Tue Nov 26 16:56:53 2013
 *
 *     Generator:  MICROSAR RTE Generator Version 2.17.2
 *       License:  License CBD1010122 valid for CBD1010122 Nexteer  GM MSR_SLP3_BSW_RTE_wGMLAN TexasInstruments TMS570 Texas Instruments
 *
 *   Description:  C-Code implementation template for SW-C <Ap_PICurrCntrl>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Thu Feb 2 13:41:03 2010
* %version:          12 %
* %derived_by:       nzt9hv %
* %date_modified:    Thu Feb 2 13:41:03 2010
******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author          Change Description               							SCR #
                                     (MDD Rev & Date)
-------   -------  --------  -----------------------------------   								----------
* 2/2/12    1.0 	RR      	  Initial Creation                     								N/A
* 3/7/12    2.0		RR			Chnages to ComOffset during offset Srv 								N/A		
* 4/18/12	3.0		RR			Changes for IPM	
* 10/21/12	4		SAH			Assign Phase advance to global interface variable.
* 11/20/12  5	   Selva 		 MtrCurrQaxFinal_Ref is added
								 Outputs are mapped acording to FDD 99B version 4
* 02/24/13  6      Selva      Updated for SF99B -v8 with only changes needed for voltage command 
								integrity check for  torque reasonableness	
 * 03/21/13  7,8 		 Selva      Updated to version 8 FDD SF99 B	                                                   7711	
 * 10/21/13  9       Selva      Updated to version 10 FDD SF99 B                                                 10050
 * 10/21/13  10       Selva      Changed Sqrt to __Sqrt for optimisation                                         10634
 * 11/06/13  11       Selva      Updated for V11 of     FDD SF99                                                   10740 
 * 11/26/13  12       Selva      Updated for V12 of FDD SF99                                                          10950
******************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Data Element Prototypes:
 ========================
  Volt_f32 of Port Interface Voltage_Volt_f32
    This signal is intended to communicate any type voltage signal measured by the ecu.  This signal has a lower limit of 0 which reequires users of the signal to provide divide by 0 protection if it is used as a denominator in a calculation.  See Vecu port prototype if a port with a lower limit is desired.


 Mode Declaration Groups:
 ========================
  StaMd_Mode
    EPS System State mode declaration

 *********************************************************************************************************************/

#include "Rte_Ap_PICurrCntrl.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


#include "Ap_PICurrCntrl_Cfg.h"
#include "Std_Types.h"
#include "CalConstants.h"
#include "fixmath.h"
#include "GlobalMacro.h"
#include "interpolation.h"
#define MTRCTRL
#include "Ap_MtrCtrl.h"
#include "MtrCtrl_Cfg.h"        

#define D_VECUMAX_VOLTS_F32                      31.0F
#define D_SQRT3OVR2_ULS_F32					    0.866025403784F
#define D_SCALERADTOCNTS_ULS_F32 				10430.3783505F
#define D_REVWITHROUND_ULS_F32					65536.5F
#define D_ROUND_ULS_F32							0.5F
#define D_DEG2RAD_ULS_F32						0.0174532925199F
#define D_GAIN_ULS_F32                          0.5F 

#define PICURRCNTRL_START_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */
/*************************/
/* Variable Definitions  */
/*************************/
/* Module Variables */
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  MtrCurrQaxPrevIntg_Volt_M_f32;
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrCurrDaxPrevIntg_Volt_M_f32;
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  MtrVoltQaxPrevFinalLimit_Volt_M_f32;
STATIC  VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltPrevDaxFinal_Volt_M_f32;
VAR(float32, AUTOMATIC) MtrCurrQaxRpl_Amp_M_f32[2];
VAR(float32, AUTOMATIC) MtrCurrQaxCog_Amp_M_f32;
STATIC  volatile VAR (float32, AUTOMATIC) MtrVoltDax_Volt_M_f32[2];                
STATIC  volatile VAR(float32, AUTOMATIC) MtrVoltQax_Volt_M_f32[2];       
STATIC  volatile VAR(float32, AUTOMATIC) MtrCurrQaxFinalRef_Amp_M_f32[2]; 

/* Display Variables */
STATIC volatile	VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  PICurrCntrl_DervLambdaQax_Volt_D_f32;
STATIC volatile	VAR(float32, AP_PICurrCntrl_VAR_NOINIT)  PICurrCntrl_DervLambdaDax_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrCurrQaxError_Amp_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrCurrDaxError_Amp_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltQaxFinal_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltQaxFinalLimit_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltDaxFinal_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltQaxProp_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltDaxProp_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltQaxInt_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) MtrVoltDaxInt_Volt_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrCurrQax_Amp_D_f32;
STATIC volatile VAR(float32, AP_PICurrCntrl_VAR_NOINIT) PICurrCntrl_MtrCurrDax_Amp_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) MtrVoltQaxIntAntiWindup_Volt_D_f32;
STATIC volatile VAR(float32, AUTOMATIC) MtrVoltDaxIntAntiWindup_Volt_D_f32;
#define PICURRCNTRL_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * Boolean: Boolean (standard type)
 * Float: Real in interval ]-FLT_MAX...FLT_MAX[ with single precision (standard type)
 * SInt16: Integer in interval [-32768...32767] (standard type)
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Defined Constants
 *
 **********************************************************************************************************************
 *
 * Primitive Type Constants:
 * =========================
 * Boolean: D_FALSE_CNT_LGC = FALSE
 * Float: D_180OVRPI_ULS_F32 = 57.295779513082
 * Float: D_2MS_SEC_F32 = 0.002
 * Float: D_2PI_ULS_F32 = 6.2831853071796
 * Float: D_ONE_ULS_F32 = 1
 * Float: D_PI_ULS_F32 = 3.1415926535898
 * Float: D_VECUMIN_VOLTS_F32 = 5
 * Float: D_ZERO_ULS_F32 = 0
 * SInt16: D_ZERO_CNT_S16 = 0
 * SInt8: D_ONE_CNT_S8 = 1
 * SInt8: D_ZERO_CNT_S8 = 0
 * UInt16: D_ZERO_CNT_U16 = 0u
 * UInt8: D_QUADRANT1_CNT_U8 = 1u
 * UInt8: D_QUADRANT2_CNT_U8 = 2u
 * UInt8: D_QUADRANT3_CNT_U8 = 3u
 * UInt8: D_QUADRANT4_CNT_U8 = 4u
 * UInt8: D_ZERO_CNT_U8 = 0u
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_AP_PICURRCNTRL_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: PICurrCntrl_Per2
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 2ms
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Implicit S/R API:
 *   -----------------
 *   Float Rte_IRead_PICurrCntrl_Per2_CorrMtrPosElec_Rev_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_EstKe_VpRadpS_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_EstR_Ohm_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_MRFMtrVel_MtrRadpS_f32(void)
 *   Float Rte_IRead_PICurrCntrl_Per2_MtrCurrDaxRef_Amp_f32(void)
 *
 * Output Interfaces:
 * ==================
 *   Implicit S/R API:
 *   -----------------
 *   void Rte_IWrite_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(void)
 *   void Rte_IWrite_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(Float data)
 *   Float *Rte_IWriteRef_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(void)
 *
 * Mode Interfaces:
 * ================
 *   Rte_ModeType_StaMd_Mode Rte_Mode_SystemState_Mode(void)
 *   Modes of Rte_ModeType_StaMd_Mode:
 *   - RTE_MODE_StaMd_Mode_DISABLE
 *   - RTE_MODE_StaMd_Mode_OFF
 *   - RTE_MODE_StaMd_Mode_OPERATE
 *   - RTE_MODE_StaMd_Mode_WARMINIT
 *   - RTE_TRANSITION_StaMd_Mode
 *
 *********************************************************************************************************************/

FUNC(void, RTE_AP_PICURRCNTRL_APPL_CODE) PICurrCntrl_Per2(void)
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: PICurrCntrl_Per2
 *********************************************************************************************************************/
	VAR(float32, AUTOMATIC) EstKe_VpRadpS_T_f32;
	VAR(float32, AUTOMATIC) EstR_Ohm_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltDax_Volt_T_f32;
	VAR(float32, AUTOMATIC) MtrVoltQax_Volt_T_f32;
	VAR(float32, AUTOMATIC) MRFMtrVel_MtrRadpS_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrDaxRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) MtrCurrQaxFinalRef_Amp_T_f32;
	VAR(float32, AUTOMATIC) NomR_Ohm_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrPosElec_Rev_T_f32;
	VAR(float32, AUTOMATIC) CorrMtrPosElec_Rad_T_f32;
	VAR(float32, AUTOMATIC) SinCorrMtrPosElec_Uls_T_f32;
	VAR(float32, AUTOMATIC)  CosCorrMtrPosElec_Uls_T_f32;
	VAR(float32, AUTOMATIC)  DervLambdaQax_Volt_T_f32;
	VAR(float32, AUTOMATIC)  DervLambdaDax_Volt_T_f32;
	VAR(uint16, AUTOMATIC)  ReadBuffer_Cnt_T_u16;
	VAR(uint16, AUTOMATIC)  WriteBuffer_Cnt_T_u16;
	VAR(float32, AUTOMATIC) DervLambdaAlphaDiag_Volt_T_f32;
	VAR(float32, AUTOMATIC) DervLambdaBetaDiag_Volt_T_f32;
	/* Configurable Start of Runnable Checkpoint */
	Rte_Call_PICurrCntrl_Per2_CP0_CheckpointReached();
	
	ReadBuffer_Cnt_T_u16 = SlowDataAccessBufIndex_Cnt_M_u16;	
	WriteBuffer_Cnt_T_u16 = (ReadBuffer_Cnt_T_u16 & 1U) ^ 1U;
	SlowDataAccessBufIndex_Cnt_M_u16 = WriteBuffer_Cnt_T_u16;
	
	EstKe_VpRadpS_T_f32= Rte_IRead_PICurrCntrl_Per2_EstKe_VpRadpS_f32();
	EstR_Ohm_T_f32 = Rte_IRead_PICurrCntrl_Per2_EstR_Ohm_f32();
	MRFMtrVel_MtrRadpS_T_f32 = Rte_IRead_PICurrCntrl_Per2_MRFMtrVel_MtrRadpS_f32();
	CorrMtrPosElec_Rev_T_f32 = Rte_IRead_PICurrCntrl_Per2_CorrMtrPosElec_Rev_f32();
	MtrCurrDaxRef_Amp_T_f32 = Rte_IRead_PICurrCntrl_Per2_MtrCurrDaxRef_Amp_f32();
	
	
	MtrVoltDax_Volt_T_f32 = MtrVoltDax_Volt_M_f32[ReadBuffer_Cnt_T_u16];
	MtrVoltQax_Volt_T_f32 = MtrVoltQax_Volt_M_f32[ReadBuffer_Cnt_T_u16];
	MtrCurrQaxFinalRef_Amp_T_f32 = MtrCurrQaxFinalRef_Amp_M_f32[ReadBuffer_Cnt_T_u16];

	
	NomR_Ohm_T_f32 = EstR_Ohm_T_f32 * D_SQRT3OVR2_ULS_F32 ;
	DervLambdaQax_Volt_T_f32 = MtrVoltQax_Volt_T_f32 -((EstKe_VpRadpS_T_f32*MRFMtrVel_MtrRadpS_T_f32) +(MtrCurrQaxFinalRef_Amp_T_f32*NomR_Ohm_T_f32));
	DervLambdaDax_Volt_T_f32 = MtrVoltDax_Volt_T_f32 -(MtrCurrDaxRef_Amp_T_f32*NomR_Ohm_T_f32);
	
	CorrMtrPosElec_Rad_T_f32 = CorrMtrPosElec_Rev_T_f32 *  D_2PI_ULS_F32;
	
	SinCorrMtrPosElec_Uls_T_f32 = sinf(CorrMtrPosElec_Rad_T_f32);
	CosCorrMtrPosElec_Uls_T_f32 = cosf(CorrMtrPosElec_Rad_T_f32);
	
	
	
	DervLambdaAlphaDiag_Volt_T_f32 = (SinCorrMtrPosElec_Uls_T_f32 * DervLambdaQax_Volt_T_f32) +(CosCorrMtrPosElec_Uls_T_f32*DervLambdaDax_Volt_T_f32);
	DervLambdaBetaDiag_Volt_T_f32 = (SinCorrMtrPosElec_Uls_T_f32 * DervLambdaDax_Volt_T_f32) -(DervLambdaQax_Volt_T_f32*CosCorrMtrPosElec_Uls_T_f32);
	
	
	PICurrCntrl_DervLambdaQax_Volt_D_f32 = DervLambdaQax_Volt_T_f32;
	PICurrCntrl_DervLambdaDax_Volt_D_f32 = DervLambdaDax_Volt_T_f32;
	

	

	
	Rte_IWrite_PICurrCntrl_Per2_DervLambdaAlphaDiag_Volt_f32(DervLambdaAlphaDiag_Volt_T_f32);
	Rte_IWrite_PICurrCntrl_Per2_DervLambdaBetaDiag_Volt_f32(DervLambdaBetaDiag_Volt_T_f32);
	/* Configurable End of Runnable Checkpoint */
	Rte_Call_PICurrCntrl_Per2_CP1_CheckpointReached();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_AP_PICURRCNTRL_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/



/*****************************************************************************
 *
 *  Function Name:     PICurrCntrlPer1
 *	
 *  Description:       PICurrCntrl
 *
 *  Inputs:            None
 *
 *  Outputs:           None
 *
 *****************************************************************************/
FUNC(void, PICurrCntrl_CODE) PICurrCntrl_Per1(void)
{
VAR(float32, AUTOMATIC) MtrCurrQax_Amp_T_f32;
VAR(float32, AUTOMATIC) MtrCurrDax_Amp_T_f32;
VAR(float32, AUTOMATIC) MtrCurrQaxRef_Amp_T_f32;
VAR(float32, AUTOMATIC) MtrCurrDaxRef_Amp_T_f32;
VAR(float32, AUTOMATIC) PIDaxIntegralGain_Uls_T_f32;
VAR(float32, AUTOMATIC) PIDaxPropotionalGain_Uls_T_f32;
VAR(float32, AUTOMATIC) PIQaxIntegralGain_Uls_T_f32;
VAR(float32, AUTOMATIC) PIQaxPropotionalGain_Uls_T_f32;
VAR(float32, AUTOMATIC) ElecPosDelayComp_Rad_T_f32;
VAR(float32, AUTOMATIC) MtrVoltDaxFF_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltQaxFF_Volt_T_f32;
VAR(float32, AUTOMATIC) Vecu_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrCurrQaxError_Amp_T_f32;
VAR(float32, AUTOMATIC) MtrCurrDaxError_Amp_T_f32;
VAR(float32, AUTOMATIC) MtrCurrQaxProptional_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrCurrDaxProptional_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrCurrQaxIntgTemp1_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrCurrQaxIntg_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltQaxIntAntiWindup_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrCurrDaxIntgTemp1_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltDaxIntAntiWindup_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrCurrDaxIntg_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltQaxFinal_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltQaxFinalLimit_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltDaxFinal_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltSq_VoltSq_T_f32;
VAR(float32, AUTOMATIC) MtrVoltCmd_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrVoltCmdFinal_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrQaxVoltage_Volt_T_f32;
VAR(float32, AUTOMATIC) MtrDaxVoltage_Volt_T_f32;
VAR(float32, AUTOMATIC) ModIdx_Uls_T_f32;
VAR(float32, AUTOMATIC) PhaseAdvance_Rad_T_f32;
VAR(float32, AUTOMATIC) QaxIntAntiWindupTemp1_VoltSq_T_f32;
VAR(float32, AUTOMATIC) DaxIntAntiWindupTemp1_VoltSq_T_f32;
VAR(float32, AUTOMATIC) PhaseAdvanceFinal_Rad_T_f32;
VAR(uint16, AUTOMATIC) PhaseAdvanceFinal_Rev_T_u0p16;
VAR(uint16, AUTOMATIC) AbsModIdx_Uls_T_u3p13;
VAR(uint16, AUTOMATIC) CommOffset_Cnt_T_u16;
VAR(uint16, AUTOMATIC) FwdDataAcessBuffer_Cnt_T_u16;
VAR(float32, AUTOMATIC) MtrCurrQaxFinalRef_Amp_T_f32;
VAR(boolean, AUTOMATIC) ModIdxSrlComSvcDft_Cnt_T_lgc;
VAR(Rte_ModeType_StaMd_Mode, AP_PICurrCntrl_VAR_NOINIT) SysState_Cnt_T_Enum;
VAR(uint32, AUTOMATIC) ModIdx_Uls_T_u16p16;
VAR(float32, AUTOMATIC) MtrVoltDaxFinalLimit_Volt_T_f32;



MtrCntrl_Read_MtrCurrQax_Amp_f32(&MtrCurrQax_Amp_T_f32);
MtrCntrl_Read_MtrCurrDax_Amp_f32(&MtrCurrDax_Amp_T_f32);
MtrCntrl_Read_Vecu_Volt_f32(&Vecu_Volt_T_f32);
MtrCntrl_Read_ModIdxSrlComSvcDft_Cnt_lgc(&ModIdxSrlComSvcDft_Cnt_T_lgc);
MtrCntrl_Read_SysState_Cnt_Enum(&SysState_Cnt_T_Enum);
FwdDataAcessBuffer_Cnt_T_u16 = (FastDataAccessBufIndex_Cnt_M_u16) ;

MtrCurrQaxRef_Amp_T_f32=MtrCurrQaxRef_Amp_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
MtrCurrDaxRef_Amp_T_f32=MtrCurrDaxRef_Amp_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
PIDaxIntegralGain_Uls_T_f32=MtrDaxIntegralGain_Uls_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
PIDaxPropotionalGain_Uls_T_f32=MtrDaxPropotionalGain_Uls_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
PIQaxIntegralGain_Uls_T_f32=MtrQaxIntegralGain_Uls_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
PIQaxPropotionalGain_Uls_T_f32=MtrQaxPropotionalGain_Uls_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
ElecPosDelayComp_Rad_T_f32=MtrPosComputationDelay_Rad_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
MtrVoltDaxFF_Volt_T_f32=MtrVoltDaxFF_Volt_M_f32[FwdDataAcessBuffer_Cnt_T_u16];
MtrVoltQaxFF_Volt_T_f32=MtrVoltQaxFF_Volt_M_f32[FwdDataAcessBuffer_Cnt_T_u16];

/*Range limit Vecu */
Vecu_Volt_T_f32 = Limit_m(Vecu_Volt_T_f32, D_VECUMIN_VOLTS_F32, D_VECUMAX_VOLTS_F32);

/* Error Signal Inputs to PI Control blocks */


PICurrCntrl_MtrCurrQax_Amp_D_f32 =MtrCurrQax_Amp_T_f32;
PICurrCntrl_MtrCurrDax_Amp_D_f32 = MtrCurrDax_Amp_T_f32;
/* I error Calculation */
/* MtrCurrQAXErrorCalc*/
MtrCurrQaxFinalRef_Amp_T_f32 = MtrCurrQaxRef_Amp_T_f32 - (MtrCurrQaxRpl_Amp_M_f32[SlowDataAccessBufIndex_Cnt_M_u16] + MtrCurrQaxCog_Amp_M_f32);
MtrCurrQaxError_Amp_T_f32 = MtrCurrQaxFinalRef_Amp_T_f32-MtrCurrQax_Amp_T_f32;
/*DAX Error Calc*/
MtrCurrDaxError_Amp_T_f32 = MtrCurrDaxRef_Amp_T_f32-MtrCurrDax_Amp_T_f32;

MtrCurrQaxError_Amp_D_f32=MtrCurrQaxError_Amp_T_f32;
MtrCurrDaxError_Amp_D_f32=MtrCurrDaxError_Amp_T_f32;


/****  Propotional Voltage ****/
MtrCurrQaxProptional_Volt_T_f32=MtrCurrQaxError_Amp_T_f32*PIQaxPropotionalGain_Uls_T_f32;
MtrCurrDaxProptional_Volt_T_f32=MtrCurrDaxError_Amp_T_f32*PIDaxPropotionalGain_Uls_T_f32;

MtrVoltQaxProp_Volt_D_f32=MtrCurrQaxProptional_Volt_T_f32;
MtrVoltDaxProp_Volt_D_f32=MtrCurrDaxProptional_Volt_T_f32;

/**** Integral Anti-WindUp Limit Calculation****/

/**** Qax Integral control plus Anti windup Limit****/
QaxIntAntiWindupTemp1_VoltSq_T_f32=((Vecu_Volt_T_f32*Vecu_Volt_T_f32)-(MtrVoltPrevDaxFinal_Volt_M_f32*MtrVoltPrevDaxFinal_Volt_M_f32));
	if(QaxIntAntiWindupTemp1_VoltSq_T_f32<D_ZERO_ULS_F32)
	{
		QaxIntAntiWindupTemp1_VoltSq_T_f32=D_ZERO_ULS_F32;
	}


MtrVoltQaxIntAntiWindup_Volt_T_f32=((__sqrtf(QaxIntAntiWindupTemp1_VoltSq_T_f32))-(Abs_f32_m(MtrVoltQaxFF_Volt_T_f32)));
	
	if(MtrVoltQaxIntAntiWindup_Volt_T_f32<D_ZERO_ULS_F32)
	{
		MtrVoltQaxIntAntiWindup_Volt_T_f32=D_ZERO_ULS_F32;
	}


/****D axis  Control plus Anti windup  Limit ****/
DaxIntAntiWindupTemp1_VoltSq_T_f32=((Vecu_Volt_T_f32*Vecu_Volt_T_f32)-(MtrVoltQaxPrevFinalLimit_Volt_M_f32*MtrVoltQaxPrevFinalLimit_Volt_M_f32));
	if(DaxIntAntiWindupTemp1_VoltSq_T_f32<D_ZERO_ULS_F32)
	{
		DaxIntAntiWindupTemp1_VoltSq_T_f32=D_ZERO_ULS_F32;
	}
	
MtrVoltDaxIntAntiWindup_Volt_T_f32=((__sqrtf(DaxIntAntiWindupTemp1_VoltSq_T_f32))-(Abs_f32_m(MtrVoltDaxFF_Volt_T_f32)));
	
	if(MtrVoltDaxIntAntiWindup_Volt_T_f32<D_ZERO_ULS_F32)
	{
		MtrVoltDaxIntAntiWindup_Volt_T_f32=D_ZERO_ULS_F32;
	}



/* Integrator Voltage */

/**** Q axis Integral  Control  ****/

MtrCurrQaxIntgTemp1_Volt_T_f32=((MtrCurrQaxError_Amp_T_f32*PIQaxIntegralGain_Uls_T_f32*k_PiSamplingTs_Sec_f32)+MtrCurrQaxPrevIntg_Volt_M_f32);
	if(Abs_f32_m(MtrCurrQaxIntgTemp1_Volt_T_f32)>MtrVoltQaxIntAntiWindup_Volt_T_f32)
			{
				MtrCurrQaxIntg_Volt_T_f32=(float32)Sign_f32_m(MtrCurrQaxIntgTemp1_Volt_T_f32)*MtrVoltQaxIntAntiWindup_Volt_T_f32;
			}
			else
			{
				MtrCurrQaxIntg_Volt_T_f32=MtrCurrQaxIntgTemp1_Volt_T_f32;
			}
			


MtrCurrQaxPrevIntg_Volt_M_f32=MtrCurrQaxIntg_Volt_T_f32;
MtrVoltQaxInt_Volt_D_f32=MtrCurrQaxIntg_Volt_T_f32;

/**** D axis Integral  Control ****/

	
MtrCurrDaxIntgTemp1_Volt_T_f32=((MtrCurrDaxError_Amp_T_f32*PIDaxIntegralGain_Uls_T_f32*k_PiSamplingTs_Sec_f32)+MtrCurrDaxPrevIntg_Volt_M_f32);
	if(Abs_f32_m(MtrCurrDaxIntgTemp1_Volt_T_f32)>MtrVoltDaxIntAntiWindup_Volt_T_f32)
			{
				MtrCurrDaxIntg_Volt_T_f32=(float32)Sign_f32_m(MtrCurrDaxIntgTemp1_Volt_T_f32)*MtrVoltDaxIntAntiWindup_Volt_T_f32;
			}
			else
			{
				MtrCurrDaxIntg_Volt_T_f32=MtrCurrDaxIntgTemp1_Volt_T_f32;
			}
			

MtrCurrDaxPrevIntg_Volt_M_f32=MtrCurrDaxIntg_Volt_T_f32;
MtrVoltDaxInt_Volt_D_f32=MtrCurrDaxIntg_Volt_T_f32;


/**** Qax voltage computation and Limit ****/	 
MtrVoltQaxFinal_Volt_T_f32= (MtrCurrQaxProptional_Volt_T_f32+MtrCurrQaxIntg_Volt_T_f32+MtrVoltQaxFF_Volt_T_f32);
MtrVoltQaxFinal_Volt_D_f32=MtrVoltQaxFinal_Volt_T_f32;

 if(Abs_f32_m(MtrVoltQaxFinal_Volt_T_f32)>Vecu_Volt_T_f32)
 {
 	MtrVoltQaxFinalLimit_Volt_T_f32=(float32)Sign_f32_m(MtrVoltQaxFinal_Volt_T_f32)*Vecu_Volt_T_f32;
 }
 else
 {
 	MtrVoltQaxFinalLimit_Volt_T_f32=MtrVoltQaxFinal_Volt_T_f32;
 }
 

MtrVoltQaxPrevFinalLimit_Volt_M_f32=MtrVoltQaxFinalLimit_Volt_T_f32; 
MtrVoltQaxFinalLimit_Volt_D_f32=MtrVoltQaxFinalLimit_Volt_T_f32;
/**** Dax voltage computation and Limit****/
MtrVoltDaxFinal_Volt_T_f32=(MtrCurrDaxProptional_Volt_T_f32+MtrCurrDaxIntg_Volt_T_f32+MtrVoltDaxFF_Volt_T_f32);
MtrVoltDaxFinal_Volt_D_f32=MtrVoltDaxFinal_Volt_T_f32;

 if(Abs_f32_m(MtrVoltDaxFinal_Volt_T_f32)>Vecu_Volt_T_f32)
 {
 	MtrVoltDaxFinalLimit_Volt_T_f32=(float32)Sign_f32_m(MtrVoltDaxFinal_Volt_T_f32)*Vecu_Volt_T_f32;
 }
 else
 {
 	MtrVoltDaxFinalLimit_Volt_T_f32=MtrVoltDaxFinal_Volt_T_f32;
 }
 


MtrVoltPrevDaxFinal_Volt_M_f32=MtrVoltDaxFinalLimit_Volt_T_f32;

/* The output Dax, Qax must be zero if not in operate state*/
if(SysState_Cnt_T_Enum!=RTE_MODE_StaMd_Mode_OPERATE)
{
	MtrCurrDaxPrevIntg_Volt_M_f32=D_ZERO_ULS_F32;
	MtrCurrQaxPrevIntg_Volt_M_f32=D_ZERO_ULS_F32;
}


/**** Final motor output command computation and Limit -Final DQ Voltage ****/

MtrVoltSq_VoltSq_T_f32=((MtrVoltQaxFinalLimit_Volt_T_f32*MtrVoltQaxFinalLimit_Volt_T_f32)+(MtrVoltDaxFinal_Volt_T_f32*MtrVoltDaxFinal_Volt_T_f32));
MtrVoltCmd_Volt_T_f32=__sqrtf(MtrVoltSq_VoltSq_T_f32);
	if(MtrVoltCmd_Volt_T_f32>=Vecu_Volt_T_f32)
	{
		MtrVoltCmdFinal_Volt_T_f32=Vecu_Volt_T_f32;
		MtrQaxVoltage_Volt_T_f32=((MtrVoltQaxFinalLimit_Volt_T_f32*Vecu_Volt_T_f32)/MtrVoltCmd_Volt_T_f32);
		MtrDaxVoltage_Volt_T_f32=((MtrVoltDaxFinal_Volt_T_f32*Vecu_Volt_T_f32)/MtrVoltCmd_Volt_T_f32);
		
	}
	else
	{
		MtrVoltCmdFinal_Volt_T_f32=MtrVoltCmd_Volt_T_f32;
		MtrQaxVoltage_Volt_T_f32=MtrVoltQaxFinalLimit_Volt_T_f32;
		MtrDaxVoltage_Volt_T_f32=MtrVoltDaxFinal_Volt_T_f32;
	}

ModIdx_Uls_T_f32=(MtrVoltCmdFinal_Volt_T_f32/Vecu_Volt_T_f32);
	
/*MtrVolt_Volt used in torque Reasonableness */	



PhaseAdvance_Rad_T_f32=atan2f(MtrVoltDaxFinal_Volt_T_f32,MtrVoltQaxFinalLimit_Volt_T_f32);
/*Correct the Calculated Phase Advance*/
PhaseAdvanceFinal_Rad_T_f32=PhaseAdvance_Rad_T_f32+ElecPosDelayComp_Rad_T_f32;


	if (PhaseAdvanceFinal_Rad_T_f32 < D_ZERO_ULS_F32)
	{
		PhaseAdvanceFinal_Rev_T_u0p16 = (uint16)((PhaseAdvanceFinal_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_REVWITHROUND_ULS_F32);
	}
	else
	{
		PhaseAdvanceFinal_Rev_T_u0p16 = (uint16)((PhaseAdvanceFinal_Rad_T_f32 * D_SCALERADTOCNTS_ULS_F32) + D_ROUND_ULS_F32);
	}

/* Note: The following code is part of implementation of FDD-15D. */ 	
AbsModIdx_Uls_T_u3p13 = FPM_FloatToFixed_m(ModIdx_Uls_T_f32, u3p13_T);

CommOffset_Cnt_T_u16 = IntplVarXY_u16_u16Xu16Y_Cnt(
									 t_CommOffsetTblX_Uls_u3p13,
									 t_CommOffsetTblY_Cnt_u16,
									 TableSize_m(t_CommOffsetTblX_Uls_u3p13), 
									 AbsModIdx_Uls_T_u3p13);
									 

if (ModIdxSrlComSvcDft_Cnt_T_lgc==TRUE)
{
		
	ModIdx_Uls_T_f32 = D_ZERO_ULS_F32;
	MtrCntrl_Read_MtrCurrOffComOffset_Cnt_u16(&CommOffset_Cnt_T_u16);
	
}



MtrVoltDaxIntAntiWindup_Volt_D_f32 = MtrVoltDaxIntAntiWindup_Volt_T_f32;
MtrVoltQaxIntAntiWindup_Volt_D_f32 = MtrVoltQaxIntAntiWindup_Volt_T_f32;


ModIdx_Uls_T_u16p16=FPM_FloatToFixed_m(ModIdx_Uls_T_f32, u16p16_T);


MtrCntrl_Write_MtrCurrQaxFinalRef_Amp_f32(MtrCurrQaxFinalRef_Amp_T_f32);
MtrCntrl_Write_MtrDaxVoltage_Volt_f32(MtrDaxVoltage_Volt_T_f32);
MtrCntrl_Write_MtrQaxVoltage_Volt_f32(MtrQaxVoltage_Volt_T_f32);
MtrCntrl_Write_ModIdx_Uls_u16p16(ModIdx_Uls_T_u16p16);
MtrCntrl_Write_PhaseAdvanceFinal_Rev_u0p16(PhaseAdvanceFinal_Rev_T_u0p16);
MtrCntrl_Write_CommOffset_Cnt_u16(CommOffset_Cnt_T_u16);	
MtrCurrQaxFinalRef_Amp_M_f32[SlowDataAccessBufIndex_Cnt_M_u16]= MtrCurrQaxFinalRef_Amp_T_f32;
MtrVoltDax_Volt_M_f32[SlowDataAccessBufIndex_Cnt_M_u16] = MtrDaxVoltage_Volt_T_f32;
MtrVoltQax_Volt_M_f32[SlowDataAccessBufIndex_Cnt_M_u16] = MtrQaxVoltage_Volt_T_f32;


} 



/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
