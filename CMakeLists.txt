cmake_minimum_required(VERSION 3.27)

project(nva_print C)
set(PROJECT_PREFIX NVA)

option(${PROJECT_PREFIX}_INLINE_MODE "Enable inline mode for nva_print" OFF)

add_library(${PROJECT_NAME} INTERFACE)

if (${${PROJECT_PREFIX}_INLINE_MODE})
    message("${PROJECT_NAME} Will be in inline mode.")
    target_compile_definitions(${PROJECT_NAME} INTERFACE -DNVA_USE_INLINE)
endif ()

target_include_directories(${PROJECT_NAME} INTERFACE
    ./inc/
    ./decl_and_def/
)

file(GLOB_RECURSE ${PROJECT_PREFIX}_SOURCES "./src/*.c")
target_sources(${PROJECT_NAME} INTERFACE ${${PROJECT_PREFIX}_SOURCES})
