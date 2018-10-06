#pragma once

#include <memory>

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

 private:
  std::unique_ptr<NcursesWindow> window;
  std::shared_ptr<types::TextView> textView;
};
} // namespace perg::tui
