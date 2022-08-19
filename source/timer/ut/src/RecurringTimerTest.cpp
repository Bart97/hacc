#include "timer/RecurringTimer.hpp"
#include <boost/pointer_cast.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include "event/EventQueueMock.hpp"
#include "event/EventWrapper.hpp"
#include "timer/events/TimerExpiredEvent.hpp"

using namespace testing;
using namespace std::chrono_literals;

namespace timer
{
class RecurringTimerTest : public Test
{
public:
    StrictMock<event::EventQueueMock> eventQueueMock;
};

TEST_F(RecurringTimerTest, timerShouldEmitEventAfterSetDuration)
{
    MockFunction<void()> callback;
    const std::chrono::milliseconds timeDelay{3ms};
    RecurringTimer sut{callback.AsStdFunction(), timeDelay, eventQueueMock};
    std::shared_ptr<event::IEventWrapper> receivedEvent;
    EXPECT_CALL(eventQueueMock, push(_)).WillOnce(SaveArg<0>(&receivedEvent));
    std::this_thread::sleep_for(timeDelay + 1ms);
    ASSERT_TRUE(receivedEvent);
    EXPECT_CALL(callback, Call());
    boost::dynamic_pointer_cast<event::EventWrapper<events::TimerExpiredEvent>>(std::move(receivedEvent))
        ->getEvent()
        .callback();
}

TEST_F(RecurringTimerTest, timerShouldEmitSecondEventAfterSetDurationElapsedTwice)
{
    MockFunction<void()> callback;
    const std::chrono::milliseconds timeDelay{3ms};
    RecurringTimer sut{callback.AsStdFunction(), timeDelay, eventQueueMock};
    EXPECT_CALL(eventQueueMock, push(_)).Times(2);
    std::this_thread::sleep_for(2 * timeDelay + 1ms);
}

TEST_F(RecurringTimerTest, abortShouldStopTimerBeforeEventSent)
{
    MockFunction<void()> callback;
    const std::chrono::milliseconds timeDelay{3ms};
    RecurringTimer sut{callback.AsStdFunction(), timeDelay, eventQueueMock};
    sut.abort();
    EXPECT_CALL(eventQueueMock, push(_)).Times(0);
    std::this_thread::sleep_for(2 * timeDelay + 1ms);
}
} // namespace timer
