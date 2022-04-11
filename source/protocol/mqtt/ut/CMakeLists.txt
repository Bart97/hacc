set(TEST_SOURCES
    src/MqttClientTest.cpp)

add_executable(${TARGET_NAME}_ut ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME}_ut
    ${TARGET_NAME}
    ${TARGET_NAME}_mock
    gtest_main
    gmock)

set(MOCKS
    mocks/protocol/mqtt/mocks/MqttWrapperMock.hpp mocks/protocol/mqtt/mocks/MqttClientMock.hpp)

add_library(${TARGET_NAME}_mock INTERFACE ${MOCKS})
target_include_directories(${TARGET_NAME}_mock INTERFACE mocks)
target_link_libraries(${TARGET_NAME}_mock INTERFACE ${TARGET_NAME} gmock )
