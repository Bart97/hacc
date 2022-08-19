#pragma once
#include <boost/range/any_range.hpp>
#include <deque>
#include <memory>
#include <string>
#include <variant>
#include "util/Timestamp.hpp"

namespace protocol::metrics::influxdb
{
class Point
{
public:
    using FieldValue = std::variant<double, std::int64_t, std::uint64_t, std::string, bool>;
    using Tag = std::pair<std::string, std::string>;
    using Field = std::pair<std::string, FieldValue>;

    explicit Point(const std::string& measurement);

    void addTag(const std::string& key, const std::string& value);
    void addField(const std::string& key, const FieldValue& value);

    std::string toLineProtocol() const;

private:
    std::string measurement;
    std::deque<Tag> tags;
    std::deque<Field> fields;
    util::Timestamp timestamp;
};

using PointRange = boost::any_range<Point, boost::forward_traversal_tag>;
} // namespace protocol::metrics::influxdb
