cmake_minimum_required(VERSION 3.9)
project(uniquePeptideExtractor)

set(CMAKE_CXX_STANDARD 11)

# include_directories(src)

set(PROG_SHARE_DIR "${PROJECT_SOURCE_DIR}/share" CACHE STRING "Path to directory with help and usage files.")
add_compile_definitions(PROG_SHARE_DIR=\"${PROG_SHARE_DIR}\")

add_executable(uniquePeptideExtractor
        src/dtafilter.cpp
        src/main.cpp
        src/params.cpp
        src/utils.cpp)
