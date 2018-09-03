#pragma once

#include <vector>
#include <string>

class Mark
{
public:
  Mark(std::string text) : mText(text), mColor(rand()) {}
  Mark(const Mark& other) : mText(other.mText), mColor(other.mColor) {}

  Mark& operator=(Mark&& other)
  {
    mText = other.mText;
    mColor = other.mColor;
  }

  std::string getText() const { return mText; }
  int getColor() const { return mColor; }

private:
  std::string mText;
  int mColor;
};

using Marks = std::vector<Mark>;
