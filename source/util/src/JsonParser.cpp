#include "util/JsonParser.hpp"
#include <json/reader.h>

namespace util
{
Json::Value parseJson(std::istream& stream)
{
    Json::Value json;
    stream >> json;
    return json;
}

Json::Value parseJson(const std::string& str)
{
    std::stringstream stream{str};
    return parseJson(stream);
}
} // namespace util
