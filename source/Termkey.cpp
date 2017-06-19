#include "Termkey.hpp"

Termkey::Termkey()
{
  tk = termkey_new(0, 0);
}

Termkey::~Termkey()
{
  termkey_destroy(tk);
}

void Termkey::init()
{
  getInstance();
}

Event Termkey::waitEvent()
{
  TermKeyResult ret;
  TermKeyKey xkey;

  ret = termkey_waitkey(tk, &xkey);

  return Event((int)'q');
}
