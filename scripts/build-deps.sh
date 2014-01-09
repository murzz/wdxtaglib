#!/bin/sh
sudo apt-get autoclean && \
sudo apt-get update && \
sudo apt-get \
   --force-yes \
   --install-suggests \
   --fix-broken \
   install \
      wget \
      zip \
      cmake \
      build-essential \
      mingw-w64 \
      g++-mingw-w64
