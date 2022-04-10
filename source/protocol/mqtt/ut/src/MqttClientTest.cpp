#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "protocol/mqtt/MqttClient.hpp"

using namespace ::testing;
namespace protocol::mqtt
{

class MqttWrapperMock: public IMqttWrapper
{
public:
    MOCK_METHOD3(publish, void(const std::string&, const std::string&, Qos));
    MOCK_METHOD2(subscribe, void(const std::string&, Qos));
    MOCK_METHOD1(setPublishCallback, void(PublishCallback));
};

class MqttClientTest: public Test
{
public:
    MqttClientTest()
    {
        EXPECT_CALL(*mqttWrapperMock, setPublishCallback(_)).WillOnce(SaveArg<0>(&sutPublishCallback));
    }

    PublishCallback sutPublishCallback;

    std::shared_ptr<StrictMock<MqttWrapperMock>> mqttWrapperMockPtr{std::make_shared<StrictMock<MqttWrapperMock>>()};
    StrictMock<MqttWrapperMock>* mqttWrapperMock = mqttWrapperMockPtr.get();
};

TEST_F(MqttClientTest, ConstructorShouldSetPublishCallbackInWrapper)
{
    MqttClient sut{mqttWrapperMockPtr};
    EXPECT_TRUE(sutPublishCallback);
}

TEST_F(MqttClientTest, PublishShouldForwardCallToWrapper)
{
    const std::string topic = "dummy/topic";
    const std::string payload = "Hello World!";
    MqttClient sut{mqttWrapperMockPtr};
    EXPECT_CALL(*mqttWrapperMock, publish(topic, payload, _));
    sut.publish(topic, payload);
}

TEST_F(MqttClientTest, SubscribeShouldForwardCallToWrapper)
{
    const std::string topic = "dummy/topic";
    MqttClient sut{mqttWrapperMockPtr};
    EXPECT_CALL(*mqttWrapperMock, subscribe(topic, _));
    sut.subscribe(topic, [](const auto&) {});
}

TEST_F(MqttClientTest, ShouldDispatchMessageAfterPublishCallbackCalled)
{
    const std::string topic = "dummy/topic";
    PublishedMessage expectedMsg{topic, "Hello World!"};
    MockFunction<void(const PublishedMessage&)> callbackMock;
    MqttClient sut{mqttWrapperMockPtr};
    EXPECT_CALL(*mqttWrapperMock, subscribe(_, _));
    sut.subscribe(topic, callbackMock.AsStdFunction());
    sutPublishCallback(expectedMsg);

    EXPECT_CALL(callbackMock, Call(expectedMsg)).Times(1);
    sut.processMessages();
}

} // namespace protocol::mqtt
