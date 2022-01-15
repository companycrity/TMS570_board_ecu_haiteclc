###############################################################################
# File Name  : <ASRMODULENAME>_rules.mak                                      #
# Description: Autosar makefile Template                                      #
#              This makefile is a template to implement the common            #
#              features of each project.                                      #
#              It is included by the Global.Makefile.target.make.$(Version)   #
#              and is supported from version 3.24 .                           #
#                                                                             #
# This Template is based on AUTOSAR_BSW_MakefileInterface.doc version 0.4     #
#                                                                             #
#-----------------------------------------------------------------------------#
#               C O P Y R I G H T                                             #
#-----------------------------------------------------------------------------#
# Copyright (c) 2007 by Vector Informatik GmbH.  All rights reserved.         #
#                                                                             #
#-----------------------------------------------------------------------------#
#               A U T H O R   I D E N T I T Y                                 #
#-----------------------------------------------------------------------------#
# Initials     Name                      Company                              #
# --------     ---------------------     -------------------------------------#
# Aba          Andreas Barac             Vector Informatik GmbH               #
#-----------------------------------------------------------------------------#
#               R E V I S I O N   H I S T O R Y                               #
#-----------------------------------------------------------------------------#
# Date         Version  Sign Description                                      #
# ----------   -------  ---- -------------------------------------------------#
# 2007/06/13   1.00     Aba  Initial Version of Template (1.0)                #
#-----------------------------------------------------------------------------#
# TemplateVersion = 1.0                                                       #
# MAKEFILE        = 0.1                                                       #
###############################################################################

ifeq ($(XCP_USE_XCPONCAN),)
  $(error Error: Xcp_check.mak: Please set XCP_USE_XCPONCAN in Xcp_cfg.mak)
endif

ifeq ($(XCP_USE_XCPONFR),)
  $(error Error: Xcp_check.mak: Please set XCP_USE_XCPONFR in Xcp_cfg.mak)
endif

###############################################################
# REGISTRY
#

#e.g.: LIBRARIES_TO_BUILD      +=    <MSN>
#e.g.: <MSN>_FILES = <MSN>\<MSN>.c
LIBRARIES_TO_BUILD      += Xcp
Xcp_FILES                = Xcp\XcpProf.c

# e.g.: CC_FILES_TO_BUILD       += <MSN>\<MSN>.c <MSN>\<MSN>_Irq.c
CC_FILES_TO_BUILD       += Xcp\XcpProf.c
ifeq ($(XCP_USE_XCPONCAN),1)
  CC_FILES_TO_BUILD     += CanXcp\CanXcp.c
  CC_INCLUDE_PATH       += CanXcp
  LIBRARIES_TO_BUILD    += CanXcp
  CanXcp_FILES           = CanXcp\CanXcp.c
endif
ifeq ($(XCP_USE_XCPONFR),1)
  CC_FILES_TO_BUILD     += FrXcp\FrXcp.c
  CC_INCLUDE_PATH       += FrXcp
  LIBRARIES_TO_BUILD    += FrXcp
  FrXcp_FILES           = FrXcp\FrXcp.c
endif

CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

#e.g.:
#ifeq ($(<MSN>_USE_<FEATURE>),1)
#CC_FILES_TO_BUILD       +=
#endif

#LIBRARIES_LINK_ONLY     += (not yet supported)
#OBJECTS_LINK_ONLY       += (not yet supported)

#-------------------------------------------------------------------------------------------------
#only define new dirs, OBJ, LIB, LOG were created automaticly
#-------------------------------------------------------------------------------------------------
DIRECTORIES_TO_CREATE   += 

#DEPEND_GCC_OPTS         += (not yet supported)

# e.g.:  GENERATED_SOURCE_FILES += $(GENDATA_DIR)\drv_par.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\xcp_par.c

ifeq ($(XCP_USE_XCPONCAN),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\CanXcp_Lcfg.c
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\CanXcp_PBcfg.c
endif
ifeq ($(XCP_USE_XCPONFR),1)
GENERATED_SOURCE_FILES  += $(GENDATA_DIR)\frxcp_par.c
endif


#e.g.: COMMON_SOURCE_FILES     += $(GENDATA_DIR)\v_par.c
COMMON_SOURCE_FILES     += 

#-------------------------------------------------------------------------------------------------
# <project>.dep & <projekt>.lnk & <project>.bin and.....
# all in err\ & obj\ & lst\ & lib\ & log\ will be deleted by clean-rule automaticly
# so in this clean-rule it is only necessary to define additional files which
# were not delete automaticly.
# e.g.: $(<PATH>)\can_test.c
#-------------------------------------------------------------------------------------------------
MAKE_CLEAN_RULES        +=
#MAKE_GENERATE_RULES     +=
#MAKE_COMPILER_RULES     +=
#MAKE_DEBUG_RULES        +=
#MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES          +=


###############################################################
# REQUIRED   (defined in BaseMake (global.Makefile.target.make...))
#
# SSC_ROOT		(required)
# PROJECT_ROOT	(required)
#
# LIB_OUTPUT_PATH	(optional)
# OBJ_OUTPUT_PATH	(optional)
#
# OBJ_FILE_SUFFIX	
# LIB_FILE_SUFFIX
#
###############################################################


###############################################################
# PROVIDE   this Section can be used to define own additional rules
#
# In vendorx_can_cfg.mak:
# Please configure the project file:
#CAN_CONFIG_FILE = $(PROJECT_ROOT)\source\network\can\my_can_config.cfg

#In vendorx_can_config :
#generate_can_config:
#$(SSC_ROOT)\core\com\can\tools\canconfiggen.exe -o $(CAN_CONFIG_FILE)


###############################################################
# SPECIFIC
#
# There are no rules defined for the Specific part of the 
# Rules-Makefile. Each author is free to create temporary 
# variables or to use other resources of GNU-MAKE
#
###############################################################


