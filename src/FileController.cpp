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
  std::unique_ptr<model::TextModel> text{new model::TextModel{fileModel.lines}};
  auto textWindow = std::make_unique<TextWindowController>(*text, keyboardInput, ncurses);
  greps.emplace_back(std::move(text), std::move(textWindow));
}

types::KeyPressed FileController::awaitEvent()
{
  while (true)
  {
    auto& textWindow = greps.back().second;
    auto keyPressed = textWindow->awaitEvent();
    if (keyPressed.keystroke != "g") // TODO: take from config
    {
      return keyPressed;
    }
    auto grepPattern = minibuffer.readText("Grep: ");
    std::vector<std::string> newLines;
    for (const auto& line : greps.back().first->lines)
    {
      if (line.find(grepPattern) != std::string::npos)
      {
        newLines.push_back(line);
      }
    }
    std::unique_ptr<model::TextModel> newText{new model::TextModel{newLines}};
    auto newTextWindow = std::make_unique<TextWindowController>(*newText, keyboardInput, ncurses);
    greps.emplace_back(std::move(newText), std::move(newTextWindow));
  }
  return types::KeyPressed{""};
}
} // namespace perg::presenter
