#pragma once

namespace ut
{
struct TestEvent
{
    int dummy{42};
    bool operator==(const TestEvent& other) const
    {
        return dummy == other.dummy;
    }
};

struct TestEvent2
{
    int foo{666};
    bool operator==(const TestEvent2& other) const
    {
        return foo == other.foo;
    }
};
} // namespace ut
