#include <thread>
#include "core/DeviceManager.hpp"
#include "event/EventDispatcher.hpp"
#include "event/EventQueue.hpp"
#include "gateway/zigbeemqtt/ZigbeeMqttGateway.hpp"
#include "gateway/zigbeemqtt/ZigbeeMqttGatewayFactory.hpp"
#include "protocol/mqtt/MqttClient.hpp"
#include "protocol/mqtt/MqttWrapperFactory.hpp"
#include "services/metrics/MetricsService.hpp"
#include "spdlog/spdlog.h"
#include "timer/TimerManager.hpp"

namespace
{
const std::string mqttHost = "10.0.1.168";
constexpr std::uint16_t mqttPort = 1883;
} // namespace

int main()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Hello world!");

    event::EventQueue eventQueue{};
    event::EventDispatcher eventDispatcher{};

    timer::TimerManager timerManager{eventQueue, eventDispatcher};

    auto mqttWrapper = protocol::mqtt::createMqttWrapper("hacc", mqttHost, mqttPort);
    auto mqttClient = std::make_shared<protocol::mqtt::MqttClient>(mqttWrapper, eventDispatcher, eventQueue);

    core::DeviceManager deviceManager{};
    deviceManager.addGateway(gateway::zigbeemqtt::createZigbeeMqttGateway(mqttClient));
    metrics::MetricsService metricsService{timerManager, deviceManager};

    while (true)
    {
        eventDispatcher.dispatch(eventQueue.waitAndPop());
    }

    return 0;
}
