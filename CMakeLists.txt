cmake_minimum_required(VERSION 3.10)
project(HACC)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps)
add_subdirectory(source)

#SET(Boost_USE_STATIC_LIBS ON)
#FIND_PACKAGE(Boost 1.54 COMPONENTS log REQUIRED)

add_executable(hacc $<TARGET_OBJECTS:startup>)

target_link_libraries(hacc startup)
