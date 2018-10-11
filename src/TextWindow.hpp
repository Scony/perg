#pragma once

#include <memory>

#include "types/Position.hpp"

namespace perg::types
{
class TextView;
}

namespace perg::tui
{
class NcursesWindow;

class TextWindow
{
 public:
  TextWindow(std::unique_ptr<NcursesWindow>, std::shared_ptr<types::TextView>);

  void render();
  void moveCursorDown();
  void moveCursorUp();
  void movePageDown();
  void movePageUp();
  void moveToTheTextEnd();
  void moveToTheTextBegin();
  void moveCursorRight();
  void moveCursorLeft();
  void moveCursorOneWordRight();
  void moveCursorOneWordLeft();
  void moveCursorToLineEnd();
  void moveCursorToLineBegin();

 private:
  std::string_view getCurrentLine() const;
  types::Position getCursorPositionInText() const;
  void setCursorPositionInText(types::Position);

  std::unique_ptr<NcursesWindow> window;
  std::shared_ptr<types::TextView> textView;
  types::Position cursorPosition{0, 0};
  types::Position windowPositionInText{0, 0};
};
} // namespace perg::tui
