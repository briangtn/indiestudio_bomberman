cmake_minimum_required(VERSION 3.11)

project(JFEntityComponentSystem)

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

add_library(jfecs ${SOURCES_CPP} ${SOURCES_HPP})
target_include_directories(
        jfecs
        PUBLIC
        include
)
