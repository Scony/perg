#include <gtest/gtest.h>

#include "Grep.hpp"

TEST(GrepTests, Init) {		// TODO: use gmock
  int x = 0;
  auto f = [&](std::shared_ptr<TextBuffer> output) {
    x = 1;
    std::vector<std::string> lines{ "xxx" };
    output->appendData(lines);
  };

  Grep g(f, "name");
  g.getBuffer()->waitForNewSize(0);

  EXPECT_EQ(x, 1);
  EXPECT_EQ(g.getName(), "name");
}
