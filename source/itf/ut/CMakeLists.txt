set(MOCKS
    mocks/device/DeviceMock.hpp
    mocks/itf/DeviceManagerMock.hpp
    mocks/itf/GatewayMock.hpp)

add_library(${TARGET_NAME}_mock INTERFACE ${MOCKS})
target_include_directories(${TARGET_NAME}_mock INTERFACE mocks)
target_link_libraries(${TARGET_NAME}_mock INTERFACE ${TARGET_NAME} gmock )
