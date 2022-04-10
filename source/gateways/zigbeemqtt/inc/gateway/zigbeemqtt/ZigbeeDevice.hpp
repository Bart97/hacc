#pragma once
#include "device/IDevice.hpp"
#include "gateway/zigbeemqtt/messages/Device.hpp"

namespace gateway::zigbeemqtt
{
class ZigbeeDevice : public device::IDevice
{
public:
    ZigbeeDevice(const messages::Device& deviceInfo);
};
} // namespace gateway::zigbeemqtt
