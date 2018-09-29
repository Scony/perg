#include "FileController.hpp"
#include "FileModel.hpp"
#include "NcursesWindow.hpp"
#include "TextModel.hpp"
#include "TextWindow.hpp"
#include "TextWindowController.hpp"

namespace perg::presenter
{
FileController::FileController(
    model::FileModel& fileModel,
    tui::KeyboardInput& keyboardInput,
    tui::Ncurses& ncurses)
    : fileModel{fileModel}, keyboardInput{keyboardInput}, ncurses{ncurses}
{
}

void FileController::awaitEvent()
{
  model::TextModel text{fileModel.lines};
  TextWindowController textWindow{text, keyboardInput, ncurses};
  textWindow.awaitEvent();
}
} // namespace perg::presenter
