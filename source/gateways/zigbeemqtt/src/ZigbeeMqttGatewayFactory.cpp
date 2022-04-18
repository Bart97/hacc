#include "gateway/zigbeemqtt/ZigbeeMqttGatewayFactory.hpp"
#include "gateway/zigbeemqtt/configuration/ConfigurationLoader.hpp"
#include "gateway/zigbeemqtt/DeviceFactory.hpp"
#include "gateway/zigbeemqtt/ZigbeeMqttGateway.hpp"

namespace gateway::zigbeemqtt
{
std::shared_ptr<gateway::IGateway> createZigbeeMqttGateway(std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient)
{
    return std::make_shared<ZigbeeMqttGateway>(
            mqttClient,
            std::make_unique<DeviceFactory>(
                    std::make_unique<configuration::ConfigurationLoader>(), mqttClient));
}
} // namespace gateway::zigbeemqtt
