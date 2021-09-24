cmake_minimum_required(VERSION 3.7)
enable_language(CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../cmake/modules)

#
# C++ version
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

#
# Set our project name
#
project(utf8_to_windows31j_cvt_chekcer)

#
# Source files
#
set(utf8_to_windows31j_cvt_chekcer_src
    "./utf8_to_windows31j_cvt_chekcer.cpp"
)

#
# Compile
#
add_executable(utf8_to_windows31j_cvt_chekcer ${utf8_to_windows31j_cvt_chekcer_src})
target_include_directories(utf8_to_windows31j_cvt_chekcer PRIVATE "../include")
