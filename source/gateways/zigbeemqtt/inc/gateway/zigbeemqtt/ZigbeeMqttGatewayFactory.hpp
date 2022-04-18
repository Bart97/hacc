#pragma once
#include <memory>
#include "itf/IGateway.hpp"

namespace protocol::mqtt
{
class IMqttClient;
} // namespace protocol::mqtt

namespace gateway::zigbeemqtt
{
std::shared_ptr<gateway::IGateway> createZigbeeMqttGateway(std::shared_ptr<protocol::mqtt::IMqttClient>);
} // namespace gateway::zigbeemqtt
