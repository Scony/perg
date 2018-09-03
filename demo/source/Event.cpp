#include "Event.hpp"
#include "Termkey.hpp"

Event::Event(TermKeyKey termKeyKey)
{
  char buffer[50] = { 0 };
  Termkey& termkey = Termkey::getInstance();
  TermKey* tk = termkey.getTermKey();

  termkey_strfkey(tk, buffer, 50, &termKeyKey, TERMKEY_FORMAT_VIM);

  mKey = std::string(buffer);
}

Event::Event(std::string keyString) :
  mKey(keyString)
{
}

bool Event::operator==(const Event& otherEvent)
{
  return mKey == otherEvent.mKey;
}

bool Event::operator!=(const Event& otherEvent)
{
  return not ((*this) == otherEvent);
}

std::string Event::describe()
{
  return mKey;
}
