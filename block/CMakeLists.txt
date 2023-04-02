cmake_minimum_required(VERSION 3.15)
project(HyperCraft)

set(CMAKE_CXX_STANDARD 17)

if (NOT TARGET hc::dep)
    add_subdirectory(../dep ../dep)
endif ()

file(GLOB BLOCK_TEXTURES texture/block/*.png)
file(GLOB MISC_TEXTURES texture/misc/*.png)

set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/internal/generated)

add_subdirectory(dep)

find_package(PNG)
if (PNG_FOUND)
    add_executable(HyperCraft_block_tex_gen generator/block_tex_gen.cpp register/blocks)
    target_link_libraries(HyperCraft_block_tex_gen PRIVATE hc::resource::dep hc::dep PNG::PNG)
    target_include_directories(HyperCraft_block_tex_gen PRIVATE internal)

    add_executable(HyperCraft_misc_tex_gen generator/misc_tex_gen.cpp)
    target_link_libraries(HyperCraft_misc_tex_gen PRIVATE hc::resource::dep hc::dep PNG::PNG)

    add_custom_command(
            OUTPUT ${GENERATED_DIR}/block_texture_png.inl
            OUTPUT ${GENERATED_DIR}/block_texture_transparency.inl
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/HyperCraft_block_tex_gen ${GENERATED_DIR}/block_texture_png.inl ${GENERATED_DIR}/block_texture_transparency.inl
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/texture/block/
            DEPENDS HyperCraft_block_tex_gen ${BLOCK_TEXTURES}
    )

    add_custom_command(
            OUTPUT ${GENERATED_DIR}/misc_texture_png.inl
            COMMAND ${CMAKE_CURRENT_BINARY_DIR}/HyperCraft_misc_tex_gen ${GENERATED_DIR}/misc_texture_png.inl
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/texture/misc/
            DEPENDS HyperCraft_misc_tex_gen ${MISC_TEXTURES}
    )
endif ()

add_library(HyperCraft_resource_header INTERFACE
        include/resource/block/BlockFace.hpp
        include/resource/block/BlockMesh.hpp
        include/resource/block/BlockProperty.hpp
        include/resource/texture/BlockTexture.hpp
        include/resource/texture/MiscTexture.hpp
        ${GENERATED_DIR}/block_texture_png.inl
        ${GENERATED_DIR}/block_texture_transparency.inl
        ${GENERATED_DIR}/misc_texture_png.inl
        )
add_library(hc::resource::header ALIAS HyperCraft_resource_header)
target_include_directories(HyperCraft_resource_header INTERFACE include internal)
target_link_libraries(HyperCraft_resource_header INTERFACE hc::dep)

add_library(HyperCraft_resource INTERFACE)
add_library(hc::resource ALIAS HyperCraft_resource)
target_link_libraries(HyperCraft_resource INTERFACE hc::resource::header hc::resource::dep)

