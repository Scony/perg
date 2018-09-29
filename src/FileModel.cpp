#include <fstream>

#include "FileModel.hpp"

namespace perg::model
{
FileModel::FileModel(boost::filesystem::path filepath) : filepath{filepath}
{
  std::ifstream fileStream;
  fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fileStream.open(filepath.c_str());
  fileStream.exceptions(std::ifstream::goodbit);
  std::string lineContent;
  while (std::getline(fileStream, lineContent))
  {
    lines.push_back(lineContent);
  }
  fileStream.close();
}

boost::filesystem::path FileModel::getFilepath() const
{
  return filepath;
}
} // namespace perg::model
