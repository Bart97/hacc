#pragma once
#include <boost/pointer_cast.hpp>
#include <functional>
#include "event/EventCallback.hpp"
#include "event/EventUidGenerator.hpp"
#include "event/EventWrapper.hpp"
#include "event/IEventCallbackWrapper.hpp"

namespace event
{
template<class EventType>
class EventCallbackWrapper final : public IEventCallbackWrapper
{
public:
    explicit EventCallbackWrapper(EventCallback<EventType> eventCallback)
        : callback(std::move(eventCallback)){};

    void operator()(std::shared_ptr<IEventWrapper> eventPtr) override
    {
        std::shared_ptr<EventWrapper<EventType>> event
            = boost::dynamic_pointer_cast<EventWrapper<EventType>>(std::move(eventPtr));

        callback(event->getEvent());
    }

    EventUID getEventUID() override
    {
        return generateEventUID<EventType>();
    }

private:
    EventCallback<EventType> callback;
};
} // namespace event
