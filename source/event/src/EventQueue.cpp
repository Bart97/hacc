#include "event/EventQueue.hpp"
#include <mutex>
#include "event/IEventWrapper.hpp"

namespace event
{
std::shared_ptr<IEventWrapper> event::EventQueue::waitAndPop()
{
    std::unique_lock guard(queueMutex);
    conditionVariable.wait(guard, [this] { return not eventQueue.empty(); });
    std::shared_ptr<IEventWrapper> event = eventQueue.front();
    eventQueue.pop_front();
    return event;
}

void event::EventQueue::push(std::shared_ptr<IEventWrapper> event)
{
    {
        std::scoped_lock guard(queueMutex);
        eventQueue.emplace_back(std::move(event));
    }
    conditionVariable.notify_all();
}
} // namespace event
