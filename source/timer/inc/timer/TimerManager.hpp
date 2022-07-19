#pragma once
#include "timer/ITimerManager.hpp"

namespace event
{
class IEventQueue;
class IEventDispatcher;
} // namespace event

namespace timer
{
class TimerManager final : public ITimerManager
{
public:
    explicit TimerManager(event::IEventQueue&, event::IEventDispatcher&);
    std::unique_ptr<ITimer> createTimer(TimerCallback, std::chrono::milliseconds) override;
    std::unique_ptr<ITimer> createRecurringTimer(TimerCallback, std::chrono::milliseconds) override;

private:
    event::IEventQueue& eventQueue;
};
} // namespace timer
