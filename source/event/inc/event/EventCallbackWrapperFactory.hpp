#pragma once
#include <memory>
#include "event/EventCallback.hpp"
#include "event/EventCallbackWrapper.hpp"

namespace event
{
template<class EventType>
std::unique_ptr<IEventCallbackWrapper> createEventCallbackWrapper(EventCallback<EventType> callback)
{
    return std::make_unique<EventCallbackWrapper<EventType>>(std::move(callback));
}
} // namespace event
