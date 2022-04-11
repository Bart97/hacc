#pragma once
#include <string>

namespace device
{
class IDevice
{
public:
    virtual ~IDevice() = default;
    virtual const std::string& getIdentifier() const = 0;
    virtual bool isPresent() = 0;
};
} // namespace device
