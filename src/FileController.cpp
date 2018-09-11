#include "FileController.hpp"
#include "FileModel.hpp"
#include "Ncurses.hpp"

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
  ncurses.printw(fileModel.getFilepath().string() + "\n");
}
} // namespace perg::presenter
