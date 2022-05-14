#pragma once
#include <boost/type_index.hpp>
#include "event/EventUidGenerator.hpp"
#include "event/IEventWrapper.hpp"

namespace event
{
template<class EventType>
class EventWrapper final : public IEventWrapper
{
public:
    explicit EventWrapper(EventType event)
        : ev(std::move(event)){};

    std::string getName() const override
    {
        std::string name = boost::typeindex::type_id<EventType>().pretty_name();
        const std::string prefix = "(anonymous namespace)";
        if (name.starts_with(prefix))
        {
            return name.substr(prefix.length());
        }
        return name;
    }

    EventUID getUID() const override
    {
        return generateEventUID<EventType>();
    }

    EventType& getEvent()
    {
        return ev;
    }

    const EventType& getEvent() const
    {
        return ev;
    }

private:
    EventType ev;
};
} // namespace event
