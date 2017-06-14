#include "Controller.hpp"

Controller::Controller(WINDOW * window) :
  mWindow(window)
{
  getmaxyx(mWindow, mRows, mCols);
}
