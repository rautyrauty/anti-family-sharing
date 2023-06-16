cmake_minimum_required (VERSION 3.2)
project (anti-family-sharing LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

set(GMOD_MODULE_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../gmod-module-base-development)

if (NOT(EXISTS ${GMOD_MODULE_BASE_DIR}))
    message( FATAL_ERROR "INSTALL AND SET GMOD MODULE BASE DEVELOPMENT FROM https://github.com/Facepunch/gmod-module-base/tree/development")
endif()

add_subdirectory(${GMOD_MODULE_BASE_DIR}/include ${GMOD_MODULE_BASE_DIR}/include/build)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC gmod-module-base
    )

set_gmod_suffix_prefix(${PROJECT_NAME})