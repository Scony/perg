#pragma once

namespace perg::model
{
class FileModel;
}

namespace perg::tui
{
class KeyboardInput;
class Ncurses;
class Minibuffer;
} // namespace perg::tui

namespace perg::types
{
struct KeyPressed;
}

namespace perg::presenter
{
class FileController
{
 public:
  FileController(model::FileModel&, tui::KeyboardInput&, tui::Ncurses&, tui::Minibuffer&);

  types::KeyPressed awaitEvent();

 private:
  model::FileModel& fileModel;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
  tui::Minibuffer& minibuffer;
};
} // namespace perg::presenter
