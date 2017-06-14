#include "ApplicationController.hpp"
#include "File.hpp"
#include "FileController.hpp"

ApplicationController::ApplicationController(WINDOW * window) :
  Controller(window),
  mStatusBar(new StatusBar(0, mRows-2, mCols)),
  mMinibuffer(new Minibuffer(0, mRows-1, mCols))
{
}

void ApplicationController::run()
{
  mStatusBar->render();
  mMinibuffer->render();

  mMinibuffer->readStr();
}

void ApplicationController::openFile(const std::string& filePath)
{
  // TODO: check if file exists ?
  auto file = std::shared_ptr<File>(new File(filePath));
  std::shared_ptr<FileController> fileController(new FileController(newwin(mRows-2, mCols, 0, 0),
								    file,
								    mStatusBar,
								    mMinibuffer));
  fileController->run();
}
