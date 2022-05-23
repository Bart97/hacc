#pragma once
#include <gmock/gmock.h>
#include "timer/ITimer.hpp"

namespace timer
{
class TimerMock : public ITimer
{
public:
    MOCK_METHOD0(abort, void());
};
} // namespace timer
