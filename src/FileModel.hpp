#pragma once

#include <boost/filesystem.hpp>

namespace perg::model
{
class FileModel
{
 public:
  FileModel(boost::filesystem::path);

  boost::filesystem::path getFilepath() const;

 private:
  const boost::filesystem::path filepath;

 public: // TODO:private
  std::vector<std::string> lines;
};
} // namespace perg::model
