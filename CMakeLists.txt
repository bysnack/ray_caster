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

set(SYSTEMS_HEADERS		systems/collision.h
						systems/initialize_map.h
						systems/movement.h
						systems/ray_cast.h
						systems/render.h
						systems/systems.h)

set(COMPONENTS_HEADERS	components/cell.h
						components/components.h
						components/container.h
						components/player.h
						components/traits.h)

set(ENTITIES_HEADERS	entities/colliding.h
						entities/dimensions.h
						entities/heading.h
						entities/position.h
						entities/render.h
						entities/speed.h)

set(UTILITIES_HEADERS	utils/utilities.h
						utils/vector.h)

set(SYSTEMS_SOURCE		systems/collision.cpp
						systems/initialize_map.cpp
						systems/movement.cpp
						systems/render.cpp
						systems/systems.cpp)

add_executable(caster main.cpp ${SYSTEM_HERADERS} ${COMPONENTS_HEADERS} ${ENTITIES_HEADERS} ${UTILITIES_HEADERS} ${SYSTEMS_SOURCE})

target_include_directories(caster PRIVATE ${GSL_INCLUDE_DIR})
target_link_libraries(caster 	sfml-graphics 
								sfml-audio 
								sfml-system 
								sfml-window)
