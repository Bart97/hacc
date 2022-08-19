#pragma once
#include <memory>
#include "protocol/http/IHttpRequest.hpp"

namespace protocol::http
{
class IHttpRequestFactory
{
public:
    virtual ~IHttpRequestFactory() = default;
    virtual std::unique_ptr<IHttpRequest> create() = 0;
};
} // namespace protocol::http
