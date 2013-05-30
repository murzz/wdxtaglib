#!/bin/sh

wdxtaglibstagedir=$1
wdxtaglibbuilddir=$2
with_64bit=$3

# set current dir to scripts dir or run me from scripts dir directly
wdxtaglib_root=$(pwd)/..

toolchainfile="$wdxtaglib_root/mk/toolchain-cross-mingw32-linux.cmake"

working_root="/tmp/wdxtaglib"
if test "$with_64bit" = "64"; then
	working_root="$working_root-64"
fi

taglibstagedir="$working_root/taglib-stage"

if test -z "$wdxtaglibstagedir"; then
	wdxtaglibstagedir="$working_root/wdxtaglib-stage"	
fi


#rm -rf "$working_root" || exit
#rm -rf $taglibstagedir || exit
mkdir -p $taglibstagedir || exit
"$wdxtaglib_root/scripts/build-taglib.sh" "$toolchainfile" "$working_root" "$taglibstagedir" $with_64bit || exit
"$wdxtaglib_root/scripts/build-wdx.sh" "$toolchainfile" "$wdxtaglib_root" "$taglibstagedir" "$working_root" "$wdxtaglibstagedir" "$wdxtaglibbuilddir" $with_64bit || exit
