#pragma once

#include <boost/fusion/include/adapt_struct.hpp>

#include "Keystroke.hpp"

namespace perg::types
{
struct KeyPressed
{
  const Keystroke keystroke;
};
} // namespace perg::types

BOOST_FUSION_ADAPT_STRUCT(
    perg::types::KeyPressed,
    (const perg::types::Keystroke, keystroke)); // TODO: enable variadic macros support
