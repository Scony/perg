#include <thread>

#include <gtest/gtest.h>

#include "TextView.hpp"

namespace
{
const perg::types::TextView::Container dummy_container{
    "aaa",
    "bbb",
    "ccc",
};
}

namespace perg::types
{
struct TextViewTests : public ::testing::Test
{
  TextView text{};
};

TEST_F(TextViewTests, TestTextViewConstruction)
{
  EXPECT_EQ(text.size(), 0u);
}

TEST_F(TextViewTests, TestTextAddition)
{
  TextView::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.size(), 3u);
}

TEST_F(TextViewTests, TestTextViewSealed)
{
  EXPECT_FALSE(text.sealed());
  TextView::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.size(), 3u);
  text.seal();
  EXPECT_TRUE(text.sealed());
  // TODO: test if append throws exception now
}

TEST_F(TextViewTests, TestTextViewIteration)
{
  TextView::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.size(), 3u);
  EXPECT_EQ(container.size(), 3u);
  TextView::Container collected{};
  text.applyFunctionToSlice(
      [&collected](TextView::Iterator begin, TextView::Iterator end) {
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

TEST_F(TextViewTests, TestWaitForSizeAtLeastInstant)
{
  TextView::Container container = dummy_container;
  text.append(std::move(container));
  EXPECT_EQ(text.waitForSizeAtLeast(2u), 3u);
  EXPECT_EQ(text.waitForSizeAtLeast(3u), 3u);
}

TEST_F(TextViewTests, TestWaitForSizeAtLeastLowerIfSealed)
{
  TextView::Container container = dummy_container;
  text.append(std::move(container));
  text.seal();
  EXPECT_EQ(text.waitForSizeAtLeast(4u), 3u);
}

TEST_F(TextViewTests, TestWaitForSizeAtLeastBlocking)
{
  std::size_t returnedSize{0u};
  auto consumer = std::thread([&]() { returnedSize = text.waitForSizeAtLeast(3u); });
  auto producer = std::thread([&]() {
    TextView::Container container = dummy_container;
    text.append(std::move(container));
  });
  consumer.join();
  producer.join();
  EXPECT_EQ(returnedSize, 3u);
}
} // namespace perg::types
