#!/bin/bash

source _env.sh || echo "Run me from scripts directory"
_make_release $@ || exit