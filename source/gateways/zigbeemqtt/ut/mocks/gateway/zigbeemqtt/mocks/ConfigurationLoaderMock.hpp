#pragma once
#include <gmock/gmock.h>
#include <string>
#include "gateway/zigbeemqtt/configuration/IConfigurationLoader.hpp"

namespace gateway::zigbeemqtt::configuration
{
class ConfigurationLoaderMock : public IConfigurationLoader
{
public:
    MOCK_METHOD2(getConfiguration, std::optional<Configuration>(const std::string&, const std::string&));
};
} // namespace gateway::zigbeemqtt::configuration
