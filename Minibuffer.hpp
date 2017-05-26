#pragma once

#include <ncurses.h>

#include "Window.hpp"

class Minibuffer : public Window
{
public:
  Minibuffer(int x, int y, int cols); // rows = 1
  ~Minibuffer();

  void render();

private:
  WINDOW * mWindow;
};
