#pragma once
#include <unordered_map>
#include "gateway/zigbeemqtt/configuration/DeviceIdentifier.hpp"
#include "gateway/zigbeemqtt/configuration/IConfigurationLoader.hpp"

namespace gateway::zigbeemqtt::configuration
{
class ConfigurationLoader final : public IConfigurationLoader
{
public:
    ConfigurationLoader();
    std::optional<Configuration> getConfiguration(const std::string& manufacturer, const std::string& modelId) override;

private:
    void storeConfiguration(Configuration);

    using ConfigurationMap = std::unordered_map<DeviceIdentifier, Configuration>;

    ConfigurationMap loadedConfigurations;
};
} // namespace gateway::zigbeemqtt::configuration
