cmake_minimum_required(VERSION 3.10)
project(HACC CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_VERBOSE_MAKEFILE ON)
set(MQTT_BUILD_TESTS OFF)
set(MQTT_BUILD_EXAMPLES OFF)
enable_testing()
add_compile_options(-Wall -Wextra -pedantic -Werror)

add_subdirectory(deps)

include(cmake/testing.cmake)

add_subdirectory(source)

#SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost 1.60 COMPONENTS system REQUIRED)

add_executable(hacc $<TARGET_OBJECTS:startup>)

target_link_libraries(hacc startup Boost::system)

include(cmake/format.cmake)

#SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_CLANG_TIDY
#    clang-tidy;
#    -header-filter=.;
#    -checks=*;
#    -warnings-as-errors=*;)
#--format-style=file --header-filter=. -p ${CMAKE_CURRENT_BINARY_DIR}
