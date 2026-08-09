#
# Independent.cmake
#

function(independent_configure_target TARGET)

    target_compile_features(${TARGET}
        PUBLIC cxx_std_17
    )

    if(MSVC)
        target_compile_options(${TARGET}
            PRIVATE
                /MP

        )
    endif()

endfunction()