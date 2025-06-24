cmake_minimum_required(VERSION 3.10)

project(AuthServer)

set(CMAKE_CXX_STANDARD 20)

### SETTING UP DEPENDENCIES
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)


file(GLOB_RECURSE AUTH_SERVER_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(AuthServer ${AUTH_SERVER_SRC_FILES})

# adding the includes for the project
target_include_directories(AuthServer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# adding the includes for PostgreSQL
target_include_directories(AuthServer PRIVATE ${LIBPQXX_INCLUDE_DIRS})
target_include_directories(AuthServer PRIVATE ${rapidjson_INCLUDE_DIRS})

### LINKING
# PostgreSQL
target_link_libraries(AuthServer PRIVATE ${LIBPQXX_LIBRARIES})
target_link_libraries(AuthServer PUBLIC Thumos)



