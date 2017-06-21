#include "ApplicationController.hpp"
#include "StaticTextBuffer.hpp"

std::vector<std::string> welcomeWindowText = {
  "Welcome to perg, multi-grep-like tool.",
  "",
  "Quit         q",
  // "Help         h",
  // "Open file    f",
  ""
};

ApplicationController::ApplicationController(Region region) :
  mRegion(region),
  mCurrentFile(-1),
  mStatusBar(new StatusBar(Region(0, region.rows-2, region.cols, 1))),
  mMinibuffer(new Minibuffer(Region(0, region.rows-1, region.cols, 1))),
  mWelcomeWindow(new TextWindow(Region(0, 0, region.cols, region.rows-2),
				std::make_shared<StaticTextBuffer>(welcomeWindowText)))
{
}

void ApplicationController::run()
{
  mStatusBar->render();
  mMinibuffer->render();

  Event event("");
  while (event != Event("q"))
    {
      if (mCurrentFile >= 0)
	event = mFileControllers[mCurrentFile]->proceed();
      else
	{
	  mStatusBar->setContent(event.describe());
	  mStatusBar->render();

	  mWelcomeWindow->render();
	  event = mWelcomeWindow->proceed();
	}

      mMinibuffer->setContent(event.describe());
      mMinibuffer->render();
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
