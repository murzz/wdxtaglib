Status
============
[![Build Status](https://travis-ci.org/murzz/wdxtaglib.svg?branch=master)](https://travis-ci.org/murzz/wdxtaglib)
[![Build status](https://ci.appveyor.com/api/projects/status/px1gljh02yttkakd/branch/master?svg=true)](https://ci.appveyor.com/project/murzz/wdxtaglib/branch/master)
[![Latest Release](https://img.shields.io/github/release/murzz/wdxtaglib.svg)](https://github.com/murzz/wdxtaglib/releases/latest)

Description
===========
WDXTagLib is a [content plugin](http://www.ghisler.ch/wiki/index.php/Content_plugin) for [Total Commander](http://ghisler.com/) which uses [TagLib](https://taglib.github.io/) library for reading and editing meta-data of audio files. TagLib supports both ID3v1 and ID3v2 for MP3 files, Ogg Vorbis comments and ID3 tags and Vorbis comments in FLAC, MPC, Speex, WavPack TrueAudio, WAV, AIFF, MP4 and ASF files.

Functionality
=============
Tags supported for reading and editing:

* title,
* artist,
* album,
* year,
* tracknumber,
* comment,
* genre. 

Readonly tags:

* bitrate,
* samplerate,
* channels,
* length,
* tag type. 

Build time dependencies
=======================
* realpath
* basename
* dirname
* wget
* zip
* libz-dev
* mingw-w64
* cmake
* make
* taglib
* ...

Clone
=====
`git clone git@github.com:murzz/wdxtaglib.git`

Build
=====
`cd build && ./build_release`

Run time dependencies
=====================
* Total Commander 7.02 or higher (7.5 for Unicode support).

Some useful links
=================
* [List of content plugins](http://www.ghisler.com/plugins.htm#content)
* [Content-Plugin Guide 2.1se](http://ghisler.fileburst.com/content/contentpluginhelp2.1se.zip), could be found on page above
* [Plugin interface descriptions](http://www.ghisler.ch/board/viewtopic.php?t=25751&sid=86a548a6c0a1d02bf17738a446f74356)
* [Content plugin wiki](http://www.ghisler.ch/wiki/index.php/Content_plugin)

License
=======
This software is distributed under the GNU General Public License (GPL) version 3 or later or GNU Lesser General Public License (LGPL) version 3 or later.

No Warranty
===========
The software described here has no warranty, it is provided “as is”. It is your responsibility to validate the behavior of the routines and their accuracy using the source code provided, or to purchase support and warranties from commercial redistributors. Consult the GNU General Public license for further details.
