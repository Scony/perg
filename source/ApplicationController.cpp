#include "ApplicationController.hpp"

ApplicationController::ApplicationController(Region region) :
  mRegion(region),
  mCurrentFile(-1),
  mStatusBar(new StatusBar(Region(0, region.rows-2, region.cols, 1))),
  mMinibuffer(new Minibuffer(Region(0, region.rows-1, region.cols, 1)))
{
}

void ApplicationController::run()
{
  mStatusBar->render();
  mMinibuffer->render();

  Event event(-1);
  while (event.key != 'q')
    {
      if (mCurrentFile >= 0)
	event = mFileControllers[mCurrentFile]->proceed();
      else
	mMinibuffer->readStr();	// TODO: display init screen
    }
}

void ApplicationController::openFile(const std::string& filePath)
{
  // TODO: check if file exists ?
  std::shared_ptr<File> file(new File(filePath));
  std::shared_ptr<FileController> fileController(new FileController(Region(0, 0, mRegion.cols, mRegion.rows-2),
								    file,
								    mStatusBar,
								    mMinibuffer));
  mFiles.insert({file->getGid(), file});
  mFileControllers.insert({file->getGid(), fileController});
  mCurrentFile = file->getGid();
}
