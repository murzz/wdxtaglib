#!/bin/sh

cmd_name=$(basename $0)
tool_dir=$(realpath $(dirname $0))
wdx_src_dir=$tool_dir/..
. $tool_dir/_env.sh || exit
_${cmd_name} "$@" || exit