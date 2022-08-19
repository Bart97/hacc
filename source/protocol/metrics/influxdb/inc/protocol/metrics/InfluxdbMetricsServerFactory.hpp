#pragma once
#include <memory>
#include "protocol/metrics/IMetricsServer.hpp"

namespace config
{
class ConfigFile;
} // namespace config

namespace protocol::http
{
class IHttpRequestFactory;
} // namespace protocol::http

namespace protocol::metrics
{
std::shared_ptr<IMetricsServer> createInfluxdbMetricsServer(
    protocol::http::IHttpRequestFactory&, const config::ConfigFile&);
} // namespace protocol::metrics
