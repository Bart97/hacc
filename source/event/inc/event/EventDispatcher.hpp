#pragma once
#include "event/IEventCallbackWrapper.hpp"
#include "event/IEventDispatcher.hpp"
#include "event/IEventWrapper.hpp"

namespace event
{
class EventDispatcher final : public IEventDispatcher
{
public:
    void subscribe(std::unique_ptr<IEventCallbackWrapper>) override;
    void dispatch(std::shared_ptr<IEventWrapper> ptr) override;

private:
    std::unordered_map<EventUID, std::vector<std::unique_ptr<IEventCallbackWrapper>>> callbackMap;
};
} // namespace event
