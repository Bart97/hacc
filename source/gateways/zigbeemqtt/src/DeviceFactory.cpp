#include "gateway/zigbeemqtt/DeviceFactory.hpp"

#include <utility>

namespace gateway::zigbeemqtt
{

DeviceFactory::DeviceFactory(std::unique_ptr<configuration::IConfigurationLoader> configurationLoader,
                             std::shared_ptr<protocol::mqtt::IMqttClient> _mqttClient)
    : configurationLoader(std::move(configurationLoader)), mqttClient(std::move(_mqttClient))
{

}

std::shared_ptr<ZigbeeDevice> DeviceFactory::createDevice(const messages::Device& deviceInfo)
{
    if (const auto configuration = configurationLoader->getConfiguration(deviceInfo.manufacturer, deviceInfo.modelId))
    {
        return std::make_shared<ZigbeeDevice>(deviceInfo, *configuration, mqttClient);
    }
    return nullptr;
}
} // namespace gateway::zigbeemqtt
