#include <gtest/gtest.h>

#include "Grep.hpp"

TEST(GrepTests, Init) {		// TODO: use gmock
  int x = 0;
  auto f = [&](std::shared_ptr<TextBuffer> _) {
    x = 1;
  };
  Grep g(f, "name");
  EXPECT_EQ(x, 1);
  EXPECT_EQ(g.getName(), "name");
}
