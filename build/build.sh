#!/usr/bin/env bash

echo "Change dir to /home/whoami"
cd 

echo "Cloning LLVM repo .."
git clone https://github.com/llvm/llvm-project.git

echo "Building LLVM, clang and clang-tools-extra. It may take some time (._.) .."
cd ~/llvm-project 
mkdir build && cd build  

cmake -DCMAKE_BUILD_TYPE=Release \
      -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
      -DLLVM_TARGETS_TO_BUILD=X86 \
      -G "Ninja" ../llvm

ninja

echo "Running the testsuite.."
ninja check-all

echo 'All set!'
