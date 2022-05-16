#pragma once
#include "protocol/mqtt/PublishedMessage.hpp"

namespace protocol::mqtt::events
{
struct MqttMessagePublishedEvent
{
    PublishedMessage message;
};
} // namespace protocol::mqtt::events
