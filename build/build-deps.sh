#!/bin/sh

sudo apt-get update && \
sudo apt-get -y remove mingw32 && \
sudo apt-get -y install wget zip build-essential mingw-w64 g++-mingw-w64 libz-dev
