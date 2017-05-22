#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

#include "Window.hpp"

class TextWindow : public Window
{
public:
  TextWindow(int x, int y, int cols, int rows);
  ~TextWindow();

  void setContent(std::vector<std::string> const& lines);
  void render();

private:
  WINDOW * mWindow;
  std::vector<std::string> mBuffer;
};
