#include "FileReader.hpp"
#include "types/Text.hpp"

namespace perg::model
{
FileReader::FileReader(boost::filesystem::path filepath) : text{std::make_shared<types::Text>()}
{
  std::vector<std::string> lines;
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
  text->append(std::move(lines));
}

std::shared_ptr<types::Text> FileReader::getText() const
{
  return text;
}
} // namespace perg::model
