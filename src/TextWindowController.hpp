#pragma once

#include <functional>
#include <map>
#include <memory>

namespace perg::tui
{
class KeyboardInput;
class Ncurses;
class TextWindow;
} // namespace perg::tui

namespace perg::types
{
struct KeyPressed;
class TextView;
} // namespace perg::types

namespace perg::presenter
{
class TextWindowController
{
 public:
  TextWindowController(std::shared_ptr<types::TextView>, tui::KeyboardInput&, tui::Ncurses&);

  types::KeyPressed awaitEvent();

 private:
  std::shared_ptr<types::TextView> textView;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
  std::unique_ptr<tui::TextWindow> textWindow;
  const std::map<std::string, std::function<void()>> handlers;
};
} // namespace perg::presenter
