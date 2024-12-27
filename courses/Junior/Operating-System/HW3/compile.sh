#!/bin/bash

# 定義變數
CC=gcc
CFLAGS="-Iinclude -lpthread"
SRC="main.c lib/buffer.c"
TARGET="s411440521HW3"

# 功能選項
if [ "$1" == "clean" ]; then
    echo "Cleaning up..."
    rm -f $TARGET
    echo "Cleaned."
    exit 0
fi

# 編譯
echo "Compiling $TARGET..."
$CC -o $TARGET $SRC $CFLAGS

if [ $? -eq 0 ]; then
    echo "Compilation successful. Run ./$TARGET <args>"
else
    echo "Compilation failed."
fi
