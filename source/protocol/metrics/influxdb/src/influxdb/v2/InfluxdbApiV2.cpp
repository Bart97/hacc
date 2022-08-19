#include "protocol/metrics/influxdb/v2/InfluxdbApiV2.hpp"
#include <boost/range/algorithm/for_each.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include "protocol/metrics/influxdb/Point.hpp"

namespace protocol::metrics::influxdb::v2
{
InfluxdbApiV2::InfluxdbApiV2(http::IHttpRequestFactory& httpRequestFactory, const IInfluxdbConfigProvider& config)
    : httpRequestFactory(httpRequestFactory)
    , hostname(config.getHostname())
    , port(config.getPort())
    , bucket(config.getBucket())
    , organization(config.getOrganization())
    , apiKey(config.getApiKey())
{
}
void InfluxdbApiV2::write(const Point& point)
{
    write(std::vector{point});
}
void InfluxdbApiV2::write(const PointRange& points)
{
    const std::uint16_t expectedResponse{204};
    std::stringstream ss;
    boost::for_each(points, [&ss](const auto& point) { ss << point.toLineProtocol(); });

    auto request = httpRequestFactory.create();
    request->setUrl(
        fmt::format("{}:{}/api/v2/write?bucket={}&org={}&precision=ns", hostname, port, bucket, organization));
    request->setMethod(http::Method::Post);
    request->setAuthorization("Token " + apiKey);
    request->setContent(ss.str());
    request->execute();

    if (const auto response = request->getResponseCode(); response != expectedResponse)
    {
        BOOST_THROW_EXCEPTION(
            std::runtime_error("Failed to write points to InfluxDB: Response " + std::to_string(response)));
    }
}
} // namespace protocol::metrics::influxdb::v2
