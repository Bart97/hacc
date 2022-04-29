#include "gateway/zigbeemqtt/ZigbeeMqttGateway.hpp"
#include <gtest/gtest.h>
#include "gateway/zigbeemqtt/mocks/DeviceFactoryMock.hpp"
#include "protocol/mqtt/mocks/MqttClientMock.hpp"

using namespace testing;
using protocol::mqtt::MqttClientMock;

namespace gateway::zigbeemqtt
{
class ZigbeeMqttGatewayTest : public Test
{
public:
    ZigbeeMqttGatewayTest() { }

    std::unique_ptr<StrictMock<DeviceFactoryMock>> deviceFactoryMockPtr
        = std::make_unique<StrictMock<DeviceFactoryMock>>();
    StrictMock<DeviceFactoryMock>* deviceFactoryMock = deviceFactoryMockPtr.get();
    std::shared_ptr<StrictMock<MqttClientMock>> mqttClientMockPtr = std::make_shared<StrictMock<MqttClientMock>>();
    StrictMock<MqttClientMock>* mqttClientMock = mqttClientMockPtr.get();
};

TEST_F(ZigbeeMqttGatewayTest, shouldSubscribeToDevicesOnCreation)
{
    EXPECT_CALL(*mqttClientMock, subscribe("zigbee2mqtt/bridge/devices", _));
    ZigbeeMqttGateway sut{mqttClientMockPtr, std::move(deviceFactoryMockPtr)};
}
} // namespace gateway::zigbeemqtt
