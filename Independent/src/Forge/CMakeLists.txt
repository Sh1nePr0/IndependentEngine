cmake_minimum_required(VERSION 3.16)

project(Forge)

set(QT_FORCE_STATIC ON)
set(BUILD_SHARED_LIBS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

add_executable(Forge
)

target_link_libraries(Forge
    PRIVATE Qt6::Widgets
    PUBLIC Independent 
)

target_include_directories(Forge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})