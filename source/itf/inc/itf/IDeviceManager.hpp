#pragma once
#include <memory>
#include <string>
#include "device/DeviceRange.hpp"

namespace device
{
class IDevice;
} // namespace device

namespace gateway
{
class IGateway;
} // namespace gateway

namespace core
{
class IDeviceManager
{
public:
    virtual void addGateway(std::shared_ptr<gateway::IGateway>) = 0;

    virtual std::shared_ptr<device::IDevice> getDeviceByName(const std::string& name) const = 0;
    virtual device::DeviceRange getAllDevices() const = 0;
};
} // namespace core
