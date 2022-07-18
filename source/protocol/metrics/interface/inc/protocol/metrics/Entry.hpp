#pragma once
#include <ostream>
#include <string>
#include <variant>
#include <vector>
#include "spdlog/fmt/ostr.h"

namespace protocol::metrics
{
struct Entry
{
    using Value = std::variant<std::string, double>;
    std::string name;
    Value value;

    bool operator==(const protocol::metrics::Entry&) const;
};

std::ostream& operator<<(std::ostream&, const Entry&);

using Entries = std::vector<Entry>;
} // namespace protocol::metrics
