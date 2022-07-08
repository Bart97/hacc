#include "core/DeviceManager.hpp"
#include <boost/range/join.hpp>

namespace core
{
DeviceManager::DeviceManager() { }

void DeviceManager::addGateway(std::shared_ptr<gateway::IGateway> gateway)
{
    gateways.emplace_back(std::move(gateway));
}

std::shared_ptr<device::IDevice> DeviceManager::getDeviceByName(const std::string& name) const
{
    for (const auto& gateway : gateways)
    {
        if (auto device = gateway->getDeviceByName(name); device)
        {
            return device;
        }
    }
    return nullptr;
}

device::DeviceRange DeviceManager::getAllDevices() const
{
    device::DeviceRange allDeviceRange{};
    for (const auto& gateway : gateways)
    {
        allDeviceRange = boost::range::join(allDeviceRange, gateway->getAllDevices());
    }
    return allDeviceRange;
}
} // namespace core
