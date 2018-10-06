#pragma once

#include <memory>
#include <thread>

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
  ~FileReader();

  std::shared_ptr<types::Text> getText() const;
  std::shared_ptr<types::TextView> getTextView() const;

 private:
  const unsigned bufferFlushThreshold = 1024;

  void work();

  boost::filesystem::path filepath;
  std::shared_ptr<types::Text> text;
  std::shared_ptr<types::TextView> textView;
  std::thread thread;
};
} // namespace perg::model
