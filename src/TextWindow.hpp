#pragma once

#include <memory>
#include <vector>

#include "types/Position.hpp"
#include "types/TextView.hpp"

namespace perg::types
{
struct Mark;
}

namespace perg::tui
{
class NcursesWindow;

class TextWindow
{
 public:
  TextWindow(
      std::unique_ptr<NcursesWindow>,
      std::shared_ptr<types::TextView>,
      const std::vector<types::Mark>&);

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
  std::string_view getSelectedText() const;

 private:
  std::string_view getCurrentLine() const;
  types::Position getCursorPositionInText() const;
  void setCursorPositionInText(types::Position);
  void renderingVisitor(types::TextView::Iterator begin, types::TextView::Iterator end);
  std::optional<types::Position> getSelectionMarkPositionInWindow() const;
  void printVisibleLineFragment(const std::size_t& y, const std::string_view& line);
  void highlightMarkedLineFragments(const std::size_t& y, const std::string_view& line);
  void highlightSelectedLineFragment(const std::size_t& y, const std::string_view& line);

  std::unique_ptr<NcursesWindow> window;
  std::shared_ptr<types::TextView> textView;
  const std::vector<types::Mark>& marks;

  types::Position cursorPosition{0, 0};
  types::Position windowPositionInText{0, 0};
  std::optional<types::Position> selectionMarkPositionInText;
};
} // namespace perg::tui
