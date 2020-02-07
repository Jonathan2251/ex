#!/bin/bash

# bash how-to-pass-an-array-as-function-argument
# https://askubuntu.com/questions/674333/how-to-pass-an-array-as-function-argument

function copyFiles() {
  arr=("$@")
  for i in "${arr[@]}";
  do
    echo "$i"
  done
}

array=("one" "two" "three")

copyFiles "${array[@]}"
