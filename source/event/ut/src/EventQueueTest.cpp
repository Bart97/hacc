#include "event/EventQueue.hpp"
#include <gtest/gtest.h>
#include "TestEvent.hpp"
#include "event/EventWrapper.hpp"

namespace event
{
using namespace ::testing;
using ut::TestEvent;

class EventQueueTest : public Test
{
public:
    EventQueue sut;
};

TEST_F(EventQueueTest, popShouldReturnQueuedEvent)
{
    std::shared_ptr<EventWrapper<TestEvent>> event = std::make_shared<EventWrapper<TestEvent>>(TestEvent{});

    sut.push(event);
    EXPECT_EQ(sut.waitAndPop(), event);
}

TEST_F(EventQueueTest, popShouldReturnQueuedEventsInCorrectOrder)
{
    std::shared_ptr<EventWrapper<TestEvent>> event1 = std::make_shared<EventWrapper<TestEvent>>(TestEvent{});
    std::shared_ptr<EventWrapper<TestEvent>> event2 = std::make_shared<EventWrapper<TestEvent>>(TestEvent{});

    sut.push(event1);
    sut.push(event2);
    EXPECT_EQ(sut.waitAndPop(), event1);
    EXPECT_EQ(sut.waitAndPop(), event2);
}
} // namespace event
