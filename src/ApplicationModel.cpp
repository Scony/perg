#include "ApplicationModel.hpp"

namespace perg::model
{
ApplicationModel::ApplicationModel(const std::vector<boost::filesystem::path>& filepaths)
    : filepaths{filepaths}
{
}
} // namespace perg::model
