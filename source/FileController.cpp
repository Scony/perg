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
  mCurrentGid = file->getGid();
}

void FileController::run()
{
  mStatusBar->setContent(mFile->getName());
  mStatusBar->render();

  mMinibuffer->readStr();
}

void FileController::addGrep(std::shared_ptr<Grep> grep)
{
  mGreps.insert({grep->getGid(), grep});
  // mTextWindows.insert({grep->getGid(), std::make_shared<TextWindow>(grep->getBuffer(), 0, 0, mCols, mRows-2)});
}
