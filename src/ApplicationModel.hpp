#pragma once

#include <filesystem>
#include <vector>

namespace perg::model
{
class ApplicationModel
{
 public:
  ApplicationModel(const std::vector<std::filesystem::path>&);

 public: // TODO: private
  std::vector<std::filesystem::path> filepaths;
};
} // namespace perg::model
