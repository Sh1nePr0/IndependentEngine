cmake_minimum_required(VERSION 3.10)
project(ImGui LANGUAGES CXX)

file(GLOB IMGUI_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(ImGui STATIC ${IMGUI_SRC})

target_include_directories(ImGui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
    ${CMAKE_SOURCE_DIR}/Independent/vendor/GLFW/include 
)

target_link_libraries(ImGui PUBLIC glfw)