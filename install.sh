#!/bin/bash

BUILD_DIR=$PWD/bin
INCLUDE_DIR=$PWD/include
PLAT=$(uname -s)

usage() {
    echo -e "Usage: $0 [OPTIONS]\n"\
    "Options:\n"\
    "\t-h, --help           Show this help message\n"\
    "\t-R, --rebuild        Force make rebuild\n"\
    "\t-l, --link           Create a symbolic link (default is to copy)"
    exit 1
}

command="cp"
rebuild=false

while [ $# -gt 0 ]; do
    case $1 in
        -h | --help)
            usage
            exit 0
            ;;
        -R | --rebuild)
            rebuild=true
            ;;
        -l | --link)
            command="ln -sf"
            ;;
        *)
            echo "Invalid option: $1" >&2
            usage
            exit 1
            ;;
    esac
    shift
done

if [[ ! -d "$BUILD_DIR" || $rebuild == true ]]; then
    make -B || exit 1
fi

t_h_path=$([[ $PLAT = "Darwin" ]] && echo "/usr/local/include/guilib" || echo "/usr/include/guilib")
t_so_path=$([[ $PLAT = "Darwin" ]] && echo "/usr/local/lib" || echo "/usr/lib")

[[ ! -d $t_h_path ]] && sudo mkdir -p $t_h_path
[[ ! -d $t_so_path ]] && sudo mkdir -p $t_so_path


full_command="sudo $command {} $t_h_path"
find $INCLUDE_DIR -type f ! -name "utils.h" -exec echo "+ $full_command" \; -exec $full_command \;



full_command="sudo $command {} $t_so_path"
find $BUILD_DIR -type f -exec echo "+ $full_command" \; -exec $full_command \;
