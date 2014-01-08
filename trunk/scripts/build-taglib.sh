#!/bin/bash

source _env.sh || echo "Run me from scripts directory"
time _download_and_build_taglib $@ || exit
