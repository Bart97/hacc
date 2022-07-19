#pragma once
#include "protocol/metrics/IMetricsServer.hpp"

namespace influxdb
{
class InfluxDB;
} // namespace influxdb

namespace protocol::metrics
{
class InfluxdbMetricsServer final : public IMetricsServer
{
public:
    explicit InfluxdbMetricsServer(const std::string&);
    void store(const Entries&) override;

public:
private:
    std::unique_ptr<influxdb::InfluxDB> influxDb;
};
} // namespace protocol::metrics
