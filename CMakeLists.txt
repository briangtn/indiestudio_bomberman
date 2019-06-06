cmake_minimum_required(VERSION 3.11)

project(indiestudio)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/jfecs)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-dependencies)

set(Irrklang_FIND_REQUIRED)
set(Irrlicht_FIND_REQUIRED)

include(${PROJECT_SOURCE_DIR}/cmake-dependencies/FindIrrlicht.cmake)
include(${PROJECT_SOURCE_DIR}/cmake-dependencies/FindIrrklang.cmake)

add_definitions(-D DO_NOT_SEND_SPECIFIC_KEY_EVENT=false)

file(
        GLOB_RECURSE
        SOURCES_CPP
		${PROJECT_SOURCE_DIR}/sources/*.cpp
)
file(
        GLOB_RECURSE
        SOURCES_HPP
		${PROJECT_SOURCE_DIR}/include/*.hpp
)

find_package(Boost 1.65 REQUIRED COMPONENTS
		date_time filesystem iostreams)

add_executable(bomberman ${SOURCES_CPP} ${SOURCES_HPP})
target_include_directories(bomberman PUBLIC
		${PROJECT_SOURCE_DIR}/lib/jfecs/include
		${PROJECT_SOURCE_DIR}/include
		${Irrlicht_INCLUDE_DIRS}
		${Irrklang_INCLUDE_DIRS}
		)
target_link_libraries(bomberman
		jfecs
		${Irrlicht_LIBRARIES}
		${Irrklang_LIBRARIES}
		Boost::filesystem
		)

if (UNIX)
	target_link_libraries(bomberman GL Xxf86vm Xext X11 Xcursor)
endif (UNIX)