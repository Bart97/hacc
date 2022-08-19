#pragma once
#include "protocol/metrics/IMetricsServer.hpp"
#include "protocol/metrics/influxdb/IInfluxdbApi.hpp"

namespace protocol::metrics
{
class InfluxdbMetricsServer final : public IMetricsServer
{
public:
    explicit InfluxdbMetricsServer(std::shared_ptr<influxdb::IInfluxdbApi>);
    void store(const Entries&) override;

public:
private:
    std::shared_ptr<influxdb::IInfluxdbApi> influxdb;
};
} // namespace protocol::metrics
