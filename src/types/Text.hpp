#pragma once

#include <deque>
#include <string>

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Text
{
  std::deque<std::string> lines;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::Text,
    (std::vector<std::string>, lines)); // TODO: enable variadic macros support
