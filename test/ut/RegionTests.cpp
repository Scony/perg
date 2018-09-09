#include <gtest/gtest.h>

#include "Region.hpp"

namespace perg::types
{
TEST(RegionTests, TestConstruction)
{
  Region region{1, 2, 3, 4};
  EXPECT_EQ(region.x, 1u);
  EXPECT_EQ(region.y, 2u);
  EXPECT_EQ(region.cols, 3u);
  EXPECT_EQ(region.rows, 4u);
}
} // namespace perg::types
