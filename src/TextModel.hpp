#pragma once

#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>

namespace perg::model
{
struct TextModel
{
  const std::vector<std::string> lines;
};
} // namespace perg::model

BOOST_FUSION_ADAPT_STRUCT(
    perg::model::TextModel,
    (const std::vector<std::string>, lines)); // TODO: TODO: enable variadic macros support
