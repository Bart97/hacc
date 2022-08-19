#include "protocol/http/HttpRequest.hpp"
#include <boost/throw_exception.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>
#include <mutex>
#include "spdlog/spdlog.h"

namespace protocol::http
{
HttpRequest::HttpRequest()
    : request()
{
    request.setOpt(curlpp::Options::Verbose(false));
    request.setOpt(curlpp::options::WriteStream(&responseStream));
    header.emplace_back("Content-Type: text/plain; charset=utf-8");
    header.emplace_back("Accept: application/json");
}

void HttpRequest::setUrl(const std::string& url)
{
    request.setOpt(curlpp::options::Url(url));
}

void HttpRequest::setMethod(const Method method)
{
    switch (method)
    {
        case Method::Get:
            request.setOpt(curlpp::Options::HttpGet(true));
            return;

        case Method::Post:
            request.setOpt(curlpp::Options::Post(true));
            return;

        case Method::Put:
            request.setOpt(curlpp::Options::Put(true));
            return;
    }

    BOOST_THROW_EXCEPTION(std::runtime_error("Unexpected method"));
}

void HttpRequest::setContent(const std::string& content)
{
    if (content.length() > std::numeric_limits<long>::max())
    {
        BOOST_THROW_EXCEPTION(std::runtime_error("Request content length exceeded max long value."));
    }
    request.setOpt(curlpp::Options::PostFields(content));
    request.setOpt(curlpp::Options::PostFieldSize(static_cast<long>(content.length())));
}

void HttpRequest::setAuthorization(const std::string& string)
{
    header.emplace_back("Authorization: " + string);
}

void HttpRequest::execute()
{
    request.setOpt(curlpp::Options::HttpHeader(header));
    try
    {
        request.perform();
    }
    catch (curlpp::LibcurlRuntimeError& e)
    {
        BOOST_THROW_EXCEPTION(std::runtime_error(e.what()));
    }
}

std::uint16_t HttpRequest::getResponseCode()
{
    return curlpp::infos::ResponseCode::get(request);
}
} // namespace protocol::http
