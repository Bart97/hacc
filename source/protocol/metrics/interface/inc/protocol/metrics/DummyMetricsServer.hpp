#pragma once
#include "protocol/metrics/IMetricsServer.hpp"

namespace protocol::metrics
{
class DummyMetricsServer : public IMetricsServer
{
public:
    void store(const Entries& entries) override;
};
} // namespace protocol::metrics
