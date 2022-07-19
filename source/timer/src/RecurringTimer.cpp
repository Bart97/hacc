#include "timer/RecurringTimer.hpp"
#include <mutex>
#include <thread>
#include "event/EventWrapperFactory.hpp"
#include "event/IEventQueue.hpp"
#include "timer/events/TimerExpiredEvent.hpp"

namespace timer
{
RecurringTimer::RecurringTimer(
    TimerCallback callback, std::chrono::milliseconds duration, event::IEventQueue& eventQueue)
{
    std::thread(
        [callback, duration, &eventQueue, this]()
        {
            std::unique_lock lock(abortMutex);
            while (!shouldAbort.test())
            {
                conditionVariable.wait_for(lock, duration);
                if (!shouldAbort.test())
                {
                    eventQueue.push(event::createEvent(events::TimerExpiredEvent{callback}));
                }
            }
        })
        .detach();
}

RecurringTimer::~RecurringTimer()
{
    {
        std::scoped_lock guard(abortMutex);
        shouldAbort.test_and_set();
    }
    conditionVariable.notify_all();
}

void RecurringTimer::abort()
{
    {
        std::scoped_lock guard(abortMutex);
        shouldAbort.test_and_set();
    }
    conditionVariable.notify_all();
}
} // namespace timer
