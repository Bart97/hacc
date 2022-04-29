#pragma once
#include <string>
#include <vector>

namespace gateway::zigbeemqtt::messages
{
enum class DeviceType : std::uint8_t
{
    Coordinator,
    Router,
    EndDevice
};

struct Device
{
    std::string friendlyName;
    std::string ieeeAddress;
    std::string manufacturer;
    std::string modelId;
    DeviceType type;
};

using Devices = std::vector<Device>;

Devices deserializeDevices(const std::string&);
} // namespace gateway::zigbeemqtt::messages
