#include "ApplicationController.hpp"
#include "ApplicationModel.hpp"
#include "Configuration.hpp"
#include "FileController.hpp"
#include "FileModel.hpp"
#include "KeyboardInput.hpp"
#include "Minibuffer.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "Region.hpp"
#include "StatusBar.hpp"
#include "TextWindow.hpp"
#include "TextWindowController.hpp"
#include "types/KeyPressed.hpp"

namespace perg::presenter
{
ApplicationController::ApplicationController(
    types::Configuration& configuration,
    model::ApplicationModel& applicationModel,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses)
    : configuration{configuration}
    , applicationModel{applicationModel}
    , keyboardInput{keyboardInput}
    , ncurses{ncurses}
{
}

void ApplicationController::awaitEvent()
{
  ncurses.printw("Welcome to perg, multi-grep-like tool.\n");
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
  if (not applicationModel.getFileModels().empty())
  {
    for (const auto& fileModel : applicationModel.getFileModels())
    {
      auto fileController = FileController{
          configuration,
          *fileModel,
          keyboardInput,
          ncurses,
          minibuffer,
      };
      while (true)
      {
        auto keyPressed = fileController.awaitEvent();
        if (keyPressed.keystroke == configuration.quit_keystroke)
        {
          return;
        }
        minibuffer.setText(keyPressed.keystroke);
        minibuffer.render();
      }
    }
  }
  else
  {
    while (true)
    {
      auto keystroke = keyboardInput.awaitKeyPressed();
      if (keystroke != configuration.quit_keystroke)
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
}
} // namespace perg::presenter
