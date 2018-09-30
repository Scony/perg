#pragma once

#include <memory>
#include <vector>

#include <boost/filesystem.hpp>

namespace perg::model
{
class IWorker;

class FileModel
{
 public:
  FileModel(boost::filesystem::path);

  boost::filesystem::path getFilepath() const;

 private:
  const boost::filesystem::path filepath;
  std::vector<std::unique_ptr<IWorker>> workers;

 public: // TODO:private
  std::vector<std::string> lines;
};
} // namespace perg::model
