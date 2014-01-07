#!/bin/bash

source _env.sh || echo "Run me from scripts directory"
_download_and_build_taglib $@ || exit