/*****************************************************************************
* Copyright 2012 Nexteer Automotive, All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : Ap_MtrCntrl_Cfg.h
* Module Description: Motor control Complex Driver configuration
* Product           : Gen II Plus - EA3.0
* Author            : Selva Sengottaiyan
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sat Mar 23 13:00:00 2013
* %version:          2 %
* %derived_by:       nzt9hv %
* %date_modified:    Wed Jun  5 11:31:23 2013 %
*---------------------------------------------------------------------------*/


#ifndef MTRCNTRL_CFG_H
#define MTRCNTRL_CFG_H






#define 	MtrCntrl_Read_MtrCurrQax_Amp_f32(ptr)    			*(ptr) = 0.0F
#define 	MtrCntrl_Read_MtrCurrDax_Amp_f32(ptr)    			*(ptr) = 0.0F
#define 	MtrCntrl_Read_Vecu_Volt_f32(ptr)    				*(ptr) = 0.0F 
#define 	MtrCntrl_Read_ModIdxSrlComSvcDft_Cnt_lgc(ptr)    	*(ptr) =  FALSE
#define 	MtrCntrl_Read_SysState_Cnt_Enum(ptr)    			*(ptr) = 0U 
#define 	MtrCntrl_Read_MtrCurrOffComOffset_Cnt_u16(ptr)   	*(ptr) = 0U 
#define 	MtrCntrl_Read_MtrElecPol_Cnt_s8(ptr)    			*(ptr) =  0
#define 	MtrCntrl_Read_MtrPosElec_Rev_u0p16(ptr)   			*(ptr) =   0U


#define MtrCntrl_Write_MtrCurrQaxFinalRef_Amp_f32(val)          val = (val)
#define MtrCntrl_Write_MtrDaxVoltage_Volt_f32(val)               val = (val)
#define MtrCntrl_Write_MtrQaxVoltage_Volt_f32(val)              val = (val)
#define MtrCntrl_Write_ModIdx_Uls_u16p16(val)                     val = (val)
#define MtrCntrl_Write_PhaseAdvanceFinal_Rev_u0p16(val)   		 val = (val)
															
#define MtrCntrl_Write_CommOffset_Cnt_u16(val)	                val = (val)

#endif
