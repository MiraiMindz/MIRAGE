#!/usr/bin/env bash

sh "$(pwd)/scripts/clean.sh"
sh "$(pwd)/scripts/build.sh"
sh "$(pwd)/scripts/sanatizecheck.sh"

LD_PRELOAD=/usr/lib/libasan.so ./build/MIRAGE