#include <thread>
#include "config/ConfigFile.hpp"
#include "core/DeviceManager.hpp"
#include "event/EventDispatcher.hpp"
#include "event/EventQueue.hpp"
#include "gateway/zigbeemqtt/ZigbeeMqttGateway.hpp"
#include "gateway/zigbeemqtt/ZigbeeMqttGatewayFactory.hpp"
#include "protocol/http/HttpRequestFactory.hpp"
#include "protocol/metrics/InfluxdbMetricsServerFactory.hpp"
#include "protocol/mqtt/MqttClient.hpp"
#include "protocol/mqtt/MqttWrapperFactory.hpp"
#include "services/metrics/MetricsService.hpp"
#include "spdlog/spdlog.h"
#include "timer/TimerManager.hpp"

namespace
{
std::string getConfigFilename(const int argc, const char* argv[])
{
    const std::string defaultConfigFile{"config.json"};

    if (argc > 1)
    {
        return argv[1];
    }

    return defaultConfigFile;
}

#ifdef DEBUG
std::string mqttClientId{"hacc-debug"};
#else
std::string mqttClientId{"hacc"};
#endif
} // namespace

int main(const int argc, const char* argv[])
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Hello world!");

    const std::string configFilename{getConfigFilename(argc, argv)};
    spdlog::info("Using {} as configuration", configFilename);
    config::ConfigFile config{configFilename};

    event::EventQueue eventQueue{};
    event::EventDispatcher eventDispatcher{};

    timer::TimerManager timerManager{eventQueue, eventDispatcher};

    protocol::http::HttpRequestFactory httpRequestFactory{};

    auto mqttWrapper = protocol::mqtt::createMqttWrapper(
        mqttClientId, config.get("zigbee2mqtt")["hostname"].asString(), config.get("zigbee2mqtt")["port"].asUInt());
    auto mqttClient = std::make_shared<protocol::mqtt::MqttClient>(mqttWrapper, eventDispatcher, eventQueue);

    core::DeviceManager deviceManager{};
    deviceManager.addGateway(gateway::zigbeemqtt::createZigbeeMqttGateway(mqttClient));
    auto metricsServer{protocol::metrics::createInfluxdbMetricsServer(httpRequestFactory, config)};
    metrics::MetricsService metricsService{timerManager, deviceManager, metricsServer};

    while (true)
    {
        eventDispatcher.dispatch(eventQueue.waitAndPop());
    }

    return 0;
}
