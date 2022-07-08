#include "core/DeviceManager.hpp"
#include <boost/range/empty.hpp>
#include <gtest/gtest.h>
#include "device/DeviceMock.hpp"
#include "itf/GatewayMock.hpp"

using namespace testing;

namespace core
{
class DeviceManagerTest : public ::testing::Test
{
public:
    DeviceManager sut{};
    std::shared_ptr<::testing::StrictMock<gateway::GatewayMock>> gatewayMock{
        std::make_shared<::testing::StrictMock<gateway::GatewayMock>>()};
    std::shared_ptr<::testing::NiceMock<device::DeviceMock>> deviceMock{
        std::make_shared<::testing::NiceMock<device::DeviceMock>>()};
};

TEST_F(DeviceManagerTest, getDeviceByName_shouldReturnNullptrWhenNoGateways)
{
    EXPECT_EQ(sut.getDeviceByName("DummyName"), nullptr);
}

TEST_F(DeviceManagerTest, getDeviceByName_shouldReturnPointerWhenDeviceIsPresent)
{
    const std::string deviceName{"dummyName"};
    sut.addGateway(gatewayMock);
    EXPECT_CALL(*gatewayMock, getDeviceByName(deviceName)).WillOnce(Return(deviceMock));
    EXPECT_EQ(sut.getDeviceByName(deviceName), deviceMock);
}

TEST_F(DeviceManagerTest, getAllDevices_shouldReturnEmptyRangeWhenNoGatewaysRegistered)
{
    EXPECT_TRUE(boost::empty(sut.getAllDevices()));
}

TEST_F(DeviceManagerTest, getAllDevices_shouldReturnRangeWithDevicesFromAllGateways)
{
    const std::vector<std::shared_ptr<device::IDevice>> deviceList1{deviceMock};
    EXPECT_CALL(*gatewayMock, getAllDevices()).WillOnce(Return(deviceList1));

    std::shared_ptr<::testing::StrictMock<gateway::GatewayMock>> gatewayMock2{
        std::make_shared<::testing::StrictMock<gateway::GatewayMock>>()};
    std::shared_ptr<::testing::NiceMock<device::DeviceMock>> deviceMock2{
        std::make_shared<::testing::NiceMock<device::DeviceMock>>()};
    const std::vector<std::shared_ptr<device::IDevice>> deviceList2{deviceMock2};
    EXPECT_CALL(*gatewayMock2, getAllDevices()).WillOnce(Return(deviceList2));

    sut.addGateway(gatewayMock);
    sut.addGateway(gatewayMock2);

    const std::vector<std::shared_ptr<device::IDevice>> allDevices{deviceMock, deviceMock2};

    EXPECT_THAT(sut.getAllDevices(), ElementsAreArray(allDevices));
}

} // namespace core
