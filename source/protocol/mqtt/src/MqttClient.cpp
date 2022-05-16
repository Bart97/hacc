#include "protocol/mqtt/MqttClient.hpp"
#include <algorithm>
#include <boost/range.hpp>
#include <ranges>
#include "event/EventCallbackWrapperFactory.hpp"
#include "event/EventWrapperFactory.hpp"
#include "event/IEventDispatcher.hpp"
#include "event/IEventQueue.hpp"
#include "protocol/mqtt/events/MqttMessagePublishedEvent.hpp"
#include "spdlog/spdlog.h"

namespace protocol::mqtt
{
MqttClient::MqttClient(
    std::shared_ptr<IMqttWrapper> wrapper, event::IEventDispatcher& dispatcher, event::IEventQueue& queue)
    : wrapper(std::move(wrapper))
    , eventDispatcher(dispatcher)
{
    eventDispatcher.subscribe(event::createEventCallbackWrapper<events::MqttMessagePublishedEvent>(
        [this](const auto& ev) { processMessage(ev.message); }));
    this->wrapper->setPublishCallback([&queue](const PublishedMessage& msg)
                                      { queue.push(event::createEvent(events::MqttMessagePublishedEvent{msg})); });
}

void MqttClient::processMessage(const PublishedMessage& msg)
{
    auto [begin, end] = callbackMap.equal_range(msg.topic);
    for (const auto& [_, callback] : boost::make_iterator_range(begin, end))
    {
        callback(msg);
    }
}

void MqttClient::publish(const std::string& title, const std::string& payload)
{
    wrapper->publish(title, payload, Qos::ExactlyOnce);
}

void MqttClient::subscribe(const std::string& topic, PublishCallback callback)
{
    spdlog::debug("[MQTT] Subscribing to topic {}", topic);
    callbackMap.insert({topic, std::move(callback)});
    wrapper->subscribe(topic, Qos::ExactlyOnce);
}
} // namespace protocol::mqtt
