#!/bin/sh
sudo apt-get autoremove && \
sudo apt-get clean && \
sudo apt-get install --fix-broken && \
sudo apt-get update && \
sudo apt-get \
   --assume-yes \
   --install-suggests \
   install \
      wget \
      zip \
      cmake \
      build-essential \
      mingw-w64 \
      g++-mingw-w64
