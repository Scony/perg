#pragma once

#include <ncurses.h>
#include <string>

#include "Window.hpp"

class Minibuffer : public Window
{
public:
  Minibuffer(int x, int y, int cols); // rows = 1
  ~Minibuffer();

  void setContent(std::string content);
  void render();

private:
  WINDOW * mWindow;
};
