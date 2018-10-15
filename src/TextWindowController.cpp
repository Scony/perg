#include "TextWindowController.hpp"
#include "KeyboardInput.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "TextWindow.hpp"
#include "types/Configuration.hpp"
#include "types/KeyPressed.hpp"
#include "types/Region.hpp"

namespace perg::presenter
{
TextWindowController::TextWindowController(
    types::Configuration& configuration,
    std::shared_ptr<types::TextView> textView,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses)
    : configuration{configuration}
    , textView{textView}
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
          {
              configuration.keystrokes.cursorDown,
              std::bind(&tui::TextWindow::moveCursorDown, textWindow.get()),
          },
          {
              configuration.keystrokes.cursorUp,
              std::bind(&tui::TextWindow::moveCursorUp, textWindow.get()),
          },
          {
              configuration.keystrokes.pageDown,
              std::bind(&tui::TextWindow::movePageDown, textWindow.get()),
          },
          {
              configuration.keystrokes.pageUp,
              std::bind(&tui::TextWindow::movePageUp, textWindow.get()),
          },
          {
              configuration.keystrokes.textEnd,
              std::bind(&tui::TextWindow::moveToTheTextEnd, textWindow.get()),
          },
          {
              configuration.keystrokes.textBegin,
              std::bind(&tui::TextWindow::moveToTheTextBegin, textWindow.get()),
          },
          {
              configuration.keystrokes.cursorRight,
              std::bind(&tui::TextWindow::moveCursorRight, textWindow.get()),
          },
          {
              configuration.keystrokes.cursorLeft,
              std::bind(&tui::TextWindow::moveCursorLeft, textWindow.get()),
          },
          {
              configuration.keystrokes.wordRight,
              std::bind(&tui::TextWindow::moveCursorOneWordRight, textWindow.get()),
          },
          {
              configuration.keystrokes.wordLeft,
              std::bind(&tui::TextWindow::moveCursorOneWordLeft, textWindow.get()),
          },
          {
              configuration.keystrokes.lineEnd,
              std::bind(&tui::TextWindow::moveCursorToLineEnd, textWindow.get()),
          },
          {
              configuration.keystrokes.lineBegin,
              std::bind(&tui::TextWindow::moveCursorToLineBegin, textWindow.get()),
          },
      }}
{
}

types::KeyPressed TextWindowController::awaitEvent()
{
  textWindow->render();
  while (true)
  {
    types::KeyPressed keyPressed{keyboardInput.awaitKeyPressed(configuration.keyPressTimeout)};
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
