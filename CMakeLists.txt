cmake_minimum_required(VERSION 3.17)
project(uniquePeptideExtractor)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(uniquePeptideExtractor
        src/dtafilter.cpp
        src/main.cpp
        src/params.cpp
        src/utils.cpp)
