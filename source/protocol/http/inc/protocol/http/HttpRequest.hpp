#pragma once
#include <curlpp/Easy.hpp>
#include <sstream>
#include "protocol/http/IHttpRequest.hpp"

namespace protocol::http
{
class HttpRequest final : public IHttpRequest
{
public:
    HttpRequest();
    void setUrl(const std::string& string) override;
    void setMethod(const Method method) override;
    void setContent(const std::string& string) override;
    void execute() override;
    void setAuthorization(const std::string& string) override;
    std::uint16_t getResponseCode() override;

private:
    curlpp::Easy request;
    std::list<std::string> header;
    std::stringstream responseStream;
};
} // namespace protocol::http
