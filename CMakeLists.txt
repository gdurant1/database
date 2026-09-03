cmake_minimum_required(VERSION 4.3)
project(database)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(.idea)

add_executable(database
        .idea/.gitignore
        .idea/database.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        database.cpp
        README.md)
