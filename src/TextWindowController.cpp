#include "TextWindowController.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "TextModel.hpp"
#include "TextWindow.hpp"
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

void TextWindowController::awaitEvent()
{
  textWindow->render();
}
} // namespace perg::presenter
