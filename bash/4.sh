#!/bin/bash

# "do compile test in $TEST_CASES_DIR"

#TEST_CASES_DIR=/home/cschen/work/20200109/test_cases_v2_compiler/
TEST_CASES_DIR=/home/cschen/work/20200109/test_cases_v2_compiler/v011_conv/00001_8bit_3x3_base/

DIR_COMPILE1=~/kncompiler/3/Kneron_Compiler/build/bin
COMPILE1=$DIR_COMPILE1/compile
CSIM=~/kncompiler/kdp520_hw_csim/build/npu_sim 

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

ret=0

printf "\n\n"
echo "****************************************"
echo "** do compile test in $TEST_CASES_DIR **"
echo "****************************************"
string=`find $TEST_CASES_DIR -name compiler.config.kdp520.json`
array=($(echo $string | tr " " "\n"))
echo "${#array[@]}"

for i in "${!array[@]}"
do
#    echo "$i"   # $i = 0,1,2,...
    json=${array[i]}    # json: a compiler.config.kdp520.json with absolut directory
#    echo "$json"
    jsons[i]="$json"
    dir=${json%"compiler_output_520"*}  # dir
#    echo $dir
    dirs[i]="$dir"
    file=`find $dir -name \*.kdp520.scaled.onnx`
#    echo $file
    files[i]="$file"
done
printf "\n"

echo "${#jsons[@]}"
echo "${#files[@]}"

for i in "${!jsons[@]}"
do
    echo "${jsons[i]}"
    echo "${files[i]}"
    echo "${dirs[i]}"
    Compile1 "${files[i]}" "${jsons[i]}"
    if [ $ret != 0 ]; then
        exit 1;
    fi
    Csim "./command.bin" "./weight.bin" "${dirs[i]}/results/test_input.txt/mode_520/layer_0000_input_1_o0_fp.bin" "./setup.bin"
    if [ $ret != 0 ]; then
        exit 1;
    fi
done
printf "\n"

exit $ret

