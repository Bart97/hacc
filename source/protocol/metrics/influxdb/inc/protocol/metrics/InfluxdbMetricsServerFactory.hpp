#pragma once
#include "protocol/metrics/IMetricsServer.hpp"
#include <memory>

namespace config
{
class ConfigFile;
} // namespace config

namespace protocol::metrics
{
std::shared_ptr<IMetricsServer> createInfluxdbMetricsServer(const config::ConfigFile&);
} // namespace protocol::metrics
