#pragma once
#include <memory>

namespace event
{
class IEventWrapper;

class IEventQueue
{
public:
    virtual ~IEventQueue() = default;
    virtual std::shared_ptr<IEventWrapper> waitAndPop() = 0;
    virtual void push(std::shared_ptr<IEventWrapper>) = 0;
};
} // namespace event
