#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Region
{
  const std::size_t x;
  const std::size_t y;
  const std::size_t cols;
  const std::size_t rows;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::Region,
    (const std::size_t, x)(const std::size_t, y)(const std::size_t, cols)(
        const std::size_t,
        rows)); // TODO: enable variadic macros support
