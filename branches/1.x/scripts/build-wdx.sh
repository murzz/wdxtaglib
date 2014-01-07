#!/bin/bash

source _env.sh || echo "Run me from scripts directory" || exit
_build_wdx $@ || exit