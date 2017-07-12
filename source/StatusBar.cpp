#include <string>

#include "StatusBar.hpp"

StatusBar::StatusBar(Region region) :
  Window(region),
  mContent(""),
  mPreviousContent(".")
{
  wattron(mWindow, A_REVERSE);
}

StatusBar::~StatusBar()
{
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
      mvwprintw(mWindow, 0, 0, "%s", rawText.c_str());
      wrefresh(mWindow);

      mPreviousContent = mContent;
    }
}
