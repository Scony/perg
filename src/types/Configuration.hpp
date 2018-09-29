#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::types
{
struct Configuration
{
  const std::string grep_keystroke;
  const std::string grep_circle_left_keystroke;
  const std::string grep_circle_right_keystroke;
  const std::string quit_keystroke;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::Configuration,
    (const std::string, grep_keystroke)(const std::string, grep_circle_left_keystroke)(
        const std::string,
        grep_circle_right_keystroke)(
        const std::string,
        quit_keystroke)); // TODO: enable variadic macros support
