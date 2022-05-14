#pragma once
#include <string>
#include "event/EventUID.hpp"

namespace event
{
class IEventWrapper
{
public:
    virtual ~IEventWrapper() = default;
    virtual std::string getName() const = 0;
    virtual EventUID getUID() const = 0;
};
} // namespace event
