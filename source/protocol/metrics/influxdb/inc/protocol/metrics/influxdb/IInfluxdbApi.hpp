#pragma once
#include "protocol/metrics/influxdb/Point.hpp"

namespace protocol::metrics::influxdb
{
class IInfluxdbApi
{
public:
    virtual ~IInfluxdbApi() = default;

    virtual void write(const Point&) = 0;
    virtual void write(const PointRange&) = 0;
};
} // namespace protocol::metrics::influxdb
