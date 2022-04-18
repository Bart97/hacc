set(TEST_SOURCES
    src/messages/DeviceDeserializerTest.cpp
    src/CapabilityTest.cpp
    src/ZigbeeDeviceTest.cpp
    src/ZigbeeMqttGatewayTest.cpp)

add_executable(${TARGET_NAME}_ut ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME}_ut
    ${TARGET_NAME}_mock
    ${TARGET_NAME}
    mqtt_mock
    gtest_main
    gmock)

set(MOCKS
    mocks/gateway/zigbeemqtt/mocks/ConfigurationLoaderMock.hpp
    mocks/gateway/zigbeemqtt/mocks/DeviceFactoryMock.hpp)

add_library(${TARGET_NAME}_mock INTERFACE ${MOCKS})
target_include_directories(${TARGET_NAME}_mock INTERFACE mocks)
target_link_libraries(${TARGET_NAME}_mock INTERFACE ${TARGET_NAME} gmock )
