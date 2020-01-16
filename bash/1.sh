#!/bin/bash

# https://landoflinux.com/linux_bash_scripting_substring_tests.html
test="land.of.linux"
echo "Stripping the shortest match from front:"
echo ${test#*.}

echo "Stripping the shortest match from back:"
echo ${test%.*}



