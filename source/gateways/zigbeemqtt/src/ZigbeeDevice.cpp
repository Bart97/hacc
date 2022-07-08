#include "gateway/zigbeemqtt/ZigbeeDevice.hpp"
#include "gateway/zigbeemqtt/Capability.hpp"
#include "spdlog/spdlog.h"

namespace gateway::zigbeemqtt
{
ZigbeeDevice::ZigbeeDevice(
    const messages::Device& deviceInfo,
    const configuration::Configuration& config,
    std::shared_ptr<protocol::mqtt::IMqttClient> _mqttClient)
    : ieeeAddress{deviceInfo.ieeeAddress}
    , mqttClient{std::move(_mqttClient)}
{
    for (const auto& configuredCapability : config.capabilityMappings)
    {
        capabilities.emplace_back(std::make_shared<Capability>(configuredCapability));
    }

    mqttClient->subscribe("zigbee2mqtt/" + ieeeAddress, [this](const auto& msg) { onUpdate(msg); });
}

const std::string& ZigbeeDevice::getIdentifier() const
{
    return ieeeAddress;
}

bool ZigbeeDevice::isPresent()
{
    return true;
}

void ZigbeeDevice::onUpdate(const protocol::mqtt::PublishedMessage& msg)
{
    spdlog::debug("Received update for device {}: {}", ieeeAddress, msg.payload);
    for (auto capability : capabilities)
    {
        spdlog::debug("Updating capability {} for device {}", capability->getName(), ieeeAddress);
        std::dynamic_pointer_cast<Capability>(capability)->onUpdate(msg);
    }
}

const device::Capabilities& ZigbeeDevice::getCapabilities() const
{
    return capabilities;
}
} // namespace gateway::zigbeemqtt
