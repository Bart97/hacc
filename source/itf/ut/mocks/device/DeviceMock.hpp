#pragma once
#include <gmock/gmock.h>
#include "device/IDevice.hpp"

namespace device
{
class DeviceMock : public IDevice
{
public:
    MOCK_CONST_METHOD0(getIdentifier, const std::string&());
    MOCK_METHOD0(isPresent, bool());
    MOCK_CONST_METHOD0(getCapabilities, Capabilities&());
};
} // namespace device
