#pragma once
#include "protocol/http/IHttpRequestFactory.hpp"
#include "protocol/metrics/IInfluxdbConfigProvider.hpp"
#include "protocol/metrics/influxdb/IInfluxdbApi.hpp"

namespace protocol::metrics::influxdb::v2
{
class InfluxdbApiV2 final : public IInfluxdbApi
{
public:
    explicit InfluxdbApiV2(protocol::http::IHttpRequestFactory&, const IInfluxdbConfigProvider&);
    void write(const Point& point) override;
    void write(const PointRange& range) override;

private:
    std::string buildWriteUrl() const;
    protocol::http::IHttpRequestFactory& httpRequestFactory;

    const std::string hostname;
    const std::uint16_t port;
    const std::string bucket;
    const std::string organization;
    const std::string apiKey;
};
} // namespace protocol::metrics::influxdb::v2
