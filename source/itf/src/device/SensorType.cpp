#include "device/SensorType.hpp"

std::ostream& operator<<(std::ostream& os, device::SensorType sensorType)
{
    using device::SensorType;
    switch (sensorType)
    {
        case SensorType::Temperature:
            os << "Temperature";
            break;
        case SensorType::Humidity:
            os << "Humidity";
            break;
        case SensorType::Pressure:
            os << "Pressure";
            break;
        default:
            os << static_cast<typename std::underlying_type<SensorType>::type>(sensorType);
    }
    return os;
}
