#include <gtest/gtest.h>
#include "gateway/zigbeemqtt/messages/Device.hpp"

namespace gateway::zigbeemqtt::messages
{
using namespace ::testing;

class DeviceDeserializerTest : public Test
{
public:
    const std::string json
        = R"([{"definition":null,"endpoints":{},"friendly_name":"Coordinator","ieee_address":"0x00124b000be86d99","interview_completed":true,"interviewing":false,"network_address":0,"supported":false,"type":"Coordinator"},{"date_code":"20201026","definition":{},"endpoints":{},"friendly_name":"0x00124b00245cf1ff","ieee_address":"0x00124b00245cf1ff","interview_completed":true,"interviewing":false,"manufacturer":"eWeLink","model_id":"TH01","network_address":64248,"power_source":"Battery","supported":true,"type":"EndDevice"},{"definition":{},"endpoints":{},"friendly_name":"Dummy","ieee_address":"0xDEADBEEF","interview_completed":true,"interviewing":false,"manufacturer":"Evil Corp","model_id":"Harambe","network_address":666,"power_source":"Battery","supported":true,"type":"Router"}])";
    const std::string jsonWithWrongType
        = R"([{"definition":null,"endpoints":{},"friendly_name":"Coordinator","ieee_address":"0x00124b000be86d99","interview_completed":true,"interviewing":false,"network_address":0,"supported":false,"type":"WRONGTYPEHERE"}])";
};

TEST_F(DeviceDeserializerTest, ShouldDeserializeAllEntries)
{
    Devices result = deserializeDevices(json);
    EXPECT_EQ(result.size(), 3);
}

TEST_F(DeviceDeserializerTest, ShouldDeserializeCorrectFriendlyName)
{
    Devices result = deserializeDevices(json);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].friendlyName, "Coordinator");
    EXPECT_EQ(result[1].friendlyName, "0x00124b00245cf1ff");
    EXPECT_EQ(result[2].friendlyName, "Dummy");
}

TEST_F(DeviceDeserializerTest, ShouldDeserializeCorrectIeeeAddress)
{
    Devices result = deserializeDevices(json);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].ieeeAddress, "0x00124b000be86d99");
    EXPECT_EQ(result[1].ieeeAddress, "0x00124b00245cf1ff");
    EXPECT_EQ(result[2].ieeeAddress, "0xDEADBEEF");
}

TEST_F(DeviceDeserializerTest, ShouldDeserializeCorrectManufacturer)
{
    Devices result = deserializeDevices(json);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].manufacturer, "");
    EXPECT_EQ(result[1].manufacturer, "eWeLink");
    EXPECT_EQ(result[2].manufacturer, "Evil Corp");
}

TEST_F(DeviceDeserializerTest, ShouldDeserializeCorrectModelId)
{
    Devices result = deserializeDevices(json);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].modelId, "");
    EXPECT_EQ(result[1].modelId, "TH01");
    EXPECT_EQ(result[2].modelId, "Harambe");
}

TEST_F(DeviceDeserializerTest, ShouldDeserializeCorrectType)
{
    Devices result = deserializeDevices(json);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].type, DeviceType::Coordinator);
    EXPECT_EQ(result[1].type, DeviceType::EndDevice);
    EXPECT_EQ(result[2].type, DeviceType::Router);
}

TEST_F(DeviceDeserializerTest, ShouldThrowOnEntryWithWrongType)
{
    EXPECT_THROW(deserializeDevices(jsonWithWrongType), std::runtime_error);
}
} // namespace gateway::zigbeemqtt
