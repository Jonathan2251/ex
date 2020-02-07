#!/bin/bash

# "do compile test in $TEST_CASES_DIR"

# 00028_8bit_dense_size.kdp520.scaled.onnx include not support format 1x8x7x3 input of Flatten, so skip test_cases_v2_compiler/v015_dense
#TEST_CASES_DIR=/home/cschen/work/20200116/test_cases_v2_compiler
#TEST_CASES_DIR=/home/cschen/work/20200116/test_cases_v2_compiler/v015_dense/00028_8bit_dense_size // fail
#TEST_CASES_DIR=/home/cschen/work/20200116/test_cases_v2_compiler/v011_conv/00001_8bit_3x3_base
TEST_CASES_DIR=/home/cschen/work/20200116/test_cases_v2_compiler/v011_conv

DIR_COMPILE1=~/kncompiler/3/Kneron_Compiler/build/bin
COMPILE1=$DIR_COMPILE1/compile
CSIM=~/kncompiler/kdp520_hw_csim/build/npu_sim 

source lib.sh

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
    dir=${json%"/compiler_output_520"*}  # dir
#    echo $dir
    dirs[i]="$dir"
    file=`find $dir -name \*.kdp520.scaled.onnx`
#    echo $file
    files[i]="$file"
done
printf "\n"

echo "${#jsons[@]}"
echo "${#files[@]}"

rm -rf dir1
mkdir dir1
for i in "${!jsons[@]}"
do
    echo "${jsons[i]}"
    echo "${files[i]}"
    echo "${dirs[i]}"
    rm -rf dir1/*

    pushd dir1
    Compile1 ${files[i]} ${jsons[i]}
    if [ $ret != 0 ]; then
        exit 1;
    fi
    popd

    pushd dir1
    Csim "./command.bin" "./weight.bin" "${dirs[i]}/results/test_input.txt/mode_520/layer_0000_input_1_o0_fp.bin" "./setup.bin"
    if [ $ret != 0 ]; then
        exit 1;
    fi
    popd

done
printf "\n"

exit $ret

