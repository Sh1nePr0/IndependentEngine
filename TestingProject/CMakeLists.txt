project(TestingProject LANGUAGES CXX)

file(GLOB_RECURSE TESTING_SRC
    src/*.cpp
    src/*.h
)

add_executable(TestingProject ${TESTING_SRC})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${TESTING_SRC})

target_compile_features(TestingProject PUBLIC cxx_std_17)
target_compile_options(TestingProject PRIVATE "/utf-8")

target_include_directories(TestingProject PRIVATE
    ${CMAKE_SOURCE_DIR}/Independent/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/Independent/src
    ${CMAKE_SOURCE_DIR}/Independent/vendor
    ${CMAKE_SOURCE_DIR}/Independent/vendor/glm
)

target_link_libraries(TestingProject PRIVATE Independent)

target_compile_definitions(TestingProject PRIVATE
    $<$<CONFIG:Debug>:IDPD_DEBUG>
    $<$<CONFIG:Release>:IDPD_RELEASE>
    $<$<CONFIG:Dist>:IDPD_DIST>
)

add_custom_command(TARGET TestingProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TestingProject>/assets
)

set_target_properties(TestingProject PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:TestingProject>"
)