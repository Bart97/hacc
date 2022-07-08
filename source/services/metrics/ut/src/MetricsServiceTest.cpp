#include "services/metrics/MetricsService.hpp"
#include <gtest/gtest.h>
#include "itf/DeviceManagerMock.hpp"
#include "timer/TimerManagerMock.hpp"

using namespace testing;

namespace metrics
{
class MetricsServiceTest : public Test
{
public:
    StrictMock<timer::TimerManagerMock> timerManagerMock;
    NiceMock<core::DeviceManagerMock> deviceManagerMock;
};

TEST_F(MetricsServiceTest, shouldStartTimerWhenCreated)
{
    EXPECT_CALL(timerManagerMock, createTimer(_, _)).Times(1);
    MetricsService sut{timerManagerMock, deviceManagerMock};
}

} // namespace metrics
