#pragma once

#include <string>

#include "Window.hpp"
#include "Region.hpp"

class Minibuffer : public Window
{
public:
  Minibuffer(Region region);
  ~Minibuffer();

  void setContent(std::string content);
  std::string readStr();
  void render();
};
