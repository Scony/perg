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
  std::string_view getSelectedText() const;
  void disableTextSelectionMode();

 private:
  void enableTextSelectionMode();

  types::Configuration& configuration;
  std::shared_ptr<types::TextView> textView;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
  std::unique_ptr<tui::TextWindow> textWindow;
  const std::map<std::string, std::function<void()>> defaultHandlers;
  const std::map<std::string, std::function<void()>> textSelectionHandlers;
  std::map<std::string, std::function<void()>> activeHandlers;
};
} // namespace perg::presenter
