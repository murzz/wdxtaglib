#!/bin/sh
sudo apt-get --quiet autoclean && \
sudo apt-get --quiet update && \
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
