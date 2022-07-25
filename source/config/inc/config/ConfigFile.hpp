#pragma once
#include <json/value.h>
#include <string>

namespace config
{
class ConfigFile
{
public:
    explicit ConfigFile(const std::string&);

    const Json::Value& getJson() const;
    const Json::Value& get(const std::string&) const;

private:
    Json::Value json;
};
} // namespace config
