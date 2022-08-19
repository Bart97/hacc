#include "protocol/http/HttpRequestFactory.hpp"
#include "protocol/http/HttpRequest.hpp"

namespace protocol::http
{
std::unique_ptr<IHttpRequest> HttpRequestFactory::create()
{
    return std::make_unique<HttpRequest>();
}
} // namespace protocol::http
