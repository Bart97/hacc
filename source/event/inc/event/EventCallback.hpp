#pragma once
#include <functional>

namespace event
{
template<class EventType>
using EventCallback = std::function<void(const EventType&)>;
} // namespace event
