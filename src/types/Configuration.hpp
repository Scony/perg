#pragma once

#include <chrono>

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Configuration
{
  struct Keystrokes
  {
    const std::string grep;
    const std::string grepCircleLeft;
    const std::string grepCircleRight;
    const std::string quit;
    const std::string cursorDown;
    const std::string cursorUp;
    const std::string pageUp;
    const std::string pageDown;
    const std::string textBegin;
    const std::string textEnd;
    const std::string cursorRight;
    const std::string cursorLeft;
    const std::string wordRight;
    const std::string wordLeft;
    const std::string lineEnd;
    const std::string lineBegin;
  };
  const Keystrokes keystrokes;
  const std::chrono::milliseconds keyPressTimeout;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::Configuration::Keystrokes,
    (const std::string, grep)(const std::string, grepCircleLeft)(
        const std::string,
        grepCircleRight)(const std::string, quit)(const std::string, cursorDown)(
        const std::string,
        cursorUp)(const std::string, pageUp)(const std::string, pageDown)(
        const std::string,
        textBegin)(const std::string, textEnd)(const std::string, cursorRight)(
        const std::string,
        cursorLeft)(const std::string, wordRight)(const std::string, wordLeft)(
        const std::string,
        lineEnd)(const std::string, lineBegin)

);

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::Configuration,
    (const perg::types::Configuration::Keystrokes,
     keystrokes)(const std::chrono::milliseconds, keyPressTimeout));
