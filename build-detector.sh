#!/bin/bash

compiler_c=clang-mp-3.9
compiler_cxx=clang++-mp-3.9

if test $# -gt 0
then
    if test $1 = "gnu"
    then
        compiler_c=gcc
        compiler_cxx=g++
    fi
fi

cmake ../detector                                  \
      -DCMAKE_INSTALL_PREFIX=../detector-install   \
      -DCMAKE_CXX_COMPILER=${compiler_cxx}         \
      -DCMAKE_C_COMPILER=${compiler_c}             \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=true
