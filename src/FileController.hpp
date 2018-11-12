#pragma once

#include <functional>
#include <map>
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
class StatusBar;
} // namespace perg::tui

namespace perg::types
{
struct KeyPressed;
struct Configuration;
} // namespace perg::types

namespace perg::presenter
{
class TextWindowController;

class FileController
{
 public:
  FileController(
      types::Configuration&,
      model::FileModel&,
      tui::KeyboardInput&,
      tui::Ncurses&,
      tui::Minibuffer&,
      tui::StatusBar&);

  types::KeyPressed awaitEvent();

 private:
  void grepCircleLeft();
  void grepCircleRight();
  void grepBySubstring();
  void toggleTextMark();

  types::Configuration& configuration;
  model::FileModel& fileModel;
  tui::KeyboardInput& keyboardInput;
  tui::Ncurses& ncurses;
  tui::Minibuffer& minibuffer;
  tui::StatusBar& statusBar;
  std::vector<std::unique_ptr<TextWindowController>> greps;
  std::size_t visibleGrep{0};
  std::map<std::string, std::function<void()>> handlers;
};
} // namespace perg::presenter
