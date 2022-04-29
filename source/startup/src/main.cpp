#include <thread>
#include "gateway/zigbeemqtt/ZigbeeMqttGateway.hpp"
#include "gateway/zigbeemqtt/ZigbeeMqttGatewayFactory.hpp"
#include "protocol/mqtt/MqttClient.hpp"
#include "protocol/mqtt/MqttWrapperFactory.hpp"
#include "spdlog/spdlog.h"

namespace
{
const std::string mqttHost = "10.0.1.168";
constexpr std::uint16_t mqttPort = 1883;
} // namespace

int main()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Hello world!");
    auto mqttWrapper = protocol::mqtt::createMqttWrapper("hacc", mqttHost, mqttPort);
    auto mqttClient = std::make_shared<protocol::mqtt::MqttClient>(mqttWrapper);

    auto zigbeeGateway = gateway::zigbeemqtt::createZigbeeMqttGateway(mqttClient);

    while (true)
    {
        mqttClient->processMessages();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    return 0;
}