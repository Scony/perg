#pragma once

#include <memory>
#include <vector>

#include <boost/filesystem.hpp>

namespace perg::types
{
struct Mark;
}

namespace perg::model
{
class IWorker;
class GrepModel;

class FileModel
{
 public:
  FileModel(boost::filesystem::path);
  ~FileModel();

  boost::filesystem::path getFilepath() const;
  std::vector<std::shared_ptr<GrepModel>> getGrepsVector() const;
  std::shared_ptr<GrepModel> grep(std::shared_ptr<GrepModel>, std::string pattern);
  const std::vector<types::Mark>& getMarks() const;
  void toggleMark(std::string text);

 private:
  const boost::filesystem::path filepath;
  std::vector<std::unique_ptr<IWorker>> workers;
  std::vector<std::shared_ptr<GrepModel>> greps;
  std::vector<types::Mark> marks;
};
} // namespace perg::model
