#include "ApplicationModel.hpp"

namespace perg::model
{
ApplicationModel::ApplicationModel(const std::vector<std::filesystem::path>& filepaths)
    : filepaths{filepaths}
{
}
} // namespace perg::model
