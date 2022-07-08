#pragma once
#include <string>
#include <vector>
#include "device/DeviceRange.hpp"

namespace gateway
{
class IGateway
{
public:
    virtual ~IGateway() = default;

    virtual std::shared_ptr<device::IDevice> getDeviceById() = 0;
    virtual std::shared_ptr<device::IDevice> getDeviceByName(const std::string&) = 0;
    virtual device::DeviceRange getAllDevices() = 0;
};
} // namespace gateway
