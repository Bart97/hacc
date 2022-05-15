#pragma once
#include <condition_variable>
#include <deque>
#include "event/IEventQueue.hpp"

namespace event
{
class EventQueue : public IEventQueue
{
public:
    std::shared_ptr<IEventWrapper> waitAndPop() override;
    void push(std::shared_ptr<IEventWrapper> ptr) override;

private:
    std::mutex queueMutex;
    std::condition_variable conditionVariable;
    std::deque<std::shared_ptr<IEventWrapper>> eventQueue;
};
} // namespace event
