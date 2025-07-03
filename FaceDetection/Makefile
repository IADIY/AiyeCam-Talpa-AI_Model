#------------------------------------------------------------------------------------------------#
#                                                                                                #
#           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        #
#                                                                                                #
#------------------------------------------------------------------------------------------------#

PROG	= nb1001_demo

APP_SRC	= Main.c User_Config.c
		
HOST_PATH:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

LIBS_HOST = $(HOST_PATH)/libs/lib_Basic.a \
			$(HOST_PATH)/libs/lib_fae.a \
            $(HOST_PATH)/libs/lib_sensor_aeg.a

CFLAGS += -DULOADER_ALIGN_SIZE=$(ULOADER_ALIGN_SIZE)
include $(ZEUS_SDK_HOME)/tools/rules/application.mk

INCLUDES += -I. \
	-I$(HOST_PATH)/include
	
