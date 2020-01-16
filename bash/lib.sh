#!/bin/bash

####################
##    FUNCTION    ##
####################

abort_if_fail()
{
    if [ $? == 0 ]; then
        echo "status: $?"
    else
        # ! attention: echo status makes $? -> 0
        echo "status: $?"
        exit 1;
    fi  
}

compare_out_files()
{
    local files=$1

    for file in $files
    do  
        echo diff dir1/$file dir2/$file
        diff dir1/$file dir2/$file
        abort_if_fail;
    done
}

function Compile1()
{
    local model=$1
    local cfg=$2
    local log=compile.${f}.log
    local compile_ret=0

    printf "=> Compiling %-60s " $f

    local str=$(date +"%s.%N")
    echo "$COMPILE1 $model $cfg debug > $log"
    $COMPILE1 $model $cfg debug > $log
    compile_ret=$?
    local end=$(date +"%s.%N")
    local time=$(echo "$end $str" | awk '{ printf "%.2f", $1 - $2 }')

    if [ $compile_ret = 0 ]; then
        printf "SUCCESS [${time} sec]\n"
    else
        ret=$compile_ret
        printf "FAILED\n"
        egrep "\[error\]" $log
        printf "\n\n"
    fi
}

function Compile2()
{
    rm -rf log
    mkdir log
    local model=$1
    local cfg=$2
    local loglevel=$3
    local logfile=$4
    local target=$5
    local log=compile.${f}.log
    local compile_ret=0

    printf "=> Compiling %-60s " $f

    local str=$(date +"%s.%N")
    echo "$COMPILE2 $model $cfg $loglevel $logfile $target > $log"
    $COMPILE2 $model $cfg $loglevel $logfile $target > $log
    compile_ret=$?
    abort_if_fail;
    local end=$(date +"%s.%N")
    local time=$(echo "$end $str" | awk '{ printf "%.2f", $1 - $2 }')

    if [ $compile_ret = 0 ]; then
        printf "SUCCESS [${time} sec]\n"
    else
        ret=$compile_ret
        printf "FAILED\n"
        egrep "\[error\]" $log
        printf "\n\n"
    fi

}

function Csim()
{
    local command_bin=$1
    local weight_bin=$2
    local input_bin=$3
    local setup_bin=$4
    local compile_ret=0

    printf "=> Csim %-60s " $f

    local str=$(date +"%s.%N")
    echo "$CSIM --cmd $command_bin --weight $weight_bin --input $input_bin --setup $setup_bin"
    $CSIM --cmd $command_bin --weight $weight_bin --input $input_bin --setup $setup_bin
    csim_ret=$?
    local end=$(date +"%s.%N")
    local time=$(echo "$end $str" | awk '{ printf "%.2f", $1 - $2 }')

    if [ $csim_ret = 0 ]; then
        printf "SUCCESS [${time} sec]\n"
    else
        ret=$csim_ret
        printf "FAILED\n"
        printf "\n\n"
    fi
}

