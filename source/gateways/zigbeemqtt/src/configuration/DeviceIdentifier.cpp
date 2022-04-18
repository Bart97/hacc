#include "gateway/zigbeemqtt/configuration/DeviceIdentifier.hpp"

namespace gateway::zigbeemqtt::configuration
{

bool DeviceIdentifier::operator== (const DeviceIdentifier& other) const
{
    return std::tie(manufacturer, modelId) == std::tie(other.manufacturer, other.modelId);
}

std::ostream& operator<<(std::ostream& os, const DeviceIdentifier& identifier)
{
    os << "[\"" << identifier.manufacturer << "\", \"" << identifier.modelId << "\"]";
    return os;
}
} // namespace gateway::zigbeemqtt::configuration