#pragma once

#include <vector>
#include <string>
#include <memory>
#include <thread>

#include "TextBuffer.hpp"

class Grep
{
public:
  Grep(std::function<void(std::shared_ptr<TextBuffer>)> workerFunction,
       std::string name = "");
  virtual ~Grep();

  std::shared_ptr<Grep> grep(std::string pattern);

  int getGid();
  std::shared_ptr<TextBuffer> getBuffer();
  const std::string& getName();
  // const std::vector<Grep>& getGreps();

protected:
  static const unsigned mLinesToFlush = 10000;
  static int sNextGid;

protected:
  int mGid;
  std::shared_ptr<TextBuffer> mBuffer;
  std::string mName;
  std::thread mThread;
  // std::vector<std::shared_ptr<Grep> > mGreps;

private:
  void grepWorker(std::string pattern, std::shared_ptr<TextBuffer> output);

private:
  Grep(const Grep&) = delete;
  Grep& operator=(const Grep&) = delete;
  Grep(Grep&&) = delete;
  Grep& operator=(Grep&&) = delete;
};
