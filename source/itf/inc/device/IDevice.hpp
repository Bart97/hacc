#pragma once

namespace device
{
class IDevice
{
public:
    virtual ~IDevice() = default;
    virtual bool isPresent() = 0;
};
} // namespace device
