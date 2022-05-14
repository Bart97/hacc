#pragma once
#include <string>

namespace event
{
using EventUID = std::size_t;
class IEventWrapper
{
public:
    virtual ~IEventWrapper() = default;
    virtual std::string getName() const = 0;
    virtual EventUID getUID() const = 0;
};
} // namespace event
