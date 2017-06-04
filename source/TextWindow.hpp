#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>

#include "Window.hpp"
#include "TextBuffer.hpp"

class TextWindow : public Window
{
public:
  TextWindow(std::shared_ptr<TextBuffer> buffer, int x, int y, int cols, int rows);
  ~TextWindow();

  int getCh();
  void render();
private:
  static const unsigned mWindowTimeoutMs = 100;

  void forceRender();

  WINDOW * mWindow;
  std::shared_ptr<TextBuffer> mBuffer;
  int mCursorY;
  int mTextOffsetY;

  int mPreviousTextOffsetY;
  int mPreviousBufferSize;
};
