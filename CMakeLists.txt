cmake_minimum_required(VERSION 3.1)
project(matrix
        VERSION 0.1
        DESCRIPTION "Practicing linear algebra concepts"
        LANGUAGES CXX)
enable_testing()

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wformat=2 -std=c++${CXX_STANDARD}")
elseif(MSVC)
    message(FATAL_ERROR "Can't compile on MSVC yet")
endif()

add_subdirectory(src)
add_subdirectory(test)