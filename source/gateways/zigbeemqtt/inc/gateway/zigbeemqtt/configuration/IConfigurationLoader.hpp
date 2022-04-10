#pragma once
#include <optional>
#include <string>
#include "gateway/zigbeemqtt/configuration/Configuration.hpp"

namespace gateway::zigbeemqtt::configuration
{
class IConfigurationLoader
{
public:
    virtual ~IConfigurationLoader() = default;
    virtual std::optional<Configuration> getConfiguration(
            const std::string& manufacturer, const std::string& modelId) = 0;
};
} // namespace gateway::zigbeemqtt::configuration
