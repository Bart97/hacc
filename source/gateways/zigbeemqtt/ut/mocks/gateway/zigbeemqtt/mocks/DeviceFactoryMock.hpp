#pragma once
#include <gmock/gmock.h>
#include "gateway/zigbeemqtt/IDeviceFactory.hpp"

namespace gateway::zigbeemqtt
{
class DeviceFactoryMock : public IDeviceFactory
{
public:
    MOCK_METHOD1(createDevice, std::shared_ptr<ZigbeeDevice>(const messages::Device&));
};
} // namespace gateway::zigbeemqtt
