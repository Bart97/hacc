#include "protocol/metrics/Entry.hpp"
#include <tuple>
#include <variant>

namespace protocol::metrics
{
// clang-format off
namespace
{
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
} // namespace
// clang-format on

bool Entry::operator==(const protocol::metrics::Entry& b) const
{
    return std::tie(name, value) == std::tie(b.name, b.value);
}

std::ostream& operator<<(std::ostream& os, const Entry& in)
{
    os << R"({"name": ")" << in.name << R"(", "value": )";

    std::visit(
        overloaded{[&os](const double v) { os << v; }, [&os](const std::string& v) { os << '"' << v << '"'; }},
        in.value);

    return os << "}";
}
} // namespace protocol::metrics
