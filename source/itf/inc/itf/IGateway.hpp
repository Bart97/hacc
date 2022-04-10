#pragma once
#include <string>

namespace device
{
class IDevice;
} // namespace device

namespace gateway
{
class IGateway
{
public:
    virtual ~IGateway() = default;

    virtual std::shared_ptr<device::IDevice> getDeviceById() = 0;
    virtual std::shared_ptr<device::IDevice> getDeviceByName(const std::string&) = 0;
};
} // namespace gateway
