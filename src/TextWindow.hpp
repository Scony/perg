#pragma once

#include <memory>
#include <string>
#include <vector>

namespace perg::tui
{
class NcursesWindow;

class TextWindow
{
 public:
  TextWindow(std::unique_ptr<NcursesWindow>, const std::vector<std::string>&);

  void render();

 private:
  std::unique_ptr<NcursesWindow> window;
  const std::vector<std::string>& lines;
};
} // namespace perg::tui
