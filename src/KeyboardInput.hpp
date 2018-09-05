#pragma once

#include <chrono>
#include <string>
#include <termkey.h>

namespace tui
{
class KeyboardInput
{
 public:
  static void init() { getInstance(); }
  static std::string awaitKeyPressed(
      std::chrono::milliseconds timeout = std::chrono::milliseconds{0});

 private:
  static KeyboardInput& getInstance()
  {
    static KeyboardInput instance;
    return instance;
  }

  KeyboardInput() : mTermKey{termkey_new(0, 0)} {}
  ~KeyboardInput() { termkey_destroy(mTermKey); }

  TermKey* mTermKey;

 public:
  KeyboardInput(const KeyboardInput&) = delete;
  KeyboardInput& operator=(const KeyboardInput&) = delete;
  KeyboardInput(KeyboardInput&&) = delete;
  KeyboardInput& operator=(KeyboardInput&&) = delete;
};
} // namespace tui
