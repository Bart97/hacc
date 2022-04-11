#pragma once
#include <memory>
#include "gateway/zigbeemqtt/ZigbeeDevice.hpp"
#include "gateway/zigbeemqtt/messages/Device.hpp"

namespace gateway::zigbeemqtt
{
class IDeviceFactory
{
public:
    virtual ~IDeviceFactory() = default;
    virtual std::shared_ptr<ZigbeeDevice> createDevice(const messages::Device&) = 0;
};
} // namespace gateway::zigbeemqtt
