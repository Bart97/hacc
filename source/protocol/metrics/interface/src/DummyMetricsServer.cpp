#include "protocol/metrics/DummyMetricsServer.hpp"
#include "spdlog/spdlog.h"

namespace protocol::metrics
{
void DummyMetricsServer::store(const Entries& entries)
{
    for (const auto& entry : entries)
    {
        spdlog::info("DummyMetricsServer storing {}", entry);
    }
}
} // namespace protocol::metrics
