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

std::vector<std::shared_ptr<GrepModel>> FileModel::getGrepsVector() const
{
  return greps;
}

std::shared_ptr<GrepModel> FileModel::grep(std::shared_ptr<GrepModel> grep, std::string pattern)
{
  types::TextView::Container newLines;
  auto baseTextView = grep->getTextView();
  // TODO: wait for sealed?
  baseTextView->applyFunctionToSlice(
      [&](types::TextView::Iterator begin, types::TextView::Iterator end) {
        for (auto it = begin; it != end; it++)
          if (it->find(pattern) != std::string::npos)
            newLines.push_back(*it);
      },
      0,
      baseTextView->size());
  auto newTextView = std::make_shared<types::TextView>();
  newTextView->append(std::move(newLines));
  auto newGrep = std::make_shared<GrepModel>(pattern, newTextView);
  greps.emplace_back(newGrep);
  return newGrep;
}
} // namespace perg::model
