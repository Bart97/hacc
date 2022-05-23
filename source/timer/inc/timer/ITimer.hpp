#pragma once

namespace timer
{
class ITimer
{
public:
    virtual ~ITimer() = default;
    virtual void abort() = 0;
};
} // namespace timer
