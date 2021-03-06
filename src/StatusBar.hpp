#pragma once

#include <memory>

namespace perg::tui
{
class NcursesWindow;

class StatusBar
{
 public:
  StatusBar(std::unique_ptr<NcursesWindow>);

  void setText(const std::string&);
  void render();

 private:
  std::unique_ptr<NcursesWindow> window;
  std::string text;
};
} // namespace perg::tui
