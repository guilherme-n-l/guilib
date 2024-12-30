#!/bin/bash

LDPATH=include
SRC_DIR=src
TARGET_DIR=bin


usage() {
    echo -e "Usage: $0 [OPTIONS]\n"\
    "Options:\n"\
    "\t-h, --help           Show this help message\n"\
    "\t-l, --link           Create a symbolic link (default is to copy)"
    exit 1
}

while [ $# -gt 0 ]; do
    case $1 in
        -h | --help)
            usage
            exit 0
            ;;
        -l | --link)
            link=1
            ;;
        *)
            echo "Invalid option: $1" >&2
            usage
            exit 1
            ;;
    esac
    shift
done

for h_path in $LDPATH/*.h; do
    lib_name=$(basename $h_path .h)
    so_path="$TARGET_DIR/lib$lib_name.so"

    [ ! -f $so_path ] && make -B

    if [ -f $so_path ]; then
        h_name=$(basename $h_path)
        so_name=$(basename $so_path)

        t_h_path=/usr/include/guilib
        t_so_path=/usr/lib

        [ ! -d $t_h_path ] && sudo mkdir $t_h_path

        if [ ! link ]; then
            sudo cp $PWD/$h_path $t_h_path/$h_name
            sudo cp $PWD/$so_path $t_so_path/$so_name
        else
            sudo ln -sf $PWD/$h_path $t_h_path/$h_name
            sudo ln -sf $PWD/$so_path $t_so_path/$so_name
        fi
    fi
done
