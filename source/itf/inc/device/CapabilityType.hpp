#pragma once
#include <ostream>

namespace device
{
enum class CapabilityType
{
    Sensor,
    Actor
};
} // namespace device
std::ostream& operator<<(std::ostream&, device::CapabilityType);
