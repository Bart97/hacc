#include "protocol/metrics/InfluxdbMetricsServerFactory.hpp"
#include <spdlog/spdlog.h>
#include "InfluxDB.h"
#include "protocol/metrics/InfluxdbConfigProvider.hpp"
#include "protocol/metrics/InfluxdbMetricsServer.hpp"

namespace protocol::metrics
{
namespace
{
std::string buildConnectionStringFromConfig(const InfluxdbConfigProvider& config)
{
    return fmt::format(
        "http://{}:{}?db={} --{}", config.getHostname(), config.getPort(), config.getDatabase(), config.getApiKey());
}
} // namespace

std::shared_ptr<IMetricsServer> createInfluxdbMetricsServer(const config::ConfigFile& config)
{
    return std::make_shared<InfluxdbMetricsServer>(buildConnectionStringFromConfig(InfluxdbConfigProvider{config}));
}
} // namespace protocol::metrics
