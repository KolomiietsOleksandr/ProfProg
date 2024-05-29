#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 source_file -o output_binary"
    exit 1
fi

COMPILER="clang++"
FLAGS="-Wall -Wextra -Wpedantic -Werror -std=c++23"

$COMPILER $FLAGS "$@"
