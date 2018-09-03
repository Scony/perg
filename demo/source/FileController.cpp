#include <algorithm>

#include "FileController.hpp"
#include "StaticTextBuffer.hpp"

FileController::FileController(Region region,
			       std::shared_ptr<File> file,
			       std::shared_ptr<StatusBar> statusBar,
			       std::shared_ptr<Minibuffer> minibuffer) :
  mRegion(region),
  mFile(file),
  mFocusWindow(nullptr),
  mStatusBar(statusBar),
  mMinibuffer(minibuffer)
{
  addGrep(file);
  mCurrentGrep = file->getGid();
}

Event FileController::proceed()
{
  if (mFocusWindow == nullptr)
    mTextWindows[mCurrentGrep]->render();
  else
    mFocusWindow->render();

  Event event("");

  while (true)
    {
      if (mFocusWindow == nullptr)
	{
	  mStatusBar->setContent(mGreps[mCurrentGrep]->getName() + " (" + std::to_string(mCurrentGrep) + ") " +
				 "[" + std::to_string(mGreps[mCurrentGrep]->getBuffer()->size()) + "]");
	  mStatusBar->render();
	  mTextWindows[mCurrentGrep]->focus();
	  event = mTextWindows[mCurrentGrep]->proceed();
	}
      else
	{
	  mStatusBar->setContent("[line focus]");
	  mStatusBar->render();
	  mFocusWindow->focus();
	  event = mFocusWindow->proceed();
	}

      if (mActiveHandlers.find(event.describe()) != mActiveHandlers.end())
	mActiveHandlers[event.describe()]();
      else
	break;
    }

  return event;
}

void FileController::addGrep(std::shared_ptr<Grep> grep)
{
  mGreps.insert({grep->getGid(), grep});
  mTextWindows.insert({grep->getGid(), std::make_shared<TextWindow>(Region(0, 0, mRegion.cols, mRegion.rows),
								    grep->getBuffer(),
								    mFile->getMarks())});
  mCurrentGrep = grep->getGid();
}

void FileController::nopHandler()
{
}

void FileController::grepHandler()
{
  auto str = mMinibuffer->readStr();
  auto grep = mGreps[mCurrentGrep]->grep(str);

  addGrep(grep);

  mCurrentGrep = grep->getGid();
  mTextWindows[mCurrentGrep]->render();
}

void FileController::circleGrepsLeftHandler()
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

void FileController::circleGrepsRightHandler()
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

void FileController::focusHandler()
{
  std::string currentLine = mTextWindows[mCurrentGrep]->getCurrentLine();
  std::vector<Line> lineFragments;

  // algorithm
  for (unsigned pos = 0; pos < currentLine.length(); pos += mRegion.cols)
    lineFragments.push_back({0, currentLine.substr(pos, mRegion.cols)});

  mFocusWindow.reset(new TextWindow(Region(0, 0, mRegion.cols, mRegion.rows),
				    std::make_shared<StaticTextBuffer>(lineFragments)));

  mActiveHandlers = {
    {"<>", std::bind(&FileController::nopHandler, this)},
    {"q", std::bind(&FileController::focusReleaseHandler, this)},
  };
}

void FileController::focusReleaseHandler()
{
  mFocusWindow.reset();

  mActiveHandlers = {
    {"<>", std::bind(&FileController::nopHandler, this)},
    {"g", std::bind(&FileController::grepHandler, this)},
    {"<M-Up>", std::bind(&FileController::circleGrepsLeftHandler, this)},
    {"<M-Down>", std::bind(&FileController::circleGrepsRightHandler, this)},
    {"f", std::bind(&FileController::focusHandler, this)},
  };

  mTextWindows[mCurrentGrep]->render();
}

void FileController::markHandler()
{
  std::string textToMark = mTextWindows[mCurrentGrep]->getSelectedText();
  if (textToMark != "")
    {
      auto marks = mFile->getMarks();
      auto searchResult = std::find_if(marks->begin(), marks->end(), [textToMark](const Mark& mark) {
	  return textToMark == mark.getText();
	});

      if (searchResult == marks->end())
      	marks->push_back(Mark(textToMark));
      else
      	marks->erase(searchResult);
    }
}
