#include "gateway/zigbeemqtt/Capability.hpp"
#include <json/json.h>

namespace
{
std::string sensorTypeToStr(const device::SensorType type)
{
    std::stringstream stringstream{};
    stringstream << type;
    return stringstream.str();
}
} // namespace

namespace gateway::zigbeemqtt
{
Capability::Capability(const configuration::CapabilityMapping& mapping)
        : type(mapping.capabilityType),
          sensorType(mapping.subtype),
          jsonPath(mapping.jsonPath),
          value(std::numeric_limits<double>::quiet_NaN())
{
    name = mapping.friendlyName.value_or(sensorTypeToStr(mapping.subtype));
}

double Capability::getValue() const
{
    return value;
}

device::CapabilityType Capability::getType() const
{
    return type;
}

device::SensorType Capability::getSubType() const
{
    return sensorType;
}

const std::string& Capability::getName()
{
    return name;
}

void Capability::onUpdate(const protocol::mqtt::PublishedMessage& msg)
{
    Json::Reader reader;
    Json::Value json;
    reader.parse(msg.payload, json);
    value = json[jsonPath].asDouble();
}
} // namespace gateway::zigbeemqtt
