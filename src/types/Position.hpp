#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Position
{
  unsigned x;
  unsigned y;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(perg::types::Position, (unsigned, x)(unsigned, y));
