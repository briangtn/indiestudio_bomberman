cmake_minimum_required(VERSION 3.11)

project(indiestudio)

add_subdirectory(lib/jfecs)

add_definitions(-D DO_NOT_SEND_SPECIFIC_KEY_EVENT=false)

file(
        GLOB_RECURSE
        SOURCES_CPP
        sources/*.cpp
)
file(
        GLOB_RECURSE
        SOURCES_HPP
        include/*.hpp
)

add_executable(bomberman ${SOURCES_CPP} ${SOURCES_HPP})
target_include_directories(
		bomberman
        PUBLIC
		lib/jfecs/include
        include
)
target_link_libraries(bomberman jfecs Irrlicht)
if (UNIX)
	target_link_libraries(bomberman GL Xxf86vm Xext X11 Xcursor)
endif (UNIX)