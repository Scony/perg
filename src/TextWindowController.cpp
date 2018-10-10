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
          {"<Up>", std::bind(&tui::TextWindow::moveCursorUp, textWindow.get())},
          {"<PageDown>", std::bind(&tui::TextWindow::movePageDown, textWindow.get())},
          {"<PageUp>", std::bind(&tui::TextWindow::movePageUp, textWindow.get())},
          {"<M->>", std::bind(&tui::TextWindow::moveToTheTextEnd, textWindow.get())},
          {"<M-<>", std::bind(&tui::TextWindow::moveToTheTextBegin, textWindow.get())},
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
