cmake_minimum_required(VERSION 3.15)
project(HyperCraft)

set(CMAKE_CXX_STANDARD 20)

if (NOT TARGET hc::dep)
    add_subdirectory(../dep ../dep)
endif ()
if (NOT TARGET hc::texture::block)
    add_subdirectory(../texture ../texture)
endif ()

set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/internal/generated)

add_executable(HyperCraft_block_gen
        generator/block_gen.cpp
        register/blocks
        block/public/Trait.hpp
        )
target_link_libraries(HyperCraft_block_gen PRIVATE hc::texture::block hc::dep)

add_library(HyperCraft_block INTERFACE
        include/block/BlockFace.hpp
        include/block/BlockMesh.hpp
        include/block/BlockProperty.hpp
        )
add_library(hc::block ALIAS HyperCraft_block)
target_include_directories(HyperCraft_block INTERFACE include internal)
target_link_libraries(HyperCraft_block INTERFACE hc::texture::block)
