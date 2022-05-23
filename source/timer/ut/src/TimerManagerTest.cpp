#include "timer/TimerManager.hpp"
#include <boost/pointer_cast.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include "event/EventDispatcherMock.hpp"
#include "event/EventQueueMock.hpp"
#include "event/EventWrapper.hpp"
#include "event/EventWrapperFactory.hpp"
#include "timer/events/TimerExpiredEvent.hpp"

using namespace testing;
using namespace std::chrono_literals;

namespace timer
{
class TimerManagerTest : public Test
{
public:
    TimerManagerTest()
    {
        EXPECT_CALL(eventDispatcherMock, subscribe).WillOnce([&](auto arg) { dispatcherCallback = std::move(arg); });
    }

    std::unique_ptr<event::IEventCallbackWrapper> dispatcherCallback;

    StrictMock<event::EventDispatcherMock> eventDispatcherMock;
    StrictMock<event::EventQueueMock> eventQueueMock;
};

TEST_F(TimerManagerTest, constructorShouldRegisterTimerExpiredEventCallback)
{
    TimerManager sut{eventQueueMock, eventDispatcherMock};
    (void)sut;
    ASSERT_TRUE(dispatcherCallback);
}

TEST_F(TimerManagerTest, eventCallbackShouldInvoke)
{
    TimerManager sut{eventQueueMock, eventDispatcherMock};
    (void)sut;
    ASSERT_TRUE(dispatcherCallback);

    MockFunction<void()> callback;
    EXPECT_CALL(callback, Call());
    (*dispatcherCallback)(event::createEvent(events::TimerExpiredEvent{callback.AsStdFunction()}));
}

} // namespace timer
