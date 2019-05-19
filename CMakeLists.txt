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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -iquote ${PROJECT_SOURCE_DIR}/lib/jfecs/include -iquote ${PROJECT_SOURCE_DIR}/include")
target_link_libraries(bomberman jfecs Irrlicht)
if (UNIX)
	target_link_libraries(bomberman GL Xxf86vm Xext X11 Xcursor)
endif (UNIX)