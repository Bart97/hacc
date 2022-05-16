#pragma once
#include <string>
#include "protocol/mqtt/PublishCallback.hpp"

namespace protocol::mqtt
{
class IMqttClient
{
public:
    virtual ~IMqttClient() = default;
    virtual void publish(const std::string&, const std::string&) = 0;
    virtual void subscribe(const std::string&, PublishCallback) = 0;
};
} // namespace protocol::mqtt
