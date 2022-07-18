#pragma once
#include "protocol/metrics/Entry.hpp"

namespace protocol::metrics
{
class IMetricsServer
{
public:
    virtual ~IMetricsServer() = default;

    virtual void store(const Entries&) = 0;
};
} // namespace protocol::metrics
