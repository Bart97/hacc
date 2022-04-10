#pragma once
#include <ostream>

namespace device
{
enum class SensorType
{
    Temperature,
    Humidity,
    Pressure
};
} // namespace device
std::ostream& operator<<(std::ostream&, device::SensorType);
