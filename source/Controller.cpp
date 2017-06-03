#include <vector>
#include <algorithm>

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
	addGrep(file);
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
	  mStatusBar->setContent(mGreps[mCurrentGid]->getName() + " (" + std::to_string(mCurrentGid) + ")");
	  mTextWindows[mCurrentGid]->render();
	  ch = mTextWindows[mCurrentGid]->getCh();
	}

      if (ch == 'q')
	break;
      else if (mCurrentGid != -1 and ch == 'g')
	{
	  auto str = mMinibuffer->readStr();
	  auto grep = mGreps[mCurrentGid]->grep(str);
	  addGrep(grep);
	  mCurrentGid = grep->getGid();
	}
      else if (mCurrentGid != -1 and ch == 544)	// CTRL+LEFT
	{
	  std::vector<int> gids;
	  for (const auto& pair : mGreps)
	    gids.push_back(pair.first);
	  std::sort(gids.begin(), gids.end());
	  for (int i = 0; i < gids.size(); i++)
	    if (gids[i] == mCurrentGid)
	      {
		if (i == 0)
		  mCurrentGid = gids[gids.size()-1];
		else
		  mCurrentGid = gids[i-1];
		break;
	      }
	}
      else if (mCurrentGid != -1 and ch == 559)	// CTRL+RIGHT
	{
	  std::vector<int> gids;
	  for (const auto& pair : mGreps)
	    gids.push_back(pair.first);
	  std::sort(gids.begin(), gids.end());
	  for (int i = 0; i < gids.size(); i++)
	    if (gids[i] == mCurrentGid)
	      {
		if (i == gids.size() - 1)
		  mCurrentGid = gids[0];
		else
		  mCurrentGid = gids[i+1];
		break;
	      }
	}
      else
	mMinibuffer->setContent(std::to_string(ch));
    }
}

void Controller::addGrep(std::shared_ptr<Grep> grep)
{
  mGreps.insert({grep->getGid(), grep});
  mTextWindows.insert({grep->getGid(), std::make_shared<TextWindow>(grep->getBuffer(), 0, 0, mCols, mRows-2)});
}
