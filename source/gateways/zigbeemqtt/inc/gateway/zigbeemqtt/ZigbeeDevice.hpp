#pragma once
#include <boost/range/any_range.hpp>
#include <memory>
#include "device/ICapability.hpp"
#include "device/IDevice.hpp"
#include "gateway/zigbeemqtt/Capability.hpp"
#include "gateway/zigbeemqtt/configuration/Configuration.hpp"
#include "gateway/zigbeemqtt/messages/Device.hpp"
#include "protocol/mqtt/IMqttClient.hpp"

namespace gateway::zigbeemqtt
{
class ZigbeeDevice : public device::IDevice
{
public:
    ZigbeeDevice(
        const messages::Device&, const configuration::Configuration&, std::shared_ptr<protocol::mqtt::IMqttClient>);

    const std::string& getIdentifier() const override;

    bool isPresent() override;

    const device::Capabilities& getCapabilities() const override;

private:
    void onUpdate(const protocol::mqtt::PublishedMessage&);

    std::string ieeeAddress;
    std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient;
    device::Capabilities capabilities;
};
} // namespace gateway::zigbeemqtt
