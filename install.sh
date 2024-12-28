#!/bin/bash

LDPATH=include
SRC_DIR=src
TARGET_DIR=bin

for h_path in $LDPATH/*.h; do
    lib_name=$(basename $h_path .h)
    so_path="$TARGET_DIR/lib$lib_name.so"

    [ ! -f $so_path ] && make

    if [ -f $so_path ]; then
        h_name=$(basename $h_path)
        so_name=$(basename $so_path)

        t_h_path=/usr/include/guilib
        t_so_path=/usr/lib

        [ ! -d $h_path ] && sudo mkdir $t_h_path

        sudo ln -sf $PWD/$h_path $t_h_path/$h_name
        sudo ln -sf $PWD/$so_path $t_so_path/$so_name
    fi
done
