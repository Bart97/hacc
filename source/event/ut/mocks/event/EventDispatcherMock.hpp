#pragma once
#include <gmock/gmock.h>
#include "event/IEventDispatcher.hpp"

namespace event
{
class EventDispatcherMock : public IEventDispatcher
{
public:
    MOCK_METHOD1(subscribe, void(std::unique_ptr<IEventCallbackWrapper>));
    MOCK_METHOD1(dispatch, void(std::shared_ptr<IEventWrapper>));
};
} // namespace event
