#include <gtest/gtest.h>

#include "TextBuffer.hpp"

TEST(TextBufferTests, Init) {
  TextBuffer tb;
  EXPECT_EQ(tb.size(), 0);
}

TEST(TextBufferTests, AppendData) {
  TextBuffer tb;
  tb.appendData(TextBuffer::Buffer{"asdf","xyz"});
  EXPECT_EQ(tb.size(), 2);
}

TEST(TextBufferTests, ApplyFunctionToSlice1) {
  TextBuffer tb;
  tb.appendData(TextBuffer::Buffer{"aaa","bbb"});

  std::string contents = "";
  tb.applyFunctionToSlice([&](TextBuffer::Iterator a, TextBuffer::Iterator b) {
      while (a != b)
	{
	  contents += *a;
	  a++;
	}
    }, 0, 2);

  EXPECT_EQ(contents, "aaabbb");
}

TEST(TextBufferTests, ApplyFunctionToSlice2) {
  TextBuffer tb;
  tb.appendData(TextBuffer::Buffer{"aaa","bbb","ccc"});

  std::string contents = "";
  tb.applyFunctionToSlice([&](TextBuffer::Iterator a, TextBuffer::Iterator b) {
      while (a != b)
	{
	  contents += *a;
	  a++;
	}
    }, 0, 2);

  EXPECT_EQ(contents, "aaabbb");
}

TEST(TextBufferTests, ApplyFunctionToSlice3) {
  TextBuffer tb;
  tb.appendData(TextBuffer::Buffer{"aaa","bbb","ccc"});

  std::string contents = "";
  tb.applyFunctionToSlice([&](TextBuffer::Iterator a, TextBuffer::Iterator b) {
      while (a != b)
	{
	  contents += *a;
	  a++;
	}
    }, 1, 2);

  EXPECT_EQ(contents, "bbbccc");
}

TEST(TextBufferTests, WaitForNewSize1) {
  TextBuffer tb;
  tb.appendData(TextBuffer::Buffer{"aaa","bbb","ccc"});
  tb.waitForNewSize(0);
  EXPECT_EQ(1, 1);
}

TEST(TextBufferTests, WaitForNewSize2) {
  TextBuffer tb;
  tb.appendData(TextBuffer::Buffer{"aaa","bbb","ccc"});
  tb.seal();
  tb.waitForNewSize(3);
  EXPECT_EQ(1, 1);
}
