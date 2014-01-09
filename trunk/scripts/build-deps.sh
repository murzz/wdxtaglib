#!/bin/sh
#sudo apt-get autoclean && \
#sudo apt-get update && \
sudo apt-get \
   --quiet \
   --assume-yes \
   --install-suggests \
   --fix-broken \
   install \
      wget \
      zip \
      cmake \
      build-essential \
      mingw-w64 \
      g++-mingw-w64
