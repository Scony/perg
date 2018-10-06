#include "TextWindow.hpp"
#include "NcursesWindow.hpp"
#include "types/TextView.hpp"

namespace perg::tui
{
TextWindow::TextWindow(
    std::unique_ptr<NcursesWindow> window,
    std::shared_ptr<types::TextView> textView)
    : window{std::move(window)}, textView{textView}
{
}

void TextWindow::render()
{
  window->clear();
  textView->applyFunctionToSlice(
      [&](types::TextView::Iterator begin, types::TextView::Iterator end) {
        unsigned lineNo = 0;
        for (auto it = begin; it != end; it++)
          window->mvprintw(0, lineNo++, std::string(*it));
      },
      0,
      textView->size());
  window->refresh();
}
} // namespace perg::tui
