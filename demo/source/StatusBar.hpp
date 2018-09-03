#pragma once

#include "Window.hpp"
#include "Region.hpp"

class StatusBar : public Window
{
public:
  StatusBar(Region region);
  ~StatusBar();

  void setContent(std::string content);
  void render();

private:
  std::string mContent;
  std::string mPreviousContent;
};
