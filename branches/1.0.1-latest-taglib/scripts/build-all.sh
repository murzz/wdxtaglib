#!/bin/sh

# set current dir or run me from project dir
projectdir=$(pwd)
toolchainfile="$projectdir/mk/toolchain-cross-mingw32-linux.cmake"
srcdir="$projectdir"
taglibstagedir=/tmp/taglib

rm -rf $taglibstagedir
mkdir -p $taglibstagedir
"$projectdir/scripts/build-taglib.sh" $toolchainfile $taglibstagedir || exit
"$projectdir/scripts/build-wdx.sh" $toolchainfile $srcdir $taglibstagedir || exit