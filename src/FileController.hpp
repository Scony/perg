#pragma once

#include <memory>
#include <vector>

namespace perg::model
{
class FileModel;
struct TextModel;
} // namespace perg::model

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
class TextWindowController;

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
  std::vector<std::pair<std::unique_ptr<model::TextModel>, std::unique_ptr<TextWindowController>>>
      greps;
  std::size_t visibleGrep{0};
};
} // namespace perg::presenter
