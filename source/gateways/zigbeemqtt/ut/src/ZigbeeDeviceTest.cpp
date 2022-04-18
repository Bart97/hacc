#include <gtest/gtest.h>
#include "gateway/zigbeemqtt/ZigbeeDevice.hpp"
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
const std::string deviceManufacturer{"Stark Corporation"};
const std::string deviceModel{"mk. 1"};
const std::string deviceAddress{"0x666"};
const messages::Device deviceInfo{"", deviceAddress, deviceManufacturer, deviceModel, messages::DeviceType::EndDevice};
} // namespace

class ZigbeeDeviceTest : public Test
{
public:
    ZigbeeDeviceTest()
    {
        spdlog::set_level(spdlog::level::debug);
    }

    std::shared_ptr<NiceMock<MqttClientMock>> mqttClientMockPtr =
            std::make_shared<NiceMock<MqttClientMock>>();
    NiceMock<MqttClientMock>* mqttClientMock = mqttClientMockPtr.get();
};

TEST_F(ZigbeeDeviceTest, shouldStoreIeeeAddressAsIdentifier)
{
    configuration::Configuration config{{deviceManufacturer, deviceModel},
                                        {}};
    ZigbeeDevice sut{deviceInfo, config, mqttClientMockPtr};
    EXPECT_EQ(sut.getIdentifier(), deviceAddress);
}

TEST_F(ZigbeeDeviceTest, shouldSubscribeToOwnTopic)
{
    configuration::Configuration config{{deviceManufacturer, deviceModel},
                                        {}};
    protocol::mqtt::PublishCallback callback;
    EXPECT_CALL(*mqttClientMock, subscribe("zigbee2mqtt/0x666", _)).WillOnce(SaveArg<1>(&callback));
    ZigbeeDevice sut{deviceInfo, config, mqttClientMockPtr};
    EXPECT_EQ(sut.getIdentifier(), deviceAddress);
    callback({"zigbee2mqtt/0x666", "Hello World!"});
}

TEST_F(ZigbeeDeviceTest, shouldAddCapabilitiesDescribedInConfig)
{
    using device::ICapability;
    configuration::Configuration config{{deviceManufacturer, deviceModel},
                                        {{
                                                 device::CapabilityType::Sensor,
                                                 device::SensorType::Pressure,
                                                 "testPath",
                                                 std::nullopt},
                                                             {
                                                                     device::CapabilityType::Sensor,
                                                                     device::SensorType::Humidity,
                                                                     "secondCapability",
                                                                     "Bob"}}};
    EXPECT_CALL(*mqttClientMock, subscribe("zigbee2mqtt/0x666", _));
    ZigbeeDevice sut{deviceInfo, config, mqttClientMockPtr};
    const auto& caps = sut.getCapabilities();
    ASSERT_EQ(caps.size(), 2);
    EXPECT_THAT(caps, UnorderedElementsAre(Pointee(Property(&ICapability::getSubType, device::SensorType::Pressure)),
                                           Pointee(Property(&ICapability::getSubType, device::SensorType::Humidity))));
}

TEST_F(ZigbeeDeviceTest, shouldUpdateCapabilitiesWhenUpdateReceived)
{
    using device::ICapability;
    configuration::Configuration config{{deviceManufacturer, deviceModel},
                                        {{
                                                 device::CapabilityType::Sensor,
                                                 device::SensorType::Pressure,
                                                 "testPath",
                                                 std::nullopt},
                                                             {
                                                                     device::CapabilityType::Sensor,
                                                                     device::SensorType::Humidity,
                                                                     "secondCapability",
                                                                     "Bob"}}};
    const std::string updateJson = R"({ "testPath": 12.34, "secondCapability": 666 })";
    protocol::mqtt::PublishCallback callback;
    EXPECT_CALL(*mqttClientMock, subscribe("zigbee2mqtt/0x666", _)).WillOnce(SaveArg<1>(&callback));
    ZigbeeDevice sut{deviceInfo, config, mqttClientMockPtr};
    callback({"zigbee2mqtt/0x666", updateJson});
    const auto& caps = sut.getCapabilities();
    ASSERT_EQ(caps.size(), 2);
    EXPECT_THAT(caps, UnorderedElementsAre(
            Pointee(AllOf(Property(&ICapability::getSubType, device::SensorType::Pressure),
                          Property(&ICapability::getValue, DoubleEq(12.34)))),
            Pointee(AllOf(Property(&ICapability::getSubType, device::SensorType::Humidity),
                          Property(&ICapability::getValue, DoubleEq(666.0))))));
}

} // namespace gateway::zigbeemqtt
