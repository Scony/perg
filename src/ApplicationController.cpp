#include "ApplicationController.hpp"
#include "ApplicationModel.hpp"
#include "FileModel.hpp"
#include "KeyboardInput.hpp"
#include "Ncurses.hpp"
#include "Region.hpp"

namespace perg::presenter
{
ApplicationController::ApplicationController(
    model::ApplicationModel& applicationModel,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses)
    : applicationModel{applicationModel}, keyboardInput{keyboardInput}, ncurses{ncurses}
{
  ncurses.printw("It works!\n");
  for (const auto& fileModel : applicationModel.getFileModels())
  {
    const auto& filepath = fileModel->getFilepath();
    ncurses.printw(filepath.string() + "\n");
  }
  ncurses.printw("\n");
  auto region = ncurses.getRegion();
  ncurses.printw("Rows: " + std::to_string(region.rows) + "\n");
  ncurses.printw("Cols: " + std::to_string(region.cols) + "\n");
  ncurses.refresh();
  keyboardInput.awaitKeyPressed();
}

void ApplicationController::awaitEvent() {}
} // namespace perg::presenter
