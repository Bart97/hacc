#pragma once
#include <boost/functional/hash.hpp>
#include <functional>
#include <string>
#include "spdlog/fmt/ostr.h"

namespace gateway::zigbeemqtt::configuration
{
struct DeviceIdentifier
{
    std::string manufacturer;
    std::string modelId;

    bool operator== (const DeviceIdentifier& other) const
    {
        return manufacturer == other.manufacturer and modelId == other.modelId;
    }
};

std::ostream& operator<<(std::ostream& os, const DeviceIdentifier& identifier)
{
    os << "[\"" << identifier.manufacturer << "\", \"" << identifier.modelId << "\"]";
    return os;
}
} // namespace gateway::zigbeemqtt::configuration

template<>
struct std::hash<gateway::zigbeemqtt::configuration::DeviceIdentifier>
{
    std::size_t operator()(gateway::zigbeemqtt::configuration::DeviceIdentifier const& identifier) const noexcept
    {
        return boost::hash_value(std::tie(identifier.manufacturer,identifier.modelId));
    }
};


