#include "TextWindowController.hpp"
#include "KeyboardInput.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "TextModel.hpp"
#include "TextWindow.hpp"
#include "types/KeyPressed.hpp"
#include "types/Region.hpp"

namespace perg::presenter
{
TextWindowController::TextWindowController(
    model::TextModel& textModel,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses)
    : textModel{textModel}
    , keyboardInput{keyboardInput}
    , ncurses{ncurses}
    , textWindow{std::make_unique<tui::TextWindow>(
          ncurses.createWindow(types::Region{
              0,
              0,
              ncurses.getRegion().cols,
              ncurses.getRegion().rows - 2,
          }),
          textModel.lines)}
{
}

types::KeyPressed TextWindowController::awaitEvent()
{
  textWindow->render();
  types::KeyPressed keyPressed{keyboardInput.awaitKeyPressed()};
  return keyPressed;
}
} // namespace perg::presenter
