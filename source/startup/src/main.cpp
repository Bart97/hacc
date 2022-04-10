#include "spdlog/spdlog.h"
#include "protocol/mqtt/MqttWrapperFactory.hpp"

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

    return 0;
}