#include "ApplicationModel.hpp"
#include "FileModel.hpp"
#include "GrepModel.hpp"
#include "IWorker.hpp"
#include "exceptions/FileOpenError.hpp"

namespace perg::model
{
ApplicationModel::ApplicationModel(const std::vector<boost::filesystem::path>& filepaths)
    : fileModels{}
{
  for (const auto& filepath : filepaths)
  {
    try
    {
      auto fileModel = std::make_shared<FileModel>(filepath);
      fileModels.push_back(fileModel);
    }
    catch (perg::exceptions::FileOpenError&)
    {
    }
  }
}

std::vector<std::shared_ptr<FileModel>> ApplicationModel::getFileModels()
{
  return fileModels;
}
} // namespace perg::model
