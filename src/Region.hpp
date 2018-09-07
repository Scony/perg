#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::tui
{
struct Region
{
  const unsigned x;
  const unsigned y;
  const unsigned cols;
  const unsigned rows;
};
} // namespace perg::tui

BOOST_FUSION_ADAPT_STRUCT(perg::tui::Region, x, y, cols, rows);
