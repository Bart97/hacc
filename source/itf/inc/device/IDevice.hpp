#pragma once
#include <string>
#include "device/ICapability.hpp"

namespace device
{
class IDevice
{
public:
    virtual ~IDevice() = default;
    virtual const std::string& getIdentifier() const = 0;
    virtual bool isPresent() = 0;
    virtual const Capabilities& getCapabilities() const = 0;
};
} // namespace device
