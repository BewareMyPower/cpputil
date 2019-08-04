#!/bin/bash
SHELL_DIR=$(dirname $0)
cd $SHELL_DIR

#find . -name "*.h" -o -name "*.cc" | xargs grep -n "// *TODO:"
find . -regextype posix-egrep -regex ".*\.(h|cc|cpp)" | xargs grep -n "// *TODO:"
