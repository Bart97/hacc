cmake_minimum_required(VERSION 3.10)
project(hacc)

set(CMAKE_CXX_STANDARD 14)

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost 1.54 COMPONENTS log REQUIRED)

add_executable(hacc main.cpp src/HaccCore.cpp src/HaccCore.h)
target_link_libraries(hacc Boost::log_setup Boost::log)
