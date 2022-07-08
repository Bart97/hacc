#pragma once
#include <gmock/gmock.h>
#include "itf/IDeviceManager.hpp"

namespace core
{
class DeviceManagerMock : public IDeviceManager
{
public:
    MOCK_METHOD1(addGateway, void(std::shared_ptr<gateway::IGateway>));
    MOCK_CONST_METHOD1(getDeviceByName, std::shared_ptr<device::IDevice>(const std::string&));
    MOCK_CONST_METHOD0(getAllDevices, device::DeviceRange());
};
} // namespace core
