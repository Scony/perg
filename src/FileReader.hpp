#pragma once

#include <memory>

#include <boost/filesystem.hpp>

#include "IWorker.hpp"

namespace perg::types
{
struct Text;
class TextView;
} // namespace perg::types

namespace perg::model
{
class FileReader : public IWorker
{
 public:
  FileReader(boost::filesystem::path);

  std::shared_ptr<types::Text> getText() const;
  std::shared_ptr<types::TextView> getTextView() const;

 private:
  std::shared_ptr<types::Text> text;
  std::shared_ptr<types::TextView> textView;
};
} // namespace perg::model
