SET(TARGET_NAME zigbeemqtt)
set(TARGET_SOURCES
    src/configuration/ConfigurationLoader.cpp
    src/messages/Device.cpp
    src/ZigbeeDevice.cpp
    src/ZigbeeMqttGateway.cpp)
set(TARGET_HEADERS
    inc/gateway/zigbeemqtt/configuration/Configuration.hpp
    inc/gateway/zigbeemqtt/configuration/ConfigurationLoader.hpp
    inc/gateway/zigbeemqtt/configuration/IConfigurationLoader.hpp
    inc/gateway/zigbeemqtt/IDeviceFactory.hpp
    inc/gateway/zigbeemqtt/ZigbeeDevice.hpp
    inc/gateway/zigbeemqtt/ZigbeeMqttGateway.hpp)

add_library(${TARGET_NAME} ${TARGET_SOURCES} ${TARGET_HEADERS})
target_link_libraries(${TARGET_NAME}
        PUBLIC
            itf
            mqtt
            ${JSONCPP_LIBRARIES}
            spdlog::spdlog)
target_include_directories(${TARGET_NAME} PUBLIC inc)

add_subdirectory(ut)
