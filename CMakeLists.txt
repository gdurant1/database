cmake_minimum_required(VERSION 3.10)
project(database)

set(CMAKE_CXX_STANDARD 26)

find_package(Boost REQUIRED COMPONENTS algorithm)

add_executable(database main.cpp)

target_link_libraries(database PRIVATE Boost::algorithm)