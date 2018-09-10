#include "FileModel.hpp"

namespace perg::model
{
FileModel::FileModel(boost::filesystem::path filepath) : filepath{filepath} {}

boost::filesystem::path FileModel::getFilepath() const
{
  return filepath;
}
} // namespace perg::model
