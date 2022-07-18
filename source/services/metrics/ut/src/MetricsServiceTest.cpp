#include "services/metrics/MetricsService.hpp"
#include <gtest/gtest.h>
#include "device/CapabilityMock.hpp"
#include "device/DeviceMock.hpp"
#include "itf/DeviceManagerMock.hpp"
#include "protocol/metrics/MetricsServerMock.hpp"
#include "timer/TimerManagerMock.hpp"

using namespace testing;

namespace metrics
{
class MetricsServiceTest : public Test
{
public:
    void storeTimerCallback()
    {
        EXPECT_CALL(timerManagerMock, createTimer(_, _))
            .WillOnce(
                [&](auto arg, auto)
                {
                    timerCallback = std::move(arg);
                    return nullptr;
                });
    }

    std::shared_ptr<NiceMock<device::CapabilityMock>> buildDeviceCapability(
        const std::string& capabilityName, const double value)
    {
        std::shared_ptr<NiceMock<device::CapabilityMock>> capabilityMock
            = std::make_shared<NiceMock<device::CapabilityMock>>();

        EXPECT_CALL(*capabilityMock, getName()).WillRepeatedly(ReturnRef(capabilityName));
        EXPECT_CALL(*capabilityMock, getValue()).WillRepeatedly(Return(value));

        return capabilityMock;
    }

    StrictMock<timer::TimerManagerMock> timerManagerMock;
    NiceMock<core::DeviceManagerMock> deviceManagerMock;
    NiceMock<protocol::metrics::MetricsServerMock> metricsServerMock;

    timer::TimerCallback timerCallback;
};

TEST_F(MetricsServiceTest, shouldStartTimerWhenCreated)
{
    EXPECT_CALL(timerManagerMock, createTimer(_, _)).Times(1);
    MetricsService sut{timerManagerMock, deviceManagerMock, metricsServerMock};
}

TEST_F(MetricsServiceTest, shouldCallStoreOnceWhenTimerExpired)
{
    storeTimerCallback();
    MetricsService sut{timerManagerMock, deviceManagerMock, metricsServerMock};
    EXPECT_CALL(metricsServerMock, store(_)).Times(1);
    EXPECT_CALL(deviceManagerMock, getAllDevices()).WillRepeatedly(Return(device::DeviceRange{}));
    timerCallback();
}

TEST_F(MetricsServiceTest, shouldAddAllSensorValuesToEntriesListForSingleDevice)
{
    using protocol::metrics::Entry;

    const std::string capability1Name{"Capability1"};
    const std::string capability2Name{"Capability2"};
    constexpr double capability1value{2137};
    constexpr double capability2value{666};
    const std::string deviceIdentifier{"Device"};

    std::shared_ptr<NiceMock<device::DeviceMock>> deviceMock = std::make_shared<NiceMock<device::DeviceMock>>();
    std::vector<std::shared_ptr<device::IDevice>> devicesList{deviceMock};

    device::Capabilities capabilities{
        buildDeviceCapability(capability1Name, capability1value),
        buildDeviceCapability(capability2Name, capability2value)};

    storeTimerCallback();
    MetricsService sut{timerManagerMock, deviceManagerMock, metricsServerMock};

    EXPECT_CALL(
        metricsServerMock,
        store(UnorderedElementsAre(Entry{capability1Name, capability1value}, Entry{capability2Name, capability2value})))
        .Times(1);
    EXPECT_CALL(deviceManagerMock, getAllDevices()).WillRepeatedly(Return(devicesList));

    EXPECT_CALL(*deviceMock, getCapabilities()).WillOnce(ReturnRef(capabilities));
    EXPECT_CALL(*deviceMock, getIdentifier()).WillRepeatedly(ReturnRef(deviceIdentifier));
    EXPECT_CALL(*deviceMock, isPresent()).WillRepeatedly(Return(true));
    timerCallback();
}
} // namespace metrics
