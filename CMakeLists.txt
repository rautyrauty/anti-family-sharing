cmake_minimum_required(VERSION 3.14)
project(AntiFamilySharing LANGUAGES CXX)
message(STATUS "the build of the ${PROJECT_NAME} has begun")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE main.cpp anti-family-sharing.cpp anti-family-sharing.h ini.h json.hpp)

#if(${OPENSSL_VERSION} VERSION_LESS "3.0")
#    message(AUTHOR_WARNING "Your version of openssl ${OPENSSL_VERSION} is no longer supported, or will soon cease to be supported: "
#                           "https://www.openssl.org/policies/releasestrat.html")
#endif()

set(BOOST_ROOT "D:/boost_1_82_0/boost_mingw_810_x64")
if(NOT(EXISTS ${BOOST_ROOT}))
    message(FATAL_ERROR "Set the correct BOOST_ROOT in the cmake lists")
endif()

FIND_PACKAGE( Boost REQUIRED )
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIR}")
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( "D:/OpenSSL-Win32/include/" )

set(GMOD_MODULE_BASE_DIR "D:/repositories/gmod-module-base-development")
if(NOT(EXISTS ${GMOD_MODULE_BASE_DIR}))
    message(FATAL_ERROR "Set the correct GMOD_MODULE_BASE_DIR in the cmake lists")
endif()

add_subdirectory(${GMOD_MODULE_BASE_DIR}/include ${GMOD_MODULE_BASE_DIR}/include/build)
target_link_libraries(${PROJECT_NAME} ws2_32)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} "D:/OpenSSL-Win32/lib/libcrypto.lib" "D:/OpenSSL-Win32/lib/libssl.lib")
target_link_libraries(${PROJECT_NAME} gmod-module-base)

set_gmod_suffix_prefix(${PROJECT_NAME})

