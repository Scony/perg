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
