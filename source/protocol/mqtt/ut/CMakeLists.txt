
set(TEST_SOURCES
    src/MqttClientTest.cpp)

add_executable(${TARGET_NAME}_ut ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME}_ut ${TARGET_NAME} gtest_main gmock)