#pragma once

#include <ncurses.h>
#include <string>
#include <memory>

#include "Controller.hpp"
#include "StatusBar.hpp"
#include "Minibuffer.hpp"

class ApplicationController : public Controller
{
public:
  ApplicationController(WINDOW * window);

  void run();

  void openFile(const std::string& filePath);

private:
  std::shared_ptr<StatusBar> mStatusBar;
  std::shared_ptr<Minibuffer> mMinibuffer;
};
