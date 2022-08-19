#include "protocol/metrics/InfluxdbConfigProvider.hpp"
#include "config/ConfigFile.hpp"

namespace protocol::metrics
{
InfluxdbConfigProvider::InfluxdbConfigProvider(const config::ConfigFile& config)
    : config(config)
{
}

std::string InfluxdbConfigProvider::getHostname() const
{
    if (not hasKey("hostname"))
    {
        throw std::runtime_error("InfluxDB hostname not configured");
    }
    return config.get("influxdb")["hostname"].asString();
}

std::uint16_t InfluxdbConfigProvider::getPort() const
{
    if (not hasKey("port"))
    {
        throw std::runtime_error("InfluxDB port not configured");
    }
    return config.get("influxdb")["port"].asUInt();
}

std::string InfluxdbConfigProvider::getDatabase() const
{
    if (not hasKey("database"))
    {
        throw std::runtime_error("InfluxDB database name not configured");
    }
    return config.get("influxdb")["database"].asString();
}

std::string InfluxdbConfigProvider::getBucket() const
{
    if (not hasKey("bucket"))
    {
        throw std::runtime_error("InfluxDB bucket not configured");
    }
    return config.get("influxdb")["bucket"].asString();
}

std::string InfluxdbConfigProvider::getOrganization() const
{
    if (not hasKey("organization"))
    {
        throw std::runtime_error("InfluxDB organization not configured");
    }
    return config.get("influxdb")["organization"].asString();
}

std::string InfluxdbConfigProvider::getApiKey() const
{
    if (not hasKey("apiKey"))
    {
        throw std::runtime_error("InfluxDB API key not configured");
    }
    return config.get("influxdb")["apiKey"].asString();
}

bool InfluxdbConfigProvider::hasKey(const std::string& name) const
{
    return config.get("influxdb").isMember(name);
}
} // namespace protocol::metrics
