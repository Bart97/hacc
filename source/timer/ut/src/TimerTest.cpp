#include "timer/Timer.hpp"
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
class TimerTest : public Test
{
public:
    StrictMock<event::EventQueueMock> eventQueueMock;
};

TEST_F(TimerTest, timerShouldEmitEventAfterSetDuration)
{
    MockFunction<void()> callback;
    const std::chrono::milliseconds timeDelay{3ms};
    Timer sut{callback.AsStdFunction(), timeDelay, eventQueueMock};
    std::shared_ptr<event::IEventWrapper> receivedEvent;
    EXPECT_CALL(eventQueueMock, push(_)).WillOnce(SaveArg<0>(&receivedEvent));
    std::this_thread::sleep_for(timeDelay + 1ms);
    ASSERT_TRUE(receivedEvent);
    EXPECT_CALL(callback, Call());
    boost::dynamic_pointer_cast<event::EventWrapper<events::TimerExpiredEvent>>(std::move(receivedEvent))
        ->getEvent()
        .callback();
}

} // namespace timer
