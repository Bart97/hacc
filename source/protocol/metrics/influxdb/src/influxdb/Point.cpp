#include "protocol/metrics/influxdb/Point.hpp"
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/throw_exception.hpp>
#include <spdlog/spdlog.h>

namespace
{
// TODO: Implement escaping special characters instead of throwing an exception
bool isStringValid(const std::string& tag)
{
    // https://docs.influxdata.com/influxdb/v2.3/reference/syntax/line-protocol/#special-characters
    const std::string specialTagCharacters{",= \t\n\r"};
    return tag.find_first_of(specialTagCharacters) == std::string::npos;
}
bool isFieldValueValid(const protocol::metrics::influxdb::Point::FieldValue& value)
{
    if (not std::holds_alternative<std::string>(value))
    {
        return true;
    }
    // https://docs.influxdata.com/influxdb/v2.3/reference/syntax/line-protocol/#special-characters
    const std::string specialTagCharacters{"\"\\"};
    return std::get<std::string>(value).find_first_of(specialTagCharacters) == std::string::npos;
}

// clang-format off
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

// clang-format on
std::string serialize(const protocol::metrics::influxdb::Point::FieldValue& value)
{
    return std::visit(
        overloaded{
            [](const double v) { return fmt::format("{}", v); },
            [](const bool v) { return std::string{v ? "T" : "F"}; },
            [](const std::uint64_t v) { return fmt::format("{}u", v); },
            [](const std::int64_t v) { return fmt::format_int(v).str(); },
            [](const std::string& v) { return '"' + v + '"'; }},
        value);
}
std::string serialize(const protocol::metrics::influxdb::Point::Field& field)
{
    const auto& [key, value] = field;
    return key + "=" + serialize(value);
}
} // namespace

namespace protocol::metrics::influxdb
{
Point::Point(const std::string& measurement)
    : measurement(measurement)
    , timestamp(std::chrono::system_clock::now())
{
}

void Point::addTag(const std::string& key, const std::string& value)
{
    if (not isStringValid(key) or not isStringValid(value))
    {
        BOOST_THROW_EXCEPTION(std::invalid_argument("Escaping special characters is not supported"));
    }
    tags.emplace_back(std::make_pair(key, value));
}

void Point::addField(const std::string& key, const Point::FieldValue& value)
{
    if (not isStringValid(key) or not isFieldValueValid(value))
    {
        BOOST_THROW_EXCEPTION(std::invalid_argument("Escaping special characters is not supported"));
    }
    fields.emplace_back(std::make_pair(key, value));
}

std::string Point::toLineProtocol() const
{
    if (fields.empty())
    {
        BOOST_THROW_EXCEPTION(std::runtime_error("Point must have at least one field"));
    }
    std::stringstream ss;
    ss << measurement;
    for (const auto& [key, value] : tags)
    {
        ss << "," << key << "=" << value;
    }
    ss << " ";

    ss << boost::algorithm::join(
        fields | boost::adaptors::transformed([](const auto& field) { return serialize(field); }), ",");

    ss << fmt::format(
        " {}", std::chrono::duration_cast<std::chrono::nanoseconds>(timestamp.time_since_epoch()).count());

    return ss.str();
}
} // namespace protocol::metrics::influxdb
