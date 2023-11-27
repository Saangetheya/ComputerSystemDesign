cmake_minimum_required(VERSION 3.24.0)

project(VIRTUAL)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(virtual main.cpp)
# target_include_directories(virtual PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/generator/include)

add_subdirectory(dev/gen)