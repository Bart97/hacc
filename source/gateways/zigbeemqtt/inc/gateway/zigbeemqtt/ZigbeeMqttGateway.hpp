#pragma once
#include <memory>
#include "itf/IGateway.hpp"
#include "protocol/mqtt/IMqttClient.hpp"
#include "gateway/zigbeemqtt/messages/Device.hpp"
#include "gateway/zigbeemqtt/IDeviceFactory.hpp"
#include "gateway/zigbeemqtt/ZigbeeDevice.hpp"

namespace gateway::zigbeemqtt
{
class ZigbeeMqttGateway: public IGateway
{
public:
    explicit ZigbeeMqttGateway(
            std::shared_ptr<protocol::mqtt::IMqttClient>,
            std::unique_ptr<IDeviceFactory>);

    std::shared_ptr<device::IDevice> getDeviceById() override;
    std::shared_ptr<device::IDevice> getDeviceByName(const std::string& string) override;

private:
    void onConfigurationChanged(const messages::Devices& newDevices);

    std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient;
    std::vector<std::shared_ptr<ZigbeeDevice>> devices;
    std::unique_ptr<IDeviceFactory> deviceFactory;
};
} // namespace gateway::zigbeemqtt
