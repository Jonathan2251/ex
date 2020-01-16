#!/bin/bash
#
# Script to split a string based on the delimiter
# ref. https://linuxhandbook.com/bash-split-string/

my_string="Ubuntu;Linux Mint;Debian;Arch;Fedora"

# The problem with this approach is that the array element are divided on ‘space delimiter’. Because of that, elements like ‘Linux Mint’ will be treated as two words.
my_array=($(echo $my_string | tr ";" "\n"))

echo "size of my_array: ${#my_array[@]}" # 6 
#echo "${#array[@]}"

#Print the split string
for i in "${my_array[@]}"
do
    echo $i
done

IFS=';' read -ra my_array2 <<< "$my_string"
echo "size of my_array2: ${#my_array2[@]}"

