cmake_minimum_required(VERSION 2.8)

project(wdxtaglib)

set(PACKAGE_DESCRIPTION_SUMMARY "Content plugin for Total Commander for reading and writing audio file tags")
set(PACKAGE_VENDOR "Dmitry Murzaikin")
set(PACKAGE_NAME "WDXTagLib")
set(PACKAGE_VERSION "1.1.0")

set(PACKAGE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x ")

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${TAGLIB_ROOT}/include/taglib
)

link_directories(
    ${TAGLIB_ROOT}/lib
)

add_definitions(
    -DBUILD_DLL
    -DTAGLIB_STATIC
)

set(SOURCES
    src/main.cpp
    src/CWDXTagLib.cpp
    src/CWDXBase.cpp
    src/CUtils.cpp
    src/cunicode.cpp
)

add_library(wdxtaglib SHARED ${SOURCES})

target_link_libraries(wdxtaglib tag)

# artifact naming
set_target_properties(wdxtaglib PROPERTIES PREFIX "")
set_target_properties(wdxtaglib PROPERTIES SUFFIX ".wdx")

# link runtime statically, remove @ from exported symbols
set_target_properties(wdxtaglib PROPERTIES LINK_FLAGS "-static -Wl,--kill-at")

install(TARGETS wdxtaglib DESTINATION .)

set(DOCS 
    doc/COPYING
    doc/COPYING.LESSER
    doc/readme.txt
    res/pluginst.inf
)

install(FILES ${DOCS} DESTINATION .)

set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_PACKAGE_FILE_NAME wdx_${PACKAGE_NAME}_${PACKAGE_VERSION})
include(CPack)
