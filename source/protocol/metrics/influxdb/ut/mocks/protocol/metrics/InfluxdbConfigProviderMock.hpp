#pragma once
#include <gmock/gmock.h>
#include "protocol/metrics/IInfluxdbConfigProvider.hpp"

namespace protocol::metrics
{

class InfluxdbConfigProviderMock : public IInfluxdbConfigProvider
{
public:
    MOCK_CONST_METHOD0(getHostname, std::string());
    MOCK_CONST_METHOD0(getPort, std::uint16_t());
    MOCK_CONST_METHOD0(getDatabase, std::string());
    MOCK_CONST_METHOD0(getBucket, std::string());
    MOCK_CONST_METHOD0(getOrganization, std::string());
    MOCK_CONST_METHOD0(getApiKey, std::string());
};
} // namespace protocol::metrics
