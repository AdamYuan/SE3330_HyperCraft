cmake_minimum_required(VERSION 3.15)
project(HyperCraft)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dep)
if (NOT TARGET HyperCraft_common)
    add_subdirectory(../common ../common)
endif ()

add_executable(HyperCraft_server
        src/main.cpp
        src/ENetServer.cpp
        include/server/ENetServer.hpp
        )

target_link_libraries(HyperCraft_server PRIVATE server_dep HyperCraft_common)
target_include_directories(HyperCraft_server PRIVATE include)
