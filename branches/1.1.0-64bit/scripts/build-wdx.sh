#!/bin/sh

#"$toolchainfile" "$wdxtaglib_root" "$taglibstagedir" "$working_root" "$wdxtaglibstagedir" "$wdxtaglibbuilddir" $with_64bit
toolchainfile="$1"
wdxtaglib_root="$2"
taglibstagedir="$3"
working_root="$4"
wdxtaglibstagedir="$5"
wdxtaglibbuilddir="$6"
with_64bit="$7"

cpu_count=$(grep -c ^processor /proc/cpuinfo)

if test ! -f "$toolchainfile"; then
    echo "toolchain file not exists: $toolchainfile"
    exit 1
fi

if test ! -d "$wdxtaglib_root"; then
    echo "wdxtaglib_root directory not exists: $wdxtaglib_root"
    exit 1
fi

if test ! -d "$taglibstagedir"; then
    echo "taglibstagedir directory not exists: $taglibstagedir"
    exit 1
fi

if test -z "$working_root"; then
	working_root="/tmp/wdxtaglib"
fi

if test -z "$wdxtaglibbuilddir"; then
	wdxtaglibbuilddir="$working_root/wdxtaglib-build"
fi


# build
cmakeparams="$cmakeparams -DCMAKE_TOOLCHAIN_FILE=$toolchainfile"
cmakeparams="$cmakeparams -DCMAKE_BUILD_TYPE=Release"
cmakeparams="$cmakeparams -DCMAKE_INSTALL_PREFIX=$wdxtaglibstagedir"
cmakeparams="$cmakeparams -DTAGLIB_ROOT=$taglibstagedir"
if test "$with_64bit" = "64"; then
	cmakeparams="$cmakeparams -DWITH_64BIT=ON"
fi

#rm -rf "$wdxtaglibbuilddir" || exit
mkdir -p "$wdxtaglibbuilddir" || exit
cd "$wdxtaglibbuilddir" || exit
if test ! -f "$wdxtaglibbuilddir/CMakeCache.txt"; then
	cmake $cmakeparams "$wdxtaglib_root" || exit
fi
make -j$cpu_count install && make -j$cpu_count package || exit
