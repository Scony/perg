#include <algorithm>

#include "FileController.hpp"

FileController::FileController(Region region,
			       std::shared_ptr<File> file,
			       std::shared_ptr<StatusBar> statusBar,
			       std::shared_ptr<Minibuffer> minibuffer) :
  mRegion(region),
  mFile(file),
  mStatusBar(statusBar),
  mMinibuffer(minibuffer)
{
  addGrep(file);
  mCurrentGrep = file->getGid();
}

Event FileController::proceed()
{
  mTextWindows[mCurrentGrep]->render();

  bool eventSupported = true;
  Event event("");

  do
    {
      mStatusBar->setContent(mGreps[mCurrentGrep]->getName() + " (" + std::to_string(mCurrentGrep) + ") " +
			     "[" + std::to_string(mGreps[mCurrentGrep]->getBuffer()->size()) + "]");
      mStatusBar->render();
      mTextWindows[mCurrentGrep]->focus();
      event = mTextWindows[mCurrentGrep]->proceed();

      if (event == Event("<>"))
	{
	}
      else if (event == Event("g"))
	{
	  auto str = mMinibuffer->readStr();
	  auto grep = mGreps[mCurrentGrep]->grep(str);

	  addGrep(grep);

	  mCurrentGrep = grep->getGid();
	  mTextWindows[mCurrentGrep]->render();
	}
      else if (event == Event("<S-Left>"))
	{
	  std::vector<unsigned> gids;
	  for (const auto& pair : mGreps)
	    gids.push_back(pair.first);
	  std::sort(gids.begin(), gids.end());
	  for (int i = 0; i < gids.size(); i++)
	    if (gids[i] == mCurrentGrep)
	      {
		if (i == 0)
		  mCurrentGrep = gids[gids.size()-1];
		else
		  mCurrentGrep = gids[i-1];
		break;
	      }

	  mTextWindows[mCurrentGrep]->render();
	}
      else if (event == Event("<S-Right>"))
	{
	  std::vector<unsigned> gids;
	  for (const auto& pair : mGreps)
	    gids.push_back(pair.first);
	  std::sort(gids.begin(), gids.end());
	  for (int i = 0; i < gids.size(); i++)
	    if (gids[i] == mCurrentGrep)
	      {
		if (i == gids.size() - 1)
		  mCurrentGrep = gids[0];
		else
		  mCurrentGrep = gids[i+1];
		break;
	      }

	  mTextWindows[mCurrentGrep]->render();
	}
      else
	eventSupported = false;
    }
  while (eventSupported);

  return event;
}

void FileController::addGrep(std::shared_ptr<Grep> grep)
{
  mGreps.insert({grep->getGid(), grep});
  mTextWindows.insert({grep->getGid(), std::make_shared<TextWindow>(Region(0, 0, mRegion.cols, mRegion.rows),
								    grep->getBuffer())});
  mCurrentGrep = grep->getGid();
}
