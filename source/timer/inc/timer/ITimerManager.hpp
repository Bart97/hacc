#pragma once
#include <chrono>
#include <memory>
#include "timer/ITimer.hpp"
#include "timer/TimerCallback.hpp"

namespace timer
{
class ITimerManager
{
public:
    virtual ~ITimerManager() = default;
    virtual std::unique_ptr<ITimer> createTimer(TimerCallback, std::chrono::milliseconds) = 0;
};
} // namespace timer
