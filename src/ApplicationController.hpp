#pragma once

namespace perg::model
{
class ApplicationModel;
}

namespace perg::tui
{
class KeyboardInput;
class Ncurses;
} // namespace perg::tui

namespace perg::presenter
{
class ApplicationController
{
 public:
  ApplicationController(
      perg::model::ApplicationModel&,
      perg::tui::KeyboardInput&,
      perg::tui::Ncurses&);

  void awaitEvent(); // TODO: void -> Event

 private:
  perg::model::ApplicationModel& applicationModel;
  perg::tui::KeyboardInput& keyboardInput;
  perg::tui::Ncurses& ncurses;
};
} // namespace perg::presenter
