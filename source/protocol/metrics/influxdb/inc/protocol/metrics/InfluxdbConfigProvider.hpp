#pragma once
#include <string>

namespace config
{
class ConfigFile;
} // namespace config

namespace protocol::metrics
{
class InfluxdbConfigProvider
{
public:
    explicit InfluxdbConfigProvider(const config::ConfigFile&);

    std::string getHostname() const;
    std::uint16_t getPort() const;
    std::string getDatabase() const;
    std::string getApiKey() const;

private:
    bool hasKey(const std::string& name) const;
    const config::ConfigFile& config;
};
}
