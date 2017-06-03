#pragma once

#include <vector>
#include <string>
#include <memory>

#include "TextBuffer.hpp"

class Grep
{
public:
  Grep(std::function<void(std::shared_ptr<TextBuffer>)> workerFunction,
       std::string name = "");
  virtual ~Grep() {};

  std::shared_ptr<Grep> grep(std::string pattern);

  int getGid();
  std::shared_ptr<TextBuffer> getBuffer();
  const std::string& getName();
  // const std::vector<Grep>& getGreps();

protected:
  int mGid;
  std::shared_ptr<TextBuffer> mBuffer;
  std::string mName;
  // std::vector<std::shared_ptr<Grep> > mGreps;

  static int sNextGid;

private:
  Grep(const Grep&) = delete;
  Grep& operator=(const Grep&) = delete;
  Grep(Grep&&) = delete;
  Grep& operator=(Grep&&) = delete;
};
