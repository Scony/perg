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
}

void FileController::run()
{
  mStatusBar->setContent(mFile->getName());
  mStatusBar->render();

  mMinibuffer->readStr();
}
