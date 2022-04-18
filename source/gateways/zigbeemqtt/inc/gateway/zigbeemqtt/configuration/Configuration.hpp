#pragma once
#include <optional>
#include <string>
#include <vector>
#include "device/CapabilityType.hpp"
#include "device/SensorType.hpp"
#include "gateway/zigbeemqtt/configuration/DeviceIdentifier.hpp"

namespace gateway::zigbeemqtt::configuration
{
struct CapabilityMapping
{
    device::CapabilityType capabilityType;
    device::SensorType subtype;
    std::string jsonPath;
    std::optional<std::string> friendlyName;
};
using CapabilityMappings = std::vector<CapabilityMapping>;

struct Configuration
{
    DeviceIdentifier deviceIdentifier;
    CapabilityMappings capabilityMappings;
};
} // namespace gateway::zigbeemqtt::configuration
