#include "device/CapabilityType.hpp"

std::ostream& operator<<(std::ostream& os, device::CapabilityType type)
{
    using device::CapabilityType;
    switch (type)
    {
        case CapabilityType::Sensor:
            os << "Sensor";
            break;
        case CapabilityType::Actor:
            os << "Actor";
            break;
        default:
            os << static_cast<typename std::underlying_type<CapabilityType>::type>(type);
    }
    return os;
}
