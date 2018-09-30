#include <cassert>

#include "Text.hpp"

namespace perg::types
{
Text::Text() : container{}, container_sealed{false} {}

bool Text::sealed() const
{
  std::lock_guard<std::mutex> lock(mutex);
  return container_sealed;
}

void Text::seal()
{
  std::lock_guard<std::mutex> lock(mutex);
  container_sealed = true;
}

std::size_t Text::size() const
{
  std::lock_guard<std::mutex> lock(mutex);
  return container.size();
}

std::size_t Text::waitForSizeAtLeast(std::size_t size) const
{
  std::unique_lock<std::mutex> lock(mutex);
  newData.wait(lock, [&]() { return container.size() >= size or container_sealed; });
  return container.size();
}

void Text::append(Container&& data)
{
  std::lock_guard<std::mutex> lock(mutex);
  container.insert(container.end(), data.begin(), data.end()); // TODO: use std::make_move_iterator?
  newData.notify_all();
}

void Text::applyFunctionToSlice(
    std::function<void(Iterator, Iterator)> function,
    std::size_t pos,
    std::size_t len) const
{
  std::lock_guard<std::mutex> lock(mutex);
  assert(pos <= container.size());
  assert(pos + len <= container.size());
  function(container.cbegin() + pos, container.cbegin() + pos + len);
}
} // namespace perg::types
