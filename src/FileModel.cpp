#include <fstream>
#include <memory>

#include <boost/throw_exception.hpp>

#include "FileModel.hpp"
#include "FileReader.hpp"
#include "GrepModel.hpp"
#include "GrepProcessor.hpp"
#include "exceptions/FileOpenError.hpp"
#include "types/TextView.hpp"

namespace perg::model
{
FileModel::FileModel(boost::filesystem::path filepath) : filepath{filepath}
{
  {
    std::ifstream fileStream(filepath.c_str());
    if (not fileStream)
    {
      BOOST_THROW_EXCEPTION(perg::exceptions::FileOpenError{});
    }
  }

  auto reader = std::make_unique<FileReader>(filepath);
  auto text = reader->getText();
  auto textView = reader->getTextView();
  workers.push_back(std::move(reader));
  greps.emplace_back(std::make_shared<GrepModel>(filepath.leaf().string(), textView));
}

FileModel::~FileModel()
{
  for (auto& worker : workers)
  {
    worker->stop();
  }
}

boost::filesystem::path FileModel::getFilepath() const
{
  return filepath;
}

std::vector<std::shared_ptr<GrepModel>> FileModel::getGrepsVector() const
{
  return greps;
}

std::shared_ptr<GrepModel> FileModel::grep(std::shared_ptr<GrepModel> grep, std::string substring)
{
  auto baseTextView = grep->getTextView();
  auto grepProcessor = std::make_unique<GrepProcessor>(baseTextView, substring);
  auto newTextView = grepProcessor->getTextView();
  workers.emplace_back(std::move(grepProcessor));
  auto fileName = filepath.leaf().string();
  auto grepName = fileName + ": \"" + substring + "\""; // TODO: move this logic to presenter
  auto newGrep = std::make_shared<GrepModel>(grepName, newTextView);
  greps.emplace_back(newGrep);
  return newGrep;
}
} // namespace perg::model
