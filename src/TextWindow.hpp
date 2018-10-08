#pragma once

#include <memory>

#include "types/Position.hpp"

namespace perg::types
{
class TextView;
}

namespace perg::tui
{
class NcursesWindow;

class TextWindow
{
 public:
  TextWindow(std::unique_ptr<NcursesWindow>, std::shared_ptr<types::TextView>);

  void render();
  void moveCursorDown();

 private:
  std::unique_ptr<NcursesWindow> window;
  std::shared_ptr<types::TextView> textView;
  types::Position cursorPosition{0, 0};
  types::Position visibleTextPosition{0, 0};
};
} // namespace perg::tui
