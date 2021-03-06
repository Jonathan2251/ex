#-------------------------------------------------------------------------------
# Shows how to build the samples vs. a released binary download of LLVM & Clang.
#
# Assumes the binary release was downloaded from http://llvm.org/releases/
# and untarred in some directory. The actual script code here uses a location
# I use on my machine, but that can be replaced by anything you fancy in the
# BINARY_DIR_PATH variable.
#
# Eli Bendersky (eliben@gmail.com)
# This code is in the public domain
#-------------------------------------------------------------------------------

#!/bin/bash

set -eu
set -x

BINARY_DIR_PATH=${BINARY_DIR_PATH:-$HOME/llvm/10.0.0/release/build-cb}
echo "BINARY_DIR_PATH: " ${BINARY_DIR_PATH}

make -j8 \
  CXX=$BINARY_DIR_PATH/bin/clang++ \
  LLVM_SRC_PATH=$HOME/llvm/10.0.0/release/src \
  LLVM_BUILD_PATH=$BINARY_DIR_PATH \
  LLVM_BIN_PATH=$BINARY_DIR_PATH/bin

make LLVM_BIN_PATH=$BINARY_DIR_PATH/bin test
