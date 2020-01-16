#!/bin/bash

# problem: how to split string with eol into array by command, IFS=... ?

my_string=`find /usr/bin/ -name \*`
echo "$my_string"

my_array=($(echo $my_string | tr " " "\n"))
IFS='\n' read -ra my_array2 <<< "$my_string"
IFS=' ' read -ra my_array3 <<< "$my_string"

echo "${#my_array[@]}"
echo "${#my_array2[@]}"
echo "${#my_array3[@]}"
