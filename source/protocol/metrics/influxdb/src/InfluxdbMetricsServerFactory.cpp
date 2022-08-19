#include "protocol/metrics/InfluxdbMetricsServerFactory.hpp"
#include <spdlog/spdlog.h>
#include "protocol/metrics/InfluxdbConfigProvider.hpp"
#include "protocol/metrics/InfluxdbMetricsServer.hpp"
#include "protocol/metrics/influxdb/v2/InfluxdbApiV2.hpp"

namespace protocol::metrics
{
std::shared_ptr<IMetricsServer> createInfluxdbMetricsServer(
    protocol::http::IHttpRequestFactory& httpRequestFactory, const config::ConfigFile& config)
{
    return std::make_shared<InfluxdbMetricsServer>(
        std::make_shared<influxdb::v2::InfluxdbApiV2>(httpRequestFactory, InfluxdbConfigProvider{config}));
}
} // namespace protocol::metrics
