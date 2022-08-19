#pragma once
#include "protocol/http/Method.hpp"

namespace protocol::http
{
class IHttpRequest
{
public:
    virtual ~IHttpRequest() = default;
    virtual void setUrl(const std::string&) = 0;
    virtual void setMethod(const Method) = 0;
    virtual void setContent(const std::string&) = 0;
    virtual void setAuthorization(const std::string&) = 0;
    virtual void execute() = 0;

    virtual std::uint16_t getResponseCode() = 0;
};
} // namespace protocol::http
