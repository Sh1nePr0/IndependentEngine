project(Independent LANGUAGES CXX)

add_subdirectory(vendor)

file(GLOB_RECURSE INDEPENDENT_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

file(GLOB_RECURSE INDEPENDENT_VENDOR_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.h
)

add_library(Independent STATIC 
    ${INDEPENDENT_SRC}
    ${INDEPENDENT_VENDOR_SRC}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src FILES ${INDEPENDENT_SRC})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/vendor FILES ${INDEPENDENT_VENDOR_SRC})

target_compile_features(Independent PUBLIC cxx_std_17)
target_compile_options(Independent PRIVATE "/utf-8")

set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
set(STB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)

target_include_directories(Independent PUBLIC
    ${SPDLOG_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Independent
    PRIVATE glfw Glad ImGui opengl32
)

target_compile_definitions(Independent PRIVATE
    _CRT_SECURE_NO_WARNINGS
    IDPD_BUILD_DLL
    GLFW_INCLUDE_NONE
    $<$<CONFIG:Debug>:IDPD_DEBUG>
    $<$<CONFIG:Release>:IDPD_RELEASE>
    $<$<CONFIG:Dist>:IDPD_DIST>
)