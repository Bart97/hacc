find_package(PkgConfig REQUIRED)
include(find_jsoncpp.cmake)
add_subdirectory(googletest)
add_subdirectory(spdlog)

set(MQTT_BUILD_TESTS OFF)
set(MQTT_BUILD_EXAMPLES OFF)
add_subdirectory(mqtt_cpp)
