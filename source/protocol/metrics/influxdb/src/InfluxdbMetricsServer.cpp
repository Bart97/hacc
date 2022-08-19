#include "protocol/metrics/InfluxdbMetricsServer.hpp"
#include <spdlog/spdlog.h>
#include "InfluxDB.h"
#include "InfluxDBFactory.h"

namespace protocol::metrics
{
namespace
{
using InfluxdbValue = std::variant<int, long long int, std::string, double>;

InfluxdbValue convert(const Entry::Value& value)
{
    return std::visit([](auto&& arg) -> InfluxdbValue { return arg; }, value);
}
} // namespace

InfluxdbMetricsServer::InfluxdbMetricsServer(const std::string& url)
    : influxDb(influxdb::InfluxDBFactory::Get(url))
{
}

void InfluxdbMetricsServer::store(const Entries& entries)
{
    influxDb->batchOf(entries.size());
    for (const auto& entry : entries)
    {
        influxDb->write(
            influxdb::Point{entry.name}.addTag("device", entry.device).addField("value", convert(entry.value)));
    }
    influxDb->flushBatch();
}
} // namespace protocol::metrics
