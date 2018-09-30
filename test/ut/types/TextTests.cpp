#include <thread>

#include <gtest/gtest.h>

#include "Text.hpp"

namespace
{
const perg::types::Text::Container dummy_container{
    "aaa",
    "bbb",
    "ccc",
};
}

namespace perg::types
{
struct TextTests : public ::testing::Test
{
  Text text{};
};

TEST_F(TextTests, TestTextConstruction)
{
  EXPECT_EQ(text.size(), 0u);
}

TEST_F(TextTests, TestTextAddition)
{
  Text::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.size(), 3u);
}

TEST_F(TextTests, TestTextSealed)
{
  EXPECT_FALSE(text.sealed());
  Text::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.size(), 3u);
  text.seal();
  EXPECT_TRUE(text.sealed());
  // TODO: test if append throws exception now
}

TEST_F(TextTests, TestTextIteration)
{
  Text::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.size(), 3u);
  EXPECT_EQ(container.size(), 3u);
  Text::Container collected{};
  text.applyFunctionToSlice(
      [&collected](Text::Iterator begin, Text::Iterator end) {
        for (auto it = begin; it != end; it++)
        {
          collected.push_back(*it);
        }
      },
      0u,
      text.size());
  EXPECT_EQ(collected.size(), 3u);
  EXPECT_EQ(collected, container);
}

TEST_F(TextTests, TestWaitForSizeAtLeastInstant)
{
  Text::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.waitForSizeAtLeast(2u), 3u);
  EXPECT_EQ(text.waitForSizeAtLeast(3u), 3u);
}

TEST_F(TextTests, TestWaitForSizeAtLeastLowerIfSealed)
{
  Text::Container container = dummy_container;
  text.append(std::move(container));
  text.seal();
  EXPECT_EQ(text.waitForSizeAtLeast(4u), 3u);
}

TEST_F(TextTests, TestWaitForSizeAtLeastBlocking)
{
  std::size_t returnedSize{0u};
  auto consumer = std::thread([&]() { returnedSize = text.waitForSizeAtLeast(3u); });
  auto producer = std::thread([&]() {
    Text::Container container = dummy_container;
    text.append(std::move(container));
  });
  consumer.join();
  producer.join();
  EXPECT_EQ(returnedSize, 3u);
}
} // namespace perg::types
