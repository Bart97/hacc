#pragma once
#include <memory>
#include "itf/IGateway.hpp"
#include "protocol/mqtt/IMqttClient.hpp"

namespace gateway::zigbeemqtt
{
class ZigbeeMqttGateway: public IGateway
{
public:
    explicit ZigbeeMqttGateway(std::shared_ptr<protocol::mqtt::IMqttClient>);

    std::shared_ptr<device::IDevice> getDeviceById() override;
    std::shared_ptr<device::IDevice> getDeviceByName(const std::string& string) override;

private:
    std::shared_ptr<protocol::mqtt::IMqttClient> mqttClient;
};
} // namespace gateway::zigbeemqtt
