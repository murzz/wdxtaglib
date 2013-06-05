#!/bin/sh

#"$working_root" "$toolchainfile" "$taglibstagedir" $with_64bit
toolchainfile="$1"
working_root="$2"
taglibstagedir="$3"
with_64bit="$4"

cpu_count=$(grep -c ^processor /proc/cpuinfo)

ver=1.8
package=taglib-$ver
archive=$package.tar.gz
url=http://taglib.github.io/releases/$archive

if test ! -f "$toolchainfile"; then
    echo "toolchain file not exists: $toolchainfile"
    exit 1
fi

if test -z "$working_root"; then
	working_root="/tmp/taglib"
fi

if test -z "$taglibstagedir"; then
	taglibstagedir="$working_root/$package-stage"
fi


# download
downloaded="$working_root/$archive"
#wgetparams="$wgetparams --quiet"
wgetparams="$wgetparams --output-document=$downloaded"
wgetparams="$wgetparams $url"

if test ! -f "$downloaded"; then
	mkdir -p "$working_root"
	wget $wgetparams || exit
fi


# untar
if test ! -f "$working_root/$package/CMakeLists.txt"; then
	tar -xf "$downloaded" -C "$working_root" || exit
fi


# build
cmakeparams="$cmakeparams -DCMAKE_TOOLCHAIN_FILE=$toolchainfile"
cmakeparams="$cmakeparams -DCMAKE_BUILD_TYPE=Release"
cmakeparams="$cmakeparams -DCMAKE_INSTALL_PREFIX=$taglibstagedir"
cmakeparams="$cmakeparams -DENABLE_STATIC=ON"
cmakeparams="$cmakeparams -DENABLE_STATIC_RUNTIME=ON"
cmakeparams="$cmakeparams -DVISIBILITY_HIDDEN=ON"
#cmakeparams="$cmakeparams -DBUILD_TESTS=ON"
#cmakeparams="$cmakeparams -DBUILD_EXAMPLES=ON"

if test "$with_64bit" = "64"; then
	cmakeparams="$cmakeparams -DWITH_64BIT=ON"
fi

builddir="$working_root/$package-build"
#rm -rf "$builddir" || exit
mkdir -p "$taglibstagedir"
mkdir -p "$builddir" || exit
cd "$builddir" || exit
if test ! -f "$builddir/CMakeCache.txt"; then
	cmake $cmakeparams "$working_root/$package" || exit
fi
make -j$cpu_count install || exit
