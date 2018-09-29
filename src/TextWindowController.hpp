#pragma once

#include <memory>

namespace perg::model
{
struct TextModel;
}

namespace perg::tui
{
class KeyboardInput;
class Ncurses;
class TextWindow;
} // namespace perg::tui

namespace perg::presenter
{
class TextWindowController
{
 public:
  TextWindowController(model::TextModel&, tui::KeyboardInput&, tui::Ncurses&);

  void awaitEvent(); // TODO: void -> Event

 private:
  model::TextModel& textModel;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
  std::unique_ptr<tui::TextWindow> textWindow;
};
} // namespace perg::presenter
