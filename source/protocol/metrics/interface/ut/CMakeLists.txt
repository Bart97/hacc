set(TEST_SOURCES
    )

#add_executable(${TARGET_NAME}_ut ${TEST_SOURCES})
#add_test(NAME ${TARGET_NAME}_ut COMMAND ${TARGET_NAME}_ut)
#add_dependencies(${UT_BUILD_TARGET} ${TARGET_NAME}_ut)
#target_link_libraries(${TARGET_NAME}_ut
#    ${TARGET_NAME}
#    ${TARGET_NAME}_mock
#    event_mock
#    gtest_main
#    gmock)

set(MOCKS
    mocks/protocol/metrics/MetricsServerMock.hpp)

add_library(${TARGET_NAME}_mock INTERFACE ${MOCKS})
target_include_directories(${TARGET_NAME}_mock INTERFACE mocks)
target_link_libraries(${TARGET_NAME}_mock INTERFACE ${TARGET_NAME} gmock)
