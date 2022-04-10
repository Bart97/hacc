#pragma once
#include <string>

namespace protocol::mqtt
{
struct PublishedMessage
{
    std::string topic;
    std::string payload;
};

bool operator==(const PublishedMessage&, const PublishedMessage&);
} // namespace protocol::mqtt
