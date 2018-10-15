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
struct Configuration;
} // namespace perg::types

namespace perg::presenter
{
class TextWindowController
{
 public:
  TextWindowController(
      types::Configuration&,
      std::shared_ptr<types::TextView>,
      tui::KeyboardInput&,
      tui::Ncurses&);

  types::KeyPressed awaitEvent();

 private:
  types::Configuration& configuration;
  std::shared_ptr<types::TextView> textView;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
  std::unique_ptr<tui::TextWindow> textWindow;
  const std::map<std::string, std::function<void()>> handlers;
};
} // namespace perg::presenter
