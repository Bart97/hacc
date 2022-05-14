#include <event/EventWrapper.hpp>
#include <gtest/gtest.h>

namespace
{
struct Event1
{
    int dummy{42};
};
} // namespace

namespace event
{
namespace test
{
struct Event2
{
    bool someFlag{true};
};
} // namespace test

TEST(EventWrapperTest, getNameShouldReturnValidNameForEventInAnonymousNamespace)
{
    EventWrapper<Event1> sut({});
    EXPECT_EQ(sut.getName(), "::Event1");
}

TEST(EventWrapperTest, getNameShouldReturnValidNameForEventNamedNamespace)
{
    EventWrapper<test::Event2> sut({});
    EXPECT_EQ(sut.getName(), "event::test::Event2");
}

TEST(EventWrapperTest, getHashShouldBeUniqueForEachEventType)
{
    EventWrapper<Event1> sut1({});
    EventWrapper<test::Event2> sut2({});
    EXPECT_NE(sut1.getUID(), sut2.getUID());
}
} // namespace event
