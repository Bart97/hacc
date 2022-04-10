#pragma once
#include "protocol/mqtt/PublishCallback.hpp"
#include "protocol/mqtt/Qos.hpp"

namespace protocol::mqtt
{
class IMqttWrapper
{
public:
    virtual ~IMqttWrapper() = default;

    virtual void publish(const std::string&, const std::string&, Qos) = 0;
    virtual void subscribe(const std::string&, Qos) = 0;
    virtual void setPublishCallback(PublishCallback) = 0;
};
} // namespace protocol::mqtt

