cmake_minimum_required(VERSION 3.10)
project(Utility)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES_UTILITY src/*.cpp)

add_library(Utility ${SRC_FILES_UTILITY})

target_link_libraries(Utility PRIVATE OpenSSL::SSL OpenSSL::Crypto)

target_include_directories(Utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(Utility PUBLIC ${rapidjson_SOURCE_DIR}/include)
target_include_directories(Utility PUBLIC ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(Utility PUBLIC ASIO_STANDALONE)
target_compile_definitions(Utility PRIVATE OPENSSL_API_COMPAT=0x10100000L)
