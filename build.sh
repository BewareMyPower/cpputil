#!/bin/bash
SHELL_DIR=$(cd $(dirname $0) && pwd)
INSTALL_DIR=$SHELL_DIR
cd $SHELL_DIR

if [ $# -eq 1 ]; then
    case $1 in
        "clean")
            echo "rm -rf $SHELL_DIR/build"
            rm -rf $SHELL_DIR/build
            exit 0
            ;;
        "uninstall")
            echo "rm -rf $INSTALL_DIR/bin $INSTALL_DIR/lib $INSTALL_DIR/include"
            rm -rf $INSTALL_DIR/bin $INSTALL_DIR/lib $INSTALL_DIR/include
            exit 0
            ;;
        *)
            echo "Invalid command: "$1
            exit 1
            ;;
    esac
fi

mkdir -p build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR && make && make install
cd ..
