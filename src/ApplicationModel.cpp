#include "ApplicationModel.hpp"
#include "FileModel.hpp"

namespace perg::model
{
ApplicationModel::ApplicationModel(const std::vector<boost::filesystem::path>& filepaths)
    : fileModels{}
{
  std::transform(
      filepaths.begin(), filepaths.end(), std::back_inserter(fileModels), [](const auto& filepath) {
        return std::make_shared<FileModel>(filepath);
      });
}

std::vector<std::shared_ptr<FileModel>> ApplicationModel::getFileModels()
{
  return fileModels;
}
} // namespace perg::model
