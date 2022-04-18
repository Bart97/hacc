#include <gtest/gtest.h>
#include "gateway/zigbeemqtt/Capability.hpp"
#include "gateway/zigbeemqtt/mocks/DeviceFactoryMock.hpp"
#include "protocol/mqtt/mocks/MqttClientMock.hpp"
#include "spdlog/spdlog.h"

using namespace testing;
using protocol::mqtt::MqttClientMock;

using namespace testing;

namespace gateway::zigbeemqtt
{
namespace
{
const configuration::CapabilityMapping testMapping{
        device::CapabilityType::Sensor,
        device::SensorType::Pressure,
        "testPath",
        std::nullopt};
} // namespace

class CapabilityTest : public Test
{
public:
    CapabilityTest()
    {
        spdlog::set_level(spdlog::level::debug);
    }
};

TEST_F(CapabilityTest, shouldSetCorrectType)
{
    Capability sut{testMapping};
    EXPECT_EQ(sut.getType(), device::CapabilityType::Sensor);
}

TEST_F(CapabilityTest, shouldSetCorrectSubType)
{
    Capability sut{testMapping};
    EXPECT_EQ(sut.getSubType(), device::SensorType::Pressure);
}

TEST_F(CapabilityTest, shouldSetCorrectNameWhenFriendlyNameConfigured)
{
    const std::string capabilityName = "Bob";
    auto mappingWithName = testMapping;
    mappingWithName.friendlyName = capabilityName;
    Capability sut{mappingWithName};
    EXPECT_EQ(sut.getName(), capabilityName);
}

TEST_F(CapabilityTest, shouldSetDefaultNameWhenFriendlyNameNotConfigured)
{
    Capability sut{testMapping};
    EXPECT_EQ(sut.getName(), "Pressure");
}

TEST_F(CapabilityTest, shouldReturnNaNValueAfterCreated)
{
    Capability sut{testMapping};
    EXPECT_TRUE(std::isnan(sut.getValue()));
}
} // namespace gateway::zigbeemqtt
