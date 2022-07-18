set(TEST_SOURCES
    src/MetricsServiceTest.cpp)

add_executable(${TARGET_NAME}_ut ${TEST_SOURCES})
add_test(NAME ${TARGET_NAME}_ut COMMAND ${TARGET_NAME}_ut)
add_dependencies(${UT_BUILD_TARGET} ${TARGET_NAME}_ut)
target_link_libraries(${TARGET_NAME}_ut
#    ${TARGET_NAME}_mock
    ${TARGET_NAME}
    itf_mock
    timer_mock
    protocol_metrics_interface_mock
    gtest_main
    gmock)

#set(MOCKS
#    mocks/gateway/zigbeemqtt/mocks/ConfigurationLoaderMock.hpp
#    mocks/gateway/zigbeemqtt/mocks/DeviceFactoryMock.hpp)
#
#add_library(${TARGET_NAME}_mock INTERFACE ${MOCKS})
#target_include_directories(${TARGET_NAME}_mock INTERFACE mocks)
#target_link_libraries(${TARGET_NAME}_mock INTERFACE ${TARGET_NAME} gmock )
