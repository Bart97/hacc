#pragma once
#include <vector>
#include "itf/IDeviceManager.hpp"
#include "itf/IGateway.hpp"

namespace core
{
class DeviceManager : public IDeviceManager
{
public:
    DeviceManager();

    void addGateway(std::shared_ptr<gateway::IGateway>) override;

    std::shared_ptr<device::IDevice> getDeviceByName(const std::string& name) const override;
    device::DeviceRange getAllDevices() const override;

private:
    std::vector<std::shared_ptr<gateway::IGateway>> gateways;
};
} // namespace core
