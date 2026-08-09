cmake_minimum_required(VERSION 3.20)
project(Independent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake/modules"
)

include(${CMAKE_SOURCE_DIR}/Independent/cmake/modules/Independent.cmake)
include(${CMAKE_SOURCE_DIR}/Independent/cmake/modules/Forge.cmake)
include(${CMAKE_SOURCE_DIR}/Independent/cmake/modules/Qt.cmake)

add_subdirectory(Independent)
add_subdirectory(TestingProject)