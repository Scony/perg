#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>

namespace perg::types
{
class Text
{
 public:
  using Container = std::vector<std::string>;
  using Iterator = Container::const_iterator;

 public:
  Text();

  bool sealed() const;
  void seal();
  std::size_t size() const;
  std::size_t waitForSizeAtLeast(std::size_t) const;
  // std::size_t waitForSealed(std::size_t) const;
  void append(Container&&);
  void applyFunctionToSlice(
      std::function<void(Iterator, Iterator)>,
      std::size_t pos,
      std::size_t len) const;

 private:
  Container container;
  bool container_sealed;
  mutable std::mutex mutex;
  mutable std::condition_variable newData;
};
} // namespace perg::types
