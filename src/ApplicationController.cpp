#include "ApplicationController.hpp"
#include "ApplicationModel.hpp"
#include "FileModel.hpp"
#include "KeyboardInput.hpp"
#include "Minibuffer.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "Region.hpp"
#include "StatusBar.hpp"

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
  auto statusWindow = ncurses.createWindow(types::Region{0, region.rows - 2, region.cols, 1});
  tui::StatusBar statusBar{std::move(statusWindow)};
  statusBar.render();
  auto minibufferWindow = ncurses.createWindow(types::Region{0, region.rows - 1, region.cols, 1});
  tui::Minibuffer minibuffer{std::move(minibufferWindow)};
  minibuffer.render();
  while (true)
  {
    auto keystroke = keyboardInput.awaitKeyPressed();
    if (keystroke != "q")
    {
      minibuffer.setText(keystroke);
      minibuffer.render();
    }
    else
    {
      break;
    }
  }
}

void ApplicationController::awaitEvent() {}
} // namespace perg::presenter
