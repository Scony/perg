#include "FileController.hpp"
#include "Configuration.hpp"
#include "FileModel.hpp"
#include "GrepModel.hpp"
#include "Minibuffer.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
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
    tui::Minibuffer& minibuffer)
    : configuration{configuration}
    , fileModel{fileModel}
    , keyboardInput{keyboardInput}
    , ncurses{ncurses}
    , minibuffer{minibuffer}
{
  auto mainTextView = fileModel.getGrepsVector()[0]->getTextView();
  auto mainTextWindow =
      std::make_unique<TextWindowController>(mainTextView, keyboardInput, ncurses);
  greps.emplace_back(std::move(mainTextWindow));
}

types::KeyPressed FileController::awaitEvent()
{
  while (true)
  {
    auto& textWindow = greps[visibleGrep];
    auto keyPressed = textWindow->awaitEvent();
    if (keyPressed.keystroke == configuration.grep_circle_left_keystroke)
    {
      visibleGrep = visibleGrep >= 1 ? visibleGrep - 1 : greps.size() - 1;
      continue;
    }
    if (keyPressed.keystroke == configuration.grep_circle_right_keystroke)
    {
      visibleGrep = (visibleGrep + 1) % greps.size();
      continue;
    }
    if (keyPressed.keystroke != configuration.grep_keystroke)
    {
      return keyPressed;
    }
    auto grepPattern = minibuffer.readText("Grep: ");
    auto presentGrep = fileModel.getGrepsVector().at(visibleGrep);
    auto newGrep = fileModel.grep(presentGrep, grepPattern);
    auto newTextView = newGrep->getTextView();
    auto newTextWindow =
        std::make_unique<TextWindowController>(newTextView, keyboardInput, ncurses);
    greps.emplace_back(std::move(newTextWindow));
    visibleGrep++;
  }
  return types::KeyPressed{""};
}
} // namespace perg::presenter
