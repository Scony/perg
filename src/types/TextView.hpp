#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <string>
#include <vector>

namespace perg::types
{
class TextView
{
 public:
  using Container = std::vector<std::string_view>;
  using Iterator = Container::const_iterator;

 public:
  TextView();

  bool sealed() const;
  void seal();
  std::size_t size() const;
  std::size_t waitForSizeAtLeast(std::size_t) const;
  std::size_t waitForSealed() const;
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
