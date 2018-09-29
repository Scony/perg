#include "Minibuffer.hpp"
#include "NcursesWindow.hpp"

namespace perg::tui
{
Minibuffer::Minibuffer(std::unique_ptr<NcursesWindow> window) : window{std::move(window)}, text{""}
{
}

void Minibuffer::setText(std::string text)
{
  this->text = text;
}

std::string Minibuffer::readText(std::string text)
{
  setText(text);
  render();
  return window->getStr();
}

void Minibuffer::render()
{
  window->clear();
  window->mvprintw(0, 0, text);
  window->refresh();
}
}; // namespace perg::tui
