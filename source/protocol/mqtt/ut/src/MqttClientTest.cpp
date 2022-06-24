#include "protocol/mqtt/MqttClient.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "event/EventDispatcherMock.hpp"
#include "event/EventQueueMock.hpp"
#include "event/EventWrapperFactory.hpp"
#include "protocol/mqtt/events/MqttMessagePublishedEvent.hpp"
#include "protocol/mqtt/mocks/MqttWrapperMock.hpp"

using namespace ::testing;
namespace protocol::mqtt
{
namespace
{
const std::string topic{"dummy/topic"};
const std::string payload{"Hello World!"};
const PublishedMessage testMessage{topic, payload};
} // namespace

class MqttClientTest : public Test
{
public:
    MqttClientTest()
    {
        EXPECT_CALL(*mqttWrapperMock, setPublishCallback(_)).WillOnce(SaveArg<0>(&sutPublishCallback));
        EXPECT_CALL(eventDispatcherMock, subscribe).WillOnce([&](auto arg) { dispatcherCallback = std::move(arg); });
    }

    MqttClient createSut()
    {
        return MqttClient{mqttWrapperMockPtr, eventDispatcherMock, eventQueueMock};
    }

    PublishCallback sutPublishCallback;
    std::unique_ptr<event::IEventCallbackWrapper> dispatcherCallback;

    std::shared_ptr<StrictMock<MqttWrapperMock>> mqttWrapperMockPtr{std::make_shared<StrictMock<MqttWrapperMock>>()};
    StrictMock<MqttWrapperMock>* mqttWrapperMock = mqttWrapperMockPtr.get();
    StrictMock<event::EventQueueMock> eventQueueMock;
    StrictMock<event::EventDispatcherMock> eventDispatcherMock;
};

TEST_F(MqttClientTest, ConstructorShouldSetPublishCallbackInWrapper)
{
    MqttClient sut{createSut()};
    EXPECT_TRUE(sutPublishCallback);
}

TEST_F(MqttClientTest, PublishShouldForwardCallToWrapper)
{
    MqttClient sut{createSut()};
    EXPECT_CALL(*mqttWrapperMock, publish(topic, payload, _));
    sut.publish(topic, payload);
}

TEST_F(MqttClientTest, SubscribeShouldForwardCallToWrapper)
{
    MqttClient sut{createSut()};
    EXPECT_CALL(*mqttWrapperMock, subscribe(topic, _));
    sut.subscribe(topic, [](const auto&) {});
}

TEST_F(MqttClientTest, WrapperCallbackShouldPushEventToQueue)
{
    MqttClient sut{createSut()};
    EXPECT_CALL(eventQueueMock, push(_));
    sutPublishCallback(testMessage);
}

TEST_F(MqttClientTest, ShouldDispatchMessageAfterPublishCallbackCalled)
{
    MockFunction<void(const PublishedMessage&)> callbackMock;
    MqttClient sut{createSut()};
    EXPECT_CALL(*mqttWrapperMock, subscribe(_, _));
    sut.subscribe(topic, callbackMock.AsStdFunction());

    EXPECT_CALL(callbackMock, Call(testMessage)).Times(1);
    (*dispatcherCallback)(event::createEvent(events::MqttMessagePublishedEvent{testMessage}));
}
} // namespace protocol::mqtt
