#pragma once
#include <chrono>
#include "TimerCallback.hpp"
#include "timer/ITimer.hpp"

namespace event
{
class IEventQueue;
} // namespace event

namespace timer
{
class Timer : public ITimer
{
public:
    explicit Timer(TimerCallback, std::chrono::milliseconds, event::IEventQueue&);
    void abort() override;
};
} // namespace timer
