#pragma once
#include <memory>
#include "device/ICapability.hpp"
#include "device/IDevice.hpp"
#include "gateway/zigbeemqtt/messages/Device.hpp"
#include "gateway/zigbeemqtt/configuration/Configuration.hpp"
#include "gateway/zigbeemqtt/Capability.hpp"
#include "protocol/mqtt/IMqttClient.hpp"
#include <boost/range/any_range.hpp>

namespace gateway::zigbeemqtt
{
class ZigbeeDevice : public device::IDevice
{
public:
    ZigbeeDevice(const messages::Device&,
                 const configuration::Configuration&,
                 std::shared_ptr<protocol::mqtt::IMqttClient>);

    const std::string& getIdentifier() const override;

    bool isPresent() override;

    const std::vector<std::shared_ptr<device::ICapability>>& getCapabilities() const;

private:
    void onUpdate(const protocol::mqtt::PublishedMessage&);

    std::string ieeeAddress;
    std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient;
    std::vector<std::shared_ptr<device::ICapability>> capabilities;
};
} // namespace gateway::zigbeemqtt
