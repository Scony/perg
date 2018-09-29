#include "FileController.hpp"
#include "FileModel.hpp"
#include "Minibuffer.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "TextModel.hpp"
#include "TextWindow.hpp"
#include "TextWindowController.hpp"
#include "types/KeyPressed.hpp"

namespace perg::presenter
{
FileController::FileController(
    model::FileModel& fileModel,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses,
    tui::Minibuffer& minibuffer)
    : fileModel{fileModel}, keyboardInput{keyboardInput}, ncurses{ncurses}, minibuffer{minibuffer}
{
}

types::KeyPressed FileController::awaitEvent()
{
  model::TextModel text{fileModel.lines};
  TextWindowController textWindow{text, keyboardInput, ncurses};
  auto keyPressed = textWindow.awaitEvent();
  if (keyPressed.keystroke == "g") // TODO: take from config
  {
    auto grepPattern = minibuffer.readText("Grep: ");
    std::vector<std::string> newLines;
    for (const auto& line : text.lines)
    {
      if (line.find(grepPattern) != std::string::npos)
      {
        newLines.push_back(line);
      }
    }
    model::TextModel newText{newLines};
    TextWindowController newTextWindow{newText, keyboardInput, ncurses};
    // textWindow.clear();
    // textWindow.refresh();
    return newTextWindow.awaitEvent();
  }
  return keyPressed;
}
} // namespace perg::presenter
