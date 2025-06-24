cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Thumos)

include(FetchContent)
###### THIRD PARTY LIBRARY INSTALATION

# How ts works
# We say what we want to process(libraries, source files etc) -> 
# We define the targets(libraries/executables that we want to create) ->
# We add include flags and library linking ->
# Profit
# 
message(STATUS "Downloading rapidjson")
# rapidjson
FetchContent_Declare(
    rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG master
)

set(RAPIDJSON_BUILD_DOC OFF CACHE INTERNAL "")
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(RAPIDJSON_BUILD_TESTS OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(rapidjson)


message(STATUS "Downloading asio")

# asio
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-34-2
)

FetchContent_MakeAvailable(asio)

message(STATUS "Downloading OpenSSL")
# OpenSSL

find_package(OpenSSL REQUIRED)

####### SOURCE FILE 
# SRC_FILES_UTILITY
file (GLOB_RECURSE SRC_FILES_UTILITY ${CMAKE_CURRENT_SOURCE_DIR}/src/Utility/*.cpp)

# SRC_FILES_FRAMEWORK
# Contains the files of: Core, Routing, HTTPInternal, HTTP Public API
file (GLOB_RECURSE SRC_FILES_FRAMEWORK 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Routing/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Web/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Detail/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Auth/*.cpp
)


#
### SRC_FILES_WEBRES_GENERATOR 
#
file (GLOB_RECURSE SRC_FILES_WEBRES_GENERATOR ${CMAKE_CURRENT_SOURCE_DIR}/src/AssetHelper/*.cpp)


add_subdirectory(Utility)
add_subdirectory(AssetHelper)

####### EXECUTABLES AND LIBRARY CREATION

add_library(Thumos STATIC ${SRC_FILES_FRAMEWORK})

######
target_compile_definitions(Thumos PRIVATE OPENSSL_API_COMPAT=0x10100000L)

### Contains actual framework and my own static libraries
target_include_directories(Thumos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Thumos PUBLIC ${rapidjson_SOURCE_DIR}/include)
target_include_directories(Thumos PUBLIC ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(Thumos PUBLIC ASIO_STANDALONE)
####### STATIC LINKING 

##### The Framework
###
#
# The framework depends on:
#   - my libraries: Utility
#   - thirdparty: Asio, OpenSSL, rapidjson 

# asio doesn't need to be linked because it's header only. It doesn't actually build into a library
target_link_libraries(Thumos PUBLIC Utility)
target_link_libraries(Thumos PUBLIC OpenSSL::SSL OpenSSL::Crypto)

add_subdirectory(examples)
