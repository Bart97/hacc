#pragma once
#include "itf/IDeviceManager.hpp"
#include "protocol/metrics/IMetricsServer.hpp"
#include "timer/ITimerManager.hpp"

namespace metrics
{
class MetricsService
{
public:
    MetricsService(timer::ITimerManager&, core::IDeviceManager&, protocol::metrics::IMetricsServer& metricsServer);

private:
    void update();

    timer::ITimerManager& timerManager;
    std::unique_ptr<timer::ITimer> updateTimer;
    core::IDeviceManager& deviceManager;
    protocol::metrics::IMetricsServer& metricsServer;
};
} // namespace metrics
