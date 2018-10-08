#include "TextWindowController.hpp"
#include "KeyboardInput.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "TextWindow.hpp"
#include "types/KeyPressed.hpp"
#include "types/Region.hpp"

namespace perg::presenter
{
TextWindowController::TextWindowController(
    std::shared_ptr<types::TextView> textView,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses)
    : textView{textView}
    , keyboardInput{keyboardInput}
    , ncurses{ncurses}
    , textWindow{std::make_unique<tui::TextWindow>(
          ncurses.createWindow(types::Region{
              0,
              0,
              ncurses.getRegion().cols,
              ncurses.getRegion().rows - 2,
          }),
          textView)}
    , handlers{{
          {"<Down>", std::bind(&tui::TextWindow::moveCursorDown, textWindow.get())},
      }}
{
}

types::KeyPressed TextWindowController::awaitEvent()
{
  textWindow->render();
  while (true)
  {
    types::KeyPressed keyPressed{keyboardInput.awaitKeyPressed()};
    if (handlers.find(keyPressed.keystroke) != handlers.end())
    {
      handlers.at(keyPressed.keystroke)();
      textWindow->render();
    }
    else
    {
      return keyPressed;
    }
  }
}
} // namespace perg::presenter
