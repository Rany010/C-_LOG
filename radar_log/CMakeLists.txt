# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

include_directories(
    ${CMAKE_SOURCE_DIR}/spdlog
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(MDLOG_LIB STATIC
    mdlog.cpp
)