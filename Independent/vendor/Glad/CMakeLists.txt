cmake_minimum_required(VERSION 3.10)
project(Glad LANGUAGES C)

add_library(Glad STATIC src/glad.c)
target_include_directories(Glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)