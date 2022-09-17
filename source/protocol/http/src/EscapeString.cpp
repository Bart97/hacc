#include "protocol/http/EscapeString.hpp"
#include <curlpp/cURLpp.hpp>

namespace protocol::http
{
std::string escapeString(const std::string& str)
{
    return curlpp::escape(str);
}
} // namespace protocol::http
