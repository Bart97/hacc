#pragma once
#include "timer/TimerCallback.hpp"

namespace timer::events
{
struct TimerExpiredEvent
{
    TimerCallback callback;
};
} // namespace timer::events
