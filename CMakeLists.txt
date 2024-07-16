cmake_minimum_required(VERSION 3.26)
project(Registry)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/6.7.1/lib/cmake/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6Widgets)

add_executable(Registry main.cpp
        Activity.h
        Registry.h)

target_link_libraries(Registry Qt6::Widgets)
