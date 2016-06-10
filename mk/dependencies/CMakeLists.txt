cmake_minimum_required(VERSION 3.0)

project(build-dependencies NONE)

if(${STAGING_ROOT} MATCHES "^$")
	set(STAGING_ROOT ${CMAKE_BINARY_DIR}/staging)
endif()

include(zlib.cmake)
include(TagLib.cmake)
