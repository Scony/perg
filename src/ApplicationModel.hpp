#pragma once

#include <boost/filesystem.hpp>
#include <vector>

namespace perg::model
{
class FileModel;

class ApplicationModel
{
 public:
  ApplicationModel(const std::vector<boost::filesystem::path>&);

  std::vector<std::shared_ptr<FileModel>> getFileModels();

 private:
  std::vector<std::shared_ptr<FileModel>> fileModels;
};
} // namespace perg::model
