cmake_minimum_required(VERSION 3.26)
project(Registry)

set(CMAKE_CXX_STANDARD 17)

# Set Qt's CMake prefix path
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/6.7.1/lib/cmake/")

# Enable automatic inclusion of current directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable Qt features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

# Find required Qt packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Test Core Gui)

# Add the Registry library
add_library(RegistryLib
        Registry.cpp
        Registry.h
        Activity.h
)

target_link_libraries(RegistryLib Qt6::Widgets Qt6::Core Qt6::Gui)

# Add the main executable
add_executable(RegistryMain
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

target_link_libraries(RegistryMain RegistryLib Qt6::Widgets Qt6::Core Qt6::Gui)

# Add subdirectory for Google Test
add_subdirectory(test/googletest-main)

# Include Google Test headers
target_include_directories(RegistryMain PRIVATE test/googletest-main/googletest/include)

# Enable testing
enable_testing()

# Test for Activity
add_executable(tst_activity
        test/tst_activity.cpp
)

target_link_libraries(tst_activity RegistryLib gtest gtest_main Qt6::Widgets Qt6::Core Qt6::Gui)

add_test(NAME tst_activity COMMAND tst_activity)

# Test for Registry
add_executable(tst_registry
        test/tst_registry.cpp
)

target_link_libraries(tst_registry RegistryLib gtest gtest_main Qt6::Widgets Qt6::Core Qt6::Gui)

add_test(NAME tst_registry COMMAND tst_registry)

# Test for MainWindow
add_executable(tst_mainwindow
        test/tst_mainwindow.cpp
        mainwindow.cpp
)

target_link_libraries(tst_mainwindow RegistryLib gtest gtest_main Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Test)

add_test(NAME tst_mainwindow COMMAND tst_mainwindow)