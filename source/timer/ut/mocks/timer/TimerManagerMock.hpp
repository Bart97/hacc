#pragma once
#include <gmock/gmock.h>
#include "timer/ITimerManager.hpp"

namespace timer
{
class TimerManagerMock : public ITimerManager
{
public:
    MOCK_METHOD2(createTimer, std::unique_ptr<ITimer>(TimerCallback callback, std::chrono::milliseconds duration));
};
} // namespace timer
