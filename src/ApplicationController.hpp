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

namespace perg::types
{
struct Configuration;
}

namespace perg::presenter
{
class ApplicationController
{
 public:
  ApplicationController(
      types::Configuration&,
      model::ApplicationModel&,
      tui::KeyboardInput&,
      tui::Ncurses&);

  void awaitEvent(); // TODO: void -> Event

 private:
  types::Configuration& configuration;
  model::ApplicationModel& applicationModel;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
};
} // namespace perg::presenter
