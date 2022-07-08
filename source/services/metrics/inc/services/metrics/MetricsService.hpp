#pragma once
#include "itf/IDeviceManager.hpp"
#include "timer/ITimerManager.hpp"

namespace metrics
{
class MetricsService
{
public:
    MetricsService(timer::ITimerManager&, core::IDeviceManager&);

private:
    void update();

    timer::ITimerManager& timerManager;
    std::unique_ptr<timer::ITimer> updateTimer;
    core::IDeviceManager& deviceManager;
};
} // namespace metrics
