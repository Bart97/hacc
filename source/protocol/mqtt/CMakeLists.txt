SET(TARGET_NAME mqtt)
SET(TARGET_SOURCES
    src/MqttClient.cpp
    src/MqttWrapper.cpp
    src/MqttWrapperFactory.cpp
    src/PublishedMessage.cpp)
SET(TARGET_HEADERS
    inc/protocol/mqtt/IMqttClient.hpp
    inc/protocol/mqtt/IMqttWrapper.hpp
    inc/protocol/mqtt/MqttClient.hpp
    inc/protocol/mqtt/MqttWrapper.hpp
    inc/protocol/mqtt/MqttWrapperFactory.hpp
    inc/protocol/mqtt/PublishCallback.hpp
    inc/protocol/mqtt/PublishedMessage.hpp
    inc/protocol/mqtt/Qos.hpp
    inc/protocol/mqtt/events/MqttMessagePublishedEvent.hpp)

add_library(${TARGET_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})
target_include_directories(${TARGET_NAME} PUBLIC inc)

#find_package(mqtt_cpp_iface REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${TARGET_NAME} PUBLIC event)
target_link_libraries(${TARGET_NAME} LINK_PUBLIC mqtt_cpp_iface)

add_subdirectory(ut)
