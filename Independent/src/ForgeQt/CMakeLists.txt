project(ForgeQt)

add_library(ForgeQt STATIC)

target_sources(ForgeQt
    PRIVATE
        src/Core/Application.cpp
        src/UI/EditorWindow.cpp

        src/Backend/Qt/ApplicationBackend.h
        src/Backend/Qt/ApplicationBackend.cpp

        src/Backend/Qt/EditorWindowBackend.h
        src/Backend/Qt/EditorWindowBackend.cpp

    PUBLIC
        include/ForgeQt/Core/Application.h

        include/ForgeQt/UI/EditorWindow.h
        include/ForgeQt/UI/DockArea.h
)

target_include_directories(ForgeQt
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(ForgeQt
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

independent_configure_target(ForgeQt)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PREFIX "Public"
    FILES
        include/ForgeQt/Core/Application.h
        include/ForgeQt/UI/EditorWindow.h
)

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
    PREFIX "Private"
    FILES
        src/Core/Application.cpp
        src/UI/EditorWindow.cpp
        src/Backend/Qt/ApplicationBackend.h
        src/Backend/Qt/ApplicationBackend.cpp
        src/Backend/Qt/EditorWindowBackend.h
        src/Backend/Qt/EditorWindowBackend.cpp
)

