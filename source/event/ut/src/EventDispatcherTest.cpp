#include "event/EventDispatcher.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "TestEvent.hpp"
#include "event/EventCallbackWrapper.hpp"
#include "event/EventCallbackWrapperFactory.hpp"
#include "event/EventWrapper.hpp"

namespace event
{
using namespace testing;
using ut::TestEvent;
using ut::TestEvent2;

namespace
{
template<class EventType>
using CallbackMock = StrictMock<MockFunction<void(const EventType&)>>;
} // namespace

class EventDispatcherTest : public Test
{
public:
    CallbackMock<TestEvent> callbackMock;
    std::unique_ptr<IEventCallbackWrapper> eventCallbackWrapper{
        createEventCallbackWrapper(callbackMock.AsStdFunction())};

    EventDispatcher sut{};
};

TEST_F(EventDispatcherTest, shouldExecuteSingleRegisteredCallback)
{
    sut.subscribe(std::move(eventCallbackWrapper));
    std::shared_ptr<EventWrapper<TestEvent>> event = std::make_shared<EventWrapper<TestEvent>>(TestEvent{});
    EXPECT_CALL(callbackMock, Call(event->getEvent()));
    sut.dispatch(event);
}

TEST_F(EventDispatcherTest, shouldExecuteCallbackOnlyForCorrectEvent)
{
    CallbackMock<TestEvent2> event2CallbackMock;
    std::unique_ptr<IEventCallbackWrapper> event2CallbackWrapper{
        createEventCallbackWrapper(event2CallbackMock.AsStdFunction())};

    sut.subscribe(std::move(eventCallbackWrapper));
    sut.subscribe(std::move(event2CallbackWrapper));
    std::shared_ptr<EventWrapper<TestEvent>> event = std::make_shared<EventWrapper<TestEvent>>(TestEvent{});
    EXPECT_CALL(callbackMock, Call(event->getEvent()));
    EXPECT_CALL(event2CallbackMock, Call(_)).Times(0);
    sut.dispatch(event);
}

TEST_F(EventDispatcherTest, shouldExecuteAllCallbackRegisteredForReceivedEvent)
{
    CallbackMock<TestEvent> callbackMock2;
    std::unique_ptr<IEventCallbackWrapper> eventCallbackWrapper2{
        createEventCallbackWrapper(callbackMock2.AsStdFunction())};

    sut.subscribe(std::move(eventCallbackWrapper));
    sut.subscribe(std::move(eventCallbackWrapper2));
    std::shared_ptr<EventWrapper<TestEvent>> event = std::make_shared<EventWrapper<TestEvent>>(TestEvent{});
    EXPECT_CALL(callbackMock, Call(event->getEvent()));
    EXPECT_CALL(callbackMock2, Call(event->getEvent()));
    sut.dispatch(event);
}
} // namespace event
