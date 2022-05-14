#include "event/EventCallbackWrapper.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "TestEvent.hpp"
#include "event/EventWrapper.hpp"

namespace event
{
using namespace testing;
using ut::TestEvent;

TEST(EventCallbackWrapperTest, shouldInvokecallbackWhenInvoked)
{
    StrictMock<MockFunction<void(TestEvent)>> callbackMock;

    EventCallbackWrapper<TestEvent> sut(callbackMock.AsStdFunction());
    EXPECT_CALL(callbackMock, Call(FieldsAre(7)));

    std::unique_ptr<EventWrapper<TestEvent>> event = std::make_unique<EventWrapper<TestEvent>>(TestEvent{7});
    sut(std::move(event));
}
} // namespace event
