set(TEST_SOURCES
    src/EventCallbackWrapperTest.cpp
    src/EventDispatcherTest.cpp
    src/EventWrapperTest.cpp
    inc/TestEvent.hpp)

add_executable(${TARGET_NAME}_ut ${TEST_SOURCES})
target_link_libraries(${TARGET_NAME}_ut
#    ${TARGET_NAME}_mock
    ${TARGET_NAME}
    gtest_main
    gmock)
target_include_directories(${TARGET_NAME}_ut PUBLIC inc)

set(MOCKS
#    mocks/
    )

#add_library(${TARGET_NAME}_mock INTERFACE ${MOCKS})
#target_include_directories(${TARGET_NAME}_mock INTERFACE mocks)
#target_link_libraries(${TARGET_NAME}_mock INTERFACE ${TARGET_NAME} gmock )
