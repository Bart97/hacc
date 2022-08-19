#pragma once
#include <gmock/gmock.h>
#include "protocol/http/IHttpRequest.hpp"

namespace protocol::http
{
class HttpRequestMock : public IHttpRequest
{
public:
    MOCK_METHOD1(setUrl, void(const std::string&));
    MOCK_METHOD1(setMethod, void(const Method));
    MOCK_METHOD1(setContent, void(const std::string&));
    MOCK_METHOD1(setAuthorization, void(const std::string&));
    MOCK_METHOD0(execute, void());
    MOCK_METHOD0(getResponseCode, std::uint16_t());
};
} // namespace protocol::http
