#pragma once

#include <exception>

namespace perg::exceptions
{
struct FileOpenError : public std::exception
{
};
} // namespace perg::exceptions
