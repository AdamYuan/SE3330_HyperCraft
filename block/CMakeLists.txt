cmake_minimum_required(VERSION 3.15)
project(HyperCraft)

set(CMAKE_CXX_STANDARD 20)

if (NOT TARGET hc::dep)
    add_subdirectory(../dep ../dep)
endif ()
if (NOT TARGET hc::texture::block)
    add_subdirectory(../texture ../texture)
endif ()

file(GLOB BLOCK_DEFS block/*.hpp block/public/*)

set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/internal/)

add_executable(HyperCraft_block_gen
        generator/block_gen.cpp
        register/blocks
        block/public/Trait.hpp
        )
target_link_libraries(HyperCraft_block_gen PRIVATE hc::texture::block hc::dep)

add_custom_command(
        OUTPUT ${GENERATED_DIR}/block/Block.hpp
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/HyperCraft_block_gen ${GENERATED_DIR}/block/Block.hpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/generator
        DEPENDS HyperCraft_block_gen generator/Block.hpp.in ${BLOCK_DEFS}
)

add_library(HyperCraft_block INTERFACE
        include/block/BlockFace.hpp
        include/block/BlockMesh.hpp
        include/block/BlockProperty.hpp
        ${GENERATED_DIR}/block/Block.hpp
        )
add_library(hc::block ALIAS HyperCraft_block)
target_include_directories(HyperCraft_block INTERFACE include ${GENERATED_DIR})
target_link_libraries(HyperCraft_block INTERFACE hc::texture::block)
