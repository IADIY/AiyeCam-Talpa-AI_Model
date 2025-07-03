#------------------------------------------------------------------------------------------------#
#                                                                                                #
#           Copyright (C) 2024 IADIY., Ltd. All rights reserved.                        #
#                                                                                                #
#------------------------------------------------------------------------------------------------#
#
# Script compiles the .c specified in the Makefile into flash.nbf
#

source ../nbsdk/nbsdk/sourceme.sh

SCRIPT_PATH="$(
    cd "$(dirname "$0")"
    pwd -P
)"
printf "script directory:\t${SCRIPT_PATH}\n"
if [ $# -gt 0 ]; then
    BRD=$1
else
    BRD=EVALBOARD
fi

WITH_ULOADER=0
eval $(grep -m2 "WITH_ULOADER" ${SCRIPT_PATH}/Token.h | tail -n1 | awk {'printf("WITH_ULOADER=%d",$3)'} | sed s/[[:space:]]//g)

echo "with_uloader:${WITH_ULOADER}"

if [ "${WITH_ULOADER}" = "0" ]; then
    export ULOADER_ALIGN_SIZE=0 # if not using uloader.nbf, set to 0
else
    export ULOADER_ALIGN_SIZE=16384 # if using uloader.nbf, set to 16384
fi

if [ -d "${SCRIPT_PATH}/build" ]; then
    rm -rf ${SCRIPT_PATH}/build
fi
rm -rf ${SCRIPT_PATH}/flash.nbf
rm -rf ${ZEUS_SDK_HOME}/tools/fwpacker/flash.nbf
make clean -C ${SCRIPT_PATH}
make BOARD=$BRD -C ${SCRIPT_PATH}
if [ -d "${SCRIPT_PATH}/pmu_fw/" ]; then
    make clean -C pmu_fw
    make -C pmu_fw
fi
if [ "$?" != "0" ]; then
    printf "MAKE failed\n"
    exit
fi

ULOADER=${SCRIPT_PATH}/resource/data/uloader.nbf
if [ -d "${SCRIPT_PATH}/uloader_fw/" ]; then
    printf "ULOADER_ALIGN_SIZE=$ULOADER_ALIGN_SIZE\n"
    if [[ $ULOADER_ALIGN_SIZE -gt 0 ]]; then
        make clean -C uloader_fw
        make -C uloader_fw
        cd uloader_fw
        ./createNBF.sh $ULOADER_ALIGN_SIZE
        if [ "$?" != "0" ]; then
            printf "createNBF uloader.nbf failed\n"
            exit
        fi
        cd ..
        cp ${SCRIPT_PATH}/uloader_fw/uloader.nbf ./resource/data/
    else
        rm -rf $ULOADER
        make clean -C uloader_fw
    fi
fi
if [ "$?" != "0" ]; then
    printf "MAKE failed\n"
    exit
fi

if [ -d "${ZEUS_SDK_HOME}/build" ]; then
    rm -rf ${ZEUS_SDK_HOME}/build
fi
cp ${ZEUS_SDK_HOME}/tools/fwpacker/fwpacker ./resource/fwpacker
cp ${SCRIPT_PATH}/build/*.elf.bin ./resource/data/project.bin
if [ "$?" != "0" ]; then
    printf "zeus_demo.elf.bin failed to copy\n"
    exit
fi
if [ -d "${SCRIPT_PATH}/pmu_fw/" ]; then
    cp ${SCRIPT_PATH}/pmu_fw/build/pmu.bin ./resource/data/
fi
if [ "$?" != "0" ]; then
    printf "pmu.bin failed to copy\n"
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

if [ -f "${ULOADER}" ]; then
    TMP=./loader.nbf
    printf "\nconcate uloader + flash.nbf to flash_uloader.nbf ... "
    cp $ULOADER $TMP
    cat $TMP ./flash.nbf >./flash_uloader.nbf
    cp ./flash_uloader.nbf ./flash.nbf
    printf "done\n"
    rm -rf ./flash_uloader.nbf
    rm -rf $TMP
fi

if grep -q "PROJECT_TAG" ${SCRIPT_PATH}/Token.h; then
    PROJECT_MAJOR_VERSION=0 PROJECT_MINOR_VERSION=0 PROJECT_TEST_VERSION=0
    eval $(grep -m2 "PROJECT_TAG" ${SCRIPT_PATH}/Token.h | tail -n1 | awk {'printf("PROJECT_TAG=%s",$3)'} | sed s/[[:space:]]//g)
    eval $(grep -m2 "PROJECT_MAJOR_VERSION" ${SCRIPT_PATH}/Token.h | tail -n1 | awk {'printf("PROJECT_MAJOR_VERSION=%s",$3)'} | sed s/[[:space:]]//g)
    eval $(grep -m2 "PROJECT_MINOR_VERSION" ${SCRIPT_PATH}/Token.h | tail -n1 | awk {'printf("PROJECT_MINOR_VERSION=%s",$3)'} | sed s/[[:space:]]//g)
    eval $(grep -m2 "PROJECT_TEST_VERSION" ${SCRIPT_PATH}/Token.h | tail -n1 | awk {'printf("PROJECT_TEST_VERSION=%s",$3)'} | sed s/[[:space:]]//g)

    #OUTPUT_FILENAME=${PROJECT_TAG}_v${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}${PROJECT_TEST_VERSION}
    OUTPUT_FILENAME=${PROJECT_TAG}
    
    eval $(grep -m2 "AEG_AC_POWER_FREQ" ${SCRIPT_PATH}/Token.h | tail -n1 | awk {'printf("AEG_AC_POWER_FREQ=%s",$3)'} | sed s/[[:space:]]//g)
    
    printf "%s\n" "$AEG_AC_POWER_FREQ"
    
    if [[ "$AEG_AC_POWER_FREQ" == "MACR_AEG_AC_FREQ_CFG_60HZ" ]]; then
        OUTPUT_FILENAME=${OUTPUT_FILENAME}_60Hz
    else
        OUTPUT_FILENAME=${OUTPUT_FILENAME}_50Hz
    fi

    OUTPUT_FILENAME=${OUTPUT_FILENAME}.nbf

    cp ./flash.nbf $SCRIPT_PATH/$OUTPUT_FILENAME
    printf "\nBuild success!\n"
    printf "Firmware image : $OUTPUT_FILENAME\n"
    printf "Image path : ${SCRIPT_PATH}/$OUTPUT_FILENAME"
else
    cp ./flash.nbf ${SCRIPT_PATH}/
    printf "\nBuild success!\n"
    printf "Firmware image : flash.nbf\n"
    printf "Image path : ${SCRIPT_PATH}/flash.nbf"
fi

if [ "$?" != "0" ]; then
    printf "flash.nbf failed to copy\n"
    exit
fi
rm -rf ./fwpacker
rm -rf ./flash.nbf
rm -rf ./project.ini
printf "\n"
sudo chmod 777 -R ${SCRIPT_PATH}/*
# ls ${SCRIPT_PATH} -oht | grep --color=always -z flash.nbf


###modified###
WINDOWS_PATH="/mnt/c/"
printf "\n"
cd ..
cp "$OUTPUT_FILENAME"  $WINDOWS_PATH
if [ "$?" != "0" ]; then
    printf "Copied file to ${WINDOWS_PATH} failed\n"
    exit
else
    printf "Copied file to ${WINDOWS_PATH} success\n"
    current_date_time=$(date)
    echo "Done at: $current_date_time"
fi
###modified###
