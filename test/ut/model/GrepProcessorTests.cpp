#include <thread>

#include <gtest/gtest.h>

#include "GrepProcessor.hpp"
#include "TextView.hpp"

namespace
{
const perg::types::TextView::Container full_text{
    "=aaa",
    "=bbb",
    "=cccx",
    "=ddd",
    "=eeex",
    "=fff",
    "=ggg",
    "=hhh",
    "=jjj",
};

const perg::types::TextView::Container chunk_1{
    "=aaa",
    "=bbb",
    "=cccx",
};

const perg::types::TextView::Container chunk_2{
    "=ddd",
    "=eeex",
    "=fff",
};

const perg::types::TextView::Container chunk_3{
    "=ggg",
    "=hhh",
    "=jjj",
};

const perg::types::TextView::Container xs_part{
    "=cccx",
    "=eeex",
};

const perg::types::TextView::Container empty_text{};

perg::types::TextView::Container fetchContainer(std::shared_ptr<perg::types::TextView> textView)
{
  perg::types::TextView::Container collected{};
  textView->applyFunctionToSlice(
      [&collected](perg::types::TextView::Iterator begin, perg::types::TextView::Iterator end) {
        for (auto it = begin; it != end; it++)
        {
          collected.push_back(*it);
        }
      },
      0u,
      textView->size());
  return collected;
}
} // namespace

namespace perg::model
{
struct GrepProcessorTests : public ::testing::Test
{
  GrepProcessorTests() : input{std::make_shared<types::TextView>()} {}
  std::shared_ptr<types::TextView> input;
};

TEST_F(GrepProcessorTests, NothingToGrep)
{
  std::thread thread([&]() { input->seal(); });
  GrepProcessor gp(input, "=");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), empty_text);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, EmptyGrepping)
{
  std::thread thread([&]() {
    auto full_text_clone{full_text};
    input->append(std::move(full_text_clone));
    input->seal();
  });
  GrepProcessor gp(input, "asdf");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), empty_text);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, BatchGreppingAllMatch)
{
  std::thread thread([&]() {
    auto full_text_clone{full_text};
    input->append(std::move(full_text_clone));
    input->seal();
  });
  GrepProcessor gp(input, "=");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), full_text);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, BatchGreppingSomeMatch)
{
  std::thread thread([&]() {
    auto full_text_clone{full_text};
    input->append(std::move(full_text_clone));
    input->seal();
  });
  GrepProcessor gp(input, "x");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), xs_part);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, ChunkByChunkGreppingAllMatch)
{
  using namespace std::chrono_literals;
  std::thread thread([&]() {
    auto chunk{chunk_1};
    input->append(std::move(chunk));
    std::this_thread::sleep_for(10ms);
    chunk = chunk_2;
    input->append(std::move(chunk));
    std::this_thread::sleep_for(10ms);
    chunk = chunk_3;
    input->append(std::move(chunk));
    std::this_thread::sleep_for(10ms);
    input->seal();
  });
  GrepProcessor gp(input, "=");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), full_text);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, ChunkByChunkGreppingSomeMatch)
{
  using namespace std::chrono_literals;
  std::thread thread([&]() {
    auto chunk{chunk_1};
    input->append(std::move(chunk));
    std::this_thread::sleep_for(10ms);
    chunk = chunk_2;
    input->append(std::move(chunk));
    std::this_thread::sleep_for(10ms);
    chunk = chunk_3;
    input->append(std::move(chunk));
    std::this_thread::sleep_for(10ms);
    input->seal();
  });
  GrepProcessor gp(input, "x");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), xs_part);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, ChunkByChunkGreppingAllMatchSleepless)
{
  std::thread thread([&]() {
    auto chunk{chunk_1};
    input->append(std::move(chunk));
    chunk = chunk_2;
    input->append(std::move(chunk));
    chunk = chunk_3;
    input->append(std::move(chunk));
    input->seal();
  });
  GrepProcessor gp(input, "=");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), full_text);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, ChunkByChunkGreppingSomeMatchSleepless)
{
  std::thread thread([&]() {
    auto chunk{chunk_1};
    input->append(std::move(chunk));
    chunk = chunk_2;
    input->append(std::move(chunk));
    chunk = chunk_3;
    input->append(std::move(chunk));
    input->seal();
  });
  GrepProcessor gp(input, "x");
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), xs_part);
  EXPECT_TRUE(gp.getTextView()->sealed());
}

TEST_F(GrepProcessorTests, ChunkByChunkGreppingInTheMiddle)
{
  GrepProcessor gp(input, "x");
  std::size_t grepSizeInTheMiddle;
  std::thread thread([&]() {
    auto chunk{chunk_1};
    input->append(std::move(chunk));
    chunk = chunk_2;
    input->append(std::move(chunk));
    grepSizeInTheMiddle = gp.getTextView()->waitForSizeAtLeast(2u);
    chunk = chunk_3;
    input->append(std::move(chunk));
    input->seal();
  });
  thread.join();
  gp.getTextView()->waitForSealed();
  EXPECT_EQ(fetchContainer(gp.getTextView()), xs_part);
  EXPECT_EQ(grepSizeInTheMiddle, xs_part.size());
  EXPECT_TRUE(gp.getTextView()->sealed());
}
} // namespace perg::model
