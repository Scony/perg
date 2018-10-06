#pragma once

#include <memory>
#include <vector>

#include <boost/filesystem.hpp>

namespace perg::model
{
class IWorker;
class GrepModel;

class FileModel
{
 public:
  FileModel(boost::filesystem::path);

  boost::filesystem::path getFilepath() const;
  std::vector<std::shared_ptr<GrepModel>> getGrepsVector();

 private:
  const boost::filesystem::path filepath;
  std::vector<std::unique_ptr<IWorker>> workers;
  std::vector<std::shared_ptr<GrepModel>> greps;
};
} // namespace perg::model
