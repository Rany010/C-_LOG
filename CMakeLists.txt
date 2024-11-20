# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(LOG_TEST)

set(CMAKE_CXX_STANDARD 11)

include_directories(
    ${CMAKE_SOURCE_DIR}/radar_log
)
add_subdirectory(radar_log)

add_executable(LOG_TEST main.cc)

target_link_libraries(LOG_TEST PRIVATE MDLOG_LIB)