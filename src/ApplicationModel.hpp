#pragma once

#include <string>
#include <vector>

namespace perg::model
{
class ApplicationModel
{
 public:
  ApplicationModel(const std::vector<std::string>& filepaths);

 public: // TODO: private
  std::vector<std::string> filepaths;
};
} // namespace perg::model
