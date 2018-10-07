#pragma once

#include <memory>
#include <thread>

#include "IWorker.hpp"

namespace perg::types
{
class TextView;
}

namespace perg::model
{
class GrepProcessor : public IWorker
{
 public:
  GrepProcessor(std::shared_ptr<types::TextView>, std::string substring);
  ~GrepProcessor();

  std::shared_ptr<types::TextView> getTextView() const;

 private:
  void work(std::string substring);

  std::shared_ptr<types::TextView> inputTextView;
  std::shared_ptr<types::TextView> outputTextView;
  std::thread thread;
};
} // namespace perg::model
