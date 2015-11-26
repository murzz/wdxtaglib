#!/bin/sh

sudo apt-get update && \
sudo apt-get dist-upgrade && \
sudo apt-get install wget zip cmake ninja-build && \
sudo apt-get --assume-yes remove mingw32 && \
sudo apt-get --assume-yes install build-essential mingw-w64 g++-mingw-w64 libz-dev
