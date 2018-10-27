#include "FileController.hpp"
#include "Configuration.hpp"
#include "FileModel.hpp"
#include "GrepModel.hpp"
#include "Minibuffer.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "StatusBar.hpp"
#include "TextView.hpp"
#include "TextWindow.hpp"
#include "TextWindowController.hpp"
#include "types/KeyPressed.hpp"

namespace perg::presenter
{
FileController::FileController(
    types::Configuration& configuration,
    model::FileModel& fileModel,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses,
    tui::Minibuffer& minibuffer,
    tui::StatusBar& statusBar)
    : configuration{configuration}
    , fileModel{fileModel}
    , keyboardInput{keyboardInput}
    , ncurses{ncurses}
    , minibuffer{minibuffer}
    , statusBar{statusBar}
{
  auto mainTextView = fileModel.getGrepsVector().at(0)->getTextView();
  auto mainTextWindow =
      std::make_unique<TextWindowController>(configuration, mainTextView, keyboardInput, ncurses);
  greps.emplace_back(std::move(mainTextWindow));
}

types::KeyPressed FileController::awaitEvent()
{
  while (true)
  {
    auto& textWindow = greps[visibleGrep];
    auto grepName = fileModel.getGrepsVector().at(visibleGrep)->getName();
    statusBar.setText(grepName);
    statusBar.render();
    auto keyPressed = textWindow->awaitEvent();
    if (keyPressed.keystroke == configuration.keystrokes.grepCircleLeft)
    {
      visibleGrep = visibleGrep >= 1 ? visibleGrep - 1 : greps.size() - 1;
      continue;
    }
    if (keyPressed.keystroke == configuration.keystrokes.grepCircleRight)
    {
      visibleGrep = (visibleGrep + 1) % greps.size();
      continue;
    }
    if (keyPressed.keystroke != configuration.keystrokes.grep)
    {
      return keyPressed;
    }
    auto grepPattern = minibuffer.readText("Grep: ");
    auto presentGrep = fileModel.getGrepsVector().at(visibleGrep);
    auto newGrep = fileModel.grep(presentGrep, grepPattern);
    auto newTextView = newGrep->getTextView();
    auto newTextWindow =
        std::make_unique<TextWindowController>(configuration, newTextView, keyboardInput, ncurses);
    greps.emplace_back(std::move(newTextWindow));
    visibleGrep++;
  }
  return types::KeyPressed{""};
}
} // namespace perg::presenter
