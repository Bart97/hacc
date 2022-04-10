#include "protocol/mqtt/MqttWrapperFactory.hpp"
#include "protocol/mqtt/MqttWrapper.hpp"

namespace protocol::mqtt
{
std::shared_ptr<IMqttWrapper> createMqttWrapper(const std::string& id, const std::string& host, std::uint16_t port)
{
    return std::make_shared<MqttWrapper>(id, host, port);
}
} // namespace protocol::mqtt
