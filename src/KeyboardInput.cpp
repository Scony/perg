#include <poll.h>
#include <termkey.h>

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
KeyboardInput::KeyboardInput() : termKey{termkey_new(0, 0)} {}
KeyboardInput::~KeyboardInput()
{
  termkey_destroy(termKey);
}

types::Keystroke KeyboardInput::awaitKeyPressed(std::chrono::milliseconds timeout)
{
  TermKeyResult ret;
  TermKeyKey retKey;
  auto& keyboardInput = getInstance();

  if (timeout.count() == 0) // blocking
  {
    ret = termkey_waitkey(keyboardInput.termKey, &retKey);
  }
  else // non-blocking
  {
    pollfd pollFd;
    pollFd.fd = termkey_get_fd(keyboardInput.termKey);
    pollFd.events = POLLIN;

    if (poll(&pollFd, 1, timeout.count()) == 0) // timeout
    {
      return "";
    }

    if (pollFd.revents & (POLLIN | POLLHUP | POLLERR))
    {
      termkey_advisereadable(keyboardInput.termKey);
    }

    ret = termkey_getkey(keyboardInput.termKey, &retKey);

    TermKeyKey tmpKey;
    while (ret == TERMKEY_RES_KEY || ret == TERMKEY_RES_AGAIN)
    {
      ret = termkey_getkey_force(keyboardInput.termKey, &tmpKey);
    }
  }

  return ::termKeyKeyToString(keyboardInput.termKey, retKey);
}
} // namespace perg::tui
