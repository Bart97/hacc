#pragma once
#include <gmock/gmock.h>
#include "protocol/mqtt/IMqttWrapper.hpp"

namespace protocol::mqtt
{
class MqttWrapperMock : public IMqttWrapper
{
public:
    MOCK_METHOD3(publish, void(const std::string&, const std::string&, Qos));
    MOCK_METHOD2(subscribe, void(const std::string&, Qos));
    MOCK_METHOD1(setPublishCallback, void(PublishCallback));
};
} // namespace protocol::mqtt
