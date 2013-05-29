#!/bin/sh

ver=1.1.0
package=wdxtaglib-$ver
#archive=$package.tar.gz
#url=http://taglib.github.io/releases/$archive
workdir=/tmp/$package
stagedir="$workdir/install"
#downloaded="$workdir/$archive"
builddir="$workdir/build"
#toolchainfile="/home/dm/src/wdxtaglib/latest-taglib/mk/toolchain-cross-mingw32-linux.cmake"
toolchainfile="$1"
srcdir="$2"
taglibstagedir="$3"

if test ! -d "$srcdir"; then
    echo "source directory not exists: $srcdir"
    exit 1
fi

if test ! -f "$toolchainfile"; then
    echo "toolchain file not exists: $toolchainfile"
    exit 1
fi

# build
cmakeparams="$cmakeparams -DCMAKE_TOOLCHAIN_FILE=$toolchainfile"
cmakeparams="$cmakeparams -DCMAKE_BUILD_TYPE=Release"
cmakeparams="$cmakeparams -DCMAKE_INSTALL_PREFIX=$stagedir"
cmakeparams="$cmakeparams -DTAGLIB_ROOT=$taglibstagedir"

#rm -rf "$builddir" || exit
mkdir -p "$builddir" || exit
cd "$builddir" || exit
if test ! -f "$builddir/CMakeCache.txt"; then
	cmake $cmakeparams "$srcdir" || exit
fi
make -j package || exit