#!/bin/sh

sudo apt-get install wget zip cmake aptitude && \
sudo aptitude remove mingw32 \
sudo aptitude install build-essential mingw-w64