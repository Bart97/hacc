#include "gateway/zigbeemqtt/configuration/ConfigurationLoader.hpp"
#include "spdlog/spdlog.h"

namespace gateway::zigbeemqtt::configuration
{
namespace
{
Configuration buildSnzb02Configuration()
{
    return {{"eWeLink", "TH01"},
            {
                {device::CapabilityType::Sensor, device::SensorType::Humidity, "humidity", std::nullopt},
                {device::CapabilityType::Sensor, device::SensorType::Temperature, "temperature", std::nullopt}
            }};
}
} // namespace

ConfigurationLoader::ConfigurationLoader()
{
    storeConfiguration(buildSnzb02Configuration());
}

std::optional<Configuration> ConfigurationLoader::getConfiguration(
        const std::string& manufacturer, const std::string& modelId)
try
{
    return loadedConfigurations.at(DeviceIdentifier{manufacturer, modelId});
}
catch (std::out_of_range&)
{
    // TODO: Dynamic configuration loading
    return std::nullopt;
}

void ConfigurationLoader::storeConfiguration(Configuration configuration)
{
    spdlog::info("Loading configuration for device {}", configuration.deviceIdentifier);
    loadedConfigurations.insert({configuration.deviceIdentifier, std::move(configuration)});
}
} // namespace gateway::zigbeemqtt::configuration
