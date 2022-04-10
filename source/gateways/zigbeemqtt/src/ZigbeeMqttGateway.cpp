#include "gateway/zigbeemqtt/ZigbeeMqttGateway.hpp"

#include "gateway/zigbeemqtt/messages/Device.hpp"
#include <json/json.h>
#include "spdlog/spdlog.h"


namespace gateway::zigbeemqtt
{
ZigbeeMqttGateway::ZigbeeMqttGateway(std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient) : mqttClient(
        std::move(mqttClient))
{
    this->mqttClient->subscribe("zigbee2mqtt/bridge/devices", [](const auto& msg) { spdlog::info("Devices published! {}", msg.payload);});
}

std::shared_ptr<device::IDevice> ZigbeeMqttGateway::getDeviceById()
{
    return nullptr;
}

std::shared_ptr<device::IDevice> ZigbeeMqttGateway::getDeviceByName(const std::string& string)
{
    (void) string;
    return nullptr;
}
} // namespace gateway::zigbeemqtt
