#include "protocol/metrics/influxdb/v2/InfluxdbApiV2.hpp"
#include <gtest/gtest.h>
#include "protocol/http/HttpRequestFactory.hpp"
#include "protocol/http/HttpRequestFactoryMock.hpp"
#include "protocol/http/HttpRequestMock.hpp"
#include "protocol/metrics/InfluxdbConfigProviderMock.hpp"

namespace
{
const std::string configHostname{"localhost"};
const std::string configBucket{"dummyBucket"};
const std::string configOrganization{"testOrg"};
const std::string configApiKey{"YOMOMA"};
constexpr std::uint16_t configPort{2137};
} // namespace

namespace protocol::metrics::influxdb::v2
{
using namespace ::testing;

class InfluxdbApiV2Test : public Test
{
public:
    InfluxdbApiV2Test()
    {
        setupDefaultConfig();
    }

    Point createDummyPoint() const
    {
        Point point{"DUMMY"};
        point.addField("val", 1);
        point.addTag("testTag", "foo");
        return point;
    }

    void setupDefaultConfig()
    {
        ON_CALL(configProvider, getHostname()).WillByDefault(Return(configHostname));
        ON_CALL(configProvider, getPort()).WillByDefault(Return(configPort));
        EXPECT_CALL(configProvider, getDatabase()).Times(0);
        ON_CALL(configProvider, getBucket()).WillByDefault(Return(configBucket));
        ON_CALL(configProvider, getOrganization()).WillByDefault(Return(configOrganization));
        ON_CALL(configProvider, getApiKey()).WillByDefault(Return(configApiKey));
    }
    NiceMock<InfluxdbConfigProviderMock> configProvider{};
    StrictMock<protocol::http::HttpRequestFactoryMock> httpRequestFactoryMock;
};

TEST_F(InfluxdbApiV2Test, writeWithSinglePoint_shouldBuildCorrectRequest)
{
    const std::uint16_t successfulResponseCode{204};
    const auto testPoint = createDummyPoint();
    InfluxdbApiV2 sut{httpRequestFactoryMock, configProvider};

    std::unique_ptr<StrictMock<http::HttpRequestMock>> requestMockPtr
        = std::make_unique<StrictMock<http::HttpRequestMock>>();
    const auto& requestMock = requestMockPtr.get();
    EXPECT_CALL(httpRequestFactoryMock, create()).WillOnce(Return(ByMove(std::move(requestMockPtr))));

    EXPECT_CALL(*requestMock, setUrl("localhost:2137/api/v2/write?bucket=dummyBucket&org=testOrg&precision=ns"));
    EXPECT_CALL(*requestMock, setMethod(http::Method::Post));
    EXPECT_CALL(*requestMock, setAuthorization("Token YOMOMA"));
    EXPECT_CALL(*requestMock, setContent(testPoint.toLineProtocol() + "\n"));
    EXPECT_CALL(*requestMock, execute());
    EXPECT_CALL(*requestMock, getResponseCode()).WillOnce(Return(successfulResponseCode));
    sut.write(testPoint);
}

TEST_F(InfluxdbApiV2Test, writeWithSinglePoint_shouldThrowIf401ResponseReceived)
{
    const std::uint16_t authenticationErrorResponseCode{401};
    const auto testPoint = createDummyPoint();
    InfluxdbApiV2 sut{httpRequestFactoryMock, configProvider};

    std::unique_ptr<StrictMock<http::HttpRequestMock>> requestMockPtr
        = std::make_unique<StrictMock<http::HttpRequestMock>>();
    const auto& requestMock = requestMockPtr.get();
    EXPECT_CALL(httpRequestFactoryMock, create()).WillOnce(Return(ByMove(std::move(requestMockPtr))));

    EXPECT_CALL(*requestMock, setUrl(_));
    EXPECT_CALL(*requestMock, setMethod(http::Method::Post));
    EXPECT_CALL(*requestMock, setAuthorization("Token YOMOMA"));
    EXPECT_CALL(*requestMock, setContent(testPoint.toLineProtocol() + "\n"));
    EXPECT_CALL(*requestMock, execute());
    EXPECT_CALL(*requestMock, getResponseCode()).WillOnce(Return(authenticationErrorResponseCode));
    EXPECT_THROW(sut.write(testPoint), std::runtime_error);
}
} // namespace protocol::metrics::influxdb::v2
