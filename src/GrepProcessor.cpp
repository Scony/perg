#include "GrepProcessor.hpp"
#include "types/TextView.hpp"

namespace perg::model
{
GrepProcessor::GrepProcessor(std::shared_ptr<types::TextView> inputTextView, std::string substring)
    : inputTextView{inputTextView}
    , outputTextView{std::make_shared<types::TextView>()}
    , thread(&GrepProcessor::work, this, substring)
{
}

GrepProcessor::~GrepProcessor()
{
  thread.join();
}

std::shared_ptr<types::TextView> GrepProcessor::getTextView() const
{
  return outputTextView;
}

void GrepProcessor::work(std::string substring)
{
  types::TextView::Container buffer{};
  std::size_t nextPosToCheck{0u};
  while (true)
  {
    auto knownSize = inputTextView->waitForSizeAtLeast(nextPosToCheck + 1u);
    if (knownSize >= nextPosToCheck + 1u)
    {
      if (isStopped())
      {
        break;
      }
      auto lenToCheck = knownSize - nextPosToCheck;
      inputTextView->applyFunctionToSlice(
          [&buffer, &substring](types::TextView::Iterator begin, types::TextView::Iterator end) {
            for (auto it = begin; it != end; it++)
            {
              if (it->find(substring) != std::string::npos)
              {
                buffer.push_back(*it);
              }
            }
          },
          nextPosToCheck,
          lenToCheck);
      outputTextView->append(std::move(buffer));
      buffer.clear();
      nextPosToCheck = knownSize;
    }
    else
    {
      break;
    }
  }
  outputTextView->seal();
}
} // namespace perg::model
