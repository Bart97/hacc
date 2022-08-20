#pragma once
#include <json/json.h>
#include <string>

namespace util
{
Json::Value parseJson(std::istream&);
Json::Value parseJson(const std::string&);
} // namespace util
