#include "config/ConfigFile.hpp"
#include <fstream>
#include <json/reader.h>

namespace config
{
ConfigFile::ConfigFile(const std::string& filename)
{
    std::ifstream configFile(filename, std::ifstream::binary);
    if (not configFile.good())
    {
        throw std::runtime_error{"Could not open config file"};
    }
    configFile >> json;
}

const Json::Value& ConfigFile::getJson() const
{
    return json;
}

const Json::Value& ConfigFile::get(const std::string& key) const
{
    return json[key];
}
} // namespace config
