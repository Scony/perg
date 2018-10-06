#pragma once

#include <memory>

namespace perg::types
{
class TextView;
}

namespace perg::model
{
class GrepModel
{
 public:
  GrepModel(std::string name, std::shared_ptr<types::TextView>);

  std::string getName() const;
  std::shared_ptr<types::TextView> getTextView() const;

 private:
  std::string name;
  std::shared_ptr<types::TextView> textView;
};
} // namespace perg::model
