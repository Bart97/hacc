#pragma once
#include <map>
#include <memory>
#include "protocol/mqtt/IMqttClient.hpp"
#include "protocol/mqtt/IMqttWrapper.hpp"

namespace event
{
class IEventDispatcher;
class IEventQueue;
} // namespace event

namespace protocol::mqtt
{
class MqttClient : public IMqttClient
{
public:
    explicit MqttClient(std::shared_ptr<IMqttWrapper>, event::IEventDispatcher&, event::IEventQueue&);

    void publish(const std::string& string, const std::string& string1) override;
    void subscribe(const std::string& string, PublishCallback callback) override;

private:
    void processMessage(const PublishedMessage&);

    std::multimap<std::string, PublishCallback> callbackMap;
    std::shared_ptr<IMqttWrapper> wrapper;
    event::IEventDispatcher& eventDispatcher;
};
} // namespace protocol::mqtt
