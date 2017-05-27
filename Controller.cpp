#include <vector>

#include "Controller.hpp"
#include "TextWindow.hpp"
#include "StatusBar.hpp"
#include "Minibuffer.hpp"

Controller::Controller(WINDOW * window, const std::vector<std::string>& fileNames)
{
  for (const auto& fileName : fileNames)
    try
      {
	mFiles.push_back(File(fileName));
      }
    catch (...)
      {
      }

  getmaxyx(stdscr, mRows, mCols);
}

void Controller::run()
{
  TextWindow tw(0, 0, mCols, mRows-2);
  StatusBar sb(0, mRows-2, mCols);
  Minibuffer mb(0, mRows-1, mCols);

  if (mFiles.size() == 0)
    tw.setContent(std::vector<std::string>());
  else
    {
      tw.setContent(mFiles[0].peekBuffer());
      sb.setContent(mFiles[0].getName());
    }

  tw.render();
  int ch;
  while (ch != 'q')
    {
      ch = tw.getCh();
      mb.setContent(std::to_string(ch));
    }
}
