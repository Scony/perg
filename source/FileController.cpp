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
  mStatusBar->setContent(mFile->getName());
  mStatusBar->render();

  mTextWindows[mCurrentGrep]->render();
  return Event(mTextWindows[mCurrentGrep]->getCh());
}

void FileController::addGrep(std::shared_ptr<Grep> grep)
{
  mGreps.insert({grep->getGid(), grep});
  mTextWindows.insert({grep->getGid(), std::make_shared<TextWindow>(Region(0, 0, mRegion.cols, mRegion.rows-2),
								    grep->getBuffer())});
  mCurrentGrep = grep->getGid();
}
