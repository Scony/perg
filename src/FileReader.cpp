#include <fstream>

#include "FileReader.hpp"
#include "types/Text.hpp"
#include "types/TextView.hpp"

namespace perg::model
{
FileReader::FileReader(boost::filesystem::path filepath)
    : text{std::make_shared<types::Text>()}, textView{std::make_shared<types::TextView>()}
{
  std::vector<std::string_view> lines;
  std::ifstream fileStream;
  fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fileStream.open(filepath.c_str());
  fileStream.exceptions(std::ifstream::goodbit);
  text->lines.reserve(999);
  std::string lineContent;
  while (std::getline(fileStream, lineContent))
  {
    text->lines.push_back(lineContent);
    lines.push_back(text->lines.back());
  }
  fileStream.close();
  textView->append(std::move(lines));
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
