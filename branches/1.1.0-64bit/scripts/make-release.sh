#!/bin/sh

working_root="/tmp"
wdxtaglibstagedir="/tmp/wdxtaglib-stage"
package="wdx_WDXTagLib_*.zip"
artifact="wdxtaglib.wdx"
artifact64="$artifact"64

./build-all.sh "$wdxtaglibstagedir" || exit

# save package
#paket lezhit ne v stage a v build papke
cp "$wdxtaglibstagedir/$package" "$working_root" || exit

rm -rf "$wdxtaglibstagedir" || exit
./build-all.sh "$wdxtaglibstagedir" 64 || exit

# add 64bit artifact to package
mv "$wdxtaglibstagedir/$artifact" "$wdxtaglibstagedir/$artifact64" || exit
zip -g "$working_root/$package" "$wdxtaglibstagedir/$artifact64" || exit