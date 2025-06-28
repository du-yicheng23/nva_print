cmake_minimum_required(VERSION 3.27)

project(nva_print C)
set(PROJECT_PREFIX NVA)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ./inc/)

file(GLOB_RECURSE ${PROJECT_PREFIX}_SOURCES "./src/*.c")
target_sources(${PROJECT_NAME} INTERFACE ${${PROJECT_PREFIX}_SOURCES})
