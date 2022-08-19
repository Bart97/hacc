#pragma once
#include <string>
#include "protocol/metrics/IInfluxdbConfigProvider.hpp"

namespace config
{
class ConfigFile;
} // namespace config

namespace protocol::metrics
{
class InfluxdbConfigProvider final : public IInfluxdbConfigProvider
{
public:
    explicit InfluxdbConfigProvider(const config::ConfigFile&);

    std::string getHostname() const override;
    std::uint16_t getPort() const override;
    std::string getDatabase() const override;
    std::string getBucket() const override;
    std::string getOrganization() const override;
    std::string getApiKey() const override;

private:
    bool hasKey(const std::string& name) const;
    const config::ConfigFile& config;
};
} // namespace protocol::metrics
