#pragma once
#include <memory>
#include "event/EventWrapper.hpp"

namespace event
{
template<class EventType>
std::shared_ptr<IEventWrapper> createEvent(EventType event)
{
    return std::make_shared<EventWrapper<EventType>>(std::move(event));
}
} // namespace event
