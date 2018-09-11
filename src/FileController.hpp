#pragma once

namespace perg::model
{
class FileModel;
}

namespace perg::tui
{
class KeyboardInput;
class Ncurses;
} // namespace perg::tui

namespace perg::presenter
{
class FileController
{
 public:
  FileController(model::FileModel&, tui::KeyboardInput&, tui::Ncurses&);

  void awaitEvent(); // TODO: void -> Event

 private:
  model::FileModel& fileModel;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
};
} // namespace perg::presenter
