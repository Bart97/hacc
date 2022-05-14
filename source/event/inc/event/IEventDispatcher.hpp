#pragma once
#include <functional>
#include "event/IEventCallbackWrapper.hpp"

namespace event
{
class IEventDispatcher
{
public:
    virtual ~IEventDispatcher() = default;
    virtual void subscribe(std::unique_ptr<IEventCallbackWrapper>) = 0;
    virtual void dispatch(std::shared_ptr<IEventWrapper>) = 0;
};
} // namespace event
