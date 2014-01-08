#!/bin/bash

source _env.sh || echo "Run me from scripts directory"
time _build_release_version $@ || exit
