#pragma once
#include <gmock/gmock.h>
#include "event/IEventQueue.hpp"

namespace event
{
class EventQueueMock : public IEventQueue
{
public:
    MOCK_METHOD0(waitAndPop, std::shared_ptr<IEventWrapper>());
    MOCK_METHOD1(push, void(std::shared_ptr<IEventWrapper>));
};
} // namespace event
