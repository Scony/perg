#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Window.hpp"
#include "ITextBuffer.hpp"
#include "Region.hpp"
#include "Event.hpp"

class TextWindow : public Window
{
public:
  TextWindow(Region region, std::shared_ptr<ITextBuffer> buffer);
  ~TextWindow();

  Event proceed();
  void render();
  void focus();

private:
  static const unsigned mWindowTimeoutMs = 100;

  void lazyRender();

  void upHandler();
  void downHandler();
  void leftHandler();
  void rightHandler();
  void pageUpHandler();
  void pageDownHandler();

  std::shared_ptr<ITextBuffer> mBuffer;
  std::map<std::string, std::function<void()> > mActiveHandlers = {
    {"<Up>", std::bind(&TextWindow::upHandler, this)},
    {"<Down>", std::bind(&TextWindow::downHandler, this)},
    {"<Left>", std::bind(&TextWindow::leftHandler, this)},
    {"<Right>", std::bind(&TextWindow::rightHandler, this)},
    {"<PageUp>", std::bind(&TextWindow::pageUpHandler, this)},
    {"<PageDown>", std::bind(&TextWindow::pageDownHandler, this)},
  };

  int mCursorX;
  int mCursorY;
  int mTextOffsetX;
  int mTextOffsetY;

  int mPreviousTextOffsetX;
  int mPreviousTextOffsetY;
  int mPreviousBufferSize;
};
