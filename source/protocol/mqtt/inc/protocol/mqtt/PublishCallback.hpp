#pragma once
#include <functional>
#include "protocol/mqtt/PublishedMessage.hpp"

namespace protocol::mqtt
{
using PublishCallback = std::function<void(const PublishedMessage&)>;
} // namespace protocol::mqtt
