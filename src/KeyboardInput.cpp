#include <poll.h>

#include "KeyboardInput.hpp"

namespace
{
std::string termKeyKeyToString(TermKey* termKey, TermKeyKey termKeyKey)
{
  char buffer[50] = {0};
  termkey_strfkey(termKey, buffer, 50, &termKeyKey, TERMKEY_FORMAT_VIM);
  return std::string{buffer};
}
} // namespace

namespace perg::tui
{
std::string KeyboardInput::awaitKeyPressed(std::chrono::milliseconds timeout)
{
  TermKeyResult ret;
  TermKeyKey retKey;
  auto& keyboardInput = getInstance();

  if (timeout.count() == 0) // blocking
  {
    ret = termkey_waitkey(keyboardInput.mTermKey, &retKey);
  }
  else // non-blocking
  {
    pollfd pollFd;
    pollFd.fd = termkey_get_fd(keyboardInput.mTermKey);
    pollFd.events = POLLIN;

    if (poll(&pollFd, 1, timeout.count()) == 0) // timeout
    {
      return "";
    }

    if (pollFd.revents & (POLLIN | POLLHUP | POLLERR))
    {
      termkey_advisereadable(keyboardInput.mTermKey);
    }

    ret = termkey_getkey(keyboardInput.mTermKey, &retKey);

    TermKeyKey tmpKey;
    while (ret == TERMKEY_RES_KEY || ret == TERMKEY_RES_AGAIN)
    {
      ret = termkey_getkey_force(keyboardInput.mTermKey, &tmpKey);
    }
  }

  return ::termKeyKeyToString(keyboardInput.mTermKey, retKey);
}
} // namespace perg::tui
