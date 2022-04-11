#pragma once
#include <gmock/gmock.h>
#include "protocol/mqtt/IMqttClient.hpp"

namespace protocol::mqtt
{
class MqttClientMock : public IMqttClient
{
public:
    MOCK_METHOD0(processMessages, void());
    MOCK_METHOD2(publish, void(const std::string&, const std::string&));
    MOCK_METHOD2(subscribe, void(const std::string&, PublishCallback));
};
} // namespace protocol::mqtt