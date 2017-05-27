#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Grep.hpp"
#include "StatusBar.hpp"
#include "Minibuffer.hpp"
#include "TextWindow.hpp"

class Controller
{
public:
  Controller(WINDOW * window, const std::vector<std::string>& fileNames);

  void run();

private:
  int mCols;
  int mRows;

  std::map<int, std::shared_ptr<Grep> > mGreps;
  std::map<int, std::shared_ptr<TextWindow> > mTextWindows;
  int mCurrentGid;

  std::unique_ptr<StatusBar> mStatusBar;
  std::unique_ptr<Minibuffer> mMinibuffer;

  WINDOW * mWindow;
};
