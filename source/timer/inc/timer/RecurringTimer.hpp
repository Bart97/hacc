#pragma once
#include <atomic>
#include <chrono>
#include <condition_variable>
#include "TimerCallback.hpp"
#include "timer/ITimer.hpp"

namespace event
{
class IEventQueue;
} // namespace event

namespace timer
{
class RecurringTimer final : public ITimer
{
public:
    explicit RecurringTimer(TimerCallback, std::chrono::milliseconds, event::IEventQueue&);
    ~RecurringTimer() override;
    void abort() override;

private:
    std::atomic<bool> shouldAbort{};
    std::mutex abortMutex;
    std::condition_variable conditionVariable;
};
} // namespace timer
