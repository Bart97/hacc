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
    std::shared_ptr<protocol::metrics::IMetricsServer> metricsServer)
    : timerManager(timerManager)
    , deviceManager(deviceManager)
    , metricsServer(std::move(metricsServer))
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
                auto value = capability->getValue();
                if (std::isnan(value))
                {
                    continue;
                }
                spdlog::info(
                    "Logging sensor value: sensor={} name={} value={}",
                    device->getIdentifier(),
                    capability->getName(),
                    value);
                entries.emplace_back(protocol::metrics::Entry{capability->getName(), device->getIdentifier(), value});
            }
        }
    }
    try
    {
        metricsServer->store(entries);
    }
    catch (const std::exception& e)
    {
        spdlog::error("Exception thrown while storing metrics: {}", e.what());
    }
}
} // namespace metrics
