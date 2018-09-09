#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Region
{
  const unsigned x;
  const unsigned y;
  const unsigned cols;
  const unsigned rows;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::Region,
    (const unsigned, x)(const unsigned, y)(const unsigned, cols)(
        const unsigned,
        rows)); // TODO: enable variadic macros support
