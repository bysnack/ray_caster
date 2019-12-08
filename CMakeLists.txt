cmake_minimum_required(VERSION 3.2)
project (caster)
#version number
set (CASTER_VERSION_MAJOR 1)
set (CASTER_VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")
set(GSL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/GSL/include)

include_directories(${SFML_INCLUDE_DIR}
										${CMAKE_SOURCE_DIR})

find_package(SFML REQUIRED COMPONENTS graphics audio system window)

add_executable(caster main.cpp Map.h User.h)

target_include_directories(caster PRIVATE ${GSL_INCLUDE_DIR})
target_link_libraries(caster 	sfml-graphics 
								sfml-audio 
								sfml-system 
								sfml-window)
