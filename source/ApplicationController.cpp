#include "ApplicationController.hpp"
#include "File.hpp"
#include "FileController.hpp"

ApplicationController::ApplicationController(Region region) :
  mRegion(region),
  mStatusBar(new StatusBar(0, region.rows-2, region.cols)),
  mMinibuffer(new Minibuffer(0, region.rows-1, region.cols))
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
  std::shared_ptr<FileController> fileController(new FileController(Region(0, 0, mRegion.cols, mRegion.rows-2),
								    file,
								    mStatusBar,
								    mMinibuffer));
  fileController->run();
}
