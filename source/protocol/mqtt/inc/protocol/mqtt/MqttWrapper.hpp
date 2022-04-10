#pragma once
#include <functional>
#include <string>
#include <type_traits>
#include "protocol/mqtt/IMqttWrapper.hpp"
#include "mqtt_client_cpp.hpp"


namespace protocol::mqtt
{
class MqttWrapper: public IMqttWrapper
{
public:
    MqttWrapper(const std::string&, const std::string&, const std::uint16_t);
    ~MqttWrapper() override;

    void publish(const std::string& topic, const std::string& payload, Qos qos) override;
    void subscribe(const std::string& topic, Qos qos) override;
    void setPublishCallback(PublishCallback) override;

private:
    using WrappedType = decltype(::mqtt::make_sync_client(std::declval<boost::asio::io_context&>(), std::declval<std::string>(), std::declval<std::uint16_t>()));
    using PacketId = typename std::remove_reference_t<WrappedType>::element_type::packet_id_t;

    void onConnected(::mqtt::connect_return_code);
    void onPublish(::MQTT_NS::optional<PacketId> packet_id,
                   ::MQTT_NS::publish_options pubopts,
                   const std::string& topic,
                   const std::string& payload);
    void onClosed();
    void onError(::MQTT_NS::error_code);

public:

private:
    boost::asio::io_context ioContext;
    WrappedType client;
    PublishCallback publishCallback;
    std::thread contextThread;
};
} // namespace protocol::mqtt
