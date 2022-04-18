#pragma once
#include "gateway/zigbeemqtt/IDeviceFactory.hpp"
#include "gateway/zigbeemqtt/configuration/IConfigurationLoader.hpp"

namespace protocol::mqtt
{
class IMqttClient;
} // namespace protocol::mqtt

namespace gateway::zigbeemqtt
{
class DeviceFactory final : public IDeviceFactory
{
public:
    DeviceFactory(std::unique_ptr<configuration::IConfigurationLoader>, std::shared_ptr<protocol::mqtt::IMqttClient>);
    std::shared_ptr<ZigbeeDevice> createDevice(const messages::Device&) override;

private:
    std::unique_ptr<configuration::IConfigurationLoader> configurationLoader;
    std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient;
};
} // namespace gateway::zigbeemqtt
