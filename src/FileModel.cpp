#include <fstream>

#include "FileModel.hpp"
#include "FileReader.hpp"
#include "types/TextView.hpp"

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
  auto textView = reader->getTextView();
  workers.push_back(std::move(reader));
  textView->applyFunctionToSlice(
      [&](types::TextView::Iterator begin, types::TextView::Iterator end) {
        for (auto it = begin; it != end; it++)
          lines.push_back(std::string(*it));
      },
      0,
      textView->size());
}

boost::filesystem::path FileModel::getFilepath() const
{
  return filepath;
}
} // namespace perg::model
