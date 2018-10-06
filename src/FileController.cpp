#include "FileController.hpp"
#include "Configuration.hpp"
#include "FileModel.hpp"
#include "GrepModel.hpp"
#include "Minibuffer.hpp"
#include "Ncurses.hpp"
#include "NcursesWindow.hpp"
#include "TextModel.hpp"
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
  std::vector<std::string> lines;
  fileModel.getGrepsVector()[0]->getTextView()->applyFunctionToSlice(
      [&](types::TextView::Iterator begin, types::TextView::Iterator end) {
        for (auto it = begin; it != end; it++)
          lines.push_back(std::string(*it));
      },
      0,
      fileModel.getGrepsVector()[0]->getTextView()->size());
  std::unique_ptr<model::TextModel> text{new model::TextModel{lines}};
  auto textWindow = std::make_unique<TextWindowController>(*text, keyboardInput, ncurses);
  greps.emplace_back(std::move(text), std::move(textWindow));
}

types::KeyPressed FileController::awaitEvent()
{
  while (true)
  {
    auto& textWindow = greps[visibleGrep].second;
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
    std::vector<std::string> newLines;
    for (const auto& line : greps[visibleGrep].first->lines)
    {
      if (line.find(grepPattern) != std::string::npos)
      {
        newLines.push_back(line);
      }
    }
    std::unique_ptr<model::TextModel> newText{new model::TextModel{newLines}};
    auto newTextWindow = std::make_unique<TextWindowController>(*newText, keyboardInput, ncurses);
    greps.emplace_back(std::move(newText), std::move(newTextWindow));
    visibleGrep++;
  }
  return types::KeyPressed{""};
}
} // namespace perg::presenter
