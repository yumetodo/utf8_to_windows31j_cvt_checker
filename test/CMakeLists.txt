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
# Config options
#
if((CMAKE_BUILD_TYPE STREQUAL "Debug") AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    message("you can specify INFERIOR_OSYNCSTREAM_ENABLE_COVERAGE")
    option(INFERIOR_OSYNCSTREAM_ENABLE_COVERAGE "enable coverage" FALSE)
else()
    set(INFERIOR_OSYNCSTREAM_ENABLE_COVERAGE FALSE)
endif()

#
# Set our project name
#
project(basic_test)

#
# Source files
#
set(basic_test_src
    "./utf8_to_windows31j_cvt_checker_test.cpp"
    "./linter_test.cpp"
)

#
# find libraries and include
#

# find thread library
find_package(Iconv REQUIRED)

if(INFERIOR_OSYNCSTREAM_ENABLE_COVERAGE)
    message("coverage enabled")
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_EXCLUDES "*gcc*" "*iutest*" "*/usr/include/*" "*mingw*")
    SETUP_TARGET_FOR_COVERAGE(
        NAME test_coverage       # New target name
        EXECUTABLE basic_test          # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES basic_test        # Dependencies to build first
    )
    option(INFERIOR_OSYNCSTREAM_ENABLE_COVERAGE_HTML "enable coverage result to html" TRUE)
    option(INFERIOR_OSYNCSTREAM_ENABLE_COVERAGE_SEND "send coverage result" FALSE)
    if(INFERIOR_OSYNCSTREAM_ENABLE_COVERAGE_HTML)
        message("coverage result to html enabled")
        SETUP_TARGET_FOR_COVERAGE_TO_HTML(
            NAME test_coverage_to_html                 # New target name
            INFO_FILE_NAME test_coverage.info.cleaned  # coverage task result file name
            DEPENDENCIES test_coverage                 # Dependencies(coverage task, etc...)
        )
    endif()
endif()

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
add_executable(basic_test ${basic_test_src})
target_include_directories(basic_test PRIVATE "../include" "../iutest/include")
target_link_libraries(basic_test PRIVATE Iconv::Iconv)

#
# Link
#
if(WIN32)
    target_link_libraries(basic_test PRIVATE Iconv::Iconv ws2_32)
else()
    target_link_libraries(basic_test PRIVATE Iconv::Iconv)
endif()

add_custom_target(run_test
    COMMAND basic_test
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS basic_test
    COMMENT "Execute produced executable."
)
