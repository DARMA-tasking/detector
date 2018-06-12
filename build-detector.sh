#!/bin/bash

compiler_c=clang-mp-3.9
compiler_cxx=clang++-mp-3.9

if test $# -gt 0
then
    build_mode=$1
else
    build_mode=debug
fi

if test $# -gt 1
then
    if test $2 = "gnu"
    then
        compiler_c=gcc
        compiler_cxx=g++
    fi
fi

cmake ../detector                                  \
      -DCMAKE_BUILD_TYPE=${build_mode}             \
      -DCMAKE_INSTALL_PREFIX=../detector-install   \
      -DCMAKE_CXX_COMPILER=${compiler_cxx}         \
      -DCMAKE_C_COMPILER=${compiler_c}             \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=true
