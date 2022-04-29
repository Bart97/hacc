#include "gateway/zigbeemqtt/messages/Device.hpp"
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <json/json.h>

namespace gateway::zigbeemqtt::messages
{
namespace
{
DeviceType convert(const std::string& in)
{
    const std::string s = boost::algorithm::to_lower_copy(in);
    if (s == "coordinator")
        return DeviceType::Coordinator;
    else if (s == "router")
        return DeviceType::Router;
    else if (s == "enddevice")
        return DeviceType::EndDevice;

    BOOST_THROW_EXCEPTION(std::runtime_error("Unknown device type."));
}

Device deserialize(const Json::Value& json)
{
    return {
        json["friendly_name"].asString(),
        json["ieee_address"].asString(),
        json["manufacturer"].asString(),
        json["model_id"].asString(),
        convert(json["type"].asString())};
}
} // namespace

Devices deserializeDevices(const std::string& jsonStr)
{
    Json::Reader reader;
    Json::Value json;
    reader.parse(jsonStr, json);
    Devices result{};
    result.reserve(json.size());
    std::transform(json.begin(), json.end(), std::back_inserter(result), &deserialize);

    return result;
}
} // namespace gateway::zigbeemqtt::messages
