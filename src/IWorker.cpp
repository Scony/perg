#include "IWorker.hpp"

namespace perg::model
{
void IWorker::stop()
{
  std::lock_guard<std::mutex> lock(stopFlagGuard);
  stopFlag = true;
}

bool IWorker::isStopped() const
{
  std::lock_guard<std::mutex> lock(stopFlagGuard);
  return stopFlag;
}
} // namespace perg::model
