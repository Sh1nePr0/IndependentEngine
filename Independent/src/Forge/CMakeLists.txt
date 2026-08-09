cmake_minimum_required(VERSION 3.16)

project(Forge)

add_executable(Forge
    Main.cpp
)

target_link_libraries(Forge
    PRIVATE 
        Independent
        ForgeQt 
)

independent_configure_target(Forge)
forge_configure_target(Forge)

set_property(DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT Forge)

if(WIN32)
    set(
        FORGE_WINDEPLOYQT
        "${INDEPENDENT_QT_ROOT}/bin/windeployqt.exe"
    )

    if(NOT EXISTS "${FORGE_WINDEPLOYQT}")
        message(FATAL_ERROR
            "windeployqt.exe was not found:\n"
            "  ${FORGE_WINDEPLOYQT}"
        )
    endif()

    add_custom_command(
        TARGET Forge
        POST_BUILD

        COMMAND
            "${FORGE_WINDEPLOYQT}"

            "$<$<CONFIG:Debug>:--debug>"
            "$<$<NOT:$<CONFIG:Debug>>:--release>"

            --force
            --verbose 1

            "$<TARGET_FILE:Forge>"

        COMMENT
            "Deploying Qt runtime dependencies for Forge"

        COMMAND_EXPAND_LISTS
        VERBATIM
    )
endif()
