# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(LOG_TEST)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/thrid_party)

add_executable(LOG_TEST main.cc mdlog.cpp)

target_link_libraries(LOG_TEST pthread)