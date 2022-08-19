SET(TARGET_NAME itf)
set(TARGET_HEADERS
    inc/itf/IDeviceManager.hpp
    inc/itf/IGateway.hpp
    inc/device/CapabilityType.hpp
    inc/device/DeviceRange.hpp
    inc/device/ICapability.hpp
    inc/device/IDevice.hpp
    inc/device/SensorType.hpp
    inc/util/Timestamp.hpp)

set(TARGET_SOURCES
    src/device/CapabilityType.cpp
    src/device/SensorType.cpp)

add_library(${TARGET_NAME} STATIC ${TARGET_HEADERS} ${TARGET_SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC inc)

add_subdirectory(ut)
