#pragma once
#include <cstdint>

namespace protocol::mqtt
{
enum class Qos: std::uint8_t
{
    AtMostOnce = 0,
    AtLeastOnce = 1,
    ExactlyOnce = 2
};
} // namespace protocol::mqtt
