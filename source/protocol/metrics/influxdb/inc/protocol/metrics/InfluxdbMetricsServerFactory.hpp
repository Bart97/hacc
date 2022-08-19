#pragma once
#include <memory>
#include "protocol/metrics/IMetricsServer.hpp"

namespace config
{
class ConfigFile;
} // namespace config

namespace protocol::metrics
{
std::shared_ptr<IMetricsServer> createInfluxdbMetricsServer(const config::ConfigFile&);
} // namespace protocol::metrics
