#!/bin/bash

# "do compile test in $TEST_CASES_DIR"

#TEST_CASES_DIR=/home/cschen/work/20200109/test_cases_v2_compiler/
TEST_CASES_DIR=/home/cschen/work/20200109/test_cases_v2_compiler/v011_conv/00001_8bit_3x3_base/

DIR_COMPILE1=~/kncompiler/3/Kneron_Compiler/build/bin
DIR_COMPILE2=~/kncompiler/1/kneron_piano/build/piano
COMPILE1=$DIR_COMPILE1/compile
COMPILE2=$DIR_COMPILE2/piano
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

rm -rf dir1 dir2
mkdir dir1 dir2
for i in "${!jsons[@]}"
do
    echo "${jsons[i]}"
    echo "${files[i]}"
    echo "${dirs[i]}"
    rm -rf dir1/* dir2/*

    pushd dir1
    Compile1 ${files[i]} ${jsons[i]}
    if [ $ret != 0 ]; then
        exit 1;
    fi
    popd

    loglevel=1
    logfile=log.txt
    target=kdp520
    pushd dir2
    Compile2 ${files[i]} ${jsons[i]} $loglevel $logfile $target
    popd

    compile_out_files="command.bin command.txt setup.bin size_check weight.bin"
    compare_out_files $compile_out_files

    pushd dir1
    Csim "./command.bin" "./weight.bin" "${dirs[i]}/results/test_input.txt/mode_520/layer_0000_input_1_o0_fp.bin" "./setup.bin"
    if [ $ret != 0 ]; then
        exit 1;
    fi
    popd

    pushd dir2
    Csim "./command.bin" "./weight.bin" "${dirs[i]}/results/test_input.txt/mode_520/layer_0000_input_1_o0_fp.bin" "./setup.bin"
    if [ $ret != 0 ]; then
        exit 1;
    fi
    popd
    
    csim_out_files="Lastlayer_final_output.bin Lastlayer_final_output_matrix.txt Lastlayer_final_output.txt node_0000_final_output.bin node_0000_final_output_matrix.txt node_0000_final_output.txt radix_scale_info.txt"
    compare_out_files $csim_out_files

done
printf "\n"

exit $ret

