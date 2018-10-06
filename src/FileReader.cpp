#include <fstream>

#include "FileReader.hpp"
#include "types/Text.hpp"
#include "types/TextView.hpp"

namespace perg::model
{
FileReader::FileReader(boost::filesystem::path filepath)
    : filepath{filepath}
    , text{std::make_shared<types::Text>()}
    , textView{std::make_shared<types::TextView>()}
    , thread(&FileReader::work, this)
{
}

FileReader::~FileReader()
{
  thread.join();
}

std::shared_ptr<types::Text> FileReader::getText() const
{
  return text;
}

std::shared_ptr<types::TextView> FileReader::getTextView() const
{
  return textView;
}

void FileReader::work()
{
  std::ifstream fileStream;
  fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fileStream.open(filepath.c_str());
  fileStream.exceptions(std::ifstream::goodbit);

  std::vector<std::string_view> buffer;
  std::string line;
  while (std::getline(fileStream, line))
  {
    text->lines.push_back(line);
    buffer.push_back(text->lines.back());
    if (buffer.size() >= bufferFlushThreshold)
    {
      textView->append(std::move(buffer));
      buffer.clear();
    }
  }
  fileStream.close();
  textView->append(std::move(buffer));
  textView->seal();
}
} // namespace perg::model
