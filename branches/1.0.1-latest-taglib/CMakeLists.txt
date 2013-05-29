cmake_minimum_required(VERSION 2.8)

project(wdxtaglib)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${TAGLIB_ROOT}/include
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
    src/CUtils.cpp)

add_library( wdxtaglib SHARED ${SOURCES})

target_link_libraries(wdxtaglib tag)

# artefact naming
set_target_properties(wdxtaglib PROPERTIES PREFIX "")
set_target_properties(wdxtaglib PROPERTIES SUFFIX ".wdx")
 
 # link runtime statically, remove @ from exported symbols
set_target_properties(wdxtaglib PROPERTIES LINK_FLAGS "-static -Wl,--kill-at")

install( TARGETS wdxtaglib DESTINATION .)

set(DOCS 
    doc/COPYING
    doc/COPYING.LESSER
    doc/read_before_install.txt
    doc/readme.txt
    res/pluginst.inf
)

install( FILES ${DOCS} DESTINATION . )

set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
include(CPack)