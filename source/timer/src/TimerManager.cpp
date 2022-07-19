#include "timer/TimerManager.hpp"
#include "event/EventCallbackWrapperFactory.hpp"
#include "event/EventDispatcher.hpp"
#include "timer/RecurringTimer.hpp"
#include "timer/Timer.hpp"
#include "timer/events/TimerExpiredEvent.hpp"

namespace timer
{

TimerManager::TimerManager(event::IEventQueue& eventQueue, event::IEventDispatcher& eventDispatcher)
    : eventQueue(eventQueue)
{
    eventDispatcher.subscribe(
        event::createEventCallbackWrapper<events::TimerExpiredEvent>([](const auto& ev) { ev.callback(); }));
}

std::unique_ptr<ITimer> TimerManager::createTimer(TimerCallback callback, std::chrono::milliseconds duration)
{
    return std::make_unique<Timer>(std::move(callback), duration, eventQueue);
}

std::unique_ptr<ITimer> TimerManager::createRecurringTimer(TimerCallback callback, std::chrono::milliseconds duration)
{
    return std::make_unique<RecurringTimer>(std::move(callback), duration, eventQueue);
}
} // namespace timer
