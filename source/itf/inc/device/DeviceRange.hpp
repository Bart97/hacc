#pragma once
#include <boost/range/any_range.hpp>
#include <memory>

namespace device
{
class IDevice;
using DeviceRange = boost::
    any_range<std::shared_ptr<IDevice>, boost::forward_traversal_tag, std::shared_ptr<IDevice>, std::ptrdiff_t>;
} // namespace device
