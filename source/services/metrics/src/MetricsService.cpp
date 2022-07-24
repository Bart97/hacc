#include "services/metrics/MetricsService.hpp"
#include <set>
#include <spdlog/spdlog.h>
#include "device/IDevice.hpp"
#include "device/SensorType.hpp"

namespace
{
using namespace std::chrono_literals;
constexpr auto updateInterval = 5s;

bool shouldStoreSensor(const device::SensorType sensorType)
{
    const std::set<device::SensorType> supportedSensors{device::SensorType::Temperature, device::SensorType::Humidity};
    return supportedSensors.contains(sensorType);
}
} // namespace

namespace metrics
{
MetricsService::MetricsService(
    timer::ITimerManager& timerManager,
    core::IDeviceManager& deviceManager,
    protocol::metrics::IMetricsServer& metricsServer)
    : timerManager(timerManager)
    , deviceManager(deviceManager)
    , metricsServer(metricsServer)
{
    updateTimer = this->timerManager.createRecurringTimer([this]() { this->update(); }, updateInterval);
}

void MetricsService::update()
{
    protocol::metrics::Entries entries;
    for (const auto device : deviceManager.getAllDevices())
    {
        if (!device or !device->isPresent())
        {
            spdlog::error("Device list contains invalid element");
            continue;
        }

        for (const auto& capability : device->getCapabilities())
        {
            if (capability->getType() == device::CapabilityType::Sensor and shouldStoreSensor(capability->getSubType()))
            {
                spdlog::info(
                    "Logging sensor value: sensor={} name={} value={}",
                    device->getIdentifier(),
                    capability->getName(),
                    capability->getValue());
                entries.emplace_back(protocol::metrics::Entry{capability->getName(), capability->getValue()});
            }
        }
    }
    metricsServer.store(entries);
}
} // namespace metrics
