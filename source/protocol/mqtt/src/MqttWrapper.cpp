#include "protocol/mqtt/MqttWrapper.hpp"
#include <boost/throw_exception.hpp>
#include <functional>
#include "spdlog/spdlog.h"

namespace
{
MQTT_NS::qos convert(const protocol::mqtt::Qos qos)
{
    using protocol::mqtt::Qos;
    switch (qos)
    {
        case Qos::AtMostOnce:
            return MQTT_NS::qos::at_most_once;
        case Qos::AtLeastOnce:
            return MQTT_NS::qos::at_least_once;
        case Qos::ExactlyOnce:
            return MQTT_NS::qos::exactly_once;
    }
    BOOST_THROW_EXCEPTION(std::runtime_error("Unexpected flow"));
}
} // namespace

namespace protocol::mqtt
{
MqttWrapper::MqttWrapper(const std::string& id, const std::string& host, const std::uint16_t port)
    : ioContext()
{
    client = ::mqtt::make_sync_client(ioContext, host, port);
    client->set_client_id(id);
    client->set_clean_session(true);
    ::MQTT_NS::setup_log();
    // Create no TLS client

    client->set_connack_handler(
        [this](bool, ::MQTT_NS::connect_return_code connack_return_code)
        {
            this->onConnected(connack_return_code);
            return true;
        });
    client->set_close_handler([this]() { this->onClosed(); });
    client->set_error_handler([this](::MQTT_NS::error_code ec) { this->onError(ec); });
    client->set_publish_handler(
        [this](auto packet_id, auto pubopts, auto topic, auto payload)
        {
            this->onPublish(packet_id, pubopts, std::string{topic}, std::string{payload});
            return true;
        });

    // Connect
    client->connect();

    contextThread = std::thread{[&ioContext = this->ioContext]() { ioContext.run(); }};
}

MqttWrapper::~MqttWrapper()
{
    ioContext.stop();
    contextThread.join();
}

void MqttWrapper::onConnected(::mqtt::connect_return_code connack_return_code)
{
    spdlog::info("[MQTT] Connection callback: {}", ::MQTT_NS::connect_return_code_to_str(connack_return_code));
    if (connack_return_code != ::MQTT_NS::connect_return_code::accepted)
    {
        spdlog::error("[MQTT] Connection failed: {}", ::MQTT_NS::connect_return_code_to_str(connack_return_code));
    }
}

void MqttWrapper::onPublish(
    ::mqtt::optional<PacketId> /*packetId*/,
    ::mqtt::publish_options /*pubopts*/,
    const std::string& topic,
    const std::string& payload)
{
    spdlog::debug("[MQTT] Received topic {}: {}", topic, payload);
    if (not publishCallback)
    {
        spdlog::warn("[MQTT] Publish callback not set");
    }
    publishCallback({topic, payload});
}

void MqttWrapper::publish(const std::string& topic, const std::string& payload, const Qos qos)
{
    spdlog::debug("[MQTT] Publishing topic {}: {}", topic, payload);
    client->publish(topic, payload, convert(qos));
}

void MqttWrapper::subscribe(const std::string& topic, const Qos qos)
{
    client->subscribe(topic, convert(qos));
}

void MqttWrapper::onClosed()
{
    spdlog::info("[MQTT] Connection closed");
}

void MqttWrapper::onError(::mqtt::error_code error)
{
    spdlog::error("[MQTT] Connection Error: {}", error.message());
}

void MqttWrapper::setPublishCallback(PublishCallback callback)
{
    publishCallback = std::move(callback);
}
} // namespace protocol::mqtt
