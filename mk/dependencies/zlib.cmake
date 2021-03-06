include(ExternalProject)

set(ZLIB_REPO_URL https://github.com/madler/zlib.git)
set(ZLIB_TAG v1.2.8)

set(ZLIB_ARGS
   ${COMMON_CMAKE_ARGS}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
)

ExternalProject_Add(zlib
        GIT_REPOSITORY ${ZLIB_REPO_URL}
        GIT_TAG ${ZLIB_TAG}
        CMAKE_ARGS ${ZLIB_ARGS}
)
