#include <cassert>

#include "TextView.hpp"

namespace perg::types
{
TextView::TextView() : container{}, container_sealed{false} {}

bool TextView::sealed() const
{
  std::lock_guard<std::mutex> lock(mutex);
  return container_sealed;
}

void TextView::seal()
{
  std::lock_guard<std::mutex> lock(mutex);
  container_sealed = true;
  newData.notify_all();
}

std::size_t TextView::size() const
{
  std::lock_guard<std::mutex> lock(mutex);
  return container.size();
}

std::size_t TextView::waitForSizeAtLeast(std::size_t size) const
{
  std::unique_lock<std::mutex> lock(mutex);
  newData.wait(lock, [&]() { return container.size() >= size or container_sealed; });
  return container.size();
}

std::size_t TextView::waitForSealed() const
{
  std::unique_lock<std::mutex> lock(mutex);
  newData.wait(lock, [&]() { return container_sealed; });
  return container.size();
}

void TextView::append(Container&& data)
{
  std::lock_guard<std::mutex> lock(mutex);
  container.insert(container.end(), data.begin(), data.end()); // TODO: use std::make_move_iterator?
  newData.notify_all();
}

void TextView::applyFunctionToSlice(
    std::function<void(Iterator, Iterator)> function,
    std::size_t pos,
    std::size_t len) const
{
  std::lock_guard<std::mutex> lock(mutex);
  assert(pos <= container.size()); // TODO: gsl::Expects
  assert(pos + len <= container.size()); // TODO: gsl::Expects
  function(container.cbegin() + pos, container.cbegin() + pos + len);
}
} // namespace perg::types
