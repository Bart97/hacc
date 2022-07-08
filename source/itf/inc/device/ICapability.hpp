#pragma once
#include <memory>
#include <vector>
#include "device/CapabilityType.hpp"
#include "device/SensorType.hpp"

namespace device
{
class ICapability
{
public:
    virtual ~ICapability() = default;
    virtual double getValue() const = 0;
    virtual CapabilityType getType() const = 0;
    virtual SensorType getSubType() const = 0;
    virtual const std::string& getName() = 0;
};
using Capabilities = std::vector<std::shared_ptr<ICapability>>;
} // namespace device
