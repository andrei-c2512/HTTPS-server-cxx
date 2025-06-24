cmake_minimum_required(VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
project(AssetHelper)

file(GLOB_RECURSE SRC_FILES_GENERATOR ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(AssetHelper ${SRC_FILES_GENERATOR})

target_link_libraries(AssetHelper PUBLIC Utility)

target_include_directories(AssetHelper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
