#pragma once
#include "event/EventUID.hpp"

namespace event
{
template<class EventType>
EventUID generateEventUID()
{
    return typeid(EventType).hash_code();
}
} // namespace event
