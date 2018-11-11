#pragma once

#include <memory>

#include "types/Position.hpp"
#include "types/TextView.hpp"

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
  void enableTextSelection();
  void disableTextSelection();

 private:
  std::string_view getCurrentLine() const;
  types::Position getCursorPositionInText() const;
  void setCursorPositionInText(types::Position);
  void renderingVisitor(types::TextView::Iterator begin, types::TextView::Iterator end);
  std::optional<types::Position> getSelectionMarkPositionInWindow() const;

  std::unique_ptr<NcursesWindow> window;
  std::shared_ptr<types::TextView> textView;
  types::Position cursorPosition{0, 0};
  types::Position windowPositionInText{0, 0};
  std::optional<types::Position> selectionMarkPositionInText;
};
} // namespace perg::tui
