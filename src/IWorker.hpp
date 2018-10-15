#pragma once

#include <mutex>

namespace perg::model
{
class IWorker
{
 public:
  virtual ~IWorker() = default;
  void stop();
  bool isStopped() const;

 private:
  bool stopFlag = false;
  mutable std::mutex stopFlagGuard;
};
} // namespace perg::model
