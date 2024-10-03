#!/usr/bin/env bash

cmake -S . -B build -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++
cmake --build build --parallel $(nproc)