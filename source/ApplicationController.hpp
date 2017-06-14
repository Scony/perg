#pragma once

#include <string>
#include <memory>

#include "StatusBar.hpp"
#include "Minibuffer.hpp"
#include "Region.hpp"

class ApplicationController
{
public:
  ApplicationController(Region region);

  void run();

  void openFile(const std::string& filePath);

private:
  Region mRegion;

  std::shared_ptr<StatusBar> mStatusBar;
  std::shared_ptr<Minibuffer> mMinibuffer;
};
