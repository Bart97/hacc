#pragma once
#include "device/ICapability.hpp"
#include "gateway/zigbeemqtt/configuration/Configuration.hpp"
#include "protocol/mqtt/PublishedMessage.hpp"

namespace gateway::zigbeemqtt
{
class Capability : public device::ICapability
{
public:
    explicit Capability(const configuration::CapabilityMapping&);
    double getValue() const override;
    device::CapabilityType getType() const override;
    device::SensorType getSubType() const override;
    const std::string& getName() override;

    void onUpdate(const protocol::mqtt::PublishedMessage&);

private:
    std::string name;
    device::CapabilityType type;
    device::SensorType sensorType;
    std::string jsonPath;
    double value;
};
} // namespace gateway::zigbeemqtt

