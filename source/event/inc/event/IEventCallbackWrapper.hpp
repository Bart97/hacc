#pragma once
#include <memory>
#include "event/IEventWrapper.hpp"

namespace event
{
class IEventCallbackWrapper
{
public:
    virtual ~IEventCallbackWrapper() = default;
    virtual void operator()(std::shared_ptr<IEventWrapper>) = 0;
    virtual EventUID getEventUID() = 0;
};
} // namespace event
