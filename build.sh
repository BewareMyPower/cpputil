#!/bin/bash
set -o errexit

function usage() {
    printf "\
Usage:
  %s [OPTIONS]

Options:
  -i, --install DIR   install headers, libraries and binaries to DIR, following
                      subdirectories will be created:
                        include/  Headers (*.h)
                        lib/      Libraries (*.a)
                        bin/      Unit test binaries if --with-tests was specified
                      (default: /usr/local)
  -u, --uninstall DIR remove headers, libraries and binaries under DIR
                      other options will be ignored if it's specified
  --with-tests        build unit test binaries
  -h, --help          display this help and exit\n" \
      $1
}

function check_dir() {
    if [[ -e $1 ]] && [[ ! -d $1 ]]; then
        echo "$1 exists but it's not a directory"
        exit 1
    fi
}

WITH_TESTS=false

function install() {
    check_dir $1
    mkdir -p $1
    INSTALL_DIR=`cd $1 && echo $PWD`
    CMAKE_OPTIONS="-DCMAKE_INSTALL_PREFIX=$INSTALL_DIR"
    if [[ $WITH_TESTS == true ]]; then
        CMAKE_OPTIONS="$CMAKE_OPTIONS -DCMAKE_BUILD_TESTS=1"
    fi
    mkdir -p build && cd build
    echo "Install cpputil to $INSTALL_DIR"
    cmake .. $CMAKE_OPTIONS
    make
    make install
}

function uninstall() {
    check_dir $1
    UNINSTALL_DIR=${1%/}
    echo $UNINSTALL_DIR
    SUBDIRS=(bin lib include)
    echo "Following directories will be removed:"
    for SUBDIR in ${SUBDIRS[@]}; do
        echo "  $UNINSTALL_DIR/$SUBDIR"
    done

    while true; do
        echo -n "Are you sure? [y/N]: "
        read ANSWER
        if [[ $ANSWER =~ ^[yYnN] ]]; then
            if [[ ${ANSWER:0:1} = [yY] ]]; then
                for SUBDIR in ${SUBDIRS[@]}; do
                    COMMAND="rm -rf $UNINSTALL_DIR/$SUBDIR"
                    echo $COMMAND && eval $COMMAND
                done
            fi
            break
        fi
    done
}

# parse args
OPTIONS=hi:u:
LONGOPTS=help,install:,uninstall:,with-tests
! PARSED=$(getopt --options=$OPTIONS --longoptions=$LONGOPTS --name "$0" -- "$@")
if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
    exit 2
fi
eval set -- "$PARSED"

UNINSTALL=false
CMAKE_INSTALL_PREFIX=/usr/local

while true; do
    case "$1" in
        -h|--help) usage $0; exit 0; ;;
        -i|--install) CMAKE_INSTALL_PREFIX=$2; shift 2; ;;
        -u|--uninstall) UNINSTALL=true; UNINSTALL_DIR=$2; shift 2; ;;
        --with-tests) WITH_TESTS=true; shift; ;;
        --) shift; break; ;;
        *) echo "Programming error"; exit 3; ;;
    esac
done

if [[ $# -ne 0 ]]; then
    echo "$0: no extra command-line arguments were needed except options"
    usage $0
    exit 4
fi

if [[ $UNINSTALL == false ]]; then
    SHELL_DIR=`cd $(dirname $0) && echo $PWD`
    cd $SHELL_DIR
    install $CMAKE_INSTALL_PREFIX
else
    uninstall $UNINSTALL_DIR
    exit 0
fi
