#include <poll.h>

#include "Termkey.hpp"

Termkey::Termkey()
{
  mTermKey = termkey_new(0, 0);
}

Termkey::~Termkey()
{
  termkey_destroy(mTermKey);
}

void Termkey::init()
{
  getInstance();
}

Event Termkey::waitEvent(unsigned timeoutMs)
{
  TermKeyResult ret;
  TermKeyKey retKey;

  if (timeoutMs == 0)		// blocking
    ret = termkey_waitkey(mTermKey, &retKey);
  else				// non-blocking
    {
      pollfd pollFd;
      pollFd.fd = termkey_get_fd(mTermKey);
      pollFd.events = POLLIN;

      if (poll(&pollFd, 1, timeoutMs) == 0) // timeout
	return Event("<>");

      if (pollFd.revents & (POLLIN|POLLHUP|POLLERR))
	termkey_advisereadable(mTermKey);

      ret = termkey_getkey(mTermKey, &retKey);

      TermKeyKey tmpKey;
      while (ret == TERMKEY_RES_KEY || ret == TERMKEY_RES_AGAIN)
	ret = termkey_getkey_force(mTermKey, &tmpKey);
    }

  return Event(retKey);
}

TermKey* Termkey::getTermKey()
{
  return mTermKey;
}
