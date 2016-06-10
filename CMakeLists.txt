cmake_minimum_required(VERSION 2.8)

project(wdxtaglib)

set(PACKAGE_DESCRIPTION_SUMMARY "Content plugin for Total Commander for reading and writing audio file tags")
set(PACKAGE_VENDOR "Dmitry Murzaikin")
set(PACKAGE_NAME "WDXTagLib")
set(PACKAGE_VERSION "1.1.4")

set(PACKAGE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})

if (CMAKE_COMPILER_IS_GNUCC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
   #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x ")
endif()

set(TAGLIB_INCLUDES ${TAGLIB_ROOT}/include/taglib)
set(TAGLIB_LIBRARY tag)

link_directories(
    ${TAGLIB_ROOT}/lib
)

if (NOT CMAKE_COMPILER_IS_GNUCC)
    set(ZLIB_LIBRARY zlibstatic)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${TAGLIB_INCLUDES}
)

add_definitions(
    -DBUILD_DLL
    -DTAGLIB_STATIC
)

set(SOURCES
    src/main.cpp
    src/plugin.cpp
    src/base.cpp
    src/utils.cpp
    src/cunicode.cpp
)

add_library(wdxtaglib SHARED ${SOURCES})

target_link_libraries(wdxtaglib ${TAGLIB_LIBRARY} ${ZLIB_LIBRARY})

# artifact naming
set_target_properties(wdxtaglib PROPERTIES PREFIX "")
set_target_properties(wdxtaglib PROPERTIES SUFFIX ".wdx")

if (CMAKE_COMPILER_IS_GNUCC)
   # link runtime statically, remove @ from exported symbols
   set_target_properties(wdxtaglib PROPERTIES LINK_FLAGS "-static -Wl,--kill-at")
endif()

install(TARGETS wdxtaglib DESTINATION .)

set(DOCS 
    COPYING
    COPYING.LESSER
    README.md
    res/pluginst.inf
)

install(FILES ${DOCS} DESTINATION .)

set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_PACKAGE_FILE_NAME wdx_${PACKAGE_NAME}_${PACKAGE_VERSION})

string(TOLOWER ${CPACK_GENERATOR} FILE_EXT)
file(WRITE ${CMAKE_BINARY_DIR}/package_name "${CPACK_PACKAGE_FILE_NAME}.${FILE_EXT}")

include(CPack)
