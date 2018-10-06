#include "GrepModel.hpp"

namespace perg::model
{
GrepModel::GrepModel(std::string name, std::shared_ptr<types::TextView> textView)
    : name{name}, textView{textView}
{
}

std::string GrepModel::getName() const
{
  return name;
}
std::shared_ptr<types::TextView> GrepModel::getTextView()
{
  return textView;
}
} // namespace perg::model
