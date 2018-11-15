#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Mark
{
  std::string text;
  unsigned color;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::Mark,
    (std::string, text)(unsigned, color)); // TODO: enable variadic macros support
