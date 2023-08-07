cmake_minimum_required(VERSION 3.14)
if(LINUX)
    set(GCC_COVERAGE_COMPILE_FLAGS "-m32")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()
project(AntiFamilySharing LANGUAGES CXX)
message(STATUS "the build of the ${PROJECT_NAME} has begun. CMake version: ${CMAKE_VERSION}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.27.0")
    cmake_policy(SET CMP0144 NEW)
endif()

set(GMOD_MODULE_BASE_DIR "/../gmod-module-base-development")
if(NOT EXISTS ${GMOD_MODULE_BASE_DIR})
    message(FATAL_ERROR "GMOD_MODULE_BASE_DIR ${GMOD_MODULE_BASE_DIR} NOT EXISTS")
endif()

add_library(${PROJECT_NAME} SHARED)
if(LINUX)
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()
target_sources(${PROJECT_NAME} PRIVATE main.cpp anti-family-sharing.cpp anti-family-sharing.h ini.h json.hpp)

FIND_PACKAGE(Boost REQUIRED)
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIR}")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

find_package(OpenSSL REQUIRED)
message(STATUS "OpenSSL include dir ${OPENSSL_INCLUDE_DIR} ")
include_directories(${OPENSSL_INCLUDE_DIR})

add_subdirectory(${GMOD_MODULE_BASE_DIR}/include ${GMOD_MODULE_BASE_DIR}/include/build)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} gmod-module-base)

set_gmod_suffix_prefix(${PROJECT_NAME})
