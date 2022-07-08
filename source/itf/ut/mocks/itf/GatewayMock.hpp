#pragma once
#include <gmock/gmock.h>
#include "itf/IGateway.hpp"

namespace gateway
{
class GatewayMock : public IGateway
{
public:
    MOCK_METHOD0(getDeviceById, std::shared_ptr<device::IDevice>());
    MOCK_METHOD1(getDeviceByName, std::shared_ptr<device::IDevice>(const std::string&));
    MOCK_METHOD0(getAllDevices, device::DeviceRange());
};
} // namespace gateway
