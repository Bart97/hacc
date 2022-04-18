#include "gateway/zigbeemqtt/ZigbeeMqttGateway.hpp"

#include <json/json.h>
#include "spdlog/spdlog.h"


namespace gateway::zigbeemqtt
{
ZigbeeMqttGateway::ZigbeeMqttGateway(
        std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient,
        std::unique_ptr<IDeviceFactory> deviceFactory) :
    mqttClient(std::move(mqttClient)), deviceFactory(std::move(deviceFactory))
{
    this->mqttClient->subscribe("zigbee2mqtt/bridge/devices", [this](const auto& msg) {
        this->onConfigurationChanged(messages::deserializeDevices(msg.payload));
        spdlog::info("Devices published! {}", msg.payload);});
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

void ZigbeeMqttGateway::onConfigurationChanged(const messages::Devices& newDevices)
{
    for (const auto& device: newDevices)
    {
        if (std::find_if(
                devices.begin(), devices.end(),
                [&id = device.ieeeAddress](const auto& dev) { return dev->getIdentifier() == id;}) == std::end(devices))
        {
            spdlog::info("Detected new device: {}", device.ieeeAddress);
            if (auto newDevice = deviceFactory->createDevice(device))
            {
                spdlog::info("Created a new device {}", newDevice->getIdentifier());
                devices.emplace_back(std::move(newDevice));
            }
            else
            {
                spdlog::error("Could not create a new device for {}", device.ieeeAddress);
            }
        }
    }
}
} // namespace gateway::zigbeemqtt
