#include "protocol/mqtt/MqttClient.hpp"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <boost/range.hpp>
#include <ranges>

namespace protocol::mqtt
{
MqttClient::MqttClient(std::shared_ptr<IMqttWrapper> wrapper) : wrapper(std::move(wrapper))
{
    this->wrapper->setPublishCallback([this](const PublishedMessage& msg) {
        this->queuePublishedMessage(msg);
    });
}

void MqttClient::processMessages()
{
    while (!messageQueue.empty())
    {
        auto msg = popMessage();

        auto [begin, end] = callbackMap.equal_range(msg.topic);
        for (const auto& [_, callback] : boost::make_iterator_range(begin, end))
        {
            callback(msg);
        }
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

void MqttClient::queuePublishedMessage(const PublishedMessage& msg)
{
    std::scoped_lock guard(queueMutex);
    messageQueue.push(msg);
}

PublishedMessage MqttClient::popMessage()
{
    std::scoped_lock guard(queueMutex);
    PublishedMessage msg = messageQueue.front();
    messageQueue.pop();
    return msg;
}
} // namespace protocol::mqtt

