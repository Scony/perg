#include "ApplicationController.hpp"
#include "ApplicationModel.hpp"
#include "KeyboardInput.hpp"
#include "Ncurses.hpp"
#include "Region.hpp"

namespace perg::presenter
{
ApplicationController::ApplicationController(
    perg::model::ApplicationModel& applicationModel,
    perg::tui::KeyboardInput& keyboardInput,
    perg::tui::Ncurses& ncurses)
    : applicationModel{applicationModel}, keyboardInput{keyboardInput}, ncurses{ncurses}
{
  ncurses.printw("It works!\n");
  for (const auto& filepath : applicationModel.filepaths)
  {
    ncurses.printw(filepath + "\n");
  }
  ncurses.printw("\n");
  auto region = ncurses.getRegion();
  ncurses.printw("Rows: " + std::to_string(region.rows) + "\n");
  ncurses.printw("Cols: " + std::to_string(region.cols) + "\n");
  ncurses.refresh();
  perg::tui::KeyboardInput::awaitKeyPressed();
}

void ApplicationController::awaitEvent() {}
} // namespace perg::presenter
