#!/bin/sh

# for debug purposes
#SVNCMD=echo
SVNCMD=svn

taglib_ver=1.9.1

tag_url=^/tags/
tag_full_url=https://wdxtaglib.googlecode.com/svn/tags/
taglib_url_root=http://taglib.github.io/releases/

cpu_count=$(grep -c ^processor /proc/cpuinfo)

_set_common_vars()
{
   if test -z "$working_root"; then
      working_root="/tmp/wdxtaglib"
   fi

   if ! test -z "$with_64bit"; then
      working_root="/tmp/wdxtaglib64"
   fi

   package="taglib-$taglib_ver"
   
   if test -z "$wdx_src_dir"; then
      wdx_src_dir="$(pwd)/.."
   fi

   version_file="$wdx_src_dir/CMakeLists.txt"

   if test -z "$toolchain_file"; then
      toolchain_file="$wdx_src_dir/mk/toolchain-cross-mingw32-linux.cmake"
   fi

   if test ! -f "$toolchain_file"; then
      echo "toolchain file not exists: $toolchain_file"
      exit 1
   fi

   wdx_build_dir="$working_root/wdxtaglib-build"
   wdx_stage_dir="$working_root/wdxtaglib-stage"
   taglib_src_dir="$working_root/$package"
   taglib_build_dir="$working_root/$package-build"
   taglib_stage_dir="$working_root/$package-stage"

   artifact="wdxtaglib.wdx"
   artifact64="$artifact"64
}

_bump_version()
{
   local new_ver=$1

   _set_common_vars || exit

   # check versions
   if test -z "${new_ver}"; then
      echo "Usage: ./make-release.sh new_version"
      exit 1
   fi

   # compose urls
   branch_url=$(svn info "$wdx_src_dir"| grep URL | cut -f2 -d' ')

   if test -z "$branch_url"; then
      echo "Branch URL is unknown"
      exit 1
   fi

   new_tag="${tag_url}${new_ver}"

   # bump version
   sed -i -e "s/PACKAGE_VERSION \"[0-9a-z\.]\+\"/PACKAGE_VERSION \"${new_ver}\"/g" $version_file || exit
   sed -i -e "s/PACKAGE_DATE \"[0-9]\{8\}\"/PACKAGE_DATE \"$(date "+%Y%m%d")\"/g" $version_file || exit
}

_make_release()
{
   local new_ver=$1
   _bump_version "$new_ver" || exit

   # commit version change
   ${SVNCMD} ci "$version_file" -m "Updated for release ${new_ver}" > /dev/null || exit

   # tag
   ${SVNCMD} cp "$branch_url" "$new_tag" -m "Release tag for ${new_ver}" > /dev/null || exit

   echo "Source released: $new_tag"
}

_download_taglib()
{
   local working_root=$1
   local package=$2

   _set_common_vars || exit

   local archive="$package.tar.gz"
   local url="$taglib_url_root$archive"

   # download
   local downloaded="$working_root/$archive"
   #local wgetparams="$wgetparams --quiet"
   local wgetparams="$wgetparams --output-document=$downloaded"
   local wgetparams="$wgetparams $url"

   if test ! -f "$downloaded"; then
      mkdir -p "$working_root"
      wget $wgetparams || exit
   fi

   # untar
   if test ! -f "$working_root/$package/CMakeLists.txt"; then
      tar -xf "$downloaded" -C "$working_root" || exit
   fi

   echo "TagLib downloaded"
}

_build_taglib()
{
   _set_common_vars || exit

   # build
   local cmakeparams="$cmakeparams -DCMAKE_TOOLCHAIN_FILE=$toolchain_file"
   local cmakeparams="$cmakeparams -DCMAKE_BUILD_TYPE=Release"
   local cmakeparams="$cmakeparams -DCMAKE_INSTALL_PREFIX=$taglib_stage_dir"
   local cmakeparams="$cmakeparams -DENABLE_STATIC=ON"
   local cmakeparams="$cmakeparams -DENABLE_STATIC_RUNTIME=ON"
   local cmakeparams="$cmakeparams -DVISIBILITY_HIDDEN=ON"
   #local cmakeparams="$cmakeparams -DBUILD_TESTS=ON"
   #local cmakeparams="$cmakeparams -DBUILD_EXAMPLES=ON"

   if ! test -z "$with_64bit"; then
      local cmakeparams="$cmakeparams -DWITH_64BIT=ON"
   fi

   local builddir="$working_root/$package-build"
   #rm -rf "$builddir" || exit
   mkdir -p "$taglib_stage_dir"
   mkdir -p "$taglib_build_dir" || exit
   cd "$taglib_build_dir" || exit

   if test ! -f "$taglib_build_dir/CMakeCache.txt"; then
      cmake $cmakeparams "$taglib_src_dir" || exit
   fi

   make -j$cpu_count install || exit

   echo "TagLib built"
}

_download_and_build_taglib()
{
   _download_taglib || exit
   _build_taglib || exit
}

_build_wdx()
{
   local with_64bit=$1
   if ! test -z "$with_64bit"; then
      with_64bit="on"
   fi

   _set_common_vars || exit
   _download_and_build_taglib || exit

   # build
   local cmakeparams="$cmakeparams -DCMAKE_TOOLCHAIN_FILE=$toolchain_file"
   local cmakeparams="$cmakeparams -DCMAKE_BUILD_TYPE=Release"
   local cmakeparams="$cmakeparams -DCMAKE_INSTALL_PREFIX=$wdx_stage_dir"
   local cmakeparams="$cmakeparams -DTAGLIB_ROOT=$taglib_stage_dir"
   if ! test -z "$with_64bit"; then
      local cmakeparams="$cmakeparams -DWITH_64BIT=ON"
   fi

   #rm -rf "$wdx_build_dir" || exit
   mkdir -p "$wdx_build_dir" || exit
   cd "$wdx_build_dir" || exit
   if test ! -f "$wdx_build_dir/CMakeCache.txt"; then
      cmake $cmakeparams "$wdx_src_dir" || exit
   fi

   make -j$cpu_count install && make -j$cpu_count package || exit

   echo "WDXTagLib built"
}

_build_wdx64()
{
   _build_wdx 64 || exit
}

_build_wdx_both()
{
   _build_wdx || exit
   _build_wdx 64 || exit
}

_build_release()
{
   _set_common_vars || exit

   _build_wdx || exit

   # save package
   local wdx_package=$(cat "$wdx_build_dir/package_name")
   local wdx_package_path="$working_root/$wdx_package"
   cp "$wdx_build_dir/$wdx_package" "$working_root" || exit

   _build_wdx64 || exit

   # add 64bit artifact to package
   mv "$wdx_stage_dir/$artifact" "$wdx_stage_dir/$artifact64" || exit
   cd "$wdx_stage_dir" || exit
   zip -g "$wdx_package_path" "$artifact64" || exit
   zip -d "$wdx_package_path" "libwdxtaglib.dll.a" || exit

   echo "Release built: $wdx_package_path"
}

_build_release_version()
{
   local version=$1

   if test -z "${version}"; then
      echo "Usage: ./build_release_version.sh version"
      exit 1
   fi

   _set_common_vars || exit   

   # checkout WDXTagLib tag
   wdx_src_dir="$working_root/wdxtaglib-$version"
   svn co "$tag_full_url$version" "$wdx_src_dir" || exit

   # build
   _build_release
}