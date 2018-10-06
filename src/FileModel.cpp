#include <fstream>
#include <memory>

#include "FileModel.hpp"
#include "FileReader.hpp"
#include "GrepModel.hpp"
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
  greps.emplace_back(std::make_shared<GrepModel>(filepath.leaf().string(), textView));
}

boost::filesystem::path FileModel::getFilepath() const
{
  return filepath;
}

std::vector<std::shared_ptr<GrepModel>> FileModel::getGrepsVector()
{
  return greps;
}
} // namespace perg::model
