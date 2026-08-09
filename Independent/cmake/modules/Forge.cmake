#
# Forge.cmake
#

function(forge_configure_target TARGET)

    target_compile_definitions(${TARGET}
        PRIVATE
            FORGE_APPLICATION
    )

endfunction()