#include <cassert>

#include "TextView.hpp"

namespace perg::types
{
TextView::TextView() : container{}, container_sealed{false} {}

bool TextView::sealed() const
{
  std::lock_guard<std::recursive_mutex> lock(mutex);
  return container_sealed;
}

void TextView::seal()
{
  std::lock_guard<std::recursive_mutex> lock(mutex);
  container_sealed = true;
}

std::size_t TextView::size() const
{
  std::lock_guard<std::recursive_mutex> lock(mutex);
  return container.size();
}

std::size_t TextView::waitForSizeAtLeast(std::size_t size) const
{
  std::unique_lock<std::recursive_mutex> lock(mutex);
  newData.wait(lock, [&]() { return container.size() >= size or container_sealed; });
  return container.size();
}

void TextView::append(Container&& data)
{
  std::lock_guard<std::recursive_mutex> lock(mutex);
  container.insert(container.end(), data.begin(), data.end()); // TODO: use std::make_move_iterator?
  newData.notify_all();
}

void TextView::reset(Container&& data)
{
  std::lock_guard<std::recursive_mutex> lock(mutex);
  container.clear();
  append(std::move(data));
}

void TextView::applyFunctionToSlice(
    std::function<void(Iterator, Iterator)> function,
    std::size_t pos,
    std::size_t len) const
{
  std::lock_guard<std::recursive_mutex> lock(mutex);
  assert(pos <= container.size());
  assert(pos + len <= container.size());
  function(container.cbegin() + pos, container.cbegin() + pos + len);
}
} // namespace perg::types
