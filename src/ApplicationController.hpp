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
  ApplicationController(model::ApplicationModel&, tui::KeyboardInput&, tui::Ncurses&);

  void awaitEvent(); // TODO: void -> Event

 private:
  model::ApplicationModel& applicationModel;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
};
} // namespace perg::presenter
