
PROG	= Project

APP_SRC	= Main.c User_Config.c

HOST_PATH:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
#$(info HOST_PATH=$(HOST_PATH))

LIBS_HOST = $(HOST_PATH)/libs/lib_Basic.a \
            $(HOST_PATH)/libs/lib_sensor_aeg.a \
            $(HOST_PATH)/libs/lib_fae.a

include $(ZEUS_SDK_HOME)/tools/rules/application.mk

INCLUDES += -I. \
	-I$(HOST_PATH)/include
	
