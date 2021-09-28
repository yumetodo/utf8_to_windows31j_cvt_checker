cmake_minimum_required(VERSION 3.11)
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
project(utf8_to_windows31j_cvt_checker)

#
# Source files
#
set(utf8_to_windows31j_cvt_checker_src
    "./utf8_to_windows31j_cvt_checker.cpp"
)

#
# find libraries and include
#

# find thread library
find_package(Iconv REQUIRED)

#
# Update compiler waring flags
#
if(MSVC AND NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

#
# Compile
#
add_executable(utf8_to_windows31j_cvt_checker ${utf8_to_windows31j_cvt_checker_src})
target_include_directories(utf8_to_windows31j_cvt_checker PRIVATE "../include")
target_link_libraries(utf8_to_windows31j_cvt_checker PRIVATE Iconv::Iconv)
