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

Event Termkey::waitEvent()
{
  TermKeyResult ret;
  TermKeyKey xkey;

  ret = termkey_waitkey(mTermKey, &xkey);

  return Event(xkey);
}

TermKey* Termkey::getTermKey()
{
  return mTermKey;
}
