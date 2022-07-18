#pragma once
#include <gmock/gmock.h>
#include "device/ICapability.hpp"

namespace device
{
class CapabilityMock : public ICapability
{
public:
    MOCK_CONST_METHOD0(getValue, double());
    MOCK_CONST_METHOD0(getType, CapabilityType());
    MOCK_CONST_METHOD0(getSubType, SensorType());
    MOCK_METHOD0(getName, const std::string&());
};
} // namespace device
