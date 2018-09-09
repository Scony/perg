#pragma once

#include <chrono>
#include <string>

#include "Keystroke.hpp"

struct TermKey;

namespace perg::tui
{
class KeyboardInput
{
 public:
  static KeyboardInput& getInstance()
  {
    static KeyboardInput instance;
    return instance;
  }
  static void init() { getInstance(); }
  types::Keystroke awaitKeyPressed(
      std::chrono::milliseconds timeout = std::chrono::milliseconds{0});

 private:
  KeyboardInput();
  ~KeyboardInput();

  TermKey* mTermKey;

 public:
  KeyboardInput(const KeyboardInput&) = delete;
  KeyboardInput& operator=(const KeyboardInput&) = delete;
  KeyboardInput(KeyboardInput&&) = delete;
  KeyboardInput& operator=(KeyboardInput&&) = delete;
};
} // namespace perg::tui
