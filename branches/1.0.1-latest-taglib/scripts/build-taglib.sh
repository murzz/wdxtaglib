#!/bin/sh

ver=1.8
package=taglib-$ver
archive=$package.tar.gz
url=http://taglib.github.io/releases/$archive
workdir=/tmp/$package
stagedir="$workdir/install"
downloaded="$workdir/$archive"
builddir="$workdir/build"
#toolchainfile="/home/dm/src/wdxtaglib/latest-taglib/mk/toolchain-cross-mingw32-linux.cmake"
toolchainfile=$1

if test ! -f "$toolchainfile"; then
    echo "toolchain file not exists: $toolchainfile"
    exit 1
fi

# download
wgetparams="$wgetparams --output-document=$downloaded"
wgetparams="$wgetparams $url"

#rm -rf "$workdir" || exit
mkdir -p "$workdir" || exit
if test ! -f "$downloaded"; then
	wget $wgetparams || exit
fi


# untar
tar -xf "$downloaded" -C "$workdir"|| exit


# build
cmakeparams="$cmakeparams -DCMAKE_TOOLCHAIN_FILE=$toolchainfile"
cmakeparams="$cmakeparams -DCMAKE_BUILD_TYPE=Release"
cmakeparams="$cmakeparams -DCMAKE_INSTALL_PREFIX=$stagedir"
cmakeparams="$cmakeparams -DENABLE_STATIC=ON"
cmakeparams="$cmakeparams -DENABLE_STATIC_RUNTIME=ON"
cmakeparams="$cmakeparams -DVISIBILITY_HIDDEN=ON"


#rm -rf "$builddir" || exit
mkdir -p "$builddir" || exit
cd "$builddir" || exit
if test ! -f "$workdir/$package/CMakeCache.txt"; then
	cmake $cmakeparams "$workdir/$package" || exit
fi
make && make install || exit