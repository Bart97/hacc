#include "timer/Timer.hpp"
#include <thread>
#include "event/EventWrapperFactory.hpp"
#include "event/IEventQueue.hpp"
#include "timer/events/TimerExpiredEvent.hpp"

namespace timer
{
Timer::Timer(TimerCallback callback, std::chrono::milliseconds duration, event::IEventQueue& eventQueue)
{
    std::thread(
        [callback, duration, &eventQueue]()
        {
            std::this_thread::sleep_for(duration);
            eventQueue.push(event::createEvent(events::TimerExpiredEvent{callback}));
        })
        .detach();
}

void Timer::abort() { } // TODO: Abortion
} // namespace timer
