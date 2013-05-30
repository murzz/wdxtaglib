#!/bin/sh

working_root="/tmp"
wdxtaglibstagedir="/tmp/wdxtaglib-stage"
wdxtaglibbuilddir="/tmp/wdxtaglib-build"
package="wdx_WDXTagLib_1.1.0.zip"
artifact="wdxtaglib.wdx"
artifact64="$artifact"64

./build-all.sh "$wdxtaglibstagedir" "$wdxtaglibbuilddir" || exit

# save package
#paket lezhit ne v stage a v build papke
cp "$wdxtaglibbuilddir/$package" "$working_root" || exit

rm -rf "$wdxtaglibstagedir" || exit
rm -rf "$wdxtaglibbuilddir" || exit
./build-all.sh "$wdxtaglibstagedir" "$wdxtaglibbuilddir" 64 || exit

# add 64bit artifact to package
mv "$wdxtaglibstagedir/$artifact" "$wdxtaglibstagedir/$artifact64" || exit
cd "$wdxtaglibstagedir" || exit
zip -g "$working_root/$package" "$artifact64" || exit
zip -d "$working_root/$package" "libwdxtaglib.dll.a" || exit
