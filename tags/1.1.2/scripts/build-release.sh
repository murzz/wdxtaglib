#!/bin/bash

source _env.sh || echo "Run me from scripts directory"
_build_release $@ || exit