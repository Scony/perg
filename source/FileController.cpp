#include "FileController.hpp"

FileController::FileController(WINDOW * window,
			       std::shared_ptr<File> file,
			       std::shared_ptr<StatusBar> statusBar,
			       std::shared_ptr<Minibuffer> minibuffer) :
  Controller(window),
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
