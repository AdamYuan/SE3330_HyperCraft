cmake_minimum_required(VERSION 3.15)
project(HyperCraft)

set(CMAKE_CXX_STANDARD 20)

if (NOT TARGET HyperCraft_resource)
    add_subdirectory(../resource ../resource)
endif ()

add_library(HyperCraft_common_header INTERFACE)
target_include_directories(HyperCraft_common_header INTERFACE include dep)

add_library(HyperCraft_common STATIC
        include/common/Endian.hpp
        include/common/Block.hpp
        include/common/BlockMesh.hpp
        include/common/BlockFace.hpp
        include/common/Light.hpp
        include/common/Message.hpp
        include/common/ByteStream.hpp
        src/WorldDatabase.cpp
        include/common/WorldDatabase.hpp
        include/common/AABB.hpp
        include/common/Position.hpp
        include/common/Biome.hpp
        include/common/Size.hpp
        )

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if (IS_BIG_ENDIAN)
    target_compile_definitions(HyperCraft_common_header INTERFACE IS_BIG_ENDIAN)
    target_compile_definitions(HyperCraft_common PUBLIC IS_BIG_ENDIAN)
    message(STATUS "Endianness: Big")
endif ()

add_subdirectory(dep)
find_package(Threads REQUIRED)

target_link_libraries(HyperCraft_common PUBLIC common_dep Threads::Threads PRIVATE HyperCraft_resource_header)
target_include_directories(HyperCraft_common PUBLIC include)
