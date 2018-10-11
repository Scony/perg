#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Position
{
  std::size_t x;
  std::size_t y;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(perg::types::Position, (std::size_t, x)(std::size_t, y));
