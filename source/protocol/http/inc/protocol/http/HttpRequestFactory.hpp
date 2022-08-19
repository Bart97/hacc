#pragma once
#include <memory>
#include "protocol/http/IHttpRequestFactory.hpp"

namespace protocol::http
{
class IHttpRequest;
class HttpRequestFactory final : public IHttpRequestFactory
{
public:
    HttpRequestFactory() = default;
    HttpRequestFactory(const HttpRequestFactory&) = delete;
    HttpRequestFactory& operator=(const HttpRequestFactory&) = delete;
    virtual std::unique_ptr<IHttpRequest> create() override;
};
} // namespace protocol::http
