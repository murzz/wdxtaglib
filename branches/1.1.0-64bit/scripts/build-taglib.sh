#!/bin/sh

ver=1.8
package=taglib-$ver
archive=$package.tar.gz
url=http://taglib.github.io/releases/$archive
workdir=/tmp/$package
#stagedir="$workdir/install"
stagedir="$2"
downloaded="$workdir/$archive"
builddir="$workdir/build"
#toolchainfile="/home/dm/src/wdxtaglib/latest-taglib/mk/toolchain-cross-mingw32-linux.cmake"
toolchainfile=$1

if test ! -f "$toolchainfile"; then
    echo "toolchain file not exists: $toolchainfile"
    exit 1
fi

if test ! -d "$stagedir"; then
    echo "stagedir not exists: $stagedir"
    exit 1
fi


# download
#wgetparams="$wgetparams --quiet"
wgetparams="$wgetparams --output-document=$downloaded"
wgetparams="$wgetparams $url"

#rm -rf "$workdir" || exit
mkdir -p "$workdir" || exit
if test ! -f "$downloaded"; then
	wget $wgetparams || exit
fi


# untar
if test ! -f "$workdir/$package/CMakeLists.txt"; then
	tar -xf "$downloaded" -C "$workdir" || exit
fi


# build
cmakeparams="$cmakeparams -DCMAKE_TOOLCHAIN_FILE=$toolchainfile"
cmakeparams="$cmakeparams -DCMAKE_BUILD_TYPE=Release"
cmakeparams="$cmakeparams -DCMAKE_INSTALL_PREFIX=$stagedir"
cmakeparams="$cmakeparams -DENABLE_STATIC=ON"
cmakeparams="$cmakeparams -DENABLE_STATIC_RUNTIME=ON"
cmakeparams="$cmakeparams -DVISIBILITY_HIDDEN=ON"
#cmakeparams="$cmakeparams -DBUILD_TESTS=ON"
#cmakeparams="$cmakeparams -DBUILD_EXAMPLES=ON"


#rm -rf "$builddir" || exit
mkdir -p "$builddir" || exit
cd "$builddir" || exit
if test ! -f "$builddir/CMakeCache.txt"; then
	cmake $cmakeparams "$workdir/$package" || exit
fi
make -j install || exit