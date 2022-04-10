#include "protocol/mqtt/PublishedMessage.hpp"

namespace protocol::mqtt
{
bool operator==(const PublishedMessage& lhs, const PublishedMessage& rhs)
{
    return lhs.topic == rhs.topic and lhs.payload == rhs.payload;
}
} // namespace protocol::mqtt
