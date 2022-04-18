set(TARGET_HEADERS
    inc/itf/IGateway.hpp
    inc/device/CapabilityType.hpp
    inc/device/ICapability.hpp
    inc/device/IDevice.hpp
    inc/device/SensorType.hpp)

set(TARGET_SOURCES
    src/device/CapabilityType.cpp
    src/device/SensorType.cpp)

add_library(itf ${TARGET_HEADERS} ${TARGET_SOURCES})
target_include_directories(itf PUBLIC inc)