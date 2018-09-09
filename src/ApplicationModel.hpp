#pragma once

#include <boost/filesystem.hpp>
#include <vector>

namespace perg::model
{
class ApplicationModel
{
 public:
  ApplicationModel(const std::vector<boost::filesystem::path>&);

 public: // TODO: private
  std::vector<boost::filesystem::path> filepaths;
};
} // namespace perg::model
