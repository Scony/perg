#include <vector>

#include "Controller.hpp"
#include "File.hpp"

Controller::Controller(WINDOW * window, const std::vector<std::string>& fileNames)
{
  mWindow = window;
  getmaxyx(mWindow, mRows, mCols);

  mCurrentGid = -1;

  for (const auto& fileName : fileNames)
    try
      {
	auto file = std::shared_ptr<Grep>(new File(fileName));
	mGreps.insert({file->getGid(), file});
	mTextWindows.insert({file->getGid(), std::make_shared<TextWindow>(0, 0, mCols, mRows-2)});
	mTextWindows[file->getGid()]->setContent(mGreps[file->getGid()]->peekBuffer());
	mCurrentGid = file->getGid();
      }
    catch (...)
      {
      }

  mStatusBar.reset(new StatusBar(0, mRows-2, mCols));
  mMinibuffer.reset(new Minibuffer(0, mRows-1, mCols));

  mStatusBar->render();
  mMinibuffer->render();
}

void Controller::run()
{
  while (true)
    {
      int ch = -1;

      if (mCurrentGid == -1)
	ch = wgetch(mWindow);		// TODO: some other window
      else
	{
	  mStatusBar->setContent(mGreps[mCurrentGid]->getName());
	  mTextWindows[mCurrentGid]->render();
	  ch = mTextWindows[mCurrentGid]->getCh();
	}

      if (ch == 'q')
	break;

      if (ch == 'g')
	{
	  auto str = mMinibuffer->readStr();
	  // TODO: add new grep and update mCurrentGid
	}
    }
}
