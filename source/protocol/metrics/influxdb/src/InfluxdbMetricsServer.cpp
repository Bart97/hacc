#include "protocol/metrics/InfluxdbMetricsServer.hpp"
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/uniqued.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/size.hpp>
#include <spdlog/spdlog.h>

namespace protocol::metrics
{
namespace
{
protocol::metrics::influxdb::Point::FieldValue convert(const Entry::Value& value)
{
    return std::visit([](auto&& arg) -> protocol::metrics::influxdb::Point::FieldValue { return arg; }, value);
}

} // namespace

InfluxdbMetricsServer::InfluxdbMetricsServer(std::shared_ptr<influxdb::IInfluxdbApi> api)
    : influxdb(std::move(api))
{
}

void InfluxdbMetricsServer::store(const Entries& entries)
{
    const auto uniqueDevices = entries | boost::adaptors::transformed([](const auto& entry) { return entry.device; })
        | boost::adaptors::uniqued;

    std::vector<influxdb::Point> points;
    points.reserve(boost::size(uniqueDevices));

    for (const auto& device : uniqueDevices)
    {
        const auto deviceEntries
            = entries | boost::adaptors::filtered([&device](const auto& entry) { return entry.device == device; });
        influxdb::Point p("sensors");
        p.addTag("device", device);
        boost::for_each(deviceEntries, [&p](const auto& entry) { p.addField(entry.name, convert(entry.value)); });
        points.emplace_back(p);
    }
    influxdb->write(points);
}
} // namespace protocol::metrics
