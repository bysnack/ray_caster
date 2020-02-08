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
						systems/render.h
						systems/lights.h
						systems/systems.h)

set(ENTITIES_HEADERS	entities/cell.h
						entities/entities.h
						entities/player.h
						entities/traits.h
						entities/light.h
						entities/map.h
						entities/ray.h)

set(COMPONENTS_HEADERS	components/dimensions.h
						components/heading.h
						components/position.h
						components/render.h
						components/speed.h
						components/seed.h)

set(UTILITIES_HEADERS	utils/utilities.h
						utils/vector.h
						utils/iterable_tuple.h
						utils/coordinates/world.h
						utils/coordinates/screen.h
						utils/coordinates/tile.h
						utils/coordinates/coordinates.h)

set(UTILITIES_SOURCE	utils/coordinates/world.cpp
						utils/coordinates/screen.cpp)

set(SYSTEMS_SOURCE		systems/collision.cpp
						systems/initialize_map.cpp
						systems/movement.cpp
						systems/render.cpp
						systems/lights.cpp
						systems/systems.cpp)

add_executable(caster main.cpp ${SYSTEMS_HEADERS} ${COMPONENTS_HEADERS} ${ENTITIES_HEADERS} ${UTILITIES_HEADERS} ${SYSTEMS_SOURCE} ${UTILITIES_SOURCE})

target_include_directories(caster PRIVATE ${GSL_INCLUDE_DIR})
target_link_libraries(caster 	sfml-graphics 
								sfml-audio 
								sfml-system 
								sfml-window)
