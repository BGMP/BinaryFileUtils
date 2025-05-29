cmake_minimum_required(VERSION 3.27)
project(BinaryFileUtils)

set(CMAKE_CXX_STANDARD 17)

add_executable(BinaryFileUtils
        src/Main.cpp
        include/Main.h
        src/BinUtils.cpp
        include/BinUtils.h)

target_include_directories(BinaryFileUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
