#include "ApplicationController.hpp"
#include "File.hpp"
#include "FileController.hpp"

ApplicationController::ApplicationController(Region region) :
  mRegion(region),
  mStatusBar(new StatusBar(Region(0, region.rows-2, region.cols, 1))),
  mMinibuffer(new Minibuffer(Region(0, region.rows-1, region.cols, 1)))
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
