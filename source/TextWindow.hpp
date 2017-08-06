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
#include "Mark.hpp"

class TextWindow : public Window
{
public:
  TextWindow(Region region,
	     std::shared_ptr<ITextBuffer> buffer,
	     std::shared_ptr<Marks> marks = std::make_shared<Marks>());
  ~TextWindow();

  Event proceed();
  void render();
  void focus();
  std::string getCurrentLine();
  std::string getSelectedText();

private:
  static const unsigned mWindowTimeoutMs = 100;

  void lazyRender();

  void upHandler();
  void downHandler();
  void leftHandler();
  void rightHandler();
  void pageUpHandler();
  void pageDownHandler();
  void lineBeginHandler();
  void lineEndHandler();
  void wordLeftHandler();
  void wordRightHandler();
  void textBeginHandler();
  void textEndHandler();
  void selectBeginHandler();
  void selectEndHandler();

  void enableStandardMode();
  void enableTextSelectionMode();

  std::map<std::string, std::function<void()> > mActiveHandlers;

  std::map<std::string, std::function<void()> > mStandardModeHandlers = {
    {"<Up>", std::bind(&TextWindow::upHandler, this)},
    {"<Down>", std::bind(&TextWindow::downHandler, this)},
    {"<Left>", std::bind(&TextWindow::leftHandler, this)},
    {"<Right>", std::bind(&TextWindow::rightHandler, this)},
    {"<PageUp>", std::bind(&TextWindow::pageUpHandler, this)},
    {"<PageDown>", std::bind(&TextWindow::pageDownHandler, this)},
    {"<C-a>", std::bind(&TextWindow::lineBeginHandler, this)},
    {"<C-e>", std::bind(&TextWindow::lineEndHandler, this)},
    {"<C-Left>", std::bind(&TextWindow::wordLeftHandler, this)},
    {"<C-Right>", std::bind(&TextWindow::wordRightHandler, this)},
    {"<M-Left>", std::bind(&TextWindow::wordLeftHandler, this)},
    {"<M-Right>", std::bind(&TextWindow::wordRightHandler, this)},
    {"<M-<>", std::bind(&TextWindow::textBeginHandler, this)},
    {"<M->>", std::bind(&TextWindow::textEndHandler, this)},
    {"<C- >", std::bind(&TextWindow::selectBeginHandler, this)},
  };

  std::map<std::string, std::function<void()> > mTextSelectionModeHandlers = {
    {"<Left>", std::bind(&TextWindow::leftHandler, this)},
    {"<Right>", std::bind(&TextWindow::rightHandler, this)},
    {"<C-a>", std::bind(&TextWindow::lineBeginHandler, this)},
    {"<C-e>", std::bind(&TextWindow::lineEndHandler, this)},
    {"<C-Left>", std::bind(&TextWindow::wordLeftHandler, this)},
    {"<C-Right>", std::bind(&TextWindow::wordRightHandler, this)},
    {"<M-Left>", std::bind(&TextWindow::wordLeftHandler, this)},
    {"<M-Right>", std::bind(&TextWindow::wordRightHandler, this)},
    {"<C- >", std::bind(&TextWindow::selectBeginHandler, this)},
    {"<C-g>", std::bind(&TextWindow::selectEndHandler, this)},
  };

  std::shared_ptr<ITextBuffer> mBuffer;
  std::shared_ptr<Marks> mMarks;

  int mCursorX;
  int mCursorY;
  int mTextOffsetX;
  int mTextOffsetY;
  int mSelectionBeginX;
  int mSelectionBeginY;

  int mPreviousTextOffsetX;
  int mPreviousTextOffsetY;
  int mPreviousBufferSize;
  int mPreviousMarksSize;
};
