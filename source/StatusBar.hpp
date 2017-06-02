#pragma once

#include <ncurses.h>

#include "Window.hpp"

class StatusBar : public Window
{
public:
  StatusBar(int x, int y, int cols); // rows = 1
  ~StatusBar();

  void setContent(std::string content);
  void render();

private:
  WINDOW * mWindow;
};
