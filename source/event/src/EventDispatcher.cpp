#include "event/EventDispatcher.hpp"
#include <spdlog/spdlog.h>

namespace event
{
void EventDispatcher::subscribe(std::unique_ptr<IEventCallbackWrapper> callback)
{
    callbackMap[callback->getEventUID()].emplace_back(std::move(callback));
}

void EventDispatcher::dispatch(std::shared_ptr<IEventWrapper> event)
{
    spdlog::info("Dispatching event {}[{}]", event->getName(), event->getUID());
    for (const auto& callback : callbackMap.at(event->getUID()))
    {
        (*callback)(event);
    }
}
} // namespace event
