#
# Qt.cmake
#

include_guard(GLOBAL)

option(
    INDEPENDENT_USE_SYSTEM_QT
    "Search for Qt in system paths instead of vendor/Qt"
    OFF
)

set(
    INDEPENDENT_QT_ROOT
    "${CMAKE_SOURCE_DIR}/Independent/vendor/Qt/6.11.1/msvc2022_64"
    CACHE PATH
    "Path to the Qt kit root"
)

if(NOT INDEPENDENT_USE_SYSTEM_QT)
    set(_qt_config_file
        "${INDEPENDENT_QT_ROOT}/lib/cmake/Qt6/Qt6Config.cmake"
    )

    if(NOT EXISTS "${_qt_config_file}")
        message(FATAL_ERROR
            "Qt was not found.\n"
            "Expected file:\n"
            "  ${_qt_config_file}\n\n"
            "Install Qt MSVC 2022 64-bit into vendor/Qt or configure with:\n"
            "  -DINDEPENDENT_QT_ROOT=<path-to-qt-kit>"
        )
    endif()

    set(Qt6_ROOT "${INDEPENDENT_QT_ROOT}")
endif()

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "Qt root: ${INDEPENDENT_QT_ROOT}")
message(STATUS "Qt6_DIR: ${Qt6_DIR}")

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    OpenGL
    OpenGLWidgets
)

qt_standard_project_setup()