#pragma once
#include <gmock/gmock.h>
#include "protocol/http/IHttpRequestFactory.hpp"

namespace protocol::http
{
class HttpRequestFactoryMock : public IHttpRequestFactory
{
public:
    MOCK_METHOD0(create, std::unique_ptr<IHttpRequest>());
};
} // namespace protocol::http
