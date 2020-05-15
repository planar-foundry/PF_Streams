cmake_minimum_required(VERSION 3.8)
project(PF_Streams VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(PFSTREAMS_BUILD_TESTS "Builds all unit tests" OFF)
option(PFSTREAMS_BIG_ENDIAN "Sets big endian mode" OFF)

add_subdirectory(ext)
add_subdirectory(src)

if (${PFSTREAMS_BUILD_TESTS})
    add_subdirectory(tests)
endif()
