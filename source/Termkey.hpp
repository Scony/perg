#pragma once

#include "termkey.h"

#include "Event.hpp"

class Termkey
{
public:
  static Termkey& getInstance()
  {
    static Termkey instance;
    return instance;
  }
  static void init();

  Event waitEvent();
  TermKey* getTermKey();

private:
  Termkey();
  ~Termkey();

  TermKey* mTermKey;

public:
  Termkey(const Termkey&) = delete;
  Termkey& operator=(const Termkey&) = delete;
  Termkey(Termkey&&) = delete;
  Termkey& operator=(Termkey&&) = delete;
};
