#include <fstream>

#include "FileModel.hpp"
#include "FileReader.hpp"

namespace perg::model
{
FileModel::FileModel(boost::filesystem::path filepath) : filepath{filepath}
{
  std::ifstream fileStream;
  fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fileStream.open(filepath.c_str());
  fileStream.close();

  auto reader = std::make_unique<FileReader>(filepath);
  auto text = reader->getText();
  workers.push_back(std::move(reader));
  text->applyFunctionToSlice(
      [&](types::Text::Iterator begin, types::Text::Iterator end) {
        for (auto it = begin; it != end; it++)
          lines.push_back(*it);
      },
      0,
      text->size());
}

boost::filesystem::path FileModel::getFilepath() const
{
  return filepath;
}
} // namespace perg::model
