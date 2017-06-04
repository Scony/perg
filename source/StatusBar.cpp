#include <string>

#include "StatusBar.hpp"

StatusBar::StatusBar(int x, int y, int cols) :
  Window(x, y, cols, 1),
  mWindow(newwin(1, cols, y, x)),
  mContent(""),
  mPreviousContent(".")
{
  wattron(mWindow, A_REVERSE);
}

StatusBar::~StatusBar()
{
  delwin(mWindow);
}

void StatusBar::setContent(std::string content)
{
  mContent = content;
}

void StatusBar::render()
{
  if (mPreviousContent != mContent)
    {
      std::string rawText = "";
      if (mContent == "")
	rawText = std::string(mCols, '-');
      else
	{
	  std::string rFill = std::string(mCols - mContent.size() - 4, '-');
	  rawText = "-- " + mContent + " " + rFill;
	}

      wclear(mWindow);
      mvwprintw(mWindow, 0, 0, rawText.c_str());
      wrefresh(mWindow);

      mPreviousContent = mContent;
    }
}
