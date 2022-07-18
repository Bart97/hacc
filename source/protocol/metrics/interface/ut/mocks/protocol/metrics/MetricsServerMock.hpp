#pragma once
#include <gmock/gmock.h>
#include "protocol/metrics/IMetricsServer.hpp"

namespace protocol::metrics
{
class MetricsServerMock : public IMetricsServer
{
public:
    MOCK_METHOD1(store, void(const Entries&));
};
} // namespace protocol::metrics
