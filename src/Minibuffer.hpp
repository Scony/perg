#pragma once

#include <memory>
#include <string>

namespace perg::tui
{
class NcursesWindow;

class Minibuffer
{
 public:
  Minibuffer(std::unique_ptr<NcursesWindow>);

  void setText(std::string);
  std::string readText(std::string);
  void render();

 private:
  std::unique_ptr<NcursesWindow> window;
  std::string text;
};
} // namespace perg::tui
