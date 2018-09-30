#include <fstream>

#include "FileReader.hpp"
#include "types/Text.hpp"
#include "types/TextView.hpp"

namespace perg::model
{
FileReader::FileReader(boost::filesystem::path filepath)
    : text{std::make_shared<types::Text>()}, textView{std::make_shared<types::TextView>()}
{
  std::ifstream fileStream;
  fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fileStream.open(filepath.c_str());
  fileStream.exceptions(std::ifstream::goodbit);
  std::string lineContent;
  while (std::getline(fileStream, lineContent))
  {
    text->lines.push_back(lineContent);
  }
  fileStream.close();

  std::vector<std::string_view> lineViews;
  for (const auto& line : text->lines)
  {
    lineViews.emplace_back(line);
  }
  textView->reset(std::move(lineViews));
}

std::shared_ptr<types::Text> FileReader::getText() const
{
  return text;
}

std::shared_ptr<types::TextView> FileReader::getTextView() const
{
  return textView;
}
} // namespace perg::model
