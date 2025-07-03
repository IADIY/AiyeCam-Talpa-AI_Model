#------------------------------------------------------------------------------------------------#
#                                                                                                #
#           Copyright (C) 2019 NeuronBasic Co., Ltd. All rights reserved.                        #
#                                                                                                #
#------------------------------------------------------------------------------------------------#
#
# Script compiles the .c specified in the Makefile into flash.nbf
#
# source ../../nbsdk/sourceme.sh
SCRIPT_PATH="$(
    cd "$(dirname "$0")"
    pwd -P
)"
printf "script directory:\t${SCRIPT_PATH}\n"
if [ $# -gt 0 ]; then
    ULOADER_ALIGN_SIZE=$1
else
    ULOADER_ALIGN_SIZE=16384
fi

if [ -d "${SCRIPT_PATH}/build" ]; then
    rm -rf ${SCRIPT_PATH}/build
fi
rm -rf ${SCRIPT_PATH}/uloader.nbf
rm -rf ${ZEUS_SDK_HOME}/tools/fwpacker/flash.nbf
make clean -C ${SCRIPT_PATH}
make -C ${SCRIPT_PATH}
if [ "$?" != "0" ]; then
    printf "MAKE failed\n"
    exit
fi
if [ -d "${ZEUS_SDK_HOME}/build" ]; then
    rm -rf ${ZEUS_SDK_HOME}/build
fi
cp ${ZEUS_SDK_HOME}/tools/fwpacker/fwpacker ./resource/fwpacker
mkdir -p ./resource/data
cp ${SCRIPT_PATH}/build/*.bin ./resource/data/project.bin
if [ "$?" != "0" ]; then
    printf "uloader.elf.bin failed to copy\n"
    exit
fi
cd resource
if [ -f "${SCRIPT_PATH}/project.ini" ]; then
    cp ${SCRIPT_PATH}/project.ini ./
else
    printf "Error:\tMissing project.ini\n"
    exit
fi
./fwpacker project.ini
if [ "$?" != "0" ]; then
    printf "FwPacker failed\n"
    exit
fi

#printf "ULOADER_ALIGN_SIZE:$ULOADER_ALIGN_SIZE\n"
printf "ULOADER_ALIGN_SIZE:$ULOADER_ALIGN_SIZE\n"
truncate --size=$(($ULOADER_ALIGN_SIZE - 16)) ./flash.nbf
echo "ULOADER.NBF...." >>./flash.nbf
cp ./flash.nbf ${SCRIPT_PATH}/uloader.nbf
if [ "$?" != "0" ]; then
    printf "flash.nbf failed to copy\n"
    exit
fi
rm -rf ./fwpacker
rm -rf ./flash.nbf
rm -rf ./project.ini
printf "\n"
sudo chmod 777 -R ${SCRIPT_PATH}/*
