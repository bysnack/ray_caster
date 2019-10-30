cmake_minimum_required(VERSION 3.2)
project (caster)
#version number
set (CASTER_VERSION_MAJOR 1)
set (CASTER_VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS -std=c++17)

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")

include_directories(${SFML_INCLUDE_DIR}
				    ${CMAKE_SOURCE_DIR})

find_package(SFML REQUIRED COMPONENTS graphics audio system window)

add_executable(caster main.cpp Map.h User.h)

target_link_libraries(caster sfml-graphics sfml-audio sfml-system sfml-window)
