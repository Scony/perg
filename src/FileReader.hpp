#pragma once

#include <memory>

#include <boost/filesystem.hpp>

#include "IWorker.hpp"

namespace perg::types
{
class Text;
}

namespace perg::model
{
class FileReader : public IWorker
{
 public:
  FileReader(boost::filesystem::path);

  std::shared_ptr<types::Text> getText() const;

 private:
  std::shared_ptr<types::Text> text;
};
} // namespace perg::model
