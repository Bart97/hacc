#pragma once
#include <memory>
#include "protocol/mqtt/IMqttWrapper.hpp"

namespace protocol::mqtt
{
std::shared_ptr<IMqttWrapper> createMqttWrapper(const std::string&, const std::string&, std::uint16_t);
} // namespace protocol::mqtt
